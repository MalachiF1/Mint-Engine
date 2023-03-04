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
        MINT_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
        MINT_CORE_ASSERT(status, "Failed to initialize glad");

        MINT_CORE_INFO("OpenGL Info:");
        MINT_CORE_INFO("    Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        MINT_CORE_INFO("    Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        MINT_CORE_INFO("    Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::swapBuffers()
    {
        MINT_PROFILE_FUNCTION();

        glfwSwapBuffers(m_windowHandle);
    }

} // namespace mint