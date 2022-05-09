#include <vector>
#include <iostream>
#include <algorithm>

int Partition(std::vector<int>& items, int left, int right)
{
    int x = items[right];
    int less = left;

    for(int i = left; i < right; ++i)
    {
        if(items[i] <= x)
        {
            std::swap(items[i], items[less]);
            ++less;
        }
    }

    std::swap(items[less], items[right]);
    return less;
}

void QuickSortImpl(std::vector<int>& items, int left, int right)
{
    if(left < right)
    {
        int q = Partition(items, left, right);
        QuickSortImpl(items, left, q - 1);
        QuickSortImpl(items, q + 1, right);
    }
}

void QuickSort(std::vector<int>& items)
{
    if(items.empty() == false)
    {
        QuickSortImpl(items, 0, items.size() - 1);
    }
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    QuickSort(items);

    for(const auto& item: items)
        std::cout << item << ",";

    std::cout << "\n";

    return 0;
}
