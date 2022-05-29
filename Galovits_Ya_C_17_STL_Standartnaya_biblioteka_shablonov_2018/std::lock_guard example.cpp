// http://scrutator.me/post/2012/04/04/parallel-world-p1.aspx

#include <chrono>
#include <iostream>
#include <limits>
#include <list>
#include <mutex>
#include <thread>

class WarehouseEmpty {};

unsigned short c_SpecialItem = std::numeric_limits<unsigned short>::max();

class Warehouse {
  std::list<unsigned short> m_Store;

 public:
  void AcceptItem(unsigned short item) { m_Store.push_back(item); }

  unsigned short HandLastItem() {
    if (m_Store.empty()) throw WarehouseEmpty();

    unsigned short item = m_Store.front();
    if (item != c_SpecialItem) m_Store.pop_front();
    return item;
  }
};

// два склада
Warehouse g_FirstWarehouse;
Warehouse g_SecondWarehouse;
std::timed_mutex g_FirstMutex;
std::mutex g_SecondMutex;

// поставщик, заполянет склады по очереди
auto supplier = []() {
  for (unsigned short i = 0, j = 0; i < 10 || j < 10;) {
    if (i < 10 && g_FirstMutex.try_lock()) {
      g_FirstWarehouse.AcceptItem(i);
      i++;
      g_FirstMutex.unlock();
    }

    if (j < 10 && g_SecondMutex.try_lock()) {
      g_SecondWarehouse.AcceptItem(j);
      j++;
      g_SecondMutex.unlock();
    }
    std::this_thread::yield();
  }

  // под конец кладем специальный товар - который говорит о том, что товаров
  // больше не будет
  std::lock_guard<std::timed_mutex> firstGuard(g_FirstMutex);
  std::lock_guard<std::mutex> secondGuard(g_SecondMutex);
  g_FirstWarehouse.AcceptItem(c_SpecialItem);
  g_SecondWarehouse.AcceptItem(c_SpecialItem);
};

// потребитель приходит на склад и ждет своей очереди в получении товара
auto consumer = []() {
  while (true) {
    unsigned short item = 0;
    try {
      std::lock_guard<std::timed_mutex> guard(g_FirstMutex);
      item = g_FirstWarehouse.HandLastItem();
    } catch (const WarehouseEmpty&) {
      std::cout << "consumer: Warehouse is empty!\n";
    }
    if (item == c_SpecialItem) break;

    std::cout << "consumer: got a new item: " << item << "!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
};

// второй покупатель нетерпеливый, ходит на второй склад, если первый занят
auto impatientConsumer = []() {
  while (true) {
    unsigned short item = 0;
    if (g_FirstMutex.try_lock_for(std::chrono::seconds(1))) {
      try {
        std::lock_guard<std::timed_mutex> guard(g_FirstMutex, std::adopt_lock);
        item = g_FirstWarehouse.HandLastItem();
      } catch (const WarehouseEmpty&) {
        std::cout << "impatientConsumer: Warehose is empty! I'm mad!!!\n";
      }
      
    } else {
      std::cout << "impatientConsumer: First warehose is always busy!!\n";

      try {
        std::lock_guard<std::mutex> guard(g_SecondMutex);
        item = g_SecondWarehouse.HandLastItem();
      } catch (const WarehouseEmpty&) {
        std::cout << "impatientConsumer: 2nd warehouse is empty!!!!\n";
      }

    }
    if (item == c_SpecialItem) break;

    std::cout << "impatientConsumer: At last I Got new item" << item << "!\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
  }
};

int main() {
  std::thread supplierThread(supplier);
  std::thread consumerThread(consumer);
  std::thread impatientConsumerThread(impatientConsumer);

  supplierThread.join();
  consumerThread.join();
  impatientConsumerThread.join();

  return 0;
}
