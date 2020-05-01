// Filename:  region.cpp
// Author(s): Rowan Gudmundsson
//            Michael Des Roches
//            Emily Godby
// Date: 30APR2020
// Class: CPE 400 - Networks
///////////////////////////////////////////////////////////////////////////////////

#include "region.hpp"

std::mt19937 Region::m_twister =
    std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());

std::unordered_map<std::string, unsigned> Region::m_test_map;
long long Region::m_test_count = 0;
std::unordered_map<Position, UAV*, PositionHasher> Region::m_dispatch;

uint8_t Region::GenDirection() {
  int dir = m_twister() % 5;

  return dir == 0 ? 0 : 1 << dir - 1;
}
/*---------------------------------------------------------------------------------
|  Function: Region(int x, int y)
|  Purpose: initializes region with size x by y 
|  Parameters: int x and int y
|  Returns: N/A
*--------------------------------------------------------------------------------*/
Region::Region(int x, int y) {
  m_x_dim = x;
  m_y_dim = y;

  reset_matrices();
}
//operatot overloads
unsigned Region::operator()(int x, int y) const {
  return m_user_locations[y * m_y_dim + x] + m_uav_locations[y * m_y_dim + x];
}

unsigned& Region::operator()(Entity::EntityType type, int x, int y) {
  if (type == Entity::USER_TYPE) {
    return m_user_locations[y * m_y_dim + x];
  }
  return m_uav_locations[y * m_y_dim + x];
}

unsigned Region::operator()(Entity::EntityType type, int x, int y) const {
  if (type == Entity::USER_TYPE) {
    return m_user_locations[y * m_y_dim + x];
  }
  return m_uav_locations[y * m_y_dim + x];
}

unsigned& Region::operator()(Entity::EntityType type, const Position& pos) {
  if (type == Entity::USER_TYPE) {
    return m_user_locations[(int)pos.y * m_y_dim + (int)pos.x];
  }
  return m_uav_locations[(int)pos.y * m_y_dim + (int)pos.x];
}

unsigned Region::operator()(Entity::EntityType type,
                            const Position& pos) const {
  if (type == Entity::USER_TYPE) {
    return m_user_locations[(int)pos.y * m_y_dim + (int)pos.x];
  }
  return m_uav_locations[(int)pos.y * m_y_dim + (int)pos.x];
}
// end of operator overloads

