#include "ApplicationLayer.h"

#include "Core/Inputs.h"
#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"

namespace Mouton
{

    RenderLayer::RenderLayer(const char* name)
        : Layer(name), m_VBO(nullptr), m_Shader(), m_VAO(),
          m_EBO(), m_Texture()
    {
        // Some temporary code here
        RendererContext::InitContext(GraphicAPI::OpenGL);
        Renderer::InitRenderer();

        static float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };

        static unsigned int indices[] = {
            0, 1, 2, 0, 3, 2
        };

        m_VAO = VertexArray::CreateVertexArray();

        m_Shader = Shader::CreateShader("res/shaders/textureShader.glsl");
        m_Shader->SetUniform("u_TexID", 0);

        m_VBO = VertexBuffer::CreateVertexBuffer();
        m_VBO->SetData(vertices, sizeof(vertices));
        m_VBO->Bind();
        m_VBO->SetLayout({
            { ShaderType::Float3, false },
            { ShaderType::Float2, false }
        });

        m_VAO->AddVertexBuffer(*m_VBO);
        m_VBO->Unbind();

        m_EBO = ElementBuffer::CreateElementBuffer();
        m_EBO->SetData(indices, sizeof(indices));

        m_Texture = Texture2D::CreateTexture("res/texture/wood.png");
    }

    void RenderLayer::OnBind()
    {
        
    }

    void RenderLayer::OnUnbind()
    {
    }

    void RenderLayer::OnUpdate()
    {
        // Some rendering stuff will come here ...
        Renderer::BeginScene();
        m_Texture->Bind();
        m_VAO->Bind();
        m_Shader->Bind();
        m_VBO->Bind();
        m_EBO->Bind();
        Renderer::DrawIndexed(6);
        m_EBO->Unbind();
        m_VBO->Unbind();
        m_VAO->Unbind();
        m_Shader->Unbind();
        m_Texture->Unbind();
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

        EventSystem::ApplyFunction<KeyPressedEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<KeyPressedEvent&>(event);
             if(ev.GetCode() == Keys::SPACE)
                MTN_INFO("Space key pressed !");
            
            return true;
        });

        EventSystem::ApplyFunction<KeyMaintainedEvent>(&event, [](Event& event) -> bool {
            auto& ev = dynamic_cast<KeyMaintainedEvent&>(event);
            if(ev.GetCode() == Keys::SPACE)
                MTN_INFO("Space key maintained !");
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
