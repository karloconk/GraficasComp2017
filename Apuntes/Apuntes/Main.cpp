/*********************************************************
Materia: Gráficas Computacionales
Fecha: 24 de noviembre del 2017
Autor: A01374526 José Karlo Hurtado Corona
Autor: A01375051 Marina Fernanda Torres Gomez
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
#include "Texture2D.h"
#include <IL/il.h>
#include "Dephtbuffer.h"


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
float deltaM = -15.0f;
float deltaA = -30.0f;
float delta2 = 0.0f;
bool d2 = false;
float MAN = (delta2 / 360) / 2;
int Turbo = 130;


//Posicion de la camara
vec3 camaraPos = vec3(0.0f, 20.0f, 50.0f);
int CPitch = -20;
vec3 lPos = glm::vec3(0.0f, 20.0f, 0.0f);
vec3 camera2Pos = lPos;


//declaro shader program y mesh
ShaderProgram sProgram;
ShaderProgram sProgram2;
ShaderProgram sProgram2Texturas;
Mesh geometria1;
Mesh geometriaDedos;

//LO del transform
Transform _transform;
Transform _transform2;
Camera _camera;
Camera _camera2;
//Los dedos
Transform PPhalanx;
Transform PMeta;
Transform IPhalanx;
Transform IMeta;
Transform MPhalanx;
Transform MMeta;
Transform APhalanx;
Transform AMeta;

//lo de la textura
Texture2D myTexture;
Texture2D base;
Texture2D cerdo;

//el depth buffer
Depthbuffer dBuffer;

//se obtuvo la informacion de #pragma region de: https://msdn.microsoft.com/en-us/library/b6xkz944.aspx

#pragma endregion 

#pragma region Colors Vertex Normals TexCoords

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
	//Esto es un palma
	std::vector<glm::vec3> positions;
	//adelante
	positions.push_back(vec3(3.0f*2.0f, -3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(3.0f*2.0f, 3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, -3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, 3.0f*3.5f, 3.0f*0.5f));
	//atras
	positions.push_back(vec3(3.0f*2.0f, -3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(3.0f*2.0f, 3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, -3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, 3.0f*3.5f, -3.0f*0.5f));
	//Derecha
	positions.push_back(vec3(3.0f*2.0f, -3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(3.0f*2.0f, 3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(3.0f*2.0f, -3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(3.0f*2.0f, 3.0f*3.5f, 3.0f*0.5f));
	//izq
	positions.push_back(vec3(-3.0f*2.0f, -3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, 3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, -3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, 3.0f*3.5f, 3.0f*0.5f));
	//arriba
	positions.push_back(vec3(3.0f*2.0f, 3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(3.0f*2.0f, 3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, 3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, 3.0f*3.5f, -3.0f*0.5f));
	//abajo
	positions.push_back(vec3(3.0f*2.0f, -3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(3.0f*2.0f, -3.0f*3.5f, -3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, -3.0f*3.5f, 3.0f*0.5f));
	positions.push_back(vec3(-3.0f*2.0f, -3.0f*3.5f, -3.0f*0.5f));

	return positions;
}

vector<vec3> posicionesDedos()
{
	//Esto es una falange

	std::vector<glm::vec3> positions;
	//adelante
	positions.push_back(vec3(3.0f*0.5f, -3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(3.0f*0.5f, 3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, -3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, 3.0f*0.8f, 3.0f*0.3f));
	//atras
	positions.push_back(vec3(3.0f*0.5f, -3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(3.0f*0.5f, 3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, -3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, 3.0f*0.8f, -3.0f*0.3f));
	//Derecha
	positions.push_back(vec3(3.0f*0.5f, -3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(3.0f*0.5f, 3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(3.0f*0.5f, -3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(3.0f*0.5f, 3.0f*0.8f, 3.0f*0.3f));
	//izq
	positions.push_back(vec3(-3.0f*0.5f, -3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, 3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, -3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, 3.0f*0.8f, 3.0f*0.3f));
	//arriba
	positions.push_back(vec3(3.0f*0.5f, 3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(3.0f*0.5f, 3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, 3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, 3.0f*0.8f, -3.0f*0.3f));
	//abajo
	positions.push_back(vec3(3.0f*0.5f, -3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(3.0f*0.5f, -3.0f*0.8f, -3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, -3.0f*0.8f, 3.0f*0.3f));
	positions.push_back(vec3(-3.0f*0.5f, -3.0f*0.8f, -3.0f*0.3f));

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

vector<vec2> TexCoords()
{
	std::vector<glm::vec2> texcoords;

	for (int i = 0;i<6;i++) 
	{
		texcoords.push_back(vec2(1.0f, 0.0f));
		texcoords.push_back(vec2(1.0f, 1.0f));
		texcoords.push_back(vec2(0.0f, 0.0f));
		texcoords.push_back(vec2(0.0f, 1.0f));
	}

	return texcoords;
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
	vec3 lSource = lPos;

	//textura
	myTexture.LoadTexture("caja.jpg");
	base.LoadTexture("base.jpg");
	cerdo.LoadTexture("crash.png");

	//queremos generar un manager
	geometria1.CreateMesh((GLint)ULTRA);
	geometria1.SetPositionAttribute(posiciones(), GL_STATIC_DRAW, 0);
	geometria1.SetColorAttribute(colores(), GL_STATIC_DRAW, 1);
	geometria1.SetNormalAttribute(normales(), GL_STATIC_DRAW, 2);
	geometria1.SetTexCoordAttribute(TexCoords(), GL_STATIC_DRAW, 3);
	geometria1.SetIndices(indices, GL_STATIC_DRAW);

	//Desactivamos el MNGR 
	glBindVertexArray(0);

	//queremos generar otro manager
	geometriaDedos.CreateMesh((GLint)ULTRA);
	geometriaDedos.SetPositionAttribute(posicionesDedos(), GL_STATIC_DRAW, 0);
	geometriaDedos.SetColorAttribute(colores(), GL_STATIC_DRAW, 1);
	geometriaDedos.SetNormalAttribute(normales(), GL_STATIC_DRAW, 2);
	geometriaDedos.SetTexCoordAttribute(TexCoords(), GL_STATIC_DRAW, 3);
	geometriaDedos.SetIndices(indices, GL_STATIC_DRAW);

	//Desactivamos el MNGR 
	glBindVertexArray(0);

//-------------------------------------------------------------1
	sProgram2.CreateProgram();

	//Vertex shader 
	//-----------------------------------------
	sProgram2.AttachShader("Depth.vert", GL_VERTEX_SHADER);
	sProgram2.AttachShader("Depth.frag", GL_FRAGMENT_SHADER);
	sProgram2.SetAttribute(0, "VertexPosition");
	sProgram2.LinkProgram();

//-------------------------------------------------------------1

//-------------------------------------------------------------2
//Vertex shader 
	//-----------------------------------------
	sProgram.CreateProgram();
	sProgram.AttachShader("Shadow.vert", GL_VERTEX_SHADER);
	sProgram.AttachShader("Shadow.frag", GL_FRAGMENT_SHADER);
	sProgram.SetAttribute(0, "VertexPosition");
	sProgram.SetAttribute(1, "VertexColor");
	sProgram.SetAttribute(2, "VertexNormal");
	sProgram.SetAttribute(3, "VertexTexCoord");

	//se cheka compatibilidad man
	sProgram.LinkProgram();

	sProgram.Activate();
	sProgram.SetUniformf("Resolution", 400.0f, 400.0f);
	sProgram.SetUniformf("LightColor", LightColour.x, LightColour.y, LightColour.z);
	sProgram.SetUniformf("LightPosition", lSource.x, lSource.y, lSource.z);
	sProgram.SetUniformf("CameraPosition", camaraPos.x, camaraPos.y, camaraPos.z);
	
	sProgram.SetUniformi("DiffuseTexture", 0);
	sProgram.SetUniformi("DiffuseTexture2", 1);
	sProgram.SetUniformi("ShadowMap", 2);

	sProgram.Deactivate();
//-------------------------------------------------------------2

//-------------------------------------------------------------3
//Vertex shader 
//-----------------------------------------
	sProgram2Texturas.CreateProgram();
	sProgram2Texturas.AttachShader("Shadow2Texturas.vert", GL_VERTEX_SHADER);
	sProgram2Texturas.AttachShader("Shadow2Texturas.frag", GL_FRAGMENT_SHADER);
	sProgram2Texturas.SetAttribute(0, "VertexPosition");
	sProgram2Texturas.SetAttribute(1, "VertexColor");
	sProgram2Texturas.SetAttribute(2, "VertexNormal");
	sProgram2Texturas.SetAttribute(3, "VertexTexCoord");

	//se cheka compatibilidad man
	sProgram2Texturas.LinkProgram();

	sProgram2Texturas.Activate();
	sProgram2Texturas.SetUniformf("Resolution", 400.0f, 400.0f);
	sProgram2Texturas.SetUniformf("LightColor", LightColour.x, LightColour.y, LightColour.z);
	sProgram2Texturas.SetUniformf("LightPosition", lSource.x, lSource.y, lSource.z);
	sProgram2Texturas.SetUniformf("CameraPosition", camaraPos.x, camaraPos.y, camaraPos.z);

	sProgram2Texturas.SetUniformi("DiffuseTexture", 0);
	sProgram2Texturas.SetUniformi("DiffuseTexture2", 1);
	sProgram2Texturas.SetUniformi("ShadowMap", 2);

	sProgram2Texturas.Deactivate();
	//-------------------------------------------------------------3
	

#pragma region Transforms

	_camera.SetPosition(camaraPos.x, camaraPos.y, camaraPos.z);
	_camera2.SetPosition(camera2Pos.x, camera2Pos.y, camera2Pos.z);
	_camera2.Pitch(-90);
	_camera.Pitch(CPitch);
	_camera2.SetOrtographic(100.0f,1.0f);

	_transform.SetRotation(-45.0f,0.0f, 0.0f);
	_transform2.SetScale(30.0f, 0.5f, 30.0f);
	_transform2.SetPosition(0.0f, -15.0f, 0.0f);
	_transform2.SetRotation(0.0f, 0.0f, 0.0f);

	PPhalanx.SetPosition(10.0f, -6.0f, 0.0f);
	PMeta.SetPosition(0.0f, 6.0f, 0.0f);
	IPhalanx.SetPosition(0.0f,	14.0f, 0.0f);
	IMeta.SetPosition(0.0f, 6.0f, 0.0f);
	MPhalanx.SetPosition(-4.5f, 14.0f, 0.0f);
	MMeta.SetPosition(0.0f, 6.0f, 0.0f);
	APhalanx.SetPosition(4.5f, 14.0f, 0.0f);
	AMeta.SetPosition(0.0f, 6.0f, 0.0f);

	PPhalanx.SetRotation( 0.0f, 0.0f, -70.0f);

#pragma endregion 

	dBuffer.Create(2048);
}

#pragma region MoverCosas

//Pulgar-------------------------------------------------
void moverPulgar2()
{
	 if (delta < Turbo * 2)
	{
		PMeta.Rotate(0.04f, 0.0f, 0.0f, false);
		PMeta.MoveForward(0.0025f, false);
	}
	else if (delta > Turbo * 3 && delta < Turbo * 4)
	{
		PMeta.Rotate(-0.08f, 0.0f, 0.0f, false);
		PMeta.MoveForward(-0.005f, false);
	}
	else
	{
		PMeta.Rotate(0.0f, 0.0f, 0.0f, false);
		PMeta.MoveForward(0.00f, false);
	}
}

void moverPulgar() 
{
	if (delta < Turbo)
	{
		PPhalanx.Rotate(0.05f, 0.0f, 0.0f, false);
		PPhalanx.MoveForward(0.005f, false);
	}
	else if (delta < Turbo *3 && delta > Turbo)
	{
		PPhalanx.Rotate(0.0f, 0.0f, 0.0f, false);
		PPhalanx.MoveForward(0.00f, false);
	}
	else if (delta > Turbo * 3 && delta < Turbo*4)
	{
		PPhalanx.Rotate(-0.05f, 0.0f, 0.0f, false);
		PPhalanx.MoveForward(-0.005f, false);
	}
	else 
	{
		PPhalanx.Rotate(0.0f, 0.0f, 0.0f, false);
		PPhalanx.MoveForward(0.00f, false);
	}
	moverPulgar2();
}

//Medio-------------------------------------------------
void moverIndice2()
{
	if (deltaM < Turbo * 2 && deltaM > 0.0f)
	{
		IMeta.Rotate(0.04f, 0.0f, 0.0f, false);
		IMeta.MoveForward(0.0025f, false);
	}
	else if (deltaM > Turbo * 3  && deltaM < (Turbo * 4))
	{
		IMeta.Rotate(-0.08f, 0.0f, 0.0f, false);
		IMeta.MoveForward(-0.005f, false);
	}
	else
	{
		IMeta.Rotate(0.0f, 0.0f, 0.0f, false);
		IMeta.MoveForward(0.00f, false);
	}
}

void moverIndice()
{
	if (deltaM < Turbo && deltaM > 0.0f)
	{
		IPhalanx.Rotate(0.05f, 0.0f, 0.0f, false);
		IPhalanx.MoveForward(0.005f, false);
	}
	else if (deltaM < Turbo * 3 && deltaM > Turbo)
	{
		IPhalanx.Rotate(0.0f, 0.0f, 0.0f, false);
		IPhalanx.MoveForward(0.00f, false);
	}
	else if (deltaM > Turbo * 3 && deltaM < Turbo * 4)
	{
		IPhalanx.Rotate(-0.05f, 0.0f, 0.0f, false);
		IPhalanx.MoveForward(-0.005f, false);
	}
	else
	{
		IPhalanx.Rotate(0.0f, 0.0f, 0.0f, false);
		IPhalanx.MoveForward(0.00f, false);
	}
	moverIndice2();
}

//Anular-------------------------------------------------
void moverMedio2()
{
	if (deltaA < Turbo *2 && deltaA > 0.0f)
	{
		MMeta.Rotate(0.04f, 0.0f, 0.0f, false);
		MMeta.MoveForward(0.0025f, false);
	}
	else if (deltaA > Turbo * 3 && deltaA < (Turbo * 4) )
	{
		MMeta.Rotate(-0.08f, 0.0f, 0.0f, false);
		MMeta.MoveForward(-0.005f, false);
	}
	else
	{
		MMeta.Rotate(0.0f, 0.0f, 0.0f, false);
		MMeta.MoveForward(0.00f, false);
	}
}

void moverMedio()
{
	if (deltaA < Turbo && deltaA > 0.0f)
	{
		MPhalanx.Rotate(0.05f, 0.0f, 0.0f, false);
		MPhalanx.MoveForward(0.005f, false);
	}
	else if (deltaA < Turbo * 3 && deltaA > Turbo)
	{
		MPhalanx.Rotate(0.0f, 0.0f, 0.0f, false);
		MPhalanx.MoveForward(0.00f, false);
	}
	else if (deltaA > Turbo * 3 && deltaA < Turbo * 4)
	{
		MPhalanx.Rotate(-0.05f, 0.0f, 0.0f, false);
		MPhalanx.MoveForward(-0.005f, false);
	}
	else
	{
		MPhalanx.Rotate(0.0f, 0.0f, 0.0f, false);
		MPhalanx.MoveForward(0.00f, false);
	}
	moverMedio2();
}

//Indice-------------------------------------------------
void moverAnular2()
{
	if (delta < Turbo * 2)
	{
		AMeta.Rotate(0.04f, 0.0f, 0.0f, false);
		AMeta.MoveForward(0.0025f, false);
	}
	else if (delta > Turbo * 3 && delta < Turbo * 4)
	{
		AMeta.Rotate(-0.08f, 0.0f, 0.0f, false);
		AMeta.MoveForward(-0.005f, false);
	}
	else
	{
		AMeta.Rotate(0.0f, 0.0f, 0.0f, false);
		AMeta.MoveForward(0.00f, false);
	}
}

void moverAnular()
{
	if (delta < Turbo)
	{
		APhalanx.Rotate(0.05f, 0.0f, 0.0f, false);
		APhalanx.MoveForward(0.005f, false);
	}
	else if (delta < Turbo * 3 && delta > Turbo)
	{
		APhalanx.Rotate(0.0f, 0.0f, 0.0f, false);
		APhalanx.MoveForward(0.00f, false);
	}
	else if (delta > Turbo * 3 && delta < Turbo * 4)
	{
		APhalanx.Rotate(-0.05f, 0.0f, 0.0f, false);
		APhalanx.MoveForward(-0.005f, false);
	}
	else
	{
		APhalanx.Rotate(0.0f, 0.0f, 0.0f, false);
		APhalanx.MoveForward(0.00f, false);
	}
	moverAnular2();
}

#pragma endregion 

void GameLoop()
{
	if (delta >= Turbo*5)
	{
		delta = 0;
		deltaM = -15;
		deltaA = -30;
	}

	//TRANSFORMS 
	_transform.Rotate( 0.0, -0.02f, 0.0f, true);
	//DEDOS------------------------------------------------
	moverPulgar();
	moverIndice();
	moverMedio();
	moverAnular();
	//------------------------------------------------

//1er Render------------------------------------------
	dBuffer.Bind();
	//dBuffer.BindDepthMap();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Palma 
	sProgram2.Activate();
	mat4 matModelo = _transform.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo);
	geometria1.Draw(GL_TRIANGLES);
	//base
	mat4 matModelo2 = _transform2.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo2);
	geometria1.Draw(GL_TRIANGLES);

#pragma region dedos

	//Pulgar posterior 
	matModelo2 = PPhalanx.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo * matModelo2);
	geometriaDedos.Draw(GL_TRIANGLES);
	//pulgar anterior
	mat4 matModelo22 = PMeta.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection()  * matModelo * matModelo2 * matModelo22);
	geometriaDedos.Draw(GL_TRIANGLES);

	//indice posterior
	mat4 mat4Modelo2 = IPhalanx.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo * mat4Modelo2);
	geometriaDedos.Draw(GL_TRIANGLES);
	//indice anterior
	matModelo2 = IMeta.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo * mat4Modelo2 * matModelo2);
	geometriaDedos.Draw(GL_TRIANGLES);

	//medio posteriror
	 mat4Modelo2 = MPhalanx.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo * mat4Modelo2);
	geometriaDedos.Draw(GL_TRIANGLES);
	//medio anterior
	matModelo2 = MMeta.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo * mat4Modelo2 * matModelo2);
	geometriaDedos.Draw(GL_TRIANGLES);

	//anular posterior
	 mat4Modelo2 = APhalanx.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo * mat4Modelo2);
	geometriaDedos.Draw(GL_TRIANGLES);
	//anular anterior
	matModelo2 = AMeta.GetModelMatrix();
	sProgram2.SetUniformMatrix("mvpMatrix", _camera2.GetViewProjection() * matModelo * mat4Modelo2 * matModelo2);
	geometriaDedos.Draw(GL_TRIANGLES);

#pragma endregion 

	sProgram2.Deactivate();
	//dBuffer.UnbindDepthMap();
	dBuffer.Unbind();
	glViewport(0, 0, 400, 400);

//2do Render------------------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	sProgram2Texturas.Activate();
	
	//EGeometria 1
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE1);
	cerdo.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	mat4 matModelo3 = _transform.GetModelMatrix();
	mat3 normalMatrix = glm::transpose(glm::inverse(mat3(_transform.GetModelMatrix())));
	sProgram2Texturas.SetUniformMatrix("modelMatrix", matModelo3);
	sProgram2Texturas.SetUniformMatrix3("normalMatrix", normalMatrix);
	sProgram2Texturas.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	sProgram2Texturas.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometria1.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE1);
	cerdo.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram2Texturas.Deactivate();

	sProgram.Activate();
	////EGeometria 2
	glActiveTexture(GL_TEXTURE0);
	base.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	mat4 matModelo21 = _transform2.GetModelMatrix();
	mat3 normalMatrix2 = glm::transpose(glm::inverse(mat3(_transform2.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo21);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());

	geometria1.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	base.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

#pragma region DEDOS2

	//Pulgar posterior 
	sProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	mat4 matModeloPul = matModelo3 * PPhalanx.GetModelMatrix();
	 normalMatrix2 = glm::transpose(glm::inverse(mat3(matModelo3 * PPhalanx.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModeloPul);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * matModelo3 * PPhalanx.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometriaDedos.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

	//pulgar anterior
	sProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	 matModelo21 = matModeloPul * PMeta.GetModelMatrix();
	 normalMatrix2 = glm::transpose(glm::inverse(mat3(matModeloPul * PMeta.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo21);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * matModeloPul * PMeta.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometriaDedos.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

	//indice posterior
	sProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	mat4 matModelo210 = matModelo3 * IPhalanx.GetModelMatrix();
	 normalMatrix2 = glm::transpose(glm::inverse(mat3(matModelo3 * IPhalanx.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo210);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * matModelo3 * IPhalanx.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometriaDedos.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

	//indice anterior
	sProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	 matModelo21 = matModelo210 * IMeta.GetModelMatrix();
	 normalMatrix2 = glm::transpose(glm::inverse(mat3(matModelo210 * IMeta.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo21);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * matModelo210 *  IMeta.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometriaDedos.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

	//medio posteriror
	sProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	mat4  matModo21 = matModelo3 * MPhalanx.GetModelMatrix();
	 normalMatrix2 = glm::transpose(glm::inverse(mat3(matModelo3 * MPhalanx.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModo21);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() *matModelo3 *  MPhalanx.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometriaDedos.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

	//medio anterior
	sProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	 matModelo21 = matModo21 * MMeta.GetModelMatrix();
	 normalMatrix2 = glm::transpose(glm::inverse(mat3(matModo21 * MMeta.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo21);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() *matModo21 *  MMeta.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometriaDedos.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

	//anular posteriror
	sProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	 mat4 matModelo214 = matModelo3 * APhalanx.GetModelMatrix();
	 normalMatrix2 = glm::transpose(glm::inverse(mat3(matModelo3 * APhalanx.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo214);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * matModelo3 * APhalanx.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometriaDedos.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

	//anular anterior
	sProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	myTexture.Bind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.BindDepthMap();
	 matModelo21 = matModelo214 * AMeta.GetModelMatrix();
	 normalMatrix2 = glm::transpose(glm::inverse(mat3(matModelo214 * AMeta.GetModelMatrix())));
	sProgram.SetUniformMatrix("modelMatrix", matModelo21);
	sProgram.SetUniformMatrix3("normalMatrix", normalMatrix2);
	sProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * matModelo214 * AMeta.GetModelMatrix());
	sProgram.SetUniformMatrix("LightVPMatrix", _camera2.GetViewProjection());
	geometriaDedos.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	myTexture.Unbind();
	glActiveTexture(GL_TEXTURE2);
	dBuffer.UnbindDepthMap();
	sProgram.Deactivate();

#pragma endregion
	
	//Cuando terminamos de renderear, cambiampos buffers
	glutSwapBuffers();
	delta += 0.1f;
	deltaM += 0.1f;
	deltaA += 0.1f;
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

	//-----------------------------------------------------------------
	// Inicializar DevIL. Esto se debe hacer sólo una vez.
	ilInit();
	// Cambiar el punto de origen de las texturas. Por default, DevIL
	// pone un punto de origen en la esquina superior izquierda.
	// Esto es compatible con el sistema operativo, pero no con el
	// funcionamiento de OpenGL. 
	ilEnable(IL_ORIGIN_SET);
	// Configurar el punto de origen de las texturas en la esquina 
	// inferior izquierda
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	//-----------------------------------------------------------------

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//config inicial del programa.
	Initialize();

	//Inicia la aplicación, el main se pausa en esta linea hasta que se cierre la ventana
	glutMainLoop();

	return 0;
}