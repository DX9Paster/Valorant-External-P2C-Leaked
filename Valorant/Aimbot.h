#pragma once
#include <Windows.h>
#include "Driver/Driver.h"

#define UCONST_Pi 3.1415926535
#define RadianToURotation 180.0f / UCONST_Pi


auto GetBone(DWORD_PTR mesh, int id) -> FVector
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
FVector VectorToRotation(FVector relativeLocation) // COPY PASTE UC SHIT
{
	constexpr auto radToUnrRot = 57.2957795f;

	return FVector(
		atan2(relativeLocation.z, sqrt((relativeLocation.x * relativeLocation.x) + (relativeLocation.y * relativeLocation.y))) * radToUnrRot,
		atan2(relativeLocation.y, relativeLocation.x) * radToUnrRot,
		0.f);
}
FVector CLAMPEDVECTOR(FVector targetLocation, FVector cameraLocation)
{
	return VectorToRotation(targetLocation - cameraLocation);
}
FVector SMOOTHEDANGLES(FVector rot1, FVector rot2, float smooth)
{
	FVector ret(0, 0, 0);

	ret.x = (rot2.x - rot1.x) / smooth + rot1.x;
	ret.y = (rot2.y - rot1.y) / smooth + rot1.y;
	ret.z = (rot2.z - rot1.z) / smooth + rot1.z;

	return ret;
}
void SMOOTHFACTOR(FVector Target, FVector Camera_rotation, float SmoothFactor)
{

	for (PlayerContrPTR PlayerPTR : PPTR)
	{
		FVector ConvertRotation = Camera_rotation;

		auto ControlRotation = Read<FVector>(PlayerPTR.PCTR + offsets::control_rotation);
		FVector DeltaRotation = ConvertRotation - ControlRotation;

		ConvertRotation = Target - (DeltaRotation * SmoothFactor);

		FVector Smoothed = SMOOTHEDANGLES(Camera_rotation, ConvertRotation, SmoothFactor);
		Write<FVector>(PlayerPTR.PCTR + offsets::control_rotation, Smoothed);
	}
	
}
auto AIMBOT(DWORD_PTR entity) -> void
{
	FVector HITHEAD = GetBone(Read<uint64_t>(entity + offsets::MeshComponent), 8);

	
#include "../Valorant/Game/cheat.hpp"

	std::vector<PlayerContrPTR> PlayerPTR;


	FVector CLAMPEDANGLE = CLAMPEDVECTOR(HITHEAD, CameraLocation);
	for (PlayerContrPTR PlayerPTR : PPTR)
	{
		if (Settings::aimbot::smooth)
		{
			SMOOTHFACTOR(CLAMPEDANGLE, CameraRotation, Settings::aimbot::smoothness);
		}
		else
		Write<FVector>(PlayerPTR.PCTR + offsets::control_rotation, CLAMPEDANGLE);
	}

}
