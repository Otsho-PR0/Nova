#pragma once

#include <Shader.hpp>

struct Vertex
{
	float x, y;
	float r, g, b;
};

class NOVA_API VertexBuffer
{
public:
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer() = default;
	VertexBuffer(RendererContext& context, Vertex* vertices, size_t size);

	VertexBuffer& operator=(const VertexBuffer&) = delete;

	void Bind(RendererContext& context);

private:
	ID3D11Buffer* m_Buffer;
};

class NOVA_API IndexBuffer
{
public:
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer() = default;
	IndexBuffer(RendererContext& context, unsigned int* indices, size_t size);

	IndexBuffer& operator=(const IndexBuffer&) = delete;

	void Bind(RendererContext& context);

private:
	ID3D11Buffer* m_Buffer;
};

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