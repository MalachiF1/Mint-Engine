#include "mtpch.h"

#include "OpenGLFramebuffer.h"

#include "GLCheck.h"

#include <glad/glad.h>

namespace mint
{

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec) : m_specification(spec)
{
    invalidate();
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
    glCheck(glDeleteFramebuffers(1, &m_rendererID));
}

void OpenGLFramebuffer::invalidate()
{
    glCheck(glCreateFramebuffers(1, &m_rendererID));
    glCheck(glBindFramebuffer(GL_TEXTURE_2D, m_rendererID));

    glCheck(glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment));
    glCheck(glBindTexture(GL_TEXTURE_2D, m_colorAttachment));
    glCheck(glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.width, m_specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr
    ));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    glCheck(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0));

    glCheck(glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment));
    glCheck(glBindTexture(GL_TEXTURE_2D, m_depthAttachment));
    glCheck(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height));
    glCheck(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0));

    MINT_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

    glCheck(glBindFramebuffer(GL_TEXTURE_2D, 0));
}

void OpenGLFramebuffer::bind()
{
    glCheck(glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID));
}

void OpenGLFramebuffer::unbind()
{
    glCheck(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

} // namespace mint
