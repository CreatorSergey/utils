#include <type_traits>
#include <iostream>

class A {
public:
    void Run() {
    }
};

class B {

};

template<typename T, typename = void>
struct has_run: std::false_type {};

template<typename T>
struct has_run<T,
std::void_t<decltype(std::declval<T>().Run())>
>: std::true_type {};

template<typename T> 
void TestRun(const T&&) {
    static_assert(has_run<T>(),
                  "need method .Run() in class");
    std::cout << "Run found";
}

int main() {
    TestRun(A());
    TestRun(B());
    return 0;
}
