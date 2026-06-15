#include <Renderer/Bindable/IndexBuffer.hpp>

using namespace Nova;

IndexBuffer::IndexBuffer(RendererContext& context, unsigned int* indices, size_t size) :
	m_Count(size / sizeof(unsigned int))
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = (UINT)size;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = sizeof(unsigned int);

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = indices;

	context.GetDevice()->CreateBuffer(&desc, &data, m_Buffer.GetAddressOf());
}

void IndexBuffer::Bind(RendererContext& context)
{
	context.GetContext()->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}

size_t IndexBuffer::GetCount()
{
	return m_Count;
}
