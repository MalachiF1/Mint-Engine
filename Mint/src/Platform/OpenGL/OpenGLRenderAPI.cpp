#include "mtpch.h"

#include "OpenGLRenderAPI.h"

#include "GLCheck.h"

#include <glad/glad.h>

namespace mint
{

void OpenGLRenderAPI::init()
{
    MINT_PROFILE_FUNCTION();

    glCheck(glEnable(GL_DEPTH_TEST));

    glCheck(glEnable(GL_BLEND));
    glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void OpenGLRenderAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glCheck(glViewport(x, y, width, height));
}

void OpenGLRenderAPI::setClearColor(glm::vec4& color)
{
    glCheck(glClearColor(color.r, color.g, color.b, color.a));
}

void OpenGLRenderAPI::clear()
{
    glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
{
    uint32_t count = indexCount == 0 ? vertexArray->getIndexBuffer()->getCount() : indexCount;
    glCheck(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}

} // namespace mint
