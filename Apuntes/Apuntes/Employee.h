#pragma once
#include <string> 

/*********************************************************
Materia: Gráficas Computacionales
Fecha: 14 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

class Employee
{
public:
	Employee(int id, std::string firstName, std::string lastName, int salary);

	int GetID();
	std::string  GetFirstName();
	std::string  GetLastName();
	std::string  GetName();
	int GetSalary();
	void SetSalary(int salary);
	int GetAnnualSalary();

	int RaiseSalary(int percent);
	std::string Print();
private:
	int _id;
	std::string _firstName;
	std::string _lastName;
	int _salary;
};