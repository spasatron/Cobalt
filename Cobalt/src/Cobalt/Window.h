#pragma once

#include "cbpc.h"

#include "Cobalt/Core.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/ApplicationEvent.h"
#include "Cobalt/Events/KeyEvent.h"
#include "Cobalt/Events/MouseEvent.h"

//The whole point of this is to make the window platform indep. 
namespace Cobalt {

	struct WindowProp {
		std::string title;
		unsigned int width, height;

		WindowProp(const std::string t = "Cobalt Engine", unsigned int w = 1280, unsigned int h = 720) : title(t), width(w), height(h) {}

	};


	//This entire class is going to be virtual essentially
	class COBALT_API Window {
	public:
		//Anytime we call a Eventcallback function it will be a std::function with event type refrence
		using EventCallBackFunc = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallBackFunc& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		//
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProp& prop = WindowProp());
	};

}

