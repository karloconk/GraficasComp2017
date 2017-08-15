#include "InputFile.h"  
#include <iostream>

using namespace std;
/*********************************************************
Materia: Gráficas Computacionales
Fecha: 15 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

int main(int argc, char* argv[])
{
	std::string filename = "Prueba.txt";  
	InputFile myFile;   
	myFile.Read(filename);   
	std::string contents = myFile.GetContents();
	std::cout << "Contents: " << contents << std::endl;
	cin.get();
}