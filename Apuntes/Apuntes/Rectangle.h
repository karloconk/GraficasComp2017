#pragma once

/*********************************************************
Materia: Gráficas Computacionales
Fecha: 14 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

class Rectangle
{
public:
	Rectangle();
	Rectangle(float w,float h);

	float GetWidth();
	void SetWidth(float w);

	float GetHeight();
	void SetHeight(float h);

	float GetArea();
	float GetPerimeter();

private:
	float _width;
	float _height;
};