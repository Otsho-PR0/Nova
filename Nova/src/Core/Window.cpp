#include <Core/Window.hpp>
#include <Core/Input.hpp>

#include <Renderer/Renderer.hpp>

using namespace Nova;

Window::Window(const char* title, int width, int height, HMENU hMenu)
{
	RECT rect = {};
	rect.right = width;
	rect.bottom = height;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, hMenu != nullptr);

	hWnd = CreateWindow(
		Nova::wc.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
		nullptr,
		hMenu,
		Nova::wc.hInstance,
		this
	);

	Show();
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

Window::operator HWND&()
{
	return hWnd;
}

void Window::Show() const
{
	ShowWindow(hWnd, SW_SHOW);
}

void Window::Hide() const
{
	ShowWindow(hWnd, SW_HIDE);
}

void Window::Maximize() const
{
	ShowWindow(hWnd, SW_MAXIMIZE);
}

void Window::Normalize() const
{
	ShowWindow(hWnd, SW_NORMAL);
}


void Window::Minimize() const
{
	ShowWindow(hWnd, SW_MINIMIZE);
}

void Window::Close()
{
	m_ShouldClose = true;
}

void Window::SetTitle(const char* title) const
{
	SetWindowText(hWnd, title);
}

void Nova::Window::SetMenu(LPCSTR menu)
{
	HMENU hMenu = LoadMenu(Nova::wc.hInstance, menu);
	::SetMenu(hWnd, hMenu);
}

void Nova::Window::SetMenu(HMENU hMenu)
{
	::SetMenu(hWnd, hMenu);
}

void Window::SetCustomWindowProc(std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> callback)
{
	m_WndProc = callback;
}

long Window::GetWidth() const
{
	RECT rect = {};

	GetClientRect(hWnd, &rect);

	return rect.right - rect.left;
}

long Window::GetHeight() const
{
	RECT rect = {};

	GetClientRect(hWnd, &rect);

	return rect.bottom - rect.top;
}

void Window::PollEvents()
{
	Input::hWnd = hWnd;
	if (CursorVisible)
		while (ShowCursor(TRUE) < 0);
	else
		while (ShowCursor(FALSE) >= 0);

	MSG Msg;
	while (PeekMessage(&Msg, NULL, 0u, 0u, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

bool Window::ShouldClose()
{
	return m_ShouldClose;
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return window->HandleMessages(hWnd, Msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMessages(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (m_Context) reinterpret_cast<RendererContext*>(m_Context)->PollEvents(hWnd, Msg, wParam, lParam);
	if (m_WndProc) m_WndProc(hWnd, Msg, wParam, lParam);

	switch (Msg)
	{
	case WM_CLOSE:
		m_ShouldClose = true;
		return TRUE;
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (Input::keyboard[wParam] ^ 0b110000)
			Input::keyboard[wParam] = 0b111100;
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Input::keyboard[wParam] = 0b000011;
		break;
	case WM_LBUTTONDOWN:
		if (Input::mouse[0] ^ 0b110000)
			Input::mouse[0] = 0b111100;
		break;
	case WM_LBUTTONUP:
		Input::mouse[0] = 0b000011;
		break;
	case WM_MBUTTONDOWN:
		if (Input::mouse[1] ^ 0b110000)
			Input::mouse[1] = 0b111100;
		break;
	case WM_MBUTTONUP:
		Input::mouse[1] = 0b000011;
		break;
	case WM_RBUTTONDOWN:
		if (Input::mouse[2] ^ 0b110000)
			Input::mouse[2] = 0b111100;
		break;
	case WM_RBUTTONUP:
		Input::mouse[2] = 0b000011;
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}