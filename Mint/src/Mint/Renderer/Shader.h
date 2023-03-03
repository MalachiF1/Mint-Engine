#pragma once

#include "Mint/Core/Base.h"

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
