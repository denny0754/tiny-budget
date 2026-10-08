#include <iostream>

#include <tb/core/Application.hpp>

int main()
{
	tb::core::Application app = tb::core::Application();

	app.Init();

	app.Run();

	app.Shutdown();
}