// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointFwd.h"
#include "FixedPointNumbers.h"
#include "FixedPointVector4.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedVector4d
{
public:
	GENERATED_BODY()

	/**
	* Default constructor, initializes all components to 0
	*/
	FORCEINLINE FFixedVector4d()
	{
		X = FFixed64();
		Y = FFixed64();
		Z = FFixed64();
		W = FFixed64();
	}

	/**
	* Constructor that casts FVector4d to FFixedVector4d
	*/
	FORCEINLINE FFixedVector4d(const FVector4d& inValue)
	{
		X = FFixed64(inValue.X);
		Y = FFixed64(inValue.Y);
		Z = FFixed64(inValue.Z);
		W = FFixed64(inValue.W);
	}
	
	/**
	* Sets all components to the supplied FFixed64 value
	*/
	FORCEINLINE FFixedVector4d(const FFixed64& inValue)
	{
		X = inValue;
		Y = inValue;
		Z = inValue;
		W = inValue;
	}

	/**
	* Sets components to the supplied FFixed64 values
	*/
	FORCEINLINE FFixedVector4d(const FFixed64& inX, const FFixed64& inY, const FFixed64& inZ, const FFixed64& inW)
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
	FORCEINLINE FFixedVector4d(const FFixedVector64& InVector)
		: X(InVector.X)
		, Y(InVector.Y)
		, Z(InVector.Z)
		, W(FixedPoint::Constants::Fixed64::One)
	{
	}

	/**
	 * Constructor.
	 *
	 * @param InVector 3D Vector to set first three components.
	 * @param InW W Coordinate.
	 */
	FORCEINLINE FFixedVector4d(const FFixedVector64& InVector, FFixed64 InW)
		: X(InVector.X)
		, Y(InVector.Y)
		, Z(InVector.Z)
		, W(InW)
	{
	}

	UPROPERTY(EditAnywhere)
	FFixed64 X;

	UPROPERTY(EditAnywhere)
	FFixed64 Y;

	UPROPERTY(EditAnywhere)
	FFixed64 Z;

	UPROPERTY(EditAnywhere)
	FFixed64 W;

	/**
	* Converts FFixedVector4d to FVector4d
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
		X = FFixed64(inValue.X);
		Y = FFixed64(inValue.Y);
		Z = FFixed64(inValue.Z);
		W = FFixed64(inValue.W);
	}

	FORCEINLINE bool operator==(const FFixedVector4d& Other) const
	{
		return ((X == Other.X) && (Y == Other.Y) && (Z == Other.Z) && (W == Other.W));
	}

	FORCEINLINE bool operator!=(const FFixedVector4d& Other) const
	{
		return ((X != Other.X) && (Y != Other.Y) && (Z != Other.Z) && (W != Other.W));
	}
	
	FORCEINLINE FFixedVector4d operator+(const FFixedVector4d& Other) const
	{
		return FFixedVector4d(X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W);
	}

	FORCEINLINE FFixedVector4d operator-(const FFixedVector4d& Other) const
	{
		return FFixedVector4d(X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W);
	}

	FORCEINLINE FFixedVector4d operator*(const FFixedVector4d& Other) const
	{
		return FFixedVector4d(X * Other.X, Y * Other.Y, Z * Other.Z, W * Other.W);
	}

	FORCEINLINE FFixedVector4d operator/(const FFixedVector4d& Other) const
	{
		return FFixedVector4d(X / Other.X, Y / Other.Y, Z / Other.Z, W / Other.W);
	}

	FORCEINLINE FFixedVector4d operator+(const FFixed64& Other) const
	{
		return FFixedVector4d
		(
			X + Other,
			Y + Other,
			Z + Other,
			W + Other
		);
	}

	FORCEINLINE FFixedVector4d operator-(const FFixed64& Other) const
	{
		return FFixedVector4d
		(
			X - Other,
			Y - Other,
			Z - Other,
			W - Other
		);
	}

	FORCEINLINE FFixedVector4d operator*(const FFixed64& Other) const
	{
		return FFixedVector4d
		(
			X * Other,
			Y * Other,
			Z * Other,
			W * Other
		);
	}

	FORCEINLINE FFixedVector4d operator/(const FFixed64& Other) const
	{
		return FFixedVector4d
		(
			X / Other,
			Y / Other,
			Z / Other,
			W / Other
		);
	}

	FORCEINLINE FFixedVector4d operator+=(const FFixedVector4d& Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
		W += Other.W;
		return *this;
	}

	FORCEINLINE FFixedVector4d operator-=(const FFixedVector4d& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;
		W -= Other.W;
		return *this;
	}

	FORCEINLINE FFixedVector4d operator*=(const FFixedVector4d& Other)
	{
		X *= Other.X;
		Y *= Other.Y;
		Z *= Other.Z;
		W *= Other.W;
		return *this;
	}

	FORCEINLINE FFixedVector4d operator/=(const FFixedVector4d& Other)
	{
		X /= Other.X;
		Y /= Other.Y;
		Z /= Other.Z;
		W /= Other.W;
		return *this;
	}

	FORCEINLINE FFixedVector4d operator+=(const FFixed64& Other)
	{
		X += Other;
		Y += Other;
		Z += Other;
		W += Other;
		return *this;
	}

	FORCEINLINE FFixedVector4d operator-=(const FFixed64& Other)
	{
		X -= Other;
		Y -= Other;
		Z -= Other;
		W -= Other;
		return *this;
	}

	FORCEINLINE FFixedVector4d operator*=(const FFixed64& Other)
	{
		X *= Other;
		Y *= Other;
		Z *= Other;
		W *= Other;
		return *this;
	}

	FORCEINLINE FFixedVector4d operator/=(const FFixed64& Other)
	{
		X /= Other;
		Y /= Other;
		Z /= Other;
		W /= Other;
		return *this;
	}

	FORCEINLINE FFixedVector4d operator^(const FFixedVector4d& Other)
	{
		return FFixedVector4d
		(
			(Y * Other.Z) - (Z * Other.Y),
			(Z * Other.X) - (X * Other.Z),
			(X * Other.Y) - (Y * Other.X),
			FFixed64()
		);
	}
};
