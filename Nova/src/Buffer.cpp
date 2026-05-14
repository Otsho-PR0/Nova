#include <Buffer.hpp>

VertexBuffer::VertexBuffer(RendererContext& context, Vertex* vertices, size_t size)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = (UINT)size;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = vertices;

	context.GetDevice()->CreateBuffer(&desc, &data, &m_Buffer);
}

void VertexBuffer::Bind(RendererContext& context)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0u;
	context.GetContext()->IASetVertexBuffers(0u, 1u, &m_Buffer, &stride, &offset);
}

IndexBuffer::IndexBuffer(RendererContext& context, unsigned int* indices, size_t size)
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

	context.GetDevice()->CreateBuffer(&desc, &data, &m_Buffer);
}

void IndexBuffer::Bind(RendererContext& context)
{
	context.GetContext()->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0u);
}
