#include <iostream>
#include <mutex>

int main()
{
    std::once_flag flag;
    std::call_once(flag,[&](){std::cout << "I'm called!\n";});
    std::call_once(flag,[&](){std::cout << "One more call!\n";});
    std::once_flag otherFlag;
    std::call_once(otherFlag,[&](){std::cout << "Another flag\n";});
    return 0;
}
