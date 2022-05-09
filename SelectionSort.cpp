#include <vector>
#include <iostream>
#include <algorithm>

void SelectionSort(std::vector<int>& items)
{
    for(auto i = items.begin(); i != items.end(); ++i)
    {
        auto j = std::min_element(i, items.end());
        std::swap(*i, *j);
    }
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    SelectionSort(items);

    for(const auto& item: items)
        std::cout << item << ",";

    std::cout << "\n";

    return 0;
}
