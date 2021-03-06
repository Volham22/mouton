#ifndef MESH_H
#define MESH_H

#include "MoutonPch.h"

#include "Buffers.h"
#include "Texture.h"
#include "VertexArray.h"

namespace Mouton {

    struct MeshVertex {
        glm::vec3 positions;
        glm::vec2 textureCoords;
        glm::vec3 normal;
        glm::ivec4 bonesID;
        glm::vec4 weight;
    };

    enum TextureType { Diffuse, Specular, Normal, Height };

    using MeshTexture = std::pair<TextureType, std::shared_ptr<Texture2D>>;

    class Mesh
    {
        friend class Node;

      public:
        Mesh(std::vector<MeshVertex>& vertices,
             std::vector<unsigned int>& indices,
             std::vector<MeshTexture> textures, bool animated = false);
        void Bind() const;
        void Unbind() const;
        void Draw() const;

      private:
        std::vector<unsigned int> m_Indices;
        std::vector<MeshVertex> m_Vertices;
        std::vector<MeshTexture> m_Textures;
        std::shared_ptr<VertexBuffer> m_VBO;
        std::shared_ptr<ElementBuffer> m_EBO;
        std::shared_ptr<VertexArray> m_VAO;
    };

} // namespace Mouton

#endif
