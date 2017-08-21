#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include <string>
#include <vector> 
#include <glm/glm.hpp>

//manager al que le vamos a asociar todos los VBOs
GLuint vao;

void Initialize() 
{
	//---------+-----------------------------------------------+-------------
	// creando toda la memoria una sola vez al inicio de la vida del programa.
	
	//Creacion del atributo de posiciones de los vertices 
	// lista de vec2
	//CLARAMENTE en el CPU y RAM
	std::vector<glm::vec2> positions;
	positions.push_back(glm::vec2(-0.5f,-0.5f));
	positions.push_back(glm::vec2(0.5f, -0.5f));
	positions.push_back(glm::vec2(-0.5f, 0.5f));
	positions.push_back(glm::vec2(0.5f, 0.5f));
	
	//queremis generar un manager
	glGenVertexArrays(1,&vao);
	//utilizar el VAO
	glBindVertexArray(vao);

	//Identificador del VBO de posiciones
	GLuint positionsVBO;
	//Creacion del VBO de posiciones
	glGenBuffers(1,&positionsVBO);
	//Lo activamos para poder utilizarlo
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	//Creamos la memoria y la inicializamos con lis datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*positions.size(),positions.data(), GL_STATIC_DRAW);
	//Activamos el atributo en la tarjeta de video 
	glEnableVertexAttribArray(0);
	//Configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE,0, nullptr);
	//YA no vamos a utilizar este VBO en este momento
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desactivamos el MNGR
	glBindVertexArray(0);

}

void GameLoop() 
{
	//Limpiamos el buffer de color y de profundidad
	//siempre hcerlo alinicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* WARNING OPENGL VIEJITO DEPRECATED------------
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
	END WARNING------------------------------------
	*/

	//activamos el manager y se activan los dbos asociados automaticamente
	glBindVertexArray(vao);

	//metodo, desde cual y cuantos verticesa dibujar
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	//MGMT DIES
	glBindVertexArray(0);

	//Cuando terminamos de renderear, cambiampos buffers
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
	//En este caso se usa pipeline Programable
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//SOLICITANDO VERSION 4.4 DE GL 
	glutInitContextVersion(4,4);
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

	std::cout << glGetString(GL_VERSION) << std::endl;

	//config inicial del programa.
	Initialize();

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