#ifndef ELEMENT_BEHAVIOUR_H
#define ELEMENT_BEHAVIOUR_H

#include "MoutonPch.h"

#include "Core/Timestep.h"
#include "Renderer/Layer.h"
#include "Ecs/Components.h"

#include <type_traits>

#define MTN_COMPONENT_TO_BEHAVIOUR(x) static_cast<Mouton::Behaviour<Mouton::Component>&>(x)

namespace Mouton
{

    template<typename T>
    class Behaviour : public Component
    {
        static_assert(std::is_base_of_v<Component, T>, "T must be derived from Mouton::Component !");

    public:
        Behaviour(const std::string& name = "BehaviourComponent")
            : Component(Component::ComponentType::BehaviourComponent, name)
        {
        }

        Behaviour(T* element, const std::string& name = "BehaviourComponent")
            : Component(Component::ComponentType::BehaviourComponent, name), m_Element(element)
        {
        }

        void SetOnSceneBegin(std::function<void(T&)> callback) { m_OnSceneBeginCallback = callback; };
        void SetOnSceneUpdate(std::function<void(T&, Timestep)> callback) { m_OnSceneUpdateCallback = callback; };
        void SetOnSceneEnd(std::function<void(T&)> callback) { m_OnSceneEndCallback = callback; };

        bool DoBegin() { return CallIfExists(m_OnSceneBeginCallback); };
        bool DoUpdate() { return CallIfExists(m_OnSceneUpdateCallback); };
        bool DoEnd() { return CallIfExists(m_OnSceneEndCallback); };

    private:
        T* m_Element = nullptr;

        std::function<void(T&)> m_OnSceneBeginCallback;
        std::function<void(T&)> m_OnSceneUpdateCallback;
        std::function<void(T&)> m_OnSceneEndCallback;

    private:
        bool CallIfExists(std::function<void(T&)>& callback)
        {
            if(!callback) return false;

            callback(*m_Element);
            return true;
        }
    };

} // namespace Mouton


#endif