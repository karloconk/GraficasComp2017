#include "InputFile.h"
#include <fstream>
#include <iostream>
#include <sstream> 
using namespace std;
/*********************************************************
Materia: Gráficas Computacionales
Fecha: 15 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/


bool InputFile::Read(std::string filename)
{
	//filename es nombre y ruta
	fstream input_Stream;
	input_Stream.open(filename);
	if (!input_Stream) 
	{
		_contents.clear();
		return false;
	}
	string input;
	std::stringstream ss;
	while (std::getline(input_Stream, input))
	{
		ss.str(input+ '\n');
		_contents += ss.str();
	}
	return true;
}

std::string InputFile::GetContents()
{
	if (_contents.empty()) 
	{
		std::string();
	}
	return _contents;
}


/*
paginas consultadas para la obtencion y desarrollo de este codigo
https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
https://stackoverflow.com/questions/6255339/checking-if-a-file-opened-successfully-with-ifstream
http://www.cplusplus.com/reference/string/string/empty/
https://www.daniweb.com/programming/software-development/threads/87777/how-to-clear-a-string
https://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
https://stackoverflow.com/questions/35974402/reading-getline-from-cin-into-a-stringstream-c
*/
