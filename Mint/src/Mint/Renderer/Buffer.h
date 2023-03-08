#pragma once

#include "Mint/Core/Base.h"

namespace mint
{

// Buffer Layout
// ----------------------------------------------------------------------------

enum class ShaderDataType
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Int2,
    Int3,
    Int4,
    Mat3,
    Mat4,
    Bool
};

static uint32_t shaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float: return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::Int: return 4;
        case ShaderDataType::Int2: return 4 * 2;
        case ShaderDataType::Int3: return 4 * 3;
        case ShaderDataType::Int4: return 4 * 4;
        case ShaderDataType::Mat3: return 4 * 3 * 3;
        case ShaderDataType::Mat4: return 4 * 4 * 4;
        case ShaderDataType::Bool: return 1;
    }

    MINT_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

struct BufferElement
{
    std::string    name;
    ShaderDataType type;
    bool           normalized;
    size_t         offset;
    uint32_t       size;

    BufferElement() = default;

    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) :
        name(name), type(type), normalized(normalized), size(shaderDataTypeSize(type)), offset(0)
    {
    }

    uint32_t getComponentCount() const
    {
        switch (type)
        {
            case ShaderDataType::Float: return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Int: return 1;
            case ShaderDataType::Int2: return 2;
            case ShaderDataType::Int3: return 3;
            case ShaderDataType::Int4: return 4;
            case ShaderDataType::Mat3: return 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4;
            case ShaderDataType::Bool: return 1;
        }

        MINT_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
};

class BufferLayout
{
    using Elements = std::vector<BufferElement>;

  public:
    BufferLayout() = default;

    BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements)
    {
        calculateOffsetAndStride();
    }

    inline const std::vector<BufferElement>& getElements() const { return m_elements; }
    inline uint32_t                          getStride() const { return m_stride; }

    Elements::const_iterator begin() const { return m_elements.begin(); }
    Elements::const_iterator end() const { return m_elements.begin(); }

  private:
    void calculateOffsetAndStride()
    {
        m_stride = 0;
        for (auto& element : m_elements)
        {
            element.offset = m_stride;
            m_stride += element.size;
        }
    }

  private:
    Elements m_elements;
    uint32_t m_stride = 0;
};


// Vertex Buffer
// ----------------------------------------------------------------------------

class VertexBuffer
{
  public:
    virtual ~VertexBuffer() {}

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual const BufferLayout& getLayout() const = 0;

    virtual void setLayout(const BufferLayout& layout)  = 0;
    virtual void setData(const void* data, size_t size) = 0;

    static Ref<VertexBuffer> create(size_t size);
    static Ref<VertexBuffer> create(const void* vertices, size_t size);
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

    static Ref<IndexBuffer> create(uint32_t* vertices, uint32_t count);
};

} // namespace mint
