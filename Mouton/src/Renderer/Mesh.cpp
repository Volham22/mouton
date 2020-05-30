#include "Mesh.h"

#include "Renderer.h"

namespace Mouton
{

    Mesh::Mesh(std::vector<MeshVertex>& vertices,
            std::vector<unsigned int>& indices,
            std::vector<MeshTexture> textures, bool animated)
    : m_Indices(indices), m_Vertices(vertices), m_Textures(textures),
      m_VBO(VertexBuffer::CreateVertexBuffer()), m_EBO(ElementBuffer::CreateElementBuffer()), m_VAO(VertexArray::CreateVertexArray())
    {
        m_VBO->SetData(&vertices[0], sizeof(MeshVertex) * vertices.size());

        if(animated)
        {
            m_VBO->SetLayout({
                { ShaderType::Float3, false },
                { ShaderType::Float2, false },
                { ShaderType::Float3, false },
                { ShaderType::Int4,   false },
                { ShaderType::Float4,   false },
            });
        }
        else
        {
            m_VBO->SetLayout({
                { ShaderType::Float3, false },
                { ShaderType::Float2, false },
                { ShaderType::Float3, false }
            });
        }

        m_EBO->SetData(&indices[0], sizeof(unsigned int) * indices.size());
        m_VAO->AddVertexBuffer(*m_VBO);
    }

    void Mesh::Bind() const
    {
        for(const MeshTexture& tex : m_Textures)
        {
            switch(tex.first)
            {
            case TextureType::Diffuse:
                tex.second->Bind(0);
                break;
            case TextureType::Specular:
                tex.second->Bind(1);
                break;
            case TextureType::Normal:
                tex.second->Bind(2);
                break;
            case TextureType::Height:
                tex.second->Bind(3);
                break;
            default:
                break;
            }
        }

        m_VAO->Bind();
        m_VBO->Bind();
        m_EBO->Bind();
    }

    void Mesh::Unbind() const
    {
        for(const MeshTexture& tex : m_Textures)
            tex.second->Unbind();

        m_VAO->Unbind();
        m_VBO->Unbind();
        m_EBO->Unbind();
    }

    void Mesh::Draw() const
    {
        Bind();
        Renderer::DrawIndexed(m_EBO->GetCount());
        Unbind();
    }

} // namespace Mouton
