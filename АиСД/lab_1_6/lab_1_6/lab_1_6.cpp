#include <iostream>

using namespace std;


// Сложность O(x)
// Размерность l = 1
// Временная сложность T(l) = c * x
// Ёмкостная сложность S(l) = x + 1
// Алгоритм линейный
bool brute_force(int x) {
	for (int i = 2; i < x; i++) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}

// Сложность O(n*log(log(n)))
// Размерность l = (n - 1) + 1
// Временная сложность T(l) = c * n*log(log(n))
// Ёмкостная сложность S(l) = (n - 1) + 3
// Алгоритм экспоненциальный
bool sieve_of_eratosthenes(int n) {
	int* a = new int[n + 1];

	for (int i = 2; i < n + 1; i++) {
		a[i] = i;
	}

	for (int p = 2; p < n + 1; p++)
	{
		if (a[p] != 0)
		{
			if (a[p] == n) {
				return true;
			}

			for (int j = p * p; j < n + 1; j += p) {
				a[j] = 0;

			}
		}
	}
	return false;
}

int main() {

	cout << brute_force(1) << endl;
	cout << sieve_of_eratosthenes(21) << endl;


	return 0;
}
