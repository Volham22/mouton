#ifndef PYTHON_BEHAVIOUR_H
#define PYTHON_BEHAVIOUR_H

#include "MoutonPch.h"
#include "Core/Timestep.h"
#include "MoutonComponents/SpriteComponent.h"
#include "MoutonComponents/OrthographicCameraComponent.h"

#include <pybind11/embed.h>

namespace Mouton
{

    class PythonBinder
    {
    public:
        virtual void OnSceneBegin() = 0;
        virtual void OnSceneUpdate(Timestep delta) = 0;
        virtual void OnSceneEnd() = 0;

        virtual const char* GetScriptableName() const = 0;
        virtual const char* GetModuleName() const = 0;
        virtual Component* GetBoundComponent() const = 0;

        virtual void SetBoundComponent(Component* component) = 0;
    };

    class SpriteComponentScriptable : public PythonBinder
    {
    public:
        SpriteComponentScriptable(const char* moduleName, SpriteComponent* comp);

        virtual void OnSceneBegin() override;
        virtual void OnSceneUpdate(Timestep delta) override;
        virtual void OnSceneEnd()  override;

        virtual const char* GetScriptableName() const override { return "SpriteComponent"; }
        virtual const char* GetModuleName() const override { return m_ModuleName; }
        virtual Component* GetBoundComponent() const override { return m_ScriptedComponent; }

        virtual void SetBoundComponent(Component* component) override;

    private:
        const char* m_ModuleName;
        SpriteComponent* m_ScriptedComponent;
        pybind11::object m_Instance;
    
    private:
        void UpdateAttributes();
    };

    class OrthographicCameraComponentScriptable : public PythonBinder
    {
    public:
        OrthographicCameraComponentScriptable(const char* moduleName,
           OrthographicCameraController* comp);

        virtual void OnSceneBegin() override;
        virtual void OnSceneUpdate(Timestep delta) override;
        virtual void OnSceneEnd()  override;

        virtual const char* GetScriptableName() const override { return "OrthographicCameraComponent"; }
        virtual const char* GetModuleName() const override { return m_ModuleName; }
        virtual Component* GetBoundComponent() const override { return nullptr; }

        virtual void SetBoundComponent(Component* component) override;

    private:
        const char* m_ModuleName;
        pybind11::object m_Instance;
    };

} // namespace Mouton


#endif
