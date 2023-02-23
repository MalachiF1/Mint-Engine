#pragma once

#include "Mint/Core.h"
#include "Mint/Event/Event.h"

namespace mint
{

    class MINT_API Layer
    {
      public:
        Layer(const std::string& name = "Layer") : m_debugName(m_debugName){};
        virtual ~Layer(){};

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& e) {}

        inline const std::string& getName() const { return m_debugName; }

      private:
        std::string m_debugName;
    };

} // namespace mint
