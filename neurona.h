#ifndef NEURONA_H
#define NEURONA_H
#include <valarray>
#include <iostream>

/*
	Perceptron simple
	y = f( w_i x_i )
	w'_i = w_i + gamma*error*x_i

	La salida es un numero entero
*/

class neurona{
public:
	typedef float value_type;
	typedef std::valarray<value_type> vector;

	neurona(int p, value_type gamma);
	//input es la entrada aumentada (la correspondiente al umbral es siempre 1)
	int test(const vector &input, int expect); 
	void train(const vector &input, int expect); 
	void print(std::ostream &out);

private:
	vector weight;
	value_type gamma;
};

#endif

