// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatMath.h"

FORCEINLINE FDeterministicNumber32 FDeterministicFloatMath::DegreesToRadians(const FDeterministicNumber32& inValue)
{
	return inValue * DeterministicFloat::Constants::Number32::PiOverOneEighty;
}

FORCEINLINE FDeterministicNumber32 FDeterministicFloatMath::RadiansToDegrees(const FDeterministicNumber32& inValue)
{
	return inValue * DeterministicFloat::Constants::Number32::OneEightyOverPi;
}

FORCEINLINE FDeterministicNumber64 FDeterministicFloatMath::DegreesToRadians(const FDeterministicNumber64& inValue)
{
	return inValue * DeterministicFloat::Constants::Number64::PiOverOneEighty;
}

FORCEINLINE FDeterministicNumber64 FDeterministicFloatMath::RadiansToDegrees(const FDeterministicNumber64& inValue)
{
	return inValue * DeterministicFloat::Constants::Number64::OneEightyOverPi;
}

FDeterministicNumber64 FDeterministicFloatMath::FloorToNumber64(const FDeterministicNumber64& inValue)
{
	return FDeterministicNumber64::Make(FMath::FloorToDouble(inValue.Value));
}

FDeterministicNumber32 FDeterministicFloatMath::FloorToNumber32(const FDeterministicNumber32& inValue)
{
	return FDeterministicNumber32::Make(FMath::FloorToFloat(inValue.Value));
}

FDeterministicNumber64 FDeterministicFloatMath::Floor(const FDeterministicNumber64& inValue)
{
	return FloorToNumber64(inValue);
}

FDeterministicNumber32 FDeterministicFloatMath::Floor(const FDeterministicNumber32& inValue)
{
	return FloorToNumber32(inValue);
}

FORCEINLINE int32 FDeterministicFloatMath::FloorToInt32(FDeterministicNumber32 F)
{
	return (int32)FloorToNumber32(F);
}

FORCEINLINE int32 FDeterministicFloatMath::FloorToInt32(FDeterministicNumber64 F)
{
	return (int32)FloorToNumber64(F);
}

FORCEINLINE int64 FDeterministicFloatMath::FloorToInt64(FDeterministicNumber64 F)
{
	return (int64)FloorToNumber64(F);
}

FORCEINLINE int32 FDeterministicFloatMath::FloorToInt(FDeterministicNumber32 F) 
{
	return FloorToInt32(F); 
}

FORCEINLINE int64 FDeterministicFloatMath::FloorToInt(FDeterministicNumber64 F) 
{ 
	return FloorToInt64(F); 
}

FORCEINLINE float FDeterministicFloatMath::FloorToFloat(FDeterministicNumber32 F)
{
	return (float)FloorToNumber32(F);
}

FORCEINLINE double FDeterministicFloatMath::FloorToDouble(FDeterministicNumber64 F)
{
	return (double)FloorToNumber64(F);
}

FORCEINLINE float FDeterministicFloatMath::FloorToFloat(FDeterministicNumber64 F)
{
	return (float)FloorToDouble(F);
}

FORCEINLINE int32 FDeterministicFloatMath::RoundToNumber32(FDeterministicNumber32 F)
{
	return FDeterministicNumber32::Make(FMath::RoundToFloat(F.Value));
}

FORCEINLINE int32 FDeterministicFloatMath::RoundToNumber64(FDeterministicNumber64 F)
{
	return FDeterministicNumber64::Make(FMath::RoundToDouble(F.Value));
}

FORCEINLINE int32 FDeterministicFloatMath::RoundToFloat(FDeterministicNumber32 F)
{
	return (float)RoundToNumber32(F);
}
FORCEINLINE int32 FDeterministicFloatMath::RoundToDouble(FDeterministicNumber64 F)
{
	return (double)RoundToNumber64(F);
}
FORCEINLINE int32 FDeterministicFloatMath::RoundToFloat(FDeterministicNumber64 F)
{
	return (float)RoundToDouble(F);
}

