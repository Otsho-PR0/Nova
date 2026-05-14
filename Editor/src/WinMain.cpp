#include <Nova.hpp>
#include <Editor.hpp>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Nova::Init(hInstance);

	Editor game;
	game.Run();

	Nova::Destroy();
	return 0;
}