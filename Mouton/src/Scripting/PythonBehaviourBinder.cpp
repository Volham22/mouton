#include "PythonBehaviourBinder.h"

namespace py = pybind11;

namespace Mouton
{

    SpriteComponentScriptable::SpriteComponentScriptable(const char* moduleName, SpriteComponent* comp)
        : m_ModuleName(moduleName), m_ScriptedComponent(comp), m_Instance()
    {
        try
        {
            m_Instance = py::module::import(m_ModuleName).attr(m_ModuleName)();
        }
        catch(const std::exception& e)
        {
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
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
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void SpriteComponentScriptable::UpdateAttributes()
    {
        m_ScriptedComponent->color = py::cast<glm::vec4>(m_Instance.attr("color"));
        m_ScriptedComponent->position = py::cast<glm::vec3>(m_Instance.attr("position"));
        m_ScriptedComponent->scale = py::cast<glm::vec2>(m_Instance.attr("scale"));
        m_ScriptedComponent->rotation = py::cast<float>(m_Instance.attr("rotation"));
    }

    OrthographicCameraComponentScriptable::OrthographicCameraComponentScriptable(const char* moduleName,
            OrthographicCameraComponent* comp)
        : m_ModuleName(moduleName), m_ScriptedComponent(comp), m_Instance()
    {
        try
        {
            m_Instance = py::module::import(m_ModuleName).attr(m_ModuleName)();
        }
        catch(const std::exception& e)
        {
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneBegin()
    {
        try
        {
            m_Instance.attr("OnSceneBegin")();
        }
        catch(std::exception& e)
        {
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneUpdate(Timestep delta)
    {
        try
        {
            m_Instance.attr("OnSceneUpdate")(delta);
        }
        catch(std::exception& e)
        {
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

    void OrthographicCameraComponentScriptable::OnSceneEnd()
    {
        try
        {
            m_Instance.attr("OnSceneEnd")();
        }
        catch(std::exception& e)
        {
            MTN_ERROR("Python script '{0}' threw an exception : {1}", m_ModuleName, e.what());
        }
    }

} // namespace Mouton
