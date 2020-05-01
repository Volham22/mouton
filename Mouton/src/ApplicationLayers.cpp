#include "ApplicationLayer.h"

#include "imgui.h"

#include "Core/Inputs.h"
#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"

namespace Mouton
{

    RenderLayer::RenderLayer(const char* name)
        : Layer(name), m_Shader(),
          m_CameraPosition(0.0f), m_CameraDirection({ 1.0f, 0.0f, 0.0f }),
          m_Camera(1280.0f / 720.0f, 45.0f, m_CameraPosition, m_CameraDirection)
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

        auto loader = SceneLoader::CreateSceneLoader("res/models/source/abandoned-brick-house-with-green-wood.obj");
        loader->Load();
        m_Scene = loader->GetLoadedScene();
    }

    void RenderLayer::OnBind()
    {
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetDirection(m_CameraDirection);
        m_Shader->SetUniform("u_VP", m_Camera.GetViewProjectionMatrix());
    }

    void RenderLayer::OnUnbind()
    {
    }

    void RenderLayer::OnUpdate()
    {
        ImGui::Begin("Camera control panel");
            ImGui::DragFloat3("Camera Position", glm::value_ptr(m_CameraPosition), 0.1f);
            ImGui::DragFloat3("Camera Direction", glm::value_ptr(m_CameraDirection), 0.1f);
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
