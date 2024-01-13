#include <fstream>

#include <vector>

#include <algorithm>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int main() {

    int m, n, naim;
    vector<vector<int>> a(100, vector<int>(100, 0)); // сюда грузим табличку
    vector<vector<int>> b(100, vector<int>(100, 0)); // здесь сохраняем результат
    vector <int> x;
    vector <int> y;
    vector<int> t(100, 0);
    naim = 10000;
    in >> n >> m;
    for (int i = 0; i < n; i++)

        for (int j = 0; j < m; j++) {

            in >> a[i][j];          // грузим исходную табличку

            if (a[i][j] == 1) {

                x.push_back(i);     // запоминаем координаты единиц
                y.push_back(j);

            }

        }

    // заполняем таблицу результатов

    for (int i = 0; i < n; i++)

        for (int j = 0; j < m; j++) {

            naim = 10000;

            for (int z = 0; z < x.size(); z++) {

                int tc = abs(i - x[z]) + abs(j - y[z]);

                naim = min(naim, tc);

            }

            b[i][j] = naim;

        }
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) out << b[i][j] << ' ';

        out << endl;

    }
    return 0;
}
