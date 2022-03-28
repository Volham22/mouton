#ifndef PYTHON_BEHAVIOUR_H
#define PYTHON_BEHAVIOUR_H

#include "Core/Timestep.h"
#include "MoutonComponents/OrthographicCameraComponent.h"
#include "MoutonComponents/SpriteComponent.h"
#include "MoutonPch.h"

#include <pybind11/embed.h>

namespace Mouton {

    class PythonBinder
    {
      public:
        using ErrorCallback = std::function<void(const std::exception&)>;

        PythonBinder(const std::string& m_ModuleName, const ErrorCallback& cb);

        virtual void OnSceneBegin() = 0;
        virtual void OnSceneUpdate(Timestep delta) = 0;
        virtual void OnSceneEnd() = 0;
        virtual void OnPythonException(const std::exception& e) const = 0;

        virtual const char* GetScriptableName() const = 0;
        virtual Component* GetBoundComponent() const = 0;

        virtual void SetBoundComponent(Component* component) = 0;

        virtual bool LoadScript() = 0;

        bool IsLoaded() const { return p_IsLoaded; }
        virtual const std::string& GetModuleName() const
        {
            return p_ModuleName;
        }
        void SetPythonErrorCallback(const ErrorCallback& cb)
        {
            p_ErrorCallback = cb;
        }

      protected:
        std::string p_ModuleName;
        pybind11::object p_Instance;
        pybind11::module p_Module;
        ErrorCallback p_ErrorCallback;
        bool p_IsLoaded;

      protected:
        void LoadPythonModule(bool reload = false);
    };

    class SpriteComponentScriptable : public PythonBinder
    {
      public:
        SpriteComponentScriptable(const std::string& moduleName,
                                  SpriteComponent* comp,
                                  const ErrorCallback& cb);

        virtual void OnSceneBegin() override;
        virtual void OnSceneUpdate(Timestep delta) override;
        virtual void OnSceneEnd() override;
        virtual void OnPythonException(const std::exception& e) const override;

        virtual const char* GetScriptableName() const override
        {
            return "SpriteComponent";
        }
        virtual Component* GetBoundComponent() const override
        {
            return m_ScriptedComponent;
        }

        virtual void SetBoundComponent(Component* component) override;

        virtual bool LoadScript() override;

      private:
        SpriteComponent* m_ScriptedComponent;

      private:
        void UpdateAttributes();
    };

    class OrthographicCameraComponentScriptable : public PythonBinder
    {
      public:
        OrthographicCameraComponentScriptable(const std::string& moduleName,
                                              OrthographicCameraComponent* comp,
                                              const ErrorCallback& cb);

        virtual void OnSceneBegin() override;
        virtual void OnSceneUpdate(Timestep delta) override;
        virtual void OnSceneEnd() override;
        virtual void OnPythonException(const std::exception& e) const override;

        virtual const char* GetScriptableName() const override
        {
            return "OrthographicCameraComponent";
        }
        virtual Component* GetBoundComponent() const override
        {
            return m_ScriptedComponent;
        }

        virtual void SetBoundComponent(Component* component) override;

        virtual bool LoadScript() override;

      private:
        OrthographicCameraComponent* m_ScriptedComponent;
    };

} // namespace Mouton

#endif
