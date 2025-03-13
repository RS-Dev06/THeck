#include "gui.h"
#include <string>
#include <stdlib.h>
#include "MemoryAccess.h"
#include "CheatFunctions.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"


MemEdit memEdit;
void opacityHandling(bool* enableWindow, HWND window, int* sliderOpacity);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message) {
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED) {
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU)
			return 0;
	} break;
	case WM_DESTROY: {
		PostQuitMessage(0);
	} return 0;
	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter);
	}return 0;
	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON) {
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 && gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE /*| SWP_NOZORDER*/ | SWP_NOMOVE
				);
		}
	}
	}
				return 0;
	}

	return DefWindowProcW(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow(LPCWSTR windowName, const char* className) noexcept {
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = (WNDPROC)WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = nullptr;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = L"class001";
	windowClass.hIconSm = 0;

	RegisterClassEx(&windowClass);

	window = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_LAYERED,
		L"class001",
		windowName,
		WS_POPUP,
		775,
		5,
		WIDTH,
		HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);
	SetLayeredWindowAttributes(window, RGB(0, 95, 95), 180, LWA_ALPHA);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}
void gui::DestroyHWindow() noexcept {
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept {
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept {
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}
void gui::DestroyDevice() noexcept {
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ::ImGui::GetIO();

	io.IniFilename = NULL;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


	ImGui::StyleColorsClassic();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
}

void gui::DestroyImGui() noexcept {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			isRunning = !isRunning;
			return;
		}
	}

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

}

void gui::EndRender() noexcept
{
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);


	/*device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(95, 95, 95, 255), 1.0f, 0);*/
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);


	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		gui::ResetDevice();
}

std::string mana = "nullptr";
std::string HP = "nullptr";
std::string placeSpeed = "nullptr";
std::string defence = "nullptr";
std::string lifeRegen = "nullptr";
std::string xCoords = "nullptr";
std::string yCoords = "nullptr";

