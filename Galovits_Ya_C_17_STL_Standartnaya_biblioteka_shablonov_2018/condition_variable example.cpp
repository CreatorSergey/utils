#include <condition_variable>
#include <iostream>
#include <mutex>
#include <chrono>

std::condition_variable g_Bell;
std::condition_variable_any g_Door;

// Один, заурядный, менеджера приходит на работу звонит в звонок и ждёт пока охранник откроет ему дверь:
class Manager
{
public:
      void ComeToWork()
      {
         std::mutex mutex;
         std::cout << "Hey security, please open the door!\n";
         g_Bell.notify_one();
         mutex.lock();
         g_Door.wait(mutex);
         std::cout << "I an here girls!\n";
         mutex.unlock();
      }
};

/*
* Работа охранника, в свою очередь, ожидать звонка в звонок и открывать дверь менеджеру. 
* Если звонок не звонит, значит можно спать. Вот такая работа.
*  Но у него есть ещё одна ответственная обязанность, взваленная на него программистами фирмы: 
* он должен предупредить их, если менеджер вдруг придёт неожиданно на работу:
*/

class Security
{
   static bool m_SectorClear;
   static std::mutex m_SectorMutex;
public:
   static bool SectorClear()
   {
      std::lock_guard<std::mutex> lock(m_SectorMutex);
      return m_SectorClear;
   }

   void NotifyFellows()
   {
      std::lock_guard<std::mutex> lock(m_SectorMutex);
      m_SectorClear = false;
   }

   void WorkHard()
   {
      m_SectorClear = true;
      std::mutex mutex;
      std::unique_lock<std::mutex> lock(mutex);
      while(true)
      {
          g_Bell.wait(lock); 

         NotifyFellows();
         g_Door.notify_one();
         std::cout << "Hello Great Manager, your slaves are readt to server you!\n";

      }
   }
};

bool Security::m_SectorClear;
std::mutex Security::m_SectorMutex;

class Programmer
{
public:
   void WorkHard()
   {
         std::cout << "Lets write some govnokod!\n";
         int i = 0;
         while(true)
         {
            i++;
            i--;
         }
   }

   void PlayStartCraft()
   {
      std::cout << "PlayStartCraft!\n";
      while(Security::SectorClear())
         ;

      WorkHard();
   }
};

int main() { 
   
   Manager manager;
   Programmer programmer;
   Security security;

   auto managerCall = [&manager](){
      manager.ComeToWork();
   };

   auto programmerCall = [&programmer]()
   {
         programmer.PlayStartCraft();
   };

   auto securityCall = [&security](){
      security.WorkHard();
   };

   std::thread securityThread(securityCall);
   std::thread programmerThread(programmerCall);
   std::this_thread::sleep_for(std::chrono::seconds(10));
   std::thread managerThread(managerCall);

   managerThread.join();
   programmerThread.join();
   securityThread.join();

   return 0; 
}
