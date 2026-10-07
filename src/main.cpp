#include <iostream>

#include <tb/app/Application.hpp>

int main()
{
	tb::app::Application app = tb::app::Application();

	app.Init();

	app.Run();

	app.Shutdown();
}