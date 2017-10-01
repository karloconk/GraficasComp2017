#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include <string>
#include <vector> 
#include <glm/glm.hpp>
#include "InputFile.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Shader.h"

using namespace std;
/*********************************************************
Materia: Gr�ficas Computacionales
Fecha: 02 de Octubre del 2017
Autor: A01374526 Jos� Karlo Hurtado Corona
*********************************************************/

//manager al que le vamos a asociar todos los VBOs
GLuint vao;

//MANAGER DE los shaders (shaderProgram)
GLuint shaderProgram;
int ULTRA = 12;

//animacion
float vertsPerFrame = 0.0f;
float delta = 0.08f;

//declaro shader program y mesh
ShaderProgram sProgram;
Mesh meshF;

void Initialize() 
{
	//---------+-----------------------------------------------+-------------
	// creando toda la memoria una sola vez al inicio de la vida del programa.
	
	//Creacion del atributo de posiciones de los vertices 
	// lista de vec2
	//CLARAMENTE en el CPU y RAM
	std::vector<glm::vec2> positions;
	std::vector<glm::vec3> colors;
	
	//Esta seccion es del pentagono-----------------------
	positions.push_back(glm::vec2(0.0f, 1.0f)); //A
	positions.push_back(glm::vec2(0.0f, 0.5f)); //B
	positions.push_back(glm::vec2(1 * (glm::cos(glm::radians((float)(18)))), 1 * (glm::sin(glm::radians((float)(18))))));         //C
	positions.push_back(glm::vec2(0.5f * (glm::cos(glm::radians((float)(18)))), 0.5f * (glm::sin(glm::radians((float)(18))))));   //D
	positions.push_back(glm::vec2(1 * (glm::cos(glm::radians((float)(306)))), 1 * (glm::sin(glm::radians((float)(306))))));       //F  
	positions.push_back(glm::vec2(0.5f * (glm::cos(glm::radians((float)(306)))), 0.5f * (glm::sin(glm::radians((float)(306)))))); //E
	positions.push_back(glm::vec2(1 * (glm::cos(glm::radians((float)(234)))), 1 * (glm::sin(glm::radians((float)(234))))));       //H 
	positions.push_back(glm::vec2(0.5f * (glm::cos(glm::radians((float)(234)))), 0.5f * (glm::sin(glm::radians((float)(234)))))); //G
	positions.push_back(glm::vec2(1 * (glm::cos(glm::radians((float)(162)))), 1 * (glm::sin(glm::radians((float)(162))))));       //J 
	positions.push_back(glm::vec2(0.5f * (glm::cos(glm::radians((float)(162)))), 0.5f * (glm::sin(glm::radians((float)(162)))))); //I
	positions.push_back(glm::vec2(0.0f, 1.0f)); //A
	positions.push_back(glm::vec2(0.0f, 0.5f)); //B



	//queremis generar un manager
	//glGenVertexArrays(1,&vao);
	meshF.CreateMesh((GLint)ULTRA);

	//utilizar el VAO
	//glBindVertexArray(vao);
	//parece ser que esto ahora solo se manda a llamar abajo GameLoop

	//-------------------------------------------VBO pos
	/*Identificador del VBO de posiciones
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
	*/ //--------------------------------------------------
	meshF.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);

	/*-------------------------------------------VBO colores
	GLuint colorsVBO;
	glGenBuffers(1,&colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*colors.size(), colors.data(), GL_STATIC_DRAW);
	//PRENDEMOS EL SIGUIENTE ATRIBUTO
	glEnableVertexAttribArray(1);
	//el tres es el numero de variables en sus vectores, en este caso 3
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	//el cero aqui es que se apague el buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
	//---------------------------------------------------------
	for (int i = 0; i< ULTRA; i++)
	{
		colors.push_back(glm::vec3(0.0f, 1.0f, (float)((i*0.1f) - 0.1f)));
	}

	meshF.SetColorAttribute(colors, GL_STATIC_DRAW, 1);

	//Desactivamos el MNGR 
	glBindVertexArray(0);


	sProgram.CreateProgram();
	sProgram.Activate();
	/*----------------------------EMPIEXO A LEER LOS ARCHIVOS DE TEXTO
	//pa leer archivos
	InputFile ifile;
	// VERTEX SHADER
	//leemos
	//ifile.Read("DiscardCenter.vert");
	ifile.Read("Default.vert");
	std::string vertexSource = ifile.GetContents();
	//se crea y se guarda en una variable
	GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *vertexSource_c = (const GLchar*)vertexSource.c_str();
	// 1 codigo fuente a donde va, se pasa por referencia no por valor 
	//pasando para asignar al shader
	glShaderSource(vertexShaderHandle,1,&vertexSource_c,nullptr);
	//solo compila en busca de errores
	glCompileShader(vertexShaderHandle);
	*/
	//Vertex shader 
	//-----------------------------------------
	sProgram.AttachShader("Default.vert", GL_VERTEX_SHADER);

	/*leemos FRAGMENT SHADER
	//ifile.Read("DiscardCenter.frag");
	ifile.Read("Default.frag");
	std::string fragmentSource = ifile.GetContents();
	GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);
	*/
	sProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);

	/*	
	creamos id de mngr shader
	shaderProgram = glCreateProgram();

	//le adjuntamos los shaders
	glAttachShader(shaderProgram, vertexShaderHandle);
	glAttachShader(shaderProgram, fragmentShaderHandle);

	//Esto se hizo en lo de arriba pero no lo quiero englobar por la separacion entre los shaders
	*/

	/*
	//asociamos un buffer con indice 0 y 1 (posiciones y colores)
	glBindAttribLocation(shaderProgram, 0, "VertexPosition");
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	*/
	sProgram.SetAttribute(0, "VertexPosition");
	sProgram.SetAttribute(1, "VertexColor");

	//se cheka compatibilidad man
	//glLinkProgram(shaderProgram);
	sProgram.LinkProgram();

	/*Para config de un uniform  
	//decimos a open gl que vamos a usar 
	//ese manager(shader program)
	glUseProgram(shaderProgram);
	GLint uniformLocation = glGetUniformLocation(shaderProgram,"Resolution");
	glUniform2f(uniformLocation,400.0f,400.0f);
	glUseProgram(0);*/
	sProgram.SetUniformf("Resolution", 400.0f, 400.0f);
	sProgram.Deactivate();
}

