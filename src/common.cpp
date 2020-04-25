#include "region.hpp"

bool operator&(uint8_t value, Direction direction) {
  return static_cast<bool>((value & (uint8_t)direction) == (uint8_t)direction);
}

double Position::Distance(Position a, Position b) {
  return std::sqrt(std::pow(std::abs(a.x - b.x), 2) +
                   std::pow(std::abs(a.y - b.y), 2));
}

void Entity::up(unsigned dt) {
  if (m_position.y - m_speed * dt <= 0.0) {
    m_position.y = 0;
  } else {
    m_position.y -= m_speed * dt;
  }
}

void Entity::down(unsigned dt) {
  if (m_position.y + m_speed * dt >= m_region->m_y_dim) {
    m_position.y = m_region->m_y_dim - 1;
  } else {
    m_position.y += m_speed * dt;
  }
}

void Entity::left(unsigned dt) {
  if (m_position.x - m_speed * dt <= 0.0) {
    m_position.x = 0;
  } else {
    m_position.x -= m_speed * dt;
  }
}

void Entity::right(unsigned dt) {
  if (m_position.x + m_speed * dt >= m_region->m_x_dim) {
    m_position.x = m_region->m_x_dim - 1;
  } else {
    m_position.x += m_speed * dt;
  }
}