#include "mtpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace mint
{

RenderAPI* RenderCommand::s_renderAPI = new OpenGLRenderAPI;

}
