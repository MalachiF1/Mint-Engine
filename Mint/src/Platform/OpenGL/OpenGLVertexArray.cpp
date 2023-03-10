#include "mtpch.h"

#include "OpenGLVertexArray.h"

#include "GLCheck.h"

#include <glad/glad.h>

namespace mint
{

static GLenum shaderDataTypeToOpenGLDataType(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Int: return GL_INT;
        case ShaderDataType::Int2: return GL_INT;
        case ShaderDataType::Int3: return GL_INT;
        case ShaderDataType::Int4: return GL_INT;
        case ShaderDataType::Mat3: return GL_FLOAT;
        case ShaderDataType::Mat4: return GL_FLOAT;
        case ShaderDataType::Bool: return GL_BOOL;
    }

    MINT_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    MINT_PROFILE_FUNCTION();

    glCheck(glCheck(glCreateVertexArrays(1, &m_rendererID)));
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    MINT_PROFILE_FUNCTION();

    glCheck(glDeleteVertexArrays(1, &m_rendererID));
}

void OpenGLVertexArray::bind() const
{
    MINT_PROFILE_FUNCTION();

    glCheck(glBindVertexArray(m_rendererID));
}

void OpenGLVertexArray::unbind() const
{
    MINT_PROFILE_FUNCTION();

    glCheck(glBindVertexArray(0));
}

void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
    MINT_PROFILE_FUNCTION();

    MINT_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "vertexBuffer must have a layout!");

    glCheck(glBindVertexArray(m_rendererID));
    vertexBuffer->bind();

    uint32_t    index  = 0;
    const auto& layout = vertexBuffer->getLayout();
    for (const auto& element : layout.getElements())
    {
        glCheck(glEnableVertexAttribArray(index));
        glCheck(glVertexAttribPointer(
            index,
            element.getComponentCount(),
            shaderDataTypeToOpenGLDataType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            layout.getStride(),
            (const void*)element.offset
        ));
        ++index;
    }

    m_vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
    MINT_PROFILE_FUNCTION();

    glCheck(glBindVertexArray(m_rendererID));
    indexBuffer->bind();

    m_indexBuffer = indexBuffer;
}

} // namespace mint
