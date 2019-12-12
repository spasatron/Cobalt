#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern Cobalt::Application* Cobalt::CreateApplication();

int main(int argc, char** argv) {
	printf("Cobalt Engine Entry Point\n");
	auto app = Cobalt::CreateApplication();
	app->Run();
	delete app;
}


#endif // CB_WINDWOS_PLATFORM

