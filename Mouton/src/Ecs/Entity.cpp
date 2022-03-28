#include "Entity.h"

namespace Mouton {

    Entity::Entity(const std::string& name, uint32_t id)
        : m_ID(id), m_Name(name)
    {}

    Entity::Entity(const std::string& name) : m_ID(0), m_Name(name) {}

} // namespace Mouton
