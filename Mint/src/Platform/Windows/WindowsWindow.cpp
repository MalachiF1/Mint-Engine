#include "mtpch.h"

#include "WindowsWindow.h"

#include "Mint/Core/Base.h"
#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/KeyEvent.h"
#include "Mint/Event/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace mint
{

    static uint8_t s_GLFWWindowsCount = 0;

    void GLFWErrorCallback(int error, const char* discription)
    {
        MINT_CORE_ERROR("GLFW ERROR ({0}): {1}", error, discription);
    }

    Scope<Window> Window::create(const WindowProps& props)
    {
        return CreateScope<WindowsWindow>(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        MINT_PROFILE_FUNCTION();

        init(props);
    }


    WindowsWindow::~WindowsWindow()
    {
        MINT_PROFILE_FUNCTION();

        shutdown();
    }

    void WindowsWindow::init(const WindowProps& props)
    {
        MINT_PROFILE_FUNCTION();

        m_data.title  = props.title;
        m_data.width  = props.width;
        m_data.height = props.height;

        MINT_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (s_GLFWWindowsCount == 0)
        {
            MINT_PROFILE_SCOPE("glfwInit");

            int success = glfwInit();
            MINT_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            MINT_PROFILE_SCOPE("glfwCreateWindow");

            m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowsCount;
        }

        m_context = new OpenGLContext(m_window);
        m_context->init();


        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.width  = width;
            data.height = height;

            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int modes) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    // TODO: extract repeat count
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int key) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(key);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int modes) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)x, (float)y);
            data.eventCallback(event);
        });
    }

    void WindowsWindow::shutdown()
    {
        MINT_PROFILE_FUNCTION();

        {
            MINT_PROFILE_SCOPE("glfwDestroyWindow");
            glfwDestroyWindow(m_window);
        }
        --s_GLFWWindowsCount;

        if (s_GLFWWindowsCount == 0)
        {
            glfwTerminate();
        }
    }

    void WindowsWindow::onUpdate()
    {
        MINT_PROFILE_FUNCTION();

        {
            MINT_PROFILE_SCOPE("glfwPollEvents");
            glfwPollEvents();
        }

        m_context->swapBuffers();
    }

    void WindowsWindow::setVSync(bool enabled)
    {
        MINT_PROFILE_FUNCTION();

        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_data.VSync = enabled;
    }

} // namespace mint
