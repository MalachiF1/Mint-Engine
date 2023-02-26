#pragma once

#include "Mint/Renderer/VertexArray.h"

namespace mint
{

    class OpenGLVertexArray : public VertexArray
    {
      public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void bind() const override;
        virtual void unbind() const override;

        inline virtual const std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const override
        {
            return m_vertexBuffers;
        }
        inline virtual const std::shared_ptr<IndexBuffer> getIndexBuffer() const override { return m_indexBuffer; }

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

      private:
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
        uint32_t m_rendererID;
    };

} // namespace mint
