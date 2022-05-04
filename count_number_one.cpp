#include <iostream>

// Посчитайте количество единиц в произвольном числе
size_t count_number_one(size_t number)
{
    if(number == 1)
        return 1;

    if(number == 0)
        return 0;

    size_t count = 0;
    while(number)
    {
        // std::cout << number << " % 10 = " << number % 10 << "\n";
        if(number % 10 == 1)
            count++;

        number /= 10;
    }

    return count;
}

int main()
{
    std::cout << count_number_one(0) << "\n"; // 0
    std::cout << count_number_one(1) << "\n"; // 1
    std::cout << count_number_one(15) << "\n"; // 1
    std::cout << count_number_one(1215) << "\n"; // 2
    std::cout << count_number_one(111111) << "\n"; // 6
    return 0;
}
