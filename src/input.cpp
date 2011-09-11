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
	if( math::norm2(v)<0.5 ) return 1; //inner
	if( math::norm2(v)<2.0 ) return -1; //middle
	return 1; //outer 
}

int hole_rect(const valarray<float> &v){
	if( 1.50<math::norm_inf(v) ) return 1; 
	if( 0.75<math::norm_inf(v) ) return -1; //middle
	return 1;
}

float offset1(float f){
	return (fabs(f)+0.75) * ((rand()%2)*2-1);
}
float offset2(float f){
	return (fabs(f)+1.5);// * ((rand()%2)*2-1);
}

int main(int argc, char **argv){
	fun oper = &hole_circ;
	srand(0);
	int n=700, p=2;
	//float ratio = 0.3;
	cout << n << ' ' << p << endl;
	#if 1
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
	#else
	for(int K=0; K<n/4; ++K){
		valarray<float> percepcion(p);
		generate_n(
			&percepcion[0],
			percepcion.size(),
			randomize<float>(-0.7,0.7)
		);
		print(
			&percepcion[0],
			&percepcion[0]+percepcion.size(),
			cout
		);
		cout << oper(percepcion) << endl;
	}
	for(int K=0; K<n/2; ++K){
		valarray<float> percepcion(p);
		generate_n(
			&percepcion[0],
			percepcion.size(),
			randomize<float>(-0.7,0.7)
		);
		percepcion = percepcion.apply( offset1 );

		print(
			&percepcion[0],
			&percepcion[0]+percepcion.size(),
			cout
		);
		cout << oper(percepcion) << endl;
	}
	for(int K=0; K<n/4; ++K){
		valarray<float> percepcion(p);
		generate_n(
			&percepcion[0],
			percepcion.size(),
			randomize<float>(-0.5,0.5)
		);
		percepcion = percepcion.apply( offset2 );

		print(
			&percepcion[0],
			&percepcion[0]+percepcion.size(),
			cout
		);
		cout << oper(percepcion) << endl;
	}
	#endif
	
	return 0;
}

