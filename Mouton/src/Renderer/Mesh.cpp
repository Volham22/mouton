#include "Mesh.h"

namespace Mouton
{

    Mesh::Mesh(std::vector<MeshVertex>& vertices,
            std::vector<unsigned int>& indices,
            std::vector<MeshTexture> textures)
    : m_Indices(indices), m_Vertices(vertices), m_Textures(textures),
      m_VBO(VertexBuffer::CreateVertexBuffer()), m_EBO(ElementBuffer::CreateElementBuffer())
    {
        m_VBO->SetData(&vertices[0], sizeof(MeshVertex) * vertices.size());
        m_VBO->SetLayout({
            { ShaderType::Float3, false },
            { ShaderType::Float2, false },
            { ShaderType::Float3, false }
        });

        m_EBO->SetData(&indices[0], sizeof(unsigned int) * indices.size());
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

        m_VBO->Bind();
        m_EBO->Bind();
    }

    void Mesh::Unbind() const
    {
        for(const MeshTexture& tex : m_Textures)
            tex.second->Unbind();
        
        m_VBO->Unbind();
        m_EBO->Unbind();
    }

} // namespace Mouton
