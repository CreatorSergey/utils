#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
 
std::condition_variable g_Condition;
std::mutex g_Mutex;
 
int main()
{
    auto call = []()
    {
        std::cout << "locked\n";
        std::unique_lock<std::mutex> lock(g_Mutex);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "end\n";
        std::notify_all_at_thread_exit(g_Condition, std::move(lock));
    };  


    std::cout << "locked 2\n";
    std::unique_lock<std::mutex> lock(g_Mutex);

    std::thread callThread(call);
    callThread.detach();

    g_Condition.wait(lock);
    std::cout << "informed\n";


    return 0;
}
