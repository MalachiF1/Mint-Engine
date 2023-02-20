#include <Mint.h>

class Sandbox : public mint::Application
{
  public:
    Sandbox() {}

    virtual ~Sandbox() final {}
};


mint::Application* mint::createApplication()
{
    return new Sandbox();
}