// Fill out your copyright notice in the Description page of Project Settings.


#include "DeterministicFloatVector64.h"
#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatPlane64Funcs.h"
#include "DeterministicFloatQuat64Funcs.h"


const FDeterministicVector64 FDeterministicVector64::ZeroVector =		FDeterministicVector64((int64)0,	(int64)0,	(int64)0);
const FDeterministicVector64 FDeterministicVector64::OneVector =		FDeterministicVector64((int64)1,	(int64)1,	(int64)1);
const FDeterministicVector64 FDeterministicVector64::UpVector =			FDeterministicVector64((int64)0,	(int64)0,	(int64)1);
const FDeterministicVector64 FDeterministicVector64::DownVector =		FDeterministicVector64((int64)0,	(int64)0,	(int64)-1);
const FDeterministicVector64 FDeterministicVector64::ForwardVector =	FDeterministicVector64((int64)1,	(int64)0,	(int64)0);
const FDeterministicVector64 FDeterministicVector64::BackwardVector =	FDeterministicVector64((int64)-1, (int64)0,	(int64)0);
const FDeterministicVector64 FDeterministicVector64::RightVector =		FDeterministicVector64((int64)0,	(int64)1,	(int64)0);
const FDeterministicVector64 FDeterministicVector64::LeftVector =		FDeterministicVector64((int64)0,	(int64)-1,	(int64)0);
const FDeterministicVector64 FDeterministicVector64::XAxisVector =		FDeterministicVector64((int64)1,	(int64)0,	(int64)0);
const FDeterministicVector64 FDeterministicVector64::YAxisVector =		FDeterministicVector64((int64)0,	(int64)1,	(int64)0);
const FDeterministicVector64 FDeterministicVector64::ZAxisVector =		FDeterministicVector64((int64)0,	(int64)0,	(int64)1);


FDeterministicVector64 FDeterministicVector64::MirrorByPlane(const FDeterministicPlane64& Plane) const
{
	return *this - Plane * (FDeterministicNumber64::Make(2.0) * Plane.PlaneDot(*this));
}

FDeterministicVector64 FDeterministicVector64::PointPlaneProject(const FDeterministicVector64& Point, const FDeterministicPlane64& Plane)
{
	//Find the distance of X from the plane
	//Add the distance back along the normal from the point
	return Point - Plane.PlaneDot(Point) * Plane;
}

FDeterministicRotator64 FDeterministicVector64::ToOrientationRotator() const
{
	FDeterministicRotator64 R;

	// Find yaw.
	R.Yaw = FDeterministicFloatMath::RadiansToDegrees(FDeterministicFloatMath::Atan2(Y, X));

	// Find pitch.
	R.Pitch = FDeterministicFloatMath::RadiansToDegrees(FDeterministicFloatMath::Atan2(Z, FDeterministicFloatMath::Sqrt(X * X + Y * Y)));

	// Find roll.
	R.Roll = 0;

	return R;
}

FDeterministicQuat64 FDeterministicVector64::ToOrientationQuat() const
{
	// Essentially an optimized Vector->Rotator->Quat made possible by knowing Roll == 0, and avoiding radians->degrees->radians.
	// This is done to avoid adding any roll (which our API states as a constraint).
	const FDeterministicNumber64 YawRad = FDeterministicFloatMath::Atan2(Y, X);
	const FDeterministicNumber64 PitchRad = FDeterministicFloatMath::Atan2(Z, FDeterministicFloatMath::Sqrt(X * X + Y * Y));

	FDeterministicNumber64 SP, SY;
	FDeterministicNumber64 CP, CY;

	FDeterministicFloatMath::SinCos(&SP, &CP, PitchRad * DeterministicFloat::Constants::Number64::Half);
	FDeterministicFloatMath::SinCos(&SY, &CY, YawRad * DeterministicFloat::Constants::Number64::Half);

	FDeterministicQuat64 RotationQuat;
	RotationQuat.X = SP * SY;
	RotationQuat.Y = -SP * CY;
	RotationQuat.Z = CP * SY;
	RotationQuat.W = CP * CY;
	return RotationQuat;
}