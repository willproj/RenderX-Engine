#include "keyboard.h"

namespace engine::input
{
	std::shared_ptr<Keyboard> Keyboard::s_instance;
	
	
	std::shared_ptr<Keyboard> Keyboard::getInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = std::shared_ptr<Keyboard>(new Keyboard());
		}
		return s_instance;
	}


	Keyboard::Keyboard()
		:keys(nullptr), isKeyPressed(false)
	{
		int32_t keyNum = KeyCode::RX_KEY_LAST;
		keys = std::shared_ptr<std::vector<bool>>(new std::vector<bool>(keyNum));
	}

	Keyboard::~Keyboard()
	{

	}

	bool Keyboard::getKey(int32_t keyCode)
	{
		return keyCode < 0 ? false : (*keys)[keyCode];
	}

	bool Keyboard::getIsKeyPressed()
	{
		return isKeyPressed;
	}

	void Keyboard::onEvent(event::KeyPressedEvent& event)
	{
		(*keys)[event.getKeyCode()] = true;
		isKeyPressed = true;
	}

	void Keyboard::onEvent(event::KeyReleasedEvent& event)
	{
		(*keys)[event.getKeyCode()] = false;	
		isKeyPressed = false;
	}



}