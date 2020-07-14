#include "Components.h"

namespace Mouton
{

    Component::Component(ComponentType type, const std::string& name)
        : p_Type(type), p_Name(name), p_ComponentID()
    {
    }

    bool Component::AddEntityID(uint32_t entityID)
    {
        if(p_ComponentID.find(entityID) != p_ComponentID.end()) return false;
        
        p_ComponentID.insert(entityID);
        return true;
    }

    bool Component::RemoveEntityID(uint32_t entityID)
    {
        if(p_ComponentID.find(entityID) == p_ComponentID.end()) return false;

        p_ComponentID.erase(entityID);
        return true;
    }

    QuadComponent::QuadComponent(const std::string& name)
        : Component(ComponentType::QuadComponent, name)
    {
    }

} // namespace Mouton
