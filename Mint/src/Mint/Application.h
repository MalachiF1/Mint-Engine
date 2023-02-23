#pragma once

#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "Event/Event.h"
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
        void pushOverLay(Layer* overlay);
        void popOverLay(Layer* overlay);

      private:
        std::unique_ptr<Window> m_window;
        bool m_running = true;
        LayerStack m_layerStack;
    };

    // To be defined in client
    Application* createApplication();

} // namespace mint
