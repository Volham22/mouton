#include "PythonBehaviourBinder.h"

namespace py = pybind11;

namespace Mouton
{

    PythonBinder::PythonBinder(const std::string& moduleName, const ErrorCallback& cb)
        : p_ModuleName(moduleName), p_Instance(), p_Module(),
          p_ErrorCallback(cb), p_IsLoaded(false)
    {
    }

    void PythonBinder::LoadPythonModule(bool reload)
    {
        if(reload)
            p_Module.reload();
        else
            p_Module = py::module::import(p_ModuleName.c_str());
    }

    SpriteComponentScriptable::SpriteComponentScriptable(const std::string& moduleName, SpriteComponent* comp,
        const ErrorCallback& cb)
        : PythonBinder(moduleName, cb), m_ScriptedComponent(comp)
    {
    }

    void SpriteComponentScriptable::SetBoundComponent(Component* component)
    {
        m_ScriptedComponent = static_cast<SpriteComponent*>(component);
    }

    void SpriteComponentScriptable::OnSceneBegin()
    {
        try
        {
            p_Instance.attr("OnBegin")();
            UpdateAttributes();
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
        }
    }

    void SpriteComponentScriptable::OnSceneUpdate(Timestep delta)
    {
        try
        {
            p_Instance.attr("OnUpdate")(delta);
            UpdateAttributes();
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
        }
    }

    void SpriteComponentScriptable::OnSceneEnd()
    {
        try
        {
            p_Instance.attr("OnEnd")();
            UpdateAttributes();
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
        }
    }

    void SpriteComponentScriptable::OnPythonException(const std::exception& e) const
    {
        p_ErrorCallback(e);
    }

    bool SpriteComponentScriptable::LoadScript()
    {
        try
        {
            LoadPythonModule(p_IsLoaded);
            p_IsLoaded = true;

            p_Instance = p_Module.attr(p_ModuleName.c_str())();
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
            p_IsLoaded = false;
        }

        return p_IsLoaded;
    }

    void SpriteComponentScriptable::UpdateAttributes()
    {
        m_ScriptedComponent->color = py::cast<glm::vec4>(p_Instance.attr("color"));
        m_ScriptedComponent->position = py::cast<glm::vec3>(p_Instance.attr("position"));
        m_ScriptedComponent->scale = py::cast<glm::vec2>(p_Instance.attr("scale"));
        m_ScriptedComponent->rotation = py::cast<float>(p_Instance.attr("rotation"));
    }

    OrthographicCameraComponentScriptable::OrthographicCameraComponentScriptable(const std::string& moduleName,
           OrthographicCameraComponent* comp, const ErrorCallback& cb)
        : PythonBinder(moduleName, cb), m_ScriptedComponent(comp)
    {
        MTN_TRACE("Module name {}", p_ModuleName);
    }

    void OrthographicCameraComponentScriptable::SetBoundComponent(Component* component)
    {
        m_ScriptedComponent = static_cast<OrthographicCameraComponent*>(component);

        // Load the python Instance again because the bound component has changed
        try
        {
            p_Instance = py::module::import(p_ModuleName.c_str())
                .attr(p_ModuleName.c_str())(m_ScriptedComponent->GetCameraControllerInstance());
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneBegin()
    {
        try
        {
            p_Instance.attr("OnBegin")();
        }
        catch(std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneUpdate(Timestep delta)
    {
        try
        {
            p_Instance.attr("OnUpdate")(delta);
        }
        catch(std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneEnd()
    {
        try
        {
            p_Instance.attr("OnEnd")();
        }
        catch(std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnPythonException(const std::exception& e) const
    {
        p_ErrorCallback(e);
    }

    bool OrthographicCameraComponentScriptable::LoadScript()
    {
        try
        {
            LoadPythonModule(p_IsLoaded);
            p_IsLoaded = true;

            p_Instance = p_Module.attr(p_ModuleName.c_str())(m_ScriptedComponent->GetCameraControllerInstance());
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", p_ModuleName, e.what());
            p_IsLoaded = false;
        }

        return p_IsLoaded;
    }

} // namespace Mouton
