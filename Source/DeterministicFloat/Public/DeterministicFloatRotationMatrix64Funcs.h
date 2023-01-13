// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatRotationMatrix64.h"
#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatQuat64Funcs.h"
#include "DeterministicFloatQuatRotationTranslationMatrix64Funcs.h"
#include "DeterministicFloatRotationTranslationMatrix64Funcs.h"

FORCEINLINE FDeterministicRotationMatrix64::FDeterministicRotationMatrix64() 
{
}

FORCEINLINE FDeterministicRotationMatrix64::FDeterministicRotationMatrix64(const FDeterministicRotator64& Rot)
	: FDeterministicRotationTranslationMatrix64(Rot, FDeterministicVector64::ZeroVector)
{ 
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::Make(FDeterministicRotator64 const& Rot)
{
	return FDeterministicRotationMatrix64(Rot);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::Make(FDeterministicQuat64 const& Rot)
{
	return FDeterministicQuatRotationTranslationMatrix64(Rot, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromX(FDeterministicVector64 const& XAxis)
{
	FDeterministicVector64 const NewX = XAxis.GetSafeNormal();

	// try to use up if possible
	FDeterministicVector64 const UpVector = (FDeterministicFloatMath::Abs(NewX.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ? 
		FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) : 
		FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);

	const FDeterministicVector64 NewY = (UpVector ^ NewX).GetSafeNormal();
	const FDeterministicVector64 NewZ = NewX ^ NewY;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromY(FDeterministicVector64 const& YAxis)
{
	FDeterministicVector64 const NewY = YAxis.GetSafeNormal();

	// try to use up if possible
	FDeterministicVector64 const UpVector = (FDeterministicFloatMath::Abs(NewY.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ? 
		FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) :
		FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);

	const FDeterministicVector64 NewZ = (UpVector ^ NewY).GetSafeNormal();
	const FDeterministicVector64 NewX = NewY ^ NewZ;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromZ(FDeterministicVector64 const& ZAxis)
{
	FDeterministicVector64 const NewZ = ZAxis.GetSafeNormal();

	// try to use up if possible
	FDeterministicVector64 const UpVector = (FDeterministicFloatMath::Abs(NewZ.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ?
		FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) :
		FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);

	const FDeterministicVector64 NewX = (UpVector ^ NewZ).GetSafeNormal();
	const FDeterministicVector64 NewY = NewZ ^ NewX;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromXY(FDeterministicVector64 const& XAxis, FDeterministicVector64 const& YAxis)
{
	FDeterministicVector64 NewX = XAxis.GetSafeNormal();
	FDeterministicVector64 Norm = YAxis.GetSafeNormal();

	// if they're almost same, we need to find arbitrary vector
	if (FDeterministicFloatMath::IsNearlyEqual(FDeterministicFloatMath::Abs(NewX | Norm), DeterministicFloat::Constants::Number64::One))
	{
		// make sure we don't ever pick the same as NewX
		Norm = (FDeterministicFloatMath::Abs(NewX.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ? 
			FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) :
			FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);
	}

	const FDeterministicVector64 NewZ = (NewX ^ Norm).GetSafeNormal();
	const FDeterministicVector64 NewY = NewZ ^ NewX;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromXZ(FDeterministicVector64 const& XAxis, FDeterministicVector64 const& ZAxis)
{
	FDeterministicVector64 const NewX = XAxis.GetSafeNormal();
	FDeterministicVector64 Norm = ZAxis.GetSafeNormal();

	// if they're almost same, we need to find arbitrary vector
	if (FDeterministicFloatMath::IsNearlyEqual(FDeterministicFloatMath::Abs(NewX | Norm), DeterministicFloat::Constants::Number64::One))
	{
		// make sure we don't ever pick the same as NewX
		Norm = (FDeterministicFloatMath::Abs(NewX.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ? 
			FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) :
			FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);
	}

	const FDeterministicVector64 NewY = (Norm ^ NewX).GetSafeNormal();
	const FDeterministicVector64 NewZ = NewX ^ NewY;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromYX(FDeterministicVector64 const& YAxis, FDeterministicVector64 const& XAxis)
{
	FDeterministicVector64 const NewY = YAxis.GetSafeNormal();
	FDeterministicVector64 Norm = XAxis.GetSafeNormal();

	// if they're almost same, we need to find arbitrary vector
	if (FDeterministicFloatMath::IsNearlyEqual(FMath::Abs(NewY | Norm), DeterministicFloat::Constants::Number64::One))
	{
		// make sure we don't ever pick the same as NewX
		Norm = (FDeterministicFloatMath::Abs(NewY.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ? 
			FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) :
			FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);
	}

	const FDeterministicVector64 NewZ = (Norm ^ NewY).GetSafeNormal();
	const FDeterministicVector64 NewX = NewY ^ NewZ;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromYZ(FDeterministicVector64 const& YAxis, FDeterministicVector64 const& ZAxis)
{
	FDeterministicVector64 const NewY = YAxis.GetSafeNormal();
	FDeterministicVector64 Norm = ZAxis.GetSafeNormal();

	// if they're almost same, we need to find arbitrary vector
	if (FDeterministicFloatMath::IsNearlyEqual(FMath::Abs(NewY | Norm), DeterministicFloat::Constants::Number64::One))
	{
		// make sure we don't ever pick the same as NewX
		Norm = (FDeterministicFloatMath::Abs(NewY.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ?
			FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) :
			FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);
	}

	const FDeterministicVector64 NewX = (NewY ^ Norm).GetSafeNormal();
	const FDeterministicVector64 NewZ = NewX ^ NewY;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromZX(FDeterministicVector64 const& ZAxis, FDeterministicVector64 const& XAxis)
{
	FDeterministicVector64 const NewZ = ZAxis.GetSafeNormal();
	FDeterministicVector64 Norm = XAxis.GetSafeNormal();

	// if they're almost same, we need to find arbitrary vector
	if (FDeterministicFloatMath::IsNearlyEqual(FMath::Abs(NewZ | Norm), DeterministicFloat::Constants::Number64::One))
	{
		// make sure we don't ever pick the same as NewX
		Norm = (FDeterministicFloatMath::Abs(NewZ.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ?
			FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) :
			FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);
	}

	const FDeterministicVector64 NewY = (NewZ ^ Norm).GetSafeNormal();
	const FDeterministicVector64 NewX = NewY ^ NewZ;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicRotationMatrix64::MakeFromZY(FDeterministicVector64 const& ZAxis, FDeterministicVector64 const& YAxis)
{
	FDeterministicVector64 const NewZ = ZAxis.GetSafeNormal();
	FDeterministicVector64 Norm = YAxis.GetSafeNormal();

	// if they're almost same, we need to find arbitrary vector
	if (FDeterministicFloatMath::IsNearlyEqual(FMath::Abs(NewZ | Norm), DeterministicFloat::Constants::Number64::One))
	{
		// make sure we don't ever pick the same as NewX
		Norm = (FDeterministicFloatMath::Abs(NewZ.Z) < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::KindaSmallNumber)) ?
			FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One) :
			FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);
	}

	const FDeterministicVector64 NewX = (Norm ^ NewZ).GetSafeNormal();
	const FDeterministicVector64 NewY = NewZ ^ NewX;

	return FDeterministicMatrix64(NewX, NewY, NewZ, FDeterministicVector64::ZeroVector);
}
