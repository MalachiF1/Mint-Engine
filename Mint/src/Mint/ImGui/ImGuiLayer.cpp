#include "mtpch.h"

#include "ImGuiLayer.h"

#include "Mint/Application.h"
#include "Mint/KeyCodes.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace mint
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

    ImGuiLayer::~ImGuiLayer() {}


    void ImGuiLayer::onAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab]            = MINT_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow]      = MINT_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow]     = MINT_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow]        = MINT_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow]      = MINT_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp]         = MINT_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown]       = MINT_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home]           = MINT_KEY_HOME;
        io.KeyMap[ImGuiKey_End]            = MINT_KEY_END;
        io.KeyMap[ImGuiKey_Insert]         = MINT_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete]         = MINT_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace]      = MINT_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space]          = MINT_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter]          = MINT_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape]         = MINT_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_Apostrophe]     = MINT_KEY_APOSTROPHE;
        io.KeyMap[ImGuiKey_Comma]          = MINT_KEY_COMMA;
        io.KeyMap[ImGuiKey_Minus]          = MINT_KEY_MINUS;
        io.KeyMap[ImGuiKey_Period]         = MINT_KEY_PERIOD;
        io.KeyMap[ImGuiKey_Slash]          = MINT_KEY_SLASH;
        io.KeyMap[ImGuiKey_Semicolon]      = MINT_KEY_SEMICOLON;
        io.KeyMap[ImGuiKey_Equal]          = MINT_KEY_EQUAL;
        io.KeyMap[ImGuiKey_LeftBracket]    = MINT_KEY_LEFT_BRACKET;
        io.KeyMap[ImGuiKey_Backslash]      = MINT_KEY_BACKSLASH;
        io.KeyMap[ImGuiKey_RightBracket]   = MINT_KEY_RIGHT_BRACKET;
        io.KeyMap[ImGuiKey_GraveAccent]    = MINT_KEY_GRAVE_ACCENT;
        io.KeyMap[ImGuiKey_CapsLock]       = MINT_KEY_CAPS_LOCK;
        io.KeyMap[ImGuiKey_ScrollLock]     = MINT_KEY_SCROLL_LOCK;
        io.KeyMap[ImGuiKey_NumLock]        = MINT_KEY_NUM_LOCK;
        io.KeyMap[ImGuiKey_PrintScreen]    = MINT_KEY_PRINT_SCREEN;
        io.KeyMap[ImGuiKey_Pause]          = MINT_KEY_PAUSE;
        io.KeyMap[ImGuiKey_Keypad0]        = MINT_KEY_KP_0;
        io.KeyMap[ImGuiKey_Keypad1]        = MINT_KEY_KP_1;
        io.KeyMap[ImGuiKey_Keypad2]        = MINT_KEY_KP_2;
        io.KeyMap[ImGuiKey_Keypad3]        = MINT_KEY_KP_3;
        io.KeyMap[ImGuiKey_Keypad4]        = MINT_KEY_KP_4;
        io.KeyMap[ImGuiKey_Keypad5]        = MINT_KEY_KP_5;
        io.KeyMap[ImGuiKey_Keypad6]        = MINT_KEY_KP_6;
        io.KeyMap[ImGuiKey_Keypad7]        = MINT_KEY_KP_7;
        io.KeyMap[ImGuiKey_Keypad8]        = MINT_KEY_KP_8;
        io.KeyMap[ImGuiKey_Keypad9]        = MINT_KEY_KP_9;
        io.KeyMap[ImGuiKey_KeypadDecimal]  = MINT_KEY_KP_DECIMAL;
        io.KeyMap[ImGuiKey_KeypadDivide]   = MINT_KEY_KP_DIVIDE;
        io.KeyMap[ImGuiKey_KeypadMultiply] = MINT_KEY_KP_MULTIPLY;
        io.KeyMap[ImGuiKey_KeypadSubtract] = MINT_KEY_KP_SUBTRACT;
        io.KeyMap[ImGuiKey_KeypadAdd]      = MINT_KEY_KP_ADD;
        io.KeyMap[ImGuiKey_KeypadEnter]    = MINT_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_KeypadEqual]    = MINT_KEY_KP_EQUAL;
        io.KeyMap[ImGuiKey_LeftShift]      = MINT_KEY_LEFT_SHIFT;
        io.KeyMap[ImGuiKey_LeftCtrl]       = MINT_KEY_LEFT_CONTROL;
        io.KeyMap[ImGuiKey_LeftAlt]        = MINT_KEY_LEFT_ALT;
        io.KeyMap[ImGuiKey_LeftSuper]      = MINT_KEY_LEFT_SUPER;
        io.KeyMap[ImGuiKey_RightShift]     = MINT_KEY_RIGHT_SHIFT;
        io.KeyMap[ImGuiKey_RightCtrl]      = MINT_KEY_RIGHT_CONTROL;
        io.KeyMap[ImGuiKey_RightAlt]       = MINT_KEY_RIGHT_ALT;
        io.KeyMap[ImGuiKey_RightSuper]     = MINT_KEY_RIGHT_SUPER;
        io.KeyMap[ImGuiKey_Menu]           = MINT_KEY_MENU;
        io.KeyMap[ImGuiKey_0]              = MINT_KEY_0;
        io.KeyMap[ImGuiKey_1]              = MINT_KEY_1;
        io.KeyMap[ImGuiKey_2]              = MINT_KEY_2;
        io.KeyMap[ImGuiKey_3]              = MINT_KEY_3;
        io.KeyMap[ImGuiKey_4]              = MINT_KEY_4;
        io.KeyMap[ImGuiKey_5]              = MINT_KEY_5;
        io.KeyMap[ImGuiKey_6]              = MINT_KEY_6;
        io.KeyMap[ImGuiKey_7]              = MINT_KEY_7;
        io.KeyMap[ImGuiKey_8]              = MINT_KEY_8;
        io.KeyMap[ImGuiKey_9]              = MINT_KEY_9;
        io.KeyMap[ImGuiKey_A]              = MINT_KEY_A;
        io.KeyMap[ImGuiKey_B]              = MINT_KEY_B;
        io.KeyMap[ImGuiKey_C]              = MINT_KEY_C;
        io.KeyMap[ImGuiKey_D]              = MINT_KEY_D;
        io.KeyMap[ImGuiKey_E]              = MINT_KEY_E;
        io.KeyMap[ImGuiKey_F]              = MINT_KEY_F;
        io.KeyMap[ImGuiKey_G]              = MINT_KEY_G;
        io.KeyMap[ImGuiKey_H]              = MINT_KEY_H;
        io.KeyMap[ImGuiKey_I]              = MINT_KEY_I;
        io.KeyMap[ImGuiKey_J]              = MINT_KEY_J;
        io.KeyMap[ImGuiKey_K]              = MINT_KEY_K;
        io.KeyMap[ImGuiKey_L]              = MINT_KEY_L;
        io.KeyMap[ImGuiKey_M]              = MINT_KEY_M;
        io.KeyMap[ImGuiKey_N]              = MINT_KEY_N;
        io.KeyMap[ImGuiKey_O]              = MINT_KEY_O;
        io.KeyMap[ImGuiKey_P]              = MINT_KEY_P;
        io.KeyMap[ImGuiKey_Q]              = MINT_KEY_Q;
        io.KeyMap[ImGuiKey_R]              = MINT_KEY_R;
        io.KeyMap[ImGuiKey_S]              = MINT_KEY_S;
        io.KeyMap[ImGuiKey_T]              = MINT_KEY_T;
        io.KeyMap[ImGuiKey_U]              = MINT_KEY_U;
        io.KeyMap[ImGuiKey_V]              = MINT_KEY_V;
        io.KeyMap[ImGuiKey_W]              = MINT_KEY_W;
        io.KeyMap[ImGuiKey_X]              = MINT_KEY_X;
        io.KeyMap[ImGuiKey_Y]              = MINT_KEY_Y;
        io.KeyMap[ImGuiKey_Z]              = MINT_KEY_Z;
        io.KeyMap[ImGuiKey_F1]             = MINT_KEY_F1;
        io.KeyMap[ImGuiKey_F2]             = MINT_KEY_F2;
        io.KeyMap[ImGuiKey_F3]             = MINT_KEY_F3;
        io.KeyMap[ImGuiKey_F4]             = MINT_KEY_F4;
        io.KeyMap[ImGuiKey_F5]             = MINT_KEY_F5;
        io.KeyMap[ImGuiKey_F6]             = MINT_KEY_F6;
        io.KeyMap[ImGuiKey_F7]             = MINT_KEY_F7;
        io.KeyMap[ImGuiKey_F8]             = MINT_KEY_F8;
        io.KeyMap[ImGuiKey_F9]             = MINT_KEY_F9;
        io.KeyMap[ImGuiKey_F10]            = MINT_KEY_F10;
        io.KeyMap[ImGuiKey_F11]            = MINT_KEY_F11;
        io.KeyMap[ImGuiKey_F12]            = MINT_KEY_F12;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach() {}

    void ImGuiLayer::onUpdate()
    {
        ImGuiIO& io          = ImGui::GetIO();
        Application& app     = Application::get();
        auto [width, height] = app.getWindow().getSize();
        io.DisplaySize       = ImVec2(width, height);

        float time   = (float)glfwGetTime();
        io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
        m_time       = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseButtonPressedEvent>(MINT_BIND_EVENT_FN(ImGuiLayer::onMouseButtonPressedEvent));
        dispatcher.dispatch<MouseButtonReleasedEvent>(MINT_BIND_EVENT_FN(ImGuiLayer::onMouseButtonReleasedEvent));
        dispatcher.dispatch<MouseMovedEvent>(MINT_BIND_EVENT_FN(ImGuiLayer::onMouseMovedEvent));
        dispatcher.dispatch<MouseScrolledEvent>(MINT_BIND_EVENT_FN(ImGuiLayer::onMouseScrolledEvent));
        dispatcher.dispatch<KeyTypedEvent>(MINT_BIND_EVENT_FN(ImGuiLayer::onKeyTypedEvent));
        dispatcher.dispatch<KeyReleasedEvent>(MINT_BIND_EVENT_FN(ImGuiLayer::onKeyReleasedEvent));
        dispatcher.dispatch<KeyPressedEvent>(MINT_BIND_EVENT_FN(ImGuiLayer::onKeyPressedEvent));
        dispatcher.dispatch<WindowResizeEvent>(MINT_BIND_EVENT_FN(ImGuiLayer::onWindowResizedEvent));
    }

    bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseDown[e.getMouseButton()] = true;

        // We don't want this function to consume the event
        return false;
    }

    bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseDown[e.getMouseButton()] = false;

        // We don't want this function to consume the event
        return false;
    }

    bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MousePos = ImVec2(e.getX(), e.getY());

        // We don't want this function to consume the event
        return false;
    }

    bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseWheel += e.getYOffset();
        io.MouseWheelH += e.getXOffset();

        // We don't want this function to consume the event
        return false;
    }

    bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.getKeyCode();
        if (keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned short)keycode);

        // We don't want this function to consume the event
        return false;
    }

    bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.KeysDown[e.getKeyCode()] = false;

        // We don't want this function to consume the event
        return false;
    }

    bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.KeysDown[e.getKeyCode()] = true;

        io.KeyCtrl  = io.KeysDown[MINT_KEY_LEFT_CONTROL] || io.KeysDown[MINT_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[MINT_KEY_LEFT_SHIFT] || io.KeysDown[MINT_KEY_RIGHT_SHIFT];
        io.KeyAlt   = io.KeysDown[MINT_KEY_LEFT_ALT] || io.KeysDown[MINT_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[MINT_KEY_LEFT_SUPER] || io.KeysDown[MINT_KEY_RIGHT_SUPER];

        // We don't want this function to consume the event
        return false;
    }

    bool ImGuiLayer::onWindowResizedEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize             = ImVec2(e.getWidth(), e.getHeight());
        io.DisplayFramebufferScale = ImVec2(1, 1);
        // Temporary -
        glViewport(0, 0, e.getWidth(), e.getHeight());

        // We don't want this function to consume the event
        return false;
    }

} // namespace mint
