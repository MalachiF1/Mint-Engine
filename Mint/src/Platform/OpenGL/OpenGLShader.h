#pragma once

#include "Mint/Renderer/Shader.h"

#include <string>

namespace mint
{

    class OpenGLShader : public Shader
    {
      public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void bind() const override;
        virtual void unbind() const override;

      private:
        uint32_t m_rendererID;
    };

} // namespace mint
