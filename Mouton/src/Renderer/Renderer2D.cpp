#include "Renderer2D.h"

#include <glad/glad.h>

namespace Mouton
{

    Renderer2D Renderer2D::s_Renderer2D;

    Renderer2D::RendererData::RendererData()
        : quadCount(0), texturesCount(0), data(), textures()
    {
    }

    Renderer2D::Renderer2D()
        : m_VAO(), m_VBO(), m_2DRendererShader()
    {
    }

    void Renderer2D::Init()
    {
        Renderer::InitRenderer();

        s_Renderer2D.m_VAO = VertexArray::CreateVertexArray();
        s_Renderer2D.m_VBO = VertexBuffer::CreateVertexBuffer();
        s_Renderer2D.m_2DRendererShader = Shader::CreateShader("res/shaders/2DRendererShader.glsl");
        s_Renderer2D.m_VP = glm::mat4(1.0f);

        s_Renderer2D.m_VBO->SetLayout({
            { ShaderType::Float3, false },
            { ShaderType::Float2, false },
            { ShaderType::Float4, false },
            { ShaderType::Int,    false }
        });

        s_Renderer2D.m_VAO->AddVertexBuffer(*(s_Renderer2D.m_VBO));
        s_Renderer2D.m_VBO->SetData(nullptr, 6 * MAXQUAD * sizeof(Vertex));
    }

    void Renderer2D::BeginScene(const glm::mat4& camera)
    {
        Renderer::BeginScene();
        s_Renderer2D.m_VP = camera;
    }

    void Renderer2D::EndScene()
    {
        Renderer::EndScene();

        if(s_Renderer2D.m_BatchData.quadCount > 0)
            s_Renderer2D.DrawBatch();
    }

    void Renderer2D::DrawQuad(const glm::vec3& quad, const glm::vec4& color)
    {
        int iQuad = s_Renderer2D.m_BatchData.quadCount;

        const glm::vec3 verticesPositions[] = {
            {-0.5f, -0.5f, 0.0f },
            {-0.5f,  0.5f, 0.0f },
            { 0.5f,  0.5f, 0.0f },

            {-0.5f, -0.5f, 0.0f },
            { 0.5f, -0.5f, 0.0f },
            { 0.5f,  0.5f, 0.0f },
        };

        const glm::vec2 texCoords[] = {
            { 0.0f, 0.0f, },
            { 0.0f, 1.0f, },
            { 1.0f, 1.0f, },

            { 0.0f, 0.0f, },
            { 1.0f, 0.0f, },
            { 1.0f, 1.0f, },
        };

        for(int i = 0; i < 6; i++)
        {
            s_Renderer2D.m_BatchData.data[iQuad + i] = {
                verticesPositions[i],
                texCoords[i],
                color,
                0
            };
        }

        s_Renderer2D.m_BatchData.quadCount += 6;

        if(s_Renderer2D.m_BatchData.quadCount >= MAXQUAD || s_Renderer2D.m_BatchData.texturesCount >= MAXTEXTURE)
            s_Renderer2D.DrawBatch();
    }

    void Renderer2D::DrawQuad(const glm::vec3& quads, const Texture& texture)
    {

    }

    void Renderer2D::DrawBatch()
    {
        m_2DRendererShader->SetUniform("u_VP", m_VP);
        m_VBO->SetSubData(&m_BatchData.data[0], 0, sizeof(Vertex) * s_Renderer2D.m_BatchData.quadCount);

        m_VBO->Bind();
        m_VAO->Bind();
        m_2DRendererShader->Bind();
        Renderer::Draw(m_BatchData.quadCount);
        m_2DRendererShader->Unbind();
        m_VBO->Unbind();
        m_VAO->Unbind();

        m_BatchData.quadCount = 0;
        m_BatchData.texturesCount = 0;
    }

} // namespace Mouton
