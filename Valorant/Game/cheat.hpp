#pragma once
#include "sdk.hpp"
#include <iostream>
#include "../Aimbot.h"
#include "../Skeleton.h"
#include "../Radar.h"
#include "../wav.c"
using namespace Globals;
using namespace Camera;
using namespace UNREALENGINE;
SCONTROLROTATION* AControlRotation;
WORLDFACTOR* UWorld;
SGAMEINSTANCE* UGameInstance;
SLOCALPLAYER* ULocalPlayer;
SPLAYERCONTROLLER* APlayerController;
SPAWN* APawn;
SACTOR* APrivatePawn;
SULEVEL* ULevel;
SUSKELETALMESH* USkeletalMeshComponent;
SUSKELETALMESH* SMesh;



auto CacheGame() -> void
{
	while (true)
	{
		std::vector<ValEntity> CachedList;

		auto WorldPtr = decryptWorld(image_base);

		auto ULevelPtr = UWorld->ULevel(WorldPtr);
		auto UGameInstancePtr = UWorld->GameInstance(WorldPtr);

		auto ULocalPlayerPtr = UGameInstance->ULocalPlayer(UGameInstancePtr);
		std::vector<PlayerContrPTR> PlayerPTR;
		auto APlayerControllerPtr = ULocalPlayer->APlayerController(ULocalPlayerPtr);
		PlayerContrPTR PlayerControllerPTR{ APlayerControllerPtr };
		PlayerPTR.push_back(PlayerControllerPTR);
		PPTR.clear();
		PPTR = PlayerPTR;
		std::vector<CameraM> CacheCamera;
		PlayerCameraManager = APlayerController->APlayerCameraManager(APlayerControllerPtr);
		CameraM ABCD{ PlayerCameraManager };
		CacheCamera.push_back(ABCD);
		CRiQC.clear();
		CRiQC = CacheCamera;
		auto MyHUD = APlayerController->AHUD(APlayerControllerPtr);
		
		auto APawnPtr = APlayerController->APawn(APlayerControllerPtr);

		if (APawnPtr != 0)
		{
			MyUniqueID = APawn->UniqueID(APawnPtr);
			MyTeamID = APawn->TeamID(APawnPtr);
			MyRelativeLocation = APawn->RelativeLocation(APawnPtr);
		}

		if (MyHUD != 0)
		{
			auto PlayerArray = ULevel->AActorArray(ULevelPtr);
			
			for (uint32_t i = 0; i < PlayerArray.Count; ++i)
			{
				//uintptr_t Actor = Read<uintptr_t>(PlayerArray + (i * 0x8));
				auto Pawns = PlayerArray[i];


				//CallAimbot(Pawns);
				if (Pawns != APawnPtr)
				{

					if (Settings::misc::option1)
					{
						switch (Settings::misc::enemyselect)
						{
						case 0: 
							if (MyUniqueID == APawn->UniqueID(Pawns) && MyTeamID != APawn->TeamID(Pawns))
							{
								ValEntity Entities{ Pawns };
								CachedList.push_back(Entities);
							}
							break;
						case 1:
							if (MyUniqueID == APawn->UniqueID(Pawns)) //&& MyTeamID != APawn->TeamID(Pawns))
							{
								ValEntity Entities{ Pawns };
								CachedList.push_back(Entities);
							}
							break;
						case 2:
							break;
						}

					}

				}
				
			}
			
			ValList.clear();
			ValList = CachedList;
			Sleep(1000);
		}
	}
}

