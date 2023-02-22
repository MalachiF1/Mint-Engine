#pragma once

#ifdef MT_PLATFORM_WINDOWS
    #ifdef MINT_BUILD_DLL
        #define MINT_API __declspec(dllexport)
    #else
        #define MINT_API __declspec(dllimport)
    #endif MINT_BUILD_DLL // MT_BUILD_DLL
#else
    #error Mint only supports windows at the moment.
#endif // MT_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
