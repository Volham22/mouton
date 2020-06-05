#include "ApplicationLayer.h"

#include "imgui.h"

#include "Core/Inputs.h"
#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"

namespace Mouton
{

    RenderLayer::RenderLayer(const char* name)
        : Layer(name), m_Shader(),
          m_CameraDirection(0.0f),
          m_Camera(1280.0f / 720.0f, 45.0f, 20.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, 1000.0f),
          m_CameraController(std::shared_ptr<OrbitalCamera>(&m_Camera))
    {
        // Some temporary code here
        RendererContext::InitContext(GraphicAPI::OpenGL);
        Renderer::InitRenderer();
        Renderer::SetDepthTest(true);

        m_Shader = Shader::CreateShader("res/shaders/3DAnimatedShader.glsl");
        m_Shader->SetUniform("u_Diffuse", 0);
        m_Shader->SetUniform("u_Specular", 1);
        m_Shader->SetUniform("u_Normal", 2);
        m_Shader->SetUniform("u_Height", 3);

        auto loader = ModelLoader::CreateModelLoader("res/models/Man/man.fbx");
        loader->Load();
        m_Model = loader->GetLoadedModel();

    }

    void RenderLayer::OnBind()
    {
        m_Camera.SetPosition(m_CameraDirection);
        m_Shader->SetUniform("u_VP", m_CameraController.GetViewProjectionMatrix());
    }

    void RenderLayer::OnUnbind()
    {
    }

    void RenderLayer::OnUpdate()
    {
        ImGui::Begin("Camera control panel");
            ImGui::DragFloat3("Camera target position", glm::value_ptr(m_CameraDirection), 0.1f);
        ImGui::End();

        auto bonesTransforms = m_Model->GetBonesTransforms();

        for(unsigned int i = 0; i < bonesTransforms->size(); i++)
            m_Shader->SetUniform("u_Bones[" + std::to_string(i) + "]", (*bonesTransforms)[i]);

        ImGui::Begin("Animation");
            ImGui::Text("Manage the animation");

            if(ImGui::Button("Play"))
                m_Model->PlayAnimation("Armature|idle");

            if(ImGui::Button("Stop"))
                m_Model->StopAnimation();

        ImGui::End();

        Renderer::BeginScene();
        m_Shader->Bind();
        m_Model->DrawModel();
        m_Shader->Unbind();
        Renderer::EndScene();
    }

    bool RenderLayer::OnEvent(Event& event)
    {
        EventSystem::ApplyFunction<WindowCloseEvent>(&event, [](Event& event) -> bool {
            MTN_INFO("On window close ...");
            return true;
        });

        // Handle Camera controller event
        m_CameraController.OnEvent(event);

        return event.Handled();
    }



} // namespace Mouton
