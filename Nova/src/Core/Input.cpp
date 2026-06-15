#include <Core/Input.hpp>

using namespace Nova;

HWND Input::hWnd;
unsigned char Input::keyboard[256] = {};
unsigned char Input::mouse[3] = {};
POINT Input::m_CursorPosition = {};
POINT Input::m_CursorDelta = {};
bool Input::mouseLocked = false;

bool Input::GetKey(Keyboard key)
{
	return keyboard[static_cast<unsigned char>(key)] & 0b111100;
}

bool Input::GetKeyDown(Keyboard key)
{
	return keyboard[static_cast<unsigned char>(key)] == 0b111100;
}

bool Input::GetKeyUp(Keyboard key)
{
	return keyboard[static_cast<unsigned char>(key)] == 0b000011;
}

bool Input::GetButton(Mouse button)
{
	return mouse[static_cast<unsigned char>(button)] & 0b111100;
}

bool Input::GetButtonDown(Mouse button)
{
	return mouse[static_cast<unsigned char>(button)] == 0b111100;
}

bool Input::GetButtonUp(Mouse button)
{
	return mouse[static_cast<unsigned char>(button)] == 0b000011;
}

float Input::GetAxis(Keyboard positive, Keyboard negative)
{
	return GetKey(positive) ? 1.0f : GetKey(negative) ? -1.0f : 0.0f;
}

long Input::GetCursorPositionX()
{
	return m_CursorPosition.x;
}

long Input::GetCursorPositionY()
{
	return m_CursorPosition.y;
}

float Input::GetAxis(Axis axis)
{
	switch (axis)
	{
	case Axis::Mouse_X:
		return m_CursorDelta.x;
		break;
	case Axis::Mouse_Y:
		return m_CursorDelta.y;
		break;
	}

	return 0.0f;
}

void Input::SetCursorPos(long x, long y)
{
	::SetCursorPos(x, y);
}

void Input::SetCursorPos(HWND hWnd, long x, long y)
{
	POINT pos = { x, y };
	ClientToScreen(hWnd, &pos);
	::SetCursorPos(pos.x, pos.y);
}

void Input::Reset()
{
	for (unsigned char& key : keyboard)
		key &= 0b110000;

	for (unsigned char& button : mouse)
		button &= 0b110000;

	GetCursorPos(&m_CursorPosition);
	ScreenToClient(hWnd, &m_CursorPosition);

	if (mouseLocked)
	{
		RECT rect = {};
		GetClientRect(hWnd, &rect);

		POINT center = { rect.right / 2, rect.bottom / 2 };

		m_CursorDelta.x = m_CursorPosition.x - center.x;
		m_CursorDelta.y = center.y - m_CursorPosition.y;

		ClientToScreen(hWnd, &center);
		SetCursorPos(center.x, center.y);
	}
	else
	{
		m_CursorDelta.x = 0.0f;
		m_CursorDelta.y = 0.0f;
	}
}