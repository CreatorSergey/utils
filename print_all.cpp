
/*
template <typename T> class AddSpace {
	const T& ref;
public:
  AddSpace(const T& r): ref(r) {}
  friend std::ostream& operator<<(std::ostream& os, AddSpace s) {
  	return os << s.ref << " ";
  }
};

void print_all() {
}

template <typename ... T> void print_all(T ... args) {
	(std::cout << ... << AddSpace(args)) << "\n";
}

*/



// на gcc 12.2 с -std=c++20
// никак не собирался 22 слайд с одним шаблонным сверточным параметром T
// получилось собрать, добавив первый шаблонный параметр отдельно от сверточного

#include <iostream>

void print_all() {}

template <typename Arg, typename ... Args> 
void print_all(Arg&& arg, Args&& ... args) {
	std::cout << arg << " ";
    if constexpr (sizeof...(args) != 0)
        print_all(std::forward<Args>(args)...);
}

int main() {
    print_all(1, 2, 3);
    print_all();    
    return 0;
}
