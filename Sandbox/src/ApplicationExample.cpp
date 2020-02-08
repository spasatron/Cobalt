#include <Cobalt.h>
#include <Cobalt/Core/EntryPoint.h>

//Include Sandbox2D play layer
#include "Sandbox2D.h"
#include "FirstGame.h"
#include "ExampleLayer.h"
#include "Fractal/MandelbrotLayer.h"




class Sandbox : public Cobalt::Application {
public: 
	Sandbox() {
		//Use this for an example layer
		//PushLayer(new ExampleLayer());
		PushLayer(new MandelbrotLayer());
	}
	~Sandbox() {
		
	}

};


Cobalt::Application* Cobalt::CreateApplication(){
	return new Sandbox();
}









/*
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
	//How to override th ImGui Layer
	void OnImGuiRender() override {

		ImGui::Begin("Text");
		ImGui::TextColored(ImVec4(1, 0, 0, 1), "Hello");
		ImGui::End();

	}

};
*/