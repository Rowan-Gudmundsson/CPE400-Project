#pragma once

#define MAX_FUEL 100
#define UAV_COVERAGE 3
#define UAV_BANDWIDTH 1000

class Region;

struct Position {
  Position(unsigned _x, unsigned _y) : x(_x), y(_y) {}

  unsigned x;
  unsigned y;
};

class Entity {
 public:
  Entity() = default;
  Entity(const Position& pos, Region* region)
      : m_position(pos), m_region(region) {}

  Position get_position() { return m_position; }

  enum EntityType {
    ERROR_TYPE = 0,
    USER_TYPE = 1,
    UAV_TYPE = 2,
  } m_type;

  virtual void update(unsigned dt) = 0;

 private:
  Position m_position;
  Region* m_region;
};
