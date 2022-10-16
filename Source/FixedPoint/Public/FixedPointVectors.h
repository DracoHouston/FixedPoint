// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointTypes.h"
#include "FixedPointNumbers.h"
#include "FixedPointVectors.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedVector
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FFixed64 X;

	UPROPERTY(EditAnywhere)
		FFixed64 Y;

	UPROPERTY(EditAnywhere)
		FFixed64 Z;

	/**
	* Default constructor, no initialization
	*/
	FORCEINLINE FFixedVector() {}
	
	/**
	* Constructor that casts FVector to FFixedVector
	*/
	FORCEINLINE FFixedVector(const FVector& inValue)
	{
		X = inValue.X;
		Y = inValue.Y;
		Z = inValue.Z;
	}

	/**
	* Sets all components to the supplied FFixed64 value
	*/
	FORCEINLINE FFixedVector(const FFixed64& inValue)
	{
		X = inValue;
		Y = inValue;
		Z = inValue;
	}

	/**
	* Sets components to the supplied FFixed64 values
	*/
	FORCEINLINE FFixedVector(const FFixed64& inX, const FFixed64& inY, const FFixed64& inZ) : X(inX), Y(inY), Z(inZ){}

	/**
	 * Constructs a vector from an TVector2<T> and Z value.
	 *
	 * @param V Vector to copy from.
	 * @param InZ Z Coordinate.
	 */
	explicit FORCEINLINE FFixedVector(const FFixedVector2d& V, const FFixed64& InZ);

	/**
	 * Constructor using the XYZ components from a 4D vector.
	 *
	 * @param V 4D Vector to copy from.
	 */
	FORCEINLINE FFixedVector(const FFixedVector4d& V);

	explicit FORCEINLINE FFixedVector(EForceInit) : X(FixedPoint::Constants::Fixed64::Zero), Y(FixedPoint::Constants::Fixed64::Zero), Z(FixedPoint::Constants::Fixed64::Zero) {}

	

	/** Zero vector (0,0,0) */
	static const FFixedVector ZeroVector;

	/** One vector (1,1,1) */
	static const FFixedVector OneVector;

	/** Unreal up vector (0,0,1) */
	static const FFixedVector UpVector;

	/** Unreal down vector (0,0,-1) */
	static const FFixedVector DownVector;

	/** Unreal forward vector (1,0,0) */
	static const FFixedVector ForwardVector;

	/** Unreal backward vector (-1,0,0) */
	static const FFixedVector BackwardVector;

	/** Unreal right vector (0,1,0) */
	static const FFixedVector RightVector;

	/** Unreal left vector (0,-1,0) */
	static const FFixedVector LeftVector;

	/** Unit X axis vector (1,0,0) */
	static const FFixedVector XAxisVector;

	/** Unit Y axis vector (0,1,0) */
	static const FFixedVector YAxisVector;

	/** Unit Z axis vector (0,0,1) */
	static const FFixedVector ZAxisVector;

	/** @return Zero Vector (0,0,0) */
	static inline FFixedVector Zero() { return ZeroVector; }

	/** @return One Vector (1,1,1) */
	static inline FFixedVector One() { return OneVector; }

	/** @return Unit X Vector (1,0,0)  */
	static inline FFixedVector UnitX() { return XAxisVector; }

	/** @return Unit Y Vector (0,1,0)  */
	static inline FFixedVector UnitY() { return YAxisVector; }

	/** @return Unit Z Vector (0,0,1)  */
	static inline FFixedVector UnitZ() { return ZAxisVector; }

	//for interoperability with epics classes, they do nothing, ints and fixed point numbers cant be nan

	FORCEINLINE void DiagnosticCheckNaN() const {}
	FORCEINLINE void DiagnosticCheckNaN(const TCHAR* Message) const {}

	/**
	* Converts FFixedVector to FVector
	*/
	FORCEINLINE FVector GetVector() const;

	/**
	* Is Equal, will find if this and Other are within default tolerance
	*/
	//bool Equals(const FFixedVector& Other);

	/**
	* Equals, will find if this and Other are within supplied tolerance
	*/
	bool Equals(const FFixedVector& Other, const FFixed64& inTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber);

	/**
	* All Components Equal, will find if this vector's components are all equal, within supplied tolerance
	*/
	bool AllComponentsEqual(const FFixed64& inTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber);

	/**
	* All Components Equal, will find if this vector's components are all equal, within default tolerance
	*/
	//bool AllComponentsEqual();

	bool IsUnit(const FFixed64& inTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber);
	//bool IsUnit();

	FFixed64 GetMax();
	FFixed64 GetAbsMax();
	FFixed64 GetMin();
	FFixed64 GetAbsMin();

	FFixedVector GetAbs();

	FFixedVector ComponentMin(const FFixedVector& Other);
	FFixedVector ComponentMax(const FFixedVector& Other);

	FFixed64 SizeSquared();
	FFixed64 Size();


	/**
	* Sets components to the values of the components of a supplied FVector
	* Avoid doing this outside design time for the sake of cross-platform determinism
	*/
	void SetVector(const FVector& inValue);

	/**
	* Is Equal, will find if 2 FFixedVectors are within default tolerance
	*/
	//static bool IsEqual(const FFixedVector& A, const FFixedVector& B);

	/**
	* Is Equal, will find if 2 FFixedVectors are within supplied tolerance
	*/
	static bool IsEqual(const FFixedVector& A, const FFixedVector& B, const FFixed64& inTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber);

	static FFixedVector Normalize(const FFixedVector& inValue);

	static FFixed64 DistSquared(const FFixedVector& A, const FFixedVector& B);
	static FFixed64 Dist(const FFixedVector& A, const FFixedVector& B);

	static FFixedVector CrossProduct(const FFixedVector& A, const FFixedVector& B);
	static FFixedVector DotProduct(const FFixedVector& A, const FFixedVector& B);
	static FFixedVector TripleProduct(const FFixedVector& A, const FFixedVector& B, const FFixedVector& C);

	FORCEINLINE bool operator==(const FFixedVector& Other) const;
	FORCEINLINE bool operator!=(const FFixedVector& Other) const;
	FORCEINLINE FFixedVector operator-() const;
	FORCEINLINE FFixedVector operator+(const FFixedVector& Other) const;
	FORCEINLINE FFixedVector operator-(const FFixedVector& Other) const;
	FORCEINLINE FFixedVector operator*(const FFixedVector& Other) const;
	FORCEINLINE FFixedVector operator/(const FFixedVector& Other) const;
	FORCEINLINE FFixedVector operator+(const FFixed64& Other) const;
	FORCEINLINE FFixedVector operator-(const FFixed64& Other) const;
	FORCEINLINE FFixedVector operator*(const FFixed64& Other) const;
	FORCEINLINE FFixedVector operator/(const FFixed64& Other) const;

	FORCEINLINE FFixedVector operator+=(const FFixedVector& Other);
	FORCEINLINE FFixedVector operator-=(const FFixedVector& Other);
	FORCEINLINE FFixedVector operator*=(const FFixedVector& Other);
	FORCEINLINE FFixedVector operator/=(const FFixedVector& Other);
	FORCEINLINE FFixedVector operator+=(const FFixed64& Other);
	FORCEINLINE FFixedVector operator-=(const FFixed64& Other);
	FORCEINLINE FFixedVector operator*=(const FFixed64& Other);
	FORCEINLINE FFixedVector operator/=(const FFixed64& Other);

	FORCEINLINE FFixedVector operator^(const FFixedVector& Other) const;
	FORCEINLINE FFixed64 operator|(const FFixedVector& Other) const;

	FORCEINLINE operator FVector() const
	{
		return FVector((double)X,(double)Y,(double)Z);
	}
};

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedVector2d
{
public:
	GENERATED_BODY()

	/**
	* Default constructor, initializes all components to 0
	*/
	FORCEINLINE FFixedVector2d();

	/**
	* Constructor that casts FVector2d to FFixedVector2d
	*/
	FORCEINLINE FFixedVector2d(const FVector2d& inValue);
	
	/**
	* Sets all components to the supplied FFixed64 value
	*/
	FORCEINLINE FFixedVector2d(const FFixed64& inValue);

	/**
	* Sets components to the supplied FFixed64 values
	*/
	FORCEINLINE FFixedVector2d(const FFixed64& inX, const FFixed64& inY);

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
	FORCEINLINE FVector2d GetVector2d() const;

	/**
	* Sets components to the values of the components of a supplied FVector2d
	* Avoid doing this outside design time for the sake of cross-platform determinism
	*/
	void SetVector2d(const FVector2d& inValue);

	FORCEINLINE bool operator==(const FFixedVector2d& Other) const;
	FORCEINLINE bool operator!=(const FFixedVector2d& Other) const;
	FORCEINLINE FFixedVector2d operator+(const FFixedVector2d& Other) const;
	FORCEINLINE FFixedVector2d operator-(const FFixedVector2d& Other) const;
	FORCEINLINE FFixedVector2d operator*(const FFixedVector2d& Other) const;
	FORCEINLINE FFixedVector2d operator/(const FFixedVector2d& Other) const;
	FORCEINLINE FFixedVector2d operator+(const FFixed64& Other) const;
	FORCEINLINE FFixedVector2d operator-(const FFixed64& Other) const;
	FORCEINLINE FFixedVector2d operator*(const FFixed64& Other) const;
	FORCEINLINE FFixedVector2d operator/(const FFixed64& Other) const;

	FORCEINLINE FFixedVector2d operator+=(const FFixedVector2d& Other);
	FORCEINLINE FFixedVector2d operator-=(const FFixedVector2d& Other);
	FORCEINLINE FFixedVector2d operator*=(const FFixedVector2d& Other);
	FORCEINLINE FFixedVector2d operator/=(const FFixedVector2d& Other);
	FORCEINLINE FFixedVector2d operator+=(const FFixed64& Other);
	FORCEINLINE FFixedVector2d operator-=(const FFixed64& Other);
	FORCEINLINE FFixedVector2d operator*=(const FFixed64& Other);
	FORCEINLINE FFixedVector2d operator/=(const FFixed64& Other);

	FORCEINLINE FFixed64 operator^(const FFixedVector2d& Other);
	FORCEINLINE FFixed64 operator|(const FFixedVector2d& Other);
};

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedVector4d
{
public:
	GENERATED_BODY()

	/**
	* Default constructor, initializes all components to 0
	*/
	FORCEINLINE FFixedVector4d();

	/**
	* Constructor that casts FVector4d to FFixedVector4d
	*/
	FORCEINLINE FFixedVector4d(const FVector4d& inValue);
	
	/**
	* Sets all components to the supplied FFixed64 value
	*/
	FORCEINLINE FFixedVector4d(const FFixed64& inValue);

	/**
	* Sets components to the supplied FFixed64 values
	*/
	FORCEINLINE FFixedVector4d(const FFixed64& inX, const FFixed64& inY, const FFixed64& inZ, const FFixed64& inW);

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
	FORCEINLINE FVector4d GetVector4d() const;

	/**
	* Sets components to the values of the components of a supplied FVector4d
	* Avoid doing this outside design time for the sake of cross-platform determinism
	*/
	void SetVector4d(const FVector4d& inValue);

	FORCEINLINE bool operator==(const FFixedVector4d& Other) const;
	FORCEINLINE bool operator!=(const FFixedVector4d& Other) const;
	FORCEINLINE FFixedVector4d operator+(const FFixedVector4d& Other) const;
	FORCEINLINE FFixedVector4d operator-(const FFixedVector4d& Other) const;
	FORCEINLINE FFixedVector4d operator*(const FFixedVector4d& Other) const;
	FORCEINLINE FFixedVector4d operator/(const FFixedVector4d& Other) const;
	FORCEINLINE FFixedVector4d operator+(const FFixed64& Other) const;
	FORCEINLINE FFixedVector4d operator-(const FFixed64& Other) const;
	FORCEINLINE FFixedVector4d operator*(const FFixed64& Other) const;
	FORCEINLINE FFixedVector4d operator/(const FFixed64& Other) const;

	FORCEINLINE FFixedVector4d operator+=(const FFixedVector4d& Other);
	FORCEINLINE FFixedVector4d operator-=(const FFixedVector4d& Other);
	FORCEINLINE FFixedVector4d operator*=(const FFixedVector4d& Other);
	FORCEINLINE FFixedVector4d operator/=(const FFixedVector4d& Other);
	FORCEINLINE FFixedVector4d operator+=(const FFixed64& Other);
	FORCEINLINE FFixedVector4d operator-=(const FFixed64& Other);
	FORCEINLINE FFixedVector4d operator*=(const FFixed64& Other);
	FORCEINLINE FFixedVector4d operator/=(const FFixed64& Other);

	FORCEINLINE FFixedVector4d operator^(const FFixedVector4d& Other);
};

