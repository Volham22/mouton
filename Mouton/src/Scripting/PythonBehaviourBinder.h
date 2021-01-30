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
        virtual void OnPythonException(const std::exception& e) const = 0;

        virtual const char* GetScriptableName() const = 0;
        virtual const char* GetModuleName() const = 0;
        virtual Component* GetBoundComponent() const = 0;
        virtual bool IsLoaded() const = 0;

        virtual void SetBoundComponent(Component* component) = 0;

        using ErrorCallback = std::function<void(const std::exception&)>;
        virtual void SetPythonErrorCallback(const ErrorCallback& cb) = 0;
        virtual bool LoadScript() = 0;
    };

    class SpriteComponentScriptable : public PythonBinder
    {
    public:
        SpriteComponentScriptable(const char* moduleName, SpriteComponent* comp, const ErrorCallback& cb);

        virtual void OnSceneBegin() override;
        virtual void OnSceneUpdate(Timestep delta) override;
        virtual void OnSceneEnd()  override;
        virtual void OnPythonException(const std::exception& e) const override;

        virtual const char* GetScriptableName() const override { return "SpriteComponent"; }
        virtual const char* GetModuleName() const override { return m_ModuleName; }
        virtual Component* GetBoundComponent() const override { return m_ScriptedComponent; }
        virtual bool IsLoaded() const override { return m_IsLoaded; }

        virtual void SetBoundComponent(Component* component) override;
        virtual void SetPythonErrorCallback(const ErrorCallback& cb) override { m_ErrorCallback = cb; }

        virtual bool LoadScript() override;

    private:
        const char* m_ModuleName;
        SpriteComponent* m_ScriptedComponent;
        pybind11::object m_Instance;
        ErrorCallback m_ErrorCallback;
        bool m_IsLoaded;

    private:
        void UpdateAttributes();
    };

    class OrthographicCameraComponentScriptable : public PythonBinder
    {
    public:
        OrthographicCameraComponentScriptable(const char* moduleName,
           OrthographicCameraComponent* comp, const ErrorCallback& cb);

        virtual void OnSceneBegin() override;
        virtual void OnSceneUpdate(Timestep delta) override;
        virtual void OnSceneEnd()  override;
        virtual void OnPythonException(const std::exception& e) const override;

        virtual const char* GetScriptableName() const override { return "OrthographicCameraComponent"; }
        virtual const char* GetModuleName() const override { return m_ModuleName; }
        virtual Component* GetBoundComponent() const override { return m_ScriptedComponent; }
        virtual bool IsLoaded() const override { return m_IsLoaded; }

        virtual void SetBoundComponent(Component* component) override;
        virtual void SetPythonErrorCallback(const ErrorCallback& cb) override { m_ErrorCallback = cb; }

        virtual bool LoadScript() override;

    private:
        OrthographicCameraComponent* m_ScriptedComponent;
        const char* m_ModuleName;
        pybind11::object m_Instance;
        ErrorCallback m_ErrorCallback;
        bool m_IsLoaded;
    };

} // namespace Mouton


#endif
