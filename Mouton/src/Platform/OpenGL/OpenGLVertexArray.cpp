#include "OpenGLVertexArray.h"

#include <glad/glad.h>

static GLenum GetGLType(Mouton::ShaderType type)
{
        switch(type)
        {
        case Mouton::ShaderType::Float:     return GL_FLOAT;
        case Mouton::ShaderType::Float2:    return  GL_FLOAT;
        case Mouton::ShaderType::Float3:    return  GL_FLOAT;
        case Mouton::ShaderType::Float4:    return GL_FLOAT;
        case Mouton::ShaderType::Int:       return GL_INT;
        case Mouton::ShaderType::Int2:      return GL_INT;
        case Mouton::ShaderType::Int3:      return GL_INT;
        case Mouton::ShaderType::Int4:      return GL_INT;
        case Mouton::ShaderType::Mat2:      return GL_FLOAT;
        case Mouton::ShaderType::Mat3:      return GL_FLOAT;
        case Mouton::ShaderType::Mat4:      return GL_FLOAT;
        case Mouton::ShaderType::Bool:      return GL_BOOL;

        default:                            return 0;
        }
}

namespace Mouton
{

    OpenGLVertexArray::OpenGLVertexArray()
        : m_VAOHandle(0)
    {
        glGenVertexArrays(1, &m_VAOHandle);
    }

    void OpenGLVertexArray::Bind()
    {
        glBindVertexArray(m_VAOHandle);
    }

    void OpenGLVertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(VertexBuffer& vb)
    {
        int slot = 0;
        uint64_t offset = 0;

        glBindVertexArray(m_VAOHandle);

        for(auto& elem : vb.GetLayout().GetElements())
        {

            glEnableVertexAttribArray(slot);
            glVertexAttribPointer(
                slot,
                elem.count,
                GetGLType(elem.type),
                elem.normalized,
                vb.GetLayout().GetStride(),
                reinterpret_cast<void*>(offset)
            );

            offset += elem.size;
            slot++;
        }

        glBindVertexArray(0);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_VAOHandle);
    }

} // namespace Mouton
