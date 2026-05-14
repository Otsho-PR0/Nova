#include <Window.hpp>
#include <Input.hpp>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

Window::Window(const char* title, int width, int height)
{
	RECT rect = {};
	rect.right = width;
	rect.bottom = height;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindow(
		Nova::wc.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
		nullptr,
		nullptr,
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

void Window::PollEvents(RendererContext* context)
{
	this->context = context;

	MSG Msg;
	while (PeekMessage(&Msg, hWnd, 0u, 0u, PM_REMOVE))
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
	Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	return window->HandleMessages(hWnd, Msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMessages(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (context) context->PollEvents(hWnd, Msg, wParam, lParam);
	ImGui_ImplWin32_WndProcHandler(hWnd, Msg, wParam, lParam);

	switch (Msg)
	{
	case WM_CLOSE:
		m_ShouldClose = true;
		return 0;
		break;
	case WM_KEYDOWN:
		if (Input::keyboard[wParam] ^ 0b110000)
			Input::keyboard[wParam] = 0b111100;
		break;
	case WM_KEYUP:
		Input::keyboard[wParam] = 0b000011;
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}