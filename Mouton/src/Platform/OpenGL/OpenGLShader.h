#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

// also include pch and glm
#include "Renderer/Shader.h"

namespace Mouton
{

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filepath);
        virtual void Bind() override;
        virtual void Unbind() override;

        // Uniforms
        virtual void SetUniform(const std::string& name, float value) override;

        virtual void SetUniform(const std::string& name, int value) override;
        virtual void SetUniform(const std::string& name, const glm::ivec2& value) override;
        virtual void SetUniform(const std::string& name, const glm::ivec3& value) override;
        virtual void SetUniform(const std::string& name, const glm::ivec4& value) override;

        virtual void SetUniform(const std::string& name, const glm::vec2& value) override;
        virtual void SetUniform(const std::string& name, const glm::vec3& value) override;
        virtual void SetUniform(const std::string& name, const glm::vec4& value) override;

        virtual void SetUniform(const std::string& name, const glm::mat2& value) override;
        virtual void SetUniform(const std::string& name, const glm::mat3& value) override;
        virtual void SetUniform(const std::string& name, const glm::mat4& value) override;

    private:
        std::pair<std::string, std::string> ProcessSourceCode(const std::string& filepath);
        unsigned int CompileShader(const char* sourceCode, int32_t type);
        void InstantiateShader(const std::string& filePath);
        int GetUniformLocation(const std::string& name);

        uint32_t m_ProgramHandle;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    };

} // namespace Mouton


#endif