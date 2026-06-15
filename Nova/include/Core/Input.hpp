#pragma once

#include <Nova.hpp>

namespace Nova
{
	class NOVA_API Input
	{
	public:
		enum class Keyboard : unsigned char
		{
			Key_Back = VK_BACK,
			Key_Tab = VK_TAB,
			Key_Clear = VK_CLEAR,
			Key_Return = VK_RETURN,
			Key_Shift = VK_SHIFT,
			Key_Control = VK_CONTROL,
			Key_Menu = VK_MENU,
			Key_Pause = VK_PAUSE,
			Key_Capital = VK_CAPITAL,
			Key_Escape = VK_ESCAPE,
			Key_Accept = VK_ACCEPT,
			Key_Space = VK_SPACE,
			Key_Prior = VK_PRIOR,
			Key_Next = VK_NEXT,
			Key_End = VK_END,
			Key_Home = VK_HOME,
			Key_Left = VK_LEFT,
			Key_Up = VK_UP,
			Key_Right = VK_RIGHT,
			Key_Down = VK_DOWN,
			Key_Select = VK_SELECT,
			Key_Print = VK_PRINT,
			Key_Execute = VK_EXECUTE,
			Key_Snapshot = VK_SNAPSHOT,
			Key_Insert = VK_INSERT,
			Key_Delete = VK_DELETE,
			Key_Help = VK_HELP,
			Key_0 = '0',
			Key_1 = '1',
			Key_2 = '2',
			Key_3 = '3',
			Key_4 = '4',
			Key_5 = '5',
			Key_6 = '6',
			Key_7 = '7',
			Key_8 = '8',
			Key_9 = '9',
			Key_A = 'A',
			Key_B = 'B',
			Key_C = 'C',
			Key_D = 'D',
			Key_E = 'E',
			Key_F = 'F',
			Key_G = 'G',
			Key_H = 'H',
			Key_I = 'I',
			Key_J = 'J',
			Key_K = 'K',
			Key_L = 'L',
			Key_M = 'M',
			Key_N = 'N',
			Key_O = 'O',
			Key_P = 'P',
			Key_Q = 'Q',
			Key_R = 'R',
			Key_S = 'S',
			Key_T = 'T',
			Key_U = 'U',
			Key_V = 'V',
			Key_W = 'W',
			Key_X = 'X',
			Key_Y = 'Y',
			Key_Z = 'Z',
			Key_LWin = VK_LWIN,
			Key_RWin = VK_RWIN,
			Key_Apps = VK_APPS,
			Key_Sleep = VK_SLEEP,
			Key_NumPad0 = VK_NUMPAD0,
			Key_NumPad1 = VK_NUMPAD1,
			Key_NumPad2 = VK_NUMPAD2,
			Key_NumPad3 = VK_NUMPAD3,
			Key_NumPad4 = VK_NUMPAD4,
			Key_NumPad5 = VK_NUMPAD5,
			Key_NumPad6 = VK_NUMPAD6,
			Key_NumPad7 = VK_NUMPAD7,
			Key_NumPad8 = VK_NUMPAD8,
			Key_NumPad9 = VK_NUMPAD9,
			Key_Multiply = VK_MULTIPLY,
			Key_Add = VK_ADD,
			Key_Separator = VK_SEPARATOR,
			Key_Subtract = VK_SUBTRACT,
			Key_Decimal = VK_DECIMAL,
			Key_Divide = VK_DIVIDE,
			Key_F1  = VK_F1,
			Key_F2  = VK_F2,
			Key_F3  = VK_F3,
			Key_F4  = VK_F4,
			Key_F5  = VK_F5,
			Key_F6  = VK_F6,
			Key_F7  = VK_F7,
			Key_F8  = VK_F8,
			Key_F9  = VK_F9,
			Key_F10 = VK_F10,
			Key_F11 = VK_F11,
			Key_F12 = VK_F12,
			Key_F13 = VK_F13,
			Key_F14 = VK_F14,
			Key_F15 = VK_F15,
			Key_F16 = VK_F16,
			Key_F17 = VK_F17,
			Key_F18 = VK_F18,
			Key_F19 = VK_F19,
			Key_F20 = VK_F20,
			Key_F21 = VK_F21,
			Key_F22 = VK_F22,
			Key_F23 = VK_F23,
			Key_F24 = VK_F24,
			Key_NavigationView = VK_NAVIGATION_VIEW,
			Key_NavigationMenu = VK_NAVIGATION_MENU,
			Key_NavigationUp = VK_NAVIGATION_UP,
			Key_NavigationDown = VK_NAVIGATION_DOWN,
			Key_NavigationLeft = VK_NAVIGATION_LEFT,
			Key_NavigationRight = VK_NAVIGATION_RIGHT,
			Key_NavigationAccept = VK_NAVIGATION_ACCEPT,
			Key_NavigationCancel = VK_NAVIGATION_CANCEL,
			Key_Numlock = VK_NUMLOCK,
			Key_Scroll = VK_SCROLL,
			Key_LShift = VK_LSHIFT,
			Key_RShift = VK_RSHIFT,
			Key_LControl = VK_LCONTROL,
			Key_RControl = VK_RCONTROL,
			Key_LMenu = VK_LMENU,
			Key_RMenu = VK_RMENU
		};

		enum class Mouse : unsigned char
		{
			Button_Left,
			Button_Middle,
			Button_Right
		};

		enum class Axis : unsigned char
		{
			Mouse_X,
			Mouse_Y
		};

		Input() = delete;
		Input& operator=(const Input&) = delete;

		static bool GetKey(Keyboard key);
		static bool GetKeyDown(Keyboard key);
		static bool GetKeyUp(Keyboard key);

		static bool GetButton(Mouse button);
		static bool GetButtonDown(Mouse button);
		static bool GetButtonUp(Mouse button);

		static long GetCursorPositionX();
		static long GetCursorPositionY();

		static float GetAxis(Keyboard positive, Keyboard negative);
		static float GetAxis(Axis axis);

		static void SetCursorPos(long x, long y);
		static void SetCursorPos(HWND hWnd, long x, long y);

		static bool mouseLocked;

		static void Reset();

	private:
		friend class Window;
		static HWND hWnd;
		static unsigned char keyboard[256];
		static unsigned char mouse[3];
		static POINT m_CursorPosition;
		static POINT m_CursorDelta;
	};
}