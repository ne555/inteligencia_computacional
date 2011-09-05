#include <iostream>
#include <cstdlib>
#include <valarray>
#include "util.h"
#include "math_vector.h"
using namespace std;

typedef int (*fun)(const valarray<float> &);

int OR(const valarray<float> &v){
	for(size_t K=0; K<v.size(); ++K)
		if( v[K]>0 )
			return 1;
	return -1;
}

int XOR(const valarray<float> &v){
	int cant=0;
	for(size_t K=0; K<v.size(); ++K)
		if( v[K]>0 )
			cant++;

	if(cant%2==0) return -1;
	else return 1;
}

int circ_rect(const valarray<float> &v){
	if( math::norm_inf(v) < 1 ) return 1;
	if( math::norm2(v) > 2 ) return -1;
	return (rand()%2)*2-1;
}

int hole_circ(const valarray<float> &v){
	if( between(.5f, math::norm2(v), 2.f) ) return -1; //middle circle
	if( between(0.f, math::norm2(v), .5f) ) return 1; //inner circle
	else return 1; //outer 
}

int hole_rect(const valarray<float> &v){
	if( math::norm_inf(v) > 1 ) return 1; 
	if( between(.75f, math::norm_inf(v), 1.f) ) return -1; //middle
	return 1;
}

int main(int argc, char **argv){
	fun oper = &hole_circ;
	srand(0);
	int n=9000, p=2;
	//float ratio = 0.3;
	cout << n << ' ' << p << endl;
	for(int K=0; K<n; ++K){
		valarray<float> percepcion(p);
		generate_n(
			&percepcion[0],
			percepcion.size(),
			randomize<float>(-2,2)
		);

		print(
			&percepcion[0],
			&percepcion[0]+percepcion.size(),
			cout
		);
		cout << oper(percepcion) << endl;
	}
	
	return 0;
}