void gui::Render(BOOL *login, KeyAuth::api Keyauthapp) noexcept
{


	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	
	ImGuiWindowFlags window_flags = 0;

	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoTitleBar;



	ImGui::Begin(
		"TMenu Prototype",
		&isRunning, window_flags
	);


	if (*login == TRUE) {

		memEdit.getMana(&mana);
		memEdit.getHp(&HP);
		memEdit.getDefense(&defence);
		memEdit.getLifeRegen(&lifeRegen);
		memEdit.getXCoords(&xCoords);
		memEdit.getYCoords(&yCoords);


		ImGui::TextColored({ 0,36,77,255 }, mana.c_str());
		ImGui::TextColored({ 255,0,0,255 }, HP.c_str());
		ImGui::TextColored({ 255, 255, 0, 255 }, defence.c_str());
		ImGui::TextColored({ 255, 0, 225, 255 }, lifeRegen.c_str());
		ImGui::Text("Coordinates"); ImGui::Indent();
		ImGui::Text(xCoords.c_str());
		ImGui::Text(yCoords.c_str());
		ImGui::Unindent();

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		// Ghost Mode Bools
		static bool isGhost = false;
		static bool isCalled = true;

		// Mana Bools
		static bool isFrozenMana = false;
		static bool isCalledFour = true;
		static bool freezeMana = false;
		static bool isFrozenManaWithIncrease = false;
		static bool isCalledFive = true;
		static bool freezeManaWithIncrease = false;

		// Health Bools
		static bool isFrozen = false;
		static bool isCalledTwo = true;
		static bool Freeze = false;
		static bool isFrozenWithIncrease = false;
		static bool isCalledThree = true;
		static bool FreezeWithIncrease = false;

		// Current Stat Bools
		static int currentHp = 0;
		static int currentMana = 0;

		//Freeze mana at the current value
		if (ImGui::Checkbox("Freeze Mana", &isFrozenMana)) {
			isCalledFour = true;
		}


		if (isCalledFour == true && isFrozenMana == true) {
			isCalledFour = false;
			memEdit.getHpInt(&currentMana);
			freezeMana = true;
		}
		else if (isCalledFour == true && isFrozenMana == false) {
			isCalledFour = false;
			freezeMana = false;
		}

		if (freezeMana) {
			if (mana != std::to_string(currentMana)) {
				memEdit.setMana(currentMana);
			}
		}

		//Only allow mana to increase

			ImGui::SameLine();
			if (ImGui::Checkbox("Freeze Mana With Increase", &isFrozenManaWithIncrease)) {
				isCalledFive = true;
			}

		if (isCalledFive == true && isFrozenManaWithIncrease == true) {
			isCalledFive = false;
			memEdit.getHpInt(&currentHp);
			std::cout << isFrozenManaWithIncrease << "\n";
			freezeManaWithIncrease = true;
		}
		else if (isCalledFive == false && isFrozenManaWithIncrease == false) {
			isCalledFive = false;
			freezeManaWithIncrease = false;
		}

		if (freezeManaWithIncrease) {
			if (HP < std::to_string(currentMana)) {
				memEdit.setHp(currentMana);
				memEdit.getHpInt(&currentMana);
			}
		}

		// Freeze health at the current value
		if (ImGui::Checkbox("Freeze Health", &isFrozen)) {
			isCalledTwo = true;
		}

		if (isCalledTwo == true && isFrozen == true) {
			isCalledTwo = false;
			memEdit.getHpInt(&currentHp);
			Freeze = true;
		}
		else if (isCalledTwo == false && isFrozen == false) {
			isCalledTwo = false;
			Freeze = false;
		}

		if (Freeze) {
			if (HP != std::to_string(currentHp)) {
				memEdit.setHp(currentHp);
			}
		}

		//Only allow health to increase

		ImGui::SameLine();
		if (ImGui::Checkbox("Freeze Health With Increase", &isFrozenWithIncrease)) {
			isCalledThree = true;
		}

		if (isCalledThree == true && isFrozenWithIncrease == true) {
			isCalledThree = false;
			memEdit.getHpInt(&currentHp);
			std::cout << isFrozenWithIncrease << "\n";
			FreezeWithIncrease = true;
		}
		else if (isCalledThree == false && isFrozenWithIncrease == false) {
			isCalledThree = false;
			FreezeWithIncrease = false;
		}

		if (FreezeWithIncrease) {
			if (HP < std::to_string(currentHp)) {
				memEdit.setHp(currentHp);
				memEdit.getHpInt(&currentHp);
			}
		}



		// Turn the player into a ghost
		if (ImGui::Checkbox("Ghost Mode", &isGhost)) {
			isCalled = true;
		}

		if (isCalled == true && isGhost == true) {
			isCalled = false;
			memEdit.setGhost(1);
		}
		else if (isCalled == true && isGhost == false) {
			isCalled = false;
			memEdit.setGhost(0);
		}

		ImGui::NewLine();

		// Slot eleven amoutn setter

		static int slAmnt = 1;
		ImGui::SliderInt("SL Amount", &slAmnt, 1, 100);

		if (ImGui::Button("Set Amount")) {

			memEdit.setSlotElevenAmount(slAmnt);
		}

		ImGui::NewLine();

		static int mouseItemAmnt = 1;
		ImGui::SliderInt("Mouse Item Amount", &mouseItemAmnt, 1, 100);

		if (ImGui::Button("Set Mouse Amount")) {
			//memedit set the mouse item after pointer is found]
		}

		ImGui::NewLine();
		
		static float posX = 0;
		static float posY = 0;

		if (ImGui::Button("Set Teleport Point")) {
			memEdit.setTpPoint(&posX, &posY);
		}

		ImGui::SameLine();

		if (ImGui::Button("Teleport To Point")) {
			memEdit.tpToPoint(posX, posY);
		}

		ImGui::NewLine();
		ImGui::NewLine();

		static int opacity = 180;
		if (ImGui::SliderInt("Opacity", &opacity, 50, 255, nullptr, ImGuiSliderFlags_AlwaysClamp)) {
			SetLayeredWindowAttributes(window, RGB(0, 95, 95), opacity, LWA_ALPHA);
		}


		static bool enableWindow = false;
		static bool prevUpKeyState = true;

		if ((GetAsyncKeyState(VK_INSERT) && 0x8000) && prevUpKeyState == true) {
			prevUpKeyState = false;
			opacityHandling(&enableWindow, window, &opacity);
		}
		else if (GetAsyncKeyState(VK_INSERT) == 0) { prevUpKeyState = true; }
	}
	else {
		static char username[256];
		static char password[256];
		ImGui::Text("Username");
		ImGui::InputText("##label", username, sizeof(username));
		ImGui::Text("Password");
		ImGui::InputText("I know it :)", password, sizeof(password));

		if (ImGui::Button("Login")) {
			Keyauthapp.login(username, password);
			if (!Keyauthapp.data.success)
			{
				Keyauthapp.data.expiry;
				LPCWSTR text = L"Incorrect Login Information.\nPlease Try Again";
				LPCWSTR caption = L"Error";
				MessageBox(window, text, caption, MB_OK);
			}
			else {
				*login = TRUE;
			}
		}
	}


	ImGui::End();
}

void opacityHandling(bool* enableWindow, HWND window, int* sliderOpacity) {
	//EnableWindow(window, !*enableWindow);
	int opacity;

	if (*enableWindow == true) {
		opacity = 180;
		*sliderOpacity = 180;
		*enableWindow = false;
	}
	else { opacity = 0; *sliderOpacity = 0; *enableWindow = true; }

	SetLayeredWindowAttributes(window, RGB(0, 95, 95), opacity, LWA_ALPHA);
}