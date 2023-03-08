#pragma once

#include "Mint/Renderer/Texture.h"

#include <glm/glm.hpp>

namespace mint
{

class SubTexture2D
{
  public:
    SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) : m_texture(texture)
    {
        m_texCoords[0] = {min.x, min.y};
        m_texCoords[1] = {max.x, min.y};
        m_texCoords[2] = {max.x, max.y};
        m_texCoords[3] = {min.x, max.y};
    }

    static Ref<SubTexture2D> createFromCoords(
        const Ref<Texture2D>& texture,
        const glm::vec2&      spriteLocation,
        const glm::vec2&      cellSize,
        const glm::vec2&      spriteSize = {1.0f, 1.0f}
    )
    {
        auto [sheetWidth, sheetHeight] = texture->getSize();

        glm::vec2 min((spriteLocation.x * cellSize.x) / sheetWidth, (spriteLocation.y * cellSize.y) / sheetHeight);
        glm::vec2 max(
            ((spriteLocation.x + spriteSize.x) * cellSize.x) / (float)sheetWidth,
            ((spriteLocation.y + spriteSize.y) * cellSize.y) / (float)sheetHeight
        );

        return CreateRef<SubTexture2D>(texture, min, max);
    }

    const Ref<Texture2D>& getTexture() const { return m_texture; }
    const glm::vec2*      getTexCoords() const { return m_texCoords; }

  private:
    Ref<Texture2D> m_texture;
    glm::vec2      m_texCoords[4];
};

} // namespace mint
