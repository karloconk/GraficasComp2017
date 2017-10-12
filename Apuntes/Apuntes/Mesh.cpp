#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"
#include <iostream>

using namespace std;
using namespace glm;
/*********************************************************
Materia: Graficas Computacionales
Fecha: 12 de Octubre del 2017
Autor: A01374526 Jose Karlo Hurtado Corona
*********************************************************/

Mesh::Mesh()
{
	_vertexArrayObject = 0;
	_positionsVertexBufferObject = 0;
	_colorsVertexBufferObject = 0;
	_vertexCount = 0;
	_indicesCount = 0;
	_indicesBufferObject = 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vertexArrayObject);
	glDeleteBuffers(1, &_positionsVertexBufferObject);
	glDeleteBuffers(1, &_colorsVertexBufferObject);
	glBindVertexArray(0);
}

void Mesh::CreateMesh(GLint vertexCount)
{
	_vertexCount = vertexCount;
	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);
}

void Mesh::Draw(GLenum primitive)
{
	if (_indicesCount == 0)
	{
		glBindVertexArray(_vertexArrayObject);
		glDrawArrays(primitive, 0, _vertexCount);
		glBindVertexArray(0);
	}
	else 
	{
		glBindVertexArray(_vertexArrayObject);
		glDrawElements(primitive, _indicesCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}

void Mesh::SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex)
{
	if (positions.empty() || positions.size() != _vertexCount)
	{;}
	else
	{
		SetAttributeData(_positionsVertexBufferObject, sizeof(vec2)*positions.size(), positions.data(), usage, locationIndex, 2);
	}
}

void Mesh::SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex)
{
	if (positions.empty() || positions.size() != _vertexCount)
	{;}
	else
	{
		SetAttributeData(_positionsVertexBufferObject, sizeof(vec3)*positions.size(), positions.data(), usage, locationIndex, 3);
	}
}

void Mesh::SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex)
{
	if (colors.empty() || colors.size() != _vertexCount)
	{;}
	else
	{
		SetAttributeData(_colorsVertexBufferObject, sizeof(vec3)*colors.size(), colors.data(), usage, locationIndex, 3);
	}
}

void Mesh::SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex)
{
	if (colors.empty() || colors.size() != _vertexCount)
	{;}
	else
	{
		SetAttributeData(_colorsVertexBufferObject, sizeof(vec4)*colors.size(), colors.data(), usage, locationIndex, 4);
	}
}

void Mesh::SetIndices(vector<unsigned int> indices, GLenum usage)
{
	if (indices.empty())
	{;}
	else
	{
		if (_indicesBufferObject != 0)
		{
			glDeleteBuffers(1, &_indicesBufferObject);
		}
		_indicesCount = indices.size();
		glBindVertexArray(_vertexArrayObject);
		glGenBuffers(1, &_indicesBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _indicesCount, indices.data(), usage);
		glBindVertexArray(0);
	}
}

void Mesh::SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components)
{
	if (&buffer != 0)
	{
		glDeleteBuffers(1, &buffer);
	}
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glEnableVertexAttribArray(locationIndex);
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}