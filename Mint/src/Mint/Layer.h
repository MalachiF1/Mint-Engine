#pragma once

#include "Mint/Core.h"
#include "Mint/Event/Event.h"

namespace mint
{

    class MINT_API Layer
    {
      public:
        Layer(const std::string& name = "Layer") : m_debugName(name){};
        virtual ~Layer(){};

        virtual void onAttach()        = 0;
        virtual void onDetach()        = 0;
        virtual void onUpdate()        = 0;
        virtual void onEvent(Event& e) = 0;

        inline const std::string& getName() const { return m_debugName; }

      private:
        std::string m_debugName;
    };

} // namespace mint
