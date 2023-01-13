// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatVector4D64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicVector4D64
{
public:
	GENERATED_BODY()

	/**
	* Default constructor, initializes all components to 0
	*/
	FORCEINLINE FDeterministicVector4D64()
	{
		X = FDeterministicNumber64();
		Y = FDeterministicNumber64();
		Z = FDeterministicNumber64();
		W = FDeterministicNumber64();
	}

	/**
	* Constructor that casts FVector4d to FDeterministicVector4D64
	*/
	FORCEINLINE FDeterministicVector4D64(const FVector4d& inValue)
	{
		X = FDeterministicNumber64(inValue.X);
		Y = FDeterministicNumber64(inValue.Y);
		Z = FDeterministicNumber64(inValue.Z);
		W = FDeterministicNumber64(inValue.W);
	}
	
	/**
	* Sets all components to the supplied FDeterministicNumber64 value
	*/
	FORCEINLINE FDeterministicVector4D64(const FDeterministicNumber64& inValue)
	{
		X = inValue;
		Y = inValue;
		Z = inValue;
		W = inValue;
	}

	/**
	* Sets components to the supplied FDeterministicNumber64 values
	*/
	FORCEINLINE FDeterministicVector4D64(const FDeterministicNumber64& inX, const FDeterministicNumber64& inY, const FDeterministicNumber64& inZ, const FDeterministicNumber64& inW)
	{
		X = inX;
		Y = inY;
		Z = inZ;
		W = inW;
	}

	/**
	 * Constructor from 3D TVector. W is set to 1.
	 *
	 * @param InVector 3D Vector to set first three components.
	 */
	FORCEINLINE FDeterministicVector4D64(const FDeterministicVector64& InVector)
		: X(InVector.X)
		, Y(InVector.Y)
		, Z(InVector.Z)
		, W(DeterministicFloat::Constants::Number64::One)
	{
	}

	/**
	 * Constructor.
	 *
	 * @param InVector 3D Vector to set first three components.
	 * @param InW W Coordinate.
	 */
	FORCEINLINE FDeterministicVector4D64(const FDeterministicVector64& InVector, FDeterministicNumber64 InW)
		: X(InVector.X)
		, Y(InVector.Y)
		, Z(InVector.Z)
		, W(InW)
	{
	}

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 X;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Y;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Z;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 W;

	/**
	* Converts FDeterministicVector4D64 to FVector4d
	*/
	FORCEINLINE FVector4d GetVector4d() const
	{
		return FVector4d((double)X, (double)Y, (double)Z, (double)W);
	}

	/**
	* Sets components to the values of the components of a supplied FVector4d
	* Avoid doing this outside design time for the sake of cross-platform determinism
	*/
	void SetVector4d(const FVector4d& inValue)
	{
		X = FDeterministicNumber64(inValue.X);
		Y = FDeterministicNumber64(inValue.Y);
		Z = FDeterministicNumber64(inValue.Z);
		W = FDeterministicNumber64(inValue.W);
	}

	FORCEINLINE bool operator==(const FDeterministicVector4D64& Other) const
	{
		return ((X == Other.X) && (Y == Other.Y) && (Z == Other.Z) && (W == Other.W));
	}

	FORCEINLINE bool operator!=(const FDeterministicVector4D64& Other) const
	{
		return ((X != Other.X) && (Y != Other.Y) && (Z != Other.Z) && (W != Other.W));
	}
	
	FORCEINLINE FDeterministicVector4D64 operator+(const FDeterministicVector4D64& Other) const
	{
		return FDeterministicVector4D64(X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W);
	}

	FORCEINLINE FDeterministicVector4D64 operator-(const FDeterministicVector4D64& Other) const
	{
		return FDeterministicVector4D64(X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W);
	}

	FORCEINLINE FDeterministicVector4D64 operator*(const FDeterministicVector4D64& Other) const
	{
		return FDeterministicVector4D64(X * Other.X, Y * Other.Y, Z * Other.Z, W * Other.W);
	}

	FORCEINLINE FDeterministicVector4D64 operator/(const FDeterministicVector4D64& Other) const
	{
		return FDeterministicVector4D64(X / Other.X, Y / Other.Y, Z / Other.Z, W / Other.W);
	}

	FORCEINLINE FDeterministicVector4D64 operator+(const FDeterministicNumber64& Other) const
	{
		return FDeterministicVector4D64
		(
			X + Other,
			Y + Other,
			Z + Other,
			W + Other
		);
	}

	FORCEINLINE FDeterministicVector4D64 operator-(const FDeterministicNumber64& Other) const
	{
		return FDeterministicVector4D64
		(
			X - Other,
			Y - Other,
			Z - Other,
			W - Other
		);
	}

	FORCEINLINE FDeterministicVector4D64 operator*(const FDeterministicNumber64& Other) const
	{
		return FDeterministicVector4D64
		(
			X * Other,
			Y * Other,
			Z * Other,
			W * Other
		);
	}

	FORCEINLINE FDeterministicVector4D64 operator/(const FDeterministicNumber64& Other) const
	{
		return FDeterministicVector4D64
		(
			X / Other,
			Y / Other,
			Z / Other,
			W / Other
		);
	}

	FORCEINLINE FDeterministicVector4D64 operator+=(const FDeterministicVector4D64& Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
		W += Other.W;
		return *this;
	}

	FORCEINLINE FDeterministicVector4D64 operator-=(const FDeterministicVector4D64& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;
		W -= Other.W;
		return *this;
	}

	FORCEINLINE FDeterministicVector4D64 operator*=(const FDeterministicVector4D64& Other)
	{
		X *= Other.X;
		Y *= Other.Y;
		Z *= Other.Z;
		W *= Other.W;
		return *this;
	}

	FORCEINLINE FDeterministicVector4D64 operator/=(const FDeterministicVector4D64& Other)
	{
		X /= Other.X;
		Y /= Other.Y;
		Z /= Other.Z;
		W /= Other.W;
		return *this;
	}

	FORCEINLINE FDeterministicVector4D64 operator+=(const FDeterministicNumber64& Other)
	{
		X += Other;
		Y += Other;
		Z += Other;
		W += Other;
		return *this;
	}

	FORCEINLINE FDeterministicVector4D64 operator-=(const FDeterministicNumber64& Other)
	{
		X -= Other;
		Y -= Other;
		Z -= Other;
		W -= Other;
		return *this;
	}

	FORCEINLINE FDeterministicVector4D64 operator*=(const FDeterministicNumber64& Other)
	{
		X *= Other;
		Y *= Other;
		Z *= Other;
		W *= Other;
		return *this;
	}

	FORCEINLINE FDeterministicVector4D64 operator/=(const FDeterministicNumber64& Other)
	{
		X /= Other;
		Y /= Other;
		Z /= Other;
		W /= Other;
		return *this;
	}

	FORCEINLINE FDeterministicVector4D64 operator^(const FDeterministicVector4D64& Other)
	{
		return FDeterministicVector4D64
		(
			(Y * Other.Z) - (Z * Other.Y),
			(Z * Other.X) - (X * Other.Z),
			(X * Other.Y) - (Y * Other.X),
			FDeterministicNumber64()
		);
	}

	/**
	 * Returns a normalized copy of the vector if safe to normalize.
	 *
	 * @param Tolerance Minimum squared length of vector for normalization.
	 * @return A normalized copy of the vector or a zero vector.
	 */
	FORCEINLINE FDeterministicVector4D64 GetSafeNormal(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber) const
	{
		const FDeterministicNumber64 SquareSum = X * X + Y * Y + Z * Z;
		if (SquareSum > Tolerance)
		{
			const FDeterministicNumber64 Scale = FDeterministicFloatMath::InvSqrt(SquareSum);
			return FDeterministicVector4D64(X * Scale, Y * Scale, Z * Scale, 0.0f);
		}
		return FDeterministicVector4D64(DeterministicFloat::Constants::Number64::Zero);
	}
};
