// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointFwd.h"
#include "FixedPointNumbers.h"
#include "FixedPointMatrix.h"
#include "FixedPointVector.h"
#include "FixedPointRotator.h"
#include "FixedPointMath.h"
#include "FixedPointRotationTranslationMatrix.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedRotationTranslationMatrix : public FFixedMatrix
{
public:
	GENERATED_BODY()

		FFixedRotationTranslationMatrix() {};

	/**
	 * Constructor.
	 *
	 * @param Rot rotation
	 * @param Origin translation to apply
	 */
	FFixedRotationTranslationMatrix(const FFixedRotator64& Rot, const FFixedVector64& Origin)
	{
		FFixed64 SP, SY, SR;
		FFixed64 CP, CY, CR;
		FFixedPointMath::SinCos(&SP, &CP, FFixedPointMath::DegreesToRadians(Rot.Pitch));
		FFixedPointMath::SinCos(&SY, &CY, FFixedPointMath::DegreesToRadians(Rot.Yaw));
		FFixedPointMath::SinCos(&SR, &CR, FFixedPointMath::DegreesToRadians(Rot.Roll));

		M[0][0] = CP * CY;
		M[0][1] = CP * SY;
		M[0][2] = SP;
		M[0][3] = FixedPoint::Constants::Fixed64::Zero;

		M[1][0] = SR * SP * CY - CR * SY;
		M[1][1] = SR * SP * SY + CR * CY;
		M[1][2] = -SR * CP;
		M[1][3] = FixedPoint::Constants::Fixed64::Zero;

		M[2][0] = -(CR * SP * CY + SR * SY);
		M[2][1] = CY * SR - CR * SP * SY;
		M[2][2] = CR * CP;
		M[2][3] = FixedPoint::Constants::Fixed64::Zero;

		M[3][0] = Origin.X;
		M[3][1] = Origin.Y;
		M[3][2] = Origin.Z;
		M[3][3] = FixedPoint::Constants::Fixed64::One;
	}

	/** Matrix factory. Return an TMatrix<T> so we don't have type conversion issues in expressions. */
	static FFixedMatrix Make(const FFixedRotator64& Rot, const FFixedVector64& Origin)
	{
		return FFixedRotationTranslationMatrix(Rot, Origin);
	}
};
