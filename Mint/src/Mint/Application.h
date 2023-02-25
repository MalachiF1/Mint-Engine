#pragma once

#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "Event/Event.h"
#include "Mint/ImGui/ImGuiLayer.h"
#include "Mint/LayerStack.h"
#include "Window.h"

namespace mint
{

    class MINT_API Application
    {
      public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event& e);

        bool onWindowClose(WindowCloseEvent& e);

        void pushLayer(Layer* layer);
        void popLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popOverlay(Layer* overlay);

        inline static Application& get() { return *s_instance; }
        inline Window& getWindow() const { return *m_window; }

      private:
        bool m_running = true;
        std::unique_ptr<Window> m_window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_layerStack;

      private:
        static Application* s_instance;
    };

    // To be defined in client
    Application* createApplication();

} // namespace mint
