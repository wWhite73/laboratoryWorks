#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class hid {
	int data;
	bool deletion;
public:
	hid() {
		data = 0;
		deletion = true;
	}
	hid(int DATA) {
		data = DATA;
		deletion = false;
	}
	void del() {
		deletion = true;
	}
	bool check_del() {
		return deletion;
	}
	int get_data() {
		return data;
	}
};

class htable {
	vector<hid> table;
	int size;
public:
	htable(int SIZE) {
		size = SIZE + 1;
		table.resize(size);
	}
	void add(int key) {
		hid a = hid(key);
		int position = key % size; //остаток от деления
		int attempt = 0;
		const int step = 1;
		bool success = false;
		while (!success) {
			if (position > size - 1) {
				table.resize(position + 1);
				size = position + 1;
			}
			if (table[position].check_del()) {
				table[position] = a;
				success = true;
			}
			else {					//линейное опробование
				position = key % size + attempt * step;
				attempt++;
			}
		}//Линейное опробование сводится к последовательному перебору сегментов таблицы с некоторым фиксированным шагом: адрес=h(x)+ci, 
		 //где i – номер попытки разрешить коллизию; c – константа, определяющая шаг перебора.

	}
	bool find(int data) {          
		int attempt = 0;
		while (attempt <= size - 1) {
			if (table[attempt].get_data() == data && !table[attempt].check_del()) {
				return true;
			}
			attempt++;
		}
		return false;
	}
	int get_position(int pos) {
		return table[pos].get_data();
	}
};


int main() {
	setlocale(LC_ALL, "Rus");
	int size;
	cout << "Введите размер: ";
	cin >> size;
	if (size < 1000) {
		cout << "Размер должен быть больше или равен 1000!\n";
		return 1;
	}
	htable a = htable(size);


	// первая 1000
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 0; i <= 1000; i++)
	{
		int b = rand();
		a.add(b);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "Время первой тысячи: " << duration << " наносекунд" << endl;

	// промежуток
	for (int i = 1001; i <= size - 1000; i++)
	{
		int b = rand();
		a.add(b);
	}

	// последняя 1000
	if (size - 1000 >= 1000) {
		t1 = high_resolution_clock::now();
		for (int i = size - 999; i <= size; i++)
		{
			int b = rand();
			a.add(b);
		}
		t2 = high_resolution_clock::now();

		duration = duration_cast<nanoseconds>(t2 - t1).count();
		cout << "Время последней тысячи: " << duration << " наносекунд" << endl;
	}

	// поиск
	int find = a.get_position(rand() % size);
	t1 = high_resolution_clock::now();
	a.find(find);
	t2 = high_resolution_clock::now();

	duration = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "Время поиска (есть в таблице): " << duration << " наносекунд" << endl;

	t1 = high_resolution_clock::now();
	a.find(-12);
	t2 = high_resolution_clock::now();

	duration = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "Время поиска (нет в таблице): " << duration << " наносекунд" << endl;
}
