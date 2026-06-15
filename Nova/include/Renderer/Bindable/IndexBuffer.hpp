#pragma once

#include <Renderer/Bindable/Bindable.hpp>

class NOVA_API IndexBuffer : public IBindable
{
public:
	IndexBuffer() = default;
	IndexBuffer(Nova::RendererContext& context, unsigned int* indices, size_t size);

	void Bind(Nova::RendererContext& context);

	size_t GetCount();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	size_t m_Count = 0u;
};
