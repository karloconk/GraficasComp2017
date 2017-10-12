#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector> 
#include <glm/glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

using namespace std;
/*********************************************************
Materia: Gráficas Computacionales
Fecha: 16 de Octubre del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

//manager al que le vamos a asociar todos los VBOs
GLuint vao;

//MANAGER DE los shaders (shaderProgram)
GLuint shaderProgram;
int ULTRA = 12 * 6;

//animacion
float vertsPerFrame = 0.0f;
float delta = 0.08f;

//declaro shader program y mesh
ShaderProgram sProgram;
Mesh meshF;

//LO del transform
Transform _transform;
Camera _camera;

void Initialize()
{
	//---------+-----------------------------------------------+-------------
	// creando toda la memoria una sola vez al inicio de la vida del programa.

	//Creacion del atributo de posiciones de los vertices 
	// lista de vec3
	//CLARAMENTE en el CPU y RAM
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> colors;

	//Esta seccion es del CUBO Y SUS VERTICes-----------------------

	//cara posterior
	positions.push_back(glm::vec3(0.0f, 0.0f, -0.5f)); //centrum --------------Right
	positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); //lowerRight
	positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); //UpperRight
	positions.push_back(glm::vec3(0.0f, 0.0f, -0.5f)); //centrum --------------Down
	positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); //LowerRight
	positions.push_back(glm::vec3(0.0f, 0.0f, -0.5f)); //centrum --------------Left
	positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); //UpperLeft
	positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.0f, 0.0f, -0.5f)); //centrum --------------Up
	positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); //UpperRight
	positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); //UpperLeft

	//Cara lateral Derecha
	positions.push_back(glm::vec3(0.5f, 0.0f, 0.0f)); //centrum --------------Right
	positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); //lowerRight
	positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); //UpperRight
	positions.push_back(glm::vec3(0.5f, 0.0f, 0.0f)); //centrum --------------Down
	positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); //LowerRight
	positions.push_back(glm::vec3(0.5f, 0.0f, 0.0f)); //centrum --------------Left
	positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); //UpperLeft
	positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.5f, 0.0f, 0.0f)); //centrum --------------Up
	positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); //UpperRight
	positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); //UpperLeft

	//cara Anterior
	positions.push_back(glm::vec3(0.0f, 0.0f, 0.5f)); //centrum --------------Right
	positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); //lowerRight
	positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); //UpperRight
	positions.push_back(glm::vec3(0.0f, 0.0f, 0.5f)); //centrum --------------Down
	positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); //LowerRight
	positions.push_back(glm::vec3(0.0f, 0.0f, 0.5f)); //centrum --------------Left
	positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); //UpperLeft
	positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.0f, 0.0f, 0.5f)); //centrum --------------Up
	positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); //UpperRight
	positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); //UpperLeft
	
	//Cara lateral Izquierda
	positions.push_back(glm::vec3(-0.5f, 0.0f, 0.0f)); //centrum --------------Right
	positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); //lowerRight
	positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); //UpperRight
	positions.push_back(glm::vec3(-0.5f, 0.0f, 0.0f)); //centrum --------------Down
	positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); //lowerLeft
	positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); //LowerRight
	positions.push_back(glm::vec3(-0.5f, 0.0f, 0.0f)); //centrum --------------Left
	positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); //UpperLeft
	positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); //lowerLeft
	positions.push_back(glm::vec3(-0.5f, 0.0f, 0.0f)); //centrum --------------Up
	positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); //UpperRight
	positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); //UpperLeft

	//Cara Arriba
	positions.push_back(glm::vec3(0.0f, 0.5f, 0.0f)); //centrum --------------Right
	positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); //lowerRight
	positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); //UpperRight
	positions.push_back(glm::vec3(0.0f, 0.5f, 0.0f)); //centrum --------------Down
	positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.5f, 0.5f, -0.5f)); //LowerRight
	positions.push_back(glm::vec3(0.0f, 0.5f, 0.0f)); //centrum --------------Left
	positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); //UpperLeft
	positions.push_back(glm::vec3(-0.5f, 0.5f, -0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.0f, 0.5f, 0.0f)); //centrum --------------Up
	positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f)); //UpperRight
	positions.push_back(glm::vec3(-0.5f, 0.5f, 0.5f)); //UpperLeft


	//Cara Abajo
	positions.push_back(glm::vec3(0.0f, -0.5f, 0.0f)); //centrum --------------Right
	positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); //lowerRight
	positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); //UpperRight
	positions.push_back(glm::vec3(0.0f, -0.5f, 0.0f)); //centrum --------------Down
	positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.5f, -0.5f, -0.5f)); //LowerRight
	positions.push_back(glm::vec3(0.0f, -0.5f, 0.0f)); //centrum --------------Left
	positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); //UpperLeft
	positions.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); //lowerLeft
	positions.push_back(glm::vec3(0.0f, -0.5f, 0.0f)); //centrum --------------Up
	positions.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); //UpperRight
	positions.push_back(glm::vec3(-0.5f, -0.5f, 0.5f)); //UpperLeft

	//COLORES
	for (int i = 0; i< ULTRA; i++) 
	{
		if (i < 12)
		{
			colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (i >= 12 && i < 24)
		{
			colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else if (i >= 24 && i < 36)
		{
			colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (i >= 36 && i < 48)
		{
			colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		}
		else if (i >= 48 && i < 60)
		{
			colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		}
		else 
		{
			colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
		}
	}

	//queremis generar un manager
	meshF.CreateMesh((GLint)ULTRA);
	meshF.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	meshF.SetColorAttribute(colors, GL_STATIC_DRAW, 1);

	//Desactivamos el MNGR 
	glBindVertexArray(0);


	sProgram.CreateProgram();
	sProgram.Activate();

	//Vertex shader 
	//-----------------------------------------
	sProgram.AttachShader("Default.vert", GL_VERTEX_SHADER);

	sProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	sProgram.SetAttribute(0, "VertexPosition");
	sProgram.SetAttribute(1, "VertexColor");

	//se cheka compatibilidad man
	sProgram.LinkProgram(); 

	sProgram.SetUniformf("Resolution", 400.0f, 400.0f);
	sProgram.Deactivate();

	_transform.SetRotation(0.0f, 0.0f, 90.0f);

	_camera.SetOrtographic(1.0f,1.0f);
}

void GameLoop() 
{
	//Limpiamos el buffer de color y de profundidad
	//siempre hcerlo alinicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//esta es la linea que hace rotar 
	//el true o false hace que rote con respecto al mundo o no 

	//_camera.MoveForward(0.0001f);
	_transform.Rotate(0.01f, 0.01f, 0.01f, false);
	//_transform.Rotate(0.0f, 0.01f, 0.0f, true );

	//activamos con rl manafer
	//glUseProgram(shaderProgram);
	sProgram.Activate();
	//sProgram.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix());
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());

	//activamos el manager y se activan los dbos asociados automaticamente
	//metodo, desde cual y cuantos verticesa dibujar
	//MGMT DIES
	meshF.Draw(GL_TRIANGLES);

	//MGMT DIES AGGAIN
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

	//su titulo e inicialización
	glutCreateWindow("HELLO WORLD GL ");

	glutDisplayFunc(GameLoop);
	
	//asociamos una funicon para el cambio de resolucion de la ventana
	//se va amandar a llamar cuando alguioen cambie el tamaño
	glutReshapeFunc(ReshapeWindow);
	glutIdleFunc(Idle);
	//inicializa glew y se encarga de obtener el api de opengl de nuestra video card
	glewInit();

	//Config OpenGL
	//este es el color por default en el buffer del color
	glClearColor(1.0f,1.0f,0.5f,1.0f);

	glEnable(GL_DEPTH_TEST);
	//borrado de caras traseras, todos los triangulos CCW
	//glEnable(GL_CULL_FACE);
	//No dibujar las caras de atras
	//glEnable(GL_BACK);
	//std::cout << glGetString(GL_VERSION) << std::endl;

	//config inicial del programa.
	Initialize();

	//Inicia la aplicación, el main se pausa en esta linea hasta que se cierre la ventana
	glutMainLoop();
	   
	return 0;
}