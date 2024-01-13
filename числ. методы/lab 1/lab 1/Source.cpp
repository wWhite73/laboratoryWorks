#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <cmath>
#define _USE_MATH_DEFINES

using namespace std;

double f(double x) { return x - cos(0.387*x); }  //�������, ���� ������� ����
double df(double x) { return 0.387*sin(0.387*x) + 1; } // ����������� �� �������
double fx(double x, double xprev) {                       
    return x - ((f(x) * (x - xprev)) / (f(x) - f(xprev)));
}
//double fx2(double x0, double xk) { //������� ��� ����
//    return (xk - ((f(xk)) * (xk - x0) / (f(xk) - f(x0))));
//}
double fh(double x, double xprev) { //������� ��� ������ ����
    return x - ((f(x) * (x - xprev)) / (f(x) - f(xprev)));
}
double roots(double l, double r, double s) { //��������� �����
    int count = 0;
    while (l < r) {
        
        cout << setw(10) << count << setw(10) << l << setw(10) << f(l) << endl;
        l = l + s;
        count++;
    }
    return 0;
}
double mpi(double x) { //������� ��� ��������� ������ � ������� ������ ������� 1
    return (-x * x * x + 3 * x * x + 10) / 9;
}



int main()
{
    setlocale(0, "RU");
    double left, right, step;
    cout << "��������� ������" << endl;
    cout << "������� ����� �������: ";
    cin >> left;
    cout << "������� ������ �������: ";
    cin >> right;
    cout << "������� ��� ���������: ";
    cin >> step;
    cout << setw(10) << "Step" << setw(10) << "  x    " << setw(10) << "   y   \n";

    roots(left, right, step);
    cout << endl;

    //........................����� ���������..............................
    double left2, right2;
    double x;
    int count = 0;

    cout << "����� ���������" << endl;
    cout << "������� ����� �������:";
    cin >> left2;
    cout << "������� ������ �������: ";
    cin >> right2;

    cout << setw(10) << "[a, b]" << setw(16) << "x" << setw(16) << "y" << endl;
    x = ((left2 + right2) / 2);

    while (f(x) != 0) {
        x = ((left2 + right2) / 2);

        cout << "[" << left2 << "," << right2 << "]   ";
        cout << setw(16) << x;
        cout << setw(16) << f(x) << endl;
        if (((right2 - left2) / 2) < 0.001) break;
        if (f(x) < 0) left2 = x;
        else right2 = x;
        count++;
    }
    cout << "����������� ������: " << x << endl;
    cout << "���������� ��������: " << count << endl << endl;

    //........................����� �������.......................


    cout << "����� �������" << endl;
    double x9, x1, x2;
    count = 0;
    cout << "������� �0:";
    cin >> x9;
    cout << "������� �1: ";
    cin >> x1;

    while (fabs(x1 - x9) > 0.001) {
        x2 = fx(x1, x9);

        x9 = x1; x1 = x2;
        count++;
    }
    cout << "����������� ������: " << x1 << endl;
    cout << "���������� ��������: " << count << endl << endl;




    //........................����� �������........................
    cout << "����� �������" << endl;

    count = 0;
    double x0;
    cout << "������� �0: ";
    cin >> x0;
    do {
        x0 = x0 - f(x0) / df(x0);
    } while (fabs(f(x0)) > 0.001);

    cout << "����������� ������: " << x0 << endl;
    cout << "���������� ��������: " << count << endl << endl;



    //....................����� ����...........................

    cout << "����� ����" << endl;
    count = 0;
    double x_0, x_k, x_2 = 0;
    cout << "������� �0: ";
    cin >> x_0;
    cout << "������� �1: ";
    cin >> x_k;

    while (fabs(x_2 - x_k) > 0.001) {
        x_2 = fh(x_0, x_k);

        cout << x_2 << endl;
        x_k = x_2;
        count++;
    }
    cout << "����������� ������: " << x_2 << endl;
    cout << "���������� ��������: " << count << endl << endl;




    //......................����� ������� ��������....................
    cout << "����� ������� ��������" << endl;


    long double x_next = 0.1;
    count = 0;
    x_0 = 0;

    do {
        x_0 = x_next;
        x_next = mpi(x_0);
        count++;
    } while (fabs(x_next - x_0) > 0.001);

    cout << "����������� ������: " << x_next << endl;
    cout << "���������� ��������: " << count << endl;


    system("pause");
    return 0;

}

