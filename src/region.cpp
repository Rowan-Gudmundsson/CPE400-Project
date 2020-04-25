#include "region.hpp"

std::mt19937 Region::m_twister =
    std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());

std::unordered_map<std::string, unsigned> Region::m_test_map;
long long Region::m_test_count = 0;

uint8_t Region::GenDirection() {
  int x_dir = m_twister() % 4 - 1;
  int y_dir = m_twister() % 4 - 1;

  x_dir = x_dir < 0 ? 0 : x_dir;
  y_dir = y_dir < 0 ? 0 : y_dir;

  uint8_t dir = x_dir | (y_dir << 2);
  return dir;
}

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

void Region::update(unsigned dt) {
  delete m_region;
  m_region = new unsigned[m_x_dim * m_y_dim];
  std::fill(m_region, m_region + m_x_dim * m_y_dim, 0);

  for (const auto& entity : m_entities) {
    uint8_t dir = GenDirection();
    entity->update(dt, dir);
    ++this->operator()(entity->get_position());
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
