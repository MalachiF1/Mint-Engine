#pragma once

#include "Mint/Utility/Debug/DebugTrap.h"

#ifdef MT_PLATFORM_WINDOWS
    #ifdef MINT_BUILD_DLL
        #define MINT_API __declspec(dllexport)
    #else
        #define MINT_API __declspec(dllimport)
    #endif MINT_BUILD_DLL // MT_BUILD_DLL
#else
    #error Mint only supports windows at the moment.
#endif // MT_PLATFORM_WINDOWS

#ifdef MINT_ENABLE_ASSERT
    #define MINT_ASSERT(x, ...)                                                                                        \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                MINT_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                      \
                debug_trap();                                                                                          \
            }                                                                                                          \
        }
    #define MINT_CORE_ASSERT(x, ...)                                                                                   \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                MINT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                 \
                debug_trap();                                                                                          \
            }                                                                                                          \
        }
#else
    #define MINT_ASSERT(x, ...)
    #define MINT_CORE_ASSERT(x, ...)
#endif // MT_ENABLE_ASSERT

#define BIT(x) (1 << x)
