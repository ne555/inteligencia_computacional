#include <iostream>
#include <valarray>
#include "simulator.h"
#include "capa.h"
#include "util.h"
#include "math_vector.h"

using namespace std;
using math::sign;
using math::sigmoid;

simulator::simulator(size_t percepciones, size_t salidas, ostream *out):
	percepciones(percepciones),
	salidas(salidas),
	red(percepciones, salidas),
	out(out){}

void simulator::addlayer(size_t n, float alpha, float momentum){
	red.addlayer(n,alpha,momentum);
}

void simulator::read(istream &in){
	size_t patrones;
	in >> patrones;
	input.resize(patrones, vector(percepciones+1));
	result.resize(patrones, vector(salidas+1) );

	for(size_t K=0; K<patrones; ++K){
		for(size_t L=0; L<percepciones; ++L){
			in >> input[K][L];
			in.ignore(); //csv o ssv funciona
		}
		
		for(size_t L=0; L<salidas; ++L){
			in >> result[K][L];
			in.ignore(); //csv o ssv funciona
		}

		input[K][percepciones] = 1; //entrada extendida
		result[K][salidas] = 1; //entrada extendida
	}
}

bool simulator::done(float success, float tol){
	float error = test();
	return error<tol;
}

float simulator::test(){ //devolver el error en las salidas
	vector error(input.size());

	for(size_t K=0; K<input.size(); ++K){
		vector sal=red.output(input[K]);
		//if(sal.size() != result[K].size())
		//	throw "simulator::test";
		error[K] = math::norm1( sal-result[K] );
	}
	return math::norm1(error)/error.size();
}

int simulator::train(size_t cant, float success_rate, float error_umbral){
	for(size_t epoch=0; epoch<cant; ++epoch){
		for(size_t K=0; K<input.size(); ++K)
			red.train(input[K], result[K]);
		
		graph();
		if( done(success_rate, error_umbral) )
			return epoch+1;
	}
	return -1;
}

void simulator::graph(){
	const int n=75;
	const float limit=2.f;
	cout << n*n << endl; //solo se visualiza con dos percepciones
	for(int K=0; K<n; ++K){
		for(int L=0; L<n; ++L){
			float x = K/float(n)*limit*2 - limit, y = L/float(n)*limit*2 - limit;
			vector v(3);
			v[0] = x;
			v[1] = y;
			v[2] = 1;
			cout << x << ' ' << y << ' ';
			cout << math::sign(red.output(v)[0]) << endl;
		}
	}
}

