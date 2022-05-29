// std::any

#include <any>
#include <iostream>
#include <map>
#include <cassert>
#include <vector>

int main() {

    // создание
    std::any a(12);

    // чтение
    std::cout << std::any_cast<int>(a) << "\n";

    // перезапись
    a = std::string("Hello!");

    // ошибка кастования
    try
    {
        std::cout << std::any_cast<int>(a) << "\n";
    }
    catch(const std::bad_any_cast& e)
    {
        std::cout << e.what() << "\n";
    }

    // сброс
    a.reset();

    // проверка на пустоту
    if(!a.has_value())
        std::cout << "a is empty!" << "\n";


    // any в контейнере
    std::map<std::string, std::any> m;
    m["integer"] = 10;
    m["string"] = std::string("Hello!");
    m["float"] = 1.0f;

    for(auto& [key, val]: m)
    {
        if(val.type() == typeid(int))
            std::cout << "int: " << std::any_cast<int>(val) << "\n";
        else if(val.type() == typeid(std::string))
        {
            std::cout << "string: " << std::any_cast<std::string>(val) << "\n";
        }
        else if (val.type() == typeid(float))
        {
            std::cout << "float: " << std::any_cast<float>(val) << "\n";
        }
    }

    // стандартная инициализация
    std::any b;
    assert(!b.has_value());

    struct MyType
    {
        int a;
        int b;

        void Print() {
            std::cout << a << ", " << b << "\n";
        }
    };

    // прямая инициализация значением
    std::any a2(10); // int;
    std::any a3(MyType(10, 11));

    // in place конструктор
    std::any a4(std::in_place_type<MyType>, 10, 11);
    std::any a5{std::in_place_type<std::string>, "Hello World"};

    // make_any
    std::any a6 = std::make_any<std::string>("Hello World");

    // изменение значения
    a = MyType(19, 23);
    a.emplace<float>(100.5f);
    a.emplace<std::vector<int>>({10, 11, 12, 13});

    // получение доступа к значению
    std::any var = std::make_any<MyType>(10, 10);
    try {
        std::any_cast<MyType&>(var).Print();
        std::any_cast<MyType&>(var).a = 11;
        std::any_cast<MyType&>(var).Print();
        std::any_cast<int>(var); // throw
    }
    catch (const std::bad_any_cast& e)
    {
        std::cout << e.what() << "\n";
    }

    // получение указателя, вернет nullptr, если каст не удался
    int* p = std::any_cast<int>(&var);
    std::cout << (p ? "constains int.. \n" : "doesnt contains an int...\n");

    MyType* pt = std::any_cast<MyType>(&var);
    if(pt)
    {
        pt->a = 12;
        std::any_cast<MyType&>(var).Print();
    }

    return 0;
}
