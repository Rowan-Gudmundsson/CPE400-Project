#pragma once

#include <random>

#include "common.hpp"

class User : public Entity {
 public:
  User() = default;
  User(Position pos, Region* region) : Entity(pos, region) { m_speed = 0.005; }

  EntityType m_type = EntityType::USER_TYPE;

  void update(unsigned dt, uint8_t direction) override;

 private:
};