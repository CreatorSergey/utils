#include <vector>
#include <iostream>

void CombSort(std::vector<int>& items)
{
    const double factor = 1.247;
    double step = items.size() - 1;

    while(step >= 1)
    {
        for(int i = 0; i + step < items.size(); ++i)
        {
            if(items[i] > items[i + step])
            {
                std::swap(items[i], items[i + step]);
            }
        }

        step /= factor;
    }
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    CombSort(items);

    for(const auto& item: items)
        std::cout << item << ",";

    std::cout << "\n";

    return 0;
}
