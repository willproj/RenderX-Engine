#pragma once
#include <common.h>
#include "event/keyboard_event.h"

namespace engine::input
{
	enum KeyCode
	{

		/* The unknown key */
		RX_KEY_UNKNOWN = -1,

		/* Printable keys */
		RX_KEY_SPACE = 32,
		RX_KEY_APOSTROPHE = 39,
		RX_KEY_COMMA = 44,
		RX_KEY_MINUS = 45,
		RX_KEY_PERIOD = 46,
		RX_KEY_SLASH = 47,
		RX_KEY_0 = 48,
		RX_KEY_1 = 49,
		RX_KEY_2 = 50,
		RX_KEY_3 = 51,
		RX_KEY_4 = 52,
		RX_KEY_5 = 53,
		RX_KEY_6 = 54,
		RX_KEY_7 = 55,
		RX_KEY_8 = 56,
		RX_KEY_9 = 57,
		RX_KEY_SEMICOLON = 59,
		RX_KEY_EQUAL = 61,
		RX_KEY_A = 65,
		RX_KEY_B = 66,
		RX_KEY_C = 67,
		RX_KEY_D = 68,
		RX_KEY_E = 69,
		RX_KEY_F = 70,
		RX_KEY_G = 71,
		RX_KEY_H = 72,
		RX_KEY_I = 73,
		RX_KEY_J = 74,
		RX_KEY_K = 75,
		RX_KEY_L = 76,
		RX_KEY_M = 77,
		RX_KEY_N = 78,
		RX_KEY_O = 79,
		RX_KEY_P = 80,
		RX_KEY_Q = 81,
		RX_KEY_R = 82,
		RX_KEY_S = 83,
		RX_KEY_T = 84,
		RX_KEY_U = 85,
		RX_KEY_V = 86,
		RX_KEY_W = 87,
		RX_KEY_X = 88,
		RX_KEY_Y = 89,
		RX_KEY_Z = 90,
		RX_KEY_LEFT_BRACKET = 91,
		RX_KEY_BACKSLASH = 92,
		RX_KEY_RIGHT_BRACKET = 93,
		RX_KEY_GRAVE_ACCENT = 96,
		RX_KEY_WORLD_1 = 161,
		RX_KEY_WORLD_2 = 162,

		RX_KEY_ESCAPE = 256,
		RX_KEY_ENTER = 257,
		RX_KEY_TAB = 258,
		RX_KEY_BACKSPACE = 259,
		RX_KEY_INSERT = 260,
		RX_KEY_DELETE = 261,
		RX_KEY_RIGHT = 262,
		RX_KEY_LEFT = 263,
		RX_KEY_DOWN = 264,
		RX_KEY_UP = 265,
		RX_KEY_PAGE_UP = 266,
		RX_KEY_PAGE_DOWN = 267,
		RX_KEY_HOME = 268,
		RX_KEY_END = 269,
		RX_KEY_CAPS_LOCK = 280,
		RX_KEY_SCROLL_LOCK = 281,
		RX_KEY_NUM_LOCK = 282,
		RX_KEY_PRINT_SCREEN = 283,
		RX_KEY_PAUSE = 284,
		RX_KEY_F1 = 290,
		RX_KEY_F2 = 291,
		RX_KEY_F3 = 292,
		RX_KEY_F4 = 293,
		RX_KEY_F5 = 294,
		RX_KEY_F6 = 295,
		RX_KEY_F7 = 296,
		RX_KEY_F8 = 297,
		RX_KEY_F9 = 298,
		RX_KEY_F10 = 299,
		RX_KEY_F11 = 300,
		RX_KEY_F12 = 301,
		RX_KEY_F13 = 302,
		RX_KEY_F14 = 303,
		RX_KEY_F15 = 304,
		RX_KEY_F16 = 305,
		RX_KEY_F17 = 306,
		RX_KEY_F18 = 307,
		RX_KEY_F19 = 308,
		RX_KEY_F20 = 309,
		RX_KEY_F21 = 310,
		RX_KEY_F22 = 311,
		RX_KEY_F23 = 312,
		RX_KEY_F24 = 313,
		RX_KEY_F25 = 314,
		RX_KEY_KP_0 = 320,
		RX_KEY_KP_1 = 321,
		RX_KEY_KP_2 = 322,
		RX_KEY_KP_3 = 323,
		RX_KEY_KP_4 = 324,
		RX_KEY_KP_5 = 325,
		RX_KEY_KP_6 = 326,
		RX_KEY_KP_7 = 327,
		RX_KEY_KP_8 = 328,
		RX_KEY_KP_9 = 329,
		RX_KEY_KP_DECIMAL = 330,
		RX_KEY_KP_DIVIDE = 331,
		RX_KEY_KP_MULTIPLY = 332,
		RX_KEY_KP_SUBTRACT = 333,
		RX_KEY_KP_ADD = 334,
		RX_KEY_KP_ENTER = 335,
		RX_KEY_KP_EQUAL = 336,
		RX_KEY_LEFT_SHIFT = 340,
		RX_KEY_LEFT_CONTROL = 341,
		RX_KEY_LEFT_ALT = 342,
		RX_KEY_LEFT_SUPER = 343,
		RX_KEY_RIGHT_SHIFT = 344,
		RX_KEY_RIGHT_CONTROL = 345,
		RX_KEY_RIGHT_ALT = 346,
		RX_KEY_RIGHT_SUPER = 347,
		RX_KEY_MENU = 348,

		RX_KEY_LAST = RX_KEY_MENU
	};


	class Keyboard
	{
	public:

		static std::shared_ptr<Keyboard> getInstance();
		~Keyboard();

		bool getKey(int32_t keyCode);
		bool getIsKeyPressed();

		void onEvent(event::KeyPressedEvent& event);
		void onEvent(event::KeyReleasedEvent& event);

	private:
		Keyboard();

	private:
		static std::shared_ptr<Keyboard> s_instance;

		std::shared_ptr<std::vector<bool>> keys;
		bool isKeyPressed;

	};
}