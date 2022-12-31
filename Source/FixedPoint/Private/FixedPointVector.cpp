// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointVector.h"
#include "FixedPointTypes.h"


const FFixedVector64 FFixedVector64::ZeroVector =		FFixedVector64((int64)0,	(int64)0,	(int64)0);
const FFixedVector64 FFixedVector64::OneVector =		FFixedVector64((int64)1,	(int64)1,	(int64)1);
const FFixedVector64 FFixedVector64::UpVector =			FFixedVector64((int64)0,	(int64)0,	(int64)1);
const FFixedVector64 FFixedVector64::DownVector =		FFixedVector64((int64)0,	(int64)0,	(int64)-1);
const FFixedVector64 FFixedVector64::ForwardVector =	FFixedVector64((int64)1,	(int64)0,	(int64)0);
const FFixedVector64 FFixedVector64::BackwardVector =	FFixedVector64((int64)-1, (int64)0,	(int64)0);
const FFixedVector64 FFixedVector64::RightVector =		FFixedVector64((int64)0,	(int64)1,	(int64)0);
const FFixedVector64 FFixedVector64::LeftVector =		FFixedVector64((int64)0,	(int64)-1,	(int64)0);
const FFixedVector64 FFixedVector64::XAxisVector =		FFixedVector64((int64)1,	(int64)0,	(int64)0);
const FFixedVector64 FFixedVector64::YAxisVector =		FFixedVector64((int64)0,	(int64)1,	(int64)0);
const FFixedVector64 FFixedVector64::ZAxisVector =		FFixedVector64((int64)0,	(int64)0,	(int64)1);


FFixedVector64 FFixedVector64::MirrorByPlane(const FFixedPlane& Plane) const
{
	return *this - Plane * (FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value * 2) * Plane.PlaneDot(*this));
}

FFixedVector64 FFixedVector64::PointPlaneProject(const FFixedVector64& Point, const FFixedPlane& Plane)
{
	//Find the distance of X from the plane
	//Add the distance back along the normal from the point
	return Point - Plane.PlaneDot(Point) * Plane;
}

FFixedRotator64 FFixedVector64::ToOrientationRotator() const
{
	FFixedRotator64 R;

	// Find yaw.
	R.Yaw = FFixedPointMath::RadiansToDegrees(FFixedPointMath::Atan2(Y, X));

	// Find pitch.
	R.Pitch = FFixedPointMath::RadiansToDegrees(FFixedPointMath::Atan2(Z, FFixedPointMath::Sqrt(X * X + Y * Y)));

	// Find roll.
	R.Roll = 0;

	return R;
}

FFixedQuat64 FFixedVector64::ToOrientationQuat() const
{
	// Essentially an optimized Vector->Rotator->Quat made possible by knowing Roll == 0, and avoiding radians->degrees->radians.
	// This is done to avoid adding any roll (which our API states as a constraint).
	const FFixed64 YawRad = FFixedPointMath::Atan2(Y, X);
	const FFixed64 PitchRad = FFixedPointMath::Atan2(Z, FFixedPointMath::Sqrt(X * X + Y * Y));

	FFixed64 SP, SY;
	FFixed64 CP, CY;

	FFixedPointMath::SinCos(&SP, &CP, PitchRad * FixedPoint::Constants::Fixed64::Half);
	FFixedPointMath::SinCos(&SY, &CY, YawRad * FixedPoint::Constants::Fixed64::Half);

	FFixedQuat64 RotationQuat;
	RotationQuat.X = SP * SY;
	RotationQuat.Y = -SP * CY;
	RotationQuat.Z = CP * SY;
	RotationQuat.W = CP * CY;
	return RotationQuat;
}