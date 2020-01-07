#include <Cobalt.h>

#include "imgui/imgui.h"

class SLayer : public Cobalt::Layer {
public:

	SLayer() : Layer("New Layer") {}

	void OnUpdate() override {
		//COBALT_INFO("Update");
	}

	void OnEvent(Cobalt::Event& e) override {
		//The OnEvent function is where you want to implement the event dispatcher
		if (e.GetEventType() == Cobalt::EventType::KeyPressed) {
			Cobalt::KeyPressedEvent& event = (Cobalt::KeyPressedEvent&)e;
			COBALT_INFO("{0}", (char)event.GetKeyCode());
		}

		//COBALT_TRACE("Event Detected{0}", e);

	}

};

class Sandbox : public Cobalt::Application {
public: 
	Sandbox() {
		PushLayer(new SLayer());
	}
	~Sandbox() {
		
	}

};


Cobalt::Application* Cobalt::CreateApplication(){
	return new Sandbox();
}