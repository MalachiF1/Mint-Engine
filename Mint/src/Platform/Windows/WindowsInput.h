#pragma once

#include "Mint/Core/Input.h"

namespace mint
{

class WindowsInput final : public Input
{
  protected:
    virtual bool                    isKeyPressedImpl(int keycode) override;
    virtual bool                    isMouseButtonPressedImpl(int button) override;
    virtual float                   getMouseXImpl() override;
    virtual float                   getMouseYImpl() override;
    virtual std::pair<float, float> getMousePosImpl() override;
};

} // namespace mint
