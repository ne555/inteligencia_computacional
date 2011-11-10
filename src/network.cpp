#include "network.h"

#include <iostream>
#include <valarray>
#include "network.h"
#include "capa.h"
#include "util.h"
#include "math_vector.h"
using namespace std;
using math::sign;
using math::sigmoid;

network::network(size_t percepciones, size_t salidas):
	cant_entradas(percepciones),
	cant_salidas(salidas)
{	
	cache_input.push_back( vector(cant_entradas+1) ); //cache de las salidas de las capas 
	cache_delta.push_back( vector(cant_entradas+1) );
}

void network::addlayer(size_t neuronas, value_type alpha, value_type momentum){
	size_t n_entradas;
	if( red.empty() )
		n_entradas = cant_entradas;
	else
		n_entradas = red.back().size();
	
	red.push_back( capa(neuronas, n_entradas, alpha, momentum) );
	cache_input.push_back( vector(neuronas+1) ); //cache de las salidas de las capas 
	cache_delta.push_back( vector(neuronas+1) ); //cache de los errores de las capas 
}

network::vector network::output(const network::vector &v){
	cache_input[0] = v;
	for(size_t K=0; K<red.size(); ++K)
		cache_input[K+1] = red[K].output(cache_input[K]);
	return cache_input.back();;
}

void network::train(const network::vector &input, const network::vector &expected){
	output(input);
	cache_delta.back() = expected-cache_input.back();

	for(size_t K=red.size(); K>0; --K)
		cache_delta[K-1] = red[K-1].error(cache_delta[K]);
	
	for(size_t K=0; K<red.size(); ++K)
		red[K].update(cache_input[K]);
}

