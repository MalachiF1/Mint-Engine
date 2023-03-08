#pragma once

#include "Mint/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

// Temporary (will add glad.h include instead, after i remove it from sandbox.cpp)
typedef unsigned int GLenum;

namespace mint
{

class OpenGLShader final : public Shader
{
  public:
    OpenGLShader(const std::string& path);
    OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    virtual ~OpenGLShader();

    inline virtual const std::string& getName() const override { return m_name; }

    virtual void bind() const override;
    virtual void unbind() const override;

    // Uniform setter functions
    virtual void setBool(const std::string& name, bool value) override;
    virtual void setInt(const std::string& name, int value) override;
    virtual void setIntArray(const std::string& name, int* values, uint32_t count) override;
    virtual void setUint(const std::string& name, unsigned int value) override;
    virtual void setFloat(const std::string& name, float value) override;

    virtual void setFloat2(const std::string& name, const glm::vec2& value) override;
    virtual void setFloat2(const std::string& name, float x, float y) override;

    virtual void setFloat3(const std::string& name, const glm::vec3& value) override;
    virtual void setFloat3(const std::string& name, float x, float y, float z) override;

    virtual void setFloat4(const std::string& name, const glm::vec4& value) override;
    virtual void setFloat4(const std::string& name, float x, float y, float z, float w) override;

    virtual void setMat2(const std::string& name, const glm::mat2& mat) override;
    virtual void setMat3(const std::string& name, const glm::mat3& mat) override;
    virtual void setMat4(const std::string& name, const glm::mat4& mat) override;

  private:
    void uploadUniformBool(const std::string& name, bool value);
    void uploadUniformInt(const std::string& name, int value);
    void uploadUniformIntArray(const std::string& name, int* values, uint32_t count);
    void uploadUniformUint(const std::string& name, unsigned int value);
    void uploadUniformFloat(const std::string& name, float value);

    void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
    void uploadUniformFloat2(const std::string& name, float x, float y);

    void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
    void uploadUniformFloat3(const std::string& name, float x, float y, float z);

    void uploadUniformFloat4(const std::string& name, const glm::vec4& value);
    void uploadUniformFloat4(const std::string& name, float x, float y, float z, float w);

    void uploadUniformMat2(const std::string& name, const glm::mat2& mat);
    void uploadUniformMat3(const std::string& name, const glm::mat3& mat);
    void uploadUniformMat4(const std::string& name, const glm::mat4& mat);

    // Get the location of a uniform (and possibly add the location to the uniform location cache)
    std::string                             readFile(const std::string& path);
    std::unordered_map<GLenum, std::string> preProcess(const std::string& src);
    void                                    compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    int                                     getUniformLocation(const std::string& name);

  private:
    uint32_t                             m_rendererID;
    std::string                          m_name;
    std::unordered_map<std::string, int> m_uniformLocationCache;
};

} // namespace mint
