#include <conio.h>

#include "region.hpp"

#define MAX_ITT 1000000

int main() {
  Region region(50, 50);

  region.spawn_users(100);
  region.spawn_uavs(5);

  auto start = std::chrono::steady_clock::now();
  auto end = start;

  long itt = 0;
  while (itt < MAX_ITT) {
    if (itt % 1000 == 0) {
      std::cout << "\r" << (double)itt / MAX_ITT * 100 << "%";
    }
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    start = std::chrono::steady_clock::now();
    region.update(elapsed.count());
    end = std::chrono::steady_clock::now();

    system("CLS");
    std::cout << region << std::endl;
    itt++;
  }
  std::cout << std::endl;
  for (const auto& kvp : Region::m_test_map) {
    std::cout << "KEY " << kvp.first << " VALUE "
              << (double)kvp.second / Region::m_test_count << std::endl;
  }
  return 0;
}