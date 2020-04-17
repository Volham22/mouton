#include "Buffers.h"

#include "RendererContext.h"

#include "Platform/OpenGL/OpenGLBuffers.h"

namespace Mouton
{

    BufferElement::BufferElement(ShaderType type, bool normalized)
        : type(type), normalized(normalized), size(GetSize(type)), count(GetCount(type))
    {
    }

    int BufferElement::GetSize(ShaderType type) const
    {
        switch(type)
        {
        case ShaderType::Float:    return sizeof(float);
        case ShaderType::Float2:   return  2 * sizeof(float);
        case ShaderType::Float3:   return  3 * sizeof(float);
        case ShaderType::Float4:   return 4 * sizeof(float);
        case ShaderType::Int:      return sizeof(int);
        case ShaderType::Int2:     return 2 * sizeof(int);
        case ShaderType::Int3:     return 3 * sizeof(int);
        case ShaderType::Int4:     return 4 * sizeof(int);
        case ShaderType::Mat2:     return 2 * 2 * sizeof(float);
        case ShaderType::Mat3:     return 3* 3 * sizeof(float);
        case ShaderType::Mat4:     return 4 * 4 * sizeof(float);
        case ShaderType::Bool:     return sizeof(bool);

        default:                   return -1;
        }
    }

    int BufferElement::GetCount(ShaderType type) const
    {
        switch(type)
        {
        case ShaderType::Float:    return 1;
        case ShaderType::Float2:   return 2;
        case ShaderType::Float3:   return 3;
        case ShaderType::Float4:   return 4;
        case ShaderType::Int:      return 1;
        case ShaderType::Int2:     return 2;
        case ShaderType::Int3:     return 3;
        case ShaderType::Int4:     return 4;
        case ShaderType::Mat2:     return 1;
        case ShaderType::Mat3:     return 1;
        case ShaderType::Mat4:     return 1;
        case ShaderType::Bool:     return 1;

        default:                   return -1;
        }
    }

    BufferLayout::BufferLayout()
        : m_BufferElements()
    {
    }

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elem)
        : m_BufferElements(elem)
    {
    }

    int BufferLayout::GetStride()
    {
        int stride = 0;
        for(BufferElement& elem : m_BufferElements)
            stride += elem.size;

        return stride;
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::CreateVertexBuffer()
    {
        switch(RendererContext::GetCurrentAPI())
        {
        case GraphicAPI::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>();
            break;
        
        default:
            MTN_ERROR("Unkown VertexBuffer implementation !!\nGraphicAPI is propably not set.");
            return nullptr;
        }
    }

} // namespace Mouton
