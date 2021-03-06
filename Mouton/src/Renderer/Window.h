#ifndef WINDOW_H
#define WINDOW_H

#include "MoutonPch.h"

namespace Mouton {

    struct WindowProperties {
        const char* name;
        int windowWidth, windowHeight;

        WindowProperties()
            : name("Mouton"), windowWidth(1280), windowHeight(720)
        {}
        WindowProperties(const char* name, int width, int height)
            : name(name), windowWidth(width), windowHeight(height)
        {}
        WindowProperties(int width, int height)
            : name("Mouton"), windowWidth(width), windowHeight(height)
        {}
    };

    class Window
    {
      public:

        virtual void OnUpdate() = 0;
        virtual void SetEventFunction(std::function<bool(Event& event)> func)
            = 0;

        virtual void EnableVSync(bool enable = true) = 0;
        virtual bool IsVSync() = 0;
        virtual bool WindowShouldClose() const = 0;

        virtual int GetWindowWidth() = 0;
        virtual int GetWindowHeight() = 0;

        virtual void* GetWindowInternalInstance() const = 0;

        static std::unique_ptr<Window>
        CreateWindowInstance(const WindowProperties& properties);
    };

} // namespace Mouton

#endif