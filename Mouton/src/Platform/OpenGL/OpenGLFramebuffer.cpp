#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Mouton {

    OpenGLFramebuffer::OpenGLFramebuffer()
        : m_FramebufferID(0), m_TextureAttachmentID(0), m_ColorAttachmentID(0)
    {
        glGenFramebuffers(1, &m_FramebufferID);
        glGenTextures(1, &m_TextureAttachmentID);
        glGenTextures(1, &m_ColorAttachmentID);
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
    }

    void OpenGLFramebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void OpenGLFramebuffer::CreateBlankTexture(uint32_t width, uint32_t height)
    {
        MTN_ASSERT((width > 0 && height > 0), "Invalid Framebuffer values !");

        // Recreate a texture iff a texture already exists
        if (m_TextureAttachmentID && m_ColorAttachmentID)
        {
            glDeleteTextures(1, &m_TextureAttachmentID);
            glDeleteTextures(1, &m_ColorAttachmentID);
            glGenTextures(1, &m_TextureAttachmentID);
            glGenTextures(1, &m_ColorAttachmentID);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
        glBindTexture(GL_TEXTURE_2D, m_TextureAttachmentID);

        glViewport(0, 0, width, height);

        // Allocate in GPU memory a blank depth stencil texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0,
                     GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                               GL_TEXTURE_2D, m_TextureAttachmentID, 0);

        glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, m_ColorAttachmentID, 0);

        MTN_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER)
                    == GL_FRAMEBUFFER_COMPLETE),
                   "Framebuffer not complete !!");

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_FramebufferID);
        glDeleteTextures(1, &m_TextureAttachmentID);
        glDeleteTextures(1, &m_ColorAttachmentID);
    }

} // namespace Mouton
