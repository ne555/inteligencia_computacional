#include <iostream>
#include <valarray>
#include "simulator.h"
#include "capa.h"
#include "util.h"
using namespace std;
using math::sign;
using math::sigmoid;

simulator::simulator(size_t patrones, size_t percepciones, size_t salidas, ostream *out):
	input(patrones, vector(percepciones+1)), 
	result(patrones, vector(salidas) ), 
	//prev_error(patrones, vector(salidas) ), 
	//actual_error(patrones, vector(salidas) ), 
	out(out){}

static bool equal_sign(const simulator::vector &a, const simulator::vector &b){
	for(size_t K=0; K<a.size(); ++K)
		if( sign(a[K])!=sign(b[K]) )
			return false;
	return true;
}

void simulator::addlayer(size_t n, float alpha, float momentum){
	size_t cant_entradas;
	if( network.empty() )
		cant_entradas = input[0].size()-1;
	else
		cant_entradas = network.back().size();
	
	network.push_back( capa(n, cant_entradas, alpha, momentum) );
}

void simulator::read(istream &in){
	const size_t n=input.size(), p=input[0].size()-1, s=result[0].size();

	for(size_t K=0; K<n; ++K){
		for(size_t L=0; L<p; ++L){
			in >> input[K][L];
			in.ignore(); //csv o ssv funciona
		}
		input[K][p] = 1; //entrada extendida
		
		for(size_t L=0; L<s; ++L){
			in >> result[K][L];
			in.ignore(); //csv o ssv funciona
		}
	}
}

bool simulator::done(float success, float tol){
	//vector error(input.size()), diff(input.size());
	//for(size_t K=0; K<prev_error.size(); ++K){
	//	diff[K] = math::norm2( actual_error[K]-prev_error[K] );
	//	error[K] = math::norm2( actual_error[K] );	
	//}
	//float umbral = math::norm2(diff)/diff.size();
	//float umbral = fabs(actual_error - prev_error)/actual_error;
	//cerr << "Diff " << umbral << '\n';
	cerr << "Error " << actual_error << ' ' << tol << '\n';

	//prev_error = actual_error;
		
	if( test() > success and actual_error<tol )
		cerr << "Meansaje alusivo de fin final " << actual_error << ' ' << tol << '\n';

	return ( test() > success and actual_error<tol );
}

float simulator::test(){ //devolver el procentaje de aciertos y el error en las salidas
	vector error(input.size());
	int aciertos=0;

	for(size_t K=0; K<input.size(); ++K){
		vector sal=test(K);
		if(sal.size() != result[K].size()){
			cerr << "Sizes don't match " << sal.size() << ' ' << result[K].size() << '\n';
			if(K) cerr << result[K].size() << '\n';
			else cerr << "K es 0\n";
			throw "simulator::test";
		}
		error[K] = math::norm1( sal-result[K] );

		if( equal_sign(sal, result[K]) )
			aciertos++;
	}
	actual_error = math::norm1(error)/error.size();

	return float(aciertos)/input.size();
}


simulator::vector simulator::test(simulator::vector v){
	for(size_t L=0; L<network.size(); ++L)
		math::assign( v, network[L].test(v) );
	return v;
}

int simulator::train(size_t cant, float success_rate, float error_umbral){
	cerr << "Inicio del entrenamiento \n";
	cerr << "Epocas " << cant << '\n';
	cerr << "Success " << success_rate << '\n';
	cerr << "Input " << input.size() << "\n";

	cerr << "Structure " << network.size() << '\n';
	for(size_t K=0; K<network.size(); ++K)
		cerr << network[K].size() << ' ';
	cerr << endl;

	for(size_t epoch=0; epoch<cant; ++epoch){
		for(size_t K=0; K<input.size(); ++K){
			vector sal = test(K);

		if(sal.size() != result[K].size()){
			cerr << "Sizes don't match " << sal.size() << ' ' << result[K].size() << '\n';
			if(K) cerr << result[K].size() << '\n';
			else cerr << "K es 0\n";
			throw "simulator::test";
		}
			vector delta = result[K]-sal;

			for(size_t L=network.size(); L>0; --L)
				math::assign(delta, network[L-1].error(delta));

			for(size_t L=0; L<network.size(); ++L)
				network[L].update();
		}
		graph();
		if( done(success_rate, error_umbral) )
			return epoch+1;
	}
	return -1;
}

void simulator::graph(){
	#if 1
	const int n=90;
	const float limit=2.f;
	cout << n*n << ' ' << 2 << endl; //solo se visualiza con dos percepciones
	for(int K=0; K<n; ++K){
		for(int L=0; L<n; ++L){
			float x = K/float(n)*limit*2 - limit, y = L/float(n)*limit*2 - limit;
			vector v(2);
			v[0] = x;
			v[1] = y;
			cout << x << ' ' << y << ' ';
			cout << math::sign(test(v)[0]) << endl;
		}
	}
	#else
	cout << input.size() << endl;
	for(size_t K=0; K<input.size(); ++K){
		cout << input[K][0] << ' ' << input[K][1] << ' ';
		cout << math::sign(test(K)[0]) << endl;
	}
	#endif
}

