#pragma once

#include "Mint/Renderer/Shader.h"

#include <string>
#include <glm/glm.hpp>

namespace mint
{

    class OpenGLShader : public Shader
    {
      public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader() final;

        virtual void bind() const override final;
        virtual void unbind() const override final;

        // Uniform setter functions
        virtual void setUniformBool(const std::string& name, bool value) override final;
        virtual void setUniformInt(const std::string& name, int value) override final;
        virtual void setUniformUint(const std::string& name, unsigned int value) override final;
        virtual void setUniformFloat(const std::string& name, float value) override final;

        virtual void setUniformVec2(const std::string& name, const glm::vec2& value) override final;
        virtual void setUniformVec2(const std::string& name, float x, float y) override final;

        virtual void setUniformVec3(const std::string& name, const glm::vec3& value) override final;
        virtual void setUniformVec3(const std::string& name, float x, float y, float z) override final;

        virtual void setUniformVec4(const std::string& name, const glm::vec4& value) override final;
        virtual void setUniformVec4(const std::string& name, float x, float y, float z, float w) override final;

        virtual void setUniformMat2(const std::string& name, const glm::mat2& mat) override final;
        virtual void setUniformMat3(const std::string& name, const glm::mat3& mat) override final;
        virtual void setUniformMat4(const std::string& name, const glm::mat4& mat) override final;

      private:
        // Get the location of a uniform (and possibly add the location to the uniform location cache)
        int getUniformLocation(const std::string& name);

      private:
        uint32_t m_rendererID;
        std::unordered_map<std::string, int> m_uniformLocationCache;
    };

} // namespace mint
