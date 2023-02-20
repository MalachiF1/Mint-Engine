#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>

#include <memory>

namespace mint
{

    class MINT_API Log
    {
      public:
        static void init();
        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
        inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

      private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };

} // namespace mint


// Core log macros
#define MINT_CORE_TRACE(...) ::mint::Log::getCoreLogger()->trace(__VA_ARGS__)
#define MINT_CORE_INFO(...) ::mint::Log::getCoreLogger()->info(__VA_ARGS__)
#define MINT_CORE_WARN(...) ::mint::Log::getCoreLogger()->warn(__VA_ARGS__)
#define MINT_CORE_ERROR(...) ::mint::Log::getCoreLogger()->error(__VA_ARGS__)
#define MINT_CORE_CRITICAL(...) ::mint::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MINT_TRACE(...) ::mint::Log::getClientLogger()->trace(__VA_ARGS__)
#define MINT_INFO(...) ::mint::Log::getClientLogger()->info(__VA_ARGS__)
#define MINT_WARN(...) ::mint::Log::getClientLogger()->warn(__VA_ARGS__)
#define MINT_ERROR(...) ::mint::Log::getClientLogger()->error(__VA_ARGS__)
#define MINT_CRITICAL(...) ::mint::Log::getClientLogger()->critical(__VA_ARGS__)
