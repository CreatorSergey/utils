#include <vector>
#include <iostream>

void ShakerSort(std::vector<int>& items)
{
    if(items.empty())
        return;

    int left = 0;
    int right = items.size() - 1;

    while(left <= right)
    {
        for(int i = right; i > left; --i)
        {
            if(items[i - 1] > items[i])
            {
                std::swap(items[i - 1], items[i]);
            }
        }
        ++left;

        for(int i = left; i < right; ++i)
        {
            if(items[i] > items[i + 1])
            {
                std::swap(items[i], items[i + 1]);
            }
        }
        --right;
    }
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    ShakerSort(items);

    for(const auto& item: items)
        std::cout << item << ",";

    std::cout << "\n";

    return 0;
}
