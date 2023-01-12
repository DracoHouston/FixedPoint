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

FORCEINLINE FDeterministicMatrix64::FDeterministicMatrix64(const FDeterministicPlane64& InX, const FDeterministicPlane64& InY, const FDeterministicPlane64& InZ, const FDeterministicPlane64& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = InW.W;
}

FORCEINLINE  FDeterministicMatrix64::FDeterministicMatrix64(const FDeterministicVector64& InX, const FDeterministicVector64& InY, const FDeterministicVector64& InZ, const FDeterministicVector64& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = DeterministicFloat::Constants::Number64::Zero;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = DeterministicFloat::Constants::Number64::Zero;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = DeterministicFloat::Constants::Number64::Zero;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = DeterministicFloat::Constants::Number64::One;
}

inline FDeterministicNumber64 FDeterministicMatrix64::GetMinimumAxisScale() const
{
	const FDeterministicNumber64 MaxRowScaleSquared = FDeterministicFloatMath::Min(
		GetScaledAxis(EAxis::X).SizeSquared(),
		FDeterministicFloatMath::Min(
			GetScaledAxis(EAxis::Y).SizeSquared(),
			GetScaledAxis(EAxis::Z).SizeSquared()
		)
	);
	return FDeterministicFloatMath::Sqrt(MaxRowScaleSquared);
}

inline FDeterministicNumber64 FDeterministicMatrix64::GetMaximumAxisScale() const
{
	const FDeterministicNumber64 MaxRowScaleSquared = FDeterministicFloatMath::Max(
		GetScaledAxis(EAxis::X).SizeSquared(),
		FDeterministicFloatMath::Max(
			GetScaledAxis(EAxis::Y).SizeSquared(),
			GetScaledAxis(EAxis::Z).SizeSquared()
		)
	);
	return FDeterministicFloatMath::Sqrt(MaxRowScaleSquared);
}

inline FDeterministicVector64 FDeterministicMatrix64::GetScaledAxis(EAxis::Type InAxis) const
{
	switch (InAxis)
	{
	case EAxis::X:
		return FDeterministicVector64(M[0][0], M[0][1], M[0][2]);

	case EAxis::Y:
		return FDeterministicVector64(M[1][0], M[1][1], M[1][2]);

	case EAxis::Z:
		return FDeterministicVector64(M[2][0], M[2][1], M[2][2]);

	default:
		ensure(0);
		return FDeterministicVector64::ZeroVector;
	}
}

inline void FDeterministicMatrix64::GetScaledAxes(FDeterministicVector64& X, FDeterministicVector64& Y, FDeterministicVector64& Z) const
{
	X.X = M[0][0]; X.Y = M[0][1]; X.Z = M[0][2];
	Y.X = M[1][0]; Y.Y = M[1][1]; Y.Z = M[1][2];
	Z.X = M[2][0]; Z.Y = M[2][1]; Z.Z = M[2][2];
}

inline FDeterministicVector64 FDeterministicMatrix64::GetUnitAxis(EAxis::Type InAxis) const
{
	return GetScaledAxis(InAxis).GetSafeNormal();
}

inline void FDeterministicMatrix64::GetUnitAxes(FDeterministicVector64& X, FDeterministicVector64& Y, FDeterministicVector64& Z) const
{
	GetScaledAxes(X, Y, Z);
	X.Normalize();
	Y.Normalize();
	Z.Normalize();
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::InverseFast() const
{
	// If we're in non final release, then make sure we're not creating NaNs
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber))
	{
		ErrorEnsure(TEXT("FDeterministicMatrix64::InverseFast(), trying to invert a NIL matrix, garbage in, garbage out! Use Inverse() instead."));
	}
	else
	{
		const FDeterministicNumber64	Det = Determinant();

		if (Det == DeterministicFloat::Constants::Number64::Zero)
		{
			ErrorEnsure(TEXT("FDeterministicMatrix64::InverseFast(), trying to invert a non-invertible matrix, garbage in, garbage out! Use Inverse() instead."));
		}
	}
#endif
	FDeterministicMatrix64 Result;
	Internal_MatrixInverse(Result, *this);
	return Result;
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::Inverse() const
{
	FDeterministicMatrix64 Result;

	//Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber))
	{
		// just set to zero - avoids unsafe inverse of zero and duplicates what QNANs were resulting in before (scaling away all children)
		Result = Identity;
	}
	else
	{
		const FDeterministicNumber64	Det = Determinant();

		if (Det == DeterministicFloat::Constants::Number64::Zero)
		{
			Result = Identity;
		}
		else
		{
			Internal_MatrixInverse(Result, *this);
		}
	}

	return Result;
}

