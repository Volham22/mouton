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
        int m_Count;
        glm::vec4 m_Color;
        glm::vec3 m_CameraPosition;
        float m_Rotation, m_QuadRotation;
        OrthographicCamera m_Camera;
        std::shared_ptr<Texture2D> m_Texture;
    };

} // namespace Mouton


#endif