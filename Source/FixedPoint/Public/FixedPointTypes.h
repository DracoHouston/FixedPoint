// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FixedPointFwd.h"

#include "FixedPointNumbers.h"
#include "FixedPointMath.h"
#include "FixedPointVector.h"
#include "FixedPointVector2D.h"
#include "FixedPointVector4.h"
#include "FixedPointPlane.h"
#include "FixedPointMatrix.h"
#include "FixedPointQuat.h"
#include "FixedPointRotator.h"
#include "FixedPointRotationTranslationMatrix.h"
#include "FixedPointRotationMatrix.h"
#include "FixedPointQuatRotationTranslationMatrix.h"
#include "FixedPointTransform.h"

FORCEINLINE FFixedVector64::FFixedVector64(const FFixedVector2d& V, const FFixed64& InZ)
{
	X = V.X;
	Y = V.Y;
	Z = InZ;
}

FORCEINLINE FFixedVector64::FFixedVector64(const FFixedVector4d& V)
{
	X = V.X;
	Y = V.Y;
	Z = V.Z;
}

FORCEINLINE FFixedVector2d FFixedVector64::UnitCartesianToSpherical() const
{
	checkSlow(IsUnit());
	//not safe for deterministic sims
	const FFixed64 Theta = FFixedPointMath::Acos(Z / Size());
	const FFixed64 Phi = FFixedPointMath::Atan2(Y, X);
	return FFixedVector2d(Theta, Phi);
}

FORCEINLINE FFixedRotator64 FFixedVector64::Rotation() const
{
	return ToOrientationRotator();
}

FORCEINLINE FFixedVector64 FFixedVector64::PointPlaneProject(const FFixedVector64& Point, const FFixedVector64& A, const FFixedVector64& B, const FFixedVector64& C)
{
	//Compute the plane normal from ABC
	FFixedPlane Plane(A, B, C);

	//Find the distance of X from the plane
	//Add the distance back along the normal from the point
	return Point - Plane.PlaneDot(Point) * Plane;
}

FORCEINLINE FFixedMatrix::FFixedMatrix(const FFixedPlane& InX, const FFixedPlane& InY, const FFixedPlane& InZ, const FFixedPlane& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = InW.W;
}

FORCEINLINE  FFixedMatrix::FFixedMatrix(const FFixedVector64& InX, const FFixedVector64& InY, const FFixedVector64& InZ, const FFixedVector64& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = FixedPoint::Constants::Fixed64::Zero;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = FixedPoint::Constants::Fixed64::Zero;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = FixedPoint::Constants::Fixed64::Zero;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = FixedPoint::Constants::Fixed64::One;
}

inline FFixedVector64 FFixedMatrix::GetScaledAxis(EAxis::Type InAxis) const
{
	switch (InAxis)
	{
	case EAxis::X:
		return FFixedVector64(M[0][0], M[0][1], M[0][2]);

	case EAxis::Y:
		return FFixedVector64(M[1][0], M[1][1], M[1][2]);

	case EAxis::Z:
		return FFixedVector64(M[2][0], M[2][1], M[2][2]);

	default:
		ensure(0);
		return FFixedVector64::ZeroVector;
	}
}

inline void FFixedMatrix::GetScaledAxes(FFixedVector64& X, FFixedVector64& Y, FFixedVector64& Z) const
{
	X.X = M[0][0]; X.Y = M[0][1]; X.Z = M[0][2];
	Y.X = M[1][0]; Y.Y = M[1][1]; Y.Z = M[1][2];
	Z.X = M[2][0]; Z.Y = M[2][1]; Z.Z = M[2][2];
}

inline FFixedVector64 FFixedMatrix::GetUnitAxis(EAxis::Type InAxis) const
{
	return GetScaledAxis(InAxis).GetSafeNormal();
}

inline void FFixedMatrix::GetUnitAxes(FFixedVector64& X, FFixedVector64& Y, FFixedVector64& Z) const
{
	GetScaledAxes(X, Y, Z);
	X.Normalize();
	Y.Normalize();
	Z.Normalize();
}

