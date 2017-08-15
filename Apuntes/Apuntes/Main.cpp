#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"

void GameLoop() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// WARNING OPENGL VIEJITO DEPRECATED
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
	glutSwapBuffers();
}

using namespace std;
/*********************************************************
Materia: Gráficas Computacionales
Fecha: 14 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

int main(int argc, char* argv[])
{
	//inicializa freglut
	//este crea ventana
	//en donde se dibuja
	glutInit(&argc, argv);
	//INICIA EL CONTEXTO DE OPENGL; ESTO SON SUS CAPACIDADES GRAFICAS
	//En este caso se usa pipeline clasico
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//freeglut nos permite configurar eventos que ocurren en la ventana
	//nos interesa cuando alguien cierra la ventana, en ese caso se deja de renderear la escena.

	//configuramos el framebuffer, true color RGBA profundidad y un segundo buffer para rendereo
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	//la ventana 
	glutInitWindowSize(400,400);

	//su titulo e inicialización
	glutCreateWindow("HELLO WORLD GL ");

	glutDisplayFunc(GameLoop);

	//inicializa glew y se encarga de obtener el api de opengl de nuestra video card
	glewInit();

	//Config OpenGL
	//este es el color por default en el buffer del color
	glClearColor(1.0f,1.0f,0.5f,1.0f);

	//Inicia la aplicación, el main se pausa en esta linea hasta que se cierre la ventana
	glutMainLoop();

	/*-------------------------------------------------------------------------------------------------------
	cout << "Circle    ++++++++++++++++++++++++++++++++++++++" << endl;
	//Costructor basico;
	Circle circulo;
	cout << "Radius: ";
	cout << circulo.GetRadius() << endl;

	//Costructor parametros;
	Circle circulo2(2.0, "green");
	cout << "Radius: ";
	cout << circulo2.GetRadius() << endl;

	cout << "Rectangle    ++++++++++++++++++++++++++++++++++++++" << endl;
	//Costructor basico;
	Rectangle rec;
	cout << "Area: ";
	cout << rec.GetArea() << endl;

	//Costructor parametros;
	Rectangle rec2(2.0f, 4.0f);
	cout << "Perimeter: ";
	cout << rec2.GetPerimeter() << endl;

	cin.get();
	*/
	return 0;
}