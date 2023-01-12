// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMatrix64.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatRotationTranslationMatrix64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicRotationTranslationMatrix64 : public FDeterministicMatrix64
{
public:
	GENERATED_BODY()

		FDeterministicRotationTranslationMatrix64() {};

	/**
	 * Constructor.
	 *
	 * @param Rot rotation
	 * @param Origin translation to apply
	 */
	FDeterministicRotationTranslationMatrix64(const FDeterministicRotator64& Rot, const FDeterministicVector64& Origin)
	{
		FDeterministicNumber64 SP, SY, SR;
		FDeterministicNumber64 CP, CY, CR;
		FDeterministicFloatMath::SinCos(&SP, &CP, FDeterministicFloatMath::DegreesToRadians(Rot.Pitch));
		FDeterministicFloatMath::SinCos(&SY, &CY, FDeterministicFloatMath::DegreesToRadians(Rot.Yaw));
		FDeterministicFloatMath::SinCos(&SR, &CR, FDeterministicFloatMath::DegreesToRadians(Rot.Roll));

		M[0][0] = CP * CY;
		M[0][1] = CP * SY;
		M[0][2] = SP;
		M[0][3] = DeterministicFloat::Constants::Number64::Zero;

		M[1][0] = SR * SP * CY - CR * SY;
		M[1][1] = SR * SP * SY + CR * CY;
		M[1][2] = -SR * CP;
		M[1][3] = DeterministicFloat::Constants::Number64::Zero;

		M[2][0] = -(CR * SP * CY + SR * SY);
		M[2][1] = CY * SR - CR * SP * SY;
		M[2][2] = CR * CP;
		M[2][3] = DeterministicFloat::Constants::Number64::Zero;

		M[3][0] = Origin.X;
		M[3][1] = Origin.Y;
		M[3][2] = Origin.Z;
		M[3][3] = DeterministicFloat::Constants::Number64::One;
	}

	/** Matrix factory. Return an TMatrix<T> so we don't have type conversion issues in expressions. */
	static FDeterministicMatrix64 Make(const FDeterministicRotator64& Rot, const FDeterministicVector64& Origin)
	{
		return FDeterministicRotationTranslationMatrix64(Rot, Origin);
	}
};
