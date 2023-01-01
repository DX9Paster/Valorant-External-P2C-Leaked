#pragma once
#include <Windows.h>
#include <D:\pasting\beef.exe sourcew\Includes\Direct3d\d3dx9.h>
#include <d3d9.h>
#include <D:\pasting\beef.exe sourcew\Includes\Direct3d\d3dx9tex.h>

#include <dwmapi.h>

#include "../../Includes/Imgui/imgui_internal.h"
#include "../../Includes/Imgui/imgui.h"
#include "../../Includes/Imgui/imgui_impl_win32.h"
#include "../../Includes/Imgui/imgui_impl_dx9.h"
#include "../game/globals.hpp"
#include "../Game/structs.hpp"

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "Dwmapi.lib")

IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };

HWND MyWnd = NULL;
HWND GameWnd = NULL;
MSG Message = { NULL };

RECT GameRect = { NULL };
D3DPRESENT_PARAMETERS d3dpp;

DWORD ScreenCenterX;
DWORD ScreenCenterY;

static ULONG Width = GetSystemMetrics(SM_CXSCREEN);
static ULONG Height = GetSystemMetrics(SM_CYSCREEN);

WPARAM main_loop();
void render();

void DefaultTheme() {

	ImGuiStyle& s = ImGui::GetStyle();

	const ImColor accentCol = ImColor(255, 0, 0, 255);
	const ImColor bgSecondary = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_WindowBg] = ImColor(32, 32, 32, 255);
	s.Colors[ImGuiCol_ChildBg] = bgSecondary;
	s.Colors[ImGuiCol_FrameBg] = ImColor(65, 64, 64, 255);
	s.Colors[ImGuiCol_FrameBgActive] = ImColor(35, 37, 39, 255);
	s.Colors[ImGuiCol_Border] = ImColor(1, 1, 1, 255);
	s.Colors[ImGuiCol_CheckMark] = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_ResizeGrip] = ImColor(24, 24, 24, 255);
	s.Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_HeaderHovered] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_TitleBg] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_TitleBgActive] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_FrameBgHovered] = ImColor(65, 64, 64, 255);
	s.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	s.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	s.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	s.Colors[ImGuiCol_Header] = ImColor(42, 42, 42, 255);
	s.Colors[ImGuiCol_HeaderHovered] = ImColor(50, 50, 50, 255);
	s.Colors[ImGuiCol_HeaderActive] = ImColor(50, 50, 50, 255);
	s.Colors[ImGuiCol_PopupBg] = ImColor(15, 15, 15, 255);
	s.Colors[ImGuiCol_Button] = ImColor(30, 30, 30, 255);
	s.Colors[ImGuiCol_ButtonHovered] = ImColor(30, 30, 30, 255);
	s.Colors[ImGuiCol_ButtonActive] = ImColor(30, 30, 30, 255);
	s.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);

	s.AntiAliasedFill = true;
	s.AntiAliasedLines = true;

	s.ChildRounding = 0.0f;
	s.FrameBorderSize = 1.0f;
	s.FrameRounding = 0.0f;
	s.PopupRounding = 0.0f;
	s.ScrollbarRounding = 0.0f;
	s.ScrollbarSize = 0.0f;
	s.TabRounding = 0.0f;
	s.WindowRounding = 0.0f;

}

auto init_wndparams(HWND hWnd) -> HRESULT
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	p_Params.FullScreen_RefreshRateInHz = 0;


	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device))) {
		p_Object->Release();
		exit(4);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGui::GetIO().Fonts->AddFontDefault();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = NULL;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 12);
	ImGuiStyle* style = &ImGui::GetStyle();

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.0f, 0.4000000059604645f, 0.407843142747879f, 1.0f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.8299999833106995f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.1568627506494522f, 0.239215686917305f, 0.2196078449487686f, 0.6000000238418579f);
	colors[ImGuiCol_Border] = ImVec4(0.0f, 1.0f, 1.0f, 0.6499999761581421f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.4392156898975372f, 0.800000011920929f, 0.800000011920929f, 0.1800000071525574f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4392156898975372f, 0.800000011920929f, 0.800000011920929f, 0.2700000107288361f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.4392156898975372f, 0.8078431487083435f, 0.8588235378265381f, 0.6600000262260437f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.1372549086809158f, 0.1764705926179886f, 0.2078431397676468f, 0.7300000190734863f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.2700000107288361f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5400000214576721f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.2000000029802322f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.2196078449487686f, 0.2862745225429535f, 0.2980392277240753f, 0.7099999785423279f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.0f, 1.0f, 1.0f, 0.4399999976158142f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.0f, 1.0f, 1.0f, 0.7400000095367432f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 1.0f, 0.6800000071525574f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.0f, 1.0f, 1.0f, 0.3600000143051147f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.7599999904632568f);
	colors[ImGuiCol_Button] = ImVec4(0.0f, 0.6470588445663452f, 0.6470588445663452f, 0.4600000083446503f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.007843137718737125f, 1.0f, 1.0f, 0.4300000071525574f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.6200000047683716f);
	colors[ImGuiCol_Header] = ImVec4(0.0f, 1.0f, 1.0f, 0.3300000131130219f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 1.0f, 1.0f, 0.4199999868869781f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.5400000214576721f);
	colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.4980392158031464f, 0.4980392158031464f, 0.3300000131130219f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.0f, 0.4980392158031464f, 0.4980392158031464f, 0.4699999988079071f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.0f, 0.6980392336845398f, 0.6980392336845398f, 1.0f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 1.0f, 1.0f, 0.5400000214576721f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 1.0f, 1.0f, 0.7400000095367432f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f, 0.5764706134796143f, 0.8619999885559082f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.800000011920929f);
	colors[ImGuiCol_TabActive] = ImVec4(0.196078434586525f, 0.407843142747879f, 0.6784313917160034f, 1.0f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9724000096321106f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 1.0f, 1.0f, 0.2199999988079071f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.03921568766236305f, 0.09803921729326248f, 0.08627451211214066f, 0.5099999904632568f);
	ImGuiStyle& s = ImGui::GetStyle();
	s.ChildRounding = 0.0f;
	s.FrameBorderSize = 1.0f;
	s.FrameRounding = 0.0f;
	s.PopupRounding = 0.0f;
	s.ScrollbarRounding = 0.0f;
	s.ScrollbarSize = 0.0f;
	s.TabRounding = 0.0f;
	s.WindowRounding = 5.0f;
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(p_Device);
	return S_OK;
}

