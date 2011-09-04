#include <iostream>
#include <valarray>
#include "simulator.h"
#include "capa.h"
#include "util.h"
using namespace std;
using math::sign;
using math::sigmoid;

simulator::simulator(size_t patrones, size_t percepciones, size_t salidas, ostream *out):
	input(vector(percepciones+1), patrones), 
	result(vector(salidas), patrones), 
	out(out){}

static bool equal_sign(const simulator::vector &a, const simulator::vector &b){
	for(size_t K=0; K<a.size(); ++K)
		if( sign(a[K])!=sign(b[K]) )
			return false;
	return true;
}

void simulator::addlayer(size_t n, float alpha){
	size_t in;
	if( network.empty() )
		in = input[0].size()-1;
	else
		in = network.back().size();
	
	network.push_back( capa(n, in, alpha) );
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

bool simulator::done(float success, float error){
	return test() > success;
}

float simulator::test(){ //devolver el procentaje de aciertos y el error en las salidas
	vector error(input.size());
	int aciertos=0;
	for(size_t K=0; K<input.size(); ++K){
		vector sal=output(K);
		error[K] = vector(sal-result[K]).norm2();
		if( equal_sign(sal, result[K]) )
			aciertos++;
	}
	return float(aciertos)/input.size();
}


simulator::vector simulator::output(size_t index){
	vector output_=input[index];
	for(size_t L=0; L<network.size(); ++L)
		output_ = network[L].test(output_);
	return output_;
}

int simulator::train(size_t cant, float success_rate, float error_umbral){
	cerr << "Inicio del entrenamiento \n";
	cerr << "Epocas " << cant << '\n';
	cerr << "Success " << success_rate << '\n';
	cerr << "Input " << input.size() << "\n";

	for(size_t epoch=0; epoch<cant; ++epoch){
		for(size_t K=0; K<input.size(); ++K){
			vector sal = output(K);
			vector delta=vector(result[K]-sal);

			for(size_t L=network.size(); L>0; --L)
				delta = network[L-1].error(delta);

			for(size_t L=0; L<network.size(); ++L)
				network[L].update();
		}
		//print();
		graph();
		if( done(success_rate, error_umbral) )
			return epoch+1;
	}
	return -1;
}

void simulator::graph(){
	#if 0
	cout << input.size() << endl;
	for(size_t K=0; K<input.size(); ++K){
		cout << input[K][0] << ' ' << input[K][1] << ' ';
		cout << math::sign(output(K)[0]) << endl;
	}
	#else
	const int n=50;
	cout << n*n << endl;
	for(int K=0; K<n; ++K){
		for(int L=0; L<n; ++L){
			float x = K/float(n)*3.f-1.5, y = L/float(n)*3.f-1.5;
			cout << x << ' ' << y << ' ';
			cout << out_(x,y) << endl;
		}
	}
	#endif
}

