#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <valarray>
#include <iostream>
#include "neurona.h"

class simulator{
public:
	typedef neurona::value_type value_type;
	typedef std::valarray<value_type> vector;
	typedef std::valarray<vector> matrix;

	simulator(size_t n, size_t p, value_type gamma, std::ostream *out=NULL);
	void read(std::istream &in);
	float test();
	int train(size_t cant, float success_rate);

private:
	bool done(float success);

	vector result;
	matrix input;
	neurona simple;

	std::ostream *out;
};

#endif

