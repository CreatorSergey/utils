#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <set>

struct X
{
    int a = 0;
    std::string text;
};

std::ostream& operator<<(std::ostream& os, X const& arg)
{
    os << "a = " << arg.a << ", text = " << arg.text;
    return os;
}

template <typename T>
void print(T container)
{
    using item = typename std::decay_t<decltype(*begin(container))>;
    std::copy(begin(container), end(container), std::ostream_iterator<item>(std::cout, " "));
    std::cout << '\n';
}

int main()
{
    std::vector<int> v1 {1, 2, 3, 4};
    std::vector<std::string> v2 { "123", "2", "3", "4"};
    std::set<int> s1{ 5, 10, 20};
    std::vector<X> v3{{1, "test"}, {2, "zero"}};

    print(v1);
    print(v2);
    print(s1);
    print(v3);
    return 0;
}
