#pragma once

#include "Core.h"
#include "Window.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

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

      private:
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    // To be defined in client
    Application* createApplication();

} // namespace mint
