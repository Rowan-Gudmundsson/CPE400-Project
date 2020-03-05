#pragma once

#include "common.hpp"

class User : public Entity {
    public:
        User() = default;
        User(Position pos, Region* region): Entity(pos, region) {}

        EntityType m_type = EntityType::USER_TYPE;

        void update(unsigned dt) override;
    private:
};