#pragma once

#include <Renderer/Bindable/Bindable.hpp>
#include <Renderer/Bindable/Shader.hpp>

namespace Nova
{
	class NOVA_API InputLayout : public IBindable
	{
	public:
		InputLayout(InputLayout const&) = delete;
		InputLayout() = default;
		InputLayout(RendererContext& context, D3D11_INPUT_ELEMENT_DESC* elements, size_t size, VertexShader& shader);

		void Bind(RendererContext& context);

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	};
}