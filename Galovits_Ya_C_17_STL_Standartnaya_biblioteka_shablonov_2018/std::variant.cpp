//  полиморфизм с помощью std::variant и std::visit

#include <iostream>
#include <variant>

class Derived {
public:
    void PrintName() const {
        std::cout << "calling Derived!\n";
    }

    void PrintText(std::string_view text) const {
        std::cout << "Derived " << text << "\n"; 
    }
};

class ExtraDerived {
public:
    void PrintName() const {
        std::cout << "calling ExtraDerived!\n";
    }

    void PrintText(std::string_view text) const {
        std::cout << "ExtraDerived " << text << "\n"; 
    }
};

int main()
{
    std::variant<Derived, ExtraDerived> var;

    // если интерфейсы разные
    struct CallPrintName {
        void operator()(const Derived& d) { d.PrintName(); }
        void operator()(const ExtraDerived& ed) { ed.PrintName(); }
    };

    std::visit(CallPrintName{}, var);

    // если интерфейсы одинаковые
    auto caller = [](const auto& obj) { obj.PrintName(); };
    std::visit(caller, var);

    // передача параметра
    struct CallPrintArg {
        void operator()(const Derived& d) { d.PrintText(text); }
        void operator()(const ExtraDerived& ed) { ed.PrintText(text); }
        std::string_view text;
    };

    std::visit(CallPrintArg{"test"}, var);

    return 0;
}
