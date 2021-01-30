#include "PythonBehaviourBinder.h"

namespace py = pybind11;

namespace Mouton
{

    SpriteComponentScriptable::SpriteComponentScriptable(const char* moduleName, SpriteComponent* comp,
        const ErrorCallback& cb)
        : m_ModuleName(moduleName), m_ScriptedComponent(comp), m_Instance(),
          m_ErrorCallback(cb), m_IsLoaded(false)
    {
        // try
        // {
        //     m_Instance = py::module::import(m_ModuleName).attr(m_ModuleName)();
        // }
        // catch(const std::exception& e)
        // {
        //     OnPythonException(e);
        //     MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        // }
    }

    void SpriteComponentScriptable::SetBoundComponent(Component* component)
    {
        m_ScriptedComponent = static_cast<SpriteComponent*>(component);
    }

    void SpriteComponentScriptable::OnSceneBegin()
    {
        try
        {
            m_Instance.attr("OnBegin")();
            UpdateAttributes();
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void SpriteComponentScriptable::OnSceneUpdate(Timestep delta)
    {
        try
        {
            m_Instance.attr("OnUpdate")(delta);
            UpdateAttributes();
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void SpriteComponentScriptable::OnSceneEnd()
    {
        try
        {
            m_Instance.attr("OnEnd")();
            UpdateAttributes();
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void SpriteComponentScriptable::OnPythonException(const std::exception& e) const
    {
        m_ErrorCallback(e);
    }

    bool SpriteComponentScriptable::LoadScript()
    {
        try
        {
            m_Instance.dec_ref();
            m_Instance = py::module::import(m_ModuleName).attr(m_ModuleName)();
            m_IsLoaded = true;
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
            m_IsLoaded = false;
        }

        return m_IsLoaded;
    }

    void SpriteComponentScriptable::UpdateAttributes()
    {
        m_ScriptedComponent->color = py::cast<glm::vec4>(m_Instance.attr("color"));
        m_ScriptedComponent->position = py::cast<glm::vec3>(m_Instance.attr("position"));
        m_ScriptedComponent->scale = py::cast<glm::vec2>(m_Instance.attr("scale"));
        m_ScriptedComponent->rotation = py::cast<float>(m_Instance.attr("rotation"));
    }

    OrthographicCameraComponentScriptable::OrthographicCameraComponentScriptable(const char* moduleName,
           OrthographicCameraComponent* comp, const ErrorCallback& cb)
        : m_ScriptedComponent(comp), m_ModuleName(moduleName), m_Instance(),
          m_ErrorCallback(cb), m_IsLoaded(false)
    {
        // try
        // {
        //     // When loading from JSON (serialized scene) comp will be null because it might
        //     // not be loaded yet.
        //     // The method SetBoundComponent will initialize m_Instance once the bound component
        //     // has been loaded.
        //     if(comp)
        //         m_Instance = py::module::import(m_ModuleName).attr(m_ModuleName)(comp->GetCameraControllerInstance());
        // }
        // catch(const std::exception& e)
        // {
        //     OnPythonException(e);
        //     MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        // }
    }

    void OrthographicCameraComponentScriptable::SetBoundComponent(Component* component)
    {
        m_ScriptedComponent = static_cast<OrthographicCameraComponent*>(component);

        // Load the python Instance again because the bound component has changed
        try
        {
            m_Instance.dec_ref();
            m_Instance = py::module::import(m_ModuleName)
                .attr(m_ModuleName)(m_ScriptedComponent->GetCameraControllerInstance());
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneBegin()
    {
        try
        {
            m_Instance.attr("OnBegin")();
        }
        catch(std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneUpdate(Timestep delta)
    {
        try
        {
            m_Instance.attr("OnUpdate")(delta);
        }
        catch(std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneEnd()
    {
        try
        {
            m_Instance.attr("OnEnd")();
        }
        catch(std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnPythonException(const std::exception& e) const
    {
        m_ErrorCallback(e);
    }

    bool OrthographicCameraComponentScriptable::LoadScript()
    {
        try
        {
            m_Instance = py::module::import(m_ModuleName)
                .attr(m_ModuleName)(m_ScriptedComponent->GetCameraControllerInstance());
            m_IsLoaded = true;
        }
        catch(const std::exception& e)
        {
            OnPythonException(e);
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
            m_IsLoaded = false;
        }

        return m_IsLoaded;
    }

} // namespace Mouton
