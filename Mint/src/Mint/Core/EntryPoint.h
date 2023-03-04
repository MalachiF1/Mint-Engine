#pragma once

#include "Mint/Core/Application.h"
#include "Mint/Core/Base.h"

#ifdef MINT_PLATFORM_WINDOWS

extern mint::Application* mint::createApplication();

int main(int argc, char** argv)
{
    // Initialize logging
    mint::Log::init();

    MINT_PROFILE_BEGIN_SESSION("Startup", "MintProfile-Startup.json");
    auto app = mint::createApplication();
    MINT_PROFILE_END_SESSION();

    MINT_PROFILE_BEGIN_SESSION("Runtime", "MintProfile-Runtime.json");
    app->run();
    MINT_PROFILE_END_SESSION();

    MINT_PROFILE_BEGIN_SESSION("Shutdown", "MintProfile-Shutdown.json");
    delete app;
    MINT_PROFILE_END_SESSION();
}

#else
    #error Mint only supports windows at the moment.
#endif // MINT_PLATFORM_WINDOWS
