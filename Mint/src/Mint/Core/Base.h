#pragma once

#include "Mint/Utility/Debug/DebugTrap.h"

#ifdef MINT_DEBUG
    #define MINT_ENABLE_ASSERT
#endif

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

#define MINT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