FORCEINLINE int32 FDeterministicFloatMath::RoundToInt32(FDeterministicNumber32 F)
{
	return (float)RoundToNumber32(F);
}

FORCEINLINE int32 FDeterministicFloatMath::RoundToInt32(FDeterministicNumber64 F)
{
	return (int32)RoundToNumber64(F);
}

FORCEINLINE int64 FDeterministicFloatMath::RoundToInt64(FDeterministicNumber64 F)
{
	return (int64)RoundToNumber64(F);
}

FORCEINLINE int32 FDeterministicFloatMath::RoundToInt(FDeterministicNumber32 F) 
{ 
	return RoundToInt32(F); 
}

FORCEINLINE int64 FDeterministicFloatMath::RoundToInt(FDeterministicNumber64 F)
{ 
	return RoundToInt64(F); 
}

FORCEINLINE FDeterministicNumber32 FDeterministicFloatMath::CeilToNumber32(const FDeterministicNumber32& inValue)
{
	return FDeterministicNumber32::Make(FMath::CeilToFloat(inValue.Value));
}

FORCEINLINE FDeterministicNumber64 FDeterministicFloatMath::CeilToNumber64(const FDeterministicNumber64& inValue)
{
	return FDeterministicNumber64::Make(FMath::CeilToDouble(inValue.Value));
}

FORCEINLINE int32 FDeterministicFloatMath::CeilToInt(const FDeterministicNumber32& inValue)
{
	return (int32)CeilToNumber32(inValue);
}

FORCEINLINE int64 FDeterministicFloatMath::CeilToInt(const FDeterministicNumber64& inValue)
{
	return (int64)CeilToNumber64(inValue);
}

FORCEINLINE float FDeterministicFloatMath::CeilToFloat(const FDeterministicNumber32& inValue)
{
	return (float)CeilToNumber32(inValue);
}

FORCEINLINE float FDeterministicFloatMath::CeilToFloat(const FDeterministicNumber64& inValue)
{
	return (float)CeilToNumber64(inValue);
}

FORCEINLINE double FDeterministicFloatMath::CeilToDouble(const FDeterministicNumber32& inValue)
{
	return (double)CeilToNumber32(inValue);
}

FORCEINLINE double FDeterministicFloatMath::CeilToDouble(const FDeterministicNumber64& inValue)
{
	return (double)CeilToNumber64(inValue);
}

FORCEINLINE FDeterministicNumber32 FDeterministicFloatMath::TruncToNumber32(const FDeterministicNumber32& inValue)
{
	return FDeterministicNumber32::Make(FMath::TruncToFloat(inValue.Value));
}

FORCEINLINE FDeterministicNumber64 FDeterministicFloatMath::TruncToNumber64(const FDeterministicNumber64& inValue)
{
	return FDeterministicNumber32::Make(FMath::TruncToDouble(inValue.Value));
}

FORCEINLINE int32 FDeterministicFloatMath::TruncToInt(const FDeterministicNumber32& inValue)
{
	return (int32)TruncToNumber32(inValue);
}

FORCEINLINE int64 FDeterministicFloatMath::TruncToInt(const FDeterministicNumber64& inValue)
{
	return (int64)TruncToNumber64(inValue);
}

FORCEINLINE float FDeterministicFloatMath::TruncToFloat(const FDeterministicNumber32& inValue)
{
	return (float)TruncToNumber32(inValue);
}

FORCEINLINE float FDeterministicFloatMath::TruncToFloat(const FDeterministicNumber64& inValue)
{
	return (float)TruncToNumber64(inValue);
}

FORCEINLINE double FDeterministicFloatMath::TruncToDouble(const FDeterministicNumber32& inValue)
{
	return (double)TruncToNumber32(inValue);
}

FORCEINLINE double FDeterministicFloatMath::TruncToDouble(const FDeterministicNumber64& inValue)
{
	return (double)TruncToNumber64(inValue);
}

FORCEINLINE bool FDeterministicFloatMath::IsEqual(const FDeterministicNumber32& A, const FDeterministicNumber32& B, const FDeterministicNumber32& inTolerance)
{
	return FDeterministicFloatMath::Abs(A - B) <= inTolerance;
}

