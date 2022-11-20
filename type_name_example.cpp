#include <iostream>
#include <string>

int& foo_lref();
int&& foo_rref();
int foo_value();

// https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c

template<typename T>
std::string type_name()
{
    typedef typename std::remove_reference<T>::type TR;

    std::string r = typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";

    return r;
}

int main(){
    int i = 0;
    const int ci = 0;
    std::cout << "decltype(i) is " << type_name<decltype(i)>() << '\n';
    std::cout << "decltype((i)) is " << type_name<decltype((i))>() << '\n';
    std::cout << "decltype(ci) is " << type_name<decltype(ci)>() << '\n';
    std::cout << "decltype((ci)) is " << type_name<decltype((ci))>() << '\n';
    std::cout << "decltype(static_cast<int&>(i)) is " << type_name<decltype(static_cast<int&>(i))>() << '\n';
    std::cout << "decltype(static_cast<int&&>(i)) is " << type_name<decltype(static_cast<int&&>(i))>() << '\n';
    std::cout << "decltype(static_cast<int>(i)) is " << type_name<decltype(static_cast<int>(i))>() << '\n';
    std::cout << "decltype(foo_lref()) is " << type_name<decltype(foo_lref())>() << '\n';
    std::cout << "decltype(foo_rref()) is " << type_name<decltype(foo_rref())>() << '\n';
    std::cout << "decltype(foo_value()) is " << type_name<decltype(foo_value())>() << '\n';
}
