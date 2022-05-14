// Копируем элементы из одних контейнеров в другие
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <iterator>
#include <algorithm>

namespace std
{

std::ostream& operator<<(std::ostream& os, const std::pair<int, std::string>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";    
}

}

int main()
{
    std::vector<std::pair<int, std::string>> v {
        {1, "one"}, {2, "two"}, {3, "three"},
        {4, "four"}, {5, "five"}
    };

    std::map<int, std::string> m;

    std::copy_n(begin(v), 3, inserter(m, begin(m)));

    auto shell_it(std::ostream_iterator<std::pair<int, std::string>>{
        std::cout, ", "});

    std::copy(begin(m), end(m), shell_it);
    std::cout << "\n";

    m.clear();
    std::move(begin(v), end(v), inserter(m, begin(m)));

    std::copy(begin(m), end(m), shell_it);
    std::cout << "\n";

    std::copy(begin(v), end(v), shell_it);
    std::cout << "\n";
    
    return 0;
}
