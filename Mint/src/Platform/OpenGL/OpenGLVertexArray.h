#pragma once

#include "Mint/Renderer/VertexArray.h"

namespace mint
{

class OpenGLVertexArray final : public VertexArray
{
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    inline virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return m_vertexBuffers; }
    inline virtual std::vector<Ref<VertexBuffer>>&       getVertexBuffers() override { return m_vertexBuffers; }
    inline virtual const Ref<IndexBuffer>&               getIndexBuffer() const override { return m_indexBuffer; }
    inline virtual Ref<IndexBuffer>&                     getIndexBuffer() override { return m_indexBuffer; }

    virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

  private:
    std::vector<Ref<VertexBuffer>> m_vertexBuffers;
    Ref<IndexBuffer>               m_indexBuffer;
    uint32_t                       m_rendererID;
};

} // namespace mint
