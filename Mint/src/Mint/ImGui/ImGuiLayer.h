#pragma once

#include "Mint/Core.h"
#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/KeyEvent.h"
#include "Mint/Event/MouseEvent.h"
#include "Mint/Layer.h"

namespace mint
{

    class MINT_API ImGuiLayer : public Layer
    {

      public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void onAttach();
        virtual void onDetach();

        virtual void onUpdate() override;
        virtual void onEvent(Event& e) override;

      private:
        bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool onMouseMovedEvent(MouseMovedEvent& e);
        bool onMouseScrolledEvent(MouseScrolledEvent& e);

        bool onKeyTypedEvent(KeyTypedEvent& e);
        bool onKeyReleasedEvent(KeyReleasedEvent& e);
        bool onKeyPressedEvent(KeyPressedEvent& e);

        bool onWindowResizedEvent(WindowResizeEvent& e);

      private:
        float m_time = 0.0f;
    };

} // namespace mint
