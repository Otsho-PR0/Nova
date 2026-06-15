#include <Nova.hpp>

#include <Core/Window.hpp>

using namespace Nova;

WNDCLASS Nova::wc = {};

LRESULT CALLBACK Nova::Setup(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_NCCREATE)
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* window = reinterpret_cast<Window*>(cs->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Window::WindowProc));

		return window->HandleMessages(hWnd, Msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void Nova::Init(HINSTANCE hInstance, LPCSTR menu, HICON hIcon)
{
	wc.hInstance = hInstance;
	wc.lpszClassName = "Window Class";
	wc.lpfnWndProc = Nova::Setup;
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = menu;
	wc.hIcon = hIcon;
	RegisterClass(&wc);
}

void Nova::Destroy()
{
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}