#ifndef TEXTURE_H
#define TEXTURE_H

#include "MoutonPch.h"

namespace Mouton
{

    class Texture
    {
    public:
        virtual void Bind(uint32_t slot = 0) = 0;
        virtual void Unbind() = 0;
        virtual int GetWidth() = 0;
        virtual int GetHeight() = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static std::shared_ptr<Texture2D> CreateTexture(const char* filepath);
    };

} // namespace Mouton


#endif