FORCEINLINE FFixedMatrix FFixedMatrix::InverseFast() const
{
	// If we're in non final release, then make sure we're not creating NaNs
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber))
	{
		ErrorEnsure(TEXT("FFixedMatrix::InverseFast(), trying to invert a NIL matrix, garbage in, garbage out! Use Inverse() instead."));
	}
	else
	{
		const FFixed64	Det = Determinant();

		if (Det == FixedPoint::Constants::Fixed64::Zero)
		{
			ErrorEnsure(TEXT("FFixedMatrix::InverseFast(), trying to invert a non-invertible matrix, garbage in, garbage out! Use Inverse() instead."));
		}
	}
#endif
	FFixedMatrix Result;
	Internal_MatrixInverse(Result, *this);
	return Result;
}

FORCEINLINE FFixedMatrix FFixedMatrix::Inverse() const
{
	FFixedMatrix Result;

	//Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber))
	{
		// just set to zero - avoids unsafe inverse of zero and duplicates what QNANs were resulting in before (scaling away all children)
		Result = Identity;
	}
	else
	{
		const FFixed64	Det = Determinant();

		if (Det == FixedPoint::Constants::Fixed64::Zero)
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

inline FFixedVector64 FFixedMatrix::ExtractScaling(FFixed64 Tolerance/*=UE_SMALL_NUMBER*/)
{
	FFixedVector64 Scale3D(0, 0, 0);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	const FFixed64 SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
	const FFixed64 SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
	const FFixed64 SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);

	if (SquareSum0 > Tolerance)
	{
		FFixed64 Scale0 = FFixedPointMath::Sqrt(SquareSum0);
		Scale3D[0] = Scale0;
		FFixed64 InvScale0 = FixedPoint::Constants::Fixed64::One / Scale0;
		M[0][0] *= InvScale0;
		M[0][1] *= InvScale0;
		M[0][2] *= InvScale0;
	}
	else
	{
		Scale3D[0] = FixedPoint::Constants::Fixed64::Zero;
	}

	if (SquareSum1 > Tolerance)
	{
		FFixed64 Scale1 = FFixedPointMath::Sqrt(SquareSum1);
		Scale3D[1] = Scale1;
		FFixed64 InvScale1 = FixedPoint::Constants::Fixed64::One / Scale1;
		M[1][0] *= InvScale1;
		M[1][1] *= InvScale1;
		M[1][2] *= InvScale1;
	}
	else
	{
		Scale3D[1] = FixedPoint::Constants::Fixed64::Zero;
	}

	if (SquareSum2 > Tolerance)
	{
		FFixed64 Scale2 = FFixedPointMath::Sqrt(SquareSum2);
		Scale3D[2] = Scale2;
		FFixed64 InvScale2 = FixedPoint::Constants::Fixed64::One / Scale2;
		M[2][0] *= InvScale2;
		M[2][1] *= InvScale2;
		M[2][2] *= InvScale2;
	}
	else
	{
		Scale3D[2] = FixedPoint::Constants::Fixed64::Zero;
	}

	return Scale3D;
}

inline FFixedVector64 FFixedMatrix::GetScaleVector(FFixed64 Tolerance) const
{
	FFixedVector64 Scale3D(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::One);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	for (int32 i = 0; i < 3; i++)
	{
		const FFixed64 SquareSum = (M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]);
		if (SquareSum > Tolerance)
		{
			Scale3D[i] = FFixedPointMath::Sqrt(SquareSum);
		}
		else
		{
			Scale3D[i] = FixedPoint::Constants::Fixed64::Zero;
		}
	}

	return Scale3D;
}

