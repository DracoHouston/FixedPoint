// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatVector2D64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicVector2D64
{
public:
	GENERATED_BODY()

	/**
	* Default constructor, initializes all components to 0
	*/
	FORCEINLINE FDeterministicVector2D64()
	{
		X = FDeterministicNumber64();
		Y = FDeterministicNumber64();
	}

	/**
	* Constructor that casts FVector2d to FDeterministicVector2D64
	*/
	FORCEINLINE FDeterministicVector2D64(const FVector2d& inValue)
	{
		X = FDeterministicNumber64(inValue.X);
		Y = FDeterministicNumber64(inValue.Y);
	}
	
	/**
	* Sets all components to the supplied FDeterministicNumber64 value
	*/
	FORCEINLINE FDeterministicVector2D64(const FDeterministicNumber64& inValue)
	{
		X = inValue;
		Y = inValue;
	}

	/**
	* Sets components to the supplied FDeterministicNumber64 values
	*/
	FORCEINLINE FDeterministicVector2D64(const FDeterministicNumber64& inX, const FDeterministicNumber64& inY)
	{
		X = inX;
		Y = inY;
	}

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 X;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Y;

	/** Global 2D zero vector constant (0,0) */
	//static const FDeterministicVector2D64 ZeroVector;

	/**
	* Global 2D one vector (poorly named) constant (1,1).
	*
	* @note Incorrectly named "unit" vector though its magnitude/length/size is not one. Would fix, though likely used all over the world. Use `Unit45Deg` below for an actual unit vector.
	*/
	//static const FDeterministicVector2D64 UnitVector;

	/**
	* Global 2D unit vector constant along the 45 degree angle or symmetrical positive axes (sqrt(.5),sqrt(.5)) or (.707,.707). https://en.wikipedia.org/wiki/Unit_vector
	*
	* @note The `UnitVector` above is actually a value with axes of 1 rather than a magnitude of one.
	*/
	//static const FDeterministicVector2D64 Unit45Deg;

//	static inline FDeterministicVector2D64 Zero() { return ZeroVector; }
	//static inline FDeterministicVector2D64 One() { return UnitVector; }
	static inline FDeterministicVector2D64 UnitX() { return FDeterministicVector2D64((int64)1, (int64)0); }
	static inline FDeterministicVector2D64 UnitY() { return FDeterministicVector2D64((int64)0, (int64)1); }

	/**
	* Converts FDeterministicVector2D64 to FVector2d
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
		X = FDeterministicNumber64(inValue.X);
		Y = FDeterministicNumber64(inValue.Y);
	}

	FORCEINLINE bool operator==(const FDeterministicVector2D64& Other) const
	{
		return ((X == Other.X) && (Y == Other.Y));
	}

	FORCEINLINE bool operator!=(const FDeterministicVector2D64& Other) const
	{
		return ((X != Other.X) && (Y != Other.Y));
	}

	FORCEINLINE FDeterministicVector2D64 operator+(const FDeterministicVector2D64& Other) const
	{
		return FDeterministicVector2D64(X + Other.X, Y + Other.Y);
	}

	FORCEINLINE FDeterministicVector2D64 operator-(const FDeterministicVector2D64& Other) const
	{
		return FDeterministicVector2D64(X - Other.X, Y - Other.Y);
	}

	FORCEINLINE FDeterministicVector2D64 operator*(const FDeterministicVector2D64& Other) const
	{
		return FDeterministicVector2D64((X * Other.X).Value, (Y * Other.Y).Value);
	}

	FORCEINLINE FDeterministicVector2D64 operator/(const FDeterministicVector2D64& Other) const
	{
		return FDeterministicVector2D64((X / Other.X).Value, (Y / Other.Y).Value);
	}

	FORCEINLINE FDeterministicVector2D64 operator+(const FDeterministicNumber64& Other) const
	{
		return FDeterministicVector2D64(X + Other, Y + Other);
	}

	FORCEINLINE FDeterministicVector2D64 operator-(const FDeterministicNumber64& Other) const
	{
		return FDeterministicVector2D64(X - Other, Y - Other);
	}

	FORCEINLINE FDeterministicVector2D64 operator*(const FDeterministicNumber64& Other) const
	{
		return FDeterministicVector2D64(X * Other, Y * Other);
	}

	FORCEINLINE FDeterministicVector2D64 operator/(const FDeterministicNumber64& Other) const
	{
		return FDeterministicVector2D64(X / Other, Y / Other);
	}

	FORCEINLINE FDeterministicVector2D64 operator+=(const FDeterministicVector2D64& Other)
	{
		X += Other.X;
		Y += Other.Y;
		return *this;
	}

	FORCEINLINE FDeterministicVector2D64 operator-=(const FDeterministicVector2D64& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		return *this;
	}

	FORCEINLINE FDeterministicVector2D64 operator*=(const FDeterministicVector2D64& Other)
	{
		X *= Other.X;
		Y *= Other.Y;
		return *this;
	}

	FORCEINLINE FDeterministicVector2D64 operator/=(const FDeterministicVector2D64& Other)
	{
		X /= Other.X;
		Y /= Other.Y;
		return *this;
	}

	FORCEINLINE FDeterministicVector2D64 operator+=(const FDeterministicNumber64& Other)
	{
		X += Other;
		Y += Other;
		return *this;
	}

	FORCEINLINE FDeterministicVector2D64 operator-=(const FDeterministicNumber64& Other)
	{
		X -= Other;
		Y -= Other;
		return *this;
	}

	FORCEINLINE FDeterministicVector2D64 operator*=(const FDeterministicNumber64& Other)
	{
		X *= Other;
		Y *= Other;
		return *this;
	}

	FORCEINLINE FDeterministicVector2D64 operator/=(const FDeterministicNumber64& Other)
	{
		X /= Other;
		Y /= Other;
		return *this;
	}

	FORCEINLINE FDeterministicNumber64 operator^(const FDeterministicVector2D64& Other)
	{
		return (X * Other.X) + (Y * Other.Y);
	}
	
	FORCEINLINE FDeterministicNumber64 operator|(const FDeterministicVector2D64& Other)
	{
		return (X * Other.Y) - (Y * Other.X);
	}
};