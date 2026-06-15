#pragma once

#include <Renderer/Drawable/Drawable.hpp>
#include <Renderer/Bindable/VertexBuffer.hpp>
#include <Renderer/Bindable/IndexBuffer.hpp>
#include <Renderer/Bindable/InputLayout.hpp>
#include <Renderer/Bindable/ConstantBuffer.hpp>

#include <Math/Vec3.hpp>

#include <Transform.hpp>

namespace Nova
{
	struct NOVA_API Vertex
	{
		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector2 texCoords;
	};

	class NOVA_API Mesh : public IDrawable
	{
	public:
		Mesh() = default;
		Mesh(RendererContext& context, Vertex* vertices, const size_t& vSize, unsigned int* indices, const size_t& iSize, const Transform& transform = {});

		void Update(RendererContext& context);
		void Draw(RendererContext& context);

		Transform transform;

		static Mesh Cube(RendererContext& context, const Transform& transform = {});

	private:
		Mesh(RendererContext& context, const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer, const Transform& transform = {});
		friend class RendererContext;
		static InputLayout  il;
		VertexBuffer vb;
		IndexBuffer  ib;
		VCBuffer     cb;
	};
}