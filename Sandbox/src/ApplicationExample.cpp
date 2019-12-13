#include <Cobalt.h>

class Sandbox : public Cobalt::Application {
public: 
	Sandbox() {
	
	}
	~Sandbox() {
	
	}

};

//
Cobalt::Application* Cobalt::CreateApplication(){
	Sandbox *sand = new Sandbox();
	sand->Run();
	return sand;
}