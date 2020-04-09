#include "GLFWWindow.h"

namespace Mouton
{

    GLFWWindowInstance::GLFWWindowInstance(const WindowProperties& properties)
        : m_GLFWWindow(nullptr), m_CallbackFunc(), m_IsVSync(false)
    {
        OnInit(properties);
    }

    void GLFWWindowInstance::OnUpdate()
    {
        // TEMP
        // glClearColor(0.2, 0.2, 0.2, 1.0);
        // glClear(GL_COLOR_BUFFER_BIT);
        // glfwSwapBuffers(m_GLFWWindow);
    }

    void GLFWWindowInstance::SetEventFunction(std::function<bool(Event& event)>& func)
    {
        m_CallbackFunc = func;
    }

    void GLFWWindowInstance::EnableVSync(bool enable)
    {
        glfwSwapInterval(enable ? 1 : 0);
        m_IsVSync = enable;
    }

    bool GLFWWindowInstance::IsVSync()
    {
        return m_IsVSync;
    }

    int GLFWWindowInstance::GetWindowWidth()
    {
        int res = -1;
        glfwGetWindowSize(m_GLFWWindow, &res, nullptr);
        return res;
    }

    int GLFWWindowInstance::GetWindowHeight()
    {
        int res = -1;
        glfwGetWindowSize(m_GLFWWindow, nullptr, &res);
        return res;
    }

    void GLFWWindowInstance::OnInit(const WindowProperties& properties)
    {
        if(!glfwInit())
        {
            glfwTerminate();
            MTN_FATAL("GLFW init failed !");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_SAMPLES, 4);

        m_GLFWWindow = glfwCreateWindow(
            properties.windowWidth, properties.windowHeight,
            properties.name, nullptr, nullptr);

        if(!m_GLFWWindow)
        {
            glfwTerminate();
            MTN_FATAL("GLFW Window creation failed !");
        }

        glfwMakeContextCurrent(m_GLFWWindow);
    }


} // namespace Mouton
