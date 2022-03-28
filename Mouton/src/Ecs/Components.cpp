#include "Components.h"

namespace Mouton {

    Component::Component(ComponentType type, const std::string& name,
                         bool isScriptable)
        : p_Type(type), p_Name(name), p_ComponentID(),
          p_IsScriptable(isScriptable)
    {}

    bool Component::AddEntityID(uint32_t entityID)
    {
        if (p_ComponentID.find(entityID) != p_ComponentID.end()) return false;

        p_ComponentID.insert(entityID);
        return true;
    }

    bool Component::RemoveEntityID(uint32_t entityID)
    {
        if (p_ComponentID.find(entityID) == p_ComponentID.end()) return false;

        p_ComponentID.erase(entityID);
        return true;
    }

    bool Component::operator==(const Component& other) const
    {
        return p_ComponentID == other.p_ComponentID;
    }

    bool Component::operator!=(const Component& other) const
    {
        return p_ComponentID != other.p_ComponentID;
    }

    const char* Component::TypeToString(ComponentType type)
    {
        switch (type)
        {
        case ComponentType::Any:
            return "Any";

        case ComponentType::BehaviourComponent:
            return "BehaviourComponent";

        case ComponentType::OrthographicCamera:
            return "OrthographicCamera";

        case ComponentType::PythonBehaviourComponent:
            return "PythonBehaviour";

        case ComponentType::SpriteComponent:
            return "SpriteComponent";

        default:
            return "";
        }
    }

} // namespace Mouton
