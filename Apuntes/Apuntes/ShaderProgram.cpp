#include <memory>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "InputFile.h" 
#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>


using namespace std;
using namespace glm;
/*********************************************************
Materia: Graficas Computacionales
Fecha: 02 de Octubre del 2017
Autor: A01374526 Jose Karlo Hurtado Corona
*********************************************************/

ShaderProgram::ShaderProgram()
{
	_programHandle = 0;
}

ShaderProgram::~ShaderProgram()
{
	DeleteProgram();
}

void ShaderProgram::CreateProgram()
{
	_programHandle = glCreateProgram();
}

void ShaderProgram::AttachShader(std::string name, GLenum type)
{
	// Create and add the shaders to a list
	std::unique_ptr<Shader> shader(new Shader);
	shader->CreateShader(name, type);
	_attachedShaders.push_back(std::move(shader)); 
}

void ShaderProgram::LinkProgram()
{
	for (int i = 0; i<_attachedShaders.size(); i++)
	{
		glAttachShader(_programHandle, _attachedShaders[i]->GetHandle());
	}
	glLinkProgram(_programHandle);
	DeleteAndDetachShaders();
}

void ShaderProgram::Activate()
{
	glUseProgram(_programHandle);
}

void ShaderProgram::Deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::SetAttribute(GLuint locationIndex, string name)
{
	glBindAttribLocation(_programHandle, locationIndex, (const GLchar*)name.c_str());
}

void ShaderProgram::SetUniformf(string name, float value)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, (const GLchar*)name.c_str());
	glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetUniformf(string name, float x, float y)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, (const GLchar*)name.c_str());
	glUniform2f(uniformLocation, x, y);
}

void ShaderProgram::SetUniformf(string name, float x, float y, float z)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, (const GLchar*)name.c_str());
	glUniform3f(uniformLocation, x, y, z);
}

void ShaderProgram::SetUniformf(string name, float x, float y, float z, float w)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, (const GLchar*)name.c_str());
	glUniform4f(uniformLocation, x, y, z, w);
}

void ShaderProgram::SetUniformMatrix(string name, glm::mat4 matrix)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, (const GLchar*)name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::DeleteAndDetachShaders()
{
	for (int i = 0; i < _attachedShaders.size(); i++)
	{
		glDetachShader(_programHandle, _attachedShaders[i]->GetHandle());
		glDeleteShader(_attachedShaders[i]->GetHandle());
	}
	_attachedShaders.clear();
}

void ShaderProgram::DeleteProgram()
{
	DeleteAndDetachShaders();
	glDeleteProgram(_programHandle);
}