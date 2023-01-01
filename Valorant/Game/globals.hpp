#pragma once
#include <Windows.h>

HWND Entryhwnd = NULL;
int processid = 0;
int process_id;
DWORD64 image_base;
DWORD_PTR PlayerState;
namespace CRiQTest
{
    uintptr_t APlayerController;
    inline uintptr_t g_localplayerpawn;
    inline uintptr_t g_localplayercontroller;
    inline int team_id1;
    uintptr_t Mesh;
}
namespace test
{
    uintptr_t abc;
}
namespace offsets
{
    DWORD
        World_Key = 0x8FB80F8,
        World_State = 0x8FB80C0,
        //
        Gameinstance = 0x1A0,
        Ulevel = 0x38,
        LocalPlayers = 0x40,
        PlayerController = 0x38,
        PlayerCameraManager = 0x478,
        MyHUD = 0x470, //struct AHUD* MyHUD; // 0x470(0x08)
        AcknowledgedPawn = 0x460,
        PlayerState = 0x3f0,
        TeamComponent = 0x628,
        TeamID = 0xf8,
        CameraFOVChange = 0x3f4,// 0x3f4(0x04)
        UniqueID = 0x38,
        FNameID = 0x18,
        AActorArray = 0xa0,
        RootComponent = 0x230,
        RelativeLocation = 0x164,
        MeshComponent = 0x430,
        DamageHandler = 0x9a8,
        bIsDormant = 0x100,
        Health = 0x1b0,
        ComponentToWorld = 0x250,
        BoneArray = 0x5C0,
        BoneArrayCache = BoneArray + 0x10,
        BoneCount = 0x5c8,
        last_submit_time = 0x378,
        last_render_time = last_submit_time + 0x4,
        bone_array = 0x5C0,
        bone_count = bone_array + 0x8,
        control_rotation = 0x440,
        bone_id = 0x30,
        camera_cache = 0x1FE0,
        PlayerCache = 0x10,
        inventory = 0x948,
        ammo_info = 0xFB0,
        current_ammo = 0xFB0,
        current_equipable = 0x228,
        max_ammo = 0x11C,
        ActorCount = 0xB8,
        CameraRotation = 0x126C,
        CameraPosition = 0x1260,
        bone_array_fail = 0x568;
}
namespace colors {

    inline float snaplines[] = { 0.f,1.f,0.f,1.f };
    inline float HP[] = { 0.f,1.f,0.f,1.f };
    inline float snaplinesinvisible[] = { 1.f,0.f,0.f,1.f };
    inline float box[] = { 0.f,1.f,0.f,1.f };
    inline float boxoutline[] = { 0.f,1.f,0.f,1.f };
    inline float boxinvisible[] = { 1.f,0.f,0.f,1.f };
    inline float boxoutlineinvisible[] = { 1.f,0.f,0.f,1.f };
    inline float BLAHBLAH[] = { 0.f,1.f,0.f,1.f };
    inline float skeleton[] = { 0.f,1.f,0.f,1.f };
    inline float skeletoninvisible[] = { 1.f,0.f,0.f,1.f };
    inline float Head[] = { 1.f,0.f,0.f,1.f };
    inline float TDBox[] = { 0.f,1.f,0.f,1.f };
    inline float TDBox1[] = { 1.f,0.f,0.f,1.f };
    inline float radar[] = { 1.f,0.f,1.f,1.f };
    inline float ImGuiCol_Border[] = { 1.f,0.f,0.f,1.f };
    inline float ImGuiCol_TitleBg[] = { 132.f ,0.f,181.f,0.3f };

}
namespace Settings
{
    inline bool bMenu = true;
    inline bool bRadar = false;
    inline bool TEST = false;
    namespace Visuals
    {
        inline float skeletonwidht = 0.5f;
        inline bool bSnaplines = false;
        inline bool bDistance = false;
        inline bool bBox = false;
        inline bool bBoxOutlined = false;
        inline bool HeadCircle = false;
        inline bool bHealth = false;
        inline bool Skeleton = false;
        inline float BoxWidth = 1.0f;
        inline float fovchangervalue;
        inline bool fovchanger = false;
        inline bool ammowarning = false;
        inline int customwarning = 4;
        inline bool isVisibleGlobal;
        inline bool FPS;
        inline bool TDBox = false;
    }
    namespace aimbot
    {
        inline bool aimbot = false;
        inline float fov = 50;
        inline float smoothness = 1.0f;
        inline bool smooth = false;
        inline bool drawfov = false;
        inline bool vischeck = false;
        inline bool filledfov = false;
    }
    namespace misc
    {
        inline bool option1 = true;
        inline float headsize = 0;

        inline int enemyselect = 0;
        inline bool radar = false;
        inline float radarentitysize = 3.0f;
        inline float Size = 256;
        static const char* Teams[]{ "Enemy", "Bots", "None" };
    }
}

namespace NewFeatures
{
    inline float renderdistance = 750;
    inline bool ActorCountDebug = false;
    inline int curractors = 0;
}

