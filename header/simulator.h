#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include "capa.h"
#include "math_vector.h"
#include "util.h"

class simulator{
public:
	typedef capa::value_type value_type;
	typedef capa::vector vector;

	typedef std::vector<vector> matrix;
	typedef std::vector<capa> container;

	simulator(size_t patrones, size_t percepciones, size_t salidas, std::ostream *out=NULL);
	void read(std::istream &in);
	value_type test();
	int train(size_t cant, float success_rate, float error);
	vector test(vector v);
	//agrega al final. La ultima debe ser la capa de salida (error prone)
	//solo llamarse luego de cargar los datos
	void addlayer(size_t n, value_type alpha, value_type momentum);

	//int out_(std::vector<double> aux){

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
	inline vector test(size_t index){
		return test(input[index]);
	}

	void print_result();

	matrix input, result; //, prev_error, actual_error;
	container network;

	float prev_error, actual_error;

	std::ostream *out;
};

#endif

