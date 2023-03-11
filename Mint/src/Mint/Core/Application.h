#pragma once

#include "Mint/Core/Base.h"
#include "Mint/Core/LayerStack.h"
#include "Mint/Core/Window.h"
#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/Event.h"
#include "Mint/ImGui/ImGuiLayer.h"

namespace mint
{

class Application
{
  public:
    Application(const std::string& name = "Mint App");
    virtual ~Application();

    void run();
    void shutdown();

    void pushLayer(Layer* layer);
    void popLayer(Layer* layer);
    void pushOverlay(Layer* overlay);
    void popOverlay(Layer* overlay);

    inline static Application& get() { return *s_instance; }

    inline Window& getWindow() const { return *m_window; }

    inline ImGuiLayer* getImGuiLayer() { return m_ImGuiLayer; }

  private:
    void onEvent(Event& e);
    bool onWindowClose(WindowCloseEvent& e);
    bool onWindowResize(WindowResizeEvent& e);

  private:
    bool m_running   = true;
    bool m_minimized = false;
    Scope<Window> m_window;
    LayerStack m_layerStack;
    ImGuiLayer* m_ImGuiLayer;
    float m_lastFrameTime = 0.0f;

  private:
    static Application* s_instance;
};

// To be defined in client
Application* createApplication();

} // namespace mint
