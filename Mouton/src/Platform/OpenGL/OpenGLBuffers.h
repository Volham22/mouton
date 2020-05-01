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
        virtual void SetSubData(void* data, size_t begin, size_t end) override;
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout;};
        virtual BufferLayout& GetLayout() override { return m_Layout; };

    private:
        BufferLayout m_Layout;
        uint32_t m_OglVboHandle;
    };

    class OpenGLElementBuffer : public ElementBuffer
    {
    public:
        OpenGLElementBuffer();
        ~OpenGLElementBuffer();

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void SetData(void* data, size_t size) override;
        virtual int GetCount() const override;
    
    private:
        uint32_t m_OglEboHandle;
        size_t m_Size;
    };

} // namespace Mouton


#endif