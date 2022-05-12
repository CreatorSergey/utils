// transform_if

#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename InputIterator, typename T, typename F>
T accumulate(InputIterator first, InputIterator last, T init, F f)
{
    for (; first != last; ++first) {
        init = f(init, *first);
    }
    return init;
}


int main()
{
    auto even ([](int i) { return i % 2 == 0; });
    auto twice ([](int i) { return i * 2; });

    auto copy_and_advance ([twice, even](auto it, auto input) {
        if(even(input))
            *it = twice(input);
        return ++it;
    });

    std::vector items {1, 2, 3, 4, 5, 6, 7, 8};

    std::vector<int> out;

    ::accumulate(std::begin(items), std::end(items), std::back_inserter(out), copy_and_advance);

    for(const auto item: out)
    {
        std::cout << item << ", ";
    }

    return 0;
}
