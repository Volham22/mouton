#ifndef SCENE_H
#define SCENE_H

#include "MoutonPch.h"
#include "Entity.h"
#include "Components.h"

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
        bool RemoveComponentToEntity(const std::string& entityName, Component::ComponentType type, const std::string& componentName);
        // A new component must be heap allocated. It will be destroyed when needed
        bool AddComponent(Component::ComponentType type, Component* newComponent);
        bool RemoveComponent(Component::ComponentType type, const std::string& componentName);
        std::vector<Entity*> GetEntities();
        std::vector<Component*> GetEntityComponent(const std::string& entityName);

        template<typename T>
        void ForEachComponents(T callback)
        {
        }

        template<typename T, typename U, typename... Args>
        void ForEachComponents(U callback, T comp, Args... args)
        {
            auto& components = m_SceneData[comp.GetComponentType()];

            for(auto&[name, comp] : components)
                callback((*comp));
            
            ForEachComponents(callback, args...);
        }

        void ForEachEntities(const std::function<void(Entity&)>& callback);

        std::vector<Component*> GetComponents()
        {
            auto res = std::vector<Component*>();
            return res;
        }

        template<typename T, typename ...U>
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

    private:
        SceneComponentData m_SceneData;
        std::unordered_map<std::string, uint16_t> m_ComponentsReferenceCount;
        std::unordered_map<std::string, Entity*> m_Entities;
        int m_EntityNumber = 0;

        void decComponent(Component::ComponentType type, const std::string& componentName);
    };

} // namespace Mouton


#endif