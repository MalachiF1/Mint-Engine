#include <Mint.h>
#include <imgui/imgui.h>

class ExampleLayer : public mint::Layer
{
  public:
    ExampleLayer() : Layer("Example") {}

    virtual void onUpdate() override
    {
        if (mint::Input::isKeyPressed(MINT_KEY_TAB))
            MINT_TRACE("TAB key was pressed! (Poll)");
    }

    virtual void onEvent(mint::Event& event) override
    {
        if (event.getEventType() == mint::EventType::KeyPressed)
        {
            mint::KeyPressedEvent& e = static_cast<mint::KeyPressedEvent&>(event);

            int keycode = e.getKeyCode();
            if (keycode == MINT_KEY_TAB)
                MINT_TRACE("Tab key was pressed! (Event)");
            else
                MINT_TRACE("{0}", (char)keycode);
        }
    }

    virtual void onImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello world");
        ImGui::End();
    }
};

class Sandbox : public mint::Application
{
  public:
    Sandbox() { pushLayer(new ExampleLayer); }

    virtual ~Sandbox() final {}
};


mint::Application* mint::createApplication()
{
    return new Sandbox();
}