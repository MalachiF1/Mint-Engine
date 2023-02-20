#pragma once

#include "Core.h"

namespace mint
{

    class MINT_API Application
    {
      public:
        Application();
        virtual ~Application();

        void run();
    };

    // To be defined in client
    Application* createApplication();

} // namespace mint
