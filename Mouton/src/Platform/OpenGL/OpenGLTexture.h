#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "Renderer/Texture.h"

namespace Mouton
{

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const char* fileapath);
        ~OpenGLTexture2D();
        virtual void Bind(uint32_t slot = 0) override;
        virtual void Unbind() override;
        virtual int GetWidth() override { return m_TextureWidth; };
        virtual int GetHeight() override { return m_TextureHeight; };
    
    private:
        void LoadTexture(const char* filepath);

        uint32_t m_TextureHandle;
        int m_TextureWidth, m_TextureHeight, m_TextureChannels;
        int m_Slot;
    };


} // namespace Mouton

#endif