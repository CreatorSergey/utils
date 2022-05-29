// http://scrutator.me/post/2017/10/07/cpp17_lang_features_p2.aspx

#include <iostream>
#include <vector>

template <typename T>
void simpleExample(T val) {
    if constexpr(std::is_integral<T>::value)
        std::cout << "Integral passed: " << val;
    else
        std::cout << "Non integrall passed: " << val;

    std::cout << "\n";
}

template <typename T>
void mixStaticWithDynamicIncorrect(T val) {
    if constexpr(std::is_integral<T>::value)
        std::cout << "Integral passed: " << val;
    else if constexpr(std::is_same_v<T, std::string>)
    {
        if(val == std::string{"clone"})
            std::cout << "Known string passed.";
        else
            std::cout << "General string passed";
    }
    else 
        std::cout << "Unknown type varaiable passed";
    std::cout << "\n";
}

template <typename T>
void testStaticAssert(T val) {
    if constexpr(std::is_integral<T>::value)
        std::cout << "Integral passed.\n";
    else
        static_assert(std::is_integral<T>::value);
}

template <typename T> 
auto returnHeadache(T val) {
    if constexpr(std::is_same_v<T, std::string>)
        return 0;
    else
        return std::string{"str"};
}

int main()
{
    simpleExample(10);
    simpleExample("test");

    mixStaticWithDynamicIncorrect(1);
    mixStaticWithDynamicIncorrect(std::string{"clone"});
    mixStaticWithDynamicIncorrect(std::string{"text"});
    mixStaticWithDynamicIncorrect(std::vector{1, 2, 3});
 
    testStaticAssert(10);
    // testStaticAssert("test"); // assert

    std::cout << returnHeadache(std::string{"test"}) << "\n";
    std::cout << returnHeadache(19) << "\n";

    return 0;
}
