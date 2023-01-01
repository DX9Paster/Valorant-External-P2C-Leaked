#pragma once
#include <Windows.h>
#include "Driver/Driver.h"
#include "../Valorant/Game/structs.hpp"
#include "Game/sdk.hpp"


void DrawLineSimple(FVector first_bone_position, FVector second_bone_position) {

	auto first_bone_screen_position = UNREALENGINE::SDK::ProjectWorldToScreen(first_bone_position);
	if (first_bone_screen_position.x == 0 && first_bone_screen_position.y == 0) return;

	auto second_bone_screen_position = UNREALENGINE::SDK::ProjectWorldToScreen(second_bone_position);
	if (second_bone_screen_position.x == 0 && second_bone_screen_position.y == 0) return;

	//ImColor White = { 0, 49, 164, 255 };
	DrawALine(ImVec2(first_bone_screen_position.x, first_bone_screen_position.y), ImVec2(second_bone_screen_position.x, second_bone_screen_position.y), ImColor(colors::skeleton[0] , colors::skeleton[1] , colors::skeleton[2] , colors::skeleton[3] ),Settings::Visuals::skeletonwidht);
}


void DrawSkeleton(uintptr_t Mesh) {

	//
	FVector vHipOut;
	FVector vHeadBoneOut;
	FVector vNeckOut;
	FVector vUpperArmLeftOut;
	FVector vLeftHandOut;
	FVector vLeftHandOut1;
	FVector vUpperArmRightOut;
	FVector vRightHandOut;
	FVector vRightHandOut1;
	FVector vLeftThighOut;
	FVector vLeftCalfOut;
	FVector vLeftFootOut;
	FVector vRightThighOut;
	FVector vRightCalfOut;
	FVector vRightFootOut;
	//

	int BoneCount = Read<int>(Mesh + offsets::BoneCount);

	if (BoneCount == 0) {
		vHipOut = GetBone(Mesh, 3);

		vHeadBoneOut = GetBone(Mesh, 8);
		vNeckOut = GetBone(Mesh, 7);

		vUpperArmLeftOut = GetBone(Mesh, 11);
		vLeftHandOut = GetBone(Mesh, 12);
		vLeftHandOut1 = GetBone(Mesh, 13);

		vUpperArmRightOut = GetBone(Mesh, 36);
		vRightHandOut = GetBone(Mesh, 37);
		vRightHandOut1 = GetBone(Mesh, 38);



		vLeftThighOut = GetBone(Mesh, 63);
		vLeftCalfOut = GetBone(Mesh, 65);
		vLeftFootOut = GetBone(Mesh, 69);

		vRightThighOut = GetBone(Mesh, 77);
		vRightCalfOut = GetBone(Mesh, 79);
		vRightFootOut = GetBone(Mesh, 83);
	}
	else {
		vHipOut = GetBone(Mesh, 3);

		vHeadBoneOut = GetBone(Mesh, 8);
		vNeckOut = GetBone(Mesh, 7);

		vUpperArmLeftOut = GetBone(Mesh, 11);
		vLeftHandOut = GetBone(Mesh, 12);
		vLeftHandOut1 = GetBone(Mesh, 13);

		vUpperArmRightOut = GetBone(Mesh, 36);
		vRightHandOut = GetBone(Mesh, 37);
		vRightHandOut1 = GetBone(Mesh, 38);



		vLeftThighOut = GetBone(Mesh, 63);
		vLeftCalfOut = GetBone(Mesh, 65);
		vLeftFootOut = GetBone(Mesh, 69);

		vRightThighOut = GetBone(Mesh, 77);
		vRightCalfOut = GetBone(Mesh, 79);
		vRightFootOut = GetBone(Mesh, 83);
	}

		DrawLineSimple(vNeckOut, vHeadBoneOut);
		DrawLineSimple(vHipOut, vNeckOut);
		DrawLineSimple(vUpperArmLeftOut, vNeckOut);
		DrawLineSimple(vUpperArmRightOut, vNeckOut);
		DrawLineSimple(vLeftHandOut, vUpperArmLeftOut);
		DrawLineSimple(vRightHandOut, vUpperArmRightOut);
		DrawLineSimple(vLeftHandOut, vLeftHandOut1);
		DrawLineSimple(vRightHandOut, vRightHandOut1);
		DrawLineSimple(vLeftThighOut, vHipOut);
		DrawLineSimple(vRightThighOut, vHipOut);
		DrawLineSimple(vLeftCalfOut, vLeftThighOut);
		DrawLineSimple(vRightCalfOut, vRightThighOut);
		DrawLineSimple(vLeftFootOut, vLeftCalfOut);
		DrawLineSimple(vRightFootOut, vRightCalfOut);


}

