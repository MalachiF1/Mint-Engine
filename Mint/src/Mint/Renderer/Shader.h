#pragma once

#include "Mint/Core/Base.h"

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace mint
{

    class Shader
    {
      public:
        virtual ~Shader() = default;

        virtual void bind() const   = 0;
        virtual void unbind() const = 0;

        virtual const std::string& getName() const = 0;

        virtual void setBool(const std::string& name, bool value)                      = 0;
        virtual void setInt(const std::string& name, int value)                        = 0;
        virtual void setIntArray(const std::string& name, int* values, uint32_t count) = 0;
        virtual void setUint(const std::string& name, unsigned int value)              = 0;
        virtual void setFloat(const std::string& name, float value)                    = 0;

        virtual void setFloat2(const std::string& name, const glm::vec2& value) = 0;
        virtual void setFloat2(const std::string& name, float x, float y)       = 0;

        virtual void setFloat3(const std::string& name, const glm::vec3& value)    = 0;
        virtual void setFloat3(const std::string& name, float x, float y, float z) = 0;

        virtual void setFloat4(const std::string& name, const glm::vec4& value)             = 0;
        virtual void setFloat4(const std::string& name, float x, float y, float z, float w) = 0;

        virtual void setMat2(const std::string& name, const glm::mat2& mat) = 0;
        virtual void setMat3(const std::string& name, const glm::mat3& mat) = 0;
        virtual void setMat4(const std::string& name, const glm::mat4& mat) = 0;

        static Ref<Shader> create(const std::string& path);
        static Ref<Shader> create(
            const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc
        );
    };

    class ShaderLibrary
    {
      public:
        void add(const Ref<Shader>& shader);
        Ref<Shader> load(const std::string& path);
        Ref<Shader> load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        Ref<Shader> get(const std::string& name);

      private:
        std::unordered_map<std::string, Ref<Shader>> m_shaders;
    };

} // namespace mint
