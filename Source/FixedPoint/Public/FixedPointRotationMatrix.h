// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointRotationTranslationMatrix.h"
#include "FixedPointQuatRotationTranslationMatrix.h"
#include "FixedPointRotationMatrix.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedRotationMatrix : public FFixedRotationTranslationMatrix
{
public:
	GENERATED_BODY()

	FFixedRotationMatrix() {};

	/**
		* Constructor.
		*
		* @param Rot rotation
		*/
	FFixedRotationMatrix(const FFixedRotator64& Rot)
		: FFixedRotationTranslationMatrix(Rot, FFixedVector64::ZeroVector)
	{ }

	/** Matrix factory. Return an FFixedMatrix so we don't have type conversion issues in expressions. */
	static FFixedMatrix Make(FFixedRotator64 const& Rot)
	{
		return FFixedRotationMatrix(Rot);
	}

	/** Matrix factory. Return an FFixedMatrix so we don't have type conversion issues in expressions. */
	static FFixedMatrix Make(FFixedQuat64 const& Rot)
	{
		return FFixedQuatRotationTranslationMatrix(Rot, FFixedVector64::ZeroVector);
	}

	/** Builds a rotation matrix given only a XAxis. Y and Z are unspecified but will be orthonormal. XAxis need not be normalized. */
	static FFixedMatrix MakeFromX(FFixedVector64 const& XAxis)
	{
		FFixedVector64 const NewX = XAxis.GetSafeNormal();

		// try to use up if possible
		FFixedVector64 const UpVector = (FFixedPointMath::Abs(NewX.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
			FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) : 
			FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);

		const FFixedVector64 NewY = (UpVector ^ NewX).GetSafeNormal();
		const FFixedVector64 NewZ = NewX ^ NewY;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}

	/** Builds a rotation matrix given only a YAxis. X and Z are unspecified but will be orthonormal. YAxis need not be normalized. */
	static FFixedMatrix MakeFromY(FFixedVector64 const& YAxis)
	{
		FFixedVector64 const NewY = YAxis.GetSafeNormal();

		// try to use up if possible
		FFixedVector64 const UpVector = (FFixedPointMath::Abs(NewY.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
			FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
			FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);

		const FFixedVector64 NewZ = (UpVector ^ NewY).GetSafeNormal();
		const FFixedVector64 NewX = NewY ^ NewZ;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}

	/** Builds a rotation matrix given only a ZAxis. X and Y are unspecified but will be orthonormal. ZAxis need not be normalized. */
	static FFixedMatrix MakeFromZ(FFixedVector64 const& ZAxis)
	{
		FFixedVector64 const NewZ = ZAxis.GetSafeNormal();

		// try to use up if possible
		FFixedVector64 const UpVector = (FFixedPointMath::Abs(NewZ.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ?
			FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
			FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);

		const FFixedVector64 NewX = (UpVector ^ NewZ).GetSafeNormal();
		const FFixedVector64 NewY = NewZ ^ NewX;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}

	/** Builds a matrix with given X and Y axes. X will remain fixed, Y may be changed minimally to enforce orthogonality. Z will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromXY(FFixedVector64 const& XAxis, FFixedVector64 const& YAxis)
	{
		FFixedVector64 NewX = XAxis.GetSafeNormal();
		FFixedVector64 Norm = YAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FFixedPointMath::Abs(NewX | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewX.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
				FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector64 NewZ = (NewX ^ Norm).GetSafeNormal();
		const FFixedVector64 NewY = NewZ ^ NewX;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}

	/** Builds a matrix with given X and Z axes. X will remain fixed, Z may be changed minimally to enforce orthogonality. Y will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromXZ(FFixedVector64 const& XAxis, FFixedVector64 const& ZAxis)
	{
		FFixedVector64 const NewX = XAxis.GetSafeNormal();
		FFixedVector64 Norm = ZAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FFixedPointMath::Abs(NewX | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewX.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
				FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector64 NewY = (Norm ^ NewX).GetSafeNormal();
		const FFixedVector64 NewZ = NewX ^ NewY;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}

	/** Builds a matrix with given Y and X axes. Y will remain fixed, X may be changed minimally to enforce orthogonality. Z will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromYX(FFixedVector64 const& YAxis, FFixedVector64 const& XAxis)
	{
		FFixedVector64 const NewY = YAxis.GetSafeNormal();
		FFixedVector64 Norm = XAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FMath::Abs(NewY | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewY.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
				FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector64 NewZ = (Norm ^ NewY).GetSafeNormal();
		const FFixedVector64 NewX = NewY ^ NewZ;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}

	/** Builds a matrix with given Y and Z axes. Y will remain fixed, Z may be changed minimally to enforce orthogonality. X will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromYZ(FFixedVector64 const& YAxis, FFixedVector64 const& ZAxis)
	{
		FFixedVector64 const NewY = YAxis.GetSafeNormal();
		FFixedVector64 Norm = ZAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FMath::Abs(NewY | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewY.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ?
				FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector64 NewX = (NewY ^ Norm).GetSafeNormal();
		const FFixedVector64 NewZ = NewX ^ NewY;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}

	/** Builds a matrix with given Z and X axes. Z will remain fixed, X may be changed minimally to enforce orthogonality. Y will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromZX(FFixedVector64 const& ZAxis, FFixedVector64 const& XAxis)
	{
		FFixedVector64 const NewZ = ZAxis.GetSafeNormal();
		FFixedVector64 Norm = XAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FMath::Abs(NewZ | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewZ.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ?
				FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector64 NewY = (NewZ ^ Norm).GetSafeNormal();
		const FFixedVector64 NewX = NewY ^ NewZ;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}

	/** Builds a matrix with given Z and Y axes. Z will remain fixed, Y may be changed minimally to enforce orthogonality. X will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromZY(FFixedVector64 const& ZAxis, FFixedVector64 const& YAxis)
	{
		FFixedVector64 const NewZ = ZAxis.GetSafeNormal();
		FFixedVector64 Norm = YAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FMath::Abs(NewZ | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewZ.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ?
				FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector64 NewX = (Norm ^ NewZ).GetSafeNormal();
		const FFixedVector64 NewY = NewZ ^ NewX;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector64::ZeroVector);
	}
};
