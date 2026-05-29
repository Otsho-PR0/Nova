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

InputLayout::InputLayout(RendererContext& context, D3D11_INPUT_ELEMENT_DESC* elements, size_t size, VertexShader& shader)
{
	context.GetDevice()->CreateInputLayout(elements, (UINT)size / (UINT)sizeof(D3D11_INPUT_ELEMENT_DESC), shader.m_Blob->GetBufferPointer(), shader.m_Blob->GetBufferSize(), &m_InputLayout);
}

void InputLayout::Bind(RendererContext& context)
{
	context.GetContext()->IASetInputLayout(m_InputLayout);
}

CBuffer::CBuffer(RendererContext& context, void* data, size_t size)
{
	if (size % 16 != 0)
		MessageBox(nullptr, "Constant Buffer should be 16bit aligned", "DirectX Error", MB_OK);

	D3D11_BUFFER_DESC desc = {};
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = size;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = data;

	context.GetDevice()->CreateBuffer(&desc, &sd, &m_Buffer);
}

void CBuffer::Map(RendererContext& context, void* data, size_t size)
{
	if (size % 16 != 0)
		MessageBox(nullptr, "Constant Buffer should be 16bit aligned", "DirectX Error", MB_OK);

	D3D11_MAPPED_SUBRESOURCE ms;
	context.GetContext()->Map(m_Buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms);
	memcpy(ms.pData, data, size);
	context.GetContext()->Unmap(m_Buffer, 0u);
}

VCBuffer::VCBuffer(RendererContext& context, void* data, size_t size) :
	CBuffer(context, data, size)
{
}

void VCBuffer::Bind(RendererContext& context)
{
	context.GetContext()->VSSetConstantBuffers(0u, 1u, &m_Buffer);
}

PCBuffer::PCBuffer(RendererContext& context, void* data, size_t size) :
	CBuffer(context, data, size)
{
}

void PCBuffer::Bind(RendererContext& context)
{
	context.GetContext()->VSSetConstantBuffers(0u, 1u, &m_Buffer);
}
