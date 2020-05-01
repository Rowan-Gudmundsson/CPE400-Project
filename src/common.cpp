// Filename: common.cpp
// Author(s): Rowan Gudmundsson
//            Michael Des Roches
//            Emily Godby
// Date: 30APR2020
// Class: CPE 400 - Networks
///////////////////////////////////////////////////////////////////////////////////

#include "region.hpp"

/*---------------------------------------------------------------------------------
|  Function: operator&()
|  Purpose: overload function
|  Parameters: value, direction
|  Returns: bool
*--------------------------------------------------------------------------------*/
bool operator&(uint8_t value, Direction direction) {
  return static_cast<bool>((value & (uint8_t)direction) == (uint8_t)direction);
}
/*---------------------------------------------------------------------------------
|  Function: Distance(Position a, Position b)
|  Purpose: computes distance from one node to another
|  Parameters: Position a, Position b
|  Returns: distance between node 'a' and node 'b'
*--------------------------------------------------------------------------------*/
double Position::Distance(Position a, Position b) {
  return std::sqrt(std::pow(std::abs(a.x - b.x), 2) +
                   std::pow(std::abs(a.y - b.y), 2));
}
/*---------------------------------------------------------------------------------
|  Function: up()
|  Purpose: moves entity up at a set speed over time
|  Parameters: time
|  Returns: NA
*--------------------------------------------------------------------------------*/
void Entity::up(unsigned dt) {
  if (m_position.y - m_speed * dt <= 0.0) {
    m_position.y = 0;
  } else {
    m_position.y -= m_speed * dt;
  }
}
/*---------------------------------------------------------------------------------
|  Function: down()
|  Purpose: moves entity down at a set speed over time
|  Parameters: time
|  Returns:  N/A
*--------------------------------------------------------------------------------*/
void Entity::down(unsigned dt) {
  if (m_position.y + m_speed * dt >= m_region->m_y_dim) {
    m_position.y = m_region->m_y_dim - 1;
  } else {
    m_position.y += m_speed * dt;
  }
}
/*---------------------------------------------------------------------------------
|  Function: left()
|  Purpose: moves entity left at a set speed over time
|  Parameters: time
|  Returns: N/A
*--------------------------------------------------------------------------------*/
void Entity::left(unsigned dt) {
  if (m_position.x - m_speed * dt <= 0.0) {
    m_position.x = 0;
  } else {
    m_position.x -= m_speed * dt;
  }
}
/*---------------------------------------------------------------------------------
|  Function: right()
|  Purpose: moves entity right at a set speed over time
|  Parameters: time
|  Returns:  N/A
*--------------------------------------------------------------------------------*/
void Entity::right(unsigned dt) {
  if (m_position.x + m_speed * dt >= m_region->m_x_dim) {
    m_position.x = m_region->m_x_dim - 1;
  } else {
    m_position.x += m_speed * dt;
  }
}