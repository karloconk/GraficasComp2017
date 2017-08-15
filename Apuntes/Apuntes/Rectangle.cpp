#include <iostream>
#include "Rectangle.h"

using namespace std;
/*********************************************************
Materia: Gráficas Computacionales
Fecha: 14 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

Rectangle::Rectangle()
{
	_width = 1.0f;
	_height = 1.0f;
}

Rectangle::Rectangle(float w, float h)
{
	_width = w;
	_height = h;
}

float Rectangle::GetWidth()
{
	return _width;
}

void Rectangle::SetWidth(float w)
{
	_width = w;
}

float Rectangle::GetHeight()
{
	return _height;
}

void Rectangle::SetHeight(float h)
{
	_height = h;
}

float Rectangle::GetArea()
{
	return _width * _height;
}

float Rectangle::GetPerimeter()
{
	return (_width + _height) * 2;
}
