#ifndef SHADER_H
#define SHADER_H

#include "MoutonPch.h"

namespace Mouton {

    class Shader
    {
      public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        // Uniforms
        virtual void SetUniform(const std::string& name, int value) = 0;
        virtual void SetUniform(const std::string& name,
                                const glm::ivec2& value)
            = 0;
        virtual void SetUniform(const std::string& name,
                                const glm::ivec3& value)
            = 0;
        virtual void SetUniform(const std::string& name,
                                const glm::ivec4& value)
            = 0;

        virtual void SetUniform(const std::string& name, float value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec2& value)
            = 0;
        virtual void SetUniform(const std::string& name, const glm::vec3& value)
            = 0;
        virtual void SetUniform(const std::string& name, const glm::vec4& value)
            = 0;

        virtual void SetUniform(const std::string& name, const glm::mat2& value,
                                bool transpose = false)
            = 0;
        virtual void SetUniform(const std::string& name, const glm::mat3& value,
                                bool transpose = false)
            = 0;
        virtual void SetUniform(const std::string& name, const glm::mat4& value,
                                bool transpose = false)
            = 0;

        static std::shared_ptr<Shader>
        CreateShader(const std::string& filepath);
    };

} // namespace Mouton

#endif