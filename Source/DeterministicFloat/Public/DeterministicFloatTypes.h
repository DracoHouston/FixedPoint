// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "DeterministicFloatFwd.h"

#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatVector2D64.h"
#include "DeterministicFloatVector4D64.h"
#include "DeterministicFloatPlane64.h"
#include "DeterministicFloatMatrix64.h"
#include "DeterministicFloatQuat64.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatRotationTranslationMatrix64.h"
#include "DeterministicFloatRotationMatrix64.h"
#include "DeterministicFloatQuatRotationTranslationMatrix64.h"
#include "DeterministicFloatTransform64.h"

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

#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatPlane64Funcs.h"
#include "DeterministicFloatQuat64Funcs.h"
#include "DeterministicFloatRotator64Funcs.h"
#include "DeterministicFloatMatrix64Funcs.h"
#include "DeterministicFloatQuatRotationTranslationMatrix64Funcs.h"
#include "DeterministicFloatRotationTranslationMatrix64Funcs.h"
#include "DeterministicFloatRotationMatrix64Funcs.h"