// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/AssertionMacros.h"
#include "FixedPointFwd.h"
#include "FixedPointNumbers.h"
#include "FixedPointMatrix.h"
#include "FixedPointVector.h"
#include "FixedPointRotator.h"
#include "FixedPointQuat.h"
#include "FixedPointMath.h"
#include "FixedPointQuatRotationTranslationMatrix.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedQuatRotationTranslationMatrix : public FFixedMatrix
{
public:
	GENERATED_BODY()

	FFixedQuatRotationTranslationMatrix() {};
	/**
	 * Constructor.
	 *
	 * @param Rot rotation
	 * @param Origin translation to apply
	 */
	FORCEINLINE FFixedQuatRotationTranslationMatrix(const FFixedQuat64& Q, const FFixedVector64& Origin)
	{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
		// Make sure Quaternion is normalized
		check(Q.IsNormalized());
#endif
		const FFixed64 x2 = Q.X + Q.X;  const FFixed64 y2 = Q.Y + Q.Y;  const FFixed64 z2 = Q.Z + Q.Z;
		const FFixed64 xx = Q.X * x2;   const FFixed64 xy = Q.X * y2;   const FFixed64 xz = Q.X * z2;
		const FFixed64 yy = Q.Y * y2;   const FFixed64 yz = Q.Y * z2;   const FFixed64 zz = Q.Z * z2;
		const FFixed64 wx = Q.W * x2;   const FFixed64 wy = Q.W * y2;   const FFixed64 wz = Q.W * z2;

		M[0][0] = FixedPoint::Constants::Fixed64::One - (yy + zz);	M[1][0] = xy - wz;												
		M[0][1] = xy + wz;											M[1][1] = FixedPoint::Constants::Fixed64::One - (xx + zz);		
		M[0][2] = xz - wy;											M[1][2] = yz + wx;												
		M[0][3] = FixedPoint::Constants::Fixed64::Zero;				M[1][3] = FixedPoint::Constants::Fixed64::Zero;	
		M[2][0] = xz + wy;											M[3][0] = Origin.X;
		M[2][1] = yz - wx;											M[3][1] = Origin.Y;
		M[2][2] = FixedPoint::Constants::Fixed64::One - (xx + yy);	M[3][2] = Origin.Z;
		M[2][3] = FixedPoint::Constants::Fixed64::Zero;				M[3][3] = FixedPoint::Constants::Fixed64::One;
	}

	/** Matrix factory. Return an FFixedMatrix so we don't have type conversion issues in expressions. */
	static FFixedMatrix Make(const FFixedQuat64& Q, const FFixedVector64& Origin)
	{
		return FFixedQuatRotationTranslationMatrix(Q, Origin);
	}
};

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedQuatRotationMatrix
	: public FFixedQuatRotationTranslationMatrix
{
public:
	GENERATED_BODY()

	FFixedQuatRotationMatrix() {};
	/** Constructor
	*
	* @param Q rotation
	*/
	FFixedQuatRotationMatrix(const FFixedQuat64& Q)
		: FFixedQuatRotationTranslationMatrix(Q, FFixedVector64::ZeroVector)
	{
	}

	/** Matrix factory. Return an FMatrix so we don't have type conversion issues in expressions. */
	static FFixedMatrix Make(const FFixedQuat64& Q)
	{
		return FFixedQuatRotationMatrix(Q);
	}
};