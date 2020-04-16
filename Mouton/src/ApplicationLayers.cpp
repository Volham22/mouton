#include "ApplicationLayer.h"

#include "Core/Inputs.h"

#include <glad/glad.h>

#include "Renderer/RendererContext.h"

namespace Mouton
{

    RenderLayer::RenderLayer(const char* name)
        : Layer(name), m_VBO(nullptr) // Temporary
    {
        // Some temporary code here
        RendererContext::InitContext(GraphicAPI::OpenGL);

        static float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
             0.5f,  -0.5f, 0.0f
        };

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        m_VBO = VertexBuffer::CreateVertexBuffer();
        m_VBO->Bind();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);
        m_VBO->Unbind();
        m_VBO->SetData(vertices, sizeof(vertices));
        glBindVertexArray(0);
    }

    void RenderLayer::OnBind()
    {
        glClearColor(0.4, 0.2, 0.2, 1.0);
    }

    void RenderLayer::OnUnbind()
    {
    }

    void RenderLayer::OnUpdate()
    {
        // Some rendering stuff will come here ...
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_VAO);
        m_VBO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_VBO->Unbind();
        glBindVertexArray(0);
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
