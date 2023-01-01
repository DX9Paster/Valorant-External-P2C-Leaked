#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <filesystem>
#include "../Includes/strings.hpp"
#include "overlay/render.hpp"
#include "overlay/menu.hpp"
#include "Game/skStr.h"
#include "game/cheat.hpp"

#include <TlHelp32.h>
#include <string>

#include "driver/driver.h"
#include "Auth/auth.hpp"

std::wstring s2ws(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

int retreiveValProcessId()
{
	//BYTE target_name[] = { 'n','o','t','e','p','a','d','.','e','x','e', 0 };
	BYTE target_name[] = { 'V','A','L','O','R','A','N','T','-','W','i','n','6','4','-','S','h','i','p','p','i','n','g','.','e','x','e', 0 };
	std::wstring process_name = s2ws(std::string((char*)target_name));
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(entry);

	if (!Process32First(snapshot, &entry)) {
		return 0;
	}

	while (Process32Next(snapshot, &entry)) {
		if (std::wstring(entry.szExeFile) == process_name) {
			return entry.th32ProcessID;
		}
	}

	return 0;
}

#include "../Includes/Mapper/Kdmapper/kdmapper.hpp"
#include "Game/skStr.h"
HANDLE iqvw64e_device_handle;

LONG WINAPI SimplestCrashHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
	std::cout << "[+] Driver Error at 0x" << ExceptionInfo->ExceptionRecord->ExceptionAddress << " by 0x" << std::hex << ExceptionInfo->ExceptionRecord->ExceptionCode << std::endl;

	if (iqvw64e_device_handle)
		intel_driver::Unload(iqvw64e_device_handle);

	return EXCEPTION_EXECUTE_HANDLER;
}

int load_driver()
{
	SetUnhandledExceptionFilter(SimplestCrashHandler);
	if (intel_driver::IsRunning())
	{
		std::cout << "[+] Restart PC!" << std::endl;
		Sleep(500);
	}
	iqvw64e_device_handle = intel_driver::Load();

	NTSTATUS exitCode = 0;
	if (!kdmapper::MapDriver(iqvw64e_device_handle, 0, 0, false, true, 0, 0, 0, &exitCode)) {
		{
			std::cout << "[+] Failed to map the driver!" << std::endl;
			intel_driver::Unload(iqvw64e_device_handle);
			Sleep(500);
			exit(0);
		}
	}
	intel_driver::Unload(iqvw64e_device_handle);

	Sleep(500);
}

auto main() -> NTSTATUS
{
	SetConsoleTitleA("Valorant");
	std::cout << "\nSponsered by Beef.exe\n";
	std::cout << "Only for testing.";
	Sleep(3000);
	system("cls");

	if (GlobalFindAtomA(XorStr("DriverAlreadyLoadedxOKOK").c_str()) == 0)
	{
		load_driver();
		system(XorStr("cls").c_str());
		GlobalAddAtomA(XorStr("DriverAlreadyLoadedxOKOK").c_str());
	}

	if (!InitHandles()) {
		printf(skCrypt("[mapper] failed to initialize communication!\n"));
		return -1;
	}
	system("cls");
	std::cout << "Waiting for valorant bloke.";

	HWND Entryhwnd = NULL;

	while (Entryhwnd == NULL)
	{

		process_id = retreiveValProcessId();;
		Entryhwnd = get_process_wnd(process_id);
		Sleep(500);
	}

	system(XorStr("cls").c_str());

	setup_window();
	init_wndparams(MyWnd);

	image_base = GetBaseAddress();
	printf("Valorant Base Address: 0x%llx\n", image_base);

	if (!image_base) {
		printf(skCrypt("[mapper] failed to get base address of process id -> %d\n"), process_id);
	}

	SetGuardedRegion();
	std::thread(CacheGame).detach();
	while (true) main_loop();

	exit(0);
}

auto render() -> void
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//if (GetAsyncKeyState(VK_F1) & 1) { settings::show_menu = !settings::show_menu; }
	//if (GetAsyncKeyState(VK_INSERT) & 1) { settings::show_radar = !settings::show_radar; }
	CheatLoop();
	drawmenu(); // huge cpu


	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}

	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
	//Sleep(1);
}


auto main_loop() -> WPARAM
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom) {

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		render();
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	cleanup_d3d();
	DestroyWindow(MyWnd);

	return Message.wParam;
}
