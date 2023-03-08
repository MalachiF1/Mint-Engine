#pragma once

#include "Mint/Core/Base.h"
#include "Mint/Renderer/Buffer.h"

#include <memory>

namespace mint
{

class VertexArray
{
  public:
    virtual ~VertexArray() {}

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual std::vector<Ref<VertexBuffer>>&       getVertexBuffers()       = 0;
    virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
    virtual Ref<IndexBuffer>&                     getIndexBuffer()         = 0;
    virtual const Ref<IndexBuffer>&               getIndexBuffer() const   = 0;

    virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)    = 0;

    static Ref<VertexArray> create();
};

} // namespace mint
