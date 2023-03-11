#include "mtpch.h"

#include "Mint/Core/Application.h"
#include "Mint/Core/Input.h"

#include <GLFW/glfw3.h>

namespace mint
{

bool Input::isKeyPressed(int keycode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

    int state = glfwGetKey(window, keycode);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMouseButtonPressed(int button)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

    int state = glfwGetMouseButton(window, button);

    return state == GLFW_PRESS;
}

float Input::getMouseX()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return (float)xpos;
}

float Input::getMouseY()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return (float)ypos;
}

std::pair<float, float> Input::getMousePos()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return std::pair<float, float>((float)xpos, (float)ypos);
}

} // namespace mint
