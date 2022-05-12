#include <iostream>
#include <functional>
#include <string>
#include <iterator>
#include <algorithm>

// Создаем сложные предикаты с помощью логической конъюнкции

static bool begins_with_a(const std::string& s)
{
    return s.find("a") == 0;
}

static bool ends_with_b(const std::string& s)
{
    return s.rfind("b") == s.length() - 1;
}

template <typename A, typename B, typename F>
auto combine(F binary_func, A a, B b)
{
    return [=](auto param)
    {
        return binary_func(a(param), b(param));
    };
}

int main()
{
    auto a_xxx_b (combine(
        std::logical_and<>{}, begins_with_a, ends_with_b
    ));

    std::vector test = {"ab", "axxxb", "test", "a", "b", "aabb"};
    std::vector<std::string> out;

    std::copy_if(begin(test), end(test), std::back_inserter(out), a_xxx_b);

    for(const auto& item: out)
    {
        std::cout << item << ",";
    }
    std::cout << "\n";
}
