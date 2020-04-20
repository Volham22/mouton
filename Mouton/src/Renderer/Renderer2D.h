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
        static void BeginScene();
        static void DrawQuad(const glm::vec3& quads, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& quads, const Texture& texture);
        static void EndScene();
    
    private:
        static std::shared_ptr<VertexArray> s_VAO;
        static std::shared_ptr<VertexBuffer> s_VBO;
        static std::shared_ptr<ElementBuffer> s_EBO;
        static std::shared_ptr<Shader> s_ColorShader;
        static std::shared_ptr<Shader> s_TexturedShader;
    };

} // namespace Mouton


#endif