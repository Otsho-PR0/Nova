#pragma once

#include <Window.hpp>
#include <Renderer.hpp>

class Editor
{
public:	
	Editor();
	~Editor();

	void Run();

private:
	Window window;
	RendererContext context;

	void Update();
	void Render();
};