auto get_process_wnd(uint32_t pid) -> HWND
{
	std::pair<HWND, uint32_t> params = { 0, pid };
	BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
		auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
		uint32_t processId = 0;

		if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
			SetLastError((uint32_t)-1);
			pParams->first = hwnd;
			return FALSE;
		}

		return TRUE;

		}, (LPARAM)&params);

	if (!bResult && GetLastError() == -1 && params.first)
		return params.first;

	return NULL;
}

auto cleanup_d3d() -> void
{
	if (p_Device != NULL) {
		p_Device->EndScene();
		p_Device->Release();
	}
	if (p_Object != NULL) {
		p_Object->Release();
	}
}

auto set_window_target() -> void
{
	while (true) {
		GameWnd = get_process_wnd(process_id);
		if (GameWnd) {
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(GameWnd, &GameRect);
			DWORD dwStyle = GetWindowLong(GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(MyWnd, GameRect.left, GameRect.top, Width, Height, true);
		}
	}
}

auto setup_window() -> void
{
	Sleep(100);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)set_window_target, 0, 0, 0);

	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA),
		0,
		DefWindowProcA,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		("AVeryExternalOverlayx"),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	RECT Rect;
	GetWindowRect(GetDesktopWindow(), &Rect);

	RegisterClassExA(&wcex);

	MyWnd = CreateWindowExA(NULL, ("AVeryExternalOverlayx"), ("AVeryExternalOverlayx"), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, NULL, NULL, wcex.hInstance, NULL);
	SetWindowLong(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	SetLayeredWindowAttributes(MyWnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(MyWnd, &margin);

	ShowWindow(MyWnd, SW_SHOW);
	UpdateWindow(MyWnd);
}

using namespace ColorStructs;



void DrawFilledRect2(int x, int y, int w, int h, ImColor color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

void DrawCornerBox(float x, float y, float w, float h, const ImColor& color)
{
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + w / 4.f, y), color);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + h / 4.f), color);

	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w - w / 4.f, y), color);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + h / 4.f), color);

	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + w / 4.f, y + h), color);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x, y + h - h / 4.f), color);

	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y + h), ImVec2(x + w, y + h - h / 4.f), color);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y + h), ImVec2(x + w - w / 4.f, y + h), color);
}

void DrawNormalBox(int x, int y, int w, int h, int borderPx, ImColor color)
{
	DrawFilledRect2(x + borderPx, y, w, borderPx, color);
	DrawFilledRect2(x + w - w + borderPx, y, w, borderPx, color);
	DrawFilledRect2(x, y, borderPx, h, color);
	DrawFilledRect2(x, y + h - h + borderPx * 2, borderPx, h, color);
	DrawFilledRect2(x + borderPx, y + h + borderPx, w, borderPx, color);
	DrawFilledRect2(x + w - w + borderPx, y + h + borderPx, w, borderPx, color);
	DrawFilledRect2(x + w + borderPx, y, borderPx, h, color);
	DrawFilledRect2(x + w + borderPx, y + h - h + borderPx * 2, borderPx, h, color);
}

using namespace UE4Structs;

auto Draw2DBox(FVector RootPosition, float Width, float Height, ImColor Color) -> void
{
	DrawNormalBox(RootPosition.x - Width / 2, RootPosition.y - Height / 2, Width, Height, Settings::Visuals::BoxWidth, Color);
}

void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
}
inline auto DrawBorder(float x, float y, float w, float h, float px, RGBA* BorderColor) -> void
{
	DrawRect(x, (y + h - px), w, px, BorderColor, 1 / 2);
	DrawRect(x, y, px, h, BorderColor, 1 / 2);
	DrawRect(x, y, w, px, BorderColor, 1 / 2);
	DrawRect((x + w - px), y, px, h, BorderColor, 1 / 2);
}
inline auto DrawCircleFilled2(int x, int y, int radius, RGBA* color) -> void
{
	ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}
