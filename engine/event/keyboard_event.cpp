#include "keyboard_event.h"

namespace engine::event
{
    KeyboardEvent::KeyboardEvent(int32_t keyCode)
        :keyCode(keyCode)
    {

    }

    KeyboardEvent::~KeyboardEvent()
    {

    }

    int32_t KeyboardEvent::getKeyCode() const
    {
        return keyCode;
    }

    KeyPressedEvent::KeyPressedEvent(int32_t keyCode, int32_t keyRepeatCount)
        :KeyboardEvent(keyCode), keyRepeatCount(keyRepeatCount)
    {

    }

    KeyPressedEvent::~KeyPressedEvent()
    {

    }

    int32_t KeyPressedEvent::getKeyRepeatCount() const
    {
        return keyRepeatCount;
    }

    KeyReleasedEvent::KeyReleasedEvent(int32_t keycode)
        :KeyboardEvent(keycode)
    {

    }

    KeyReleasedEvent::~KeyReleasedEvent()
    {

    }
    
    
}