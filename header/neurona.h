#ifndef NEURONA_H
#define NEURONA_H

#include <iostream>
#include <valarray>

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

	neurona(int p, value_type alpha, value_type momentum); 
	//input es la entrada aumentada (la correspondiente al umbral es siempre 1)
	value_type output(const vector &input) const; 
	void train(const vector &input, value_type delta); 
	void print(std::ostream &out) const;

	vector error(value_type delta) const;

	void init(); //error prone

	void structure(){
		using std::cerr;
		cerr << "pesos " << weight.size() << '\n';
	}

private:
	vector weight, delta_weight;
	value_type alpha, momentum; 
};

#endif