inline FDeterministicVector64 FDeterministicMatrix64::ExtractScaling(FDeterministicNumber64 Tolerance/*=UE_SMALL_NUMBER*/)
{
	FDeterministicVector64 Scale3D(0, 0, 0);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	const FDeterministicNumber64 SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
	const FDeterministicNumber64 SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
	const FDeterministicNumber64 SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);

	if (SquareSum0 > Tolerance)
	{
		FDeterministicNumber64 Scale0 = FDeterministicFloatMath::Sqrt(SquareSum0);
		Scale3D[0] = Scale0;
		FDeterministicNumber64 InvScale0 = DeterministicFloat::Constants::Number64::One / Scale0;
		M[0][0] *= InvScale0;
		M[0][1] *= InvScale0;
		M[0][2] *= InvScale0;
	}
	else
	{
		Scale3D[0] = DeterministicFloat::Constants::Number64::Zero;
	}

	if (SquareSum1 > Tolerance)
	{
		FDeterministicNumber64 Scale1 = FDeterministicFloatMath::Sqrt(SquareSum1);
		Scale3D[1] = Scale1;
		FDeterministicNumber64 InvScale1 = DeterministicFloat::Constants::Number64::One / Scale1;
		M[1][0] *= InvScale1;
		M[1][1] *= InvScale1;
		M[1][2] *= InvScale1;
	}
	else
	{
		Scale3D[1] = DeterministicFloat::Constants::Number64::Zero;
	}

	if (SquareSum2 > Tolerance)
	{
		FDeterministicNumber64 Scale2 = FDeterministicFloatMath::Sqrt(SquareSum2);
		Scale3D[2] = Scale2;
		FDeterministicNumber64 InvScale2 = DeterministicFloat::Constants::Number64::One / Scale2;
		M[2][0] *= InvScale2;
		M[2][1] *= InvScale2;
		M[2][2] *= InvScale2;
	}
	else
	{
		Scale3D[2] = DeterministicFloat::Constants::Number64::Zero;
	}

	return Scale3D;
}

inline FDeterministicVector64 FDeterministicMatrix64::GetScaleVector(FDeterministicNumber64 Tolerance) const
{
	FDeterministicVector64 Scale3D(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::One);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	for (int32 i = 0; i < 3; i++)
	{
		const FDeterministicNumber64 SquareSum = (M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]);
		if (SquareSum > Tolerance)
		{
			Scale3D[i] = FDeterministicFloatMath::Sqrt(SquareSum);
		}
		else
		{
			Scale3D[i] = DeterministicFloat::Constants::Number64::Zero;
		}
	}

	return Scale3D;
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::ConcatTranslation(const FDeterministicVector64& Translation) const
{
	FDeterministicMatrix64 Result;

	FDeterministicNumber64* RESTRICT Dest = &Result.M[0][0];
	const FDeterministicNumber64* RESTRICT Src = &M[0][0];
	const FDeterministicNumber64* RESTRICT Trans = &Translation.X;

	Dest[0] = Src[0];
	Dest[1] = Src[1];
	Dest[2] = Src[2];
	Dest[3] = Src[3];
	Dest[4] = Src[4];
	Dest[5] = Src[5];
	Dest[6] = Src[6];
	Dest[7] = Src[7];
	Dest[8] = Src[8];
	Dest[9] = Src[9];
	Dest[10] = Src[10];
	Dest[11] = Src[11];
	Dest[12] = Src[12] + Trans[0];
	Dest[13] = Src[13] + Trans[1];
	Dest[14] = Src[14] + Trans[2];
	Dest[15] = Src[15];
	
	return Result;
}

inline void FDeterministicMatrix64::ScaleTranslation(const FDeterministicVector64& InScale3D)
{
	M[3][0] *= InScale3D.X;
	M[3][1] *= InScale3D.Y;
	M[3][2] *= InScale3D.Z;
}

inline FDeterministicMatrix64 FDeterministicMatrix64::ApplyScale(FDeterministicNumber64 Scale) const
{
	FDeterministicMatrix64 ScaleMatrix(
		FDeterministicPlane64(Scale, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero),
		FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, Scale, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero),
		FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, Scale, DeterministicFloat::Constants::Number64::Zero),
		FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One)
	);
	return ScaleMatrix * *this;
}

inline FDeterministicVector64 FDeterministicMatrix64::GetOrigin() const
{
	return FDeterministicVector64(M[3][0], M[3][1], M[3][2]);
}

inline FDeterministicPlane64 FDeterministicPlane64::TransformBy(const FDeterministicMatrix64& M) const
{
	const FDeterministicMatrix64 tmpTA = M.TransposeAdjoint();
	const FDeterministicNumber64 DetM = M.Determinant();
	return this->TransformByUsingAdjointT(M, DetM, tmpTA);
}

