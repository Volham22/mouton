#include "OpenGLRenderCommand.h"

#include <glad/glad.h>

namespace Mouton
{

    void OpenGLRenderCommand::ClearImp()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRenderCommand::SetClearColorImp(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderCommand::SetBlendingImpl(bool enable)
    {
        if(enable)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
        }
        else
            glDisable(GL_BLEND);
    }

    void OpenGLRenderCommand::SetDebugMessageImpl()
    {
    
        const char* glVersion = (const char*)glGetString(GL_VERSION);
           
           if(strlen(glVersion) > 0)
           {
               if(glVersion[0] < '4')
               {
                   MTN_WARN("OpenGL debug feature is available is with OGL 4 and above")
                   return;
               }
           }
           
           MTN_INFO("Running OpenGL with debug message");

           glEnable(GL_DEBUG_OUTPUT);
           glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
           glDebugMessageCallback((GLDEBUGPROC)[](
                GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam) {

                switch(severity)
                {
                case GL_DEBUG_SEVERITY_HIGH:
                    MTN_ERROR("OpenGL: id: {0} Message: {1}", id, message);
                    break;
                
                case GL_DEBUG_SEVERITY_MEDIUM:
                    MTN_WARN("OpenGL: id: {0} Message: {1}", id, message);
                    break;
                
                case GL_DEBUG_SEVERITY_LOW:
                    MTN_WARN("OpenGL: id: {0} Message: {1}", id, message);
                    break;
                
                case GL_DEBUG_SEVERITY_NOTIFICATION:
                    MTN_INFO("OpenGL: id: {0} Message: {1}", id, message);
                    break;
                
                default:
                    MTN_WARN("OpenGL: id: {0} Message: {1}", id, message);
                }
           },
           nullptr);

           glDebugMessageControl(
                GL_DONT_CARE,
                GL_DONT_CARE,
                GL_DONT_CARE,
                0,
                nullptr,
                true);

    }

    void OpenGLRenderCommand::DrawImp(int count)
    {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void OpenGLRenderCommand::DrawIndexedImp(int indicesCount)
    {
        // EBO must be bound before !
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
    }

} // namespace Mouton
