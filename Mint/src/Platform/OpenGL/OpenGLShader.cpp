#include "mtpch.h"

#include "OpenGLShader.h"

#include "GLCheck.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace mint
{

static GLenum shaderTypeFromString(const std::string& type)
{
    MINT_PROFILE_FUNCTION();

    if (type == "vertex")
        return GL_VERTEX_SHADER;
    if (type == "fragment" || type == "pixel")
        return GL_FRAGMENT_SHADER;

    MINT_CORE_ASSERT(false, "Unknown shader type {0}", type);
    return 0;
}

std::string OpenGLShader::readFile(const std::string& path)
{
    MINT_PROFILE_FUNCTION();

    std::string   result;
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
    MINT_PROFILE_FUNCTION();

    std::unordered_map<GLenum, std::string> shaderSources;

    const char* typeToken       = "#type";
    size_t      typeTokenLength = strlen(typeToken);
    size_t      pos             = src.find(typeToken, 0);
    while (pos != std::string::npos)
    {
        size_t eol = src.find_first_of("\r\n", pos);
        MINT_CORE_ASSERT(eol != std::string::npos, "Syntax error");
        size_t      begin = pos + typeTokenLength + 1;
        std::string type  = src.substr(begin, eol - begin);
        MINT_CORE_ASSERT(shaderTypeFromString(type), "Invalid shader type specified!");

        size_t nextLinePos = src.find_first_not_of("\r\n", eol);
        MINT_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
        pos = src.find(typeToken, nextLinePos);

        shaderSources[shaderTypeFromString(type)] = (pos == std::string::npos)
                                                      ? src.substr(nextLinePos)
                                                      : src.substr(nextLinePos, pos - nextLinePos);
    }

    return shaderSources;
}

void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
    MINT_PROFILE_FUNCTION();

    // Get a program object.
    GLuint program;
    glCheck(program = glCreateProgram());
    MINT_CORE_ASSERT(shaderSources.size() <= 2, "Currently only supporting 2 shaders");
    std::array<GLuint, 2> glShaderIDs;
    int                   glShaderIDIndex = 0;

    for (auto&& [type, src] : shaderSources)
    {
        // Create an empty vertex shader handle
        GLuint shader;
        glCheck(shader = glCreateShader(type));

        // Send the shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* sourceCStr = (const GLchar*)src.c_str();
        glCheck(glShaderSource(shader, 1, &sourceCStr, 0));

        // Compile the shader
        glCheck(glCompileShader(shader));

        GLint isCompiled = 0;
        glCheck(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glCheck(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glCheck(glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]));

            // We don't need the shader anymore.
            glCheck(glDeleteShader(shader));

            MINT_CORE_ERROR("{0}", infoLog.data());
            MINT_CORE_ASSERT(false, "Shader compilation failure!");
            break;
        }

        // Shader was successfully compiled.
        // Now attach our shader to our program
        glCheck(glAttachShader(program, shader));
        glShaderIDs[glShaderIDIndex++] = shader;
    }

    // Link our program
    glCheck(glLinkProgram(program));

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glCheck(glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked));
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glCheck(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glCheck(glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]));

        // We don't need the program anymore.
        glCheck(glDeleteProgram(program));
        // Don't leak shaders either.
        for (GLuint id : glShaderIDs) glDeleteShader(id);

        MINT_CORE_ERROR("{0}", infoLog.data());
        MINT_CORE_ASSERT(false, "Shader program failed to link!");
        return;
    }

    m_rendererID = program;

    // Always detach shaders after a successful link.
    glCheck(for (GLuint id : glShaderIDs) glDetachShader(program, id));
}


OpenGLShader::OpenGLShader(const std::string& path)
{
    MINT_PROFILE_FUNCTION();

    std::string                             shaderSrc     = readFile(path);
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
    MINT_PROFILE_FUNCTION();

    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER]   = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;
    compile(sources);
}

