#pragma once

#include "Mint/Core/Base.h"

namespace mint
{

class Input
{
  public:
    static bool isKeyPressed(int keycode);
    static bool isMouseButtonPressed(int button);
    static float getMouseX();
    static float getMouseY();
    static std::pair<float, float> getMousePos();
};

} // namespace mint
