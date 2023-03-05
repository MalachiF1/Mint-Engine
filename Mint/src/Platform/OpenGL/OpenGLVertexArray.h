#pragma once

#include "Mint/Renderer/VertexArray.h"

namespace mint
{

    class OpenGLVertexArray : public VertexArray
    {
      public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() final;

        virtual void bind() const override final;
        virtual void unbind() const override final;

        inline virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override final
        {
            return m_vertexBuffers;
        }
        inline virtual std::vector<Ref<VertexBuffer>>& getVertexBuffers() override final { return m_vertexBuffers; }
        inline virtual const Ref<IndexBuffer>& getIndexBuffer() const override final { return m_indexBuffer; }
        inline virtual Ref<IndexBuffer>& getIndexBuffer() override final { return m_indexBuffer; }

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override final;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override final;

      private:
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
        uint32_t m_rendererID;
    };

} // namespace mint
