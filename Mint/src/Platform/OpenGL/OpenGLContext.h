#pragma once

#include "Mint/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace mint
{

    class OpenGLContext : public RenderingContext
    {
      public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void init() override final;
        virtual void swapBuffers() override final;

      private:
        GLFWwindow* m_windowHandle;
    };

} // namespace mint
