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
Fecha: 12 de Octubre del 2017
Autor: A01374526 Jose Karlo Hurtado Corona
*********************************************************/

class Mesh
{
public:
	Mesh();
	~Mesh();
	void CreateMesh(GLint vertexCount);
	void Draw(GLenum primitive);
	void SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex);
	void SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex);
	void SetIndices(vector<unsigned int> indices, GLenum usage);
	void SetNormalAttribute(vector<vec3> normals, GLenum usage, GLuint locationIndex);
	void SetTexCoordAttribute(vector<vec2> texCoords, GLenum usage, GLuint locationIndex);
private:
	GLuint _vertexArrayObject;
	GLuint _positionsVertexBufferObject;
	GLuint _colorsVertexBufferObject;
	GLuint _normalVBO;
	GLint  _vertexCount;
	void   SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components);
	GLuint _indicesBufferObject;
	GLint  _indicesCount;
	GLuint _texCoordsVertexBufferObject;
};