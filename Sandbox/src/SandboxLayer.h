#include "Renderer/Layer.h"

#include "Core/Events/Events.h"

#include "Renderer/Shader.h"
#include "Renderer/Model.h"
#include "Renderer/OrbitalCameraController.h"

class SandboxLayer : public Mouton::Layer
{
public:
    SandboxLayer();

    virtual void OnBind() override;
    virtual void OnUpdate() override;
    virtual void OnUnbind() override;
    virtual bool OnEvent(Mouton::Event& event) override;

private:
        std::shared_ptr<Mouton::Shader> m_Shader;
        std::shared_ptr<Mouton::Model> m_Model;
        glm::vec3 m_CameraDirection;
        Mouton::OrbitalCamera m_Camera;
        Mouton::OrbitalCameraController m_CameraController;
};