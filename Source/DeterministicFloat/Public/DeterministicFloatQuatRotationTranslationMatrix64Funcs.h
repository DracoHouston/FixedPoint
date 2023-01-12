// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatQuatRotationTranslationMatrix64.h"
#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatTypes.h"
#include "Misc/AssertionMacros.h"


FORCEINLINE FDeterministicQuatRotationTranslationMatrix64::FDeterministicQuatRotationTranslationMatrix64()
{
}

FORCEINLINE FDeterministicQuatRotationTranslationMatrix64::FDeterministicQuatRotationTranslationMatrix64(const FDeterministicQuat64& Q, const FDeterministicVector64& Origin)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
	// Make sure Quaternion is normalized
	check(Q.IsNormalized());
#endif
	const FDeterministicNumber64 x2 = Q.X + Q.X;  const FDeterministicNumber64 y2 = Q.Y + Q.Y;  const FDeterministicNumber64 z2 = Q.Z + Q.Z;
	const FDeterministicNumber64 xx = Q.X * x2;   const FDeterministicNumber64 xy = Q.X * y2;   const FDeterministicNumber64 xz = Q.X * z2;
	const FDeterministicNumber64 yy = Q.Y * y2;   const FDeterministicNumber64 yz = Q.Y * z2;   const FDeterministicNumber64 zz = Q.Z * z2;
	const FDeterministicNumber64 wx = Q.W * x2;   const FDeterministicNumber64 wy = Q.W * y2;   const FDeterministicNumber64 wz = Q.W * z2;

	M[0][0] = DeterministicFloat::Constants::Number64::One - (yy + zz);	M[1][0] = xy - wz;												
	M[0][1] = xy + wz;											M[1][1] = DeterministicFloat::Constants::Number64::One - (xx + zz);		
	M[0][2] = xz - wy;											M[1][2] = yz + wx;												
	M[0][3] = DeterministicFloat::Constants::Number64::Zero;				M[1][3] = DeterministicFloat::Constants::Number64::Zero;	
	M[2][0] = xz + wy;											M[3][0] = Origin.X;
	M[2][1] = yz - wx;											M[3][1] = Origin.Y;
	M[2][2] = DeterministicFloat::Constants::Number64::One - (xx + yy);	M[3][2] = Origin.Z;
	M[2][3] = DeterministicFloat::Constants::Number64::Zero;				M[3][3] = DeterministicFloat::Constants::Number64::One;
}

/** Matrix factory. Return an FDeterministicMatrix64 so we don't have type conversion issues in expressions. */
FORCEINLINE FDeterministicMatrix64 FDeterministicQuatRotationTranslationMatrix64::Make(const FDeterministicQuat64& Q, const FDeterministicVector64& Origin)
{
	return FDeterministicQuatRotationTranslationMatrix64(Q, Origin);
}

FORCEINLINE FDeterministicQuatRotationMatrix64::FDeterministicQuatRotationMatrix64()
{
}

FORCEINLINE FDeterministicQuatRotationMatrix64::FDeterministicQuatRotationMatrix64(const FDeterministicQuat64& Q)
	: FDeterministicQuatRotationTranslationMatrix64(Q, FDeterministicVector64::ZeroVector)
{
}

FORCEINLINE FDeterministicMatrix64 FDeterministicQuatRotationMatrix64::Make(const FDeterministicQuat64& Q)
{
	return FDeterministicQuatRotationMatrix64(Q);
}
