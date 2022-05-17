#include <iostream>

namespace tools {

// специализация для указателя
template <typename T> struct default_delete {
    void operator()(T* ptr) const {
        delete ptr;
    }
};

// специализация для массива
template <typename T> struct default_delete<T[]> {
    void operator()(T* ptr) const {
        delete [] ptr;
    }
};

template <typename T, typename Deleter = default_delete<T>>
class unique_ptr {
    using self = unique_ptr;
 public:
    unique_ptr(T* ptr, Deleter del = Deleter())
        : ptr_(ptr), del_(del) {
        std::cout << "unique_ptr construct: " << this << "\n";
    }
    
    template<typename ...Args>
    unique_ptr(Args&& ...args) 
        : ptr_(new T(std::forward<Args>(args)...)) {
            std::cout << "unique_ptr variadic constuct: " << this << "\n";
        }
 
    unique_ptr(const self& other) = delete;
    self& operator=(const self& other) = delete;
    unique_ptr(self&& other) noexcept 
        : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
        std::cout << "unique_ptr move construct: " << this << "\n";
    }
    self& operator=(self&& other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        std::cout << "unique_ptr move assigment: " << this << "\n";
        return *this;
    }
    ~unique_ptr() {
        del_(ptr_);
    }
    const T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    T* get() const { return ptr_; }

private:
    T* ptr_;
    Deleter del_;
};

class test_object {
    using self = test_object;
 public:
    test_object() {
        std::cout << "test_object default construct: " << this << "\n";
    }

    test_object(int value) {
        value_ = value;
        std::cout << "test_object int construct: " << this << "\n";
    }

    ~test_object() {
        std::cout << "test_object destroy: " << this << "\n";
    }

    test_object(const self& other) {
        value_ = other.value_;
        std::cout << "test_object copy construct: " << this << "\n";
    }

    test_object& operator=(const self& other) noexcept {
        value_ = other.value_;
        std::cout << "test_object copy assigment: " << this << "\n";
        return *this;
    }

    test_object(self&& other) noexcept {
        value_ = other.value_;
        other.value_ = 0;
        std::cout << "test_object move construct: " << this << "\n";
    }

    test_object& operator=(self&& other) {
        value_ = other.value_;
        other.value_ = 0;
        std::cout << "test_object move assigment: " << this << "\n";
        return *this;
    }

    int value() const {
        return value_;
    }

private:
    int value_ = 0;
};

std::ostream& operator<<(std::ostream& os, const test_object& item) {
    return os << item.value();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const unique_ptr<T>& item) {
    return os << *item;
}

} // tools

int main()
{
    tools::unique_ptr<tools::test_object> test1(new tools::test_object());
    tools::unique_ptr<tools::test_object> test2 = std::move(test1);
    tools::unique_ptr<tools::test_object> test3;
    test3 = std::move(test2);

    tools::unique_ptr<tools::test_object> test4(5);

    const auto& test4_ref = *test4;
    std::cout << test4_ref << "\n";
    std::cout << test4 << "\n";
}
