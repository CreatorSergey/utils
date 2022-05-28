// string_view
// выстрелы в ногу (shoot yourself in the foot)
// 1. string_view могут указывать на строки, которые не заканчиваются нулем (аккуратней с методом data)
// 2. string_view могут провиснуть и указывать на освобожденную строку
// 3. не вовзращать из функции, когда string_view указывает на временную строку

#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <cctype>

std::string trim_whitespace_surrounding(const std::string& s) {
    const char items[] {" \t\n"};
    const std::size_t first (s.find_first_not_of(items)); // ищем первый символ не похожий ни на один из списка
    if (std::string::npos == first) { return {}; }
    const std::size_t last (s.find_last_not_of(items)); // последний не похожий на символ из списка
    
    // метод принимает начало и кол-во символов (поэтому вычисляем)
    return s.substr(first, (last - first + 1));
}

void print(std::string_view v) {

    // ищем индекс первлшл символа не из списка
    const auto words_begin (v.find_first_not_of(" \t\n"));

    // выбираем меньшее - размер строки или индекс (если в строке одни пробелы, то вернется -1)
    v.remove_prefix(std::min(words_begin, v.size()));

    const auto words_end(v.find_last_not_of(" \t\n"));
    if (words_end != std::string_view::npos) {
        v.remove_suffix(v.size() - words_end - 1);
    }

    std::cout << "length: " << v.length() << " [" << v << "]\n";

}

int main(int argc, char* argv[]) {
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    // создание
    std::string a {"a"};
    auto b {"b"s};

    std::string_view c {"c"};
    auto d {"d"sv};

    // вывод
    std::cout << a << ", " << b << "\n";
    std::cout << c << ", " << d << "\n";

    // конкатенация
    std::cout << a + b << "\n";
    std::cout << a + std::string{c} << "\n";

    std::string x{"test"};
    x.append(c);
    std::cout << x << "\n";

    std::ostringstream o;
    o << a << " " << b << " " << c << " " << d;
    auto concatenated(o.str());
    std::cout << concatenated << "\n";

    // преобразование
    std::transform(begin(concatenated), end(concatenated), begin(concatenated), ::toupper);
    std::cout << concatenated << "\n";

    // очистка от пробелов
    {
        std::string s { "\t\n string surrounded by ugly"
                        " whitespaces \t\n"};

        std::cout << "{" << s << "}\n";
        std::cout << "{" << trim_whitespace_surrounding(s) << "}\n";
    }

    // очистка от пробелов через string_view
    {
        print(argv[0]);
        print({});
        print("a const char* array");
        print("an std::string_view literal"sv);
        print("an std::string instance"s);
        print(" \t\n foobar \n \t ");
        
        // строка, которая не заканчивается нулем
        char cstr[] {'a', 'b', 'c'};
        print(cstr); // UB - ошибка - будет выведен мусор 

        // передача размера - защита от UB
        print(std::string_view(cstr, sizeof(cstr)));

        std::string_view sv2 {"bar"s}; // UB - временная строка кладется во view
        std::cout << sv2 << "\n";


    }
    return 0;
}
