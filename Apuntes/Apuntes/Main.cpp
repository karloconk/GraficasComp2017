/*********************************************************
Materia: Gráficas Computacionales
Fecha: 16 de Octubre del 2017
Autor: A01374526 José Karlo Hurtado Corona
Autor: 
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
int g = 4;
int ULTRA = g *6;

//animacion
float vertsPerFrame = 0.0f;
float delta = 0.0f;
float delta2 = 0.0f;
bool d2 = false;
float MAN = (delta2 / 360) / 2;

//Posicion de la camara
vec3 camaraPos = vec3(0.0f, 0.0f, 50.0f);

//declaro shader program y mesh
ShaderProgram sProgram;
Mesh geometria1;

//LO del transform
Transform _transform;
Transform _transform2;
Camera _camera;

//se obtuvo la informacion de #pragma region de: https://msdn.microsoft.com/en-us/library/b6xkz944.aspx

#pragma endregion 

#pragma region Colors Vertex Normals

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
	//adelante
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	//atras
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	//Derecha
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	//izq
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	//arriba
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	//abajo
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));

	return positions;
}

vector<vec3> normales()
{
	std::vector<glm::vec3> normals;
	//Delantera
	for (int i = 0; i < 4; i++) 
	{
		normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	}
	//atras
	for (int i = 0; i < 4; i++)
	{
		normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	}
	//derecha
	for (int i = 0; i < 4; i++)
	{
		normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	//izq
	for (int i = 0; i < 4; i++)
	{
		normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	//arriba
	for (int i = 0; i < 4; i++)
	{
		normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	//abajo
	for (int i = 0; i < 4; i++)
	{
		normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	return normals;
}

#pragma endregion 

void Initialize()
{
	//---------+-----------------------------------------------+-------------
	// creando toda la memoria una sola vez al inicio de la vida del programa.
	//los indices
	vector<unsigned int> indices = {0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7, 8, 9, 10, 10, 9, 11, 12, 13, 14, 14, 13, 15, 16, 17, 18, 18, 17, 19, 20,21,22,22,21,23};

	//Cosas de Luz -------------------------------+------------------+-------
	vec3 LightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	vec3 lSource = glm::vec3(18.0f, 0.0f, 20.0f);

	//queremos generar un manager
	geometria1.CreateMesh((GLint)ULTRA);
	geometria1.SetPositionAttribute(posiciones(), GL_STATIC_DRAW, 0);
	geometria1.SetColorAttribute(colores(), GL_STATIC_DRAW, 1);
	geometria1.SetNormalAttribute(normales(), GL_STATIC_DRAW, 2);
	geometria1.SetIndices(indices, GL_STATIC_DRAW);

	//Desactivamos el MNGR 
	glBindVertexArray(0);

	sProgram.CreateProgram();
	

	//Vertex shader 
	//-----------------------------------------
	sProgram.AttachShader("Default.vert", GL_VERTEX_SHADER);
	sProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	sProgram.SetAttribute(0, "VertexPosition");
	sProgram.SetAttribute(1, "VertexColor");
	sProgram.SetAttribute(2,  "VertexNormal");

	//se cheka compatibilidad man
	sProgram.LinkProgram();

	sProgram.Activate();
	sProgram.SetUniformf("Resolution", 400.0f, 400.0f);
	sProgram.SetUniformf("LightColor", LightColour.x, LightColour.y, LightColour.z);
	sProgram.SetUniformf("LightPosition", lSource.x, lSource.y, lSource.z);
	sProgram.SetUniformf("CameraPosition", camaraPos.x, camaraPos.y, camaraPos.z);

	sProgram.Deactivate();


#pragma region Transforms

	_camera.SetPosition(camaraPos.x, camaraPos.y, camaraPos.z);
	_transform.SetScale(2, 2, 2);
	_transform.SetRotation(0.0f, 25.0f, 0.0f);
	_transform2.SetScale(30.0f, 0.5f, 30.0f);
	_transform2.SetPosition(0.0f, -15.0f, 0.0f);
	_transform2.SetRotation(0.0f, 0.0f, 0.0f);

#pragma endregion 

}

void GameLoop()
{
	//Limpiamos el buffer de color y de profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (delta == 360)
	{
		delta = 0;
	}
	_transform.Rotate(0.05, -0.05f, 0.05f, false);

	sProgram.Activate();

	//EGeometria 1
	mat4 matModelo = _transform.GetModelMatrix();
	mat3 normalMatrix = glm::transpose(glm::inverse(mat3(_transform.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	geometria1.Draw(GL_TRIANGLES);

	////EGeometria 2
	mat4 matModelo2 = _transform2.GetModelMatrix();
	mat3 normalMatrix2 = glm::transpose(glm::inverse(mat3(_transform2.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo2);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
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
	//Cuando opengl entra ne modo de reposo le decimos que vuelva a llamar el gameloop 
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

	//asociamos una funicon para el cambio de resolucion de la ventana, se va amandar a llamar cuando alguien cambie el tamaño
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

	//config inicial del programa.
	Initialize();

	//Inicia la aplicación, el main se pausa en esta linea hasta que se cierre la ventana
	glutMainLoop();

	return 0;
}
