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
	FFixedRotationMatrix(const FFixedRotator& Rot)
		: FFixedRotationTranslationMatrix(Rot, FFixedVector::ZeroVector)
	{ }

	/** Matrix factory. Return an FFixedMatrix so we don't have type conversion issues in expressions. */
	static FFixedMatrix Make(FFixedRotator const& Rot)
	{
		return FFixedRotationMatrix(Rot);
	}

	/** Matrix factory. Return an FFixedMatrix so we don't have type conversion issues in expressions. */
	static FFixedMatrix Make(FFixedQuat const& Rot)
	{
		return FFixedQuatRotationTranslationMatrix(Rot, FFixedVector::ZeroVector);
	}

	/** Builds a rotation matrix given only a XAxis. Y and Z are unspecified but will be orthonormal. XAxis need not be normalized. */
	static FFixedMatrix MakeFromX(FFixedVector const& XAxis)
	{
		FFixedVector const NewX = XAxis.GetSafeNormal();

		// try to use up if possible
		FFixedVector const UpVector = (FFixedPointMath::Abs(NewX.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
			FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) : 
			FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);

		const FFixedVector NewY = (UpVector ^ NewX).GetSafeNormal();
		const FFixedVector NewZ = NewX ^ NewY;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}

	/** Builds a rotation matrix given only a YAxis. X and Z are unspecified but will be orthonormal. YAxis need not be normalized. */
	static FFixedMatrix MakeFromY(FFixedVector const& YAxis)
	{
		FFixedVector const NewY = YAxis.GetSafeNormal();

		// try to use up if possible
		FFixedVector const UpVector = (FFixedPointMath::Abs(NewY.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
			FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
			FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);

		const FFixedVector NewZ = (UpVector ^ NewY).GetSafeNormal();
		const FFixedVector NewX = NewY ^ NewZ;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}

	/** Builds a rotation matrix given only a ZAxis. X and Y are unspecified but will be orthonormal. ZAxis need not be normalized. */
	static FFixedMatrix MakeFromZ(FFixedVector const& ZAxis)
	{
		FFixedVector const NewZ = ZAxis.GetSafeNormal();

		// try to use up if possible
		FFixedVector const UpVector = (FFixedPointMath::Abs(NewZ.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ?
			FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
			FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);

		const FFixedVector NewX = (UpVector ^ NewZ).GetSafeNormal();
		const FFixedVector NewY = NewZ ^ NewX;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}

	/** Builds a matrix with given X and Y axes. X will remain fixed, Y may be changed minimally to enforce orthogonality. Z will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromXY(FFixedVector const& XAxis, FFixedVector const& YAxis)
	{
		FFixedVector NewX = XAxis.GetSafeNormal();
		FFixedVector Norm = YAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FFixedPointMath::Abs(NewX | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewX.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
				FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector NewZ = (NewX ^ Norm).GetSafeNormal();
		const FFixedVector NewY = NewZ ^ NewX;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}

	/** Builds a matrix with given X and Z axes. X will remain fixed, Z may be changed minimally to enforce orthogonality. Y will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromXZ(FFixedVector const& XAxis, FFixedVector const& ZAxis)
	{
		FFixedVector const NewX = XAxis.GetSafeNormal();
		FFixedVector Norm = ZAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FFixedPointMath::Abs(NewX | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewX.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
				FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector NewY = (Norm ^ NewX).GetSafeNormal();
		const FFixedVector NewZ = NewX ^ NewY;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}

	/** Builds a matrix with given Y and X axes. Y will remain fixed, X may be changed minimally to enforce orthogonality. Z will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromYX(FFixedVector const& YAxis, FFixedVector const& XAxis)
	{
		FFixedVector const NewY = YAxis.GetSafeNormal();
		FFixedVector Norm = XAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FMath::Abs(NewY | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewY.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ? 
				FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector NewZ = (Norm ^ NewY).GetSafeNormal();
		const FFixedVector NewX = NewY ^ NewZ;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}

	/** Builds a matrix with given Y and Z axes. Y will remain fixed, Z may be changed minimally to enforce orthogonality. X will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromYZ(FFixedVector const& YAxis, FFixedVector const& ZAxis)
	{
		FFixedVector const NewY = YAxis.GetSafeNormal();
		FFixedVector Norm = ZAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FMath::Abs(NewY | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewY.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ?
				FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector NewX = (NewY ^ Norm).GetSafeNormal();
		const FFixedVector NewZ = NewX ^ NewY;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}

	/** Builds a matrix with given Z and X axes. Z will remain fixed, X may be changed minimally to enforce orthogonality. Y will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromZX(FFixedVector const& ZAxis, FFixedVector const& XAxis)
	{
		FFixedVector const NewZ = ZAxis.GetSafeNormal();
		FFixedVector Norm = XAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FMath::Abs(NewZ | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewZ.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ?
				FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector NewY = (NewZ ^ Norm).GetSafeNormal();
		const FFixedVector NewX = NewY ^ NewZ;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}

	/** Builds a matrix with given Z and Y axes. Z will remain fixed, Y may be changed minimally to enforce orthogonality. X will be computed. Inputs need not be normalized. */
	static FFixedMatrix MakeFromZY(FFixedVector const& ZAxis, FFixedVector const& YAxis)
	{
		FFixedVector const NewZ = ZAxis.GetSafeNormal();
		FFixedVector Norm = YAxis.GetSafeNormal();

		// if they're almost same, we need to find arbitrary vector
		if (FFixedPointMath::IsNearlyEqual(FMath::Abs(NewZ | Norm), FixedPoint::Constants::Fixed64::One))
		{
			// make sure we don't ever pick the same as NewX
			Norm = (FFixedPointMath::Abs(NewZ.Z) < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::KindaSmallNumber)) ?
				FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One) :
				FFixedVector(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);
		}

		const FFixedVector NewX = (Norm ^ NewZ).GetSafeNormal();
		const FFixedVector NewY = NewZ ^ NewX;

		return FFixedMatrix(NewX, NewY, NewZ, FFixedVector::ZeroVector);
	}
};
