#pragma once

#include <Core/Window.hpp>
#include <Renderer/Renderer.hpp>
#include <Renderer/Drawable/Mesh.hpp>
#include <Renderer/Bindable/Shader.hpp>
#include <Camera.hpp>

class Editor
{
public:	
	Editor();
	~Editor();

	void Run();

private:
	Nova::Window window;
	Nova::RendererContext context;
	Nova::Mesh cube1;
	Nova::Mesh cube2;
	Nova::VertexShader vs;
	Nova::PixelShader ps;
	Nova::Camera camera;

	void Update();
	void Render();
};