#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <stb_image.h>

namespace Mouton
{

    OpenGLTexture2D::OpenGLTexture2D(const char* filepath)
        : m_TextureHandle(0), m_TextureWidth(0), m_TextureHeight(0),
          m_TextureChannels(0), m_Slot(0)
    {
        glGenTextures(1, &m_TextureHandle);
        LoadTexture(filepath);
    }

    void OpenGLTexture2D::Bind(uint32_t slot)
    {
        m_Slot = slot;
        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
    }

    void OpenGLTexture2D::Unbind()
    {
        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture2D::LoadTexture(const char* filepath)
    {
        uint8_t* data = stbi_load(
            filepath,
            &m_TextureWidth,
            &m_TextureHeight,
            &m_TextureChannels,
            0 // No prefered texture channels number
        );

        glBindTexture(GL_TEXTURE_2D, m_TextureHandle);

        if(data)
        {
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                m_TextureChannels > 3 ? GL_RGBA : GL_RGB,
                m_TextureWidth,
                m_TextureHeight,
                0,
                m_TextureChannels > 3 ? GL_RGBA : GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );

            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);

        }
        else
            MTN_WARN("Texture '{0}' coundn't be loaded !", filepath);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_TextureHandle);
    }

} // namespace Mouton
