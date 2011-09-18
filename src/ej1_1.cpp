/*
	Perceptron multicapa
	Clasifica.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

#include "simulator.h"
#include "util.h"

using namespace std;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin [OPTIONS]\n";
		cerr << "Clasifica entre grupos.\n" << 
		"-n N \t Indica la cantidad maxima de epocas de entrenamiento\n" <<
		"-a R \t Parametro de velocidad de aprendizaje\n" <<
		"-s R \t Porcentaje de exito para detener el entrenamiento [0..1]\n" << 
		"-m R \t Termino de momento\n" << 
		"-e string \t Nombre del archivo de entrenamiento\n" << 
		"-p string \t Nombre del archivo de prueba\n" << 
		"-h \t Ayuda del programa\n";
	}

	exit (status);
}


int main(int argc, char **argv){
	//Entrada n p s
	//n = cantidad de ejemplos
	//p = cantidad de percepciones
	//s = cantidad de salidas
	srand( time(NULL) );
	//srand(42);

	int p,s,epoch=1500;
	float success=0.90, alpha=0.07, momentum=0.03;
    const char *train_file=NULL, *test_file=NULL;
	int option;
	while( (option=getopt(argc, argv, "n:a:s:m:e:p:h")) != -1 ){
		switch(option){
		case 'n': epoch=convert<int>(optarg); break;
		case 'a': alpha=convert<float>(optarg); break;
		case 's': success=convert<float>(optarg); break;
		case 'm': momentum=convert<float>(optarg); break;
		case 'e': train_file=optarg; break;
		case 'p': test_file=optarg; break;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

    if (train_file==NULL||test_file==NULL) {
        cerr << "Hay que indicar los archivos de entrenamiento y prueba" << endl;
        return EXIT_FAILURE;
    }
	ifstream train(train_file), test(test_file);

	cin>>p>>s;

	simulator benchmark(p,s,&cout);

    // Agregar capas
	int capas;
    cin >> capas;
    for (int K = 0; K < capas; K++) {
		int neuronas;
        cin >> neuronas;
        benchmark.addlayer(neuronas,alpha,momentum);
	}
	benchmark.addlayer(s,alpha,momentum);

	benchmark.read(train);
	int cant = benchmark.train(epoch, success, 0.2);
	benchmark.read(test);
	float rate = benchmark.test();

	if(cant == -1)
		cerr << "No hubo convergencia" <<endl;
	else
		cerr << "Convergencia en " << cant << " epocas" << endl;

	cerr << "Con los datos de prueba se obtuvo " << rate << " de error" <<endl;
	return EXIT_SUCCESS;
}

