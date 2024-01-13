#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

long double functionValue(long double x) {
	return exp(-x) + pow(x,2);
}

long double derivativeValue(long double x) { //производное значение 
	return 2*x -(exp(-x));
}

long double secondDerivativeValue(long double x) {
	return log(2) * log(2) * (exp(-x) + pow(x, 2));
}

void rightDerivative(long double start, long double end, long double delta) {
	cout << "r: ";
	for (long double i = start; i < end - delta; i += delta) {
		cout << setw(10) << (functionValue(i + delta) - functionValue(i)) / delta;
	}
	cout << setw(10) << "---";
	cout << "\n";
}

void leftDerivative(long double start, long double end, long double delta) { 
	cout << "l: ";
	cout << setw(10) << "---";
	for (long double i = start + delta; i < end; i += delta) {
		cout << setw(10) << (functionValue(i) - functionValue(i - delta)) / delta;
	}
	cout << "\n";
}

void centerDerivative(long double start, long double end, long double delta) {
	cout << "c: ";
	cout << setw(10) << "---";
	for (long double i = start + delta; i < end - delta; i += delta) {
		cout << setw(10) << (functionValue(i + delta) - functionValue(i - delta)) / (2 * delta);
	}
	cout << setw(10) << "---";
	cout << "\n";
}

void realDerivative(long double start, long double end, long double delta) {
	cout << "t: ";
	for (long double i = start; i < end; i += delta) {
		cout << setw(10) << derivativeValue(i);
	}
	cout << "\n\n";
}

void secondDerivative(long double start, long double end, long double delta) {
	cout << "s: ";
	cout << setw(10) << "---";
	for (long double i = start + delta; i < end - delta; i += delta) {
		cout << setw(10) << (functionValue(i + delta) + functionValue(i - delta) - 2 * functionValue(i)) / (delta * delta);
	}
	cout << setw(10) << "---";
	cout << "\n";
}

void realSecondDerivative(long double start, long double end, long double delta) {
	cout << "t: ";
	for (long double i = start; i < end; i += delta) {
		cout << setw(10) << secondDerivativeValue(i);
	}
	cout << "\n\n";
}

int main() {
	setlocale(LC_ALL, "Russian");

	long double start = 0, end = 1, delta;

	cout << "Начальное знаечение: "<< start << endl;
	

	cout << "Конечное значение: "<< end << endl;
	

	cout << "введите шаг: ";
	cin >> delta;

	cout << "\n\n";


	rightDerivative(start, end, delta);
	leftDerivative(start, end, delta);
	centerDerivative(start, end, delta);
	realDerivative(start, end, delta);
	secondDerivative(start, end, delta);
	realSecondDerivative(start, end, delta);

	return 0;
}