#include "Renderer2D.h"

namespace Mouton
{

    std::shared_ptr<VertexArray> Renderer2D::s_VAO;
    std::shared_ptr<VertexBuffer> Renderer2D::s_VBO;
    std::shared_ptr<ElementBuffer> Renderer2D::s_EBO;
    std::shared_ptr<Shader> Renderer2D::s_ColorShader;
    std::shared_ptr<Shader> Renderer2D::s_TexturedShader;

    void Renderer2D::Init()
    {
        Renderer::InitRenderer();

        s_VAO = VertexArray::CreateVertexArray();
        s_VBO = VertexBuffer::CreateVertexBuffer();
        s_EBO = ElementBuffer::CreateElementBuffer();
        s_ColorShader = Shader::CreateShader("res/shaders/basicShader.glsl");
        s_TexturedShader = Shader::CreateShader("res/shaders/textureShader.glsl");

        // These indices will not change during the whole scene
        unsigned int indices[] = {
            0, 1, 2, 0, 3, 2
        };

        s_EBO->SetData(indices, sizeof(indices));
    }

    void Renderer2D::BeginScene()
    {
        Renderer::BeginScene();
    }

    void Renderer2D::EndScene()
    {
        Renderer::EndScene();
    }

    void Renderer2D::DrawQuad(const glm::vec3& quad, const glm::vec4& color)
    {
        s_VBO->SetLayout({
            { ShaderType::Float3, false }
        });

        float vertices[] = {
            quad.x, quad.y, quad.z,
            quad.x, quad.y + 0.5f, quad.z,
            quad.x + 0.5f, quad.y + 0.5f, quad.z,
            quad.x + 0.5f, quad.y, quad.z
        };

        s_ColorShader->SetUniform("u_Color", color);

        s_VBO->SetData(vertices, sizeof(vertices));
        s_VBO->Bind();
        s_VAO->AddVertexBuffer(*s_VBO);

        s_ColorShader->Bind();
        s_VAO->Bind();
        s_EBO->Bind();
        Renderer::DrawIndexed(6);
        s_VAO->Unbind();
        s_EBO->Unbind();
        s_ColorShader->Unbind();
    }

    void Renderer2D::DrawQuad(const glm::vec3& quads, const Texture& texture)
    {

    }

} // namespace Mouton