inline auto renderBones(uintptr_t Mesh)  -> void {

	FVector head_position = GetBone(Mesh, 8);
	FVector neck_position;
	FVector chest_position = GetBone(Mesh, 6);
	FVector l_upper_arm_position;
	FVector l_fore_arm_position;
	FVector l_hand_position;
	FVector r_upper_arm_position;
	FVector r_fore_arm_position;
	FVector r_hand_position;
	FVector stomach_position = GetBone(Mesh, 4);
	FVector pelvis_position = GetBone(Mesh, 3);
	FVector l_thigh_position;
	FVector l_knee_position;
	FVector l_foot_position;
	FVector r_thigh_position;
	FVector r_knee_position;
	FVector r_foot_position;
	std::vector<SSkeletal> SKLT;

	for (SSkeletal SKLT : SPTR)
	{
		auto BoneCount = (SKLT.Skeletal);
		//printf("Bones = %i \n", BoneCount);
		
		if (BoneCount == 104) { // MALE & FEMALE

			neck_position = GetBone(Mesh, 19);

			l_upper_arm_position = GetBone(Mesh, 21);
			l_fore_arm_position = GetBone(Mesh, 22);
			l_hand_position = GetBone(Mesh, 23);

			r_upper_arm_position = GetBone(Mesh, 47);
			r_fore_arm_position = GetBone(Mesh, 48);
			r_hand_position = GetBone(Mesh, 49);

			l_thigh_position = GetBone(Mesh, 75);
			l_knee_position = GetBone(Mesh, 76);
			l_foot_position = GetBone(Mesh, 78);

			r_thigh_position = GetBone(Mesh, 82);
			r_knee_position = GetBone(Mesh, 83);
			r_foot_position = GetBone(Mesh, 85);
		}

		else if (BoneCount == 101) {

			neck_position = GetBone(Mesh, 21);

			l_upper_arm_position = GetBone(Mesh, 45);
			l_fore_arm_position = GetBone(Mesh, 42);
			l_hand_position = GetBone(Mesh, 44);

			r_upper_arm_position = GetBone(Mesh, 48);
			r_fore_arm_position = GetBone(Mesh, 67);
			r_hand_position = GetBone(Mesh, 69);

			l_thigh_position = GetBone(Mesh, 75);
			l_knee_position = GetBone(Mesh, 76);
			l_foot_position = GetBone(Mesh, 78);

			r_thigh_position = GetBone(Mesh, 82);
			r_knee_position = GetBone(Mesh, 84);
			r_foot_position = GetBone(Mesh, 85);
		}

		else if (BoneCount == 103) { // BOT

			neck_position = GetBone(Mesh, 9);

			l_upper_arm_position = GetBone(Mesh, 33);
			l_fore_arm_position = GetBone(Mesh, 30);
			l_hand_position = GetBone(Mesh, 32);

			r_upper_arm_position = GetBone(Mesh, 58);
			r_fore_arm_position = GetBone(Mesh, 55);
			r_hand_position = GetBone(Mesh, 57);

			l_thigh_position = GetBone(Mesh, 63);
			l_knee_position = GetBone(Mesh, 65);
			l_foot_position = GetBone(Mesh, 69);

			r_thigh_position = GetBone(Mesh, 77);
			r_knee_position = GetBone(Mesh, 79);
			r_foot_position = GetBone(Mesh, 83);
		}
		else {
			return;
		}
	}



	DrawLineSimple(head_position, neck_position);
	DrawLineSimple(neck_position, chest_position);
	DrawLineSimple(neck_position, l_upper_arm_position);
	DrawLineSimple(l_upper_arm_position, l_fore_arm_position);
	DrawLineSimple(l_fore_arm_position, l_hand_position);
	DrawLineSimple(neck_position, r_upper_arm_position);
	DrawLineSimple(r_upper_arm_position, r_fore_arm_position);
	DrawLineSimple(r_fore_arm_position, r_hand_position);
	DrawLineSimple(chest_position, stomach_position);
	DrawLineSimple(stomach_position, pelvis_position);
	DrawLineSimple(pelvis_position, l_thigh_position);
	DrawLineSimple(l_thigh_position, l_knee_position);
	DrawLineSimple(l_knee_position, l_foot_position);
	DrawLineSimple(pelvis_position, r_thigh_position);
	DrawLineSimple(r_thigh_position, r_knee_position);
	DrawLineSimple(r_knee_position, r_foot_position);
}