/**
* CONSTRUCTORS
*/

//FFixedVector

FORCEINLINE FFixedVector::FFixedVector(const FFixedVector2d& V, const FFixed64& InZ)
{
	X = V.X;
	Y = V.Y;
	Z = InZ;
}

FORCEINLINE FFixedVector::FFixedVector(const FFixedVector4d& V)
{
	X = V.X;
	Y = V.Y;
	Z = V.Z;
}

//FFixedVector2d

FORCEINLINE FFixedVector2d::FFixedVector2d()
{
	X = FFixed64();
	Y = FFixed64();
}

FORCEINLINE FFixedVector2d::FFixedVector2d(const FVector2d& inValue)
{
	X = FFixed64(inValue.X);
	Y = FFixed64(inValue.Y);
}

FORCEINLINE FFixedVector2d::FFixedVector2d(const FFixed64& inValue)
{
	X = inValue;
	Y = inValue;
}

FORCEINLINE FFixedVector2d::FFixedVector2d(const FFixed64& inX, const FFixed64& inY)
{
	X = inX;
	Y = inY;
}

//FFixedVector4d

FORCEINLINE FFixedVector4d::FFixedVector4d()
{
	X = FFixed64();
	Y = FFixed64();
	Z = FFixed64();
	W = FFixed64();
}

FORCEINLINE FFixedVector4d::FFixedVector4d(const FVector4d& inValue)
{
	X = FFixed64(inValue.X);
	Y = FFixed64(inValue.Y);
	Z = FFixed64(inValue.Z);
	W = FFixed64(inValue.W);
}

FORCEINLINE FFixedVector4d::FFixedVector4d(const FFixed64& inValue)
{
	X = inValue;
	Y = inValue;
	Z = inValue;
	W = inValue;
}

FORCEINLINE FFixedVector4d::FFixedVector4d(const FFixed64& inX, const FFixed64& inY, const FFixed64& inZ, const FFixed64& inW)
{
	X = inX;
	Y = inY;
	Z = inZ;
	W = inW;
}