#pragma once

#include "Mint/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace mint
{

class OpenGLContext final : public RenderingContext
{
  public:
    OpenGLContext(GLFWwindow* windowHandle);

    virtual void init() override;
    virtual void swapBuffers() override;

  private:
    GLFWwindow* m_windowHandle;
};

} // namespace mint
