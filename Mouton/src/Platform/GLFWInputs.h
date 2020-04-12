#ifndef GLFW_INPUTS
#define GLFW_INPUTS

#include "Core/Inputs.h"

struct GLFWwindow;

namespace Mouton
{

    class GLFWInputs : public Inputs
    {
    public:
        GLFWInputs(GLFWwindow* window);
        virtual bool IsKeyPressedInt(int keycode) override;
    
    private:
        GLFWwindow* m_Window;
    };

} // namespace Mouton


#endif