#include "gui.h"
#include <Windows.h>
#include <string>
#include "skStr.h"
#include <thread>

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);


std::string name = "TMenuPrototype"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "dFoGcigSbN"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "cd9fe9c847898c1d7273c867bb963f66c31b28c6372df194e5485113aa5fba46"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting


KeyAuth::api KeyAuthAppp(name, ownerid, secret, version, url);


int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
//int main()
{
	// create gui
	//KeyAuthAppp.init();

	//if (KeyAuthAppp.checkblack()) {
	//	abort();
	//}

	BOOL login = TRUE;

	gui::CreateHWindow(L"TMenu", "Cheat Menu Class");
	gui::CreateDevice();
	gui::CreateImGui();

	while (gui::isRunning)
	{

		gui::BeginRender();
		gui::Render(&login, KeyAuthAppp);
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));


		if (GetAsyncKeyState(VK_END) & 1) {
			exit(0);
		}

	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}
