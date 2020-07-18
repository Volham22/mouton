#include "ImGuiLayer.h"

#include <GLFW/glfw3.h>

#include "Platform/MoutonOpenGLImGui.h"
#include "imgui.h"

namespace Mouton
{

    ImGUILayer::ImGUILayer(void* win, const char* name)
            : Layer(name), m_WindowInstance(static_cast<GLFWwindow*>(win))
    {
        InitMoutonImgui(m_WindowInstance);

        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    }

    void ImGUILayer::OnBind()
    {
        auto& io = ImGui::GetIO();
        int width = 0, height = 0;
        glfwGetWindowSize(m_WindowInstance, &width, &height);
        io.DisplaySize = ImVec2((float)width, (float)height);

        NewImguiMoutonFrame();
    }

    void ImGUILayer::OnUpdate()
    {
    }

    void ImGUILayer::OnUnbind()
    {
        auto& io = ImGui::GetIO();

        RenderImguiMouton();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
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