FORCEINLINE FDeterministicVector4D64 FDeterministicMatrix64::TransformFVector4(const FDeterministicVector4D64& P) const
{
	FDeterministicVector4D64 VOurX = FDeterministicVector4D64(M[0][0], M[0][1], M[0][2], M[0][3]);
	FDeterministicVector4D64 VOurY = FDeterministicVector4D64(M[1][0], M[1][1], M[1][2], M[1][3]);
	FDeterministicVector4D64 VOurZ = FDeterministicVector4D64(M[2][0], M[2][1], M[2][2], M[2][3]);
	FDeterministicVector4D64 VOurW = FDeterministicVector4D64(M[3][0], M[3][1], M[3][2], M[3][3]);

	FDeterministicVector4D64 VTempX = FDeterministicVector4D64(P.X);
	FDeterministicVector4D64 VTempY = FDeterministicVector4D64(P.Y);
	FDeterministicVector4D64 VTempZ = FDeterministicVector4D64(P.Z);
	FDeterministicVector4D64 VTempW = FDeterministicVector4D64(P.W);

	VTempX = VTempX * VOurX;
	VTempX = (VTempY * VOurY) + VTempX;
	VTempX = (VTempZ * VOurZ) + VTempX;
	VTempX = (VTempW * VOurW) + VTempX;

	return VTempX;
}

FORCEINLINE FDeterministicVector4D64 FDeterministicMatrix64::TransformPosition(const FDeterministicVector64& V) const
{
	return TransformFVector4(FDeterministicVector4D64(V.X, V.Y, V.Z, DeterministicFloat::Constants::Number64::One));
}

FORCEINLINE FDeterministicVector64 FDeterministicMatrix64::InverseTransformPosition(const FDeterministicVector64& V) const
{
	FDeterministicMatrix64 InvSelf = this->InverseFast();
	return InvSelf.TransformPosition(V);
	return FDeterministicVector64();
}

FORCEINLINE FDeterministicVector4D64 FDeterministicMatrix64::TransformVector(const FDeterministicVector64& V) const
{
	return TransformFVector4(FDeterministicVector4D64(V.X, V.Y, V.Z, FDeterministicNumber64()));
}

FORCEINLINE FDeterministicVector64 FDeterministicMatrix64::InverseTransformVector(const FDeterministicVector64& V) const
{
	FDeterministicMatrix64 InvSelf = this->InverseFast();
	return InvSelf.TransformVector(V);
	return FDeterministicVector64();
}

FORCEINLINE FDeterministicRotator64::FDeterministicRotator64(const FDeterministicQuat64& Quat)
{
	*this = Quat.Rotator();
}

FORCEINLINE FDeterministicRotator64 FDeterministicRotator64::GetInverse() const
{
	return Quaternion().Inverse().Rotator();
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

inline void FDeterministicMatrix64::SetAxis(int32 i, const FDeterministicVector64& Axis)
{
	checkSlow(i >= 0 && i <= 2);
	M[i][0] = Axis.X;
	M[i][1] = Axis.Y;
	M[i][2] = Axis.Z;
}

inline void FDeterministicMatrix64::SetOrigin(const FDeterministicVector64& NewOrigin)
{
	M[3][0] = NewOrigin.X;
	M[3][1] = NewOrigin.Y;
	M[3][2] = NewOrigin.Z;
}

inline void FDeterministicMatrix64::SetAxes(const FDeterministicVector64* Axis0 /*= NULL*/, const FDeterministicVector64* Axis1 /*= NULL*/, const FDeterministicVector64* Axis2 /*= NULL*/, const FDeterministicVector64* Origin /*= NULL*/)
{
	if (Axis0 != NULL)
	{
		M[0][0] = Axis0->X;
		M[0][1] = Axis0->Y;
		M[0][2] = Axis0->Z;
	}
	if (Axis1 != NULL)
	{
		M[1][0] = Axis1->X;
		M[1][1] = Axis1->Y;
		M[1][2] = Axis1->Z;
	}
	if (Axis2 != NULL)
	{
		M[2][0] = Axis2->X;
		M[2][1] = Axis2->Y;
		M[2][2] = Axis2->Z;
	}
	if (Origin != NULL)
	{
		M[3][0] = Origin->X;
		M[3][1] = Origin->Y;
		M[3][2] = Origin->Z;
	}
}

inline FDeterministicVector64 FDeterministicMatrix64::GetColumn(int32 i) const
{
	checkSlow(i >= 0 && i <= 3);
	return FDeterministicVector64(M[0][i], M[1][i], M[2][i]);
}

inline void FDeterministicMatrix64::SetColumn(int32 i, FDeterministicVector64 Value)
{
	checkSlow(i >= 0 && i <= 3);
	M[0][i] = Value.X;
	M[1][i] = Value.Y;
	M[2][i] = Value.Z;
}

//FFixedVector FDeterministicRotator64::RotateVector(const FFixedVector& V) const
//{
//	return FDeterministicRotationMatrix64(*this).TransformVector(V);
//}

//FFixedVector FDeterministicRotator64::UnrotateVector(const FFixedVector& V) const
//{
//	FDeterministicRotationMatrix64(*this).GetTransposed().TransformVector( V );
//}

#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatQuat64Funcs.h"
#include "DeterministicFloatQuatRotationTranslationMatrix64Funcs.h"