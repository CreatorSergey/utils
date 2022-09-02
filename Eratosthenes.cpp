#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <algorithm>

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
using Numbers = std::vector<int>;

/*
* Решето эратосфена
* @param max_number - максимально число для поиска
*/
Numbers Eratosthenes(int max_number) {
    // Определяем массив для чисел.
    std::vector<bool> is_composite(max_number);

    // Исключаем числа, кратные 2.
    for(int i = 4; i < max_number; i += 2)
        is_composite[i] = true;

    // Исключаем числа, кратные найденным простым числам.
    int next_prime = 3;
    int stop_at = sqrt(max_number);
    while(next_prime <= stop_at) {
        for(int i = next_prime * 2; i < max_number; i += next_prime) {
            is_composite[i] = true;
        }

        next_prime = next_prime + 2;
        while(next_prime <= max_number && is_composite[next_prime])
            next_prime = next_prime + 2;
    }

    Numbers primes;
    for(int i = 2; i < max_number; ++i) {
        if (is_composite[i] == false)
            primes.push_back(i);
    }

    return primes;
}

/*
* Запуск
*/
int main() {
    Numbers numbers = Eratosthenes(120);
    std::copy(begin(numbers), end(numbers), std::ostream_iterator<int>(std::cout, ","));
    Numbers success = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113};
    assert(numbers == success);
    return 0;
}
