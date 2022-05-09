#include <vector>
#include <iostream>

void InsertionSort(std::vector<int>& items)
{
    for(size_t i = 1; i < items.size(); ++i)
    {
        int x = items[i];
        size_t j = i;

        while(j > 0 && items[j - 1] > x)
        {
            items[j] = items[j - 1];
            --j;
        }
        items[j] = x;
    }
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    InsertionSort(items);

    for(const auto& item: items)
        std::cout << item << ",";

    std::cout << "\n";

    return 0;
}
