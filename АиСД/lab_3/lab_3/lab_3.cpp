// Консольные шахматы v 1.0 от 16.01.2016 (Termit779)

#include<iostream>
#include <string>
using namespace std;

string buff; // Буфер хранения фигуры
bool flag_buff = false; // Флаг буфера    
string doska[9][9]; // Массив представления
bool doska_b[9][9]; // Массив состояния
int sum_hod = 0; // Считаем полуходы

struct Figura // Фигуры
{
    string Kw, Kb, Qw, Qb, Rw, Rb, Nw, Nb, Bw, Bb, Pw, Pb;
    Figura()
        : Kw{ "Kw" }, Kb{ "Kb" }, Qw{ "Qw" }, Qb{ "Qb" }, Rw{ "Rw" }, Rb{ "Rb" }, Nw{ "Nw" },
        Nb{ "Nb" }, Bw{ "Bw" }, Bb{ "Bb" }, Pw{ "Pw" }, Pb{ "Pb" }
    {

    }
};

void doska_print() // Вывод доски и фигур на экран
{
   /* system("cls")*/; // Очищаем консоль (для Windows. В *Nix вроде не "канает")
    char num = 'a'; // Для вывода указателей столбцов (a,b,c,d ...)
    cout << "|Выход 'Ctrl+Z'|" << endl;
    cout << "\t\t\t    Консольные шахматы v 1.0" << endl
        << "\t\t\tПример хода: 'e2 e4' через пробел" << endl
        << "\t\t     (пешка белых пошла с позиции e2 на e4)";
    cout << "\n\n";
    for (int i = 0; i < 8; i++)
    {
        cout << "\t\t\t" << 8 - i;
        for (int j = 0; j < 9; j++)
        {
            cout << doska[i][j];
        }
        cout << endl;
    }
    cout << "\t\t\t";
    for (int i = 1; i < 9; i++)
    {
        cout << "   " << num;
        ++num;
    }
    if (sum_hod % 2 == 0 & sum_hod > 0 | sum_hod == 1) {
        cout << endl << "Ход черных: "; // Приглашение к ходу
    }
    else {
        cout << endl << "Ход  белых: ";
    }
   
}

void doska_default() {  // Начальное положение доски и фигур
    Figura f;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            doska[i][j] = "|__|";
            doska_b[i][j] = 0;
        }
    }
    for (int i = 1; i < 9; i++)
    {
        doska[1][i] = "|" + f.Pb + "|"; doska_b[1][i] = 1;
        doska[6][i] = "|" + f.Pw + "|"; doska_b[6][i] = 1;
    }
    doska[0][1] = doska[0][8] = "|" + f.Bb + "|"; doska_b[0][1] = doska_b[0][8] = 1;
    doska[7][1] = doska[7][8] = "|" + f.Bw + "|"; doska_b[7][1] = doska_b[7][8] = 1;
    doska[0][2] = doska[0][7] = "|" + f.Nb + "|"; doska_b[0][2] = doska_b[0][7] = 1;
    doska[7][2] = doska[7][7] = "|" + f.Nw + "|"; doska_b[7][2] = doska_b[7][7] = 1;
    doska[0][3] = doska[0][6] = "|" + f.Rb + "|"; doska_b[0][3] = doska_b[0][6] = 1;
    doska[7][3] = doska[7][6] = "|" + f.Rw + "|"; doska_b[7][3] = doska_b[7][6] = 1;
    doska[0][4] = "|" + f.Qb + "|"; doska_b[0][4] = 1;
    doska[0][5] = "|" + f.Kb + "|"; doska_b[0][5] = 1;
    doska[7][4] = "|" + f.Qw + "|"; doska_b[7][4] = 1;
    doska[7][5] = "|" + f.Kw + "|"; doska_b[7][5] = 1;

    doska_print(); // Выводим доску и фигуры
}

void doska_figura_remove(int x, int y) // Удаляет фигуру из указанной позиции
{
    doska[8 - y][8 - (104 - x)] = "|__|";
}

void doska_hod(int x, int y) // Выполнить ход (только ход, не обработчик игрового сюжета)
{
    if (doska_b[8 - y][8 - (104 - x)] == 1) { // В клетке стоит фигура
        buff = doska[8 - y][8 - (104 - x)]; // Фигуру в буфер
        doska_figura_remove(x, y); // Удалить фигуру с доски
        doska_b[8 - y][8 - (104 - x)] = 0; // Состояние клетки в false
        flag_buff = true;   // Поднять флаг (буфер не пустой)... Возможно понадобится
    }
    else {                      // В клетке пусто
        doska[8 - y][8 - (104 - x)] = buff; // Поставить фигуру из буфера в клетку
        doska_b[8 - y][8 - (104 - x)] = 1; // Состояние клетки в true (не пуста)
        buff = "";              // Обнулить буфер
        flag_buff = false;      // Опустить флаг, буфер свободен
        doska_print();          // Выводим доску и фигуры
    }
    ++sum_hod; // Увеличим счетчик полуходов
}

int main() {
    setlocale(0, "Russian");
    doska_default();
    int str = 0;
    char stb = 0;
    while (cin >> stb >> str)
    {
        doska_hod(stb, str);
    }
    return 0;
}