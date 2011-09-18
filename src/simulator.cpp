#include <iostream>
#include <valarray>
#include "simulator.h"
#include "capa.h"
#include "util.h"
#include "math_vector.h"
using namespace std;
using math::sign;
using math::sigmoid;

simulator::simulator(size_t patrones, size_t percepciones, size_t salidas, ostream *out):
	input(patrones, vector(percepciones+1)), 
	result(patrones, vector(salidas) ), 
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
	float error = test();
	return error<tol;
}

float simulator::test(){ //devolver el error en las salidas
	vector error(input.size());

	for(size_t K=0; K<input.size(); ++K){
		vector sal=test(K);
		if(sal.size() != result[K].size())
			throw "simulator::test";
		error[K] = math::norm1( sal-result[K] );

	}
	return math::norm1(error)/error.size();
}


simulator::vector simulator::test(simulator::vector v){
	for(size_t L=0; L<network.size(); ++L)
		math::assign( v, network[L].test(v) );
	return v;
}

int simulator::train(size_t cant, float success_rate, float error_umbral){
	for(size_t epoch=0; epoch<cant; ++epoch){
		for(size_t K=0; K<input.size(); ++K){
			vector sal = test(K);

			if(sal.size() != result[K].size())
				throw "simulator::test";
			
			vector delta = result[K]-sal;
			for(size_t L=network.size(); L>0; --L)
				math::assign(delta, network[L-1].error(delta));
			for(size_t L=0; L<network.size(); ++L)
				network[L].update();
		}
		//graph();
		if( done(success_rate, error_umbral) )
			return epoch+1;
		
	}
	return -1;
}

void simulator::graph(){
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
}

