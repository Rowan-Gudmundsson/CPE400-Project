#include <conio.h>

#include "region.hpp"

#define MAX_ITT 1000000

int main() {
  Region region(60, 60);

  region.spawn_users(1000);
  region.spawn_uavs(10);

  auto start = std::chrono::steady_clock::now();
  auto end = start;

  long itt = 0;
  while (itt < MAX_ITT) {
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    start = std::chrono::steady_clock::now();
    region.update(elapsed.count());
    end = std::chrono::steady_clock::now();

    if (itt % 1000 == 0) {
      system("CLS");
      std::cout << region << std::endl;
    }
    itt++;
  }

  return 0;
}