#ifndef OPENGL_BUFFERS_H
#define OPENGL_BUFFERS_H

// Include Pch
#include "Renderer/Buffers.h"

namespace Mouton
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer();
        ~OpenGLVertexBuffer();
        OpenGLVertexBuffer(void* data);

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void SetData(void* data, size_t size) override;
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout;};
        virtual BufferLayout& GetLayout() override { return m_Layout; };

    private:
        BufferLayout m_Layout;
        uint32_t m_OglVboHandle;
    };

} // namespace Mouton


#endif