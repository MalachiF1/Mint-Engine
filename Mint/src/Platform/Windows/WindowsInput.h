#pragma once

#include "Mint/Core/Input.h"

namespace mint
{

    class WindowsInput : public Input
    {
      protected:
        virtual bool isKeyPressedImpl(int keycode) override final;
        virtual bool isMouseButtonPressedImpl(int button) override final;
        virtual float getMouseXImpl() override final;
        virtual float getMouseYImpl() override final;
        virtual std::pair<float, float> getMousePosImpl() override final;
    };

} // namespace mint
