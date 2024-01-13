#include <iostream>
#include <cmath>
#include <math.h>
#include <conio.h>

using namespace std;

int factoriall(int x) {
	int result = 1;
	for (int i = 1; i <= x; i++) {
		result *= i;
	}

	return result;
}

class  sinIs {
	double element = 1;
	double sum = this->element;

	double calcElement(double x, int i) {
		return pow(-1, i)* pow(x, 2 * i + 1) / factoriall(2 * i + 1);
	}

public:
	sinIs(long double x, int n) {
		for (int i = 1; i < n; i++) {
			/*this->sum += calcElement(x, i);*/
			this->element *= x / i;
			sum += element;
		}
	}

	void print_sum() {
		cout << "Сумма: "<< this->sum<< endl;
	}

};

int main() {
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "Введите количество членов суммы: ";
	cin >> n;

	long double x;
	cout << "Введите значение x: ";
	cin >> x;

	sinIs value = sinIs(x, n);
	value.print_sum();

	return 0;
}
