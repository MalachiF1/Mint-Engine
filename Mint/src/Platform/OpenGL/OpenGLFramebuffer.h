#pragma once

#include "Mint/Renderer/Framebuffer.h"

namespace mint
{

    class OpenGLFramebuffer : public Framebuffer
    {
      public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer() override final;

        inline virtual const FramebufferSpecification& getSpecification() const override final
        {
            return m_specification;
        }

        inline virtual uint32_t getColorAttachment() const override final { return m_colorAttachment; }

        void invalidate();

        virtual void bind() override final;
        void unbind() override final;

      private:
        uint32_t m_rendererID;
        uint32_t m_colorAttachment, m_depthAttachment;
        FramebufferSpecification m_specification;
    };

} // namespace mint
