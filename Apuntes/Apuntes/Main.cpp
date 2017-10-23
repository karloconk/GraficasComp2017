/*********************************************************
Materia: Gráficas Computacionales
Fecha: 16 de Octubre del 2017
Autor: A01374526 José Karlo Hurtado Corona
Autor: A01374645 Javier Esponda Hernandez
*********************************************************/

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

#pragma region Global Scope vars

//manager al que le vamos a asociar todos los VBOs
GLuint vao;

//MANAGER DE los shaders (shaderProgram)
GLuint shaderProgram;
int g = 1;
int ULTRA = g * 5;

//animacion
float vertsPerFrame = 0.0f;
float delta = 0.0f;
float delta2 = 0.0f;
bool d2 = false;
float MAN = (delta2 / 360) / 2;


//declaro shader program y mesh
ShaderProgram sProgram;
Mesh geometria1;

//LO del transform
Transform _transform;
Transform _transform2;
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
		switch (i)
		{
		case 0:
			colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case 1:
			colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			break;
		case 2:
			colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 3:
			colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			break;
		case 4:
			colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
			break;
		}
	}
	return colors;
}

vector<vec3> posiciones()
{
	//Esto es una PIRAMIDE
	std::vector<glm::vec3> positions;
	//cara posterior
	positions.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); //centrum
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
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
	vector<unsigned int> indices = { 0, 1, 2,  0, 2, 4,  0, 4, 3, 0, 3, 1, 1,3,4,1,2,4 };
	//queremos generar un manager
	geometria1.CreateMesh((GLint)ULTRA);
	geometria1.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	geometria1.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	geometria1.SetIndices(indices, GL_STATIC_DRAW);

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
	_camera.SetPosition(0.0f, 0.0f, 25.0f);
	//_camera.Rotate(320.0f, 0.0f, 0.0f, false);
	//_camera.Yaw(-120.0f);

	_transform.SetScale(3, 3, 3);
	_transform2.SetScale(0.5f, 0.5f, 0.5f);
#pragma endregion 
}

void GameLoop()
{
	//Limpiamos el buffer de color y de profundidad
	//siempre hcerlo alinicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (delta == 360)
	{
		delta = 0;
	}
	//esta es la linea que hace rotar 
	//el true o false hace que rote con respecto al mundo o no 

	//_camera.MoveForward(0.1f);
	_transform.Rotate(0.005, -0.005f, 0.005f, false);
	float x, y;
	x = 5 * (glm::cos(glm::radians((float)(delta))));
	y = 5 * (glm::sin(glm::radians((float)(delta))));
	_transform.SetPosition(x, y, 0);

	_transform2.Rotate(-0.01f, 0.01f, -0.01f, false);
	_transform2.SetPosition(0.0f, 0.0f, 0.0f);
	_transform2.SetScale(0.5f + MAN, 0.5f + MAN, 0.5f + MAN);

	//activamos con rl manafer
	//glUseProgram(shaderProgram);
	sProgram.Activate();
	//sProgram.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix());

	//EGeometria 1
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	geometria1.Draw(GL_TRIANGLES);

	//EGeometria 2
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	geometria1.Draw(GL_TRIANGLES);


	sProgram.Deactivate();

	//Cuando terminamos de renderear, cambiampos buffers
	glutSwapBuffers();

	delta += 0.01f;
	if (delta2 >= 360)
	{
		d2 = true;
	}
	if (delta2 <= -180)
	{
		d2 = false;
	}

	if (d2 == true)
	{
		delta2 -= 0.1f;
	}
	else
	{
		delta2 += 0.1f;
	}
	MAN = (delta2 / 360) / 2;
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
	glutInitContextVersion(4, 4);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//freeglut nos permite configurar eventos que ocurren en la ventana
	//nos interesa cuando alguien cierra la ventana, en ese caso se deja de renderear la escena.

	//configuramos el framebuffer, true color RGBA profundidad y un segundo buffer para rendereo
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	//la ventana 
	glutInitWindowSize(400, 400);

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
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

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
