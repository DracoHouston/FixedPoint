// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatMathFuncs.h"
#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatQuat64Funcs.h"

FORCEINLINE void FDeterministicRotator64::DiagnosticCheckNaN() const
{
}
FORCEINLINE void FDeterministicRotator64::DiagnosticCheckNaN(const TCHAR* Message) const
{
}

FORCEINLINE FDeterministicRotator64::FDeterministicRotator64()
{
}

FORCEINLINE FDeterministicRotator64::FDeterministicRotator64(FDeterministicNumber64 InF) : Pitch(InF), Yaw(InF), Roll(InF)
{
}

FORCEINLINE FDeterministicRotator64::FDeterministicRotator64(FDeterministicNumber64 InPitch, FDeterministicNumber64 InYaw, FDeterministicNumber64 InRoll)
	: Pitch(InPitch), Yaw(InYaw), Roll(InRoll)	
{
}

FORCEINLINE FDeterministicRotator64::FDeterministicRotator64(EForceInit) : Pitch(DeterministicFloat::Constants::Number64::Zero), Yaw(DeterministicFloat::Constants::Number64::Zero), Roll(DeterministicFloat::Constants::Number64::Zero) {}

FORCEINLINE FDeterministicRotator64::FDeterministicRotator64(const FDeterministicQuat64& Quat)
{
	*this = Quat.Rotator();
}

