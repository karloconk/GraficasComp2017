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
using namespace glm;
/*********************************************************
Materia: Gráficas Computacionales
Fecha: 16 de Octubre del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

#pragma region Global Scope vars

//manager al que le vamos a asociar todos los VBOs
GLuint vao;

//MANAGER DE los shaders (shaderProgram)
GLuint shaderProgram;
int g = 9;
int ULTRA = g * 6;

//animacion
float vertsPerFrame = 0.0f;
float delta = 0.08f;

//declaro shader program y mesh
ShaderProgram sProgram;
Mesh meshF;

//LO del transform
Transform _transform;
Transform _transform2;
Transform _transform3; 
Transform _transform4;
Transform _transform5;
Camera _camera;

//se obtuvo la informacion de #pragma region de: https://msdn.microsoft.com/en-us/library/b6xkz944.aspx

#pragma endregion 

//LOS COLORES Y LOS VERTICES
vector<vec3> colores()
{
	//COLORES Distintos para cada cara
	std::vector<glm::vec3> colors;
	for (int i = 0; i< ULTRA; i++)
	{
		if (i < g)
		{
			colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (i >= g && i < (g * 2))
		{
			colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else if (i >= (g * 2) && i < (g * 3))
		{
			colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (i >= (g * 3) && i < (g * 4))
		{
			colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		}
		else if (i >= (g * 4) && i < (g * 5))
		{
			colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		}
		else
		{
			colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
		}
	}
	return colors;
}

vector<vec3> posiciones() 
{
	//Esto es un CUBO 
	std::vector<glm::vec3> positions;
	//cara posterior
	positions.push_back(glm::vec3(0.0f, 0.0f, -3.0f)); //centrum
	positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f)); //lowerRight
	positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f)); //LowerRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, -3.0f)); //UpperLeft
	positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, -3.0f)); //UpperLeft

														//Cara lateral Derecha
	positions.push_back(glm::vec3(3.0f, 0.0f, 0.0f)); //centrum 
	positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f)); //lowerRight
	positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f)); //UpperRight
	positions.push_back(glm::vec3(3.0f, -3.0f, 3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f)); //LowerRight
	positions.push_back(glm::vec3(3.0f, 3.0f, 3.0f)); //UpperLeft
	positions.push_back(glm::vec3(3.0f, -3.0f, 3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f)); //UpperRight
	positions.push_back(glm::vec3(3.0f, 3.0f, 3.0f)); //UpperLeft

													  //cara Anterior
	positions.push_back(glm::vec3(0.0f, 0.0f, 3.0f)); //centrum 
	positions.push_back(glm::vec3(3.0f, -3.0f, 3.0f)); //lowerRight
	positions.push_back(glm::vec3(3.0f, 3.0f, 3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, -3.0f, 3.0f)); //LowerRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f)); //UpperLeft
	positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, 3.0f, 3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f)); //UpperLeft

													   //Cara lateral Izquierda
	positions.push_back(glm::vec3(-3.0f, 0.0f, 0.0f)); //centrum 
	positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f)); //lowerRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, -3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f)); //lowerLeft
	positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f)); //LowerRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f)); //UpperLeft
	positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f)); //lowerLeft
	positions.push_back(glm::vec3(-3.0f, 3.0f, -3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f)); //UpperLeft

													   //Cara Arriba
	positions.push_back(glm::vec3(0.0f, 3.0f, 0.0f)); //centrum 
	positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f)); //lowerRight
	positions.push_back(glm::vec3(3.0f, 3.0f, 3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, -3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f)); //LowerRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f)); //UpperLeft
	positions.push_back(glm::vec3(-3.0f, 3.0f, -3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, 3.0f, 3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f)); //UpperLeft

													   //Cara Abajo
	positions.push_back(glm::vec3(0.0f, -3.0f, 0.0f)); //centrum 
	positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f)); //lowerRight
	positions.push_back(glm::vec3(3.0f, -3.0f, 3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f)); //LowerRight
	positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f)); //UpperLeft
	positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f)); //lowerLeft
	positions.push_back(glm::vec3(3.0f, -3.0f, 3.0f)); //UpperRight
	positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f)); //UpperLeft

	return positions;
}

void Initialize()
{
	//---------+-----------------------------------------------+-------------
	// creando toda la memoria una sola vez al inicio de la vida del programa.

	//Creacion del atributo de posiciones de los vertices 
	// lista de vec3
	//CLARAMENTE en el CPU y RAM
	std::vector<glm::vec3> positions = posiciones();
	std::vector<glm::vec3> colors = colores();

	//los indices
	vector<unsigned int> indices = { 0, 1, 2, 0, 3, 4, 0, 5, 6, 0, 7, 8, 9, 10, 11, 9, 12, 13, 9, 14, 15, 9, 16, 17, 18, 19, 20,18, 21, 22,18, 23, 24,18, 25, 26, 27, 28, 29,27, 30, 31,27,  32, 33, 27, 34, 35, 36, 37, 38,36,  39, 40,36,  41, 42,36,  43, 44, 45, 46, 47,45, 48, 49,45, 50, 51,45, 52, 53 };

	//queremis generar un manager
	meshF.CreateMesh((GLint)ULTRA);
	meshF.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	meshF.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	meshF.SetIndices(indices, GL_STATIC_DRAW);

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


#pragma region Transforms

	//Apilados
	_transform.SetRotation(0.0f, 180.0f, 0.0f);

	//_transform2.SetScale(0.5f, 0.5f, 0.5f);
	_transform2.SetPosition(0.0f, 6.0f, 0.0f);
	_transform2.SetRotation(0.0f, 0.0f, 0.0f);
	//---------------------------------

	//PISO
	_transform3.SetScale(30.0f, 0.5f, 30.0f);
	_transform3.SetPosition(8.0f, -10.0f, 0.0f);
	_transform3.SetRotation(0.0f, 0.0f, 0.0f);

	_transform4.SetPosition(-20.0f, 6.0f, 5.0f);

	_transform5.SetPosition(-20.0f, 16.0f, 5.0f);

	//_camera.SetOrtographic(10.0f,1.0f);
	
	_camera.SetPosition(0.0f, 0.0f, 40.0f);
	_camera.MoveUp(15.0f);

#pragma endregion 
}

void GameLoop() 
{
	//Limpiamos el buffer de color y de profundidad
	//siempre hcerlo alinicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//esta es la linea que hace rotar 
	//el true o false hace que rote con respecto al mundo o no 

	//_camera.MoveForward(0.1f);
	//_transform.Rotate(0.01f, 0.04f, 0.01f, true);
	//_transform2.Rotate(0.0f, 0.04f, 0.0f, true);
	_camera.Rotate(0.0f, 0.001f, 0.00f, false);

	_transform4.Rotate(0.0f, 0.1f, 0.0f, false);
	_transform5.Rotate(0.0f, -0.1f, 0.0f, false);

	//activamos con rl manafer
	//glUseProgram(shaderProgram);
	sProgram.Activate();
	//sProgram.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix());

	//ESTE TRANSFORM ME DICE QUE PUN
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	meshF.Draw(GL_TRIANGLES);

	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	meshF.Draw(GL_TRIANGLES);

	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform3.GetModelMatrix());
	meshF.Draw(GL_TRIANGLES);

	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform4.GetModelMatrix());
	meshF.Draw(GL_TRIANGLES);

	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform5.GetModelMatrix());
	meshF.Draw(GL_TRIANGLES);
	
	//sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	//meshF.Draw(GL_TRIANGLES);

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



