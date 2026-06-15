#pragma once

#include <Renderer/Renderer.hpp>

class IDrawable
{
public:
	virtual void Draw(Nova::RendererContext& context) = 0;
};