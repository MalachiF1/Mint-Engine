#include "mtpch.h"

#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace mint
{

    static GLenum shaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        MINT_CORE_ASSERT(false, "Unknown shader type {0}", type);
        return 0;
    }

    std::string OpenGLShader::readFile(const std::string& path)
    {
        std::string result;
        std::ifstream in(path, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            MINT_CORE_ERROR("Could not open file '{0}'!", path);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& src)
    {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken  = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos             = src.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = src.find_first_of("\r\n", pos);
            MINT_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin     = pos + typeTokenLength + 1;
            std::string type = src.substr(begin, eol - begin);
            MINT_CORE_ASSERT(shaderTypeFromString(type), "Invalid shader type specified!");

            size_t nextLinePos = src.find_first_not_of("\r\n", eol);
            MINT_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = src.find(typeToken, nextLinePos);

            shaderSources[shaderTypeFromString(type)] =
                (pos == std::string::npos) ? src.substr(nextLinePos) : src.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        // Get a program object.
        GLuint program = glCreateProgram();
        MINT_CORE_ASSERT(shaderSources.size() <= 2, "Currently only supporting 2 shaders");
        std::array<GLuint, 2> glShaderIDs;
        int glShaderIDIndex = 0;

        for (auto&& [type, src] : shaderSources)
        {
            // Create an empty vertex shader handle
            GLuint shader = glCreateShader(type);

            // Send the shader source code to GL
            // Note that std::string's .c_str is NULL character terminated.
            const GLchar* sourceCStr = (const GLchar*)src.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            // Compile the shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                MINT_CORE_ERROR("{0}", infoLog.data());
                MINT_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            // Shader was successfully compiled.
            // Now attach our shader to our program
            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

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
            for (GLuint id : glShaderIDs) glDeleteShader(id);

            MINT_CORE_ERROR("{0}", infoLog.data());
            MINT_CORE_ASSERT(false, "Shader program failed to link!");
            return;
        }

        m_rendererID = program;

        // Always detach shaders after a successful link.
        for (GLuint id : glShaderIDs) glDetachShader(program, id);
    }


    OpenGLShader::OpenGLShader(const std::string& path)
    {
        std::string shaderSrc                                 = readFile(path);
        std::unordered_map<GLenum, std::string> shaderSources = preProcess(shaderSrc);
        compile(shaderSources);

        // Extract file name
        size_t lastSlash = path.find_last_of("/\\");
        lastSlash        = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        size_t lastDot   = path.rfind('.');
        size_t count     = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;

        m_name = path.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) :
        m_name(name)
    {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER]   = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(sources);
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