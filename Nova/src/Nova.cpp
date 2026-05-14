#include <Nova.hpp>

#include <Window.hpp>

WNDCLASS Nova::wc = {};

LRESULT CALLBACK DefWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_NCCREATE)
	{
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		Window* window = (Window*)cs->lpCreateParams;

		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)Window::WindowProc);

		return window->HandleMessages(hWnd, Msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void Nova::Init(HINSTANCE hInstance)
{
	wc.hInstance = hInstance;
	wc.lpszClassName = "Window Class";
	wc.lpfnWndProc = DefWinProc;
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&wc);
}

void Nova::Destroy()
{
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}