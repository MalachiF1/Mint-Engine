#pragma once

#include "Mint/Utility/Debug/DebugTrap.h"

#include <filesystem>
#include <string_view>

namespace mint
{

#ifdef MINT_DEBUG
    #define glCheck(expr)                                                                                              \
        do {                                                                                                           \
            expr;                                                                                                      \
            mint::glCheckError(__FILE__, __LINE__, #expr);                                                             \
        } while (false)

#else
    #define glCheck(expr) (expr)

#endif


void glCheckError(const std::filesystem::path& file, unsigned int line, std::string_view expression);

} // namespace mint
