#ifndef COMPONENT_H
#define COMPONENT_H

#include "MoutonPch.h"

namespace Mouton
{

    class Component
    {
    public:

        enum class ComponentType : uint16_t {
            UnknownType = 0, QuadComponent = 1 // add it here ...
        };

        Component(ComponentType type, const std::string& name);
        virtual ~Component() {};

        virtual bool operator==(const Component& other) const = 0;
        virtual bool operator!=(const Component& other) const = 0;
        const std::unordered_set<uint32_t>& GetEntitiesIDs() const { return p_ComponentID; };
        std::unordered_set<uint32_t>& GetEntitiesIDs() { return p_ComponentID; };
        bool AddEntityID(uint32_t entityID);
        bool RemoveEntityID(uint32_t entityID);
        ComponentType GetComponentType() const { return p_Type; };
        const std::string& GetComponentName() const {  return p_Name; };

    protected:
        ComponentType p_Type;
        std::string p_Name;
        std::unordered_set<uint32_t> p_ComponentID;
    };

    // TODO: Implement the class
    class QuadComponent : public Component
    {
    public:
        QuadComponent(const std::string& name);

        virtual bool operator==(const Component& other) const override { return true; };
        virtual bool operator!=(const Component& other) const override { return true; };
    };

} // namespace Mouton


#endif