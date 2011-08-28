#include "neurona.h"
#include "util.h"
#include <iostream>
#include <algorithm>
using namespace std;

neurona::neurona(int p, value_type gamma, value_type dead_zone):
	weight(p+1), gamma(gamma), dead_zone(dead_zone){
	const value_type ratio=1;
	generate_n(
		&weight[0],
		weight.size(),
		randomize<value_type>(-ratio,ratio)
	);
}

int neurona::test(const vector &input, int expect){ 
	return expect-sign( weight.dot(input) );
}

void neurona::train(const vector &input, int expect){
	float error = weight.dot(input);
	int correction = ( fabs(error)<dead_zone )? expect: expect-sign(error);

	weight += gamma*correction * input/input.norm2();
}

void neurona::print(ostream &out){
	out << "plot [-2:2] [-2:2] \"./input.txt\" using 1:2 with points";
	out << ", " << -weight[1]/weight[0] << "*x + "<<-weight[2]/weight[0]<<'\n';
}

