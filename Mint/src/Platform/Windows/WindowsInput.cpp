#include "mtpch.h"

#include "WindowsInput.h"

#include "Mint/Core/Application.h"

#include <GLFW/glfw3.h>

namespace mint
{

Input* Input::s_instance = new WindowsInput();

bool WindowsInput::isKeyPressedImpl(int keycode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

    int state = glfwGetKey(window, keycode);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::isMouseButtonPressedImpl(int button)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

    int state = glfwGetMouseButton(window, button);

    return state == GLFW_PRESS;
}

float WindowsInput::getMouseXImpl()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    double      xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return (float)xpos;
}

float WindowsInput::getMouseYImpl()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    double      xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return (float)ypos;
}

std::pair<float, float> WindowsInput::getMousePosImpl()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    double      xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return std::pair<float, float>((float)xpos, (float)ypos);
}

} // namespace mint
