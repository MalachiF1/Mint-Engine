#pragma once

#include "Mint/Core.h"
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
        float m_time = 0.0f;
    };

} // namespace mint
