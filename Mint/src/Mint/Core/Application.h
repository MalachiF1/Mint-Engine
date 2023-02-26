#pragma once

#include "Mint/Core/Base.h"
#include "Mint/Core/LayerStack.h"
#include "Mint/Core/Window.h"
#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/Event.h"
#include "Mint/ImGui/ImGuiLayer.h"
#include "Mint/Renderer/Buffer.h"
#include "Mint/Renderer/Shader.h"
#include "Mint/Renderer/VertexArray.h"

namespace mint
{

    class Application
    {
      public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event& e);

        bool onWindowClose(WindowCloseEvent& e);

        void pushLayer(Layer* layer);
        void popLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popOverlay(Layer* overlay);

        inline static Application& get() { return *s_instance; }
        inline Window& getWindow() const { return *m_window; }

      private:
        bool m_running = true;
        std::unique_ptr<Window> m_window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_layerStack;
        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<VertexArray> m_vertexArrray;

      private:
        static Application* s_instance;
    };

    // To be defined in client
    Application* createApplication();

} // namespace mint
