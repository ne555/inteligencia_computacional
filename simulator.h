#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <valarray>
#include <iostream>

class simulator{
	typedef float value_type;
	typedef std::valarray<value_type> vector;
	typedef std::valarray<vector> matrix;
private:
	vector result;
	matrix input;
public:
	simulator(size_t n, size_t p);
	void read(std::ifstream &in);
};

#endif

