// Filename:  common.hpp
// Author(s): Rowan Gudmundsson
//            Michael Des Roches
//            Emily Godby
// Date: 30APR2020
// Class: CPE 400 - Networks
///////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_FUEL 100
#define UAV_COVERAGE 10
#define UAV_BANDWIDTH 100
#define MICRO_CONVERSION 1000000

#include <cmath>
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
  /**
   * \brief Compute the distance from one point to another
   **/
  static double Distance(Position a, Position b);

  Position() = default;
  Position(double _x, double _y) : x(_x), y(_y) {}

  bool operator==(Position b) {
    return (int)x == (int)b.x && (int)y == (int)b.y;
  }
  bool operator==(const Position& b) const {
    return (int)x == (int)b.x && (int)y == (int)b.y;
  }

  double x;
  double y;
};

class PositionHasher {
 public:
  size_t operator()(const Position& key) const {
    return (long long unsigned)key.x | ((long long unsigned)key.y << 32);
  }
};

class Entity {
 public:
  Entity() = default;
  Entity(const Position& pos, Region* region)
      : m_position(pos), m_region(region) {
    m_speed = 0.05;
  }

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