FORCEINLINE bool FDeterministicFloatMath::IsEqual(const FDeterministicNumber64& A, const FDeterministicNumber64& B, const FDeterministicNumber64& inTolerance)
{
	return FDeterministicFloatMath::Abs(A - B) <= inTolerance;
}

UE_NODISCARD FORCEINLINE bool FDeterministicFloatMath::IsNearlyEqual(FDeterministicNumber32 A, FDeterministicNumber32 B, FDeterministicNumber32 ErrorTolerance)
{
	return Abs(A - B) <= ErrorTolerance;
}

UE_NODISCARD FORCEINLINE bool FDeterministicFloatMath::IsNearlyEqual(FDeterministicNumber64 A, FDeterministicNumber64 B, FDeterministicNumber64 ErrorTolerance)
{
	return Abs(A - B) <= ErrorTolerance;
}

UE_NODISCARD FORCEINLINE bool FDeterministicFloatMath::IsNearlyZero(FDeterministicNumber32 Value, FDeterministicNumber32 ErrorTolerance)
{
	return Abs(Value) <= ErrorTolerance;
}

UE_NODISCARD FORCEINLINE bool FDeterministicFloatMath::IsNearlyZero(FDeterministicNumber64 Value, FDeterministicNumber64 ErrorTolerance)
{
	return Abs(Value) <= ErrorTolerance;
}

FDeterministicNumber64 FDeterministicFloatMath::Acos(FDeterministicNumber64 x)
{
	//copied from nvidias cg language reference implementation, full of magic numbers, i'm scared too.
	FDeterministicNumber64 negate = FDeterministicNumber64((int64)(x < DeterministicFloat::Constants::Number64::Zero));
	x = Abs(x);
	FDeterministicNumber64 ret = DeterministicFloat::Constants::Number64::InvTrigMagicOne;
	ret = ret * x;
	ret = ret + DeterministicFloat::Constants::Number64::InvTrigMagicTwo;
	ret = ret * x;
	ret = ret - DeterministicFloat::Constants::Number64::InvTrigMagicThree;
	ret = ret * x;
	ret = ret + DeterministicFloat::Constants::Number64::HalfPi;
	ret = ret * Sqrt(DeterministicFloat::Constants::Number64::One - x);
	ret = ret - FDeterministicNumber64::Make(2.0) * negate * ret;
	return negate * DeterministicFloat::Constants::Number64::Pi + ret;
}

FDeterministicNumber64 FDeterministicFloatMath::Asin(FDeterministicNumber64 x) {
	FDeterministicNumber64 negate = FDeterministicNumber64((int64)(x < DeterministicFloat::Constants::Number64::Zero));
	x = Abs(x);
	FDeterministicNumber64 ret = DeterministicFloat::Constants::Number64::InvTrigMagicOne;
	ret *= x;
	ret += DeterministicFloat::Constants::Number64::InvTrigMagicTwo;
	ret *= x;
	ret -= DeterministicFloat::Constants::Number64::InvTrigMagicThree;
	ret *= x;
	ret += DeterministicFloat::Constants::Number64::HalfPi;
	ret = DeterministicFloat::Constants::Number64::Pi * DeterministicFloat::Constants::Number64::Half - Sqrt(DeterministicFloat::Constants::Number64::One - x) * ret;
	return ret - FDeterministicNumber64::Make(2.0) * negate * ret;
}

FDeterministicNumber64 FDeterministicFloatMath::Atan(FDeterministicNumber64 X)
{
	return Atan2(X, DeterministicFloat::Constants::Number64::One);
}

