﻿#include <iostream>
#include <math.h>


#define _USE_MATH_DEFINES 

using namespace std;

long double function_value(long double x) {
	return x / ((2 * x) + 1);
}

long double antiderivative(long double x) {
	return (x / 2) - ((1 / 4) * (log(abs(2 * x + 1))));
}

long double left_rectangle(long double start, long double end, int n) {
	cout << "\n\n";
	long double result = 0;
	long double h = (end - start) / n;

	for (long double i = start; i < end; i += h) {
		result += function_value(i) * h;
	}

	return result;
}

long double right_rectangle(long double start, long double end, int n) {
	cout << "\n\n";
	long double result = 0;
	long double h = (end - start) / n;

	for (long double i = end; i > start; i -= h) {
		result += function_value(i) * h;
	}

	return result;
}

long double center_rectangle(long double start, long double end, int n) {
	cout << "\n\n";
	long double result = 0;
	long double h = (end - start) / n;

	for (long double i = start; i < end; i += h) {
		result += function_value(i + h / 2) * h;
	}

	return result;
}

long double trapezoidal_method(long double start, long double end, int n) {
	cout << "\n\n";
	long double result = 0;
	long double h = (end - start) / n;

	for (long double i = start; i < end; i += h) {
		result += (function_value(i) + function_value(i + h)) / 2 * h;
	}

	return result;
}

long double parabola_method(long double start, long double end, int n) {
	cout << "\n\n";
	long double result = 0;
	long double h = (end - start) / n;

	for (long double i = start + h; i < end - h; i += 2 * h) {
		result += h / 3 * (function_value(i - h) + 4 * function_value(i) + function_value(i + h));
	}

	return result;
}

long double gauss_method(long double start, long double end, int n) {
	cout << "\n\n";
	long double result = 0;

	long double xk[] = { -0.9324700, -0.6612094, -0.2386142, 0.2386142, 0.6612094, 0.9324700 };
	long double cn[] = { 0.1713245, 0.3607616, 0.4679140, 0.4679140, 0.3607616, 0.1713245 };

	for (int i = 0; i < 6; i++) {
		result += cn[i] * function_value(((end - start) / 2) * xk[i] + ((end + start) / 2));
	}

	return ((end - start) / 2) * result;
}
long double anti(long double x1=1,long double x2 = 0.2) {
	return ((x1 / 2) - ((1 / 4) * (log(abs(2 * x1 + 1)))))- ((x2 / 2) - ((1 / 4) * (log(abs(2 * x2 + 1)))));
}


int main() {
	setlocale(LC_ALL, "Russian");

	long double start = 0.2;
	long double end = 1;

	cout << "Начало интервала интегрирования: " << start << endl;
	cout << "Конец интервала интегрирования: " << end  << endl;

	int n = 0;
	cout << "Введите число отрезков разбиения: ";
	cin >> n;
	long double gvhug;
	gvhug = antiderivative(1) - antiderivative(0.2);

	cout << "\n\n";
	cout << "Значение интеграла по формуле Ньютона-Лейбница: " << anti << endl;
	cout << "Значение интеграла по методу левых прямоугольников: " << left_rectangle(start, end, n) << endl;
	cout << "Значение интеграла по методу правых прямоугольников: " << right_rectangle(start, end, n) << endl;
	cout << "Значение интеграла по методу центральных прямоугольников: " << center_rectangle(start, end, n) << endl;
	cout << "Значение интеграла по методу трапеций: " << trapezoidal_method(start, end, n) << endl;
	cout << "Значение интеграла по методу параболы: " << parabola_method(start, end, n) << endl;
	cout << "Значение интеграла по методу Гаусса: " << gauss_method(start, end, n) << endl;

	cout << "\n\n";
	return 0;
}