// Удаляем конкретные элементы из контейнеров

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void print(const std::vector<int>& v)
{
    std::copy(begin(v), end(v), std::ostream_iterator<int>{std::cout, ","});
    std::cout << "\n";
}

int main()
{
    std::vector<int> v {1, 2, 3, 4, 5, 6 };
    print(v);

    // удаление значений
    {
        const auto new_end(std::remove(begin(v), end(v), 2));
        v.erase(new_end, end(v));
    }
    print(v);

    // удаление нечетных чисел
    {
        // нечетное число
        auto odd_number([](int i) { return i % 2 != 0; });

        const auto new_end(
            std::remove_if(begin(v), end(v), odd_number)
        );
        v.erase(new_end, end(v));
        print(v);
    }

    // замена значений
    std::replace(begin(v), end(v), 4, 123);
    print(v);

    // Заполним ветор совершенно новыми значениями и создадим два новых путсых вектора
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2;
    std::vector<int> v3;
    std::vector<int> v4;
    std::vector<int> v5;

    {
        // нечетное число
        auto odd_number([](int i) {return i % 2 != 0; });
        // четное число
        auto even_number([](int i) { return i % 2 == 0; });

        // копирует все из исходного контейнера в другой при условии
        // что значение не соответсвует ограничению налагаемому предикатом
        // идет отрицание предиката
        std::remove_copy_if(begin(v), end(v), back_inserter(v2), odd_number);

        print(v2);

        // копирует все из исходного контейнера в другой при условии
        // что значение соответсвует ограничению из предиката
        std::copy_if(begin(v), end(v), back_inserter(v3), even_number);
        print(v3);

        std::remove_copy(begin(v), end(v), back_inserter(v4), 8);
        print(v4);


        std::replace_copy(begin(v), end(v), back_inserter(v5), 6, 12);
        print(v5);

               
    }

    return 0;
}
