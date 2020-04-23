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
        Renderer::SetBlending(true);

        s_Renderer2D.m_VAO = VertexArray::CreateVertexArray();
        s_Renderer2D.m_VBO = VertexBuffer::CreateVertexBuffer();
        s_Renderer2D.m_2DRendererShader = Shader::CreateShader("res/shaders/2DRendererShader.glsl");
        s_Renderer2D.m_VP = glm::mat4(1.0f);

        s_Renderer2D.m_VBO->SetLayout({
            { ShaderType::Float4, false },
            { ShaderType::Float2, false },
            { ShaderType::Float4, false },
            { ShaderType::Float,  false }
        });

        s_Renderer2D.m_VAO->AddVertexBuffer(*(s_Renderer2D.m_VBO));
        s_Renderer2D.m_VBO->SetData(nullptr, 6 * MAXQUAD * sizeof(Vertex));
    }

    void Renderer2D::BeginScene(const glm::mat4& camera)
    {
        Renderer::BeginScene();
        s_Renderer2D.m_VP = camera;
        s_Renderer2D.m_BatchData.drawCallPerFrame = 0;
        s_Renderer2D.m_BatchData.verticesAmount = 0;
    }

    void Renderer2D::EndScene()
    {
        Renderer::EndScene();

        if(s_Renderer2D.m_BatchData.quadCount > 0)
            s_Renderer2D.DrawBatch();
    }

    void Renderer2D::DrawQuad(const glm::vec3& quad, const glm::vec2 size, const glm::vec4& color, float rotation)
    {
        int iQuad = s_Renderer2D.m_BatchData.quadCount;

        const glm::vec4 verticesPositions[] = {
            {-0.5f, -0.5f, 0.0f, 1.0f },
            {-0.5f,  -0.5f + size.y, 0.0f, 1.0f },
            { -0.5f + size.x,  -0.5f + size.y, 0.0f, 1.0f },

            {-0.5f, -0.5f, 0.0f, 1.0f },
            { -0.5f + size.x, -0.5f, 0.0f, 1.0f },
            { -0.5f + size.x,  -0.5f + size.y, 0.0f, 1.0f },
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
                s_Renderer2D.m_VP * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
                    glm::translate(glm::mat4(1.0f), quad) * verticesPositions[i],
                texCoords[i],
                color,
                0
            };
        }

        s_Renderer2D.m_BatchData.quadCount += 6;
        s_Renderer2D.m_BatchData.verticesAmount += 6;

        if(s_Renderer2D.m_BatchData.quadCount >= MAXQUAD || s_Renderer2D.m_BatchData.texturesCount >= MAXTEXTURE)
            s_Renderer2D.DrawBatch();
    }

    void Renderer2D::DrawQuad(const glm::vec3& quad, const glm::vec2& size, std::shared_ptr<Texture2D>& texture, float rotation)
    {
        int iQuad = s_Renderer2D.m_BatchData.quadCount;

        glm::vec4 verticesPositions[] = {
            {-0.5f, -0.5f, 0.0f, 1.0f },
            {-0.5f,  -0.5f + size.y, 0.0f, 1.0f },
            { -0.5f + size.x,  -0.5f + size.y, 0.0f, 1.0f },

            {-0.5f, -0.5f, 0.0f, 1.0f },
            { -0.5f + size.x, -0.5f, 0.0f, 1.0f },
            { -0.5f + size.x,  -0.5f + size.y, 0.0f, 1.0f },
        };

        const glm::vec2 texCoords[] = {
            { 0.0f, 0.0f, },
            { 0.0f, 1.0f, },
            { 1.0f, 1.0f, },

            { 0.0f, 0.0f, },
            { 1.0f, 0.0f, },
            { 1.0f, 1.0f, },
        };

        // Check if the texture has been previously used
        int textureIndice = 0;
        for(int i = 1; i < s_Renderer2D.m_BatchData.texturesCount; i++)
        {
            if(texture.get() == s_Renderer2D.m_BatchData.textures[i].get())
            {
                textureIndice = i;
                break;
            }
        }

        // Add the texture if needed
        if(textureIndice == 0)
        {
            s_Renderer2D.m_BatchData.texturesCount++;
            s_Renderer2D.m_BatchData.textures[s_Renderer2D.m_BatchData.texturesCount] = texture;
            textureIndice = s_Renderer2D.m_BatchData.texturesCount;
        }

        for(int i = 0; i < 6; i++)
        {
            s_Renderer2D.m_BatchData.data[iQuad + i] = {
                s_Renderer2D.m_VP * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
                    glm::translate(glm::mat4(1.0f), quad) * verticesPositions[i],
                texCoords[i],
                glm::vec4(1.0f),
                static_cast<float>(textureIndice)
            };
        }

        s_Renderer2D.m_BatchData.quadCount += 6;
        s_Renderer2D.m_BatchData.verticesAmount += 6;

        if(s_Renderer2D.m_BatchData.quadCount >= MAXQUAD || s_Renderer2D.m_BatchData.texturesCount >= MAXTEXTURE)
            s_Renderer2D.DrawBatch();
    }

    int Renderer2D::GetDrawCallPerFrame()
    {
        return s_Renderer2D.m_BatchData.drawCallPerFrame;
    }

    int Renderer2D::GetVerticesAmount()
    {
        return s_Renderer2D.m_BatchData.verticesAmount;
    }

    void Renderer2D::DrawBatch()
    {
        for(int i = 1; i < m_BatchData.texturesCount + 1; i++)
        {
            m_BatchData.textures[i]->Bind(i);
            m_2DRendererShader->SetUniform("u_TextureID[" + std::to_string(i) + "]", i);
        }

        //m_2DRendererShader->SetUniform("u_VP", m_VP);
        m_VBO->SetSubData(&m_BatchData.data[0], 0, sizeof(Vertex) * s_Renderer2D.m_BatchData.quadCount);

        m_VBO->Bind();
        m_VAO->Bind();
        m_2DRendererShader->Bind();
        Renderer::Draw(m_BatchData.quadCount);
        m_2DRendererShader->Unbind();
        m_VBO->Unbind();
        m_VAO->Unbind();

        for(int i = 1; i < m_BatchData.texturesCount + 1; i++)
            s_Renderer2D.m_BatchData.textures[i]->Unbind();

        m_BatchData.quadCount = 0;
        m_BatchData.texturesCount = 0;
        m_BatchData.drawCallPerFrame++;
    }

} // namespace Mouton
