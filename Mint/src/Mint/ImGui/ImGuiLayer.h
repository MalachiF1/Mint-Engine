#pragma once

#include "Mint/Core/Base.h"
#include "Mint/Core/Layer.h"
#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/KeyEvent.h"
#include "Mint/Event/MouseEvent.h"

namespace mint
{

class ImGuiLayer final : public Layer
{

  public:
    ImGuiLayer();
    virtual ~ImGuiLayer() override;

    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onEvent(Event& e) override;

    void begin();
    void end();

    inline void setBlockEvents(bool block) { m_blockEvents = block; }

  private:
    bool m_blockEvents = true;
    float m_time       = 0.0f;
};

} // namespace mint