FORCEINLINE FDeterministicRotator64::FDeterministicRotator64(const FRotator& Rot)
{
	Pitch = Rot.Pitch;
	Yaw = Rot.Yaw;
	Roll = Rot.Roll;
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::operator+(const FDeterministicRotator64& R) const
{
	return FDeterministicRotator64(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll);
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::operator-(const FDeterministicRotator64& R) const
{
	return FDeterministicRotator64(Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll);
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::operator*(FDeterministicNumber64 Scale) const
{
	return FDeterministicRotator64(Pitch * Scale, Yaw * Scale, Roll * Scale);
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::operator*=(FDeterministicNumber64 Scale)
{
	Pitch = Pitch * Scale; Yaw = Yaw * Scale; Roll = Roll * Scale;
	return *this;
}

FORCEINLINE bool FDeterministicRotator64::operator==(const FDeterministicRotator64& R) const
{
	return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll;
}

FORCEINLINE bool FDeterministicRotator64::operator!=(const FDeterministicRotator64& V) const
{
	return Pitch != V.Pitch || Yaw != V.Yaw || Roll != V.Roll;
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::operator+=(const FDeterministicRotator64& R)
{
	Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
	return *this;
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::operator-=(const FDeterministicRotator64& R)
{
	Pitch -= R.Pitch; Yaw -= R.Yaw; Roll -= R.Roll;
	return *this;
}

FORCEINLINE bool FDeterministicRotator64::IsNearlyZero(FDeterministicNumber64 Tolerance) const
{
	return
		FDeterministicFloatMath::Abs(NormalizeAxis(Pitch)) <= Tolerance
		&& FDeterministicFloatMath::Abs(NormalizeAxis(Yaw)) <= Tolerance
		&& FDeterministicFloatMath::Abs(NormalizeAxis(Roll)) <= Tolerance;
}

FORCEINLINE bool FDeterministicRotator64::IsZero() const
{
	return (ClampAxis(Pitch) == DeterministicFloat::Constants::Number64::Zero) && (ClampAxis(Yaw) == DeterministicFloat::Constants::Number64::Zero) && (ClampAxis(Roll) == DeterministicFloat::Constants::Number64::Zero);
}

FORCEINLINE bool FDeterministicRotator64::Equals(const FDeterministicRotator64& R, FDeterministicNumber64 Tolerance) const
{
	return (FDeterministicFloatMath::Abs(NormalizeAxis(Pitch - R.Pitch)) <= Tolerance)
		&& (FDeterministicFloatMath::Abs(NormalizeAxis(Yaw - R.Yaw)) <= Tolerance)
		&& (FDeterministicFloatMath::Abs(NormalizeAxis(Roll - R.Roll)) <= Tolerance);
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::Add(FDeterministicNumber64 DeltaPitch, FDeterministicNumber64 DeltaYaw, FDeterministicNumber64 DeltaRoll)
{
	Yaw += DeltaYaw;
	Pitch += DeltaPitch;
	Roll += DeltaRoll;
	return *this;
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::GetInverse() const
{
	return Quaternion().Inverse().Rotator();
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::GridSnap(const FDeterministicRotator64& RotGrid) const
{
	return FDeterministicRotator64
	(
		FDeterministicFloatMath::GridSnap(Pitch, RotGrid.Pitch),
		FDeterministicFloatMath::GridSnap(Yaw, RotGrid.Yaw),
		FDeterministicFloatMath::GridSnap(Roll, RotGrid.Roll)
	);
}

FORCEINLINE FDeterministicVector64 FDeterministicRotator64::Vector() const
{
	// Remove winding and clamp to [-360, 360]
	const FDeterministicNumber64 PitchNoWinding = FDeterministicFloatMath::Fmod(Pitch, DeterministicFloat::Constants::Number64::ThreeSixty);
	const FDeterministicNumber64 YawNoWinding = FDeterministicFloatMath::Fmod(Yaw, DeterministicFloat::Constants::Number64::ThreeSixty);

	FDeterministicNumber64 CP, SP, CY, SY;
	FDeterministicFloatMath::SinCos(&SP, &CP, FDeterministicFloatMath::DegreesToRadians(PitchNoWinding));
	FDeterministicFloatMath::SinCos(&SY, &CY, FDeterministicFloatMath::DegreesToRadians(YawNoWinding));
	FDeterministicVector64 V = FDeterministicVector64(CP * CY, CP * SY, SP);

	return V;
}

FORCEINLINE FDeterministicQuat64 FDeterministicRotator64::Quaternion() const
{
	const FDeterministicNumber64 DEG_TO_RAD = DeterministicFloat::Constants::Number64::PiOverOneEighty;
	const FDeterministicNumber64 RADS_DIVIDED_BY_2 = DEG_TO_RAD / FDeterministicNumber64::Make(2.0);
	FDeterministicNumber64 SP, SY, SR;
	FDeterministicNumber64 CP, CY, CR;

	const FDeterministicNumber64 PitchNoWinding = FDeterministicFloatMath::Fmod(Pitch, DeterministicFloat::Constants::Number64::ThreeSixty);
	const FDeterministicNumber64 YawNoWinding = FDeterministicFloatMath::Fmod(Yaw, DeterministicFloat::Constants::Number64::ThreeSixty);
	const FDeterministicNumber64 RollNoWinding = FDeterministicFloatMath::Fmod(Roll, DeterministicFloat::Constants::Number64::ThreeSixty);

	FDeterministicFloatMath::SinCos(&SP, &CP, PitchNoWinding * RADS_DIVIDED_BY_2);
	FDeterministicFloatMath::SinCos(&SY, &CY, YawNoWinding * RADS_DIVIDED_BY_2);
	FDeterministicFloatMath::SinCos(&SR, &CR, RollNoWinding * RADS_DIVIDED_BY_2);

	FDeterministicQuat64 RotationQuat;
	RotationQuat.X = CR * SP * SY - SR * CP * CY;
	RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
	RotationQuat.Z = CR * CP * SY - SR * SP * CY;
	RotationQuat.W = CR * CP * CY + SR * SP * SY;

	return RotationQuat;
}

FORCEINLINE FDeterministicVector64 FDeterministicRotator64::Euler() const
{
	return FDeterministicVector64(Roll, Pitch, Yaw);
}

FORCEINLINE FDeterministicVector64 FDeterministicRotator64::RotateVector(const FDeterministicVector64& V) const
{
	return FDeterministicRotationMatrix64(*this).TransformVector(V);
}

FORCEINLINE FDeterministicVector64 FDeterministicRotator64::UnrotateVector(const FDeterministicVector64& V) const
{
	return FDeterministicRotationMatrix64(*this).GetTransposed().TransformVector(V);
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::Clamp() const
{
	return FDeterministicRotator64(ClampAxis(Pitch), ClampAxis(Yaw), ClampAxis(Roll));
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::GetNormalized() const
{
	FDeterministicRotator64 Rot = *this;
	Rot.Normalize();
	return Rot;
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::GetDenormalized() const
{
	FDeterministicRotator64 Rot = *this;
	Rot.Pitch = ClampAxis(Rot.Pitch);
	Rot.Yaw = ClampAxis(Rot.Yaw);
	Rot.Roll = ClampAxis(Rot.Roll);
	return Rot;
}

FORCEINLINE FDeterministicNumber64 FDeterministicRotator64::GetComponentForAxis(EAxis::Type Axis) const
{
	switch (Axis)
	{
	case EAxis::X:
		return Roll;
	case EAxis::Y:
		return Pitch;
	case EAxis::Z:
		return Yaw;
	default:
		return DeterministicFloat::Constants::Number64::Zero;
	}
}

FORCEINLINE void FDeterministicRotator64::SetComponentForAxis(EAxis::Type Axis, FDeterministicNumber64 Component)
{
	switch (Axis)
	{
	case EAxis::X:
		Roll = Component;
		break;
	case EAxis::Y:
		Pitch = Component;
		break;
	case EAxis::Z:
		Yaw = Component;
		break;
	}
}

FORCEINLINE void FDeterministicRotator64::Normalize()
{
	Pitch = NormalizeAxis(Pitch);
	Yaw = NormalizeAxis(Yaw);
	Roll = NormalizeAxis(Roll);
}

FORCEINLINE FDeterministicNumber64 FDeterministicRotator64::GetManhattanDistance(const FDeterministicRotator64& Rotator) const
{
	return FDeterministicFloatMath::Abs(Yaw - Rotator.Yaw) + FDeterministicFloatMath::Abs(Pitch - Rotator.Pitch) + FDeterministicFloatMath::Abs(Roll - Rotator.Roll);
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::GetEquivalentRotator() const
{
	return FDeterministicRotator64(DeterministicFloat::Constants::Number64::OneEighty - Pitch, Yaw + DeterministicFloat::Constants::Number64::OneEighty, Roll + DeterministicFloat::Constants::Number64::OneEighty);
}

FORCEINLINE void FDeterministicRotator64::SetClosestToMe(FDeterministicRotator64& MakeClosest) const
{
	FDeterministicRotator64 OtherChoice = MakeClosest.GetEquivalentRotator();
	FDeterministicNumber64 FirstDiff = GetManhattanDistance(MakeClosest);
	FDeterministicNumber64 SecondDiff = GetManhattanDistance(OtherChoice);
	if (SecondDiff < FirstDiff)
		MakeClosest = OtherChoice;
}

FORCEINLINE FString FDeterministicRotator64::ToString() const
{
	return FString::Printf(TEXT("P=%f Y=%f R=%f"), (double)Pitch, (double)Yaw, (double)Roll);
}

FORCEINLINE FString FDeterministicRotator64::ToCompactString() const
{
	if (IsNearlyZero())
	{
		return FString::Printf(TEXT("R(0)"));
	}

	FString ReturnString(TEXT("R("));
	bool bIsEmptyString = true;
	if (!FDeterministicFloatMath::IsNearlyZero(Pitch))
	{
		ReturnString += FString::Printf(TEXT("P=%.2f"), (double)Pitch);
		bIsEmptyString = false;
	}
	if (!FDeterministicFloatMath::IsNearlyZero(Yaw))
	{
		if (!bIsEmptyString)
		{
			ReturnString += FString(TEXT(", "));
		}
		ReturnString += FString::Printf(TEXT("Y=%.2f"), (double)Yaw);
		bIsEmptyString = false;
	}
	if (!FDeterministicFloatMath::IsNearlyZero(Roll))
	{
		if (!bIsEmptyString)
		{
			ReturnString += FString(TEXT(", "));
		}
		ReturnString += FString::Printf(TEXT("R=%.2f"), (double)Roll);
		bIsEmptyString = false;
	}
	ReturnString += FString(TEXT(")"));
	return ReturnString;
}

FORCEINLINE bool FDeterministicRotator64::InitFromString(const FString& InSourceString)
{
	Pitch = Yaw = Roll = 0;

	// The initialization is only successful if the X, Y, and Z values can all be parsed from the string
	double p = 0.0;
	double y = 0.0;
	double r = 0.0;
	const bool bSuccessful = FParse::Value(*InSourceString, TEXT("P="), p) && FParse::Value(*InSourceString, TEXT("Y="), y) && FParse::Value(*InSourceString, TEXT("R="), r);
	Pitch = (FDeterministicNumber64)p;
	Yaw = (FDeterministicNumber64)y;
	Roll = (FDeterministicNumber64)r;

	DiagnosticCheckNaN();
	return bSuccessful;
}

FORCEINLINE bool FDeterministicRotator64::ContainsNaN() const
{
	return false;
}

FORCEINLINE FDeterministicNumber64 FDeterministicRotator64::ClampAxis(FDeterministicNumber64 Angle)
{
	// returns Angle in the range (-360,360)
	Angle = FDeterministicFloatMath::Fmod(Angle, DeterministicFloat::Constants::Number64::ThreeSixty);

	if (Angle < DeterministicFloat::Constants::Number64::Zero)
	{
		// shift to [0,360) range
		Angle += DeterministicFloat::Constants::Number64::ThreeSixty;
	}

	return Angle;
}

FORCEINLINE FDeterministicNumber64 FDeterministicRotator64::NormalizeAxis(FDeterministicNumber64 Angle)
{
	// returns Angle in the range [0,360)
	Angle = ClampAxis(Angle);

	if (Angle > DeterministicFloat::Constants::Number64::OneEighty)
	{
		// shift to (-180,180]
		Angle -= DeterministicFloat::Constants::Number64::ThreeSixty;
	}

	return Angle;
}

FORCEINLINE uint8 FDeterministicRotator64::CompressAxisToByte(FDeterministicNumber64 Angle)
{
	// map [0->360) to [0->256) and mask off any winding
	return (uint8)((int64)FDeterministicFloatMath::RoundToInt(Angle * FDeterministicNumber64::Make(256.0) / DeterministicFloat::Constants::Number64::ThreeSixty) & 0xFF);
}

FORCEINLINE FDeterministicNumber64 FDeterministicRotator64::DecompressAxisFromByte(uint8 Angle)
{
	// map [0->256) to [0->360)
	return (FDeterministicNumber64)((double)(Angle * (360.0 / 256.0)));
}

FORCEINLINE uint16 FDeterministicRotator64::CompressAxisToShort(FDeterministicNumber64 Angle)
{
	// map [0->360) to [0->65536) and mask off any winding
	return (uint8)((int64)FDeterministicFloatMath::RoundToInt(Angle * FDeterministicNumber64::Make(65536.0) / DeterministicFloat::Constants::Number64::ThreeSixty) & 0xFFFF);
}

FORCEINLINE FDeterministicNumber64 FDeterministicRotator64::DecompressAxisFromShort(uint16 Angle)
{
	// map [0->65536) to [0->360)
	return (FDeterministicNumber64((int64)Angle) * DeterministicFloat::Constants::Number64::ThreeSixty / FDeterministicNumber64::Make(65536.0));
}
