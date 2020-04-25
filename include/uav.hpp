#pragma once

#include <unordered_map>
#include <vector>

#include "common.hpp"

class UAV : public Entity {
 public:
  static const int m_coverage = UAV_COVERAGE;
  static const int m_bandwidth = UAV_BANDWIDTH;
  static const int m_fuel_capacity = MAX_FUEL;

  UAV() = default;
  UAV(const Position& pos, Region* region) : Entity(pos, region) {
    m_speed = 0.0005;
  }

  EntityType m_type = EntityType::UAV_TYPE;

  void update(unsigned dt, uint8_t direction) override;
  bool attach_user(Entity* user, unsigned dt);
  unsigned get_covered();
  bool dispatch(Position pos);
  bool reached() { return m_reached; }
  bool ready() { return !m_refueling && m_reached; }

 private:
  unsigned m_accumulator = 0;
  double m_fuel_level = m_fuel_capacity;
  std::vector<Entity*> m_attached_users;
  int m_current_usage = 0;
  Position m_target;
  bool m_reached = true;
  bool m_refueling = false;
};
