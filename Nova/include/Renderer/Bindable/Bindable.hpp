#pragma once

#include <Renderer/Renderer.hpp>

#include <wrl/client.h>

class IBindable
{
public:
	virtual void Bind(Nova::RendererContext& context) = 0;
};