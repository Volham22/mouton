#include "ApplicationLayer.h"

#include "imgui.h"

#include "Core/Inputs.h"
#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"

namespace Mouton
{

    RenderLayer::RenderLayer(const char* name)
        : Layer(name), m_Count(10), m_Color({ 1.0f, 1.0f, 1.0f, 1.0f }),
          m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_CameraPosition(0.0f), m_Rotation(0.0f), m_QuadRotation(0.0f),
          m_Texture()
    {
        // Some temporary code here
        RendererContext::InitContext(GraphicAPI::OpenGL);
        Renderer2D::Init();

        m_Texture = Texture2D::CreateTexture("res/texture/error.png");
    }

    void RenderLayer::OnBind()
    {
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_Rotation);
    }

    void RenderLayer::OnUnbind()
    {
    }

    void RenderLayer::OnUpdate()
    {
        // Some rendering stuff will come here ...
        ImGui::Begin("Control texture color !");
            ImGui::Text("Scroll color");
            ImGui::DragFloat4("Color", glm::value_ptr(m_Color), 0.01f, 0.0f, 1.0f);
            ImGui::DragFloat("Rotate", &m_QuadRotation);
            ImGui::DragInt("Quad count", &m_Count);
        ImGui::End();

        ImGui::Begin("Renderer 2D stats");
            ImGui::Text(("Number of drawcalls per frame : " + std::to_string(Renderer2D::GetDrawCallPerFrame())).c_str());
            ImGui::Text(("Number of vertices per frame : " + std::to_string(Renderer2D::GetVerticesAmount())).c_str());
        ImGui::End();

        Renderer2D::BeginScene(m_Camera.GetViewProjectionMatrix());

        for(int i = 0; i < m_Count; i++)
        {
            for(int j = 0; j < m_Count; j++)
                Renderer2D::DrawQuad({ i * 10.0f, j * 10.0f, 0.0f}, { 5.0f, 5.0f }, m_Texture, m_QuadRotation);
        }

        Renderer2D::EndScene();
    }

    bool RenderLayer::OnEvent(Event& event)
    {
        EventSystem::ApplyFunction<WindowCloseEvent>(&event, [](Event& event) -> bool {
            MTN_INFO("On window close ...");
            return true;
        });

        EventSystem::ApplyFunction<WindowFocusEvent>(&event, [](Event& event) -> bool {
            MTN_INFO("On window focus");
            return true;
        });

        EventSystem::ApplyFunction<WindowLostFocusEvent>(&event, [](Event& event) -> bool {
            MTN_INFO("Window lost focus");
            return true;
        });

        EventSystem::ApplyFunction<WindowMovedEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<WindowMovedEvent&>(event);
            MTN_TRACE("On window move");
            return true;
        });

        EventSystem::ApplyFunction<WindowMinimizedEvent>(&event, [](Event & event) -> bool {
            MTN_INFO("On window minimize");
                 return true;
            });

         EventSystem::ApplyFunction<WindowResizeEvent>(&event, [](Event& event) -> bool {
            MTN_INFO("On window resize")
            return true;
        });

        EventSystem::ApplyFunction<KeyPressedEvent>(&event, [this](Event& event) -> bool {
            auto& ev = dynamic_cast<KeyPressedEvent&>(event);

            if(ev.GetCode() == Keys::RIGHT)
                m_CameraPosition.x += 0.5f;
            else if(ev.GetCode() == Keys::LEFT)
                m_CameraPosition.x += -0.5f;
            else if(ev.GetCode() == Keys::UP)
                m_CameraPosition.y += 0.5f;
            else if(ev.GetCode() == Keys::DOWN)
                m_CameraPosition.y += -0.5f;
            else if(ev.GetCode() == Keys::Q)
                m_Rotation += 0.5f;
            else if(ev.GetCode() == Keys::R)
                m_Rotation += -0.5f;

            return true;
        });

        EventSystem::ApplyFunction<KeyMaintainedEvent>(&event, [this](Event& event) -> bool {
            auto& ev = dynamic_cast<KeyMaintainedEvent&>(event);

            if(ev.GetCode() == Keys::RIGHT)
                m_CameraPosition.x += 0.5f;
            else if(ev.GetCode() == Keys::LEFT)
                m_CameraPosition.x += -0.5f;
            else if(ev.GetCode() == Keys::UP)
                m_CameraPosition.y += 0.5f;
            else if(ev.GetCode() == Keys::DOWN)
                m_CameraPosition.y += -0.5f;
            else if(ev.GetCode() == Keys::Q)
                m_Rotation += 0.5f;
            else if(ev.GetCode() == Keys::R)
                m_Rotation += -0.5f;
            return true;
        });

        EventSystem::ApplyFunction<KeyReleasedEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<KeyReleasedEvent&>(event);
            if(ev.GetCode() == Keys::SPACE)
                MTN_INFO("Space key released !");
            return true;
        });

        EventSystem::ApplyFunction<MouseButtonPressedEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<MouseButtonPressedEvent&>(event);
            if(ev.GetCode() == Keys::MOUSE1)
                MTN_INFO("Left button pressed !");
            return true;
        });

        EventSystem::ApplyFunction<MouseButtonMaintainedEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<MouseButtonMaintainedEvent&>(event);
            if(ev.GetCode() == Keys::MOUSE1)
                MTN_INFO("Left button maintained !");
            return true;
        });

        EventSystem::ApplyFunction<MouseButtonReleasedEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<MouseButtonReleasedEvent&>(event);
            if(ev.GetCode() == Keys::MOUSE1)
                MTN_INFO("Left button released !");
            return true;
        });

        EventSystem::ApplyFunction<MouseMovedEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<MouseMovedEvent&>(event);
            //MTN_INFO("Mouse moved");
            return true;
        });

        EventSystem::ApplyFunction<MouseScrolledEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<MouseScrolledEvent&>(event);
            MTN_INFO("Mouse scrolled");
            return true;
        });

        return event.Handled();
    }



} // namespace Mouton
