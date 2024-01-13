// Программа на C++ для поиска возможности
// записать число n как произведение ровно k
// положительные числа больше 1.
 
#include <iostream>

#include <vector>
using namespace std;

// Выводит k делителей n, если n можно записать
// как кратное k чисел. Остальное печатает: k коэффициентов невозможно .
 
void kFactors(int n, int k)
{
    // Вектор для хранения всех простых множителей числа n
    vector<int> P;

    // Вставляем все двойки в вектор
    while (n % 2 == 0)
    {
        P.push_back(2);
        n /= 2;
    }

    // n должно быть нечетным в этот момент
    // Таким образом, мы пропускаем один элемент (i = i + 2)
    for (int i = 3; i * i <= n; i = i + 2)
    {
        while (n % i == 0)
        {
            n = n / i;
            P.push_back(i);
        }
    }

    // Это необходимо для обработки, когда n > 2 и
    // n простое
    if (n > 2)
        P.push_back(n);


    // Если size(P) < k, k коэффициентов невозможно
    if (P.size() < k)
    {
        cout << "k коэффициентов невозможно" << endl;
        return;
    }


    // вывод первых k-1 факторов
    for (int i = 0; i < k - 1; i++)
        cout  << P[i] << ", ";
        
    // расчет и печать произведения остатка
    // чисел
    int product = 1;
    for (int i = k - 1; i < P.size(); i++)
        product = product * P[i];

    cout << product << endl;
}

// Программа для проверки вышеуказанной функции
int main()
{
    setlocale(LC_ALL, "Russian");
    int n, k;
    cout << "Введите N: ";
    cin >> n;

    cout << "Введите K: ";
    cin >> k;

    kFactors(n, k);
    return 0;
}
//#include <iostream>
//using namespace std;
//int main()
//{
//    int n, div = 2;
//    cout << "N = ";
//    cin >> n;
//    cout << n << " = 1";
//    while (n > 1)
//    {
//        while (n % div == 0)
//        {
//            cout << " * " << div;
//            n = n / div;
//        }
//        div++;
//    }
//    cin.get(); cin.get();
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//int main() {
//    long long numb, divisor = 2;
//    cin >> numb;
//    while (divisor * divisor <= numb)
//    {
//        if (numb % divisor == 0)
//        {
//            cout << divisor;
//            numb = numb / divisor;
//            cout << '*';
//        }
//        else if (divisor == 2) divisor = 3;
//        else divisor = divisor + 2;
//    }
//    cout << numb;
//    return 0;
//}
// C++ program to implement
// the above approach

//#include <iostream>
//
//#include <vector>
//using namespace std;
//
//// Function to find the total number of
//// ways to represent N as the sum of
//// integers over the range [1, K]
//int NumberOfways(int N, int K)
//{
//
//    // Initialize a list
//    vector<int> dp(N + 1, 0);
//
//    // Update dp[0] to 1
//    dp[0] = 1;
//
//    // Iterate over the range [1, K + 1]
//    for (int row = 1; row < K + 1; row++)
//    {
//
//        // Iterate over the range [1, N + 1]
//        for (int col = 1; col < N + 1; col++)
//        {
//
//            // If col is greater
//            // than or equal to row
//            if (col >= row)
//
//                // Update current
//                // dp[col] state
//                dp[col] = dp[col] + dp[col - row];
//        }
//    }
//
//    // Return the total number of ways
//    return(dp[N]);
//}
//
//// Driver Code
//int main()
//{
//    int N = 2;
//    int K = 2;
//
//    cout << (NumberOfways(N, K));
//}