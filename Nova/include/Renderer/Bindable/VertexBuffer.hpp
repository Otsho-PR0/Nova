#pragma once

#include <Renderer/Bindable/Bindable.hpp>

class NOVA_API VertexBuffer : public IBindable
{
public:
	VertexBuffer() = default;
	VertexBuffer(Nova::RendererContext& context, void* vertices, size_t structureSize, size_t size);

	void Bind(Nova::RendererContext& context);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	UINT m_Stride = 0u;
};
