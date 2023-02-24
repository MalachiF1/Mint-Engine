#include <Mint.h>

class ExampleLayer : public mint::Layer
{
  public:
    ExampleLayer() : Layer("Example") {}

    virtual void onUpdate() override { MINT_INFO("ExamplerLayer::Update"); }
    virtual void onEvent(mint::Event& event) override { MINT_TRACE("{0}", event); }
    virtual void onAttach() override {}
    virtual void onDetach() override {}
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