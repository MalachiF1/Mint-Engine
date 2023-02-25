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
        virtual void onImGuiRender();

        void begin();
        void end();

      private:
        float m_time = 0.0f;
    };

} // namespace mint
