#pragma once

#include "Mint/Renderer/Texture.h"

#include <glad/glad.h>

namespace mint
{

    class OpenGLTexture2D : public Texture2D
    {
      public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D() override final;

        inline virtual uint32_t getWidth() const override final { return m_width; }
        inline virtual uint32_t getHeight() const override final { return m_height; }
        inline virtual std::pair<uint32_t, uint32_t> getSize() const override final
        {
            return std::pair<uint32_t, uint32_t>(m_width, m_height);
        }

        virtual void setData(void* data, size_t size) override final;

        virtual void bind(uint32_t slot = 0) const override final;

      private:
        std::string m_path;
        uint32_t m_width, m_height;
        GLenum m_internalFormat, m_dataFormat;
        uint32_t m_rendererID;
    };

} // namespace mint
