#include <Cobalt.h>
#include <Cobalt/Core/EntryPoint.h>

//Include Sandbox2D play layer
#include "Sandbox2D.h"
#include "FirstGame.h"
#include "ExampleLayer.h"
#include "Fractal/MandelbrotLayer.h"

class MyLayer : public Cobalt::Layer {
	public:
	MyLayer() : Layer("MyLayer"), m_cameraController(1280.0f/720.0f){}

	void OnUpdate(Cobalt::TimeStep ts) override {

		Cobalt::RenderCommand::SetClearColor({ .3f, .2f, .8f, 1.0f });
		Cobalt::RenderCommand::Clear();

		Cobalt::Renderer2D::BeginScene(m_cameraController.GetCamera());
		Cobalt::Renderer2D::RenderText("Hello World", { 0, 0 }, { .8f, .3f, .2f, 1.0f });

		Cobalt::Renderer2D::EndScene();


	}
	void OnAttach() override {
		
	}


private:
	Cobalt::OrthographicCameraController m_cameraController;
};


class Sandbox : public Cobalt::Application {
public: 
	Sandbox() {
		//Use this for an example layer
		//PushLayer(new ExampleLayer());
		//PushLayer(new MandelbrotLayer());
		PushLayer(new MyLayer());
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