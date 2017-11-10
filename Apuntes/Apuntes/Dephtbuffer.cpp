#include "Dephtbuffer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector> 
#include <glm/glm.hpp>
#include <IL/il.h>

Depthbuffer::Depthbuffer()
{
	_framebuffer = 0;
    _depthmap = 0;
	_resolution = 0;
}

Depthbuffer::~Depthbuffer()
{
	glDeleteFramebuffers(1, &_framebuffer);
	glDeleteTextures(1, &_depthmap);
}

void Depthbuffer::Create(int resolution)
{
	_resolution = resolution;
	//buffer---
	glGenFramebuffers(1, &_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	//texture-----
	glGenTextures(1, &_depthmap);
	BindDepthMap();

	//texture filter	// y wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _resolution, _resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthmap, 0);


	//UnbindDepthMap();
	Unbind();
}

void Depthbuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glViewport(0,0,_resolution,_resolution);
}

void Depthbuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Depthbuffer::BindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, _depthmap);
}

void Depthbuffer::UnbindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
