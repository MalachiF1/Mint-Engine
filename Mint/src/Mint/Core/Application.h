#pragma once

#include "Mint/Core/Base.h"
#include "Mint/Core/LayerStack.h"
#include "Mint/Core/Timestep.h"
#include "Mint/Core/Window.h"
#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/Event.h"
#include "Mint/ImGui/ImGuiLayer.h"

namespace mint
{

    class Application
    {
      public:
        Application();
        virtual ~Application();

        void run();

        void pushLayer(Layer* layer);
        void popLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popOverlay(Layer* overlay);

        inline static Application& get() { return *s_instance; }
        inline Window& getWindow() const { return *m_window; }

      private:
        void onEvent(Event& e);
        bool onWindowClose(WindowCloseEvent& e);

      private:
        bool m_running = true;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_layerStack;
        Scope<Window> m_window;
        float m_lastFrameTime = 0.0f;

      private:
        static Application* s_instance;
    };

    // To be defined in client
    Application* createApplication();

} // namespace mint
