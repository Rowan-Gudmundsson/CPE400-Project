// Filename:  main.cpp
// Author(s): Rowan Gudmundsson
//            Michael Des Roches
//            Emily Godby
// Date: 30APR2020
// Class: CPE 400 - Networks
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "region.hpp"

/*---------------------------------------------------------------------------------
|  Function: update()
|  Purpose: updates position
|  Parameters: time and direction
|  Returns: N/A
*--------------------------------------------------------------------------------*/
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