#ifndef OPENGL_FRAMEBUFFER_H
#define OPENGL_FRAMEBUFFER_H

#include "MoutonPch.h"

#include "Renderer/Framebuffer.h"

namespace Mouton
{

    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer();
        ~OpenGLFramebuffer();

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void CreateBlankTexture(uint32_t width, uint32_t height) override;
        virtual uint32_t GetTextureAttachmentID() const override { return m_ColorAttachmentID; };

        private:
            uint32_t m_FramebufferID;
            uint32_t m_TextureAttachmentID, m_ColorAttachmentID;
    };

} // namespace Mouton


#endif