#include <Nova.hpp>
#include <Core/Exception.hpp>
#include <Math/Matrix.hpp>
#include <Editor.hpp>

#include <string>

#include <resource.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Nova::Init(hInstance, NULL, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

	std::string log;

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), log.c_str(), log.length(), nullptr, nullptr);

	try
	{
		Editor game;
		game.Run();
	}
	catch (Nova::Exception& e)
	{
		MessageBox(nullptr, e.what(), e.Caption(), MB_ICONERROR);
	}
	catch (Nova::ExceptionW& e)
	{
		MessageBoxW(nullptr, e.Message(), e.Caption(), MB_ICONERROR);
	}
	catch (std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Nova", MB_ICONERROR);
	}

	Nova::Destroy();
	return 0;
}