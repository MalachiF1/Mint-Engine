#include "EditorLayer.h"

#include <Mint.h>
#include <Mint/Core/EntryPoint.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

namespace mint
{

class Spearmint final : public Application
{
  public:
    Spearmint() : Application("Spearmint")
    {
        // pushLayer(new ExampleLayer());
        pushLayer(new EditorLayer());
    }

    virtual ~Spearmint() = default;
};


Application* createApplication()
{
    return new Spearmint();
}

} // namespace mint