FDeterministicNumber64 FDeterministicFloatMath::Atan2(FDeterministicNumber64 Y, FDeterministicNumber64 X)
{
	const FDeterministicNumber64 absX = Abs(X);
	const FDeterministicNumber64 absY = Abs(Y);
	const bool yAbsBigger = (absY > absX);
	FDeterministicNumber64 t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
	FDeterministicNumber64 t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

	if (t0 == DeterministicFloat::Constants::Number64::Zero)
		return DeterministicFloat::Constants::Number64::Zero;

	FDeterministicNumber64 t3 = t1 / t0;
	FDeterministicNumber64 t4 = t3 * t3;

	const FDeterministicNumber64 c[7] = {
		DeterministicFloat::Constants::Number64::AtanMagicOne,
		DeterministicFloat::Constants::Number64::AtanMagicTwo,
		DeterministicFloat::Constants::Number64::AtanMagicThree,
		DeterministicFloat::Constants::Number64::AtanMagicFour,
		DeterministicFloat::Constants::Number64::AtanMagicFive,
		DeterministicFloat::Constants::Number64::AtanMagicSix,
		DeterministicFloat::Constants::Number64::One
	};

	t0 = c[0];
	t0 = t0 * t4 + c[1];
	t0 = t0 * t4 + c[2];
	t0 = t0 * t4 + c[3];
	t0 = t0 * t4 + c[4];
	t0 = t0 * t4 + c[5];
	t0 = t0 * t4 + c[6];
	t3 = t0 * t3;

	t3 = yAbsBigger ? DeterministicFloat::Constants::Number64::HalfPi - t3 : t3;
	t3 = (X < DeterministicFloat::Constants::Number64::Zero) ? DeterministicFloat::Constants::Number64::Pi - t3 : t3;
	t3 = (Y < DeterministicFloat::Constants::Number64::Zero) ? -t3 : t3;

	return t3;
}

FDeterministicNumber32 FDeterministicFloatMath::Acos(FDeterministicNumber32 x)
{
	//copied from nvidias cg language reference implementation, full of magic numbers, i'm scared too.
	FDeterministicNumber32 negate = FDeterministicNumber32((int32)(x < DeterministicFloat::Constants::Number32::Zero));
	x = Abs(x);
	FDeterministicNumber32 ret = DeterministicFloat::Constants::Number32::InvTrigMagicOne;
	ret = ret * x;
	ret = ret + DeterministicFloat::Constants::Number32::InvTrigMagicTwo;
	ret = ret * x;
	ret = ret - DeterministicFloat::Constants::Number32::InvTrigMagicThree;
	ret = ret * x;
	ret = ret + DeterministicFloat::Constants::Number32::HalfPi;
	ret = ret * Sqrt(DeterministicFloat::Constants::Number32::One - x);
	ret = ret - FDeterministicNumber32::Make(2.0) * negate * ret;
	return negate * DeterministicFloat::Constants::Number32::Pi + ret;
}

FDeterministicNumber32 FDeterministicFloatMath::Asin(FDeterministicNumber32 x) {
	FDeterministicNumber32 negate = FDeterministicNumber32((int32)(x < DeterministicFloat::Constants::Number32::Zero));
	x = Abs(x);
	FDeterministicNumber32 ret = DeterministicFloat::Constants::Number32::InvTrigMagicOne;
	ret *= x;
	ret += DeterministicFloat::Constants::Number32::InvTrigMagicTwo;
	ret *= x;
	ret -= DeterministicFloat::Constants::Number32::InvTrigMagicThree;
	ret *= x;
	ret += DeterministicFloat::Constants::Number32::HalfPi;
	ret = DeterministicFloat::Constants::Number32::Pi * DeterministicFloat::Constants::Number32::Half - Sqrt(DeterministicFloat::Constants::Number32::One - x) * ret;
	return ret - FDeterministicNumber32::Make(2.0) * negate * ret;
}

FDeterministicNumber32 FDeterministicFloatMath::Atan(FDeterministicNumber32 X)
{
	return Atan2(X, DeterministicFloat::Constants::Number32::One);
}

