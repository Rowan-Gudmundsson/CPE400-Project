#pragma once

#include <random>

#include "common.hpp"

class User : public Entity {
 public:
  User() = default;
  User(Position pos, Region* region, unsigned usage) : Entity(pos, region) {
    m_speed = 0.00005;
    m_usage_level = usage;
  }
  unsigned m_usage_level;

  EntityType m_type = EntityType::USER_TYPE;

  void update(unsigned dt, uint8_t direction) override;

 private:
};