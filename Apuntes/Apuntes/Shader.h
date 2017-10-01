#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
using namespace std;
using namespace glm;

/*********************************************************
Materia: Graficas Computacionales
Fecha: 02 de Octubre del 2017
Autor: A01374526 Jose Karlo Hurtado Corona
*********************************************************/

class Shader
{
public:
	Shader();
	~Shader();
	void CreateShader(string path, GLenum  type);
	GLuint GetHandle();
private:
	GLuint _shaderHandle;
};