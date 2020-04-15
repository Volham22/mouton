#include "ImGuiLayer.h"

#include <GLFW/glfw3.h>

#include "Platform/MoutonOpenGLImGui.h"
#include "imgui.h"

namespace Mouton
{

    ImGUILayer::ImGUILayer(void* win, const char* name)
            : m_WindowInstance(static_cast<GLFWwindow*>(win)), Layer(name)
    {
        InitMoutonImgui(m_WindowInstance);

        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    }

    void ImGUILayer::OnBind()
    {
        auto& io = ImGui::GetIO();
        int width = 0, height = 0;
        glfwGetWindowSize(m_WindowInstance, &width, &height);
        io.DisplaySize = ImVec2((float)width, (float)height);
    }

    void ImGUILayer::OnUpdate()
    {
        auto& io = ImGui::GetIO();

        NewImguiMoutonFrame();
        ImGui::ShowDemoWindow();
        RenderImguiMouton();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGUILayer::OnUnbind()
    {

    }

    bool ImGUILayer::OnEvent(Event& event)
    {
        return false;
    }

    ImGUILayer::~ImGUILayer()
    {
        DestroyMoutonImgui();
    }

} // namespace Mouton

