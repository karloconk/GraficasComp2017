#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "InputFile.h"
#include <iostream>
#include "Mesh.h"
#include "ShaderProgram.h"

using namespace std;
using namespace glm;
/*********************************************************
Materia: Graficas Computacionales
Fecha: 02 de Octubre del 2017
Autor: A01374526 Jose Karlo Hurtado Corona
*********************************************************/

Shader::Shader()
{
	_shaderHandle = 0;
}

Shader::~Shader()
{
	glDeleteShader(_shaderHandle);
}

void Shader::CreateShader(string path, GLenum  type)
{
	if (_shaderHandle != 0)
	{
		glDeleteShader(_shaderHandle);
	}
	_shaderHandle = glCreateShader(type);
	InputFile ifile;
	ifile.Read(path);
	string shaderSource = ifile.GetContents();
	//std::cout << shaderSource << std::endl;
	const GLchar *thisSource = (const GLchar*)shaderSource.c_str();
	glShaderSource(_shaderHandle, 1, &thisSource, nullptr);
	glCompileShader(_shaderHandle); 
}

GLuint Shader::GetHandle()
{
	return _shaderHandle;
}
