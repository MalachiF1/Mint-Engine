#pragma once

namespace mint
{

class RenderingContext
{
  public:
    virtual ~RenderingContext() = default;

    virtual void init()        = 0;
    virtual void swapBuffers() = 0;
};

} // namespace mint
