#ifndef BEHAVIOUR_COMPONENT_H
#define BEHAVIOUR_COMPONENT_H

#include "MoutonPch.h"

#include "Scripting/PythonBehaviourBinder.h"

#include <type_traits>

namespace Mouton
{

    enum class PythonBehaviourType : uint16_t {
        Unknown = 0, SpriteBehaviour = 1, OrthographicCameraBehaviour = 2
    };

    // Python Behaviour Component is here to hold any PythonBinder implementation
    // in order to be a component in the ECS.
    template<typename T>
    struct PythonBehaviourComponent : public Component {
        static_assert(std::is_base_of_v<PythonBinder, T>, "T must implements PythonBinder interface !");

        std::unique_ptr<PythonBinder> pythonBehaviour;

        template<typename... Args>
        PythonBehaviourComponent(const std::string& name, Args... args)
            : Component(Component::ComponentType::PythonBehaviourComponent, name),
              pythonBehaviour(std::make_unique<T>(args...))
        {
        }

        static PythonBehaviourComponent<PythonBinder>& ToPythonBehaviourComponent(Component& comp)
        {
            return static_cast<PythonBehaviourComponent<PythonBinder>&>(comp);
        }

        template<typename Writer>
        void Serialize(Writer& writer)
        {
            writer.String("Type");
            writer.String(pythonBehaviour->GetScriptableName());
            writer.String("ModuleName");
            writer.String(pythonBehaviour->GetModuleName());
        }
    };

} // namespace Mouton


#endif
