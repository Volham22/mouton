#ifndef BUFFERS_H
#define BUFFERS_H

#include "MoutonPch.h"

namespace Mouton
{
    class VertexBuffer
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetData(void* data, size_t size) = 0;

        static std::shared_ptr<VertexBuffer> CreateVertexBuffer();
    };

} // namespace Mouton


#endif