#include "MoutonOpenGLImGui.h"

#include "MoutonPch.h"

namespace Mouton
{
    void InitMoutonImgui(GLFWwindow* win)
    {
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(win, false);
        ImGui_ImplOpenGL3_Init("#version 130");

        if(!IMGUI_CHECKVERSION())
            MTN_WARN("Imgui version check failed !");


        ImGui::StyleColorsDark();
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
