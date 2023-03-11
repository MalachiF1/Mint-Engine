#pragma once

#include "Mint/Renderer/Framebuffer.h"

namespace mint
{

class OpenGLFramebuffer final : public Framebuffer
{
  public:
    OpenGLFramebuffer(const FramebufferSpecification& spec);
    virtual ~OpenGLFramebuffer() override;

    inline virtual const FramebufferSpecification& getSpecification() const override { return m_specification; }
    inline virtual uint32_t getColorAttachmentRendererID() const override { return m_colorAttachment; }

    virtual void bind() override;
    virtual void unbind() override;

    virtual void resize(uint32_t width, uint32_t height) override;

  private:
    void invalidate();

  private:
    uint32_t m_rendererID      = 0;
    uint32_t m_colorAttachment = 0;
    uint32_t m_depthAttachment = 0;
    FramebufferSpecification m_specification;
};

} // namespace mint
