#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Buffers.h"
#include "MoutonPch.h"

namespace Mouton {

    class VertexArray
    {
      public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddVertexBuffer(VertexBuffer& vb) = 0;

        static std::shared_ptr<VertexArray> CreateVertexArray();
    };

} // namespace Mouton

#endif