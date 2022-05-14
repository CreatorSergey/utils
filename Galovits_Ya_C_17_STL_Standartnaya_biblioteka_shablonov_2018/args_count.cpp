#include <cstddef>
#include <iostream>

template<typename... Args>
struct args_count
{
    static const std::size_t value = sizeof...(Args);
};

int main()
{
    std::cout << args_count<int, int, int>::value << "\n";
}
