#include "neurona.h"
#include "util.h"
#include <iostream>
#include <algorithm>
using namespace std;

neurona::neurona(int p, value_type gamma): 
	weight(p+1), gamma(gamma){
	const value_type ratio=1;
	generate_n(
		&weight[0],
		weight.size(),
		randomize<value_type>(-ratio,ratio)
	);
}

int neurona::test(const vector &input, int expect){ 
	return expect-sign( (weight*input).sum() );
}

void neurona::train(const vector &input, int expect){
	int error = test(input, expect);
	weight += gamma*error*input;
}

void neurona::print(ostream &out){
	out << "plot [-2:2] [-2:2] \"./input.txt\" using 1:2 with points";
	out << ", " << -weight[1]/weight[0] << "*x + "<<-weight[2]/weight[0]<<'\n';
}

