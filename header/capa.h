#ifndef CAPA_H
#define CAPA_H

#include <valarray>
#include <vector>
#include "neurona.h"

class capa{
public:
	typedef neurona::value_type value_type;
	typedef neurona::vector vector;

	typedef std::valarray<vector> matrix;
	typedef std::vector<neurona> container;
	
	void update();
	vector test(const vector &input);
	vector error(const vector &delta);

	capa(size_t n, size_t in, value_type alpha, value_type momentum);
	size_t size() const;

private:
	container layer;
	vector delta, salida, input;
};

#endif

