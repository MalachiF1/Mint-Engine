#pragma once

#include "Mint/Core/Application.h"
#include "Mint/Core/Base.h"

#ifdef MINT_PLATFORM_WINDOWS

extern mint::Application* mint::createApplication();

int main(int argc, char** argv)
{
    // Initialize logging
    mint::Log::init();
    MINT_CORE_WARN("Initialized Log!");

    auto app = mint::createApplication();
    app->run();
    delete app;
}

#else
    #error Mint only supports windows at the moment.
#endif // MINT_PLATFORM_WINDOWS
