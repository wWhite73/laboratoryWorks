#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"


#include <string>
#include <Windows.h>
#include <random>
#include <iomanip>

using namespace std;

 void go_dirty(Deque clean, Stack dirty) {
	if (rand() % 2 == 1) {
		dirty.push(clean.pop_front());
	}
	else {
		dirty.push(clean.pop_back());
	}
}

int go_front_dirty(Deque clean, Stack dirty) {
		int plate;
		plate = clean.pop_front();
		dirty.push(plate);
		return plate;
}

 int go_back_dirty(Deque clean, Stack dirty) {
		 int plate;
		 plate = clean.pop_back();
		 dirty.push(plate);
		 return plate;
	 }

void go_machine(Stack dirty, Queue machine1, Queue machine2) {
	if (rand() % 2 == 1) {
		machine1.push(dirty.pop());
	}
	else {
		machine2.push(dirty.pop());
	}
}

int go_one_machine(Stack dirty, Queue machine) {
	int plate = dirty.pop();
	machine.push(plate);
	return plate;
}

void go_clean(Queue machine, Deque clean) {
	if (rand() % 2 == 1) {
		clean.push_front(machine.pop());
	}
	else {
	
		clean.push_back( machine.pop());
	}
}

int go_front_clean(Queue machine, Deque clean) {
		int plate;
		plate = machine.pop();
		clean.push_front(plate);
		return plate;
}

int go_back_clean(Queue machine, Deque clean) {
	int plate;
	plate = machine.pop();
	clean.push_back(plate);
	return plate;
}

void start(Stack dirty,Queue machine1, Queue machine2, Deque clean)
{
	int i = rand() % 3 + 1;
	switch (i) {
	case 1:
		if (clean.length()) {
			go_dirty(clean, dirty);
		}
		break;
	case 2:
		if (dirty.length()) {
			go_machine(dirty, machine1, machine2);
		}
		break;
	case 3:
		if (machine1.length()) {
			go_clean(machine1, clean);
		}
		if (machine2.length()) {
			go_clean(machine2, clean);
		}
	}
}


void draw(int first_cln, int last_cln, int top_drt, int mech1_drt, int mech2_drt) {
	if (mech1_drt == first_cln || mech1_drt == last_cln) mech1_drt = -1;
	if (mech2_drt == first_cln || mech2_drt == last_cln) mech2_drt = -1;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 7);
	cout << " \n";

	SetConsoleTextAttribute(handle, 7);
	cout << setw(5) << " " << first_cln << " ";
	SetConsoleTextAttribute(handle, 119);
	cout << setw(11) << " ";
	SetConsoleTextAttribute(handle, 7);
	cout << " " << last_cln << "\n";

	SetConsoleTextAttribute(handle, 7);
	cout << setw(25) << " ";
	SetConsoleTextAttribute(handle, 6);
	cout << top_drt << "\n";
	for (int i = 0; i < 4; i++)
	{
		SetConsoleTextAttribute(handle, 7);
		cout << setw(25) << " ";
		SetConsoleTextAttribute(handle, 102);
		cout << "  ";
		SetConsoleTextAttribute(handle, 7);
		cout << "  \n";
	}

	SetConsoleTextAttribute(handle, 7);
	cout << setw(5) << " ";
	SetConsoleTextAttribute(handle, 51);
	cout << setw(11) << " ";
	SetConsoleTextAttribute(handle, 3);
	cout << " " << mech1_drt;
	SetConsoleTextAttribute(handle, 7);

	SetConsoleTextAttribute(handle, 7);
	cout << endl << setw(5) << " ";
	SetConsoleTextAttribute(handle, 51);
	cout << setw(11) << " ";
	SetConsoleTextAttribute(handle, 3);
	cout << " " << mech2_drt;
	SetConsoleTextAttribute(handle, 7);
}


int main() {
	setlocale(0, "Russian");
	srand(time(0));
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 6);
	cout << "\n грязная ";
	SetConsoleTextAttribute(handle, 102);
	cout << " ";
	SetConsoleTextAttribute(handle, 7);
	cout << "\n чистая  ";
	SetConsoleTextAttribute(handle, 119);
	cout << " ";
	SetConsoleTextAttribute(handle, 3);
	cout << "\n в машине (моется) ";
	SetConsoleTextAttribute(handle, 51);
	cout << " ";
	SetConsoleTextAttribute(handle, 7);
	cout << " \n";




	Stack dirty;
	Queue machine1;
	Queue machine2;
	Deque clean;

	int first_cln = -1;
	int last_cln = -1;
	int top_drt = -1;
	int mech1_drt = -1;
	int mech2_drt = -1;

	for (int i = 0; i < 15; i++)
	{
		clean.push_front(i);
	}
	first_cln = clean.pop_front();
	clean.push_front(first_cln);
	last_cln = clean.pop_back();
	clean.push_back(last_cln);
	for (int i = 15; i < 26; i++) {
		dirty.push(i);
	}
	top_drt = dirty.pop();
	dirty.push(top_drt);



	for (int j = 0; j < 100; j++)
	{
		int i = rand() % 3 + 1;
		switch (i) {
		case 1:
			if (clean.length()) {
				if (rand() % 2 == 1) {
					top_drt = clean.pop_front();
					dirty.push(top_drt);
					cout << "\n\nЧистая тарелка взята спереди и стала грязной\n";

					first_cln = clean.pop_front();
					if (first_cln !=-42)
					clean.push_front(first_cln);
				}
				else {
					top_drt = clean.pop_back();
					dirty.push(top_drt);
					cout << "\n\nЧистая тарелка взята сзади и стала грязной\n";

					last_cln = clean.pop_back();
					if (last_cln != -42)
						clean.push_back(last_cln);
				}
			}
			break;
		case 2:
			if (dirty.length()) {
				if (rand() % 2 == 1) {
					mech1_drt = dirty.pop();
					machine1.push(mech1_drt);
					cout << "\n\nГрязную тарелку положили на первую пролосу посудомоечной машины\n";
				}
				else {
					mech2_drt = dirty.pop();
					machine2.push(mech2_drt);
					cout << "\n\nГрязную тарелку положили на вторую полосу посудомоечной машины\n";
				}
				top_drt = dirty.pop();
				if (top_drt != -42)
					dirty.push(top_drt);
			}
			break;
		case 3:
			if (machine1.length()) {
				if (rand() % 2 == 1) {
					first_cln = machine1.pop();
					clean.push_front(first_cln);
					cout << "\n\nТарелку из посудомоечной машины (первая полоса) положили в начало чистой посуды\n";
				}
				else {
					last_cln = machine1.pop();
					clean.push_back(last_cln);
					cout << "\n\nТарелку из посудомоечной машины (первая полоса) положили в конец чистой посуды\n";
				}
			}
			if (machine2.length()) {
				if (rand() % 2 == 1) {
					first_cln = machine2.pop();
					clean.push_front(first_cln);
					cout << "\n\nТарелку из посудомоечной машины (вторая полоса) положили в начало чистой посуды\n";
				}
				else {
					last_cln = machine2.pop();
					clean.push_front(last_cln);
					cout << "\n\nТарелку из посудомоечной машины (вторая полоса) положили в конец чистой посуды\n";
				}
			}
		}
		draw(first_cln, last_cln, top_drt, mech1_drt, mech2_drt);
		Sleep(300);
	}

}