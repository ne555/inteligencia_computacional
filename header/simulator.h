#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "network.h"

	#include <iostream>
class simulator{
public:
	typedef network::value_type value_type;
	typedef network::vector vector;

	typedef std::vector<vector> matrix;
	typedef std::vector<network> container;

	simulator(size_t percepciones, size_t salidas, FILE *out=NULL);
	void read(std::istream &in);

	float test();
	int train(size_t cant, float success_rate, float error);

	//agrega al final. La ultima debe ser la network de salida (error prone)
	//solo llamarse luego de cargar los datos
	void addlayer(size_t n, value_type alpha, value_type momentum);

	void graph();

	void structure(){
		using std::cerr;
		cerr << "input " << input.size() << 'x' << input[0].size() << '\n';
		cerr << "result " << result.size() << 'x' << result[0].size() << '\n';
		red.structure();
	}

	void classify(std::ostream&);

private:
	bool done(float success, float error);

	matrix input, result; //, prev_error, actual_error;
	network red;

	size_t percepciones, salidas;

	FILE *out;
};

#endif