FORCEINLINE FFixedMatrix FFixedMatrix::ConcatTranslation(const FFixedVector64& Translation) const
{
	FFixedMatrix Result;

	FFixed64* RESTRICT Dest = &Result.M[0][0];
	const FFixed64* RESTRICT Src = &M[0][0];
	const FFixed64* RESTRICT Trans = &Translation.X;

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

inline void FFixedMatrix::ScaleTranslation(const FFixedVector64& InScale3D)
{
	M[3][0] *= InScale3D.X;
	M[3][1] *= InScale3D.Y;
	M[3][2] *= InScale3D.Z;
}

inline FFixedMatrix FFixedMatrix::ApplyScale(FFixed64 Scale) const
{
	FFixedMatrix ScaleMatrix(
		FFixedPlane(Scale, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero),
		FFixedPlane(FixedPoint::Constants::Fixed64::Zero, Scale, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero),
		FFixedPlane(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, Scale, FixedPoint::Constants::Fixed64::Zero),
		FFixedPlane(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One)
	);
	return ScaleMatrix * *this;
}

inline FFixedVector64 FFixedMatrix::GetOrigin() const
{
	return FFixedVector64(M[3][0], M[3][1], M[3][2]);
}

inline FFixedPlane FFixedPlane::TransformBy(const FFixedMatrix& M) const
{
	const FFixedMatrix tmpTA = M.TransposeAdjoint();
	const FFixed64 DetM = M.Determinant();
	return this->TransformByUsingAdjointT(M, DetM, tmpTA);
}

FORCEINLINE FFixedVector4d FFixedMatrix::TransformFVector4(const FFixedVector4d& P) const
{
	FFixedVector4d VOurX = FFixedVector4d(M[0][0], M[0][1], M[0][2], M[0][3]);
	FFixedVector4d VOurY = FFixedVector4d(M[1][0], M[1][1], M[1][2], M[1][3]);
	FFixedVector4d VOurZ = FFixedVector4d(M[2][0], M[2][1], M[2][2], M[2][3]);
	FFixedVector4d VOurW = FFixedVector4d(M[3][0], M[3][1], M[3][2], M[3][3]);

	FFixedVector4d VTempX = FFixedVector4d(P.X);
	FFixedVector4d VTempY = FFixedVector4d(P.Y);
	FFixedVector4d VTempZ = FFixedVector4d(P.Z);
	FFixedVector4d VTempW = FFixedVector4d(P.W);

	VTempX = VTempX * VOurX;
	VTempX = (VTempY * VOurY) + VTempX;
	VTempX = (VTempZ * VOurZ) + VTempX;
	VTempX = (VTempW * VOurW) + VTempX;

	return VTempX;
}

FORCEINLINE FFixedVector4d FFixedMatrix::TransformPosition(const FFixedVector64& V) const
{
	return TransformFVector4(FFixedVector4d(V.X, V.Y, V.Z, FixedPoint::Constants::Fixed64::One));
}

FORCEINLINE FFixedVector64 FFixedMatrix::InverseTransformPosition(const FFixedVector64& V) const
{
	FFixedMatrix InvSelf = this->InverseFast();
	return InvSelf.TransformPosition(V);
	return FFixedVector64();
}

FORCEINLINE FFixedVector4d FFixedMatrix::TransformVector(const FFixedVector64& V) const
{
	return TransformFVector4(FFixedVector4d(V.X, V.Y, V.Z, FFixed64()));
}

FORCEINLINE FFixedVector64 FFixedMatrix::InverseTransformVector(const FFixedVector64& V) const
{
	FFixedMatrix InvSelf = this->InverseFast();
	return InvSelf.TransformVector(V);
	return FFixedVector64();
}

FORCEINLINE FFixedRotator64::FFixedRotator64(const FFixedQuat64& Quat)
{
	*this = Quat.Rotator();
}

FORCEINLINE FFixedQuat64::FFixedQuat64(const FFixedRotator64& R)
{
	*this = R.Quaternion();
}

FORCEINLINE FFixedRotator64 FFixedRotator64::GetInverse() const
{
	return Quaternion().Inverse().Rotator();
}

FORCEINLINE FFixedQuat64 FFixedRotator64::Quaternion() const
{
	const FFixed64 DEG_TO_RAD = FixedPoint::Constants::Fixed64::Pi / (FixedPoint::Constants::Fixed64::OneEighty);
	const FFixed64 RADS_DIVIDED_BY_2 = DEG_TO_RAD / FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2);
	FFixed64 SP, SY, SR;
	FFixed64 CP, CY, CR;

	const FFixed64 PitchNoWinding = FFixedPointMath::Fmod(Pitch, FixedPoint::Constants::Fixed64::ThreeSixty);
	const FFixed64 YawNoWinding = FFixedPointMath::Fmod(Yaw, FixedPoint::Constants::Fixed64::ThreeSixty);
	const FFixed64 RollNoWinding = FFixedPointMath::Fmod(Roll, FixedPoint::Constants::Fixed64::ThreeSixty);

	FFixedPointMath::SinCos(&SP, &CP, PitchNoWinding * RADS_DIVIDED_BY_2);
	FFixedPointMath::SinCos(&SY, &CY, YawNoWinding * RADS_DIVIDED_BY_2);
	FFixedPointMath::SinCos(&SR, &CR, RollNoWinding * RADS_DIVIDED_BY_2);

	FFixedQuat64 RotationQuat;
	RotationQuat.X = CR * SP * SY - SR * CP * CY;
	RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
	RotationQuat.Z = CR * CP * SY - SR * SP * CY;
	RotationQuat.W = CR * CP * CY + SR * SP * SY;

	return RotationQuat;
}

