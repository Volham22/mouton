#ifndef OPENGL_VERTEX_ARRAY_H
#define OPENGL_VERTEX_ARRAY_H

#include "Renderer/VertexArray.h"

namespace Mouton
{

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();
        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void AddVertexBuffer(VertexBuffer& vb) override;
    
    private:
        uint32_t m_VAOHandle;
    };

} // namespace Mouton


#endif