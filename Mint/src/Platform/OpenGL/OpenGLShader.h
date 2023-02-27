#pragma once

#include "Mint/Renderer/Shader.h"

#include <string>

namespace mint
{

    class OpenGLShader : public Shader
    {
      public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader() final;

        virtual void bind() const override final;
        virtual void unbind() const override final;

      private:
        uint32_t m_rendererID;
    };

} // namespace mint
