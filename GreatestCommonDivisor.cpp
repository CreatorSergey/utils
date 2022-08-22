#include <iostream>
#include <cassert>

// наибольший общий делитель Евклида
int GreatestCommonDivisor(int a, int b) {
    while(b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int main() {
    const auto value = GreatestCommonDivisor(4851, 3003);
    assert(value == 231);
    std::cout << "value: " << value << "\n";
    return 0;
}
