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
        m_ComponentsReferenceCount[componentName] = 0;
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
        
        std::vector<std::pair<Component::ComponentType, Component*>> toDecRef;

        if(m_Entities.find(entityName) == m_Entities.end()) return false;

        for(auto& categories : m_SceneData)
        {
            for(auto&[_, comp] : categories.second)
            {
                auto& entities = comp->GetEntitiesIDs();
                if(entities.find(entity->GetID()) != entities.end())
                {
                    toDecRef.push_back(std::make_pair(categories.first, comp));
                    entities.erase(entity->GetID());
                }
            }

            for(auto[type, comp] : toDecRef)
            {
                if(comp)
                    decComponent(type, comp->GetComponentName());
            }
        }

        delete m_Entities[entityName];
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

    std::vector<Entity*> Scene::GetEntities()
    {
        std::vector<Entity*> entities;
    
        for(auto&[_, entity] : m_Entities)
            entities.push_back(entity);

        return entities;
    }

    std::vector<Component*> Scene::GetEntityComponent(const std::string& entityName)
    {
        std::vector<Component*> components;
        uint32_t entityID = m_Entities[entityName]->GetID();

        for(auto&[type, typeComp] : m_SceneData)
        {
            for(auto&[_, comp] : typeComp)
            {
                auto& compIds = comp->GetEntitiesIDs();

                if(compIds.find(entityID) != compIds.end())
                    components.push_back(comp);
            }
        }

        return components;
    }

    void Scene::decComponent(Component::ComponentType type, std::string componentName)
    {
        if((--m_ComponentsReferenceCount[componentName]) == 0)
        {
            Component* component = m_SceneData[type][componentName];
            delete component;
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
