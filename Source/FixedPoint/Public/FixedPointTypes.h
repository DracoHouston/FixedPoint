// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FFixed64;
struct FFixed32;
struct FFixedVector;
struct FFixedVector2d;
struct FFixedVector4d;
struct FFixedMatrix;
struct FFixedQuat;
struct FFixedPlane;
struct FFixedRotator;

#include "FixedPointNumbers.h"
#include "FixedPointMath.h"
#include "FixedPointVectors.h"
#include "FixedPointPlane.h"
#include "FixedPointMatrix.h"
#include "FixedPointQuat.h"
#include "FixedPointRotator.h"

FORCEINLINE FFixedMatrix::FFixedMatrix(const FFixedPlane& InX, const FFixedPlane& InY, const FFixedPlane& InZ, const FFixedPlane& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = InW.W;
}

FORCEINLINE  FFixedMatrix::FFixedMatrix(const FFixedVector& InX, const FFixedVector& InY, const FFixedVector& InZ, const FFixedVector& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = FixedPoint::Constants::Fixed64::Zero;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = FixedPoint::Constants::Fixed64::Zero;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = FixedPoint::Constants::Fixed64::Zero;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = FixedPoint::Constants::Fixed64::One;
}

inline FFixedVector FFixedMatrix::GetScaledAxis(EAxis::Type InAxis) const
{
	switch (InAxis)
	{
	case EAxis::X:
		return FFixedVector(M[0][0], M[0][1], M[0][2]);

	case EAxis::Y:
		return FFixedVector(M[1][0], M[1][1], M[1][2]);

	case EAxis::Z:
		return FFixedVector(M[2][0], M[2][1], M[2][2]);

	default:
		ensure(0);
		return FFixedVector::ZeroVector;
	}
}

inline void FFixedMatrix::GetScaledAxes(FFixedVector& X, FFixedVector& Y, FFixedVector& Z) const
{
	X.X = M[0][0]; X.Y = M[0][1]; X.Z = M[0][2];
	Y.X = M[1][0]; Y.Y = M[1][1]; Y.Z = M[1][2];
	Z.X = M[2][0]; Z.Y = M[2][1]; Z.Z = M[2][2];
}

inline FFixedVector FFixedMatrix::GetUnitAxis(EAxis::Type InAxis) const
{
	return GetScaledAxis(InAxis).GetSafeNormal();
}

inline void FFixedMatrix::GetUnitAxes(FFixedVector& X, FFixedVector& Y, FFixedVector& Z) const
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

inline FFixedVector FFixedMatrix::ExtractScaling(FFixed64 Tolerance/*=UE_SMALL_NUMBER*/)
{
	FFixedVector Scale3D(0, 0, 0);

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

inline FFixedVector FFixedMatrix::GetScaleVector(FFixed64 Tolerance) const
{
	FFixedVector Scale3D(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::One);

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

FORCEINLINE FFixedMatrix FFixedMatrix::ConcatTranslation(const FFixedVector& Translation) const
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

inline void FFixedMatrix::ScaleTranslation(const FFixedVector& InScale3D)
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

inline FFixedVector FFixedMatrix::GetOrigin() const
{
	return FFixedVector(M[3][0], M[3][1], M[3][2]);
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

FORCEINLINE FFixedVector4d FFixedMatrix::TransformPosition(const FFixedVector& V) const
{
	return TransformFVector4(FFixedVector4d(V.X, V.Y, V.Z, FixedPoint::Constants::Fixed64::One));
}

FORCEINLINE FFixedVector FFixedMatrix::InverseTransformPosition(const FFixedVector& V) const
{
	FFixedMatrix InvSelf = this->InverseFast();
	return InvSelf.TransformPosition(V);
	return FFixedVector();
}

FORCEINLINE FFixedVector4d FFixedMatrix::TransformVector(const FFixedVector& V) const
{
	return TransformFVector4(FFixedVector4d(V.X, V.Y, V.Z, FFixed64()));
}

FORCEINLINE FFixedVector FFixedMatrix::InverseTransformVector(const FFixedVector& V) const
{
	FFixedMatrix InvSelf = this->InverseFast();
	return InvSelf.TransformVector(V);
	return FFixedVector();
}

FORCEINLINE FFixedRotator::FFixedRotator(const FFixedQuat& Quat)
{
	*this = Quat.Rotator();
}