/*---------------------------------------------------------------------------------
|  Function: spawn_users(int n)
|  Purpose:  place users in the region at a random position, and creates a new 
|            User class object
|  Parameters: n - how many users to spawn in random positions of the region
|  Returns: N/A
*--------------------------------------------------------------------------------*/
void Region::spawn_users(int n) {
  for (unsigned i = 0; i < n; i++) {
    Position random_pos = {double(m_twister() % m_x_dim),
                           double(m_twister() % m_y_dim)};

    ++this->operator()(Entity::USER_TYPE, random_pos);

    User* user = new User(random_pos, this, m_twister() % 5 + 1);

    m_users.push_back(user);
  }
}
/*---------------------------------------------------------------------------------
|  Function: spawn_uavs(int n)
|  Purpose: places uavs in the region at a random position, and creates a new 
|           UAV class object
|  Parameters: number of uavs
|  Returns:  N/A
*--------------------------------------------------------------------------------*/
void Region::spawn_uavs(int n) {
  for (unsigned i = 0; i < n; i++) {
    Position random_pos = {double(m_twister() % m_x_dim),
                           double(m_twister() % m_y_dim)};

    ++this->operator()(Entity::UAV_TYPE, random_pos);

    UAV* uav = new UAV(random_pos, this);

    m_uavs.push_back(uav);
  }
}
/*---------------------------------------------------------------------------------
|  Function: update(unsigned dt)
|  Purpose: The region creates a vector of the user coverage needed in each 
|           subregion. Then, it dispatches the UAVs to the locations with 
|           the most user coverage. Finally, it updates the User and UAVs 
|           and determines the error calculation.
|  Parameters: time
|  Returns: N/A
*--------------------------------------------------------------------------------*/
void Region::update(unsigned dt) {
  std::vector<unsigned> user_discretized = discretize_user(UAV_COVERAGE);

  //displays discretized matrix
  std::cout << "DISCRETIZED" << std::endl;
  for (unsigned i = 0; i < m_x_dim / UAV_COVERAGE; i++) {
    for (unsigned j = 0; j < m_y_dim / UAV_COVERAGE; j++) {
      std::cout << user_discretized[j * m_y_dim / UAV_COVERAGE + i] << " ";
    }
    std::cout << std::endl;
  }

  dispatch_uavs(user_discretized); //sends uavs accordingly

  reset_matrices();

  for (const auto& user : m_users) {
    uint8_t dir = GenDirection();
    user->update(dt, dir);
    this->operator()(Entity::USER_TYPE, user->get_position()) +=
        user->m_usage_level;
  }

  for (const auto& uav : m_uavs) {
    uint8_t dir = GenDirection();
    uav->update(dt, dir);
    ++this->operator()(Entity::UAV_TYPE, uav->get_position());
  }

  double error = determine_error(dt);

  std::cout << "ERROR: " << error << std::endl;
}
/*---------------------------------------------------------------------------------
|  Function: determoine_error()
|  Purpose: for debugging and error detection, the region will calculate 
|           its error based on the amount of users who are not covered 
|           compared to the demand of the network.
|  Parameters: time
|  Returns: double
*--------------------------------------------------------------------------------*/
double Region::determine_error(unsigned dt) {
  unsigned demand = 0;
  for (const auto& user : m_users) {
    demand += user->m_usage_level;
    UAV* nearest_uav = nullptr;
    double nearest_distance = 0;
    for (const auto& uav : m_uavs) {
      double uav_distance =
          Position::Distance(uav->get_position(), user->get_position());
      if (uav_distance <= UAV::m_coverage) {
        if (!nearest_uav) {
          bool attached = uav->attach_user(user, dt);
          nearest_uav = attached ? uav : nullptr;
          nearest_distance = attached ? uav_distance : 0;
        } else {
          if (uav_distance < nearest_distance) {
            bool attached = uav->attach_user(user, dt);
            nearest_uav = attached ? uav : nearest_uav;
            nearest_distance = attached ? uav_distance : nearest_distance;
          }
        }
      }
    }
  }

  unsigned covered = 0;
  for (const auto& uav : m_uavs) {
    covered += uav->get_covered();
  }

  return 1 - (double)covered / demand;
}
/*---------------------------------------------------------------------------------
|  Function: discretize_user(unsigned size)
|  Purpose: creates a matrix based upon UAV coverage 
|  Parameters: UAV_COVERAGE
|  Returns: vector
*--------------------------------------------------------------------------------*/
std::vector<unsigned> Region::discretize_user(unsigned size) {
  std::vector<unsigned> result =
      std::vector<unsigned>(m_x_dim / size * m_y_dim / size);
  std::fill(result.begin(), result.end(), 0);
  for (unsigned block_x = 0; block_x < m_x_dim / size; block_x++) {
    for (unsigned block_y = 0; block_y < m_y_dim / size; block_y++) {
      for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
          result[block_y * m_y_dim / size + block_x] += this->operator()(
              Entity::USER_TYPE, block_x* size + i, block_y * size + j);
        }
      }
    }
  }

  return result;
}
/*---------------------------------------------------------------------------------
|  Function: dispatch_uavs()
|  Purpose: dispatches the closest UAV to the subregion with the most 
|           demand for coverage.
|  Parameters: vector
|  Returns: N/A
*--------------------------------------------------------------------------------*/
void Region::dispatch_uavs(std::vector<unsigned>& discretized) {
  std::vector<unsigned> sorted = discretized;
  std::sort(sorted.begin(), sorted.end());

  unsigned num_uavs = m_uavs.size();
  std::unordered_set<UAV*> dispatched;

  for (unsigned i = 0; i < num_uavs; i++) {
    auto it = std::find(discretized.begin(), discretized.end(), sorted.back());
    sorted.pop_back();

    int index = std::distance(discretized.begin(), it);
    discretized.erase(it);
    int index_y = index / (m_y_dim / UAV_COVERAGE);
    int index_x = index % (m_y_dim / UAV_COVERAGE);

    Position dispatch(index_x, index_y);
    // if (m_dispatch.find(dispatch) != m_dispatch.end()) {
    //   continue;
    // }

    index_x *= UAV_COVERAGE;
    index_y *= UAV_COVERAGE;

    UAV* closest = nullptr;
    double closest_distance = 0;
    for (auto uav : m_uavs) {
      if (dispatched.find(uav) == dispatched.end() && uav->ready()) {
        if (closest == nullptr) {
          closest = uav;
          closest_distance = Position::Distance(uav->get_position(),
                                                Position(index_x, index_y));
        } else {
          double uav_distance = Position::Distance(uav->get_position(),
                                                   Position(index_x, index_y));
          if (uav_distance < closest_distance) {
            closest = uav;
            closest_distance = uav_distance;
          }
        }
      }
    }

    if (closest != nullptr &&
        closest->dispatch(
            Position(index_x + UAV_COVERAGE / 2, index_y + UAV_COVERAGE / 2))) {
      dispatched.insert(closest);
      m_dispatch[dispatch] = closest;
    }

    // for (auto it = m_dispatch.end(); it != m_dispatch.end(); ++it) {
    //   if (it->second == closest && closest->reached()) {
    //     m_dispatch.erase(it);
    //   }
    // }
  }
}
/*---------------------------------------------------------------------------------
|  Function: reset_matrices()
|  Purpose: region is reset with new random user locations
|  Parameters: NONE
|  Returns: N/A
*--------------------------------------------------------------------------------*/
void Region::reset_matrices() {
  if (m_user_locations == nullptr) {
    delete m_user_locations;
  }

  if (m_uav_locations == nullptr) {
    delete m_uav_locations;
  }

  m_user_locations = new unsigned[m_x_dim * m_y_dim];
  m_uav_locations = new unsigned[m_x_dim * m_y_dim];

  std::fill(m_user_locations, m_user_locations + m_x_dim * m_y_dim, 0);
  std::fill(m_uav_locations, m_uav_locations + m_x_dim * m_y_dim, 0);
}
/*---------------------------------------------------------------------------------
|  Function: <<operator()
|  Purpose: printing the matrix
|  Parameters: stream and region
|  Returns: stream
*--------------------------------------------------------------------------------*/
std::ostream& operator<<(std::ostream& stream, const Region& region) {
  for (int i = 0; i < region.m_x_dim; i++) {
    for (int j = 0; j < region.m_y_dim; j++) {
      if (region(Entity::UAV_TYPE, i, j)) {
        stream << "\x1B[31m";
      }
      stream << region(i, j) << " ";
      if (region(Entity::UAV_TYPE, i, j)) {
        stream << "\x1B[37m";
      }
    }
    stream << std::endl;
  }

  return stream;
}
