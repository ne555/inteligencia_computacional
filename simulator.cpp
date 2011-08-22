#include "simulator.h"

simulator(size_t n, size_t p): result(n), input(vector(p+1), n) {}

void read(size_t n, size_t p, valarray<int> &result){
	valarray<valarray<float> > v( valarray<float>(p+1), n );
	result.resize(n);

	for(size_t K=0; K<n; ++K){
		for(size_t L=0; L<p; ++L){
			cin >> v[K][L];
			//cin.ignore(); //damn csv file
		}
		v[K][p] = 1; //entrada extendida
		cin >> result[K];
	}

	return v;
}
