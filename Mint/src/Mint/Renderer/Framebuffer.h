#pragma once

#include "Mint/Core/Base.h"

namespace mint
{

struct FramebufferSpecification
{
    uint32_t width, height;
    uint32_t samples = 1;

    bool swapChainTarget = false;
};

class Framebuffer
{
  public:
    virtual ~Framebuffer() = default;

    virtual void bind()   = 0;
    virtual void unbind() = 0;

    virtual uint32_t getColorAttachment() const = 0;

    virtual const FramebufferSpecification& getSpecification() const = 0;

    static Ref<Framebuffer> create(const FramebufferSpecification& spec);
};

} // namespace mint
