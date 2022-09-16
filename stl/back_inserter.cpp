#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>

int main() {

    // Карта с данными
    std::map<std::string, int> mapped;
    mapped["apple"] = 2;
    mapped["android"] = 3;

    // вектор для будущих данных
    using pair = std::pair<std::string, int>;
    std::vector<pair> vectorized;

    // Преобразование карты в вектор
    std::copy(mapped.begin(), mapped.end(), std::back_inserter(vectorized));

    // проверка
    assert(vectorized.size() == 2);

    // Вывод пары 
    for(const pair& x: vectorized) {
        std::cout << x.first << " " << x.second << "\n";
    }

    return 0;
}
