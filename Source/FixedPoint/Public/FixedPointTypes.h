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

#include "FixedPointNumbers.h"
#include "FixedPointMath.h"
#include "FixedPointVectors.h"
#include "FixedPointPlane.h"
#include "FixedPointMatrix.h"
#include "FixedPointQuat.h"

FORCEINLINE FFixedMatrix::FFixedMatrix(const FFixedPlane& InX, const FFixedPlane& InY, const FFixedPlane& InZ, const FFixedPlane& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = InW.W;
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

inline FFixedPlane FFixedPlane::TransformBy(const FFixedMatrix& M) const
{
	const FFixedMatrix tmpTA = M.TransposeAdjoint();
	const FFixed64 DetM = M.Determinant();
	return this->TransformByUsingAdjointT(M, DetM, tmpTA);
}