#include "uav.hpp"

#include "user.hpp"

void UAV::update(unsigned dt, uint8_t direction) {
  m_fuel_level -= (double)dt / MICRO_CONVERSION;
  if (m_fuel_level <= 0) {
    m_refueling = true;
    m_reached = false;
    m_target = Position(0, 0);
  }

  if (m_position == Position(0, 0)) {
    m_refueling = false;
    m_reached = true;
    m_fuel_level = m_fuel_capacity;
  }

  if (m_position == m_target) {
    m_reached = true;
  }

  m_accumulator += dt;
  m_attached_users.clear();

  if (m_accumulator >= MICRO_CONVERSION) {
    m_accumulator = 0;
    m_current_usage = 0;
  }

  Position zero_vec(0, 0);
  Position vector(m_target.x - m_position.x, m_target.y - m_position.y);

  double normal = Position::Distance(zero_vec, vector);
  vector.x /= normal == 0 ? 1 : normal;
  vector.y /= normal == 0 ? 1 : normal;

  vector.x *= m_speed * dt;
  vector.y *= m_speed * dt;

  if (Position::Distance(m_position, m_target) <= m_speed * dt) {
    m_position = m_target;
  } else {
    m_position = Position(vector.x + m_position.x, vector.y + m_position.y);
  }
}

bool UAV::attach_user(Entity* user, unsigned dt) {
  if (m_fuel_level <= 0) {
    return false;
  }

  if (((User*)user)->m_usage_level * (double)dt / MICRO_CONVERSION +
          m_current_usage <=
      m_bandwidth) {
    m_attached_users.push_back(user);
    m_current_usage +=
        ((User*)user)->m_usage_level * (double)dt / MICRO_CONVERSION;
    return true;
  }

  return false;
}

unsigned UAV::get_covered() {
  unsigned total = 0;
  for (const auto& user : m_attached_users) {
    total += ((User*)user)->m_usage_level;
  }

  return total;
}

bool UAV::dispatch(Position pos) {
  if (m_reached && !m_refueling) {
    m_target = pos;
    m_reached = false;
    return true;
  }

  return false;
}