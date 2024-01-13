
/////////////////////////////////////////////////////////////////////////////////////////
//Имеется N прямоугольных конвертов и N прямоугольных открыток различных размеров. 
//Можно ли разложить все открытки по конвертам, чтобы в каждом конверте было по одной открытке?
//Замечание. Открытки нельзя складывать, сгибать и т.п., но можно помещать в конверт под углом. 
//Например, открытка с размерами сторон 5:1 помещается в конверты с размерами 
//5:1, 6:3, 4.3:4.3, но не входит в конверты с размерами 4:1, 10:0.5, 4.2:4.2.

/////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>
#include <complex>
#include <functional>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
/////////////////////////////////////////////////////////////////////////////////////////
typedef double          T_real;
typedef std::string     T_str;
/////////////////////////////////////////////////////////////////////////////////////////
class  T_rectangle
{
    typedef std::pair<T_real, T_real>   T_rectangle_sizes;
    //-----------------------------------------------------------------------------------
    T_rectangle_sizes   sizes_;
    //-----------------------------------------------------------------------------------
public:
    //-----------------------------------------------------------------------------------
    T_rectangle
    (
        T_real  A,
        T_real  B
    )
        :
        sizes_
        (
            std::min(A, B),
            std::max(A, B)
        )
    {}
    //-----------------------------------------------------------------------------------
    T_real  A()                                                 const
    {
        return  sizes_.first;
    }
    //-----------------------------------------------------------------------------------
    T_real  B()                                                 const
    {
        return  sizes_.second;
    }
    //-----------------------------------------------------------------------------------
    //Меньший прямоугольник можно вложить в больший.
    bool  operator<= (T_rectangle  rectangle)                   const
    {
        return      A() <= rectangle.A()
            && (
                B() <= rectangle.B()
                || is_framed_in_with_incline(rectangle)
                );
    }
    //-----------------------------------------------------------------------------------
    //Для сортировки.
    bool  operator< (T_rectangle  rectangle)                    const
    {
        return  sizes_ < rectangle.sizes_;
    }
    //-----------------------------------------------------------------------------------
    void  print()                                               const
    {
        std::cout << std::complex<T_real>
            (
                sizes_.first,
                sizes_.second
                );
    }
    //-----------------------------------------------------------------------------------
private:
    //-----------------------------------------------------------------------------------
    bool  is_framed_in_with_incline(T_rectangle  rectangle)     const
    {
        T_real  a = A();
        T_real  b = B();
        T_real  A = rectangle.A();
        T_real  B = rectangle.B();

        T_real  alpha = asin
        (
            (A * b - a * sqrt(a * a + b * b - A * A))
            / (a * a + b * b)
        );

        return  B >= a * sin(alpha) + b * cos(alpha);
    }
};
/////////////////////////////////////////////////////////////////////////////////////////
typedef std::multiset   < T_rectangle   >   T_rectangles_multiset;
typedef std::vector     < T_rectangle   >   T_rectangles;


