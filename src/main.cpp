// Filename:  main.cpp
// Author(s): Rowan Gudmundsson
//            Michael Des Roches
//            Emily Godby
// Date: 30APR2020
// Class: CPE 400 - Networks
///////////////////////////////////////////////////////////////////////////////////

#include "region.hpp"
#include "conio.h"

#define MAX_ITT 1000000

/*---------------------------------------------------------------------------------
|  Function: main()
|  Purpose:  driver function
|  Parameters: N/A
|  Returns:  0
*--------------------------------------------------------------------------------*/
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

      std::cout << region << std::endl;

      getch();

      system("CLS");
    itt++;
  }

  return 0;
}