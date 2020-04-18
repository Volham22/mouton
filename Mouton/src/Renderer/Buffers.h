#ifndef BUFFERS_H
#define BUFFERS_H

#include "MoutonPch.h"

namespace Mouton
{
    enum class ShaderType{
        Int, Int2, Int3, Int4,
        Float, Float2, Float3, Float4,
        Mat2, Mat3, Mat4,
        Bool
    };

    struct BufferElement {
        BufferElement();
        BufferElement(ShaderType type, bool normalized = false);
        ShaderType type;
        bool normalized;
        int size;
        int count;

    private:
        int GetSize(ShaderType type) const;
        int GetCount(ShaderType type) const;
    };

    class BufferLayout
    {
    public:
        BufferLayout();
        BufferLayout(std::initializer_list<BufferElement> elem);
        int GetStride();
        std::vector<BufferElement>& GetElements() { return m_BufferElements; };
    
    private:
        std::vector<BufferElement> m_BufferElements;
    };

    class Buffer
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetData(void* data, size_t size) = 0;
    };

    class VertexBuffer : public Buffer
    {
    public:
        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual BufferLayout& GetLayout() = 0;

        static std::shared_ptr<VertexBuffer> CreateVertexBuffer();
    };

    class ElementBuffer : public Buffer
    {
    public:
        static std::shared_ptr<ElementBuffer> CreateElementBuffer();
    };

} // namespace Mouton


#endif