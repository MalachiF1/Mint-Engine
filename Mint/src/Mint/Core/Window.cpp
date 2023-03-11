#include "mtpch.h"

#include "Window.h"

#ifdef MINT_PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsWindow.h"
#endif

namespace mint
{

Scope<Window> Window::create(const WindowProps& props)
{
#ifdef MINT_PLATFORM_WINDOWS
    return CreateScope<WindowsWindow>(props);
#else
    MINT_CORE_ASSERT(false, "Unkown platform");
    return nullptr;
#endif
}

} // namespace mint
