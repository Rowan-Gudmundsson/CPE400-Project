#include "region.hpp"

bool operator&(uint8_t value, Direction direction) {
  return static_cast<bool>(value & (uint8_t)direction);
}

void Entity::up(unsigned dt) {
  if ((int)m_position.y + m_speed * dt >= m_region->m_y_dim) {
    m_position.y = m_region->m_y_dim - 1;
  } else {
    m_position.y = m_position.y + m_speed * dt;
  }
}

void Entity::down(unsigned dt) {
  if ((int)m_position.y - m_speed * dt < 0) {
    m_position.y = 0;
  } else {
    m_position.y = m_position.y - m_speed * dt;
  }
}

void Entity::left(unsigned dt) {
  if ((int)m_position.x - m_speed * dt < 0) {
    m_position.x = 0;
  } else {
    m_position.x = m_position.x - m_speed * dt;
  }
}

void Entity::right(unsigned dt) {
  if ((int)m_position.x + m_speed * dt >= m_region->m_x_dim) {
    m_position.x = m_region->m_x_dim - 1;
  } else {
    m_position.x = m_position.x + m_speed * dt;
  }
}