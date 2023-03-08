#include "mtpch.h"

#include "OpenGLBuffer.h"

#include "GLCheck.h"

#include <glad/glad.h>

namespace mint
{

// Vertex Buffer
// ----------------------------------------------------------------------------

OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
{
    MINT_PROFILE_FUNCTION();

    glCheck(glCreateBuffers(1, &m_rendererID));
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    glCheck(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, size_t size)
{
    MINT_PROFILE_FUNCTION();

    glCheck(glCreateBuffers(1, &m_rendererID));
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    glCheck(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    MINT_PROFILE_FUNCTION();

    glCheck(glDeleteBuffers(1, &m_rendererID));
}

void OpenGLVertexBuffer::bind() const
{
    MINT_PROFILE_FUNCTION();

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void OpenGLVertexBuffer::unbind() const
{
    MINT_PROFILE_FUNCTION();

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void OpenGLVertexBuffer::setData(const void* data, size_t size)
{
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    glCheck(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}


// Index Buffer
// ----------------------------------------------------------------------------

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_count(count)
{
    MINT_PROFILE_FUNCTION();

    glCheck(glCreateBuffers(1, &m_rendererID));
    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
    glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    MINT_PROFILE_FUNCTION();

    glCheck(glDeleteBuffers(1, &m_rendererID));
}

void OpenGLIndexBuffer::bind() const
{
    MINT_PROFILE_FUNCTION();

    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void OpenGLIndexBuffer::unbind() const
{
    MINT_PROFILE_FUNCTION();

    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

} // namespace mint