auto CheatLoop() -> void
{

	if (Settings::aimbot::drawfov)
	{
		DrawAimbotFov(ScreenCenterX, ScreenCenterY, Settings::aimbot::fov, &Col.blue, 1);
	}
	if (Settings::Visuals::FPS)
	{

		ImVec2 abc = ImVec2(0, 0);
		DrawFPS(abc);

	}
	float closestDistance = FLT_MAX;


	for (ValEntity ValEntityList : ValList)
	{
		DWORD_PTR closestPawn1 = NULL;
		auto SkeletalMesh = APrivatePawn->USkeletalMeshComponent(ValEntityList.Actor);
		auto RelativeLocation = APawn->RelativeLocation(ValEntityList.Actor);
		auto RelativeLocationProjected = UNREALENGINE::SDK::ProjectWorldToScreen(RelativeLocation);
		auto CameraManager = Read<uintptr_t>(PlayerCameraManager + offsets::PlayerCameraManager);

		for (CameraM CameraCacheList : CRiQC)
		{

		
			if (Settings::Visuals::fovchanger)
			{
				Write<float>(CameraCacheList.CameraMCRiQ + offsets::CameraFOVChange, Settings::Visuals::fovchangervalue);

			}
		}

		auto RelativePosition = RelativeLocation - CameraLocation;
		auto RelativeDistance = RelativePosition.Length() / 10000 * 2;

		auto HeadBone = UNREALENGINE::SDK::GetEntityBone(SkeletalMesh, 8);
		auto HeadBoneProjected = UNREALENGINE::SDK::ProjectWorldToScreen(HeadBone);
		auto HeadBoneProjected2 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x, HeadBone.y, HeadBone.z ));
		auto RootBone = UNREALENGINE::SDK::GetEntityBone(SkeletalMesh, 0);
		auto RootBoneProjected = UNREALENGINE::SDK::ProjectWorldToScreen(RootBone);
		auto RootBoneProjected2 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x, RootBone.y, RootBone.z - 15));
		auto Distance = MyRelativeLocation.Distance(RelativeLocation);

		auto ControlRotation = AControlRotation->AControlRotation(ValEntityList.Actor);
		float BoxHeight = abs(HeadBoneProjected.y - RootBoneProjected.y);
		float BoxWidth = BoxHeight * 0.40;



		
		auto dx = HeadBoneProjected2.x - (Width / 2);
		auto dy = HeadBoneProjected2.y - (Height / 2);
		auto dist = sqrtf(dx * dx + dy * dy);

		if (dist < Settings::aimbot::fov && dist < closestDistance)
		{
			if (Settings::aimbot::vischeck)
			{
				closestDistance = dist;
				closestPawn1 = ValEntityList.Actor;
			}
			else
			{
				closestDistance = dist;
				closestPawn1 = ValEntityList.Actor;
			}
		}	
		auto Health = APawn->Health(ValEntityList.Actor);
		auto IsVisible = isVisible(SkeletalMesh);
		if (Settings::misc::radar) {

			if (GetAsyncKeyState(VK_F1) & 1) { Settings::bRadar = !Settings::bRadar; }
			if (Settings::bRadar)
			{
				DrawRadar(RelativePosition);
			}

		}
		if (Health <= 0) continue;
		if (Distance < NewFeatures::renderdistance)
		{
			
			if (APawn->bIsDormant(ValEntityList.Actor))
			{
				std::vector<SSkeletal> SkeletalPTR;
				auto GetBones = SMesh->BoneCount(SkeletalMesh);
				SSkeletal SSkeletalPTR{ GetBones };
				SkeletalPTR.push_back(SSkeletalPTR);
				SPTR.clear();
				SPTR = SkeletalPTR;
				if (IsVisible)
				{
	
					if (Settings::Visuals::bSnaplines)
						DrawTracers(RootBoneProjected, ImColor(colors::snaplines[0], colors::snaplines[1], colors::snaplines[2], colors::snaplines[3]));
					if (Settings::Visuals::bBox)
						Draw2DBox(RelativeLocationProjected, BoxWidth, BoxHeight, ImColor(colors::box[0], colors::box[1], colors::box[2], colors::box[3]));

					if (Settings::Visuals::bBoxOutlined)
						DrawOutlinedBox(RelativeLocationProjected, BoxWidth, BoxHeight, ImColor(colors::boxoutline[0], colors::boxoutline[1], colors::boxoutline[2], colors::boxoutline[3]));
					if (Settings::Visuals::HeadCircle)
					{
						DrawCircleFilled3(HeadBoneProjected.x, HeadBoneProjected.y, (HeadBoneProjected.y) / Settings::misc::headsize, ImColor(colors::Head[0], colors::Head[1], colors::Head[2], colors::Head[3]));
					}
				}
				else
				{

					if (Settings::Visuals::bSnaplines)
						DrawTracers(RootBoneProjected, ImColor(colors::snaplinesinvisible[0], colors::snaplinesinvisible[1], colors::snaplinesinvisible[2], colors::snaplinesinvisible[3]));
					if (Settings::Visuals::bBox)
						Draw2DBox(RelativeLocationProjected, BoxWidth, BoxHeight, ImColor(colors::boxinvisible[0], colors::boxinvisible[1], colors::boxinvisible[2], colors::boxinvisible[3]));

					if (Settings::Visuals::bBoxOutlined)
						DrawOutlinedBox(RelativeLocationProjected, BoxWidth, BoxHeight, ImColor(colors::boxoutlineinvisible[0], colors::boxoutlineinvisible[1], colors::boxoutlineinvisible[2], colors::boxoutlineinvisible[3]));

				}

				if (Settings::Visuals::bHealth)
					DrawHealthBar(RelativeLocationProjected, BoxWidth, BoxHeight, Health, RelativeDistance);

				if (Settings::Visuals::bDistance)
					DrawDistance(RootBoneProjected2, Distance);
				if (NewFeatures::ActorCountDebug)
				{
						DrawActorDebug(RootBoneProjected2);
						NewFeatures::curractors = ValList.size();
				}
				if (Settings::aimbot::aimbot)
				{
					if (ValEntityList.Actor != 0)
					{
						if (closestPawn1 && GetAsyncKeyState(hotkeys::aimkey) < 0)
						{
							if (IsVisible) 
							{
								AIMBOT(closestPawn1);
							}
						}
					}
			
				
				}
				if (Settings::Visuals::TDBox)
				{
					if (IsVisible)
					{

						if (HeadBoneProjected2.x != 0 || HeadBoneProjected2.y != 0 || HeadBoneProjected2.z != 0)
						{
							FVector BOTTOMSIDELEFT = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x + 40, RootBone.y - 40, RootBone.z));
							FVector BOTTOMSIDERIGHT = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x - 40, RootBone.y - 40, RootBone.z));
							FVector BOTTOMSIDELEFT1 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x - 40, RootBone.y + 40, RootBone.z));
							FVector BOTTOMSIDELEFT2 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x + 40, RootBone.y + 40, RootBone.z));
							FVector TOPSIDELEFT = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x + 40, HeadBone.y - 40, HeadBone.z + 15));
							FVector TOPSIDERIGHT = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x - 40, HeadBone.y - 40, HeadBone.z + 15));
							FVector TOPSIDELEFT1 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x - 40, HeadBone.y + 40, HeadBone.z + 15));
							FVector TOPSIDELEFT2 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x + 40, HeadBone.y + 40, HeadBone.z + 15));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT.x, BOTTOMSIDELEFT.y), ImVec2(TOPSIDELEFT.x, TOPSIDELEFT.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDERIGHT.x, BOTTOMSIDERIGHT.y), ImVec2(TOPSIDERIGHT.x, TOPSIDERIGHT.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT1.x, BOTTOMSIDELEFT1.y), ImVec2(TOPSIDELEFT1.x, TOPSIDELEFT1.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT2.x, BOTTOMSIDELEFT2.y), ImVec2(TOPSIDELEFT2.x, TOPSIDELEFT2.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT.x, BOTTOMSIDELEFT.y), ImVec2(BOTTOMSIDERIGHT.x, BOTTOMSIDERIGHT.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDERIGHT.x, BOTTOMSIDERIGHT.y), ImVec2(BOTTOMSIDELEFT1.x, BOTTOMSIDELEFT1.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT1.x, BOTTOMSIDELEFT1.y), ImVec2(BOTTOMSIDELEFT2.x, BOTTOMSIDELEFT2.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT2.x, BOTTOMSIDELEFT2.y), ImVec2(BOTTOMSIDELEFT.x, BOTTOMSIDELEFT.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(TOPSIDELEFT.x, TOPSIDELEFT.y), ImVec2(TOPSIDERIGHT.x, TOPSIDERIGHT.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(TOPSIDERIGHT.x, TOPSIDERIGHT.y), ImVec2(TOPSIDELEFT1.x, TOPSIDELEFT1.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(TOPSIDELEFT1.x, TOPSIDELEFT1.y), ImVec2(TOPSIDELEFT2.x, TOPSIDELEFT2.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(TOPSIDELEFT2.x, TOPSIDELEFT2.y), ImVec2(TOPSIDELEFT.x, TOPSIDELEFT.y), ImColor(colors::TDBox[0], colors::TDBox[1], colors::TDBox[2], colors::TDBox[3]));
						}
					}
					else
					{
						if (HeadBoneProjected2.x != 0 || HeadBoneProjected2.y != 0 || HeadBoneProjected2.z != 0)
						{
							FVector BOTTOMSIDELEFT = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x + 40, RootBone.y - 40, RootBone.z));
							FVector BOTTOMSIDERIGHT = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x - 40, RootBone.y - 40, RootBone.z));
							FVector BOTTOMSIDELEFT1 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x - 40, RootBone.y + 40, RootBone.z));
							FVector BOTTOMSIDELEFT2 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(RootBone.x + 40, RootBone.y + 40, RootBone.z));
							FVector TOPSIDELEFT = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x + 40, HeadBone.y - 40, HeadBone.z + 15));
							FVector TOPSIDERIGHT = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x - 40, HeadBone.y - 40, HeadBone.z + 15));
							FVector TOPSIDELEFT1 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x - 40, HeadBone.y + 40, HeadBone.z + 15));
							FVector TOPSIDELEFT2 = UNREALENGINE::SDK::ProjectWorldToScreen(FVector(HeadBone.x + 40, HeadBone.y + 40, HeadBone.z + 15));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT.x, BOTTOMSIDELEFT.y), ImVec2(TOPSIDELEFT.x, TOPSIDELEFT.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDERIGHT.x, BOTTOMSIDERIGHT.y), ImVec2(TOPSIDERIGHT.x, TOPSIDERIGHT.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT1.x, BOTTOMSIDELEFT1.y), ImVec2(TOPSIDELEFT1.x, TOPSIDELEFT1.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT2.x, BOTTOMSIDELEFT2.y), ImVec2(TOPSIDELEFT2.x, TOPSIDELEFT2.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT.x, BOTTOMSIDELEFT.y), ImVec2(BOTTOMSIDERIGHT.x, BOTTOMSIDERIGHT.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDERIGHT.x, BOTTOMSIDERIGHT.y), ImVec2(BOTTOMSIDELEFT1.x, BOTTOMSIDELEFT1.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT1.x, BOTTOMSIDELEFT1.y), ImVec2(BOTTOMSIDELEFT2.x, BOTTOMSIDELEFT2.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(BOTTOMSIDELEFT2.x, BOTTOMSIDELEFT2.y), ImVec2(BOTTOMSIDELEFT.x, BOTTOMSIDELEFT.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(TOPSIDELEFT.x, TOPSIDELEFT.y), ImVec2(TOPSIDERIGHT.x, TOPSIDERIGHT.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(TOPSIDERIGHT.x, TOPSIDERIGHT.y), ImVec2(TOPSIDELEFT1.x, TOPSIDELEFT1.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(TOPSIDELEFT1.x, TOPSIDELEFT1.y), ImVec2(TOPSIDELEFT2.x, TOPSIDELEFT2.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(TOPSIDELEFT2.x, TOPSIDELEFT2.y), ImVec2(TOPSIDELEFT.x, TOPSIDELEFT.y), ImColor(colors::TDBox1[0], colors::TDBox1[1], colors::TDBox1[2], colors::TDBox1[3]));
						}
					}
				}
				if (Settings::Visuals::Skeleton)
				{
					if (IsVisible)
					{

						
						colors::skeleton[0] = 0.f;
						colors::skeleton[1] = 1.f;
						colors::skeleton[2] = 0.f;
						colors::skeleton[3] = 1.f;



					}
					else
					{
						colors::skeleton[0] = { 1.f };
						colors::skeleton[1] = { 0.f };
						colors::skeleton[2] = { 0.f };
						colors::skeleton[3] = { 1.f };
					}
					renderBones(SkeletalMesh);
				}
			}
		}
	}
	//Sleep(10);
}
