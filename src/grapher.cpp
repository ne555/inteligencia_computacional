#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <GL/glut.h>

#include <unistd.h>
using namespace std;

const float 
	white[] = {1, 1, 1, 1}, 
	red[]   = {1, 0, 0, 1}, 
	green[] = {0, 1, 0, 1}, 
	blue[]  = {0, 0, 1, 1}, 
	black[] = {0, 0, 0, 1}, 
	dark_red[]   = {.5, 0, 0, 1}, 
	dark_green[] = {0, .5, 0, 1}, 
	dark_blue[]  = {0, 0, .5, 1}, 
	light_red[]   = {1, 0.75, 0.75, 1}, 
	light_green[] = {0.75, 1, 0.75, 1}, 
	light_blue[]  = {0.75, 0.75, 1, 1};

int width=480, height=480;

bool last = false;

vector< vector<float> > points;
vector<int> clase;

void display();
void reshape(int w, int h);
void draw(int id);
void axis(const float *color);
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_STENCIL | GLUT_ACCUM);
	glutInitWindowSize(width,height); glutInitWindowPosition(50,50);
	glutCreateWindow("Graficador de puntos de colores");
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutIdleFunc(wait_for_input);

	glClearColor( white[0], white[1], white[2], 1);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();

	const float factor=0.5;
	glScaled(factor,factor,factor);
	
	glEnable(GL_STENCIL_TEST);
	glClearStencil(1);
	glLineWidth(4);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glStencilFunc(GL_EQUAL, 0, ~0);
	//glAccum(GL_RETURN, 1);
	//glStencilFunc(GL_EQUAL, 1, ~0);

	draw(-1);
	glutSwapBuffers();

}

void fixed_background(){
	glPointSize(5);

	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 0, ~0);
	glStencilOp(GL_KEEP,GL_ZERO,GL_ZERO);

	axis(black);
	glColor3fv(red); draw(1);
	glColor3fv(dark_blue); draw(-1);

	glColor3fv(blue);

	glStencilFunc(GL_EQUAL, 1, ~0);
	glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
	glAccum(GL_LOAD, 1);

	glPointSize(3);
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

void draw(int id){
	glBegin(GL_POINTS);{
		for(size_t K=0; K<points.size(); ++K){
			if(clase[K] == id)
				glVertex2f(points[K][0], points[K][1]);}
	};glEnd();
}

void axis(const float *color){
	glColor4fv( color );
	glBegin(GL_LINES);{
		glVertex2i(-1, 0);
		glVertex2i( 1, 0);
		glVertex2i( 0,-1);
		glVertex2i( 0, 1);
	};glEnd();
}

void wait_for_input(){
	static bool first_time=true;
	size_t n;
	cin>>n; //compatibilidad con la prueba
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if(not cin){
		glutIdleFunc(NULL);
		last = true;
		glutPostRedisplay();
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

