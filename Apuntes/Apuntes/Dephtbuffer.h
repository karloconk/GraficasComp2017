#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
using namespace std;
using namespace glm;

/*********************************************************
Materia: Gr�ficas Computacionales
Fecha: 06 de Noviembre del 2017
Autor: A01374526 Jos� Karlo Hurtado Corona
Autor: A01375051 Marina Fernanda Torres Gomez
*********************************************************/

class Depthbuffer
{
public:
	Depthbuffer();
	~Depthbuffer();
	void Create(int resolution);
	void Bind();
	void Unbind();
	void BindDepthMap();
	void UnbindDepthMap();
private:
	GLuint _framebuffer = 0;
	GLuint _depthmap = 0;
	GLsizei _resolution = 0;
};