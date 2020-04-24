#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include "Renderer/Layer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Camera.h"
#include "Renderer/Texture.h"

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
        std::shared_ptr<VertexArray> m_VAO;
        std::shared_ptr<VertexBuffer> m_VBO;
        std::shared_ptr<Texture2D> m_Texture;
        glm::vec3 m_CameraPosition, m_CameraDirection;
        PerspectiveCamera m_Camera;
    };

} // namespace Mouton


#endif