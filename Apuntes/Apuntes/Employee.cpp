#include <iostream>
#include "Employee.h"

using namespace std;
/*********************************************************
Materia: Gráficas Computacionales
Fecha: 14 de Agosto del 2017
Autor: A01374526 José Karlo Hurtado Corona
*********************************************************/

Employee::Employee(int id, std::string firstName, std::string lastName, int salary)
{
	_id = id;
	_firstName = firstName;
	_lastName = lastName;
	_salary = salary;
}

int Employee::GetID()
{
	return _id;
}

std::string Employee::GetFirstName()
{
	return _firstName;
}

std::string Employee::GetLastName()
{
	return _lastName;
}

std::string Employee::GetName()
{
	return _firstName + ' ' + _lastName;
}

int Employee::GetSalary()
{
	return _salary;
}

void Employee::SetSalary(int salary)
{
	_salary = salary;
}

int Employee::GetAnnualSalary()
{
	return _salary*12;
}

int Employee::RaiseSalary(int percent)
{
	_salary = _salary + (_salary*percent);
	return _salary;
}

std::string Employee::Print()
{
	//snippet obtenido de https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c 
	std::string s = std::to_string(_salary);
	// ese 

	return "Employee[" +_id+ ',' +  GetName() + ", " + s + ']';
}
