// transform_if

#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename InputIterator, typename OutputIterator,
 typename P, typename Transform>
OutputIterator transform_if(InputIterator first, InputIterator last,
 OutputIterator out,
 P predicate, Transform trans)
{
    for (; first != last; ++first) {
        if (predicate(*first)) {
            *out = trans(*first);
            ++out;
        }
    }
    return out;
}

int main()
{
    auto even ([](int i) { return i % 2 == 0; });
    auto twice ([](int i) { return i * 2; });

    std::vector items {1, 2, 3, 4, 5, 6, 7, 8};

    std::vector<int> out;

    transform_if(begin(items), end(items), std::back_inserter(out), even, twice);

    for(const auto item: out)
    {
        std::cout << item << ", ";
    }

    return 0;
}
