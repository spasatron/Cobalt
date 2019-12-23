#pragma once

#include "Event.h"


namespace Cobalt{


	class COBALT_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keyCode) : m_keyCode(keyCode) {}
		int m_keyCode;
	};

	class COBALT_API KeyPressedEvent : public KeyEvent {
	public:
		//Will create a KeyEvent with a assigned keyCode and repeat count
		KeyPressedEvent(int keyCode, int repeat) : KeyEvent(keyCode), m_repeatCount(repeat) {}
		
		//Override the event to string default to display the keycode and repeat count
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent::" << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		inline int GetRepeatCount() const { return m_repeatCount; }

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeatCount;

	};


	class COBALT_API KeyReleasedEvent : public KeyEvent {
	public:

		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override{
			std::stringstream ss;
			ss << "KeyReleasedEvent::" << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}
