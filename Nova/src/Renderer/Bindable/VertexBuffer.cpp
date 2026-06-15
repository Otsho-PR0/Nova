#include <Renderer/Bindable/VertexBuffer.hpp>

using namespace Nova;

VertexBuffer::VertexBuffer(RendererContext& context, void* vertices, size_t stride, size_t size) :
	m_Stride((UINT)stride)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = (UINT)size;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = (UINT)stride;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = vertices;

	context.GetDevice()->CreateBuffer(&desc, &data, m_Buffer.GetAddressOf());
}

void VertexBuffer::Bind(RendererContext& context)
{
	UINT stride = m_Stride;
	UINT offset = 0u;
	context.GetContext()->IASetVertexBuffers(0u, 1u, m_Buffer.GetAddressOf(), &stride, &offset);
}
