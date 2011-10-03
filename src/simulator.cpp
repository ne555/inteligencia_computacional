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

	if(out){
		#if 0
		ostringstream salida;
		salida << input.size() << endl;
		for(size_t K=0; K<patrones; ++K){
			salida << input[K][0] << ' ' << input[K][1] << ' ';
			salida << result[K][0] << '\n';
		}
		fwrite( salida.str().c_str(), salida.str().size(), sizeof(char), out ); 
		#else
		fprintf(out, "%lu\n", input.size());
		for(size_t K=0; K<input.size(); ++K)
			fprintf( out, "%f %f %d\n", input[K][0], input[K][1], math::sign(result[K][0]) );
		fflush(out);
		#endif
	}
}

bool simulator::done(float success, float tol){
	float error = test();
	//return error<tol;
	return error>success;
}

float simulator::test(){ //devolver el error en las salidas
	#if 0
	vector error(input.size());

	for(size_t K=0; K<input.size(); ++K){
		vector sal=red.output(input[K]);
		//if(sal.size() != result[K].size())
		//	throw "simulator::test";
		error[K] = math::norm1( sal-result[K] );
	}
	return math::norm1(error)/error.size();
	#else
	int acierto=0;
	for(size_t K=0; K<input.size(); ++K){
		float sal=red.output(input[K])[0];
		if( math::sign(sal) == math::sign(result[K][0]) )
			acierto++;
	}
	return 1-float(acierto)/input.size();
	#endif

}

int simulator::train(size_t cant, float success_rate, float error_umbral){
	for(size_t epoch=0; epoch<cant; ++epoch){
		for(size_t K=0; K<input.size(); ++K)
			red.train(input[K], result[K]);
		
		if(out)
			graph();
		if( done(success_rate, error_umbral) )
			return epoch+1;
	}
	return -1;
}

void simulator::graph(){
	const size_t n=200;
	const float limit=2.f;
	//ostringstream salida;
	//salida << n*n << endl; //solo se visualiza con dos percepciones
	fprintf(out, "%lu\n", n*n);
	for(size_t K=0; K<n; ++K){
		for(size_t L=0; L<n; ++L){
			float x = K/float(n)*limit*2 - limit, y = L/float(n)*limit*2 - limit;
			vector v(3);
			v[0] = x; v[1] = y; v[2] = 1;
	//		salida << x << ' ' << y << ' ';
	//		salida << math::sign(red.output(v)[0]) << endl;
			fprintf( out, "%f %f %d\n", v[0], v[1], math::sign(red.output(v)[0]) );
		}
	}
	fflush(out);
	//fwrite( salida.str().c_str(), salida.str().size(), sizeof(char), out ); 
}

