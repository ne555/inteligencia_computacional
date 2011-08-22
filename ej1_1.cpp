#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

#include "simulator.h"
#include "util.h"

using namespace std;

//usage
//program <train epoch(N)> gamma(R) success(R)

int main(int argc, char **argv){
	//Entrada n p 
	//n = cantidad de ejemplos
	//p = cantidad de percepciones
	srand(0);
	//ofstream out("recta.txt");
	//out << "plot [-2:2] [-2:2] \"input.txt\" using 1:2 with points";

	int n,p,epoch=1;
	float success=0.8,gamma=0.01;
	cin>>n>>p;
	int option;
	while( (option=getopt(argc, argv, "t:g:s:")) != -1 ){
		switch(option){
		case 't': 
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
	cout << "Parametros " << endl;
	cout << "Ejemplos " << n << endl;
	cout << "Percepciones " << p << endl;
	cout << "Gamma " << gamma << endl;
	cout << "epocas " << epoch << endl;
	cout << "Expected success rate %" << success*100 << endl;

	simulator benchmark(n, p, gamma);

	benchmark.read(cin);
	cerr << "lectura de entrenamiento\n";
	int cant = benchmark.train(epoch, success);

	//benchmark.read(cin);
	cerr << "lectura de prueba\n";
	float rate = benchmark.test();

	if(cant == -1)
		cout << "No hubo convergencia" <<endl;
	else
		cout << "Convergencia en " << cant << " epocas" << endl;
	//benchmark.print(cout);

	cout << "Con los datos de prueba se obtuvo %" << rate*100 << " de acierto" <<endl;
}

