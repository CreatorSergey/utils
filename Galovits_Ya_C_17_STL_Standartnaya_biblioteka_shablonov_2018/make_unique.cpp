#include <memory>
#include <iostream>

template <class T, class... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main()
{
    auto uptr = make_unique<int>(123);
    std::cout << *uptr << "\n";
}
