#include <type_traits>
#include <utility>
#include <iostream>

template <typename T, typename ... Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template <typename T, typename ... Ts>
struct first_arg { using type = T; };

template <typename ... Ts>
using first_arg_t = typename first_arg<Ts...>::type;

template <typename ... Ts>
concept Addable = requires(Ts&&... args) {
    { (... + std::forward<Ts>(args)) } -> std::same_as<first_arg_t<Ts...>>;
    requires are_same_v<Ts...>;
    requires sizeof...(Ts) > 1;
};

template <typename ... Ts>
auto sum_all(Ts&& ... args) requires Addable<Ts...> {
    return (... + std::forward<Ts>(args));
}

int main() {
    std::cout << sum_all(1, 2, 3);
}
