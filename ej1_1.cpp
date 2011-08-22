#include <iostream>
#include <fstream>
#include <valarray>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>

#include "neurona.h"
#include "util.h"

using namespace std;


bool done(const valarray<int> &error, float success);

//usage
//program <train epoch(N)> gamma(R) success(R)

int main(int argc, char **argv){
	//Entrada n p 
	//n = cantidad de ejemplos
	//p = cantidad de percepciones
	srand(0);
	ofstream out("recta.txt");
	out << "plot [-2:2] [-2:2] \"input.txt\" using 1:2 with points";

	int n,p,epoch=1;
	float success=0.8,gamma=0.01;
	cin>>n>>p;
	int option;
	bool train=false;
	while( (option=getopt(argc, argv, "t:g:s:")) != -1 ){
		switch(option){
		case 't': train=true;
			epoch=convert<int>(optarg); break;
		case 'g': gamma=convert<float>(optarg); break;
		case 's': success=convert<float>(optarg); break;
		default: cerr << "Unhandled option " << option << ' ' << (char)option;
			cerr << "\nUsage program [options]";
			cerr << "\noptions: <t epoch(N)> <g(R)> <e(N)> <s(R [0..1])>\n";
			return EXIT_FAILURE;
		}
	}

	cout << "Perceptron simple ";
	cout <<  ((train)? "Entrenamiento" : "Prueba") << endl;
	cout << "Parametros " << endl;
	cout << "Ejemplos " << n << endl;
	cout << "Percepciones " << p << endl;
	cout << "Gamma " << gamma << endl;
	cout << "epocas " << epoch << endl;

	valarray<int> result;
	valarray<valarray<float> > input = read(n, p, result);
	
	neurona simple(p, gamma);
	int K;
	for(K=0; K<epoch; ++K){
		valarray<int> error(n);
		if(train)
			for(int L=0; L<n; ++L){
				simple.train(input[L], result[L]);
				if(L%10==0) simple.print(out);
			}

		for(int L=0; L<n; ++L)
			error[L] = simple.test(input[L], result[L]);

		//cout << "error: " << ((error*error).sum()/4)/float(n); 
		//cout << " weights: "; simple.print(cout); cout << endl;
		if( train and done(error, success) )
			break;
	}
	cout << "Terminado luego de " << K+1 << " epocas" << endl;
	simple.print(cout);cout << endl;
	out << endl << "pause -1" << endl;
	return 0;
}

bool done(const valarray<int> &error, float success){
	size_t cant0 = 
		count(
			&error[0],
			&error[0]+error.size(),
			0
		);
	return float(cant0)/error.size() > success;
}

