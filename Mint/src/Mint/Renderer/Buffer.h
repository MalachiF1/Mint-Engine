#pragma once

namespace mint
{

    // Vertex Buffer
    // ----------------------------------------------------------------------------

    class VertexBuffer
    {
      public:
        virtual ~VertexBuffer() {}

        virtual void bind() const   = 0;
        virtual void unbind() const = 0;

        static VertexBuffer* create(float* vertices, size_t size);
    };

    // Index Buffer
    // ----------------------------------------------------------------------------
    class IndexBuffer
    {
      public:
        virtual ~IndexBuffer() {}

        virtual void bind() const   = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        static IndexBuffer* create(uint32_t* vertices, uint32_t count);
    };

} // namespace mint