FDeterministicNumber32 FDeterministicFloatMath::Atan2(FDeterministicNumber32 Y, FDeterministicNumber32 X)
{
	const FDeterministicNumber32 absX = Abs(X);
	const FDeterministicNumber32 absY = Abs(Y);
	const bool yAbsBigger = (absY > absX);
	FDeterministicNumber32 t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
	FDeterministicNumber32 t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

	if (t0 == DeterministicFloat::Constants::Number32::Zero)
		return DeterministicFloat::Constants::Number32::Zero;

	FDeterministicNumber32 t3 = t1 / t0;
	FDeterministicNumber32 t4 = t3 * t3;

	const FDeterministicNumber32 c[7] = {
		DeterministicFloat::Constants::Number32::AtanMagicOne,
		DeterministicFloat::Constants::Number32::AtanMagicTwo,
		DeterministicFloat::Constants::Number32::AtanMagicThree,
		DeterministicFloat::Constants::Number32::AtanMagicFour,
		DeterministicFloat::Constants::Number32::AtanMagicFive,
		DeterministicFloat::Constants::Number32::AtanMagicSix,
		DeterministicFloat::Constants::Number32::One
	};

	t0 = c[0];
	t0 = t0 * t4 + c[1];
	t0 = t0 * t4 + c[2];
	t0 = t0 * t4 + c[3];
	t0 = t0 * t4 + c[4];
	t0 = t0 * t4 + c[5];
	t0 = t0 * t4 + c[6];
	t3 = t0 * t3;

	t3 = yAbsBigger ? DeterministicFloat::Constants::Number32::HalfPi - t3 : t3;
	t3 = (X < DeterministicFloat::Constants::Number32::Zero) ? DeterministicFloat::Constants::Number32::Pi - t3 : t3;
	t3 = (Y < DeterministicFloat::Constants::Number32::Zero) ? -t3 : t3;

	return t3;
}

constexpr FORCEINLINE FDeterministicNumber64 FDeterministicFloatMath::FloatSelect(FDeterministicNumber64 Comparand, FDeterministicNumber64 ValueGEZero, FDeterministicNumber64 ValueLTZero)
{
	return Comparand >= DeterministicFloat::Constants::Number64::Zero ? ValueGEZero : ValueLTZero;
}
constexpr FORCEINLINE FDeterministicNumber32 FDeterministicFloatMath::FloatSelect(FDeterministicNumber32 Comparand, FDeterministicNumber32 ValueGEZero, FDeterministicNumber32 ValueLTZero)
{
	return Comparand >= DeterministicFloat::Constants::Number32::Zero ? ValueGEZero : ValueLTZero;
}

UE_NODISCARD constexpr FORCEINLINE FDeterministicNumber64 FDeterministicFloatMath::GridSnap(FDeterministicNumber64 Location, FDeterministicNumber64 Grid)
{
	return (Grid == DeterministicFloat::Constants::Number64::Zero) ? Location : (Floor((Location + (Grid / FDeterministicNumber64::Make(2.0))) / Grid) * Grid);
}

UE_NODISCARD constexpr FORCEINLINE FDeterministicNumber32 FDeterministicFloatMath::GridSnap(FDeterministicNumber32 Location, FDeterministicNumber32 Grid)
{
	return (Grid == DeterministicFloat::Constants::Number32::Zero) ? Location : (Floor((Location + (Grid / FDeterministicNumber32::Make(2.0))) / Grid) * Grid);
}

UE_NODISCARD constexpr FDeterministicNumber32 FDeterministicFloatMath::UnwindDegrees(FDeterministicNumber32 A)
{
	while (A > DeterministicFloat::Constants::Number32::OneEighty)
	{
		A -= DeterministicFloat::Constants::Number32::ThreeSixty;
	}

	while (A < -DeterministicFloat::Constants::Number32::OneEighty)
	{
		A += DeterministicFloat::Constants::Number32::ThreeSixty;
	}

	return A;
}

UE_NODISCARD constexpr FDeterministicNumber64 FDeterministicFloatMath::UnwindDegrees(FDeterministicNumber64 A)
{
	while (A > DeterministicFloat::Constants::Number64::OneEighty)
	{
		A -= DeterministicFloat::Constants::Number64::ThreeSixty;
	}

	while (A < -DeterministicFloat::Constants::Number64::OneEighty)
	{
		A += DeterministicFloat::Constants::Number64::ThreeSixty;
	}

	return A;
}

