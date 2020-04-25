#pragma once

#define MAX_FUEL 100
#define UAV_COVERAGE 3
#define UAV_BANDWIDTH 1000

#include <cstdint>

class Region;

enum class Direction {
  NONE = 0,
  UP = 1 << 0,
  DOWN = 1 << 1,
  LEFT = 1 << 2,
  RIGHT = 1 << 3
};

bool operator&(uint8_t value, Direction direction);

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

  virtual void update(unsigned dt, uint8_t direction) = 0;

 protected:
  Position m_position;
  Region* m_region;
  float m_speed;

  void up(unsigned dt);
  void down(unsigned dt);
  void left(unsigned dt);
  void right(unsigned dt);
};
