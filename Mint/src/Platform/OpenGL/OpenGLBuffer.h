#pragma once

#include "Mint/Renderer/Buffer.h"

namespace mint
{

// Vertex Buffer
// ----------------------------------------------------------------------------

class OpenGLVertexBuffer final : public VertexBuffer
{
  public:
    OpenGLVertexBuffer(size_t size);
    OpenGLVertexBuffer(const void* vertices, size_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    inline virtual const BufferLayout& getLayout() const override { return m_layout; }
    inline virtual void                setLayout(const BufferLayout& layout) override { m_layout = layout; };

    virtual void setData(const void* data, size_t size) override;

  private:
    uint32_t     m_rendererID;
    BufferLayout m_layout;
};

// Index Buffer
// ----------------------------------------------------------------------------

class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    inline virtual uint32_t getCount() const override { return m_count; }

  private:
    uint32_t m_rendererID;
    uint32_t m_count;
};

} // namespace mint
