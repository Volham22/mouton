#include "MoutonOpenGLImGui.h"

#include "MoutonPch.h"

namespace Mouton {
    void InitMoutonImgui(GLFWwindow* win)
    {
        ImGui::CreateContext();

        if (!IMGUI_CHECKVERSION()) MTN_WARN("Imgui version check failed !");

        auto& io = ImGui::GetIO();
        ImGui::StyleColorsClassic();

        // Enable some flags
        // Mouton support ImGui docking and viewports
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL(win, false);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void DestroyMoutonImgui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void NewImguiMoutonFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void RenderImguiMouton()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

} // namespace Mouton
