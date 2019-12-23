#pragma once


#include "Event.h"


namespace Cobalt {
	
	class COBALT_API WindowResizeEvent : public Event {
		
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

		inline unsigned int GetWidth() { return m_width; }
		inline unsigned int GetHeight() { return m_height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent::(Width: " << m_width << ", Height: " << m_height << ")";
			return ss.str();
		}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned int m_width, m_height;
	};

	class COBALT_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};

	class COBALT_API AppTickEvent : public Event {
		AppTickEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppTick)
	};
	class COBALT_API AppUpdateEvent : public Event {
		AppUpdateEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppUpdate)
	};
	class COBALT_API AppRenderEvent : public Event {
		AppRenderEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
			EVENT_CLASS_TYPE(AppRender)
	};

}
