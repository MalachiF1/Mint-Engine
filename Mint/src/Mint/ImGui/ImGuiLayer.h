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
