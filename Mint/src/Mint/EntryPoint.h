#pragma once


#ifdef MT_PLATFORM_WINDOWS

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
#endif // MT_PLATFORM_WINDOWS
