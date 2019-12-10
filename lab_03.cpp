#include <iostream>
#include "math.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
double Random(double left, double right)//Выбор случайной координаты на интервале
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(left * 100000000, right * 100000000);
	double x = distribution(generator);
	return x / 100000000;
}
//Унимодальная функция
double u_function(double x)
{
	return 2 * cos(x) + log10(x);
}
//Мультимодальная функция
double m_function(double x)
{
	return u_function(x) * sin(5 * x);
}
//Вероятность перехода
bool probability(double P)
{
	double value = Random(0, 1);
	if (value <= P)
		return true;
	else
		return false;
}
//Метод имитации отжига
void metod(double left, double right)
{
	double x, xk, P, df, xmin;
	std::string p;
	double Tmax = 1000;//Начальное значение температуры
	double Tmin = 0.001;//Конечное значение температуры
	double T = Tmax;
	xk = Random(left, right);
	xmin = xk;
	int i = 1;
	std::cout << std::fixed;
	std::cout << "+---+------------+----------+------------+------------+-------------+" << std::endl;
	std::cout << "|" << std::setw(3) << "N" << "|" << std::setw(12) << "T" << "|" << std::setw(10) << "x" << "|" << std::setw(12) << "f(x)" << "|" << std::setw(12) << "P" << "|" << std::setw(13) << "true or false" << "|" << std::endl;
	std::cout << "+---+------------+----------+------------+------------+-------------+" << std::endl;
	while (T > Tmin)
	{

		if (T == 1000)
		{
			P = 100;
			p = "true";
			std::cout << "|" << std::setw(3) << i << "|" << std::setw(12) << T << "|" << std::setw(10) << xk << "|" << std::setw(12) << u_function(xk) << "|" << std::setw(12) << P << "|" << std::setw(13) << p << "|" << std::endl;
			T = Tmax * 0.95;
			Tmax = T;
			i++;
			continue;
		}
		x = Random(left, right);
		df = u_function(x) - u_function(xk);//Вычисляем разность значений функции,для дальнейшего сравнения
		if (df <= 0)
		{
			P = 100;
			xk = x;
			p = "true";//Переход выполнен
		}
		else
		{
			P = exp(-df / T);//Вероятность перехода
			probability(P);
			P = P * 100;
			if (probability(P) == true)
			{
				xk = x;
				p = "true";//Переход выполен
			}
			else
			{
				p = "false";//Переход не выполнен
			}
		}
		//Вывод значений
		std::cout << "|" << std::setw(3) << i << "|" << std::setw(12) << T << "|" << std::setw(10) << xk << "|" << std::setw(12) << u_function(xk) << "|" << std::setw(12) << P << "|" << std::setw(13) << p << "|" << std::endl;
		if (u_function(xk) < u_function(xmin))
		{
			xmin = xk;
		}
		T = Tmax * 0.95;//Понижение температуры
		Tmax = T;
		i++;
	}
	//Вывод наименьшего значения функции на заданном интервале 
	std::cout << "+---+------------+----------+------------+------------+-------------+" << std::endl;
	std::cout << "Result:" << ' ' << "Xmin=" << xmin << ' ' << "Fmin=" << u_function(xmin);
	std::cout << std::endl << std::endl;


	//Мультимодальная функции
	std::cout << "+---+------------+----------+------------+------------+-------------+" << std::endl;
	std::cout << "|" << std::setw(3) << "N" << "|" << std::setw(12) << "T" << "|" << std::setw(10) << "x" << "|" << std::setw(12) << "f(x)" << "|" << std::setw(12) << "P" << "|" << std::setw(13) << "true or false" << "|" << std::endl;
	std::cout << "+---+------------+----------+------------+------------+-------------+" << std::endl;
	xmin = xk;
	Tmax = 1000;//Начальное значение температуры
	Tmin = 0.001;//Конечное значение температуры
	T = Tmax;
	i = 1;
	while (T > Tmin)
	{
		if (T == 1000)
		{
			P = 100;
			std::cout << "|" << std::setw(3) << i << "|" << std::setw(12) << T << "|" << std::setw(10) << xk << "|" << std::setw(12) << u_function(xk) << "|" << std::setw(12) << P << "|" << std::setw(13) << p << "|" << std::endl;
			T = Tmax * 0.95;
			Tmax = T;
			i++;
			continue;
		}
		x = Random(left, right);
		df = m_function(x) - m_function(xk);//Вычисляем разность значений функции,для дальнейшего сравнения
		if (df <= 0)
		{
			P = 100;
			xk = x;
			p = "true";//Переход выполнен
		}
		else
		{
			P = exp(-df / T);//Вероятность перехода
			probability(P);
			P = P * 100;
			if (probability(P) == true)
			{
				xk = x;
				p = "true";//Переход выполнен
			}
			else
			{
				p = "false";//Переход не выполнен
			}
		}
		//Ввывод значений 
		std::cout << "|" << std::setw(3) << i << "|" << std::setw(12) << T << "|" << std::setw(10) << xk << "|" << std::setw(12) << u_function(xk) << "|" << std::setw(12) << P << "|" << std::setw(13) << p << "|" << std::endl;
		if (m_function(xk) < m_function(xmin))
		{
			xmin = xk;
		}
		T = Tmax * 0.95;//Понижение температуры
		Tmax = T;
		i++;
	}
	//Вывод наименьшего значения функции на заданном интервале
	std::cout << "+---+------------+----------+------------+------------+-------------+" << std::endl;
	std::cout << "Result:" << ' ' << "Xmin=" << xmin << ' ' << "Fmin=" << m_function(xmin);
}
int main()
{
	metod(1.5, 5);
	return 0;
}