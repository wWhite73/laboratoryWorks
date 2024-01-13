#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class laba
{
public:
    vector<int> a;

    friend ostream& operator<<(ostream& out, laba p);

    friend void two_way_merge();
};

ostream& operator<<(ostream& out, laba p)
{

    int o = p.a.size();

    for (int i = 0; i < o;)
    {
        cout << p.a[i] << ".";

        i += 1;
    }

    return out;

};

void two_way_merge()
{
    cout << "Введите количество элементов ->";
    int d = 0;
    cin >> d;

    int X, Y;
    int sum = 0, a = 0, b = 1, sum1 = 0;
    for (int i = 0; b <= d;)
    {
        X = b;
        Y = a;

        sum = a + b;
        sum1 += sum;
        a = b;
        b = sum;

        i += 1;
    }

    vector<laba> F1;
    vector<laba> F2;
    vector<laba> F3;

    int pika = 0;

    if (d < b)
    {
        pika = b - d;
    }

    cout << "Первый вектор" << endl;
    for (int i = 0; i < X;)
    {
        laba g;

        if (i < pika)
        {
            F1.push_back(g);
        }
        else
        {
            g.a.push_back(round(rand() % 1000));
            F1.push_back(g);
        }

        cout << F1[i] << "||";

        i += 1;

    }
    /*for (int i = 0; i < 8;)
    {
        laba g;


        if (i == 0 || i == 1)
        {

            F1.push_back(g);
        }
        else
        {
            if (i == 2)
            {
                g.a.push_back(31);
                F1.push_back(g);
            }
            if (i == 3)
            {
                g.a.push_back(72);
                F1.push_back(g);
            }
            if (i == 4)
            {
                g.a.push_back(19);
                F1.push_back(g);
            }
            if (i == 5)
            {
                g.a.push_back(45);
                F1.push_back(g);
            }
            if (i == 6)
            {
                g.a.push_back(44);
                F1.push_back(g);
            }
            if (i == 7)
            {
                g.a.push_back(40);
                F1.push_back(g);
            }
        }

        cout << F1[i] << "||";

        i += 1;
    }
    cout << endl;*/

    cout << endl;

    cout << "Второй вектор" << endl;
    for (int i = 0; i < Y;)
    {
        laba g;

        g.a.push_back(round(rand() % 1000));
        F2.push_back(g);

        cout << F2[i] << "||";

        i += 1;

    }
    /*for (int i = 0; i < 5;)
    {
        laba g;

        if (i == 0)
        {
            g.a.push_back(8);
            F2.push_back(g);
        }
        if (i == 1)
        {
            g.a.push_back(57);
            F2.push_back(g);
        }
        if (i == 2)
        {
            g.a.push_back(77);
            F2.push_back(g);
        }
        if (i == 3)
        {
            g.a.push_back(63);
            F2.push_back(g);
        }
        if (i == 4)
        {
            g.a.push_back(13);
            F2.push_back(g);
        }

        cout << F2[i] << "||";

        i += 1;
    }*/

    cout << endl;

    bool pr3 = true;

    while (pr3 == true)
    {
        if (F1.empty())
        {
            int i = 0;

            while (!F3.empty() && !F2.empty())
            {

                if ((F3[0].a.size() == 1 && F2[0].a.size() == 1) || (F3[0].a.empty() && !F2[0].a.empty()) || (!F3[0].a.empty() && F2[0].a.empty()))
                {
                    if (F3[0].a[0] > F2[0].a[0])
                    {
                        F1.push_back(F2[0]);

                        F2.erase(F2.begin());

                        F1.push_back(F3[0]);

                        F3.erase(F3.begin());

                    }
                    else
                    {
                        F1.push_back(F3[0]);

                        F3.erase(F3.begin());

                        F1.push_back(F2[0]);

                        F2.erase(F2.begin());
                    }
                }

                if (F2[0].a.size() > 1 || F3[0].a.size() > 1)
                {
                    laba g;

                    F1.push_back(g);

                    int sizeF2 = F2[0].a.size();
                    int sizeF3 = F3[0].a.size();
                    int min = F2[0].a[0];
                    int winner = 0;

                    if (sizeF2 > sizeF3)
                    {
                        while (!F3[0].a.empty())
                        {
                            min = F2[0].a[0];

                            if (min > F3[0].a[0])
                            {

                                F1[i].a.push_back(F3[0].a[0]);

                                F3[0].a.erase(F3[0].a.begin());

                                if (F3[0].a.empty())
                                {
                                    F3.erase(F3.begin());

                                    while (!F2[0].a.empty())
                                    {
                                        F1[i].a.push_back(F2[0].a[0]);

                                        F2[0].a.erase(F2[0].a.begin());

                                    }

                                    F2.erase(F2.begin());


                                    break;

                                }

                                if (F2.empty() || F3.empty())
                                {
                                    break;
                                }

                            }
                            else
                            {

                                F1[i].a.push_back(min);

                                F2[0].a.erase(F2[0].a.begin());

                                if (F2[0].a.empty())
                                {
                                    F2.erase(F2.begin());

                                    while (!F3[0].a.empty())
                                    {
                                        F1[i].a.push_back(F3[0].a[0]);

                                        F3[0].a.erase(F3[0].a.begin());

                                    }

                                    F3.erase(F3.begin());

                                    break;

                                }

                                if (F2.empty() || F3.empty())
                                {
                                    break;
                                }

                            }

                        }

                        //if (F2.empty())
                        //{
                        //    sizeF3 = F3[0].a.size();

                        //    for (int i1 = 0; i1 < sizeF3;)
                        //    {

                        //        F1[i].a.push_back(F3[0].a[0]);

                        //        F3[0].a.erase(F3[0].a.begin());

                        //        i1 += 1;
                        //    }

                        //    F3.erase(F3.begin());

                        //    /*if (F2.empty() || F3.empty())
                        //    {
                        //        break;
                        //    }*/

                        //}

                        //if (F3.empty())
                        //{
                        //    sizeF2 = F2[0].a.size();

                        //    for (int i1 = 0; i1 < sizeF2;)
                        //    {

                        //        F1[i].a.push_back(F2[0].a[0]);

                        //        F2[0].a.erase(F2[0].a.begin());

                        //        i1 += 1;
                        //    }

                        //    F2.erase(F2.begin());

                        //    /*if (F2.empty() || F3.empty())
                        //    {
                        //        break;
                        //    }*/

                        //}

                    }
                    else
                    {
                        while (!F2[0].a.empty())
                        {
                            min = F3[0].a[0];

                            if (min > F2[0].a[0])
                            {
                                F1[i].a.push_back(F2[0].a[0]);

                                F2[0].a.erase(F2[0].a.begin());

                                if (F2[0].a.empty())
                                {
                                    while (!F3[0].a.empty())
                                    {
                                        F1[i].a.push_back(F3[0].a[0]);

                                        F3[0].a.erase(F3[0].a.begin());

                                    }

                                    F3.erase(F3.begin());

                                    F2.erase(F2.begin());

                                    break;

                                }

                                if (F2.empty() || F3.empty())
                                {
                                    break;
                                }

                            }
                            else
                            {
                                F1[i].a.push_back(min);

                                F3[0].a.erase(F3[0].a.begin());

                                if (F3[0].a.empty())
                                {
                                    F3.erase(F3.begin());

                                    while (!F2[0].a.empty())
                                    {
                                        F1[i].a.push_back(F2[0].a[0]);

                                        F2[0].a.erase(F2[0].a.begin());

                                    }

                                    F2.erase(F2.begin());

                                    break;

                                }

                                if (F2.empty() || F3.empty())
                                {
                                    break;
                                }

                            }

                        }

                        //if (F2.empty())
                        //{
                        //    sizeF3 = F3[0].a.size();

                        //    for (int i1 = 0; i1 < sizeF3;)
                        //    {

                        //        F1[i].a.push_back(F3[0].a[0]);

                        //        F3[0].a.erase(F3[0].a.begin());

                        //        i1 += 1;
                        //    }

                        //    F3.erase(F3.begin());

                        //}

                        //if (F3.empty())
                        //{
                        //    sizeF2 = F2[0].a.size();

                        //    for (int i1 = 0; i1 < sizeF2;)
                        //    {

                        //        F1[i].a.push_back(F2[0].a[0]);

                        //        F2[0].a.erase(F2[0].a.begin());

                        //        i1 += 1;
                        //    }

                        //    F2.erase(F2.begin());

                        //   /* if (F2.empty() || F3.empty())
                        //    {
                        //        break;
                        //    }*/

                        //}

                    }

                }

                cout << "-------------------------------" << endl;
                cout << "F with iter ->" << i << endl;

                if (!F1.empty())
                {
                    cout << endl;

                    cout << "F1 : ->";

                    int l = F1.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F1[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                if (!F2.empty())
                {
                    cout << endl;

                    cout << "F2 : ->";

                    int l = F2.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F2[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                if (!F3.empty())
                {
                    cout << endl;

                    cout << "F3 : ->";

                    int l = F3.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F3[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                cout << "-------------------------------" << endl;

                i += 1;

            }
        }

        if (F2.empty())
        {
            int i = 0;

            while (!F1.empty() && !F3.empty())
            {
                int opi = F1.size();
                int opi1 = F3.size();

                if ((F1[0].a.size() == 1 && F3[0].a.size() == 1) || (F1[0].a.empty() && !F3[0].a.empty()) || (!F1[0].a.empty() && F3[0].a.empty()))
                {
                    if (F1[0].a.size() == 1 && F3[0].a.size() == 1)
                    {

                        if (F1[0].a[0] > F3[0].a[0])
                        {
                            F2.push_back(F3[0]);

                            F3.erase(F3.begin());

                            F2[i].a.push_back(F1[0].a[0]);

                            F1.erase(F1.begin());

                        }
                        else
                        {
                            F2.push_back(F1[0]);

                            F1.erase(F1.begin());

                            F2[i].a.push_back(F3[0].a[0]);

                            F3.erase(F3.begin());
                        }

                        if (F1.empty() || F3.empty())
                        {
                            break;
                        }
                    }

                    if (F1[0].a.empty() && !F3[0].a.empty())
                    {
                        F2.push_back(F3[0]);

                        F3.erase(F3.begin());

                        F1.erase(F1.begin());

                        if (F1.empty() || F3.empty())
                        {
                            break;
                        }
                    }

                    if (!F1[0].a.empty() && F3[0].a.empty())
                    {
                        F2.push_back(F1[0]);

                        F1.erase(F1.begin());

                        F3.erase(F3.begin());

                        if (F1.empty() || F3.empty())
                        {
                            break;
                        }
                    }

                }
                else
                    if (F1[0].a.size() > 1 || F3[0].a.size() > 1)
                    {
                        laba g;

                        F2.push_back(g);

                        int sizeF1 = F1[0].a.size();
                        int sizeF3 = F3[0].a.size();
                        int min = F1[0].a[0];
                        int winner = 0;

                        if (sizeF1 > sizeF3)
                        {
                            while (!F3[0].a.empty())
                            {
                                min = F1[0].a[0];

                                if (min > F3[0].a[0])
                                {

                                    F2[i].a.push_back(F3[0].a[0]);

                                    F3[0].a.erase(F3[0].a.begin());

                                    if (F3[0].a.empty())
                                    {
                                        F3.erase(F3.begin());

                                        while (!F1[0].a.empty())
                                        {
                                            F2[i].a.push_back(F1[0].a[0]);

                                            F1[0].a.erase(F1[0].a.begin());

                                        }

                                        F1.erase(F1.begin());

                                        break;

                                    }

                                    if (F1.empty() || F3.empty())
                                    {
                                        break;
                                    }

                                }
                                else
                                {

                                    F2[i].a.push_back(min);

                                    F1[0].a.erase(F1[0].a.begin());

                                    if (F1[0].a.empty())
                                    {
                                        F1.erase(F1.begin());

                                        while (!F3[0].a.empty())
                                        {
                                            F2[i].a.push_back(F3[0].a[0]);

                                            F3[0].a.erase(F3[0].a.begin());

                                        }

                                        F3.erase(F3.begin());

                                        break;

                                    }

                                    if (F1.empty() || F3.empty())
                                    {
                                        break;
                                    }

                                }

                            }

                            //if (F1.empty())
                            //{
                            //    sizeF3 = F3[0].a.size();

                            //    for (int i1 = 0; i1 < sizeF3;)
                            //    {

                            //        F2[i].a.push_back(F3[0].a[0]);

                            //        F3[0].a.erase(F3[0].a.begin());

                            //        i1 += 1;
                            //    }

                            //    F3.erase(F3.begin());

                            //   /* if (F1.empty() || F3.empty())
                            //    {
                            //        break;
                            //    }*/

                            //}

                            //if (F3.empty())
                            //{
                            //    sizeF1 = F1[0].a.size();

                            //    for (int i1 = 0; i1 < sizeF1;)
                            //    {

                            //        F2[i].a.push_back(F1[0].a[0]);

                            //        F1[0].a.erase(F1[0].a.begin());

                            //        i1 += 1;
                            //    }

                            //    F1.erase(F1.begin());

                            //    /*if (F1.empty() || F3.empty())
                            //    {
                            //        break;
                            //    }*/

                            //}

                        }
                        else
                        {
                            while (!F1[0].a.empty())
                            {
                                min = F3[0].a[0];

                                if (min > F1[0].a[0])
                                {

                                    F2[i].a.push_back(F1[0].a[0]);

                                    F1[0].a.erase(F1[0].a.begin());

                                    if (F1[0].a.empty())
                                    {
                                        F1.erase(F1.begin());

                                        while (!F3[0].a.empty())
                                        {
                                            F2[i].a.push_back(F3[0].a[0]);

                                            F3[0].a.erase(F3[0].a.begin());

                                        }

                                        F3.erase(F3.begin());

                                        break;

                                    }

                                    if (F1.empty() || F3.empty())
                                    {
                                        break;
                                    }

                                }
                                else
                                {

                                    F2[i].a.push_back(min);

                                    F3[0].a.erase(F3[0].a.begin());

                                    if (F3[0].a.empty())
                                    {
                                        F3.erase(F3.begin());

                                        while (!F1[0].a.empty())
                                        {
                                            F2[i].a.push_back(F1[0].a[0]);

                                            F1[0].a.erase(F1[0].a.begin());

                                        }

                                        F1.erase(F1.begin());

                                        break;

                                    }

                                    if (F1.empty() || F3.empty())
                                    {
                                        break;
                                    }

                                }

                            }

                            //if (F1.empty())
                            //{
                            //    sizeF3 = F3[0].a.size();

                            //    for (int i1 = 0; i1 < sizeF3;)
                            //    {

                            //        F2[i].a.push_back(F3[0].a[0]);

                            //        F3[0].a.erase(F3[0].a.begin());

                            //        i1 += 1;
                            //    }

                            //    F3.erase(F3.begin());

                            //    /*if (F1.empty() || F3.empty())
                            //    {
                            //        break;
                            //    }*/

                            //}

                            //if (F3.empty())
                            //{
                            //    sizeF1 = F1[0].a.size();

                            //    for (int i1 = 0; i1 < sizeF1;)
                            //    {

                            //        F2[i].a.push_back(F1[0].a[0]);

                            //        F1[0].a.erase(F1[0].a.begin());

                            //        i1 += 1;
                            //    }

                            //    F1.erase(F1.begin());

                            //   /* if (F1.empty() || F3.empty())
                            //    {
                            //        break;
                            //    }*/

                            //}

                        }

                    }

                cout << "-------------------------------" << endl;
                cout << "F with iter ->" << i << endl;

                if (!F1.empty())
                {
                    cout << endl;

                    cout << "F1 : ->";

                    int l = F1.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F1[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                if (!F2.empty())
                {
                    cout << endl;

                    cout << "F2 : ->";

                    int l = F2.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F2[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                if (!F3.empty())
                {
                    cout << endl;

                    cout << "F3 : ->";

                    int l = F3.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F3[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                cout << "-------------------------------" << endl;

                i += 1;

            }
        }

        if (F3.empty())
        {
            int i = 0;

            while (!F1.empty() && !F2.empty())
            {


                if ((F1[0].a.size() == 1 && F2[0].a.size() == 1) || (F1[0].a.empty() && !F2[0].a.empty()) || (!F1[0].a.empty() && F2[0].a.empty()))
                {
                    if (F1[0].a.size() == 1 && F2[0].a.size() == 1)
                    {
                        if (F1[0].a[0] > F2[0].a[0])
                        {
                            F3.push_back(F2[0]);

                            F2.erase(F2.begin());

                            F3[i].a.push_back(F1[0].a[0]);

                            F1.erase(F1.begin());

                        }
                        else
                        {
                            F3.push_back(F1[0]);

                            F1.erase(F1.begin());

                            F3[i].a.push_back(F2[0].a[0]);

                            F2.erase(F2.begin());
                        }

                        if (F1.empty() || F2.empty())
                        {
                            break;
                        }

                    }

                    if (F1[0].a.empty() && !F2[0].a.empty())
                    {
                        F3.push_back(F2[0]);

                        F2.erase(F2.begin());

                        F1.erase(F1.begin());

                        if (F1.empty() || F2.empty())
                        {
                            break;
                        }

                    }

                    if (!F1[0].a.empty() && F2[0].a.empty())
                    {
                        F3.push_back(F1[0]);

                        F1.erase(F1.begin());

                        F2.erase(F2.begin());

                        if (F1.empty() || F2.empty())
                        {
                            break;
                        }

                    }

                }

                if (F1[0].a.size() > 1 || F2[0].a.size() > 1)
                {
                    laba g;

                    F3.push_back(g);

                    int sizeF1 = F1[0].a.size();
                    int sizeF2 = F2[0].a.size();
                    int min = F1[0].a[0];
                    int winner = 0;

                    if (sizeF2 > sizeF1)
                    {
                        while (!F1[0].a.empty())
                        {
                            min = F1[0].a[0];

                            if (min > F1[0].a[0])
                            {

                                F3[i].a.push_back(F1[0].a[0]);

                                F1[0].a.erase(F1[0].a.begin());

                                if (F1[0].a.empty())
                                {
                                    F1.erase(F1.begin());

                                    while (!F2[0].a.empty())
                                    {
                                        F3[i].a.push_back(F2[0].a[0]);

                                        F2[0].a.erase(F2[0].a.begin());

                                    }

                                    F2.erase(F2.begin());

                                    break;
                                }

                                if (F2.empty() || F1.empty())
                                {
                                    break;
                                }

                            }
                            else
                            {

                                F3[i].a.push_back(min);

                                F2[0].a.erase(F2[0].a.begin());

                                if (F2[0].a.empty())
                                {
                                    F2.erase(F2.begin());

                                    while (!F1[0].a.empty())
                                    {
                                        F3[i].a.push_back(F1[0].a[0]);

                                        F1[0].a.erase(F1[0].a.begin());

                                    }

                                    F1.erase(F1.begin());

                                    break;
                                }

                                if (F2.empty() || F1.empty())
                                {
                                    break;
                                }

                            }

                        }

                        //if (F2.empty())
                        //{
                        //    sizeF1 = F1[0].a.size();

                        //    for (int i1 = 0; i1 < sizeF1;)
                        //    {

                        //        F3[i].a.push_back(F1[0].a[0]);

                        //        F1[0].a.erase(F1[0].a.begin());

                        //        i1 += 1;
                        //    }

                        //    F1.erase(F1.begin());

                        //    /*if (F2.empty() || F1.empty())
                        //    {
                        //        break;
                        //    }*/

                        //}

                        //if (F1.empty())
                        //{
                        //    sizeF2 = F2[0].a.size();

                        //    for (int i1 = 0; i1 < sizeF2;)
                        //    {

                        //        F3[i].a.push_back(F2[0].a[0]);

                        //        F2[0].a.erase(F2[0].a.begin());

                        //        i1 += 1;
                        //    }

                        //    F2.erase(F2.begin());

                        //    /*if (F2.empty() || F1.empty())
                        //    {
                        //        break;
                        //    }*/

                        //}

                    }
                    else
                    {
                        while (!F2[0].a.empty())
                        {
                            min = F1[0].a[0];

                            if (min > F2[0].a[0])
                            {

                                F3[i].a.push_back(F2[0].a[0]);

                                F2[0].a.erase(F2[0].a.begin());

                                if (F2[0].a.empty())
                                {
                                    F2.erase(F2.begin());

                                    while (!F1[0].a.empty())
                                    {
                                        F3[i].a.push_back(F1[0].a[0]);

                                        F1[0].a.erase(F1[0].a.begin());

                                    }

                                    F1.erase(F1.begin());

                                    break;

                                }

                                if (F2.empty() || F1.empty())
                                {
                                    break;
                                }

                            }
                            else
                            {

                                F3[i].a.push_back(min);

                                F1[0].a.erase(F1[0].a.begin());

                                if (F1[0].a.empty())
                                {
                                    F1.erase(F1.begin());

                                    while (!F2[0].a.empty())
                                    {
                                        F3[i].a.push_back(F2[0].a[0]);

                                        F2[0].a.erase(F2[0].a.begin());

                                    }

                                    F2.erase(F2.begin());

                                    break;
                                }

                                if (F2.empty() || F1.empty())
                                {
                                    break;
                                }

                            }

                        }

                        //if (F2.empty())
                        //{
                        //    sizeF1 = F1[0].a.size();

                        //    for (int i1 = 0; i1 < sizeF1;)
                        //    {

                        //        F3[i].a.push_back(F1[0].a[0]);

                        //        F1[0].a.erase(F1[0].a.begin());

                        //        i1 += 1;
                        //    }

                        //    F1.erase(F1.begin());

                        //   /* if (F2.empty() || F1.empty())
                        //    {
                        //        break;
                        //    }*/

                        //}

                        //if (F1.empty())
                        //{
                        //    sizeF2 = F2[0].a.size();

                        //    for (int i1 = 0; i1 < sizeF2;)
                        //    {

                        //        F3[i].a.push_back(F2[0].a[0]);

                        //        F2[0].a.erase(F2[0].a.begin());

                        //        i1 += 1;
                        //    }

                        //    F2.erase(F2.begin());

                        //    /*if (F2.empty() || F1.empty())
                        //    {
                        //        break;
                        //    }*/

                        //}

                    }

                }

                cout << "-------------------------------" << endl;
                cout << "F with iter ->" << i << endl;

                if (!F1.empty())
                {
                    cout << endl;

                    cout << "F1 : ->";

                    int l = F1.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F1[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                if (!F2.empty())
                {
                    cout << endl;

                    cout << "F2 : ->";

                    int l = F2.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F2[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                if (!F3.empty())
                {
                    cout << endl;

                    cout << "F3 : ->";

                    int l = F3.size();

                    for (int i = 0; i < l;)
                    {
                        cout << F3[i] << "|";

                        i += 1;
                    }

                    cout << endl;

                }

                cout << "-------------------------------" << endl;

                i += 1;

            }

        }

        if (!F1.empty())
        {
            cout << endl;

            cout << "F1 : ->";

            int l = F1.size();

            for (int i = 0; i < l;)
            {
                cout << F1[i] << "|";

                i += 1;
            }

            cout << endl;

        }

        if (!F2.empty())
        {
            cout << endl;

            cout << "F2 : ->";

            int l = F2.size();

            for (int i = 0; i < l;)
            {
                cout << F2[i] << "|";

                i += 1;
            }

            cout << endl;

        }

        if (!F3.empty())
        {
            cout << endl;

            cout << "F3 : ->";

            int l = F3.size();

            for (int i = 0; i < l;)
            {
                cout << F3[i] << "|";

                i += 1;
            }

            cout << endl;

        }


        bool pr = F1.empty();
        bool pr1 = F2.empty();
        bool pr2 = F3.empty();

        if (pr == false && pr1 == true && pr2 == true)
        {
            pr3 = false;

            int l = F1.size();

            cout << "Конечный массив" << endl;

            for (int i = 0; i < l;)
            {
                cout << F1[i] << "|";

                i += 1;
            }

        }

        if (pr1 == false && pr == true && pr2 == true)
        {
            pr3 = false;

            int l = F2.size();

            cout << "Конечный массив" << endl;

            for (int i = 0; i < l;)
            {
                cout << F2[i] << "|";

                i += 1;
            }

        }

        if (pr2 == false && pr1 == true && pr == true)
        {
            pr3 = false;

            int l = F3.size();

            cout << "Конечный массив" << endl;

            for (int i = 0; i < l;)
            {
                cout << F3[i] << "|";

                i += 1;
            }

        }

    }

    cout << endl;
    cout << endl;

    int time = clock();

    cout << "Время работы многофазной сортировки =" << time << endl;

}

int main()
{
    setlocale(LC_ALL, "russian");

    two_way_merge();

}