// Реализуем функцию transform_if с применением std::accumulate и лямбда-выражений

#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename T>
auto map(T fn)
{
    return [=](auto reduce_fn){
        return[=](auto accum, auto input)
        {
            return reduce_fn(accum, fn(input));
        };
    };
}

template<typename T>
auto filter(T predicate)
{
    return [=](auto reduce_fn)
    {
        return [=] (auto accum, auto input)
        {
            if(predicate(input))
            {
                return reduce_fn(accum, input);
            }
            else
                return accum;
        };
    };
}

int main()
{
    auto even ([](int i) { return i % 2 == 0; });
    auto twice ([](int i) { return i * 2; });

    auto copy_and_advance([](auto it, auto input)
    {
        *it = input;
        return ++it;
    });

    std::vector items {1, 2, 3, 4, 5, 6, 7, 8};

    std::vector<int> out;

    std::accumulate(begin(items), end(items), std::back_inserter(out),
        filter(even)(
            map(twice)(
                copy_and_advance
            )
        ));

    for(const auto item: out)
    {
        std::cout << item << ", ";
    }

    return 0;
}
