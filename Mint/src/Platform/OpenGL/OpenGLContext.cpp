#include "mtpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace mint
{

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle)
    {
        MINT_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
        MINT_CORE_ASSERT(status, "Failed to initialize glad");
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }

} // namespace mint