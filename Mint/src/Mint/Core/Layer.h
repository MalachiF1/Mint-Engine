#pragma once

#include "Mint/Core/Base.h"
#include "Mint/Core/Timestep.h"
#include "Mint/Event/Event.h"

namespace mint
{

    class Layer
    {
      public:
        Layer(const std::string& name = "Layer") : m_debugName(name){};
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Timestep timestep) {}
        virtual void onEvent(Event& e) {}
        virtual void onImGuiRender() {}

        inline const std::string& getName() const { return m_debugName; }

      private:
        std::string m_debugName;
    };

} // namespace mint
