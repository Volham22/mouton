#ifndef SCENE_H
#define SCENE_H

#include "MoutonPch.h"
#include "Entity.h"
#include "Components.h"

#include "MoutonComponents/OrthographicCameraComponent.h"
#include "MoutonComponents/PythonBehaviourComponent.h"
#include "MoutonComponents/SpriteComponent.h"
#include "Scripting/ElementBehaviour.h"

namespace Mouton
{

    class Scene
    {
    public:
        using SceneComponentData = std::unordered_map<Component::ComponentType, std::unordered_map<std::string, Component*>>;
        Scene() = default;
        ~Scene();

        bool AddEntity(Entity* entity);
        bool RemoveEntity(const std::string& entityName);
        bool AddComponentToEntity(const std::string& entityName, Component::ComponentType type, const std::string& componentName);
        bool AddComponentToEntity(const uint16_t entityId, Component::ComponentType type, const std::string& componentName);
        bool RemoveComponentToEntity(const std::string& entityName, Component::ComponentType type, const std::string& componentName);
        // A new component must be heap allocated. It will be destroyed when needed
        bool AddComponent(Component::ComponentType type, Component* newComponent);
        bool RemoveComponent(Component::ComponentType type, const std::string& componentName);
        std::vector<Entity*> GetEntities();
        std::vector<Component*> GetEntityComponent(const std::string& entityName);
        Component* GetComponentByName(const std::string& name);

        template<typename T>
        void ForEachComponents(T callback)
        {
        }

        template<typename T, typename U, typename... Args>
        void ForEachComponents(T comp, Args... args, U callback)
        {
            if(comp == Component::ComponentType::Any)
            {
                for(auto&[type, components] : m_SceneData)
                {
                    for(auto&[name, comp] : components)
                        callback(*comp);
                }

                return;
            }

            auto& components = m_SceneData[comp];

            for(auto&[name, compo] : components)
                callback((*compo));
            
            ForEachComponents(args..., callback);
        }

        void ForEachEntities(const std::function<void(Entity&)>& callback);

        std::vector<Component*> GetComponents()
        {
            auto res = std::vector<Component*>();
            return res;
        }

        template<typename T, typename... U>
        std::vector<Component*> GetComponents(T t, U... args)
        {
            if(t == Component::ComponentType::Any)
            {
                std::vector<Component*> res;

                for(auto&[_, components] : m_SceneData)
                {
                    for(auto& values : components)
                        res.push_back(values.second);
                }

                return res;
            }

            std::vector<Component*> append;
            for(auto&[name, component] : m_SceneData[t])
                append.push_back(component);
            
            auto&& recVec = GetComponents(args...);
            recVec.insert(recVec.end(), append.begin(), append.end());
            return recVec;
        }

        template<typename Writer>
        void Serialize(Writer& writer) const
        {
            using ComponentType = Component::ComponentType;

            writer.StartObject();

            for(auto&[type, components] : m_SceneData)
            {
                writer.String(Component::TypeToString(type));
                writer.StartArray();

                for(auto&[name, component] : components)
                {
                    writer.StartObject();
                    component->Serialize(writer);

                    switch(type)
                    {
                    // case ComponentType::BehaviourComponent:
                    //     static_cast<ElementBehaviour*>(component)->Serialize(writer);
                    //     break;

                    case ComponentType::OrthographicCamera:
                        static_cast<OrthographicCameraComponent*>(component)->Serialize(writer);
                        break;

                    case ComponentType::PythonBehaviourComponent:
                        static_cast<PythonBehaviourComponent<PythonBinder>*>(component)->Serialize(writer);
                        break;

                    case ComponentType::SpriteComponent:
                        static_cast<SpriteComponent*>(component)->Serialize(writer);
                        break;
                    
                    // default:
                    }

                    writer.EndObject();
                }

                writer.EndArray();
            }

            writer.String("Entities");

            writer.StartArray();
            for(auto&[name, entity] : m_Entities)
            {
                writer.StartObject();

                writer.String(name.c_str());
                writer.Int(entity->GetID());

                writer.EndObject();
            }

            writer.EndArray();
            writer.EndObject();
        }

        static Scene FromJson(const std::string& json);

    private:
        SceneComponentData m_SceneData;
        std::unordered_map<std::string, uint16_t> m_ComponentsReferenceCount;
        std::unordered_map<std::string, Entity*> m_Entities;
        int m_EntityNumber = 0;

        void decComponent(Component::ComponentType type, std::string componentName);

        template<typename Value>
        void BindEntities(const Value& value, Component* component)
        {
            const Value& ids = value["Ids"];

            for(auto it = ids.Begin(); it != ids.End(); it++)
                AddComponentToEntity(it->GetInt(), component->GetComponentType(), component->GetComponentName());
        }
    };

} // namespace Mouton


#endif