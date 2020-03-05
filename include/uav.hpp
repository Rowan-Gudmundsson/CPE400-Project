#pragma once

#include "common.hpp"

class UAV : public Entity {
    public:
        UAV() = default;
        UAV(const Position& pos, Region* region): Entity(pos, region) {}

        EntityType m_type = EntityType::UAV_TYPE;

        void update(unsigned dt) override;

    private:
        static const int m_coverage = UAV_COVERAGE;
        static const int m_bandwidth = UAV_BANDWIDTH;
        static const int m_fuel_capacity = MAX_FUEL;


        int m_fuel_level = m_fuel_capacity;
};
