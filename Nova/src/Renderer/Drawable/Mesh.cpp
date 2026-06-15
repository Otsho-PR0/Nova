#include <Renderer/Drawable/Mesh.hpp>
#include <utility>

using namespace Nova;

InputLayout Mesh::il;

Mesh::Mesh(RendererContext& context, Vertex* vertices, const size_t& vSize, unsigned int* indices, const size_t& iSize, const Transform& transform) :
	transform(transform),
	vb(context, vertices, sizeof(Vertex), vSize),
	ib(context, indices, iSize)
{
	Math::Matrix data = transform.GetMVP();
	cb = std::move(VCBuffer(context, &data, sizeof(Math::Matrix)));
}

Mesh::Mesh(RendererContext& context, const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer, const Transform& transform) :
	transform(transform),
	vb(vertexBuffer),
	ib(indexBuffer)
{
	Math::Matrix data = transform.GetMVP();
	cb = std::move(VCBuffer(context, &data, sizeof(Math::Matrix)));
}

void Mesh::Update(RendererContext& context)
{
	Math::Matrix data = transform.GetMVP();
	cb.Map(context, &data, sizeof(Math::Matrix));
}

void Mesh::Draw(RendererContext& context)
{
	il.Bind(context);
	vb.Bind(context);
	ib.Bind(context);
	cb.Bind(context);
	context.GetContext()->DrawIndexed((UINT)ib.GetCount(), 0u, 0u);
}

Mesh Mesh::Cube(RendererContext& context, const Transform& transform)
{
	static Vertex vertices[] =
	{
		{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f } },
		{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f } },
		{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f } },
		{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f } },

		{ {  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f } },
		{ { -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
		{ {  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } },
		{ { -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f } },

		{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f } },
		{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f } },
		{ {  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f } },
		{ { -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f } },

		{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f } },
		{ {  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f } },
		{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f } },
		{ { -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f } },

		{ {  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },
		{ {  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f } },
		{ {  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f } },
		{ {  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },

		{ { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f } },
		{ { -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },
		{ { -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },
		{ { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f } },
	};

	static unsigned int indices[] =
	{
		 0u,  1u,  2u,  1u,  3u,  2u,
		 4u,  5u,  6u,  5u,  7u,  6u,
		 8u,  9u, 10u,  9u, 11u, 10u,
		12u, 13u, 14u, 13u, 15u, 14u,
		16u, 17u, 18u, 17u, 19u, 18u,
		20u, 21u, 22u, 21u, 23u, 22u
	};

	static VertexBuffer vb(context, vertices, sizeof(Vertex), sizeof(vertices));
	static IndexBuffer  ib(context, indices, sizeof(indices));

	return { context, vb, ib, transform };
}