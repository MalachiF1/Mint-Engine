#include "mtpch.h"

#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace mint
{

    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = (const GLchar*)vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            MINT_CORE_ERROR("{0}", infoLog.data());
            MINT_CORE_ASSERT(false, "Vertex shader compilation failure!");
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar*)fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            MINT_CORE_ERROR("{0}", infoLog.data());
            MINT_CORE_ASSERT(false, "Fragment shader compilation failure!");
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_rendererID   = glCreateProgram();
        GLuint program = m_rendererID;

        // Attach our shaders to our program
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            MINT_CORE_ERROR("{0}", infoLog.data());
            MINT_CORE_ASSERT(false, "Shader program failed to link!");
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_rendererID);
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(m_rendererID);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }

    int OpenGLShader::getUniformLocation(const std::string& name)
    {
        if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
            return m_uniformLocationCache[name];

        int location;
        location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
        {
            MINT_CORE_WARN("Warning: uniform {0} doesn't exist!", name);
        }
        m_uniformLocationCache[name] = location;
        return location;
    }


    void OpenGLShader::setUniformBool(const std::string& name, bool value)
    {
        glUniform1i(getUniformLocation(name), (int)value);
    }
    void OpenGLShader::setUniformInt(const std::string& name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }
    void OpenGLShader::setUniformUint(const std::string& name, unsigned int value)
    {
        glUniform1ui(getUniformLocation(name), value);
    }
    void OpenGLShader::setUniformFloat(const std::string& name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void OpenGLShader::setUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }
    void OpenGLShader::setUniformFloat2(const std::string& name, float x, float y)
    {
        glUniform2f(getUniformLocation(name), x, y);
    }

    void OpenGLShader::setUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }
    void OpenGLShader::setUniformFloat3(const std::string& name, float x, float y, float z)
    {
        glUniform3f(getUniformLocation(name), x, y, z);
    }

    void OpenGLShader::setUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }
    void OpenGLShader::setUniformFloat4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(getUniformLocation(name), x, y, z, w);
    }

    void OpenGLShader::setUniformMat2(const std::string& name, const glm::mat2& mat)
    {
        glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }
    void OpenGLShader::setUniformMat3(const std::string& name, const glm::mat3& mat)
    {
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }
    void OpenGLShader::setUniformMat4(const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

} // namespace mint