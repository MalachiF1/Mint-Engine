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
    inline virtual uint32_t                        getColorAttachment() const override { return m_colorAttachment; }

    void invalidate();

    virtual void bind() override;
    virtual void unbind() override;

  private:
    uint32_t                 m_rendererID;
    uint32_t                 m_colorAttachment, m_depthAttachment;
    FramebufferSpecification m_specification;
};

} // namespace mint
