#pragma once

#include "Mint/Core/Base.h"
#include "Mint/Core/Layer.h"
#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/KeyEvent.h"
#include "Mint/Event/MouseEvent.h"

namespace mint
{

    class ImGuiLayer : public Layer
    {

      public:
        ImGuiLayer();
        virtual ~ImGuiLayer() override final;

        virtual void onAttach() override final;
        virtual void onDetach() override final;

        void begin();
        void end();

      private:
        float m_time = 0.0f;
    };

} // namespace mint
