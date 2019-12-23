#pragma once

#include "Event.h"


namespace Cobalt {


	class COBALT_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float xPos, float yPos) : m_mouseX(xPos), m_mouseY(yPos) {}
		

	
		inline float GetX() { return m_mouseX; }
		inline float GetY() { return m_mouseY;}


		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent::(x: " << m_mouseX << ", y: " << m_mouseY << ")";
			return ss.str();
		}
		//Both input and mouse
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseMoved)

	private:
		float m_mouseX, m_mouseY;
	};



	class COBALT_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOff, float yOff) : m_xOffset(xOff), m_yOffset(yOff) {}

		inline float GetXOffset() { return m_xOffset; }
		inline float GetYOffset() { return m_yOffset; }


		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent::(xOff: " << m_xOffset << ", yOff: " << m_xOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
		EVENT_CLASS_TYPE(MouseScrolled)


	private:
		float m_xOffset, m_yOffset;
	};

	class COBALT_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() { return m_button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:

		MouseButtonEvent(int button) : m_button(button) {}
		int m_button;
	};


	class COBALT_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:

		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent::" << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class COBALT_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:

		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent::" << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}

