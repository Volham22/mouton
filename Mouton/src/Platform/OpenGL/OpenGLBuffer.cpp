#include "OpenGLBuffers.h"

#include <glad/glad.h>

namespace Mouton
{

    OpenGLVertexBuffer::OpenGLVertexBuffer()
        : m_OglVboHandle(0)
    {
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(void* data)
        : m_OglVboHandle(0)
    {
        glGenBuffers(GL_ARRAY_BUFFER, &m_OglVboHandle); // TODO: Error handling here
        glBindBuffer(GL_ARRAY_BUFFER, m_OglVboHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    }

    void OpenGLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_OglVboHandle);
    }

    void OpenGLVertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_OglVboHandle);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(GL_ARRAY_BUFFER, &m_OglVboHandle);
    }

} // namespace Mouton
