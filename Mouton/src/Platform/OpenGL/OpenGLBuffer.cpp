#include "OpenGLBuffers.h"

#include <glad/glad.h>

namespace Mouton {

    OpenGLVertexBuffer::OpenGLVertexBuffer() : m_OglVboHandle(0)
    {
        glGenBuffers(1, &m_OglVboHandle);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(void* data) : m_OglVboHandle(0)
    {
        glGenBuffers(1, &m_OglVboHandle); // TODO: Error handling here
        glBindBuffer(GL_ARRAY_BUFFER, m_OglVboHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    }

    void OpenGLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_OglVboHandle);
    }

    void OpenGLVertexBuffer::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void OpenGLVertexBuffer::SetData(void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_OglVboHandle);
        glBufferData(GL_ARRAY_BUFFER, size, data,
                     !data ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetSubData(void* data, size_t begin, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_OglVboHandle);
        glBufferSubData(GL_ARRAY_BUFFER, begin, size, data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(GL_ARRAY_BUFFER, &m_OglVboHandle);
    }

    OpenGLElementBuffer::OpenGLElementBuffer() : m_OglEboHandle(0), m_Size(0)
    {
        glGenBuffers(1, &m_OglEboHandle);
    }

    void OpenGLElementBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OglEboHandle);
    }

    void OpenGLElementBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLElementBuffer::SetData(void* data, size_t size)
    {
        m_Size = size;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OglEboHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    int OpenGLElementBuffer::GetCount() const
    {
        return m_Size / sizeof(uint32_t);
    }

    OpenGLElementBuffer::~OpenGLElementBuffer()
    {
        glDeleteBuffers(1, &m_OglEboHandle);
    }

} // namespace Mouton
