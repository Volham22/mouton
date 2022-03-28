#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H

#include "Renderer/Window.h"

struct GLFWwindow;

namespace Mouton {

    class GLFWWindowInstance : public Window
    {
      public:
        GLFWWindowInstance(const WindowProperties& properties);
        ~GLFWWindowInstance();

        virtual void OnUpdate() override;
        virtual void
        SetEventFunction(std::function<bool(Event& event)> func) override;

        virtual void EnableVSync(bool enable = true) override;
        virtual bool IsVSync() override;
        virtual bool WindowShouldClose() const override;

        virtual int GetWindowWidth() override;
        virtual int GetWindowHeight() override;

        virtual void* GetWindowInternalInstance() const override;

      private:
        void OnInit(const WindowProperties& properties);

        GLFWwindow* m_GLFWWindow;
        std::function<bool(Event& event)> m_CallbackFunc;
        bool m_IsVSync;
    };

} // namespace Mouton

#endif