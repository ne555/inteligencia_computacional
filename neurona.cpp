#include "neurona.h"
#include "util.h"
#include "math_vector.h"
#include <iostream>
#include <algorithm>
using namespace std;

neurona::neurona(int p, value_type alpha, value_type momentum):
	weight(p+1), delta_weight(p+1), alpha(alpha), momentum(momentum){}

void neurona::init(){
	const value_type ratio=1;
	generate_n(
		&weight[0],
		weight.size(),
		randomize<value_type>(-ratio,ratio)
	);
}

neurona::value_type neurona::test(const vector &input){ 
	//return math::sign( weight.dot(input) );
	return math::sigmoid( math::dot(weight,input) );
}

void neurona::train(const vector &input, value_type delta){
	delta_weight = alpha*delta*input + momentum*delta_weight;
	weight += delta_weight;
	//weight += alpha*delta*input + momentum*prev_delta_weight;
	//prev_weight = temp;
}

void neurona::print(ostream &out){
	for(size_t K=0; K<weight.size(); ++K)
		out << weight[K] << ' ';
	
	out << endl;
}

neurona::vector neurona::error(neurona::value_type delta){
	return vector(delta*weight);
}

