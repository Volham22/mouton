#include "GLFWInputs.h"

#include <GLFW/glfw3.h>

namespace Mouton
{

    GLFWInputs::GLFWInputs(GLFWwindow* window)
        : m_Window(window)
    {
    }

    bool GLFWInputs::IsKeyPressedInt(int keycode)
    {
        int status = glfwGetKey(m_Window, keycode);
        return (status == GLFW_PRESS) || (status == GLFW_REPEAT);
    }

} // namespace Mouton
