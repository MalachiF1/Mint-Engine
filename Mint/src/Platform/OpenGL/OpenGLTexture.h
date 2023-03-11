#pragma once

#include "Mint/Renderer/Texture.h"

#include <glad/glad.h>

namespace mint
{

class OpenGLTexture2D final : public Texture2D
{
  public:
    OpenGLTexture2D(uint32_t width, uint32_t height);
    OpenGLTexture2D(const std::string& path);
    virtual ~OpenGLTexture2D() override;

    inline virtual uint32_t getWidth() const override { return m_width; }
    inline virtual uint32_t getHeight() const override { return m_height; }

    inline virtual std::pair<uint32_t, uint32_t> getSize() const override
    {
        return std::pair<uint32_t, uint32_t>(m_width, m_height);
    }

    inline virtual uint32_t getRendererID() const override { return m_rendererID; }

    virtual void setData(void* data, size_t size) override;

    virtual void bind(uint32_t slot = 0) const override;

    inline virtual bool operator==(const Texture& other) const override
    {
        return m_rendererID == ((OpenGLTexture2D&)other).m_rendererID;
    }

  private:
    std::string m_path;
    uint32_t    m_width, m_height;
    GLenum      m_internalFormat, m_dataFormat;
    uint32_t    m_rendererID;
};

} // namespace mint
