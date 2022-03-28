#ifndef COMPONENT_H
#define COMPONENT_H

#include "MoutonPch.h"

namespace Mouton {

    class Component
    {
      public:

        enum class ComponentType : uint16_t {
            Any = 0,
            SpriteComponent = 1,
            BehaviourComponent = 2,
            PythonBehaviourComponent = 3,
            OrthographicCamera = 4
        };

        Component(ComponentType type, const std::string& name,
                  bool isScriptable = false);
        virtual ~Component() {};

        virtual bool operator==(const Component& other) const;
        virtual bool operator!=(const Component& other) const;
        const std::unordered_set<uint32_t>& GetEntitiesIDs() const
        {
            return p_ComponentID;
        };
        std::unordered_set<uint32_t>& GetEntitiesIDs()
        {
            return p_ComponentID;
        };
        bool AddEntityID(uint32_t entityID);
        bool RemoveEntityID(uint32_t entityID);
        ComponentType GetComponentType() const { return p_Type; };
        const std::string& GetComponentName() const { return p_Name; };
        bool IsScriptable() const { return p_IsScriptable; };

        static const char* TypeToString(ComponentType type);

        template<typename Writer>
        void Serialize(Writer& writer)
        {
            writer.String("Name");
            writer.String(p_Name.c_str());

            writer.String("Ids");
            writer.StartArray();
            for (uint32_t id : p_ComponentID)
                writer.Int(id);
            writer.EndArray();
        }

      protected:
        ComponentType p_Type;
        std::string p_Name;
        std::unordered_set<uint32_t> p_ComponentID;
        bool p_IsScriptable;
    };

} // namespace Mouton

#endif