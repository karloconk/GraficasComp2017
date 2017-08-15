#pragma once
#include <string> 

/*********************************************************
Materia: Gráficas Computacionales
Fecha: 14 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

class Circle 
{
public:
	Circle();
	Circle(double r);
	Circle(double r, std::string c);

	double GetArea();
	double GetRadius();
	std::string GetColor();
	void SetRadius(double r);
	void SetColor(std::string c);
private:
	double _radius;
	std::string _color;
};