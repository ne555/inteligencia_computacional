#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include "neurona.h"
#include "capa.h"
#include "math_vector.h"
#include "util.h"

class simulator{
public:
	typedef neurona::value_type value_type;
	typedef math::vector<value_type> vector;
	typedef math::vector<vector> matrix;
	typedef std::vector<capa> container;

	simulator(size_t patrones, size_t percepciones, size_t salidas, std::ostream *out=NULL);
	void read(std::istream &in);
	value_type test();
	int train(size_t cant, float success_rate, float error);
	vector output(size_t index);
	//agrega al final. La ultima debe ser la capa de salida (error prone)
	//solo llamarse luego de cargar los datos
	void addlayer(size_t n, value_type alpha);

	//int out_(std::vector<double> aux){
	int out_(value_type x, value_type y){
		vector in(2);
		in[0] = x;
		in[1] = y;
		for(size_t K=0; K<network.size(); ++K)
			in = network[K].test(in);
		return math::sign(in[0]);
	}

	void graph();

	void print(){
		for(size_t K=0; K<network.size(); ++K) {
			std::cout << "Layer " << K << '\n';
			network[K].print();
		}
		std::cout << std::endl;
	}

//private:
	bool done(float success, float error);

	matrix result;
	matrix input;
	container network;

	std::ostream *out;
};

#endif

