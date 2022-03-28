#include "Scene.h"

#include <rapidjson/document.h>

#include "Core/Utils/StringHash.h"

namespace Mouton {

    bool Scene::AddComponentToEntity(const std::string& entityName,
                                     Component::ComponentType type,
                                     const std::string& componentName)
    {
        auto& components = m_SceneData[type];
        if (components.find(componentName) == components.end()) return false;

        if (components[componentName]->AddEntityID(
                m_Entities[entityName]->GetID()))
        {
            m_ComponentsReferenceCount[componentName]++;
            return true;
        } else
            return false;
    }

    bool Scene::AddComponentToEntity(const uint16_t entityId,
                                     Component::ComponentType type,
                                     const std::string& componentName)
    {
        auto& components = m_SceneData[type];
        if (components.find(componentName) == components.end()) return false;

        if (components[componentName]->AddEntityID(entityId))
        {
            m_ComponentsReferenceCount[componentName]++;
            return true;
        } else
            return false;
    }

    bool Scene::RemoveComponentToEntity(const std::string& entityName,
                                        Component::ComponentType type,
                                        const std::string& componentName)
    {
        auto& components = m_SceneData[type];
        if (components.find(componentName) == components.end()) return false;

        if (components[componentName]->RemoveEntityID(
                m_Entities[entityName]->GetID()))
        {
            decComponent(type, componentName);
            return true;
        } else
            return false;
    }

    bool Scene::AddComponent(Component::ComponentType type,
                             Component* newComponent)
    {
        auto& components = m_SceneData[type];
        const std::string& componentName = newComponent->GetComponentName();

        if (components.find(componentName) != components.end()) return false;

        components[componentName] = newComponent;
        m_ComponentsReferenceCount[componentName] = 0;
        return true;
    }

    bool Scene::AddEntity(Entity* entity)
    {
        if (m_Entities.find(entity->GetName()) != m_Entities.end())
            return false;

        entity->SetID(++m_EntityNumber);
        m_Entities[entity->GetName()] = entity;
        return true;
    }

    bool Scene::RemoveEntity(const std::string& entityName)
    {
        Entity* entity = nullptr;
        if (m_Entities.find(entityName) != m_Entities.end())
            entity = m_Entities[entityName];
        else
            return false;

        std::vector<std::pair<Component::ComponentType, Component*>> toDecRef;

        if (m_Entities.find(entityName) == m_Entities.end()) return false;

        for (auto& categories : m_SceneData)
        {
            for (auto& [_, comp] : categories.second)
            {
                auto& entities = comp->GetEntitiesIDs();
                if (entities.find(entity->GetID()) != entities.end())
                {
                    toDecRef.push_back(std::make_pair(categories.first, comp));
                    entities.erase(entity->GetID());
                }
            }

            for (auto [type, comp] : toDecRef)
            {
                if (comp) decComponent(type, comp->GetComponentName());
            }
        }

        delete m_Entities[entityName];
        m_Entities.erase(entityName);
        return true;
    }

    bool Scene::RemoveComponent(Component::ComponentType type,
                                const std::string& componentName)
    {
        if (m_SceneData[type].find(componentName) != m_SceneData[type].end())
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

        for (auto& [_, entity] : m_Entities)
            entities.push_back(entity);

        return entities;
    }

    std::vector<Component*>
    Scene::GetEntityComponent(const std::string& entityName)
    {
        std::vector<Component*> components;
        uint32_t entityID = m_Entities[entityName]->GetID();

        for (auto& [type, typeComp] : m_SceneData)
        {
            for (auto& [_, comp] : typeComp)
            {
                auto& compIds = comp->GetEntitiesIDs();

                if (compIds.find(entityID) != compIds.end())
                    components.push_back(comp);
            }
        }

        return components;
    }

    Component* Scene::GetComponentByName(const std::string& name)
    {
        for (auto& [_, components] : m_SceneData)
        {
            if (auto it = components.find(name); it != components.end())
                return it->second;
        }

        return nullptr;
    }

    void Scene::decComponent(Component::ComponentType type,
                             std::string componentName)
    {
        if ((--m_ComponentsReferenceCount[componentName]) == 0)
        {
            Component* component = m_SceneData[type][componentName];
            delete component;
            m_SceneData[type].erase(componentName);
        }
    }

