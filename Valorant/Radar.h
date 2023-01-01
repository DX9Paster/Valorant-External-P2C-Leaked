#pragma once
//#include "Game/structs.hpp"
#include "Vector3.h"

inline FVector2D WorldRadar(FVector srcPos, FVector distPos, float yaw, float radarX, float radarY, float size)
{
	auto cosYaw = cos(DegreeToRadian(yaw));
	auto sinYaw = sin(DegreeToRadian(yaw));

	auto deltaX = srcPos.x - distPos.x;
	auto deltaY = srcPos.y - distPos.y;

	auto locationX = (float)(deltaY * cosYaw - deltaX * sinYaw) / 45.f;
	auto locationY = (float)(deltaX * cosYaw + deltaY * sinYaw) / 45.f;

	if (locationX > (size - 2.f))
		locationX = (size - 2.f);
	else if (locationX < -(size - 2.f))
		locationX = -(size - 2.f);

	if (locationY > (size - 6.f))
		locationY = (size - 6.f);
	else if (locationY < -(size - 6.f))
		locationY = -(size - 6.f);

	return FVector2D((int)(-locationX + radarX), (int)(locationY + radarY));
}

static FVector pRadar;
static FVector pRadar1;
static int enemy_size = 3;
inline auto DrawRadar(FVector EntityPos) -> void
{
	auto radar_posX = pRadar.x + 135;
	auto radar_posY = pRadar.y + 135;
	//if (CRiQTest::g_localplayerpawn == 0) return;
	uint64_t LocalRootComp = Read<uint64_t>(LocalPlayer + offsets::RootComponent);
	uint64_t rot = Read<uint64_t>(PlayerController + offsets::CameraRotation);
	FVector LocalPos = Read<FVector>(LocalRootComp + offsets::RelativeLocation);
	auto Radar2D = WorldRadar(LocalPos, EntityPos, rot, radar_posX, radar_posY, 1000.f);

	
	//ImGui::SetWindowSize(ImVec2(Settings::misc::Size, Settings::misc::Size));
	ImGui::SetNextWindowSize(ImVec2(Settings::misc::Size, Settings::misc::Size));
	ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX));


	//ImGui::SetNextWindowPos(ImVec2(0,0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 150.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 150.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 150.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 150.0f);
	//ImGui::Begin("STATIC RADAR", &Settings::bRadar, ImGuiWindowFlags_NoResize  | ImGuiWindowFlags_NoTitleBar);
	ImGui::Begin("STATIC RADAR", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 winpos = ImGui::GetWindowPos();
	ImVec2 winsize = ImGui::GetWindowSize();
	draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y), ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y), ImColor(70, 70, 70, 255), 0.5f);
	draw_list->AddLine(ImVec2(winpos.x, winpos.y + winsize.y * 0.5f), ImVec2(winpos.x + winsize.x, winpos.y + winsize.y * 0.5f), ImColor(70, 70, 70, 255), 0.5f);

	//draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y * 0.5f), ImVec2(winpos.x, winpos.y), ImColor(90, 90, 90, 255), 0.5f);
	//draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y * 0.5f), ImVec2(winpos.x + winsize.x, winpos.y), ImColor(90, 90, 90, 255), 0.5f);


	//draw_list->DrawCircleFilled22(Radar2D.x, Radar2D.y, 4, ImColor(255, 255, 255, 255));
	draw_list->AddCircleFilled(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y * 0.5f), 3, ImColor(0, 255, 0, 255));

	draw_list->AddCircleFilled(ImVec2(winpos.x + Radar2D.x, winpos.y +Radar2D.y ), Settings::misc::radarentitysize, ImColor(colors::radar[0], colors::radar[1], colors::radar[2], colors::radar[3]));
	//DrawCircleFilled(Radar2D.x, Radar2D.y, 4, &Col.red);
	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}