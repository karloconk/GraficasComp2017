#include <iostream>
using namespace std;

int PerimetroRectangulo(int base, int altura)
{
	return 2 * (base + altura);
}

float AreaTriangulo(float base, float altura)
{
	return (base*altura) / 2;
}

int Mayor(int numero1,int numero2, int numero3)
{
	int top = numero1; 
	if (numero2 > top) 
	{
		top = numero2;
	}
	if (numero3 > top)
	{
		top = numero3;
	}
	return top;
}

int Menor(int numero1, int numero2, int numero3)
{
	int top = numero1;
	if (numero2 < top)
	{
		top = numero2;
	}
	if (numero3 < top)
	{
		top = numero3;
	}
	return top;
}

void FilaEstrellas(int n)
{
	for(int o = 0; o<n;o++) 
	{
		cout << "*" ;
	}
	cout << " " << endl;
}

void MatrizEstrellas(int n)
{
	for (int ok = 0; ok < n; ok++)
	{
		for (int o = 0; o < n; o++)
		{
			cout << "*";
		}
		cout << " " << endl;
	}
	cout << " " << endl;
}

void PiramideEstrellas(int n)
{
	for (int ok = 0; ok < n; ok++)
	{
		for (int o = 0; o <= ok; o++)
		{
			cout << "*";
		}
		cout << " " << endl;
	}
	cout << " " << endl;
}

void FlechaEstrellas(int n)
{
	int u = 0;
	//Upperpart
	for (int ok = 0; ok < n; ok++)
	{
		for (int o = 0; o <= ok; o++)
		{
			cout << "*";
		}
		cout << " " << endl;
		u = ok - 1;
	}

	//lowerpart
	for (int ok = u; ok >= 0; ok--)
	{
		for (int o = 0; o <= ok; o++)
		{
			cout << "*";
		}
		cout << " " << endl;
	}
	cout << " " << endl;
}

void Fibonacci(int n)
{
	int one, two, three;
	for (int i = 0;i<n;i++)
	{
		if (i<2) 
		{
			one = 1;
			two = 1;
			cout << 1;
		}
		else 
		{
			three = two+one;
			one = two;
			two = three;
			cout << two;
		}

		if (i < n - 1) 
		{
			cout << ',';
		}
		else 
		{
			cout << endl;
		}
	}

}

bool EsPrimo(int numero)
{
	if (numero <= 1) 
	{ 
		return false;
	}
	if (numero % 2 == 0 && numero !=2 ) 
	{
		return false;
	}
	for(int i = 3;i<numero;i+=2) 
	{
		if (i != numero) 
		{
			if (numero%i == 0) 
			{
				return false;
			}
		}
	}
	return true;
}

int main() 
{
	//1--------------------------------------------------------------------
	cout << "PerimetroRectangulo(5,3)" << endl;
	cout << PerimetroRectangulo(5,3) << endl;

	//2--------------------------------------------------------------------
	cout << "AreaTriangulo(5.0f,3.0f)" << endl;
	cout << AreaTriangulo(5.0f, 3.0f) << endl;

	//3--------------------------------------------------------------------
	cout << "Mayor(5,9,1)" << endl;
	cout << Mayor(5, 9, 1) << endl;

	//4--------------------------------------------------------------------
	cout << "Menor(5,9,1)" << endl;
	cout << Menor(5, 9, 1) << endl;

	//5--------------------------------------------------------------------
	cout << "FilaEstrellas(5)" << endl;
	FilaEstrellas(5);

	//6--------------------------------------------------------------------
	cout << "MatrizEstrellas(4)" << endl;
	MatrizEstrellas(4);

	//7--------------------------------------------------------------------
	cout << "PiramideEstrellas(6)" << endl;
	PiramideEstrellas(6);

	//8--------------------------------------------------------------------
	cout << "FlechaEstrellas(3)" << endl;
	FlechaEstrellas(3);

	//9--------------------------------------------------------------------
	cout << "Fibonacci(9)" << endl;
	Fibonacci(9);

	//10-------------------------------------------------------------------
	cout << "EsPrimo(79)" << endl;
	bool one = EsPrimo(79);
	if (one == true)
	{
		cout << "Es primo" << endl;
	}
	else 
	{
		cout << "No es" << endl;
	}

	cout << "EsPrimo(52)" << endl;
	one = EsPrimo(52);
	if (one == true)
	{
		cout << "Es primo" << endl;
	}
	else
	{
		cout << "No es" << endl;
	}
	cin.get();

	return 0;
}