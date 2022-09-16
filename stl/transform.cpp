#include <algorithm>
#include <vector>
#include <cassert>
#include <iterator>
#include <iostream>

int multi(int x) {
    return x * 2;
}

int main() {

    std::vector<int> items {1, 2, 3, 4};

    std::transform(items.begin(), items.end(), items.begin(), multi);

    assert(items[0] == 2);
    assert(items[1] == 4);
    assert(items[2] == 6);
    assert(items[3] == 8);

    std::copy(items.begin(), items.end(), std::ostream_iterator<int>(std::cout, ","));

    return 0;
}
