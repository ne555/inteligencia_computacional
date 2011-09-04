#ifndef CAPA_H
#define CAPA_H

#include <valarray>
#include "neurona.h"
	#include <iostream>

class capa{
public:
	typedef neurona::value_type value_type;
	typedef math::vector<value_type> vector;
	typedef math::vector<vector> matrix;
	typedef math::vector<neurona> container;
	
	void update();
	vector test(const vector &input);
	vector error(const vector &delta);

	capa(size_t n, size_t in, value_type alpha);
	size_t size();

	void print(){
		for(size_t K=0; K<layer.size(); ++K) {
			std::cout << "neurona " << K << ": ";
			layer[K].print(std::cout);
		}
	}

//private:
	container layer;
	vector delta, salida, input;
};

#endif

