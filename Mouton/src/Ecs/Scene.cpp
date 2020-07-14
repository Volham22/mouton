#include "Scene.h"

namespace Mouton
{

    bool Scene::AddComponentToEntity(const std::string& entityName, Component::ComponentType type, const std::string& componentName)
    {
        auto& components = m_SceneData[type];
        if(components.find(componentName) == components.end()) return false;

        if(components[componentName]->AddEntityID(m_Entities[entityName]->GetID()))
        {
            m_ComponentsReferenceCount[componentName]++;
            return true;
        }
        else
            return false;
    }

    bool Scene::RemoveComponentToEntity(const std::string& entityName, Component::ComponentType type, const std::string& componentName)
    {
        auto& components = m_SceneData[type];
        if(components.find(componentName) == components.end()) return false;

        if(components[componentName]->RemoveEntityID(m_Entities[entityName]->GetID()))
        {
            decComponent(type, componentName);
            return true;
        }
        else
            return false;
    }

    bool Scene::AddComponent(Component::ComponentType type, Component* newComponent)
    {
        auto& components = m_SceneData[type];
        const std::string& componentName = newComponent->GetComponentName();

        if(components.find(componentName) != components.end())
            return false;

        components[componentName] = newComponent;
        m_ComponentsReferenceCount[componentName]++;
        return true;
    }

    bool Scene::AddEntity(Entity* entity)
    {
        if(m_Entities.find(entity->GetName()) != m_Entities.end()) return false;

        entity->SetID(++m_EntityNumber);
        m_Entities[entity->GetName()] = entity;
        return true;
    }

    bool Scene::RemoveEntity(const std::string& entityName)
    {
        Entity* entity = nullptr;
        if(m_Entities.find(entityName) != m_Entities.end())
            entity = m_Entities[entityName];
        else
            return false;

        if(m_Entities.find(entityName) == m_Entities.end()) return false;

        for(auto& categories : m_SceneData)
        {
            for(auto&[_, comp] : categories.second)
            {
                auto& entities = comp->GetEntitiesIDs();
                if(entities.find(entity->GetID()) != entities.end())
                {
                    decComponent(comp->GetComponentType(), comp->GetComponentName());
                    entities.erase(entity->GetID());
                }
            }
        }

        m_Entities.erase(entityName);
        return true;
    }

    bool Scene::RemoveComponent(Component::ComponentType type, const std::string& componentName)
    {
        if(m_SceneData[type].find(componentName) != m_SceneData[type].end())
        {
            delete m_SceneData[type][componentName];
            m_SceneData[type].erase(componentName);
            // Delete the reference counter
            m_ComponentsReferenceCount.erase(componentName);
            return true;
        }

        return false;
    }

    void Scene::decComponent(Component::ComponentType type, const std::string& componentName)
    {
        if(!(-- m_ComponentsReferenceCount[componentName]))
        {
            delete m_SceneData[type][componentName];
            m_SceneData[type].erase(componentName);
        }
    }

    void Scene::ForEachEntities(const std::function<void(Entity&)>& callback)
    {
        for(auto&[name, entity] : m_Entities)
            callback((*entity));
    }

    Scene::~Scene()
    {
        for(auto& type : m_SceneData)
        {
            for(auto& comp : type.second)
                delete comp.second;
        }

        for(auto& entity : m_Entities)
            delete entity.second;
    }

} // namespace Mouton
