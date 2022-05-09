#include <vector>
#include <iostream>
#include <algorithm>

void HeapSort(std::vector<int>& items)
{
    std::make_heap(begin(items), end(items));
    for(auto i = items.end(); i != items.begin(); --i)
    {
        std::pop_heap(items.begin(), i);
    }
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    HeapSort(items);

    for(const auto& item: items)
        std::cout << item << ",";

    std::cout << "\n";

    return 0;
}