void GameLoop() 
{
	//Limpiamos el buffer de color y de profundidad
	//siempre hcerlo alinicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//activamos con rl manafer
	//glUseProgram(shaderProgram);
	sProgram.Activate();

	//activamos el manager y se activan los dbos asociados automaticamente
	//glBindVertexArray(vao);
	//metodo, desde cual y cuantos verticesa dibujar
	//glDrawArrays(GL_TRIANGLE_FAN, 0, glm::clamp(vertsPerFrame, 0.0f, 362.0f));
	//glDrawArrays(GL_TRIANGLE_STRIP, 0,ULTRA);
	//MGMT DIES
	//glBindVertexArray(0);
	//TODO ESO ESTA EN ESTO AHORA
	meshF.Draw(GL_TRIANGLE_STRIP);

	//MGMT DIES AGGAIN
	//glUseProgram(0);
	//DIES YEAH
	sProgram.Deactivate();

	//Cuando terminamos de renderear, cambiampos buffers
	glutSwapBuffers();
	
}

void ReshapeWindow(int width, int height) 
{
	glViewport(0, 0, width, height);
}

void Idle() 
{
	//Cuando opengl entra ne modo de reposo 
	//le decimos que vuelva a llamar el gameloop 
	glutPostRedisplay();
}

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

	//su titulo e inicializaci�n
	glutCreateWindow("HELLO WORLD GL ");

	glutDisplayFunc(GameLoop);
	
	//asociamos una funicon para el cambio de resolucion de la ventana
	//se va amandar a llamar cuando alguioen cambie el tama�o
	glutReshapeFunc(ReshapeWindow);
	glutIdleFunc(Idle);
	//inicializa glew y se encarga de obtener el api de opengl de nuestra video card
	glewInit();

	//Config OpenGL
	//este es el color por default en el buffer del color
	glClearColor(1.0f,1.0f,0.5f,1.0f);

	glEnable(GL_DEPTH_TEST);
	//borrado de caras traseras, todos los triangulos CCW
	glEnable(GL_CULL_FACE);
	//No dibujar las caras de atras
	glEnable(GL_BACK);
	//std::cout << glGetString(GL_VERSION) << std::endl;

	//config inicial del programa.
	Initialize();

	//Inicia la aplicaci�n, el main se pausa en esta linea hasta que se cierre la ventana
	glutMainLoop();
	   
	return 0;
}