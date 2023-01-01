#include <math.h>
#include "../Valorant/Game/structs.hpp"
#include "Game/sdk.hpp"
#define M_PI                       3.14159265358979323846f

#define URotationToRadians(URotation)		((URotation)* (M_PI / 32768.0f))
#define URotationToDegree( URotation )		( ( URotation ) * ( 360.0f / 65536.0f ) ) 

#define DegreeToURotation( Degree )			( ( Degree ) * ( 65536.0f / 360.0f ) )
#define DegreeToRadian( Degree )			( ( Degree ) * ( M_PI / 180.0f ) )

#define RadianToURotation( URotation )		( ( URotation ) * ( 32768.0f / M_PI ) ) 
#define RadianToDegree( Radian )			( ( Radian ) * ( 180.0f / M_PI ) )

#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )

struct alignas(16) FPlane : public FVector
{
    float                                              W;                                                        // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
};
struct Vector2 {
public:
    float x;
    float y;

    inline Vector2() : x(0), y(0) {}
    inline Vector2(float x, float y) : x(x), y(y) {}

    inline float Distance(Vector2 v) {
        return sqrtf(((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
    }

    inline Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    inline Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }
};
struct FVector2D {
public:
    float x;
    float y;

    inline FVector2D() : x(0), y(0) {}
    inline FVector2D(float x, float y) : x(x), y(y) {}

    inline float Distance(FVector2D v) {
        return sqrtf(((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
    }

    inline FVector2D operator+(const FVector2D& v) const {
        return FVector2D(x + v.x, y + v.y);
    }

    inline FVector2D operator-(const FVector2D& v) const {
        return FVector2D(x - v.x, y - v.y);
    }

};
struct FMatrix
{
    struct FPlane                                      XPlane;                                                   // 0x0000(0x0010) (Edit, BlueprintVisible, SaveGame, IsPlainOldData)
    struct FPlane                                      YPlane;                                                   // 0x0010(0x0010) (Edit, BlueprintVisible, SaveGame, IsPlainOldData)
    struct FPlane                                      ZPlane;                                                   // 0x0020(0x0010) (Edit, BlueprintVisible, SaveGame, IsPlainOldData)
    struct FPlane                                      WPlane;                                                   // 0x0030(0x0010) (Edit, BlueprintVisible, SaveGame, IsPlainOldData)

    FMatrix operator*(const FMatrix& pM2)
    {
        FMatrix pOut;
        pOut.XPlane.x = XPlane.x * pM2.XPlane.x + XPlane.y * pM2.YPlane.x + XPlane.z * pM2.ZPlane.x + XPlane.W * pM2.WPlane.x;
        pOut.XPlane.y = XPlane.x * pM2.XPlane.y + XPlane.y * pM2.YPlane.y + XPlane.z * pM2.ZPlane.y + XPlane.W * pM2.WPlane.y;
        pOut.XPlane.z = XPlane.x * pM2.XPlane.z + XPlane.y * pM2.YPlane.z + XPlane.z * pM2.ZPlane.z + XPlane.W * pM2.WPlane.z;
        pOut.XPlane.W = XPlane.x * pM2.XPlane.W + XPlane.y * pM2.YPlane.W + XPlane.z * pM2.ZPlane.W + XPlane.W * pM2.WPlane.W;
        pOut.YPlane.x = YPlane.x * pM2.XPlane.x + YPlane.y * pM2.YPlane.x + YPlane.z * pM2.ZPlane.x + YPlane.W * pM2.WPlane.x;
        pOut.YPlane.y = YPlane.x * pM2.XPlane.y + YPlane.y * pM2.YPlane.y + YPlane.z * pM2.ZPlane.y + YPlane.W * pM2.WPlane.y;
        pOut.YPlane.z = YPlane.x * pM2.XPlane.z + YPlane.y * pM2.YPlane.z + YPlane.z * pM2.ZPlane.z + YPlane.W * pM2.WPlane.z;
        pOut.YPlane.W = YPlane.x * pM2.XPlane.W + YPlane.y * pM2.YPlane.W + YPlane.z * pM2.ZPlane.W + YPlane.W * pM2.WPlane.W;
        pOut.ZPlane.x = ZPlane.x * pM2.XPlane.x + ZPlane.y * pM2.YPlane.x + ZPlane.z * pM2.ZPlane.x + ZPlane.W * pM2.WPlane.x;
        pOut.ZPlane.y = ZPlane.x * pM2.XPlane.y + ZPlane.y * pM2.YPlane.y + ZPlane.z * pM2.ZPlane.y + ZPlane.W * pM2.WPlane.y;
        pOut.ZPlane.z = ZPlane.x * pM2.XPlane.z + ZPlane.y * pM2.YPlane.z + ZPlane.z * pM2.ZPlane.z + ZPlane.W * pM2.WPlane.z;
        pOut.ZPlane.W = ZPlane.x * pM2.XPlane.W + ZPlane.y * pM2.YPlane.W + ZPlane.z * pM2.ZPlane.W + ZPlane.W * pM2.WPlane.W;
        pOut.WPlane.x = WPlane.x * pM2.XPlane.x + WPlane.y * pM2.YPlane.x + WPlane.z * pM2.ZPlane.x + WPlane.W * pM2.WPlane.x;
        pOut.WPlane.y = WPlane.x * pM2.XPlane.y + WPlane.y * pM2.YPlane.y + WPlane.z * pM2.ZPlane.y + WPlane.W * pM2.WPlane.y;
        pOut.WPlane.z = WPlane.x * pM2.XPlane.z + WPlane.y * pM2.YPlane.z + WPlane.z * pM2.ZPlane.z + WPlane.W * pM2.WPlane.z;
        pOut.WPlane.W = WPlane.x * pM2.XPlane.W + WPlane.y * pM2.YPlane.W + WPlane.z * pM2.ZPlane.W + WPlane.W * pM2.WPlane.W;
        return pOut;
    }
};