FORCEINLINE FFixedVector64 FFixedRotator64::Vector() const
{
	// Remove winding and clamp to [-360, 360]
	const FFixed64 PitchNoWinding = FFixedPointMath::Fmod(Pitch, FixedPoint::Constants::Fixed64::ThreeSixty);
	const FFixed64 YawNoWinding = FFixedPointMath::Fmod(Yaw, FixedPoint::Constants::Fixed64::ThreeSixty);

	FFixed64 CP, SP, CY, SY;
	FFixedPointMath::SinCos(&SP, &CP, FFixedPointMath::DegreesToRadians(PitchNoWinding));
	FFixedPointMath::SinCos(&SY, &CY, FFixedPointMath::DegreesToRadians(YawNoWinding));
	FFixedVector64 V = FFixedVector64(CP * CY, CP * SY, SP);

	return V;
}

FORCEINLINE FFixedVector64 FFixedRotator64::Euler() const
{
	return FFixedVector64(Roll, Pitch, Yaw);
}

FORCEINLINE FFixedVector64 FFixedRotator64::RotateVector(const FFixedVector64& V) const
{
	return FFixedRotationMatrix(*this).TransformVector(V);
}

FORCEINLINE FFixedVector64 FFixedRotator64::UnrotateVector(const FFixedVector64& V) const
{
	return FFixedRotationMatrix(*this).GetTransposed().TransformVector(V);
}

FORCEINLINE_DEBUGGABLE FFixedRotator64 FFixedPointMath::LerpRange(const FFixedRotator64& A, const FFixedRotator64& B, FFixed64 Alpha)
{
	// Similar to Lerp, but does not take the shortest path. Allows interpolation over more than 180 degrees.
	return (A * (FixedPoint::Constants::Fixed64::One - Alpha) + B * Alpha).GetNormalized();
}

FORCEINLINE_DEBUGGABLE FFixed64 FFixedPointMath::ClampAngle(FFixed64 AngleDegrees, FFixed64 MinAngleDegrees, FFixed64 MaxAngleDegrees)
{
	const FFixed64 MaxDelta = FFixedRotator64::ClampAxis(MaxAngleDegrees - MinAngleDegrees) * FixedPoint::Constants::Fixed64::Half;			// 0..180
	const FFixed64 RangeCenter = FFixedRotator64::ClampAxis(MinAngleDegrees + MaxDelta);						// 0..360
	const FFixed64 DeltaFromCenter = FFixedRotator64::NormalizeAxis(AngleDegrees - RangeCenter);				// -180..180

	// maybe clamp to nearest edge
	if (DeltaFromCenter > MaxDelta)
	{
		return FFixedRotator64::NormalizeAxis(RangeCenter + MaxDelta);
	}
	else if (DeltaFromCenter < -MaxDelta)
	{
		return FFixedRotator64::NormalizeAxis(RangeCenter - MaxDelta);
	}

	// already in range, just return it
	return FFixedRotator64::NormalizeAxis(AngleDegrees);
}

