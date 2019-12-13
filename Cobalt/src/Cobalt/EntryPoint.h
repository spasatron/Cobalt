#pragma once

#ifdef CB_PLATFORM_WINDOWS


extern Cobalt::Application* Cobalt::CreateApplication();

int main(int argc, char** argv) {

	Cobalt::Log::Init();
	COBALT_CORE_WARN("Client has started up");
	int a = 120;
	COBALT_CORE_ERROR("Critical Message test {0}", a);
	COBALT_INFO("Client trace test");

	auto app = Cobalt::CreateApplication();
	app->Run();

	delete app;
}


#endif // CB_WINDWOS_PLATFORM

