#include <iostream>
#include <cassert>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>

// Род Стивенс - Алгоритмы. Теория и практическое применение

// Нахождение простых множителей
std::vector<int> FindFactors(int number) {
    std::vector<int> factors;
    int i = 2;
    while(i < number) {
        while(number % i == 0) {
            factors.push_back(i);

            number = number / i;
        }
        i = i + 1;
    }
    if (number > 1)
        factors.push_back(number);

    return factors;
}

// Нахождение простых множителей (усовершенствованная версия)
// но работает не корректно
std::vector<int> FindFactors2(int number) {
    std::vector<int> factors;
    while(number % 2)
    {
        factors.push_back(2);
        number = number / 2;
    }

    int i = 3;
    int max_factor = sqrt(number);

    while(i <= max_factor) {
        while(number % i == 0) {
            factors.push_back(i);

            number = number / i;
            max_factor = sqrt(number);
        }
        i = i + 2;
    }
    if(number > 1)
        factors.push_back(number);

    return factors;
}


int main() {
    const auto items = FindFactors(999);
    assert(items.size() == 4);
    assert(items[0] == 3);
    assert(items[1] == 3);
    assert(items[2] == 3);
    assert(items[3] == 37);
    std::copy(begin(items), end(items), std::ostream_iterator<int>(std::cout, " "));
}
