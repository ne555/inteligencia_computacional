#include <iostream>
#include <cstdlib>
#include <valarray>
#include "util.h"
using namespace std;

typedef int (*fun)(const valarray<float> &);

//int oper(const valarray<float> &v){
//	for(size_t K=0; K<v.size(); ++K)
//		if( v[K]>0 )
//			return 1;
//	return -1;
//}

int oper(const valarray<float> &v){
	int cant=0;
	for(size_t K=0; K<v.size(); ++K)
		if( v[K]>0 )
			cant++;

	if(cant%2==0) return -1;
	else return 1;
}


int main(int argc, char **argv){
	srand(0);
	int n=300, p=2;
	float ratio = 0.3;
	cout << n << ' ' << p << endl;
	for(int K=0; K<n; ++K){
		valarray<float> percepcion(p), desvio(p);
		generate_n(
			&percepcion[0],
			percepcion.size(),
			randomize<int>(0,1)
		);
		percepcion *= 2;
		percepcion -= 1; //aleatoriamente -1 o 1

		generate_n(
			&desvio[0],
			desvio.size(),
			randomize<float>(-ratio, ratio)
		);
		percepcion += desvio;
		print(
			&percepcion[0],
			&percepcion[0]+percepcion.size(),
			cout
		);
		cout << oper(percepcion) << endl;
	}
	
	return 0;
}

