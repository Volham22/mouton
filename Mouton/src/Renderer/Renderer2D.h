#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "MoutonPch.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Buffers.h"
#include "Shader.h"

namespace Mouton
{

    class Renderer2D
    {
    public:
        static void Init();
        static void BeginScene(const glm::mat4& camera);
        static void DrawQuad(const glm::vec3& quads, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& quads, const Texture& texture);
        static void EndScene();
    
    private:
        static const int MAXQUAD = 10000;
        static const int MAXTEXTURE = 8;

        static Renderer2D s_Renderer2D;

        Renderer2D();
        void DrawBatch();

        struct Vertex {
            glm::vec3 positions;
            glm::vec2 texCoords;
            glm::vec4 color;
            int textureID;
        };

        struct RendererData {
            RendererData();
            int quadCount; // number of quads actually in the buffer
            int texturesCount;
            std::array<Vertex, MAXQUAD * 6> data;
            std::array<std::shared_ptr<Texture>, MAXTEXTURE> textures;
        };

        std::shared_ptr<VertexArray> m_VAO;
        std::shared_ptr<VertexBuffer> m_VBO;
        std::shared_ptr<Shader> m_2DRendererShader;
        glm::mat4 m_VP;

        RendererData m_BatchData;
    };

} // namespace Mouton


#endif