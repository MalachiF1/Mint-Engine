#include "mtpch.h"

#include "OpenGLTexture.h"

#include <stb_image.h>

namespace mint
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) :
        m_path(""), m_width(width), m_height(height), m_internalFormat(0), m_dataFormat(0)
    {
        m_internalFormat = GL_RGBA8;
        m_dataFormat     = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_path(path), m_internalFormat(0), m_dataFormat(0)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        MINT_CORE_ASSERT(data, "Failed to load image {0}", path);
        m_width  = (uint32_t)width;
        m_height = (uint32_t)height;

        if (channels == 4)
        {
            m_internalFormat = GL_RGBA8;
            m_dataFormat     = GL_RGBA;
        }
        else if (channels == 3)
        {
            m_internalFormat = GL_RGB8;
            m_dataFormat     = GL_RGB;
        }
        MINT_CORE_ASSERT(m_internalFormat & m_dataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_rendererID);
    }

    void OpenGLTexture2D::setData(void* data, size_t size)
    {
        uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
        MINT_CORE_ASSERT(size == m_width * m_height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_rendererID);
    }

} // namespace mint