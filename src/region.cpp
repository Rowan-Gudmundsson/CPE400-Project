#include "region.hpp"

std::mt19937 Region::m_twister =
    std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());

Region::Region(int x, int y) {
  m_x_dim = x;
  m_y_dim = y;

  m_region = new unsigned[x * y];
  for (int i = 0; i < x * y; i++) {
    m_region[i] = 0;
  }
}

unsigned& Region::operator()(int x, int y) { return m_region[x * m_x_dim + y]; }

unsigned Region::operator()(int x, int y) const {
  return m_region[x * m_x_dim + y];
}

unsigned& Region::operator()(const Position& pos) {
  return m_region[pos.x * m_x_dim + pos.y];
}

unsigned Region::operator()(const Position& pos) const {
  return m_region[pos.x * m_x_dim + pos.y];
}

void Region::spawn_users(int n) {
  for (unsigned i = 0; i < n; i++) {
    Position random_pos = {m_twister() % m_x_dim, m_twister() % m_y_dim};

    ++this->operator()(random_pos);

    User* user = new User(random_pos, this);

    m_entities.push_back(user);
  }
}

void Region::spawn_uavs(int n) {
  for (unsigned i = 0; i < n; i++) {
    Position random_pos = {m_twister() % m_x_dim, m_twister() % m_y_dim};

    ++this->operator()(random_pos);

    UAV* uav = new UAV(random_pos, this);

    m_entities.push_back(uav);
  }
}

std::ostream& operator<<(std::ostream& stream, const Region& region) {
  for (int i = 0; i < region.m_x_dim; i++) {
    for (int j = 0; j < region.m_y_dim; j++) {
      stream << region(i, j) << " ";
    }
    stream << std::endl;
  }

  return stream;
}
