#pragma once

void draw(int first_cln, int last_cln, int top_drt, int mech1_cln, int mech1_drt) {
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
	cout << "\n\n";

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
		cout << "  \n";
	}

	SetConsoleTextAttribute(handle, 7);
	cout << setw(5) << " ";
	SetConsoleTextAttribute(handle, 3);
	cout << mech1_cln << " ";
	SetConsoleTextAttribute(handle, 51);
	cout << setw(11) << " ";
	SetConsoleTextAttribute(handle, 3);
	cout << " " << mech1_drt;
}

void stable_start(Stack dirty, Queue machine1, Queue machine2, Deque clean) {

	int first_cln = 0;
	int last_cln = 0;
	int top_drt = 0;
	int mech1_cln = 0;
	int mech1_drt = 0;
	int mech2_cln = 0;
	int mech2_drt = 0;

	int i = rand() % 3 + 1;
	switch (i) {
	case 1:
		if (!clean.isEmpty()) {
			int j = rand() % 2;
			if (j == 1) {
				first_cln = 80085;
			}
			else last_cln - 80085;
			top_drt = go_front_dirty(clean, dirty);
		}
		break;
	case 2:
		if (!dirty.isEmpty()) {
			int j = rand() % 2;
			if (j == 1) {
				mech1_cln = go_one_machine(dirty, machine1);
			}
			else mech2_cln = go_one_machine(dirty, machine2);

		}
		break;
	case 3:
		if (!machine1.isEmpty()) {
			int j = rand() % 2;
			if (j == 1) {
				first_cln = go_front_clean(machine1, clean);
			}
			else last_cln = go_back_clean(machine1, clean);
		}
		if (!machine2.isEmpty()) {
			int j = rand() % 2;
			if (j == 1) {
				first_cln = go_front_clean(machine2, clean);
			}
			else last_cln = go_back_clean(machine2, clean);
		}
	};
	draw(first_cln, last_cln, top_drt, mech1_cln, mech1_drt);
}