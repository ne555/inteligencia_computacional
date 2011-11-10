#include <iostream>
#include <sstream>
#include <cstdio>
#include <valarray>
#include "simulator.h"
#include "capa.h"
#include "util.h"
#include "math_vector.h"

using namespace std;
using math::sign;
using math::sigmoid;

simulator::simulator(size_t percepciones, size_t salidas, FILE *out):
	percepciones(percepciones),
	salidas(salidas),
	red(percepciones, salidas),
	out(out){}

void simulator::addlayer(size_t n, value_type alpha, value_type momentum){
	red.addlayer(n,alpha,momentum);
}

void simulator::read(std::istream &in){
	int patrones;
	in >> patrones;
	input.clear(); result.clear();
	input.resize(patrones, vector(percepciones+1));
	result.resize(patrones, vector(-1, salidas+1) );

	for(size_t K=0; K<patrones; ++K){
		for(size_t L=0; L<percepciones; ++L)
			in >> input[K][L];

		int clase;
		in>>clase;
		result[K][clase] = 1;
		
		input[K][percepciones] = 1; //entrada extendida
		result[K][salidas] = 1; //entrada extendida
	}

	if(out){
		fprintf(out, "%lu\n", input.size());
		for(size_t K=0; K<input.size(); ++K)
			fprintf( out, "%f %f %d\n", input[K][0], input[K][1], math::sign(result[K][0]) );
		fflush(out);
	}
}

bool simulator::done(float success, float tol){
	float error = test();
	return error>success;
}

static bool equal_sign( const simulator::vector &a, const simulator::vector &b){
	for(size_t K=0; K<a.size(); ++K)
		if( math::sign(a[K]) != math::sign(b[K]) )
			return false;
	return true;
}

float simulator::test(){ //devolver el error en las salidas
	int acierto=0;
	for(size_t K=0; K<input.size(); ++K){
		vector sal=red.output(input[K]);
		//if( math::sign(sal) == math::sign(result[K][0]) )
		if( equal_sign(sal, result[K]) )
			acierto++;
	}
	cerr <<  acierto << ' ' << float(acierto)/input.size() << '\n';
	return float(acierto)/input.size();
}

int simulator::train(size_t cant, float success_rate, float error_umbral){
	cerr << "inicio del entrenamiento\n";
	for(size_t epoch=0; epoch<cant; ++epoch){
		for(size_t K=0; K<input.size(); ++K)
			red.train(input[K], result[K]);
		
		if(out) graph();
		cerr << "T " << epoch << ' ' ;
		if( done(success_rate, error_umbral) )
			return epoch+1;
	}
	return -1;
}

void simulator::graph(){
	const size_t n=200;
	const float limit=2.f;
	fprintf(out, "%lu\n", n*n);
	for(size_t K=0; K<n; ++K){
		for(size_t L=0; L<n; ++L){
			float x = K/float(n)*limit*2 - limit, y = L/float(n)*limit*2 - limit;
			vector v(3);
			v[0] = x; v[1] = y; v[2] = 1;
			fprintf( out, "%f %f %d\n", v[0], v[1], math::sign(red.output(v)[0]) );
		}
	}
	fflush(out);
}

void simulator::classify(std::ostream &output){
	for(size_t L=0; L<input.size(); ++L){
		vector sal=red.output(input[L]);
		size_t K;
		for(K=0; K<sal.size()-1; ++K)
			if(sal[K] > 0){
				output << K << ' ';
				break;
			}
		if(K == sal.size()-1) 
			output << K << ' ';
	}
}

