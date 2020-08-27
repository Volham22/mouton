#ifndef ENGINE_H
#define ENGINE_H

#include "Core/MoutonCore.h"

#include "Renderer/Window.h"
#include "Renderer/LayerManager.h"
#include "ImGuiLayer.h"

#define MOUTON_CORE_INCLUDED Mouton::Application* Mouton::Application::s_Application;

namespace Mouton
{
    
    class Application
    {
    public:
        Application(const WindowProperties& properties);
        Application(Application &app) = delete;
        static void InitApplication();
        static void PushLayer(Layer* layer);
        static void Run();
        static bool ApplicationShouldStop();
        static void SetApplicationShouldStop(bool state = false);
        static void EndApplication();

    private:
        Application();
        void OnInit();
        void RunImpl();
        void PushLayerImpl(Layer* layer);
        bool OnEvent(Event& event);
        bool GetWindowShouldCloseImpl() const { return m_WindowShouldClose; };
        void SetWindowShouldCloseImpl(bool state = false) { m_WindowShouldClose = state; };

    private:
        static Application* s_Application;
        std::unique_ptr<Window> m_WindowInstance;
        LayerManager m_LayerManager;
        ImGUILayer m_ImGuiLayer;
        bool m_WindowShouldClose;
    };

}

#endif