    void Scene::ForEachEntities(const std::function<void(Entity&)>& callback)
    {
        for (auto& [name, entity] : m_Entities)
            callback((*entity));
    }

    std::shared_ptr<Scene> Scene::FromJson(const std::string& json)
    {
        rapidjson::Document document;
        document.Parse(json.c_str());
        auto scene = std::make_shared<Scene>();

        constexpr size_t HASH_SPRITE_COMPONENT
            = Utils::StringHash::HashString("SpriteComponent");
        constexpr size_t HASH_BEHAVIOUR_COMPONENT
            = Utils::StringHash::HashString("BehaviourComponent");
        constexpr size_t HASH_PYTHONBEHAVIOUR_COMPONENT
            = Utils::StringHash::HashString("PythonBehaviour");
        constexpr size_t HASH_ORTHOGRAPHIC_CAMERA
            = Utils::StringHash::HashString("OrthographicCamera");
        constexpr size_t HASH_ENTIIES
            = Utils::StringHash::HashString("Entities");

        const auto& entities = document["Entities"].GetArray();

        for (auto& val : entities)
        {
            Entity* entity = nullptr;

            for (auto it = val.MemberBegin(); it != val.MemberEnd(); it++)
                entity = new Entity(it->name.GetString(), it->value.GetInt());

            scene->AddEntity(entity);
        }

        for (auto it = document.MemberBegin(); it != document.MemberEnd(); it++)
        {
            auto& value = it->value;
            size_t hashName = Utils::StringHash::HashString(
                std::string(it->name.GetString()));

            for (auto objIt = value.Begin(); objIt != value.End(); objIt++)
            {
                const auto& objValue = objIt->GetObject();

                switch (hashName)
                {
                case HASH_ENTIIES:
                    continue;

                case HASH_SPRITE_COMPONENT: {
                    Component* comp = SpriteComponent::LoadJson(objValue);
                    scene->AddComponent(
                        Component::ComponentType::SpriteComponent, comp);
                    scene->BindEntities(objValue, comp);
                    break;
                }

                case HASH_BEHAVIOUR_COMPONENT: {
                    Component* comp = SpriteComponent::LoadJson(objValue);
                    scene->AddComponent(
                        Component::ComponentType::BehaviourComponent, comp);
                    scene->BindEntities(objValue, comp);
                    break;
                }

                case HASH_PYTHONBEHAVIOUR_COMPONENT: {
                    Component* comp
                        = PythonBehaviourComponent<PythonBinder>::LoadJson(
                            objValue);
                    scene->AddComponent(
                        Component::ComponentType::PythonBehaviourComponent,
                        comp);
                    scene->BindEntities(objValue, comp);
                    break;
                }

                case HASH_ORTHOGRAPHIC_CAMERA: {
                    Component* comp
                        = OrthographicCameraComponent::LoadJson(objValue);
                    scene->AddComponent(
                        Component::ComponentType::OrthographicCamera, comp);
                    scene->BindEntities(objValue, comp);
                    break;
                }

                default:
                    MTN_ERROR("Failed to determine type {0} with hash {1}",
                              it->name.GetString(), hashName);
                }
            }
        }

        // Bind scritpted components to python behaviours if any
        if (document.HasMember("PythonBehaviour"))
        {
            const auto& pythonBehaviours
                = document["PythonBehaviour"].GetArray();

            for (auto& val : pythonBehaviours)
            {
                if (val["BoundComponent"].IsNull()) continue;

                std::string name = val["Name"].GetString();
                PythonBehaviourComponent<PythonBinder>* pythonBehaviour
                    = static_cast<PythonBehaviourComponent<PythonBinder>*>(
                        scene->GetComponentByName(name));

                std::string boundName = val["BoundComponent"].GetString();
                Component* boundComponent
                    = scene->GetComponentByName(boundName);

                pythonBehaviour->pythonBehaviour->SetBoundComponent(
                    boundComponent);
            }
        }

        return scene;
    }

    Scene::~Scene()
    {
        for (auto& type : m_SceneData)
        {
            for (auto& comp : type.second)
                delete comp.second;
        }

        for (auto& entity : m_Entities)
            delete entity.second;
    }

} // namespace Mouton
