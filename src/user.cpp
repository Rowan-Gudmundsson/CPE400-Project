#include <iostream>

#include "region.hpp"

void User::update(unsigned dt, uint8_t direction) {
  bool did_something = false;
  if (direction & Direction::UP) {
    did_something = true;
    Region::m_test_map["up"]++;
    up(dt);
  } else if (direction & Direction::DOWN) {
    did_something = true;
    Region::m_test_map["down"]++;
    down(dt);
  }

  if (direction & Direction::LEFT) {
    did_something = true;
    Region::m_test_map["left"]++;
    left(dt);
  } else if (direction & Direction::RIGHT) {
    did_something = true;
    Region::m_test_map["right"]++;
    right(dt);
  }

  if (!did_something) {
    Region::m_test_map["none"]++;
  }
  Region::m_test_count++;
}