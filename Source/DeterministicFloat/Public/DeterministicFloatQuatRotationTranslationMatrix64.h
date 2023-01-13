// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/AssertionMacros.h"
//#include "DeterministicFloatTypes.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMatrix64.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatQuat64.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatQuatRotationTranslationMatrix64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicQuatRotationTranslationMatrix64 : public FDeterministicMatrix64
{
public:
	GENERATED_BODY()

	FDeterministicQuatRotationTranslationMatrix64();
	
	FORCEINLINE FDeterministicQuatRotationTranslationMatrix64(const FDeterministicQuat64& Q, const FDeterministicVector64& Origin);

	FORCEINLINE static FDeterministicMatrix64 Make(const FDeterministicQuat64& Q, const FDeterministicVector64& Origin);
};

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicQuatRotationMatrix64
	: public FDeterministicQuatRotationTranslationMatrix64
{
public:
	GENERATED_BODY()

	FORCEINLINE FDeterministicQuatRotationMatrix64();
	
	FORCEINLINE FDeterministicQuatRotationMatrix64(const FDeterministicQuat64& Q);

	/** Matrix factory. Return an FMatrix so we don't have type conversion issues in expressions. */
	FORCEINLINE static FDeterministicMatrix64 Make(const FDeterministicQuat64& Q);
};