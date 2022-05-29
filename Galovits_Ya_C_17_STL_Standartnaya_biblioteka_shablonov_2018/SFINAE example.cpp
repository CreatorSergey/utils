// http://scrutator.me/post/2017/04/10/has_function_metaprogramming.aspx

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <list>

template <typename Type>
struct HasFunctionSort {
    template<typename T>
    static auto test(T&&) ->
        decltype(std::declval<T>().sort(), std::true_type{});
    
    static std::false_type test(...);

    static constexpr bool value = 
        std::is_same<decltype(test(std::declval<Type>())), std::true_type>::value;
};

template <typename T>
constexpr bool HasFunctionSort_v = HasFunctionSort<T>::value;

template<typename Container>
std::enable_if_t<HasFunctionSort_v<Container>>
sort(Container& container)
{
    std::cout << "Calling member sort function\n";
    container.sort();
}

template<typename Container>
std::enable_if_t<!HasFunctionSort_v<Container>>
sort(Container& container)
{
    std::cout << "Calling std::sort function\n";
    std::sort(begin(container), end(container));
}

int main()
{
    std::vector items {1, 2, 3, 4};
    sort(items);

    std::list items2 {1, 2, 3, 4};

    sort(items2);

    return 0;
}
