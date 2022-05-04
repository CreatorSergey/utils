#include <iostream>
#include <forward_list>
#include <iterator>

int main()
{
    std::forward_list<size_t> items {1,2,3,4,5};
    items.reverse();
    std::copy(begin(items), end(items), std::ostream_iterator<size_t>(std::cout, " "));
    return 0;
}
