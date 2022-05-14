// Сортируем контейнеры
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <random>

static void print(const std::vector<auto>& v)
{
    using type = typename std::decay<decltype(*std::begin(v))>::type;
    std::copy(begin(v), end(v), std::ostream_iterator<type>{std::cout, ", "});
    std::cout << "\n";
}

int main()
{
    std::vector v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::random_device rd;
    std::mt19937 g {rd()};

    std::cout << std::is_sorted(begin(v), end(v)) << "\n";

    std::shuffle(begin(v), end(v), g);

    std::cout << std::is_sorted(begin(v), end(v)) << "\n";
    print(v);

    std::sort(begin(v), end(v));
    std::cout << std::is_sorted(begin(v), end(v)) << "\n";
    print(v);

    std::shuffle(begin(v), end(v), g);
    std::partition(begin(v), end(v), [](auto i)
    {
        return i % 2 == 0;
    });
    print(v);

    std::shuffle(begin(v), end(v), g);
    print(v);

    std::cout << "partial_sort:" << "\n";
    auto middle (std::next(begin(v), v.size() / 2));
    std::partial_sort(begin(v), middle, end(v));
    print(v);

    struct mystruct
    {
        int a;
        int b;
    };
    
    std::vector<mystruct> mv {
        {5, 100}, {1, 50}, {-123, 1000},
        {3, 70}, {-10, 20}
    };

    std::sort(begin(mv), end(mv), [](const auto& lhs, const auto& rhs){
        return lhs.b < rhs.b;
    });

    for(const auto& [a, b]: mv)
    {
        std::cout << "{" << a << ", " << b << "}";
    }
    std::cout << "\n";

}