OpenGLShader::~OpenGLShader()
{
    MINT_PROFILE_FUNCTION();

    glCheck(glDeleteProgram(m_rendererID));
}

void OpenGLShader::bind() const
{
    MINT_PROFILE_FUNCTION();

    glCheck(glUseProgram(m_rendererID));
}

void OpenGLShader::unbind() const
{
    MINT_PROFILE_FUNCTION();

    glCheck(glUseProgram(0));
}

void OpenGLShader::setBool(const std::string& name, bool value)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformBool(name, value);
}
void OpenGLShader::setInt(const std::string& name, int value)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformInt(name, value);
}
void OpenGLShader::setIntArray(const std::string& name, int* values, uint32_t count)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformIntArray(name, values, count);
}
void OpenGLShader::setUint(const std::string& name, unsigned int value)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformUint(name, value);
}
void OpenGLShader::setFloat(const std::string& name, float value)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformFloat(name, value);
}
void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& value)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformFloat2(name, value);
}
void OpenGLShader::setFloat2(const std::string& name, float x, float y)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformFloat2(name, x, y);
}
void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformFloat3(name, value);
}
void OpenGLShader::setFloat3(const std::string& name, float x, float y, float z)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformFloat3(name, x, y, z);
}
void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformFloat4(name, value);
}
void OpenGLShader::setFloat4(const std::string& name, float x, float y, float z, float w)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformFloat4(name, x, y, z, w);
}
void OpenGLShader::setMat2(const std::string& name, const glm::mat2& mat)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformMat2(name, mat);
}
void OpenGLShader::setMat3(const std::string& name, const glm::mat3& mat)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformMat3(name, mat);
}
void OpenGLShader::setMat4(const std::string& name, const glm::mat4& mat)
{
    MINT_PROFILE_FUNCTION();

    uploadUniformMat4(name, mat);
}

int OpenGLShader::getUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    int location;
    glCheck(location = glGetUniformLocation(m_rendererID, name.c_str()));
    if (location == -1)
    {
        MINT_CORE_WARN("Warning: uniform {0} doesn't exist!", name);
    }
    m_uniformLocationCache[name] = location;
    return location;
}


void OpenGLShader::uploadUniformBool(const std::string& name, bool value)
{
    glCheck(glUniform1i(getUniformLocation(name), (int)value));
}
void OpenGLShader::uploadUniformInt(const std::string& name, int value)
{
    glCheck(glUniform1i(getUniformLocation(name), value));
}
void OpenGLShader::uploadUniformIntArray(const std::string& name, int* values, uint32_t count)
{
    glCheck(glUniform1iv(getUniformLocation(name), count, values));
}
void OpenGLShader::uploadUniformUint(const std::string& name, unsigned int value)
{
    glCheck(glUniform1ui(getUniformLocation(name), value));
}
void OpenGLShader::uploadUniformFloat(const std::string& name, float value)
{
    glCheck(glUniform1f(getUniformLocation(name), value));
}

void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& value)
{
    glCheck(glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value)));
}
void OpenGLShader::uploadUniformFloat2(const std::string& name, float x, float y)
{
    glCheck(glUniform2f(getUniformLocation(name), x, y));
}

void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& value)
{
    glCheck(glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value)));
}
void OpenGLShader::uploadUniformFloat3(const std::string& name, float x, float y, float z)
{
    glCheck(glUniform3f(getUniformLocation(name), x, y, z));
}

void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& value)
{
    glCheck(glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value)));
}
void OpenGLShader::uploadUniformFloat4(const std::string& name, float x, float y, float z, float w)
{
    glCheck(glUniform4f(getUniformLocation(name), x, y, z, w));
}

void OpenGLShader::uploadUniformMat2(const std::string& name, const glm::mat2& mat)
{
    glCheck(glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}
void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& mat)
{
    glCheck(glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}
void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& mat)
{
    glCheck(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}

} // namespace mint
