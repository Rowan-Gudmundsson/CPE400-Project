#pragma once

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "common.hpp"
#include "uav.hpp"
#include "user.hpp"

class Region {
 public:
  Region(int x, int y);

  unsigned& operator()(int x, int y);
  unsigned operator()(int x, int y) const;

  unsigned& operator()(const Position& pos);
  unsigned operator()(const Position& pos) const;

  void spawn_users(int n);
  void spawn_uavs(int n);

  friend std::ostream& operator<<(std::ostream& stream, const Region& region);

 private:
  static std::mt19937 m_twister;

  int m_x_dim;
  int m_y_dim;

  unsigned* m_region;
  std::vector<Entity*> m_entities;
};
