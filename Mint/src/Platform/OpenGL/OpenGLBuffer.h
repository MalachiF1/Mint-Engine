#pragma once

#include "Mint/Renderer/Buffer.h"

namespace mint
{

    // Vertex Buffer
    // ----------------------------------------------------------------------------

    class OpenGLVertexBuffer : public VertexBuffer
    {
      public:
        OpenGLVertexBuffer(size_t size);
        OpenGLVertexBuffer(const void* vertices, size_t size);
        virtual ~OpenGLVertexBuffer() final;

        virtual void bind() const override final;
        virtual void unbind() const override final;

        inline virtual const BufferLayout& getLayout() const override final { return m_layout; }
        inline virtual void setLayout(const BufferLayout& layout) override final { m_layout = layout; };

        virtual void setData(const void* data, size_t size) override final;

      private:
        uint32_t m_rendererID;
        BufferLayout m_layout;
    };

    // Index Buffer
    // ----------------------------------------------------------------------------

    class OpenGLIndexBuffer : public IndexBuffer
    {
      public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer() final;

        virtual void bind() const override final;
        virtual void unbind() const override final;

        inline virtual uint32_t getCount() const override final { return m_count; }

      private:
        uint32_t m_rendererID;
        uint32_t m_count;
    };

} // namespace mint
