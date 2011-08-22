#include <iostream>
#include <valarray>
#include "simulator.h"
using namespace std;

simulator::simulator(size_t n, size_t p, value_type gamma): 
	result(n), input(vector(p+1), n), simple(p, gamma) {}

void simulator::read(istream &in){
	const size_t n=input.size(), p=input[0].size()-1;

	//cerr << "Lectura: cantidad " << n << " percepcionoes " << p << '\n';

	for(size_t K=0; K<n; ++K){
		for(size_t L=0; L<p; ++L)
			in >> input[K][L];
			//cin.ignore(); //damn csv file
		input[K][p] = 1; //entrada extendida
		in >> result[K];
	}
}

bool simulator::done(float success){
	return test() > success;
}

float simulator::test(){
	const size_t n = input.size();
	std:://cerr << "Test " << n << '\n';

	valarray<int> error(n);
	for(int L=0; L<n; ++L)
		error[L] = simple.test(input[L], result[L]);

	size_t cant = 
		count(
			&error[0],
			&error[0]+error.size(),
			0
		);
	
	return float(cant)/error.size();
}

int simulator::train(size_t cant, float success_rate){
	const size_t n = input.size();
	//cerr << "Entrenamiento " << n << ' ' << cant << '\n';
	//cerr << n << ' ' << result.size() << '\n';

	for(size_t K=0; K<cant; ++K){
		for(int L=0; L<n; ++L)
			simple.train(input[L], result[L]);

		if( done(success_rate) )
			return K+1;
	}
	return -1;
}

