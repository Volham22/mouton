#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include "Renderer/Layer.h"
#include "Renderer/Shader.h"
#include "Renderer/OrbitalCameraController.h"
#include "Renderer/Scene.h"

struct GLFWwindow;

namespace Mouton
{

    class RenderLayer : public Layer
    {
    public:
        RenderLayer(const char* name = "RenderLayer");
        virtual void OnBind() override;
        virtual void OnUpdate() override;
        virtual void OnUnbind() override;
        virtual bool OnEvent(Event& event) override;
    
    private:
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Scene> m_Scene;
        glm::vec3 m_CameraDirection;
        OrbitalCamera m_Camera;
        OrbitalCameraController m_CameraController;
    };

} // namespace Mouton


#endif