UE_NODISCARD constexpr FDeterministicNumber64 FDeterministicFloatMath::UnwindRadians(FDeterministicNumber64 A)
{
	while (A > DeterministicFloat::Constants::Number64::Pi)
	{
		A -= DeterministicFloat::Constants::Number64::TwoPi;
	}

	while (A < -DeterministicFloat::Constants::Number64::Pi)
	{
		A += DeterministicFloat::Constants::Number64::TwoPi;
	}

	return A;
}

UE_NODISCARD constexpr FDeterministicNumber32 FDeterministicFloatMath::UnwindRadians(FDeterministicNumber32 A)
{
	while (A > DeterministicFloat::Constants::Number32::Pi)
	{
		A -= DeterministicFloat::Constants::Number32::TwoPi;
	}

	while (A < -DeterministicFloat::Constants::Number32::Pi)
	{
		A += DeterministicFloat::Constants::Number32::TwoPi;
	}

	return A;
}

FORCEINLINE int32 FDeterministicFloatMath::GetQuadrantRadians(const FDeterministicNumber64& inValue)
{
	FDeterministicNumber64 val = UnwindRadians(inValue);

	val = val < DeterministicFloat::Constants::Number64::Zero ? val + DeterministicFloat::Constants::Number64::TwoPi : val;

	if ((inValue > DeterministicFloat::Constants::Number64::Zero) && (val == DeterministicFloat::Constants::Number64::HalfPi))
	{
		return 0;
	}
	else if ((inValue > DeterministicFloat::Constants::Number64::Zero) && (val == DeterministicFloat::Constants::Number64::Pi))
	{
		return 1;
	}
		
	val /= DeterministicFloat::Constants::Number64::HalfPi;
	return (int32)val;
}

FORCEINLINE int32 FDeterministicFloatMath::GetQuadrantRadians(const FDeterministicNumber32& inValue)
{
	FDeterministicNumber32 val = UnwindRadians(inValue);

	val = val < DeterministicFloat::Constants::Number32::Zero ? val + DeterministicFloat::Constants::Number32::TwoPi : val;

	if ((inValue > DeterministicFloat::Constants::Number32::Zero) && (val == DeterministicFloat::Constants::Number32::HalfPi))
	{
		return 0;
	}
	else if ((inValue > DeterministicFloat::Constants::Number32::Zero) && (val == DeterministicFloat::Constants::Number32::Pi))
	{
		return 1;
	}

	val /= DeterministicFloat::Constants::Number32::HalfPi;
	return (int32)val;
}

FORCEINLINE bool FDeterministicFloatMath::IsNaN(FDeterministicNumber32 A)
{ 
	return false; 
}

FORCEINLINE bool FDeterministicFloatMath::IsNaN(FDeterministicNumber64 A)
{ 
	return false; 
}

FORCEINLINE bool FDeterministicFloatMath::IsFinite(FDeterministicNumber32 A)
{ 
	return false; 
}

FORCEINLINE bool FDeterministicFloatMath::IsFinite(FDeterministicNumber64 A)
{ 
	return false; 
}

FORCEINLINE_DEBUGGABLE FDeterministicRotator64 FDeterministicFloatMath::LerpRange(const FDeterministicRotator64& A, const FDeterministicRotator64& B, FDeterministicNumber64 Alpha)
{
	// Similar to Lerp, but does not take the shortest path. Allows interpolation over more than 180 degrees.
	return (A * (DeterministicFloat::Constants::Number64::One - Alpha) + B * Alpha).GetNormalized();
}

