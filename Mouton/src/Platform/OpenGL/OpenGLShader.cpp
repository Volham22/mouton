#include "OpenGLShader.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Mouton {
    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        InstantiateShader(filepath);
    }

    void OpenGLShader::Bind() { glUseProgram(m_ProgramHandle); }

    void OpenGLShader::Unbind() { glUseProgram(0); }

    void OpenGLShader::SetUniform(const std::string& name, int value)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniform1i(location, value);
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::ivec2& value)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniform2i(location, value.x, value.y);
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::ivec3& value)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniform3i(location, value.x, value.y, value.z);
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::ivec4& value)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniform4i(location, value.x, value.y, value.z, value.w);
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name, float value)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniform1f(location, value);
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::vec2& value)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniform2f(location, value.x, value.y);
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::vec3& value)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniform3f(location, value.x, value.y, value.z);
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::vec4& value)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniform4f(location, value.x, value.y, value.z, value.w);
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::mat2& value, bool tranpose)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniformMatrix2fv(location, 1, tranpose, glm::value_ptr(value));
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::mat3& value, bool transpose)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(value));
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name,
                                  const glm::mat4& value, bool transpose)
    {
        glUseProgram(m_ProgramHandle);
        int location = GetUniformLocation(name);

        if (location >= 0)
            glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(value));
        else
            MTN_WARN("Uniform '{0}' not found !", name.c_str());
        glUseProgram(0);
    }

    std::pair<std::string, std::string>
    OpenGLShader::ProcessSourceCode(const std::string& filepath)
    {
        std::ifstream file(filepath,
                           std::ios::in | std::ios::binary | std::ios::ate);
        std::string vertexCode;
        std::string fragmentCode;

        if (file.is_open())
        {
            int size = file.tellg();

            std::string fileCode;
            fileCode.resize(size);
            file.seekg(std::ios::beg);
            file.read(&fileCode[0], size);

            unsigned int beginVertex
                = fileCode.find("#type vertex") + strlen("#type vertex");
            unsigned int endVertex = fileCode.find("#endtype vertex");

            if (beginVertex != std::string::npos
                && endVertex != std::string::npos)
                vertexCode
                    = fileCode.substr(beginVertex, endVertex - beginVertex);
            else
                MTN_ERROR(
                    "Missing or unclosed '#type vertex' directive in '{0}'",
                    filepath.c_str());

            unsigned int beginFragment
                = fileCode.find("#type fragment") + strlen("#type fragment");
            unsigned int endFragment = fileCode.find("#endtype fragment");

            if (beginFragment != std::string::npos
                && endFragment != std::string::npos)
                fragmentCode = fileCode.substr(beginFragment,
                                               endFragment - beginFragment);
            else
                MTN_ERROR(
                    "Missing or unclosed '#type fragment' directive in '{0}'",
                    filepath.c_str());
        } else
            MTN_ERROR("Unable to open shader file : '{0}'", filepath.c_str());

        return { vertexCode, fragmentCode };
    }

    unsigned int OpenGLShader::CompileShader(const char* sourceCode,
                                             int32_t type)
    {
        unsigned int shaderID = glCreateShader(type);
        glShaderSource(shaderID, 1, &sourceCode, nullptr);
        glCompileShader(shaderID);

        int status = 0;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            int size = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &size);

            std::vector<char> infoLog(size);
            glGetShaderInfoLog(shaderID, size, &size, &infoLog[0]);

            MTN_ERROR("Shader compilation failed :'{0}'", infoLog.data());
            glDeleteShader(shaderID);
        }

        return shaderID;
    }

    void OpenGLShader::InstantiateShader(const std::string& filepath)
    {
        auto sourceCode = ProcessSourceCode(filepath);
        unsigned int vertexShaderID
            = CompileShader(sourceCode.first.c_str(), GL_VERTEX_SHADER);
        unsigned int fragmentShaderID
            = CompileShader(sourceCode.second.c_str(), GL_FRAGMENT_SHADER);

        m_ProgramHandle = glCreateProgram();
        glAttachShader(m_ProgramHandle, vertexShaderID);
        glAttachShader(m_ProgramHandle, fragmentShaderID);
        glLinkProgram(m_ProgramHandle);

        int isLinked = 0;
        glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &isLinked);

        if (!isLinked)
        {
            int size = 0;
            glGetProgramiv(m_ProgramHandle, GL_INFO_LOG_LENGTH, &size);

            std::vector<char> infoLog(size);
            glGetProgramInfoLog(m_ProgramHandle, size, &size, &infoLog[0]);
            MTN_ERROR("Failed to link program for shader '{0}' with the "
                      "following error \n\t{1}",
                      filepath.c_str(), infoLog.data());
            glDeleteProgram(m_ProgramHandle);
        }

        glDetachShader(m_ProgramHandle, vertexShaderID);
        glDetachShader(m_ProgramHandle, fragmentShaderID);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    int OpenGLShader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];
        else
        {
            glUseProgram(m_ProgramHandle);
            int location = glGetUniformLocation(m_ProgramHandle, name.c_str());

            if (location >= 0)
            {
                m_UniformLocationCache[name] = location;
                return location;
            } else
                MTN_WARN("Uniform '{0}' not found !", name.c_str());
        }

        return -1;
    }

} // namespace Mouton
