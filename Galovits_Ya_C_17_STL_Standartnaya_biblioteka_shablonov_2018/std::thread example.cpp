#include <iostream>
#include <thread>
#include <string>
#include <chrono>

int main() {

    // функция для исполнения
    auto func = [](const std::string& first, const std::string second) {
        std::cout << first << " " << second << "\n";

        // останавливаю поток на 2 секунды
        std::this_thread::sleep_for(std::chrono::seconds(2));

    };

    // создание потока
    std::thread thread_1(func, "Hello", "threads!");
    // получаю кол-во потоков на устройстве
    std::cout << std::thread::hardware_concurrency() << "\n";

    // получаю идентификатор потока
    std::cout << "thread id: " << thread_1.get_id() << "\n";

    std::cout << "current thread id: " << std::this_thread::get_id() << "\n";

    // останавливаю поток до момента в будущем
    auto next_time = std::chrono::system_clock::now() + std::chrono::seconds(4);
    std::this_thread::sleep_until(next_time);

    thread_1.join();     // ожидание завершений потока

    return 0;
}
