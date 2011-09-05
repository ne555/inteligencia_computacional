#ifndef NEURONA_H
#define NEURONA_H
//#include <valarray>
#include <iostream>
#include "math_vector.h"

/*
	Perceptron simple
	y = f( w_i x_i )
	w'_i = w_i + gamma*error*x_i

	f = sigmoid
	Salida es un real
*/

class neurona{
public:
	typedef float value_type;
	typedef std::valarray<value_type> vector;

	//neurona(){}
	neurona(int p, value_type gamma); //, value_type dead_zone);
	//input es la entrada aumentada (la correspondiente al umbral es siempre 1)
	value_type test(const vector &input); 
	void train(const vector &input, value_type delta); 
	void print(std::ostream &out);

	vector error(value_type delta);

	void init(); //error prone

//private:
	//value_type delta;
	vector weight;
	value_type alpha; //, dead_zone;
};

#endif

