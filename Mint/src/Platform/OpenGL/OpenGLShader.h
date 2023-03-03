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
        void setUniformBool(const std::string& name, bool value);
        void setUniformInt(const std::string& name, int value);
        void setUniformUint(const std::string& name, unsigned int value);
        void setUniformFloat(const std::string& name, float value);

        void setUniformFloat2(const std::string& name, const glm::vec2& value);
        void setUniformFloat2(const std::string& name, float x, float y);

        void setUniformFloat3(const std::string& name, const glm::vec3& value);
        void setUniformFloat3(const std::string& name, float x, float y, float z);

        void setUniformFloat4(const std::string& name, const glm::vec4& value);
        void setUniformFloat4(const std::string& name, float x, float y, float z, float w);

        void setUniformMat2(const std::string& name, const glm::mat2& mat);
        void setUniformMat3(const std::string& name, const glm::mat3& mat);
        void setUniformMat4(const std::string& name, const glm::mat4& mat);

      private:
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
