#include <valarray>
#include "neurona.h"
#include "capa.h"
#include "util.h"

using namespace std;

capa::capa(size_t n, size_t in, value_type alpha): 
	layer(neurona(in, alpha), n), delta(n), salida(n), input(1, in+1) {
	for(size_t K=0; K<layer.size(); ++K) layer[K].init(); 
}

void capa::update(){
	for(size_t K=0; K<layer.size(); ++K)
		layer[K].train(input,delta[K]);
}

capa::vector capa::test(const capa::vector &input_){
	for(size_t K=0; K<input_.size(); ++K)
		input[K] = input_[K];

	for(size_t K=0; K<salida.size(); ++K)
		salida[K] = layer[K].test(input);

	return salida;
}

capa::vector capa::error(const capa::vector &d){
	delta = d*(1-salida*salida)/2;

	vector next(input.size());
	for(size_t K=0; K<delta.size(); ++K)
		next += layer[K].error(delta[K]);

	return next;
}

size_t capa::size(){
	return layer.size();
}

