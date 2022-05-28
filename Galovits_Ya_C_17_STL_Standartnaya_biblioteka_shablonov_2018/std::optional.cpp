// std::optional 
// с bool типом лучше не использовать
// с указателями лучше не использовать

#include <optional>
#include <string>
#include <iostream>
#include <complex>
#include <vector>

std::optional<std::string> findUserNick(bool nick_available) {

    if(nick_available)
        return { "test" };

    return std::nullopt;
}

struct Point {
    Point (int a, int b) : x(a), y(b) {}

    int x;
    int y;
};

int main()
{
    {
        auto nick = findUserNick(false);
        if(nick)
            std::cout << *nick << "\n";
    }

    {
        auto nick = findUserNick(true);
        if(nick)
            std::cout << *nick << "\n";
    }

    // пустой
    std::optional<int> empty;
    std::optional<float> float_empty = std::nullopt;

    // прямой
    std::optional<int> opt_int(10);
    std::optional opt_int_deduction(12);

    std::cout << *opt_int << "\n";
    std::cout << *empty << " " << (empty ? "true" : "false") << "\n";

    // make optinal
    auto double_opt = std::make_optional(3.0);
    auto complex = std::make_optional<std::complex<double>>(3.0, 4.0);
    std::cout << *complex << "\n";

    // in_place конструирование
    std::optional<std::complex<double>> o7{std::in_place, 3.0, 4.0};

    // вызов вектора с прямой инциализацией
    std::optional<std::vector<int>> oVec {std::in_place, {1, 2, 3}};

    // копирование / присванивание
    auto oIntCopy = opt_int;

    // создание из структуры
    std::optional<Point> opt_structure{std::in_place, 0, 1};

    // получение значения
    std::optional<int> opt_int_1 = 10;
    std::cout << "opt_int_1 = " << *opt_int_1 << "\n";

    // c помощью value()
    std::optional<std::string> ostr; //("hello");
    try
    {
        std::cout << "ostr= " << ostr.value() << "\n";
    } catch (const std::bad_optional_access& e)
    {
        std::cout << e.what() << "\n";
    }

    // с помощью value_or
    std::optional<double> odouble;
    std::cout << "odouble" << odouble.value_or(10.9) << "\n";

    // замена значения
    odouble.emplace(24.0);
    std::cout << "odouble" << odouble.value() << "\n";

    // очистка
    odouble.reset();


    return 0;
}
