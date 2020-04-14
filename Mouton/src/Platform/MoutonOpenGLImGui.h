#ifndef MTN_OPENGL_IMGUI_H
#define MTN_OPENGL_IMGUI_H


// Includes required implementation files from imgui
#include "imgui.h"
#include "imguiImplementation/imgui_impl_glfw.h"
#include "imguiImplementation/imgui_impl_opengl3.h"

namespace Mouton
{
    /*
     * All these functions wraps needed ImGui and ImGui Mouton Implementation calls
     * They must be used instead of legacy ImGui calls like
     * ImGui::NewFrame(), ImGui::Render() ...
     */
    void InitMoutonImgui(GLFWwindow* win);
    void DestroyMoutonImgui();
    void NewImguiMoutonFrame();
    void RenderImguiMouton();

} // namespace Mouton


#endif