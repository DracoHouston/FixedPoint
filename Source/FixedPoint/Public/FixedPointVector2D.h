// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointFwd.h"
#include "FixedPointVector2D.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedVector2d
{
public:
	GENERATED_BODY()

	/**
	* Default constructor, initializes all components to 0
	*/
	FORCEINLINE FFixedVector2d()
	{
		X = FFixed64();
		Y = FFixed64();
	}

	/**
	* Constructor that casts FVector2d to FFixedVector2d
	*/
	FORCEINLINE FFixedVector2d(const FVector2d& inValue)
	{
		X = FFixed64(inValue.X);
		Y = FFixed64(inValue.Y);
	}
	
	/**
	* Sets all components to the supplied FFixed64 value
	*/
	FORCEINLINE FFixedVector2d(const FFixed64& inValue)
	{
		X = inValue;
		Y = inValue;
	}

	/**
	* Sets components to the supplied FFixed64 values
	*/
	FORCEINLINE FFixedVector2d(const FFixed64& inX, const FFixed64& inY)
	{
		X = inX;
		Y = inY;
	}

	UPROPERTY(EditAnywhere)
	FFixed64 X;

	UPROPERTY(EditAnywhere)
	FFixed64 Y;

	/** Global 2D zero vector constant (0,0) */
	//static const FFixedVector2d ZeroVector;

	/**
	* Global 2D one vector (poorly named) constant (1,1).
	*
	* @note Incorrectly named "unit" vector though its magnitude/length/size is not one. Would fix, though likely used all over the world. Use `Unit45Deg` below for an actual unit vector.
	*/
	//static const FFixedVector2d UnitVector;

	/**
	* Global 2D unit vector constant along the 45 degree angle or symmetrical positive axes (sqrt(.5),sqrt(.5)) or (.707,.707). https://en.wikipedia.org/wiki/Unit_vector
	*
	* @note The `UnitVector` above is actually a value with axes of 1 rather than a magnitude of one.
	*/
	//static const FFixedVector2d Unit45Deg;

//	static inline FFixedVector2d Zero() { return ZeroVector; }
	//static inline FFixedVector2d One() { return UnitVector; }
	static inline FFixedVector2d UnitX() { return FFixedVector2d((int64)1, (int64)0); }
	static inline FFixedVector2d UnitY() { return FFixedVector2d((int64)0, (int64)1); }

	/**
	* Converts FFixedVector2d to FVector2d
	*/
	FORCEINLINE FVector2d GetVector2d() const
	{
		return FVector2d((double)X, (double)Y);
	}

	/**
	* Sets components to the values of the components of a supplied FVector2d
	* Avoid doing this outside design time for the sake of cross-platform determinism
	*/
	void SetVector2d(const FVector2d& inValue)
	{
		X = FFixed64(inValue.X);
		Y = FFixed64(inValue.Y);
	}

	FORCEINLINE bool operator==(const FFixedVector2d& Other) const
	{
		return ((X == Other.X) && (Y == Other.Y));
	}

	FORCEINLINE bool operator!=(const FFixedVector2d& Other) const
	{
		return ((X != Other.X) && (Y != Other.Y));
	}

	FORCEINLINE FFixedVector2d operator+(const FFixedVector2d& Other) const
	{
		return FFixedVector2d(X + Other.X, Y + Other.Y);
	}

	FORCEINLINE FFixedVector2d operator-(const FFixedVector2d& Other) const
	{
		return FFixedVector2d(X - Other.X, Y - Other.Y);
	}

	FORCEINLINE FFixedVector2d operator*(const FFixedVector2d& Other) const
	{
		return FFixedVector2d((X * Other.X).Value, (Y * Other.Y).Value);
	}

	FORCEINLINE FFixedVector2d operator/(const FFixedVector2d& Other) const
	{
		return FFixedVector2d((X / Other.X).Value, (Y / Other.Y).Value);
	}

	FORCEINLINE FFixedVector2d operator+(const FFixed64& Other) const
	{
		return FFixedVector2d(X + Other, Y + Other);
	}

	FORCEINLINE FFixedVector2d operator-(const FFixed64& Other) const
	{
		return FFixedVector2d(X - Other, Y - Other);
	}

	FORCEINLINE FFixedVector2d operator*(const FFixed64& Other) const
	{
		return FFixedVector2d(X * Other, Y * Other);
	}

	FORCEINLINE FFixedVector2d operator/(const FFixed64& Other) const
	{
		return FFixedVector2d(X / Other, Y / Other);
	}

	FORCEINLINE FFixedVector2d operator+=(const FFixedVector2d& Other)
	{
		X += Other.X;
		Y += Other.Y;
		return *this;
	}

	FORCEINLINE FFixedVector2d operator-=(const FFixedVector2d& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		return *this;
	}

	FORCEINLINE FFixedVector2d operator*=(const FFixedVector2d& Other)
	{
		X *= Other.X;
		Y *= Other.Y;
		return *this;
	}

	FORCEINLINE FFixedVector2d operator/=(const FFixedVector2d& Other)
	{
		X /= Other.X;
		Y /= Other.Y;
		return *this;
	}

	FORCEINLINE FFixedVector2d operator+=(const FFixed64& Other)
	{
		X += Other;
		Y += Other;
		return *this;
	}

	FORCEINLINE FFixedVector2d operator-=(const FFixed64& Other)
	{
		X -= Other;
		Y -= Other;
		return *this;
	}

	FORCEINLINE FFixedVector2d operator*=(const FFixed64& Other)
	{
		X *= Other;
		Y *= Other;
		return *this;
	}

	FORCEINLINE FFixedVector2d operator/=(const FFixed64& Other)
	{
		X /= Other;
		Y /= Other;
		return *this;
	}

	FORCEINLINE FFixed64 operator^(const FFixedVector2d& Other)
	{
		return (X * Other.X) + (Y * Other.Y);
	}
	
	FORCEINLINE FFixed64 operator|(const FFixedVector2d& Other)
	{
		return (X * Other.Y) - (Y * Other.X);
	}
};