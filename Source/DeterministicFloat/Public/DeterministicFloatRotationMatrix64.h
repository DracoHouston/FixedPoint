// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMatrix64.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatQuat64.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatRotationTranslationMatrix64.h"
#include "DeterministicFloatQuatRotationTranslationMatrix64.h"
#include "DeterministicFloatRotationMatrix64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicRotationMatrix64 : public FDeterministicRotationTranslationMatrix64
{
public:
	GENERATED_BODY()

		FORCEINLINE FDeterministicRotationMatrix64();

	/**
		* Constructor.
		*
		* @param Rot rotation
		*/
	FORCEINLINE FDeterministicRotationMatrix64(const FDeterministicRotator64& Rot);

	/** Matrix factory. Return an FDeterministicMatrix64 so we don't have type conversion issues in expressions. */
	FORCEINLINE static FDeterministicMatrix64 Make(FDeterministicRotator64 const& Rot);

	/** Matrix factory. Return an FDeterministicMatrix64 so we don't have type conversion issues in expressions. */
	FORCEINLINE static FDeterministicMatrix64 Make(FDeterministicQuat64 const& Rot);

	/** Builds a rotation matrix given only a XAxis. Y and Z are unspecified but will be orthonormal. XAxis need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromX(FDeterministicVector64 const& XAxis);

	/** Builds a rotation matrix given only a YAxis. X and Z are unspecified but will be orthonormal. YAxis need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromY(FDeterministicVector64 const& YAxis);

	/** Builds a rotation matrix given only a ZAxis. X and Y are unspecified but will be orthonormal. ZAxis need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromZ(FDeterministicVector64 const& ZAxis);

	/** Builds a matrix with given X and Y axes. X will remain fixed, Y may be changed minimally to enforce orthogonality. Z will be computed. Inputs need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromXY(FDeterministicVector64 const& XAxis, FDeterministicVector64 const& YAxis);

	/** Builds a matrix with given X and Z axes. X will remain fixed, Z may be changed minimally to enforce orthogonality. Y will be computed. Inputs need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromXZ(FDeterministicVector64 const& XAxis, FDeterministicVector64 const& ZAxis);

	/** Builds a matrix with given Y and X axes. Y will remain fixed, X may be changed minimally to enforce orthogonality. Z will be computed. Inputs need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromYX(FDeterministicVector64 const& YAxis, FDeterministicVector64 const& XAxis);

	/** Builds a matrix with given Y and Z axes. Y will remain fixed, Z may be changed minimally to enforce orthogonality. X will be computed. Inputs need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromYZ(FDeterministicVector64 const& YAxis, FDeterministicVector64 const& ZAxis);

	/** Builds a matrix with given Z and X axes. Z will remain fixed, X may be changed minimally to enforce orthogonality. Y will be computed. Inputs need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromZX(FDeterministicVector64 const& ZAxis, FDeterministicVector64 const& XAxis);

	/** Builds a matrix with given Z and Y axes. Z will remain fixed, Y may be changed minimally to enforce orthogonality. X will be computed. Inputs need not be normalized. */
	FORCEINLINE static FDeterministicMatrix64 MakeFromZY(FDeterministicVector64 const& ZAxis, FDeterministicVector64 const& YAxis);
};
