#include "neurona.h"
#include "util.h"
#include <iostream>
#include <algorithm>
using namespace std;

neurona::neurona(int p, value_type alpha):
	weight(p+1), alpha(alpha){}

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
	return math::sigmoid( weight.dot(input) );
}

void neurona::train(const vector &input, value_type delta){
	weight += alpha*delta*input;
}

void neurona::print(ostream &out){
	for(size_t K=0; K<weight.size(); ++K)
		out << weight[K] << ' ';
	
	out << endl;
}

neurona::vector neurona::error(neurona::value_type delta){
	return vector(delta*weight);
}

