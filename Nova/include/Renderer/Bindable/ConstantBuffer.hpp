#pragma once

#include <Renderer/Bindable/Bindable.hpp>

class CBuffer : public IBindable
{
public:
	CBuffer(CBuffer const&) = delete;
	CBuffer() = default;
	CBuffer(Nova::RendererContext& context, void* data, size_t size);

	void Map(Nova::RendererContext& context, void* data, size_t size);

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
};

class VCBuffer : public CBuffer
{
public:
	VCBuffer(VCBuffer const&) = delete;
	VCBuffer() = default;
	VCBuffer(Nova::RendererContext& context, void* data, size_t size);
	VCBuffer& operator=(VCBuffer&&) = default;

	void Bind(Nova::RendererContext& context);
};

class PCBuffer : public CBuffer
{
public:
	PCBuffer(PCBuffer const&) = delete;
	PCBuffer() = default;
	PCBuffer(Nova::RendererContext& context, void* data, size_t size);
	PCBuffer& operator=(PCBuffer&&) = default;

	void Bind(Nova::RendererContext& context);
};
