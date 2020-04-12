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
        glfwPollEvents();
    }

    void GLFWWindowInstance::SetEventFunction(std::function<bool(Event& event)> func)
    {
        m_CallbackFunc = func;

        // Workaround to retrieve callback from lambdas
        glfwSetWindowUserPointer(m_GLFWWindow, &m_CallbackFunc);

        // Set GLFW Event Callback
        glfwSetWindowIconifyCallback(m_GLFWWindow, [](GLFWwindow* win, int iconified) {
            if(iconified)
            {
                auto funcPtr = reinterpret_cast<std::function<bool(Event& event)>*>(glfwGetWindowUserPointer(win));
                auto& func = *funcPtr;

                WindowMinimizedEvent ev;
                func(ev);
            }
        });

        glfwSetWindowFocusCallback(m_GLFWWindow, [](GLFWwindow* win, int focused) {
            auto funcPtr = reinterpret_cast<std::function<bool(Event& event)>*>(glfwGetWindowUserPointer(win));
            auto& func = *funcPtr;

            if(focused)
            {
                WindowFocusEvent ev;
                func(ev);
            }
            else
            {
                WindowLostFocusEvent ev;
                func(ev);
            }
        });

        glfwSetWindowPosCallback(m_GLFWWindow, [](GLFWwindow* win, int x, int y) {
            auto funcPtr = reinterpret_cast<std::function<bool(Event& event)>*>(glfwGetWindowUserPointer(win));
            auto& func = *funcPtr;

            WindowMovedEvent ev = WindowMovedEvent(x, y);
            func(ev);
        });

        glfwSetFramebufferSizeCallback(m_GLFWWindow, [](GLFWwindow* win, int width, int height) {
            auto funcPtr = reinterpret_cast<std::function<bool(Event& event)>*>(glfwGetWindowUserPointer(win));
            auto& func = *funcPtr;

            WindowResizeEvent ev = WindowResizeEvent(width, height);
            func(ev);
        });

        glfwSetWindowCloseCallback(m_GLFWWindow, [](GLFWwindow* win) {
            auto funcPtr = reinterpret_cast<std::function<bool(Event& event)>*>(glfwGetWindowUserPointer(win));
            auto& func = *funcPtr;

            WindowCloseEvent ev;
            func(ev);
        });

        glfwSetKeyCallback(m_GLFWWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
            auto funcPtr = reinterpret_cast<std::function<bool(Event& event)>*>(glfwGetWindowUserPointer(win));
            auto& func = *funcPtr;

            if(action == GLFW_PRESS)
            {
                KeyPressedEvent ev = KeyPressedEvent(key);
                func(ev);
            }
            else if(action == GLFW_REPEAT)
            {
                KeyMaintainedEvent ev = KeyMaintainedEvent(key);
                func(ev);
            }
            else if(action == GLFW_RELEASE)
            {
                KeyReleasedEvent ev = KeyReleasedEvent(key);
                func(ev);
            }
            else
                MTN_WARN("Unknown key action from GLFW !");

        });

        glfwSetMouseButtonCallback(m_GLFWWindow, [](GLFWwindow* win, int key, int action, int mods) {
            auto funcPtr = reinterpret_cast<std::function<bool(Event& event)>*>(glfwGetWindowUserPointer(win));
            auto& func = *funcPtr;

            if(action == GLFW_PRESS)
            {
                MouseButtonPressedEvent ev = MouseButtonPressedEvent(key);
                func(ev);
            }
            else if(action == GLFW_REPEAT)
            {
                MouseButtonMaintainedEvent ev = MouseButtonMaintainedEvent(key);
                func(ev);
            }
            else if(action == GLFW_RELEASE)
            {
                MouseButtonReleasedEvent ev = MouseButtonReleasedEvent(key);
                func(ev);
            }
            else
                MTN_WARN("Unknown key action from GLFW !");

        });
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

    void* GLFWWindowInstance::GetWindowInternalInstance() const
    {
        return static_cast<void*>(m_GLFWWindow);
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

        // Set GLFW Error callback
        glfwSetErrorCallback([](int error, const char* message) {
            MTN_ERROR(message);
        });

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
