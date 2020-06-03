// Methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <math.h>
#include "windows.h"
#include <iostream>

using namespace std;

float F(double x, double y) // y'
{
	return 4 * cos(x) + sin(2 * x);
}

//Вывод
void Output(float* X, float* Y, int n)
{
	for (int i = 0; i <= n; i++)
	{
		cout << "X[" << i << "]=" << X[i] << " ";
	}
	cout << endl;
	for (int i = 0; i <= n; i++)
	{
		cout << "Y[" << i << "]=" << Y[i] << " ";
	}
}

//Модифицированный метод Эйлера
void ModifiedEulerMethod(double a1, double a2, double b, float h, float* X, float* Y, int n )
{
	X[0] = a1; Y[0] = a2;
	float y12;
	for (int i = 0; i <= n; i++) 
	{
		y12 = Y[i] + h / 2 * F(X[i], Y[i]);
		Y[i + 1] = Y[i] + h * F(X[i] + h / 2, y12);
		X[i + 1] = X[i] + h;
	}
	Output(X, Y, n);
}

//Метод Эйлера с пересчетом
void EulerMethodWithRecalculation(double a1, double a2, double b, float h, float* X, float* Y, int n)
{
	X[0] = a1; Y[0] = a2; 
	float y12;
	for (int i = 0; i <= n; i++)
	{
		y12 = Y[i] + h * F(X[i], Y[i]);
		Y[i + 1] = Y[i] + h / 2 * (F(X[i], Y[i]) + F(X[i] + h, y12));
		X[i + 1] = X[i] + h;
	}
	Output(X, Y, n);
}

//Метод Рунге - Кутты 4 порядка
void RungeKuttaMethod(double a1, double a2, double b, float h, float* X, float* Y, int n)
{
	float* Y1 = new float[n];
	float* Y2 = new float[n];
	float* Y3 = new float[n];
	float* Y4 = new float[n];
	X[0] = a1; Y[0] = a2;
	for (int i = 1; i <= n; i++) 
	{
		X[i] = a1 + i * h;
		Y1[i] = h * F(X[i - 1], Y[i - 1]);
		Y2[i] = h * F(X[i - 1] + h / 2.0, Y[i - 1] + Y1[i] / 2.0);
		Y3[i] = h * F(X[i - 1] + h / 2, Y[i - 1] + Y2[i] / 2);
		Y4[i] = h * F(X[i - 1] + h, Y[i - 1] + Y3[i]);
		Y[i] = Y[i - 1] + (Y1[i] + 2 * Y2[i] + 2 * Y3[i] + Y4[i]) / 6;
	}
	Output(X, Y, n);
}

//Метод Адамса
void AdamsMethod(double a1, double a2, double b, float h, float* X, float* Y, int n)
{
	double k1, k2, k3, k4;
	float* f = new float[n];
	X[0] = a1; Y[0] = a2;
	f[0] = F(X[0], Y[0]);
	for (int i = 0; i <= n; i++)
	{
		X[i+1] = X[i] + h;
		f[i + 1] = F(X[i + 1], Y[i + 1]);
	}
	for (int i = 1; i < 4; i++)
	{
		k1 = h * f[i - 1];
		k2 = h * F(X[i - 1] + h / 2, Y[i - 1] + k1 / 2);
		k3 = h * F(X[i - 1] + h / 2, Y[i - 1] + k2 / 2);
		k4 = h * F(X[i - 1] + h, Y[i - 1] + k3);
		Y[i] = Y[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}	
	for (int i = 3; i < n; i++)
	{		
		Y[i + 1] = Y[i] + h / 24 * (55.0 * f[i] - 59.0 * f[i - 1] + 37.0 * f[i - 2] - 9.0 * f[i - 3]);		
	}
	Output(X, Y, n);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double a1; double a2; double b; float h; double n;
	cout << "Введите начальное условие задачи Коши (y(0)): " << endl;
	cin >> a2;
	cout << "Введите шаг: " << endl;
	cin >> h;
	cout << "Введите начало отрезка, на котором надо решить ДУ: " << endl;
	cin >> a1;
	cout << "Введите конец отрезка: " << endl;
	cin >> b;
	n = (b - a1) / h;
	float* X = new float[(int)n];
	float* Y = new float[(int)n];
	cout << "Модифицированный метод Эйлера:" << endl;
	ModifiedEulerMethod(a1,a2,b,h,X,Y,(int)n);
	cout << endl << endl;
	cout << "Метод Эйлера с пересчетом:"<<endl;
	EulerMethodWithRecalculation(a1, a2, b, h, X, Y, (int)n);
	cout << endl << endl;
	cout << "Метод Рунге-Кутты 4 порядка:" << endl;
	RungeKuttaMethod(a1, a2, b, h, X, Y, (int)n);
	cout << endl << endl;
	cout << "Метод Адамса:" << endl;
	AdamsMethod(a1, a2, b, h, X, Y, (int)n);
	cout << endl << endl;
}