FORCEINLINE_DEBUGGABLE FFixed32 FFixedPointMath::ClampAngle(FFixed32 AngleDegrees, FFixed32 MinAngleDegrees, FFixed32 MaxAngleDegrees)
{
	const FFixed32 MaxDelta = FFixedRotator64::ClampAxis(MaxAngleDegrees - MinAngleDegrees) * FixedPoint::Constants::Fixed32::Half;			// 0..180
	const FFixed32 RangeCenter = FFixedRotator64::ClampAxis(MinAngleDegrees + MaxDelta);						// 0..360
	const FFixed32 DeltaFromCenter = FFixedRotator64::NormalizeAxis(AngleDegrees - RangeCenter);				// -180..180

	// maybe clamp to nearest edge
	if (DeltaFromCenter > MaxDelta)
	{
		return FFixedRotator64::NormalizeAxis(RangeCenter + MaxDelta);
	}
	else if (DeltaFromCenter < -MaxDelta)
	{
		return FFixedRotator64::NormalizeAxis(RangeCenter - MaxDelta);
	}

	// already in range, just return it
	return FFixedRotator64::NormalizeAxis(AngleDegrees);
}

inline FFixedVector64 FFixedPointMath::LinePlaneIntersection
(
	const FFixedVector64& Point1,
	const FFixedVector64& Point2,
	const FFixedVector64& PlaneOrigin,
	const FFixedVector64& PlaneNormal
)
{
	return
		Point1
		+ (Point2 - Point1)
		* (((PlaneOrigin - Point1) | PlaneNormal) / ((Point2 - Point1) | PlaneNormal));
}

inline bool FFixedPointMath::LineSphereIntersection(const FFixedVector64& Start, const FFixedVector64& Dir, FFixed64 Length, const FFixedVector64& Origin, FFixed64 Radius)
{
	const FFixedVector64	EO = Start - Origin;
	const FFixed64		v = (Dir | (Origin - Start));
	const FFixed64		disc = Radius * Radius - ((EO | EO) - v * v);

	if (disc >= FixedPoint::Constants::Fixed64::Zero)
	{
		const FFixed64	Time = (v - Sqrt(disc)) / Length;

		if (Time >= FixedPoint::Constants::Fixed64::Zero && Time <= FixedPoint::Constants::Fixed64::One)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

inline FFixedVector64 FFixedPointMath::VRand()
{
	FFixedVector64 Result;
	FFixed64 L;

	do
	{
		// Check random vectors in the unit sphere so result is statistically uniform.
		Result.X = FRand() * 2.f - 1.f;
		Result.Y = FRand() * 2.f - 1.f;
		Result.Z = FRand() * 2.f - 1.f;
		L = Result.SizeSquared();
	} while (L > FixedPoint::Constants::Fixed64::One || L < FixedPoint::Constants::Fixed64::KindaSmallNumber);

	return Result * (FixedPoint::Constants::Fixed64::One / Sqrt(L));
}

inline void FFixedMatrix::SetAxis(int32 i, const FFixedVector64& Axis)
{
	checkSlow(i >= 0 && i <= 2);
	M[i][0] = Axis.X;
	M[i][1] = Axis.Y;
	M[i][2] = Axis.Z;
}

inline void FFixedMatrix::SetOrigin(const FFixedVector64& NewOrigin)
{
	M[3][0] = NewOrigin.X;
	M[3][1] = NewOrigin.Y;
	M[3][2] = NewOrigin.Z;
}

inline void FFixedMatrix::SetAxes(const FFixedVector64* Axis0 /*= NULL*/, const FFixedVector64* Axis1 /*= NULL*/, const FFixedVector64* Axis2 /*= NULL*/, const FFixedVector64* Origin /*= NULL*/)
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

inline FFixedVector64 FFixedMatrix::GetColumn(int32 i) const
{
	checkSlow(i >= 0 && i <= 3);
	return FFixedVector64(M[0][i], M[1][i], M[2][i]);
}

inline void FFixedMatrix::SetColumn(int32 i, FFixedVector64 Value)
{
	checkSlow(i >= 0 && i <= 3);
	M[0][i] = Value.X;
	M[1][i] = Value.Y;
	M[2][i] = Value.Z;
}

//FFixedVector FFixedRotator64::RotateVector(const FFixedVector& V) const
//{
//	return FFixedRotationMatrix(*this).TransformVector(V);
//}

//FFixedVector FFixedRotator64::UnrotateVector(const FFixedVector& V) const
//{
//	FFixedRotationMatrix(*this).GetTransposed().TransformVector( V );
//}