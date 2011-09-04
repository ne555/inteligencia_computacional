/*
	Perceptron Simple
	Clasifica entre dos grupos, separandoles mediante un hiperplano
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

#include "simulator.h"
#include "util.h"

using namespace std;

//usage
//program <train epoch(N)> gamma(R) success(R)
void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin [OPTIONS]\n";
		cerr << "Clasifica entre dos grupos, separandoles mediante un hiperplano.\n" << 
		"-t N \t Indica la cantidad maxima de epocas de entrenamiento\n" <<
		"-g R \t Parametro de velocidad de aprendizaje\n" <<
		"-s R \t Porcentaje de exito para detener el entrenamiento [0..1]\n";
	}

	exit (status);
}


int main(int argc, char **argv){
	//Entrada n p 
	//n = cantidad de ejemplos
	//p = cantidad de percepciones
	srand( time(NULL) );
	ofstream out("recta.txt");
	out << "set terminal gif animate delay 10\n";
	out << "set output \"animate.gif\"\n" << flush;

	int n,p,epoch=200;
	float success=0.9, gamma=0.1, dead_zone=0.2;
	int option;
	while( (option=getopt(argc, argv, "t:g:s:d:h")) != -1 ){
		switch(option){
		case 't': epoch=convert<int>(optarg); break;
		case 'g': gamma=convert<float>(optarg); break;
		case 's': success=convert<float>(optarg); break;
		case 'd': dead_zone=convert<float>(optarg); break;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

	cin>>n>>p;
	#if 0
	cout << "Perceptron simple ";
	cout << "Parametros " << endl;
	cout << "Ejemplos " << n << endl;
	cout << "Percepciones " << p << endl;
	cout << "Gamma " << gamma << endl;
	cout << "epocas " << epoch << endl;
	cout << "Expected success rate %" << success*100 << endl;

	cout << "fin de informe *";
	#endif

	simulator benchmark(n,p,1,&cout);

	benchmark.read(cin);
	benchmark.addlayer(2,gamma);
	benchmark.addlayer(1,gamma);

	int cant = benchmark.train(epoch, success, 0);
	//benchmark.read(cin);
	float rate = benchmark.test();

	if(cant == -1)
		cerr << "No hubo convergencia" <<endl;
	else
		cerr << "Convergencia en " << cant << " epocas" << endl;
	
		//benchmark.print();
	//benchmark.print(cout);

	cerr << "Con los datos de prueba se obtuvo %" << rate*100 << " de acierto" <<endl;
	return EXIT_SUCCESS;
}

