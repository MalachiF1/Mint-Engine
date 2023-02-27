#pragma once

#include "Mint/Renderer/Buffer.h"

namespace mint
{

    // Vertex Buffer
    // ----------------------------------------------------------------------------

    class OpenGLVertexBuffer : public VertexBuffer
    {
      public:
        OpenGLVertexBuffer(float* vertices, size_t size);
        virtual ~OpenGLVertexBuffer() final;

        virtual void bind() const override final;
        virtual void unbind() const override final;

        inline virtual const BufferLayout& getLayout() const override final { return m_layout; }
        inline virtual void setLayout(const BufferLayout& layout) override final { m_layout = layout; };

      private:
        uint32_t m_rendererID;
        BufferLayout m_layout;
    };

    // Index Buffer
    // ----------------------------------------------------------------------------

    class OpenGLIndexBuffer : public IndexBuffer
    {
      public:
        OpenGLIndexBuffer(uint32_t* indices, size_t count);
        virtual ~OpenGLIndexBuffer() final;

        virtual void bind() const override final;
        virtual void unbind() const override final;

        inline virtual size_t getCount() const override final { return m_count; }

      private:
        uint32_t m_rendererID;
        size_t m_count;
    };

} // namespace mint
