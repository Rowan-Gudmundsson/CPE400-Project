#include <iostream>

#include "region.hpp"

void User::update(unsigned dt, uint8_t direction) {
  if (direction & Direction::UP) {
    up(dt);
  } else if (direction & Direction::DOWN) {
    down(dt);
  } else if (direction & Direction::LEFT) {
    left(dt);
  } else if (direction & Direction::RIGHT) {
    right(dt);
  }
}