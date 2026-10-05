#include <iostream>

#include <mtkm/core/Application.hpp>

int main()
{
	mtkm::core::Application app = mtkm::core::Application();

	app.Init();

	app.Run();

	app.Shutdown();
}