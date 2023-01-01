#pragma once

#include <Windows.h>
#include <map>
#include <d3d9types.h>
#include "../Overlay/render.hpp"
#include "../Driver/driver.h"
#include "structs.hpp"
#include <vector>
#include "../defs.h"
using namespace UE4Structs;

namespace Globals
{

	DWORD_PTR
		LocalPlayer,
		PlayerController,
		PlayerCameraManager;

	int MyUniqueID, MyTeamID, BoneCount;
	inline int g_localteamid;
	FVector MyRelativeLocation, closestPawn;

	namespace Camera
	{
		FVector CameraLocation, CameraRotation, TargetRotation;
		float FovAngle;
	}


}

using namespace Globals;
using namespace Camera;


namespace UNREALENGINE
{

	struct SGAMEINSTANCE {
		uintptr_t ULocalPlayer(uintptr_t UGameInstance) {
			auto ULocalPlayerArray = Read<uintptr_t>(UGameInstance + offsets::LocalPlayers);
			return Read<uintptr_t>(ULocalPlayerArray);
		};
	};

	struct SULEVEL {
		TArrayDrink<uintptr_t> AActorArray(uintptr_t ULevel) {
			return Read<TArrayDrink<uintptr_t>>(ULevel + offsets::AActorArray);
		};
	};



	struct SUSKELETALMESH {
		int BoneCount(uintptr_t Mesh) {
			return Read<uintptr_t>(Mesh + offsets::BoneCount);
		};
	};

	struct SLOCALPLAYER {
		uintptr_t APlayerController(uintptr_t ULocalPlayer) {
			return Read<uintptr_t>(ULocalPlayer + offsets::PlayerController);
		};
	};
	struct SACTOR {
		uintptr_t USkeletalMeshComponent(uintptr_t Pawn) {
			return Read<uintptr_t>(Pawn + offsets::MeshComponent);
		};
	};
	struct SPLAYERCONTROLLER {
		uintptr_t APlayerCameraManager(uintptr_t APlayerController) {
			return Read<uintptr_t>(APlayerController + offsets::PlayerCameraManager);
		};
		uintptr_t AHUD(uintptr_t APlayerController) {
			return Read<uintptr_t>(APlayerController + offsets::MyHUD);
		};
		uintptr_t APawn(uintptr_t APlayerController) {
			return Read<uintptr_t>(APlayerController + offsets::AcknowledgedPawn);
		};
	};
	struct SCONTROLROTATION {
		uintptr_t AControlRotation(uintptr_t APlayerController) {
			return Read<uintptr_t>(APlayerController + offsets::control_rotation);
		};
	};
	struct WORLDFACTOR
	{
		uintptr_t GameInstance(uintptr_t GameWorld) {
			return Read<uintptr_t>(GameWorld + offsets::Gameinstance);
		};

		uintptr_t ULevel(uintptr_t World) {
			return Read<uintptr_t>(World + offsets::Ulevel);
		};
	};
	struct SPAWN {
		auto TeamID(uintptr_t APawn) -> int {
			auto PlayerState = Read<uintptr_t>(APawn + offsets::PlayerState);
			auto TeamComponent = Read<uintptr_t>(PlayerState + offsets::TeamComponent);
			return Read<int>(TeamComponent + offsets::TeamID);
		};

		auto UniqueID(uintptr_t APawn) -> int {
			return Read<int>(APawn + offsets::UniqueID);
		};

		auto FNameID(uintptr_t APawn) -> int {
			return Read<int>(APawn + offsets::FNameID);
		};

		auto RelativeLocation(uintptr_t APawn) -> FVector {
			auto RootComponent = Read<uintptr_t>(APawn + offsets::RootComponent);
			return Read<FVector>(RootComponent + offsets::RelativeLocation);
		};

		auto bIsDormant(uintptr_t APawn) -> bool {
			return Read<bool>(APawn + offsets::bIsDormant);
		};

		auto Health(uintptr_t APawn) -> float {
			auto DamageHandler = Read<uintptr_t>(APawn + offsets::DamageHandler);
			return Read<float>(DamageHandler + offsets::Health);
		};
	};

	auto GetWorld(uintptr_t Pointer) -> uintptr_t
	{
		std::uintptr_t uworld_addr = Read<uintptr_t>(Pointer + 0x50);

		unsigned long long uworld_offset;

		if (uworld_addr > 0x10000000000)
		{
			uworld_offset = uworld_addr - 0x10000000000;
		}
		else {
			uworld_offset = uworld_addr - 0x8000000000;
		}

		return Pointer + uworld_offset;
	}
	auto isVisible(DWORD_PTR mesh) -> bool
	{
		float fLastSubmitTime = Read<float>(mesh + offsets::last_submit_time);
		float fLastRenderTimeOnScreen = Read<float>(mesh + offsets::last_render_time);

		const float fVisionTick = 0.06f;
		bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;

		return bVisible;
	}


	namespace SDK
	{
		auto GetEntityBone(DWORD_PTR mesh, int id) -> FVector
		{
			DWORD_PTR array = Read<uintptr_t>(mesh + offsets::BoneArray);
			if (array == NULL)
				array = Read<uintptr_t>(mesh + offsets::BoneArrayCache);

			FTransform bone = Read<FTransform>(array + (id * 0x30));

			FTransform ComponentToWorld = Read<FTransform>(mesh + offsets::ComponentToWorld);
			D3DMATRIX Matrix;

			Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

			return FVector(Matrix._41, Matrix._42, Matrix._43);
		}

		auto ProjectWorldToScreen(FVector WorldLocation) -> FVector
		{
			FVector Screenlocation = FVector(0, 0, 0);

			auto ViewInfo = Read<FMinimalViewInfo>(PlayerCameraManager + offsets::camera_cache + offsets::PlayerCache);

			CameraLocation = ViewInfo.Location;
			CameraRotation = ViewInfo.Rotation;


			D3DMATRIX tempMatrix = Matrix(CameraRotation, FVector(0, 0, 0));

			FVector vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]),
				vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]),
				vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

			FVector vDelta = WorldLocation - CameraLocation;
			FVector vTransformed = FVector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

			if (vTransformed.z < 1.f) vTransformed.z = 1.f;

			FovAngle = ViewInfo.FOV;

			float ScreenCenterX = Width / 2.0f;
			float ScreenCenterY = Height / 2.0f;

			Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
			Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

			return Screenlocation;
		}

		bool IsVec3Valid(FVector vec3)
		{
			return !(vec3.x == 0 && vec3.y == 0 && vec3.z == 0);
		}
	}
}

uintptr_t decryptWorld(uintptr_t base_address)
{
	const auto key = Read<uintptr_t>(image_base + offsets::World_Key);
	const auto state = Read<State>(image_base + offsets::World_State);
	const auto uworld_ptr = decrypt_uworld(key, (uintptr_t*)&state);
	return Read<uintptr_t>(uworld_ptr);
}
