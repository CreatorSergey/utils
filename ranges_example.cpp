#include <utility>
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

class fib_iterator {
    int cur_ = 0;
    int next_ = 1;
public:
    using value_type = int;
    using difference_type = int;

    int operator*() const { return cur_; }

    fib_iterator& operator++() {
        cur_ = std::exchange(next_, cur_ + next_);
        return *this;
    }

    fib_iterator operator++(int) {
        auto oldval = *this;
        ++*this;
        return oldval;
    }
};

template <auto V> struct EndValue {
  bool operator==(auto pos) const { return *pos == V; }  
};

int main() {
    fib_iterator fi;
    for(int i = 0; i < 10; ++i, ++fi)
        std::cout << *fi << ",";

    std::cout << "\n";

    fib_iterator fi2;
    auto ci = std::counted_iterator{fi2, 10};
    for(auto it = ci; it != std::default_sentinel; ++it) {
        std::cout << *it << ",";
    }

    std::cout << "\n";

    std::vector<int> v {1, 4, 2, 8, 16, 32, 64};

    auto w = std::ranges::subrange(v.begin() + 1, EndValue<8>{});
    std::ranges::common_view cv(w);
    // std::sort(cv.begin(), cv.end());

    fib_iterator fi3;
    auto fv = std::ranges::subrange {fi3, std::unreachable_sentinel};
    auto fib_tk = std::views::take(fv, 10);
    for(auto item: fib_tk) {
        std::cout << item << ",";
    }

    return 0;
}
