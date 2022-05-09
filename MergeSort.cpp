#include <vector>
#include <iostream>
#include <algorithm>

void MergeSortImpl(std::vector<int>& items, std::vector<int>& buffer, int left, int right)
{
    if(left < right)
    {
        int m = (left + right) / 2;
        MergeSortImpl(items, buffer, left, m);
        MergeSortImpl(items, buffer, m + 1, right);

        int k = left;
        for(int i = left, j = m + 1; i <= m || j <= right; )
        {
            if(j > right || (i <= m && items[i] < items[j]))
            {
                buffer[k] = items[i];
                ++i;
            }
            else
            {
                buffer[k] = items[j];
                ++j;
            }
            ++k;
        }

        for(int i = left; i <= right; ++i)
        {
            items[i] = buffer[i];
        }
    }
}

void MergeSort(std::vector<int>& items)
{
    if(items.empty() == false)
    {
        std::vector<int> buffer(items.size());
        MergeSortImpl(items, buffer, 0, items.size() - 1);
    }
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    MergeSort(items);

    for(const auto& item: items)
        std::cout << item << ",";

    std::cout << "\n";

    return 0;
}
