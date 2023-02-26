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
        virtual ~OpenGLVertexBuffer();

        virtual void bind() const override;
        virtual void unbind() const override;

      private:
        uint32_t m_rendererID;
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
