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
          m_Camera(1280.0f / 720.0f, 45.0f, 2.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, 200.0f),
          m_Horizontal(0.0f), m_Vertical(0.0f), m_Distance(5.0f)
    {
        // Some temporary code here
        RendererContext::InitContext(GraphicAPI::OpenGL);
        Renderer::InitRenderer();
        Renderer::SetDepthTest(true);

        m_Shader = Shader::CreateShader("res/shaders/3DShader.glsl");
        m_Shader->SetUniform("u_Diffuse", 0);
        m_Shader->SetUniform("u_Specular", 1);
        m_Shader->SetUniform("u_Normal", 2);
        m_Shader->SetUniform("u_Height", 3);

        auto loader = SceneLoader::CreateSceneLoader("res/models/Cat/cat.obj");
        loader->Load();
        m_Scene = loader->GetLoadedScene();
    }

    void RenderLayer::OnBind()
    {
        m_Camera.SetPosition(m_CameraDirection);
        m_Camera.Orbit(m_Horizontal, m_Vertical, m_Distance);
        m_Shader->SetUniform("u_VP", m_Camera.GetViewProjectionMatrix());
    }

    void RenderLayer::OnUnbind()
    {
    }

    void RenderLayer::OnUpdate()
    {
        ImGui::Begin("Camera control panel");
            ImGui::DragFloat("Camera distance", &m_Distance, 0.1f);
            ImGui::DragFloat("Camera Horizontal", &m_Horizontal, 0.1f);
            ImGui::DragFloat("Camera Vertical", &m_Vertical, 0.1f);
            ImGui::DragFloat3("Camera target position", glm::value_ptr(m_CameraDirection), 0.1f);
        ImGui::End();


        Renderer::BeginScene();
        m_Shader->Bind();
        m_Scene->DrawScene();
        m_Shader->Unbind();
        Renderer::EndScene();
    }

    bool RenderLayer::OnEvent(Event& event)
    {
        EventSystem::ApplyFunction<WindowCloseEvent>(&event, [](Event& event) -> bool {
            MTN_INFO("On window close ...");
            return true;
        });
        return event.Handled();
    }



} // namespace Mouton
