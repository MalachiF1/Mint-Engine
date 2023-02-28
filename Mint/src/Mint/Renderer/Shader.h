#pragma once

#include <glm/glm.hpp>
#include <string>

namespace mint
{

    class Shader
    {
      public:
        virtual ~Shader(){};

        virtual void bind() const   = 0;
        virtual void unbind() const = 0;

        // Uniform setter functions
        virtual void setUniformBool(const std::string& name, bool value)         = 0;
        virtual void setUniformInt(const std::string& name, int value)           = 0;
        virtual void setUniformUint(const std::string& name, unsigned int value) = 0;
        virtual void setUniformFloat(const std::string& name, float value)       = 0;

        virtual void setUniformVec2(const std::string& name, const glm::vec2& value) = 0;
        virtual void setUniformVec2(const std::string& name, float x, float y)       = 0;

        virtual void setUniformVec3(const std::string& name, const glm::vec3& value)    = 0;
        virtual void setUniformVec3(const std::string& name, float x, float y, float z) = 0;

        virtual void setUniformVec4(const std::string& name, const glm::vec4& value)             = 0;
        virtual void setUniformVec4(const std::string& name, float x, float y, float z, float w) = 0;

        virtual void setUniformMat2(const std::string& name, const glm::mat2& mat) = 0;
        virtual void setUniformMat3(const std::string& name, const glm::mat3& mat) = 0;
        virtual void setUniformMat4(const std::string& name, const glm::mat4& mat) = 0;

        static Shader* create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };

} // namespace mint
