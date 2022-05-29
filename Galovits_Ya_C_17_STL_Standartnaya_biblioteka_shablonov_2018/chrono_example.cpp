// https://habr.com/ru/post/324984/

#include <chrono>
#include <thread>
#include <future>
#include <iostream>

int find_answer_to_the_ultimate_question_of_life()
{
    using namespace std::chrono;
    std::this_thread::sleep_for(5s);

    return 42;
}

int main() {

    using namespace std::chrono;

    auto start = steady_clock::now();
    if(steady_clock::now() < start + 1s)
        std::cout << "Less than a second!\n";

    seconds s = 4min;

    minutes m1 = duration_cast<minutes>(-100s);
    std::cout << m1 << "\n";

    std::cout << s << "\n";

    std::future<int> f = std::async(find_answer_to_the_ultimate_question_of_life);

    if(f.wait_for(6000ms) == std::future_status::ready)
    {
        std::cout << "answer is " << f.get() << "\n";
    }
    else
    {
        std::cout << "Cant wait anymore\n";
    }

    return 0;
}
