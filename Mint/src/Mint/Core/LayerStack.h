#pragma once

#include "Mint/Core/Base.h"
#include "Mint/Core/Layer.h"

#include <vector>

namespace mint
{

    class LayerStack
    {
        friend class Application;

        using Layers = std::vector<Layer*>;

      public:
        LayerStack() = default;

        // TODO: find a better implementation that either doesn't take ownership of the layers, or keeps a unique_ptr to
        // each layer. As it stands, if you pop a layer and don't push it back, it won't get deleted in the constructor
        // as the LayerStack loses refrence to it.
        ~LayerStack();

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popLayer(Layer* layer);
        void popOverlay(Layer* overlay);

        inline Layers::const_iterator begin() { return m_layers.begin(); }
        inline Layers::const_iterator end() { return m_layers.begin(); }
        inline Layers::const_reverse_iterator rbegin() { return m_layers.rbegin(); }
        inline Layers::const_reverse_iterator rend() { return m_layers.rend(); }


      private:
        Layers m_layers;
        // Index of 1 after where we will place the next non overlay layer
        int m_layerInsertIndex = 0;
    };

} // namespace mint
