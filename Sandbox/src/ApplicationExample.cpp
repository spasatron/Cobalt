#include <Cobalt.h>



class SLayer : public Cobalt::Layer {
public:

	SLayer() : Layer("My Example Layer") {}

	void OnUpdate() override {
		//COBALT_INFO("Update");
	}

	void OnEvent(Cobalt::Event& e) override {

		COBALT_TRACE("Event Detected{0}", e);

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