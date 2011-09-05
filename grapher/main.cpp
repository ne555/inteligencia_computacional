#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <GL/glut.h>

#include <unistd.h>
using namespace std;

const float 
	white[] = {1,1,1,0.5},
	red[]   = {1,0,0,0.5},
	green[] = {0,1,0,0.5},
	blue[]  = {0,0,1,0.5},
	black[] = {0,0,0,0.5},
	dark_red[]   = {.5,0,0,1},
	dark_green[] = {0,.5,0,1},
	dark_blue[]  = {0,0,.5,1};

int width=480, height=480;

vector< vector<float> > points;
vector<int> clase;

void display();
void reshape(int w, int h);
void draw(const float *c1, const float *c2);
void wait_for_input();
void fixed_background();

void init();

int main(int argc, char **argv){
	glutInit(&argc, argv);
	init();
	glutMainLoop();
	return 0;
}

void init(){
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ACCUM);
	glutInitWindowSize(width,height); glutInitWindowPosition(50,50);
	glutCreateWindow("Graficador de puntos de colores");
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutIdleFunc(wait_for_input);

	glClearColor( white[0], white[1], white[2], 1);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();

	const float factor=0.5;
	glScaled(factor,factor,factor);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_POINT_SMOOTH);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glAccum(GL_RETURN, 1);
	draw(red, green);

	glutSwapBuffers();
	usleep(100e3);
}

void fixed_background(){
	glClear(GL_COLOR_BUFFER_BIT);
	draw(red, green);
	glAccum(GL_LOAD, 1);
}

void reshape(int w, int h){
	if( w==0 or h==0 ) return;
	width = w; 
	height = h;

	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,0,height,-1,1);

	glutPostRedisplay();
}

void draw(const float *c1, const float *c2){
	glPointSize(5);
	glBegin(GL_POINTS);{
		for(size_t K=0; K<points.size(); ++K){
			if(clase[K] == 1) glColor4fv( c1 );
			else glColor4fv( c2 );
			glVertex2f(points[K][0], points[K][1]);
		}
	};glEnd();
//	glPointSize(7);
//	glBegin(GL_POINTS);{
//		glColor3fv( black );
//		glVertex2f(-1, -1);
//		glVertex2f(1, -1);
//		glVertex2f(-1, 1);
//		glVertex2f(1, 1);
//	};glEnd();
}

void wait_for_input(){
	static bool first_time=true;
	int n,p;
	cin>>n>>p; //compatibilidad con la prueba
	if(not cin){
		cin.clear();
		string s;
		getline(cin,s);
		cerr << s << endl;
		glutIdleFunc(NULL);
		cerr << "Fin\n";
		return;
	}

	points.resize(n, vector<float>(2));
	clase.resize(n);
	for(size_t K=0; K<n; ++K)
		cin>>points[K][0]>>points[K][1]>>clase[K];

	if(first_time){
		first_time=false;
		fixed_background();
	}
	glutPostRedisplay();
}