/////////////////////////////////////////////////////////////////////////////////////////
T_real  input_rect_size(const T_str  prompt)
{
    T_real  res;
    std::cout << std::endl;
    do
    {
        std::cout << '\t'
            << '\t'
            << prompt
            << '\t';

        std::cin >> res;
    } while (res < 0);

    return  res;
}
/////////////////////////////////////////////////////////////////////////////////////////
T_rectangle  input_rectangle()
{
    T_real  L = input_rect_size("длина:");
    T_real  W = input_rect_size("ширина:");

    return  T_rectangle(L, W);
}
/////////////////////////////////////////////////////////////////////////////////////////
void  input_rectangles
(
    T_rectangles_multiset& rectangles_multiset,
    int                     rectangles_total
)
{
    for (int i = 0; i < rectangles_total; ++i)
    {
        std::cout << std::endl
            << "\t#"
            << i + 1
            << ":\t";

        rectangles_multiset.insert(input_rectangle());
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
struct  T_cover_framed_card
{
    T_rectangle  card_;
    //-----------------------------------------------------------------------------------
    T_cover_framed_card(T_rectangle  card)
        :
        card_(card)
    {}
    //-----------------------------------------------------------------------------------
    bool  operator() (T_rectangle  cover)
    {
        return  card_ <= cover;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////
bool  insert_card
(
    T_rectangle             card,
    T_rectangles_multiset& covers,
    T_rectangles& covers_for_cards,
    size_t                  ind
)
{
    T_rectangles_multiset::iterator   find_cover_begin_it = covers.begin();
    if (ind < covers_for_cards.size())
    {
        covers.insert(covers_for_cards.back());
        find_cover_begin_it = covers.upper_bound(covers_for_cards.back());
        covers_for_cards.pop_back();
    }

    T_rectangles_multiset::iterator   cover_it
        = std::find_if
        (
            find_cover_begin_it,
            covers.end(),
            T_cover_framed_card(card)
        );

    bool  bool_res = cover_it != covers.end();
    if (bool_res)
    {
        covers_for_cards.push_back(*cover_it);
        covers.erase(cover_it);
    }
    return  bool_res;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool  insert_cards_in_covers
(
    const T_rectangles_multiset& cards,
    T_rectangles_multiset           covers,
    T_rectangles& covers_for_cards
)
{
    //Проходим по открыткам и вкладываем их в конверты.
    //Если для очередной открытки нет коверта, то перекладываем последнюю вложенную
    //открытку в следующий конверт и переходим к следующей.
    //Если же для открытки нет конверта, то выходим с сообщением о неудаче.
    for (T_rectangles_multiset::const_iterator card_it = cards.begin(); ; )
    {
        if (
            insert_card
            (
                *card_it,
                covers,
                covers_for_cards,
                std::distance
                (
                    cards.begin(),
                    card_it
                )
            )
            )
        {
            ++card_it;
            if (card_it == cards.end())
            {
                return  true;
            }
        }
        else
        {
            if (card_it == cards.begin())
            {
                return  false;
            }
            else
            {
                --card_it;
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    std::locale::global(std::locale(""));

    int  cards_total = 0;
    do
    {
        std::cout << "Введите количество открыток: ";
        std::cin >> cards_total;
    } while (cards_total <= 0);

    std::cout << std::endl
        << std::endl
        << "Введите размеры "
        << cards_total
        << " открыток:"
        << std::endl;

    T_rectangles_multiset  cards;
    input_rectangles
    (
        cards,
        cards_total
    );

    std::cout << std::endl
        << std::endl
        << "Введите размеры "
        << cards_total
        << " конвертов:"
        << std::endl;

    T_rectangles_multiset  covers;
    input_rectangles
    (
        covers,
        cards_total
    );

    T_rectangles  covers_for_cards;
    if (
        !insert_cards_in_covers
        (
            cards,
            covers,
            covers_for_cards
        )
        )
    {
        std::cout << std::endl
            << std::endl
            << "Заданные открытки невозможно разложить в заданные конверты."
            << std::endl;
    }
    else
    {
        const int     FIELD_WIDTH = 20;

        std::cout << std::endl
            << std::endl
            << "Открытки разложены по конвертам так:"
            << std::endl;

        std::cout << std::setw(FIELD_WIDTH)
            << "открытки"
            << "\t"
            << std::setw(FIELD_WIDTH)
            << "конверты"
            << std::endl;

        for (
            T_rectangles_multiset::iterator
            card_it = cards.begin();
            card_it != cards.end();
            ++card_it
            )
        {
            std::cout << std::setw(FIELD_WIDTH);
            card_it->print();
            std::cout << "\t";
            std::cout << std::setw(FIELD_WIDTH);

            covers_for_cards
                [
                    std::distance
                    (
                        cards.begin(),
                        card_it
                    )
                ]
            .print();

            std::cout << std::endl;
        }
    }
}
