#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common.hpp"
#include "uav.hpp"
#include "user.hpp"

class Region {
 public:
  static uint8_t GenDirection();
  static std::unordered_map<std::string, unsigned> m_test_map;
  static long long m_test_count;

  Region(int x, int y);

  unsigned operator()(int x, int y) const;
  unsigned& operator()(Entity::EntityType type, int x, int y);
  unsigned operator()(Entity::EntityType type, int x, int y) const;

  unsigned& operator()(Entity::EntityType type, const Position& pos);
  unsigned operator()(Entity::EntityType type, const Position& pos) const;

  void spawn_users(int n);
  void spawn_uavs(int n);

  void update(unsigned dt);

  friend std::ostream& operator<<(std::ostream& stream, const Region& region);
  friend class Entity;

 private:
  static std::mt19937 m_twister;
  static std::unordered_map<Position, UAV*, PositionHasher> m_dispatch;

  int m_x_dim;
  int m_y_dim;

  unsigned* m_uav_locations = nullptr;
  unsigned* m_user_locations = nullptr;

  std::vector<User*> m_users;
  std::vector<UAV*> m_uavs;

  double determine_error(unsigned dt);
  std::vector<unsigned> discretize_user(unsigned size);
  void dispatch_uavs(std::vector<unsigned>& discretized);

  void reset_matrices();
};
