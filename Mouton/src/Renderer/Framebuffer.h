#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "MoutonPch.h"

namespace Mouton {

    class Framebuffer
    {
      public:
        static std::shared_ptr<Framebuffer> CreateFramebuffer();

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void CreateBlankTexture(uint32_t width, uint32_t height) = 0;
        virtual uint32_t GetTextureAttachmentID() const = 0;
    };

} // namespace Mouton

#endif