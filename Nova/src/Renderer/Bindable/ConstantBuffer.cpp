#include <Renderer/Bindable/ConstantBuffer.hpp>

using namespace Nova;

CBuffer::CBuffer(RendererContext& context, void* data, size_t size)
{
	if (size % 16 != 0)
		MessageBox(nullptr, "Constant Buffer should be 16bit aligned", "DirectX Error", MB_OK);

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = (UINT)size;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = data;

	context.GetDevice()->CreateBuffer(&desc, &sd, m_Buffer.GetAddressOf());
}

void CBuffer::Map(RendererContext& context, void* data, size_t size)
{
	if (size % 16 != 0)
		MessageBox(nullptr, "Constant Buffer should be 16bit aligned", "DirectX Error", MB_OK);

	D3D11_MAPPED_SUBRESOURCE ms;
	context.GetContext()->Map(m_Buffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms);
	memcpy(ms.pData, data, size);
	context.GetContext()->Unmap(m_Buffer.Get(), 0u);
}

VCBuffer::VCBuffer(RendererContext& context, void* data, size_t size) :
	CBuffer(context, data, size)
{
}

void VCBuffer::Bind(RendererContext& context)
{
	context.GetContext()->VSSetConstantBuffers(0u, 1u, m_Buffer.GetAddressOf());
}

PCBuffer::PCBuffer(RendererContext& context, void* data, size_t size) :
	CBuffer(context, data, size)
{
}

void PCBuffer::Bind(RendererContext& context)
{
	context.GetContext()->VSSetConstantBuffers(0u, 1u, m_Buffer.GetAddressOf());
}
