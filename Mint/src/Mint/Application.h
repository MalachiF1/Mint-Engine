#pragma once

#include "Core.h"
#include "Window.h"

namespace mint
{

    class MINT_API Application
    {
      public:
        Application();
        virtual ~Application();

        void run();

      private:
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    // To be defined in client
    Application* createApplication();

} // namespace mint
