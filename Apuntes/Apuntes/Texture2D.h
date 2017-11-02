/*********************************************************
Materia: Gráficas Computacionales
Fecha: 30 de Octubre del 2017
Autor: A01374526 José Karlo Hurtado Corona
Autor: A01375051 Marina Fernanda Torres Gomez
*********************************************************/
#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <IL/il.h>

using namespace std;
using namespace glm;

class Texture2D
{
public:
	Texture2D();
	~Texture2D();
	void LoadTexture(string path);
	void Bind();
	void Unbind();
private:
	GLuint _textureID;
};