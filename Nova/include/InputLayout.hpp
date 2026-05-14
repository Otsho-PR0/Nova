#pragma once

#include <Shader.hpp>

class NOVA_API InputLayout
{
public:
	InputLayout(const InputLayout&) = delete;
	InputLayout() = default;
	InputLayout(RendererContext& context, D3D11_INPUT_ELEMENT_DESC* elements, size_t size, VertexShader& shader);

	InputLayout& operator=(const InputLayout&) = delete;

	void Bind(RendererContext& context);

private:
	ID3D11InputLayout* m_InputLayout;
};