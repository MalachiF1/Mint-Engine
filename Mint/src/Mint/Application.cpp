#include "mtpch.h"

#include "Application.h"

#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/Event.h"

namespace mint
{

    Application::Application() {}

    Application::~Application() {}


    void Application::run()
    {
        WindowResizeEvent e(1280, 720);
        if (e.isInCategory(EventCategoryApplication))
        {
            MINT_INFO("Yes");
        }
        else
        {
            MINT_INFO("No");
        }

        // MINT_TRACE(e);

        while (true) {};
    }

} // namespace mint
