// std::invoke
#include <functional>
#include <iostream>

template<typename F, typename V1, typename V2>
void foo(F f, V1 v1, V2 v2)
{
    std::invoke(f, v1, v2);
}

void bar(int v1, int v2)
{
    std::cout << v1 << " " << v2 << "\n";
}

class Bar {
private:
    int m_v;

public:
    explicit Bar(int v) : m_v{v} {}
    void bar(int v2)
    {
        std::cout << m_v << " " << v2 << "\n";
    }

    static void test(int v1, int v2)
    {
        std::cout << "call static: " << v1 << " " << v2 << "\n";
    }
};

int main() {

    int v1{12};
    int v2{23};

    // вызов метода с аргументами
    foo(&bar, v1, v2);


    // вызов нестатического метода класса по ссылке
    Bar b{42};
    foo(&Bar::bar, b, v2);

    // вызов нестатического метода класса по указателю
    foo(&Bar::bar, &b, v2);

    // вызов статического метода
    foo(&Bar::test, v1, v2);

    return 0;
}
