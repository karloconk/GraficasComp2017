#pragma once
#include <string> 

/*********************************************************
Materia: Gráficas Computacionales
Fecha: 15 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

class InputFile
{
public:
	bool Read(const std::string& filename);
	const std::string GetContents() const;
private:
	std::string _contents;
};