/*********************************************************
Materia: Gráficas Computacionales
Fecha: 30 de Octubre del 2017
Autor: A01374526 José Karlo Hurtado Corona
Autor: A01375051 Marina Fernanda Torres Gomez
*********************************************************/
#include "Texture2D.h"
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <IL/il.h>
#include <string>

Texture2D::Texture2D()
{
	_textureID = 0;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_textureID);
}

void Texture2D::LoadTexture(string path)
{
	//DEVil
	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage(path.std::string::c_str());

	//OpenGL-----
	glGenTextures(1, &_textureID);
	Bind();

	//texture filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// y wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
	Unbind();

}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

//conversion a string 
//https://stackoverflow.com/questions/13656501/no-suitable-conversion-from-stdstring-to-char-exists
//Filter y wrap 
//https://www.khronos.org/opengl/wiki/GLAPI/glTexParameter