inline auto DrawCircleFilled3(int x, int y, int radius, ImColor color) -> void
{
	ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImColor(colors::Head[0], colors::Head[1], colors::Head[2], colors::Head[3]));
}
inline auto DrawLineNew12(int x1, int y1, int x2, int y2, RGBA* color, int thickness) -> void
{
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}
auto DrawOutlinedBox(FVector RootPosition, float Width, float Height, ImColor Color) -> void
{
	DrawCornerBox(RootPosition.x - Width / 2, RootPosition.y - Height / 2, Width, Height, Color);
	DrawCornerBox(RootPosition.x - Width / 2 - 1, RootPosition.y - Height / 2 - 1, Width, Height, ImColor(0, 0, 0));
	DrawCornerBox(RootPosition.x - Width / 2 + 1, RootPosition.y - Height / 2 + 1, Width, Height, ImColor(0, 0, 0));
}

auto DrawDistance(FVector Location, float Distance) -> void
{
	char dist[64];
	sprintf_s(dist, "%.fm", Distance);

	ImVec2 TextSize = ImGui::CalcTextSize(dist);
	ImGui::GetForegroundDrawList()->AddText(ImVec2(Location.x - TextSize.x / 2, Location.y - TextSize.y / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), dist);
}

auto DrawActorDebug(FVector Location) -> void
{

	std::string Out = "[RENDERED " + std::to_string(ValList.size()) + " TIMES]";
	ImVec2 TextSize = ImGui::CalcTextSize(Out.c_str());
	if (NewFeatures::ActorCountDebug == 1 && Settings::Visuals::bDistance == 0)
	{
		ImGui::GetForegroundDrawList()->AddText(ImVec2(Location.x - TextSize.x / 2, Location.y  - TextSize.y / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), Out.c_str());
	}
	else
	{
		ImGui::GetForegroundDrawList()->AddText(ImVec2(Location.x - TextSize.x / 2, Location.y + 15 - TextSize.y / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), Out.c_str());

	}
}
auto DrawFPS(ImVec2 Location) -> void
{
	ImGuiIO io = ImGui::GetIO();
	std::string FPS = "FPS (" + std::to_string(io.Framerate) + ") Diego SOFTWARE";
	ImVec2 TextSize = ImGui::CalcTextSize(FPS.c_str());
	ImGui::GetForegroundDrawList()->AddText(ImVec2(Location.x, Location.y), ImGui::GetColorU32({ 132, 0, 181, 255 }), FPS.c_str());

}
auto DrawAimbotFov(int x, int y, int radius, RGBA* color, float segments)
{
	ImGui::GetForegroundDrawList()->AddCircle(ImVec2(x, y), Settings::aimbot::fov,ImGui::GetColorU32({ 255, 255, 255, 255 }), 0, 1);
}
auto DrawALine(const ImVec2& x, const ImVec2 y, ImU32 color, const FLOAT width)
{
	ImGui::GetForegroundDrawList()->AddLine(x, y, color, width);
}
auto DrawALine2(const ImVec2& x, const ImVec2 y, ImU32 color, const FLOAT width)
{
	ImGui::GetForegroundDrawList()->AddLine(x, y, color, width);
}
auto DrawTracers(FVector Target, ImColor Color) -> void
{
	ImGui::GetForegroundDrawList()->AddLine(
		ImVec2(ScreenCenterX, Height),
		ImVec2(Target.x, Target.y),
		Color,
		0.1f
	);
}
struct vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};
void DrawCircleFilled23(float x, float y, float r, unsigned int p, DWORD color)
{


	vertex* pVertex = new vertex[p + 1];

	for (unsigned int i = 0; i <= p; ++i)
	{
		pVertex[i].x = x + r * cos(D3DX_PI * (i / (p / 2.f)));
		pVertex[i].y = y + r * sin(D3DX_PI * (i / (p / 2.f)));
		pVertex[i].z = 0;
		pVertex[i].rhw = 0;
		pVertex[i].color = color;

	}

//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, p - 1, pVertex, sizeof(vertex));

	delete[] pVertex;
}
auto DrawHealthBar(FVector RootPosition, float Width, float Height, float Health, float RelativeDistance)-> void
{
	auto HPBoxWidth = 1 / RelativeDistance;

	auto HPBox_X = RootPosition.x - Width / 2 - 5 - HPBoxWidth;
	auto HPBox_Y = RootPosition.y - Height / 2 + (Height - Height * (Health / 100));

	int HPBoxHeight = Height * (Health / 100);

	DrawFilledRect2(HPBox_X, HPBox_Y, HPBoxWidth, HPBoxHeight, ImColor(colors::HP[0], colors::HP[1], colors::HP[2], colors::HP[3]));
	DrawRect(HPBox_X - 1, HPBox_Y - 1, HPBoxWidth + 2, HPBoxHeight + 2, &ColorStructs::Col.black, 0.5);
}