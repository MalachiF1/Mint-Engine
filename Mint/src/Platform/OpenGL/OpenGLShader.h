#pragma once

#include "Mint/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

// Temporary (will add glad.h include instead, after i remove it from sandbox.cpp)
typedef unsigned int GLenum;

namespace mint
{

    class OpenGLShader : public Shader
    {
      public:
        OpenGLShader(const std::string& path);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader() final;

        inline virtual const std::string& getName() const override final { return m_name; }

        virtual void bind() const override final;
        virtual void unbind() const override final;

        // Uniform setter functions
        virtual void setBool(const std::string& name, bool value) override final;
        virtual void setInt(const std::string& name, int value) override final;
        virtual void setUint(const std::string& name, unsigned int value) override final;
        virtual void setFloat(const std::string& name, float value) override final;

        virtual void setFloat2(const std::string& name, const glm::vec2& value) override final;
        virtual void setFloat2(const std::string& name, float x, float y) override final;

        virtual void setFloat3(const std::string& name, const glm::vec3& value) override final;
        virtual void setFloat3(const std::string& name, float x, float y, float z) override final;

        virtual void setFloat4(const std::string& name, const glm::vec4& value) override final;
        virtual void setFloat4(const std::string& name, float x, float y, float z, float w) override final;

        virtual void setMat2(const std::string& name, const glm::mat2& mat) override final;
        virtual void setMat3(const std::string& name, const glm::mat3& mat) override final;
        virtual void setMat4(const std::string& name, const glm::mat4& mat) override final;

      private:
        void uploadUniformBool(const std::string& name, bool value);
        void uploadUniformInt(const std::string& name, int value);
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
        std::string readFile(const std::string& path);
        std::unordered_map<GLenum, std::string> preProcess(const std::string& src);
        void compile(const std::unordered_map<GLenum, std::string>& shaderSources);
        int getUniformLocation(const std::string& name);

      private:
        uint32_t m_rendererID;
        std::string m_name;
        std::unordered_map<std::string, int> m_uniformLocationCache;
    };

} // namespace mint
