#include "region.hpp"

int main() {
  Region region(50, 50);

  region.spawn_users(2000);
  region.spawn_uavs(500);

  std::cout << region << std::endl;
  return 0;
}