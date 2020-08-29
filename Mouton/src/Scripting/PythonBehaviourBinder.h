#ifndef PYTHON_BEHAVIOUR_H
#define PYTHON_BEHAVIOUR_H

#include "MoutonPch.h"
#include "Core/Timestep.h"
#include "MoutonComponents/SpriteComponent.h"

#include <pybind11/embed.h>

namespace Mouton
{

    class PythonBinder
    {
    public:
        virtual void OnSceneBegin() = 0;
        virtual void OnSceneUpdate(Timestep delta) = 0;
        virtual void OnSceneEnd() = 0;
    };

    class SpriteComponentScriptable : public PythonBinder
    {
    public:
        SpriteComponentScriptable(const char* moduleName, SpriteComponent* comp);

        virtual void OnSceneBegin() override;
        virtual void OnSceneUpdate(Timestep delta) override;
        virtual void OnSceneEnd()  override;
    
    private:
        const char* m_ModuleName;
        SpriteComponent* m_ScriptedComponent;
        pybind11::object m_Instance;
    
    private:
        void UpdateAttributes();
    };

} // namespace Mouton


#endif