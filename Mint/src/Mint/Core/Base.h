#pragma once

#include "Mint/Utility/Debug/DebugTrap.h"

#include <memory>

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

namespace mint
{

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

} // namespace mint
