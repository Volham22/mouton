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
        virtual std::string GetFilename() const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        virtual bool operator==(Texture2D& other) const = 0;

        static std::shared_ptr<Texture2D> CreateTexture(const char* filepath);
    };

} // namespace Mouton


#endif