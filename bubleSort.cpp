#include <vector>
#include <iostream>

void bubleSort(std::vector<int>& items)
{
    for(size_t i = 0; i + 1 < items.size(); ++i)
    {
        for(size_t j = 0; j + 1 < items.size() - i; ++j)
        {
            if(items[j + 1] < items[j])
                std::swap(items[j], items[j + 1]);
        }
    }
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    bubleSort(items);

    for(const auto& item: items)
        std::cout << item << ",";

    std::cout << "\n";

    return 0;
}