FORCEINLINE_DEBUGGABLE FDeterministicNumber64 FDeterministicFloatMath::ClampAngle(FDeterministicNumber64 AngleDegrees, FDeterministicNumber64 MinAngleDegrees, FDeterministicNumber64 MaxAngleDegrees)
{
	const FDeterministicNumber64 MaxDelta = FDeterministicRotator64::ClampAxis(MaxAngleDegrees - MinAngleDegrees) * DeterministicFloat::Constants::Number64::Half;			// 0..180
	const FDeterministicNumber64 RangeCenter = FDeterministicRotator64::ClampAxis(MinAngleDegrees + MaxDelta);						// 0..360
	const FDeterministicNumber64 DeltaFromCenter = FDeterministicRotator64::NormalizeAxis(AngleDegrees - RangeCenter);				// -180..180

	// maybe clamp to nearest edge
	if (DeltaFromCenter > MaxDelta)
	{
		return FDeterministicRotator64::NormalizeAxis(RangeCenter + MaxDelta);
	}
	else if (DeltaFromCenter < -MaxDelta)
	{
		return FDeterministicRotator64::NormalizeAxis(RangeCenter - MaxDelta);
	}

	// already in range, just return it
	return FDeterministicRotator64::NormalizeAxis(AngleDegrees);
}

FORCEINLINE_DEBUGGABLE FDeterministicNumber32 FDeterministicFloatMath::ClampAngle(FDeterministicNumber32 AngleDegrees, FDeterministicNumber32 MinAngleDegrees, FDeterministicNumber32 MaxAngleDegrees)
{
	const FDeterministicNumber32 MaxDelta = FDeterministicRotator64::ClampAxis(MaxAngleDegrees - MinAngleDegrees) * DeterministicFloat::Constants::Number32::Half;			// 0..180
	const FDeterministicNumber32 RangeCenter = FDeterministicRotator64::ClampAxis(MinAngleDegrees + MaxDelta);						// 0..360
	const FDeterministicNumber32 DeltaFromCenter = FDeterministicRotator64::NormalizeAxis(AngleDegrees - RangeCenter);				// -180..180

	// maybe clamp to nearest edge
	if (DeltaFromCenter > MaxDelta)
	{
		return FDeterministicRotator64::NormalizeAxis(RangeCenter + MaxDelta);
	}
	else if (DeltaFromCenter < -MaxDelta)
	{
		return FDeterministicRotator64::NormalizeAxis(RangeCenter - MaxDelta);
	}

	// already in range, just return it
	return FDeterministicRotator64::NormalizeAxis(AngleDegrees);
}

inline FDeterministicVector64 FDeterministicFloatMath::LinePlaneIntersection
(
	const FDeterministicVector64& Point1,
	const FDeterministicVector64& Point2,
	const FDeterministicVector64& PlaneOrigin,
	const FDeterministicVector64& PlaneNormal
)
{
	return
		Point1
		+ (Point2 - Point1)
		* (((PlaneOrigin - Point1) | PlaneNormal) / ((Point2 - Point1) | PlaneNormal));
}

inline bool FDeterministicFloatMath::LineSphereIntersection(const FDeterministicVector64& Start, const FDeterministicVector64& Dir, FDeterministicNumber64 Length, const FDeterministicVector64& Origin, FDeterministicNumber64 Radius)
{
	const FDeterministicVector64	EO = Start - Origin;
	const FDeterministicNumber64		v = (Dir | (Origin - Start));
	const FDeterministicNumber64		disc = Radius * Radius - ((EO | EO) - v * v);

	if (disc >= DeterministicFloat::Constants::Number64::Zero)
	{
		const FDeterministicNumber64	Time = (v - Sqrt(disc)) / Length;

		if (Time >= DeterministicFloat::Constants::Number64::Zero && Time <= DeterministicFloat::Constants::Number64::One)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

inline FDeterministicVector64 FDeterministicFloatMath::VRand()
{
	FDeterministicVector64 Result;
	FDeterministicNumber64 L;

	do
	{
		// Check random vectors in the unit sphere so result is statistically uniform.
		Result.X = FRand() * 2.f - 1.f;
		Result.Y = FRand() * 2.f - 1.f;
		Result.Z = FRand() * 2.f - 1.f;
		L = Result.SizeSquared();
	} while (L > DeterministicFloat::Constants::Number64::One || L < DeterministicFloat::Constants::Number64::KindaSmallNumber);

	return Result * (DeterministicFloat::Constants::Number64::One / Sqrt(L));
}
