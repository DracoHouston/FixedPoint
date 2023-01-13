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

		FORCEINLINE FDeterministicRotationTranslationMatrix64();

	/**
	 * Constructor.
	 *
	 * @param Rot rotation
	 * @param Origin translation to apply
	 */
	FORCEINLINE FDeterministicRotationTranslationMatrix64(const FDeterministicRotator64& Rot, const FDeterministicVector64& Origin);

	/** Matrix factory. Return an TMatrix<T> so we don't have type conversion issues in expressions. */
	FORCEINLINE static FDeterministicMatrix64 Make(const FDeterministicRotator64& Rot, const FDeterministicVector64& Origin);
};
