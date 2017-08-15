#include <iostream>
#include "Circle.h"

using namespace std;
/*********************************************************
Materia: Gráficas Computacionales
Fecha: 14 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

// en la clase cirlce  implemento su constructor
Circle::Circle() 
{
	_radius = 1.0;
	_color = "red";
}

Circle::Circle(double r)
{
	_radius = r;
	_color = "red";
}

Circle::Circle(double r, string c)
{
	_radius = r;
	_color = c;
}

double Circle::GetRadius() 
{
	return _radius;
}

std::string Circle::GetColor()
{
	return _color;
}

void Circle::SetRadius(double r)
{
	_radius = r;
}

void Circle::SetColor(std::string c)
{
	_color = c;
}

double Circle::GetArea()
{
	return 3.14159 * _radius * _radius;
}
