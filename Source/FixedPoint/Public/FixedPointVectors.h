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

	//for interoperability with epics classes, they do nothing, ints and fixed point numbers can't be nan

	FORCEINLINE void DiagnosticCheckNaN() const {}
	FORCEINLINE void DiagnosticCheckNaN(const TCHAR* Message) const {}

	/**
	* Equals, will find if this and Other are within supplied tolerance
	*/
	FORCEINLINE bool Equals(const FFixedVector& Other, const FFixed64& inTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return FFixedVector::IsEqual(*this, Other, inTolerance);
	}

	/**
	* All Components Equal, will find if this vector's components are all equal, within supplied tolerance
	*/
	FORCEINLINE bool AllComponentsEqual(const FFixed64& inTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return FFixedPointMath::IsEqual(X, Y, inTolerance) && FFixedPointMath::IsEqual(X, Z, inTolerance) && FFixedPointMath::IsEqual(Y, Z, inTolerance);
	}


	/**
	 * Get the maximum value of the vector's components.
	 *
	 * @return The maximum value of the vector's components.
	 */
	FORCEINLINE FFixed64 GetMax() const
	{
		return FFixedPointMath::Max(FFixedPointMath::Max(X, Y), Z);
	}

	/**
	 * Get the maximum absolute value of the vector's components.
	 *
	 * @return The maximum absolute value of the vector's components.
	 */
	FORCEINLINE FFixed64 GetAbsMax() const
	{
		return FFixedPointMath::Max(FFixedPointMath::Max(FFixedPointMath::Abs(X), FFixedPointMath::Abs(Y)), FFixedPointMath::Abs(Z));
	}

	/**
	 * Get the minimum value of the vector's components.
	 *
	 * @return The minimum value of the vector's components.
	 */
	FORCEINLINE FFixed64 GetMin() const
	{
		return FFixedPointMath::Min(FFixedPointMath::Min(X, Y), Z);
	}

	/**
	 * Get the minimum absolute value of the vector's components.
	 *
	 * @return The minimum absolute value of the vector's components.
	 */
	FORCEINLINE FFixed64 GetAbsMin() const
	{
		return FFixedPointMath::Min(FFixedPointMath::Min(FFixedPointMath::Abs(X), FFixedPointMath::Abs(Y)), FFixedPointMath::Abs(Z));
	}

	/**
	 * Get a copy of this vector with absolute value of each component.
	 *
	 * @return A copy of this vector with absolute value of each component.
	 */
	FORCEINLINE FFixedVector GetAbs() const
	{
		return FFixedVector(FFixedPointMath::Abs(X), FFixedPointMath::Abs(Y), FFixedPointMath::Abs(Z));
	}

	/** Gets the component-wise min of two vectors. */
	FORCEINLINE FFixedVector ComponentMin(const FFixedVector& Other) const
	{
		return FFixedVector(FFixedPointMath::Min(X, Other.X), FFixedPointMath::Min(Y, Other.Y), FFixedPointMath::Min(Z, Other.Z));
	}

	/** Gets the component-wise max of two vectors. */
	FORCEINLINE FFixedVector ComponentMax(const FFixedVector& Other) const
	{
		return FFixedVector(FFixedPointMath::Max(X, Other.X), FFixedPointMath::Max(Y, Other.Y), FFixedPointMath::Max(Z, Other.Z));
	}

	FORCEINLINE FFixed64 SizeSquared() const
	{
		return (X * X) + (Y * Y) + (Z * Z);
	}

	FORCEINLINE FFixed64 Size() const
	{
		return FFixedPointMath::Sqrt(SizeSquared());
	}

	/**
	 * Get the length of the 2D components of this vector.
	 *
	 * @return The 2D length of this vector.
	 */
	FORCEINLINE FFixed64 Size2D() const
	{
		return FFixedPointMath::Sqrt(X * X + Y * Y);
	}

	/**
	 * Get the squared length of the 2D components of this vector.
	 *
	 * @return The squared 2D length of this vector.
	 */
	FORCEINLINE FFixed64 SizeSquared2D() const
	{
		return X * X + Y * Y;
	}

	/**
	 * Checks whether vector is near to zero within a specified tolerance.
	 *
	 * @param Tolerance Error tolerance.
	 * @return true if the vector is near to zero, false otherwise.
	 */
	FORCEINLINE bool IsNearlyZero(const FFixed64& Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return
			FFixedPointMath::Abs(X) <= Tolerance
			&& FFixedPointMath::Abs(Y) <= Tolerance
			&& FFixedPointMath::Abs(Z) <= Tolerance;
	}

	/**
	 * Checks whether all components of the vector are exactly zero.
	 *
	 * @return true if the vector is exactly zero, false otherwise.
	 */
	FORCEINLINE bool IsZero() const
	{
		return X == FixedPoint::Constants::Fixed64::Zero && Y == FixedPoint::Constants::Fixed64::Zero && Z == FixedPoint::Constants::Fixed64::Zero;
	}

	/**
	 * Check if the vector is of unit length, with specified tolerance.
	 *
	 * @param LengthSquaredTolerance Tolerance against squared length.
	 * @return true if the vector is a unit vector within the specified tolerance.
	 */
	FORCEINLINE bool IsUnit(const FFixed64& LengthSquaredTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return FFixedPointMath::Abs(FixedPoint::Constants::Fixed64::One - SizeSquared()) < LengthSquaredTolerance;
	}

	/**
	 * Checks whether vector is normalized.
	 *
	 * @return true if normalized, false otherwise.
	 */
	FORCEINLINE bool IsNormalized() const
	{
		return (FFixedPointMath::Abs(FixedPoint::Constants::Fixed64::One - SizeSquared()) < FixedPoint::Constants::Fixed64::ThreshVectorNormalized);
	}

	/**
	* Is Equal, will find if 2 FFixedVectors are within supplied tolerance
	*/
	FORCEINLINE static bool IsEqual(const FFixedVector& A, const FFixedVector& B, const FFixed64& inTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber)
	{
		return FFixedPointMath::IsEqual(A.X, B.X, inTolerance) && FFixedPointMath::IsEqual(A.Y, B.Y, inTolerance) && FFixedPointMath::IsEqual(A.Z, B.Z, inTolerance);
	}

	/**
	 * Normalize this vector in-place if it is larger than a given tolerance. Leaves it unchanged if not.
	 *
	 * @param Tolerance Minimum squared length of vector for normalization.
	 * @return true if the vector was normalized correctly, false otherwise.
	 */
	FORCEINLINE bool Normalize(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		const FFixed64 SquareSum = (X * X) + (Y * Y) + (Z * Z);
		if (SquareSum > Tolerance)
		{
			const FFixed64 Scale = FFixedPointMath::InvSqrt(SquareSum);
			X *= Scale; Y *= Scale; Z *= Scale;
			return true;
		}
		return false;
	}

	/**
	 * Squared distance between two points.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The squared distance between two points.
	 */
	FORCEINLINE static FFixed64 DistSquared(const FFixedVector& A, const FFixedVector& B)
	{
		return FFixedPointMath::Square(B.X - A.X) + FFixedPointMath::Square(B.Y - A.Y) + FFixedPointMath::Square(B.Z - A.Z);
	}
	
	/**
	 * Euclidean distance between two points.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The distance between two points.
	 */
	FORCEINLINE static FFixed64 Dist(const FFixedVector& A, const FFixedVector& B)
	{
		return FFixedPointMath::Sqrt(FFixedVector::DistSquared(A, B));
	}
	static FORCEINLINE FFixed64 Distance(const FFixedVector& V1, const FFixedVector& V2) { return Dist(V1, V2); }

	/**
	 * Squared distance between two points in the XY plane only.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The squared distance between two points in the XY plane
	 */
	static FORCEINLINE FFixed64 DistSquaredXY(const FFixedVector& V1, const FFixedVector& V2)
	{
		return FMath::Square(V2.X - V1.X) + FMath::Square(V2.Y - V1.Y);
	}
	static FORCEINLINE FFixed64 DistSquared2D(const FFixedVector& V1, const FFixedVector& V2) { return DistSquaredXY(V1, V2); }

	/**
	* Euclidean distance between two points in the XY plane (ignoring Z).
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The distance between two points in the XY plane.
	*/
	static FORCEINLINE FFixed64 DistXY(const FFixedVector& V1, const FFixedVector& V2)
	{
		return FFixedPointMath::Sqrt(DistSquaredXY(V1, V2));
	}
	static FORCEINLINE FFixed64 Dist2D(const FFixedVector& V1, const FFixedVector& V2) { return DistXY(V1, V2); }

	FORCEINLINE static FFixedVector CrossProduct(const FFixedVector& A, const FFixedVector& B)
	{
		return A ^ B;
	}

	FORCEINLINE static FFixedVector DotProduct(const FFixedVector& A, const FFixedVector& B)
	{
		return A | B;
	}

	/**
	 * Triple product of three vectors: X dot (Y cross Z).
	 *
	 * @param X The first vector.
	 * @param Y The second vector.
	 * @param Z The third vector.
	 * @return The triple product: X dot (Y cross Z).
	 */
	FORCEINLINE static FFixedVector Triple(const FFixedVector& X, const FFixedVector& Y, const FFixedVector& Z)
	{
		return
			((X.X * (Y.Y * Z.Z - Y.Z * Z.Y))
				+ (X.Y * (Y.Z * Z.X - Y.X * Z.Z))
				+ (X.Z * (Y.X * Z.Y - Y.Y * Z.X)));
	}

	FORCEINLINE bool operator==(const FFixedVector& Other) const
	{
		return ((X == Other.X) && (Y == Other.Y) && (Z == Other.Z));
	}

	FORCEINLINE bool operator!=(const FFixedVector& Other) const
	{
		return ((X != Other.X) && (Y != Other.Y) && (Z != Other.Z));
	}

	FORCEINLINE FFixedVector operator-() const
	{
		return FFixedVector(-X, -Y, -Z);
	}

	FORCEINLINE FFixedVector operator+(const FFixedVector& Other) const
	{
		return FFixedVector(X + Other.X, Y + Other.Y, Z + Other.Z);
	}

	FORCEINLINE FFixedVector operator-(const FFixedVector& Other) const 
	{
		return FFixedVector(X - Other.X, Y - Other.Y, Z - Other.Z);
	}

	FORCEINLINE FFixedVector operator*(const FFixedVector& Other) const
	{
		return FFixedVector(X * Other.X, Y * Other.Y, Z * Other.Z);
	}

	FORCEINLINE FFixedVector operator/(const FFixedVector& Other) const
	{
		return FFixedVector(X / Other.X, Y / Other.Y, Z / Other.Z);
	}

	FORCEINLINE FFixedVector operator+(const FFixed64& Other) const
	{
		return FFixedVector(X + Other, Y + Other, Z + Other);
	}

	FORCEINLINE FFixedVector operator-(const FFixed64& Other) const
	{
		return FFixedVector(X - Other, Y - Other, Z - Other);
	}

	FORCEINLINE FFixedVector operator*(const FFixed64& Other) const
	{
		return FFixedVector(X * Other, Y * Other, Z * Other);
	}

	FORCEINLINE FFixedVector operator/(const FFixed64& Other) const
	{
		return FFixedVector(X / Other, Y / Other, Z / Other);
	}

	FORCEINLINE FFixedVector operator+=(const FFixedVector& Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
		return *this;
	}

	FORCEINLINE FFixedVector operator-=(const FFixedVector& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;
		return *this;
	}

	FORCEINLINE FFixedVector operator*=(const FFixedVector& Other)
	{
		X *= Other.X;
		Y *= Other.Y;
		Z *= Other.Z;
		return *this;
	}

	FORCEINLINE FFixedVector operator/=(const FFixedVector& Other)
	{
		X /= Other.X;
		Y /= Other.Y;
		Z /= Other.Z;
		return *this;
	}

	FORCEINLINE FFixedVector operator+=(const FFixed64& Other)
	{
		X += Other;
		Y += Other;
		Z += Other;
		return *this;
	}

	FORCEINLINE FFixedVector operator-=(const FFixed64& Other)
	{
		X -= Other;
		Y -= Other;
		Z -= Other;
		return *this;
	}

	FORCEINLINE FFixedVector operator*=(const FFixed64& Other)
	{
		X *= Other;
		Y *= Other;
		Z *= Other;
		return *this;
	}

	FORCEINLINE FFixedVector operator/=(const FFixed64& Other)
	{
		X /= Other;
		Y /= Other;
		Z /= Other;
		return *this;
	}

	FORCEINLINE FFixedVector operator^(const FFixedVector& Other) const
	{
		return FFixedVector
		(
			(Y * Other.Z) - (Z * Other.Y),
			(Z * Other.X) - (X * Other.Z),
			(X * Other.Y) - (Y * Other.X)
		);
	}

	FORCEINLINE FFixed64 operator|(const FFixedVector& Other) const
	{
		return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z);
	}

	/**
	 * Gets specific component of the vector.
	 *
	 * @param Index the index of vector component
	 * @return reference to component.
	 */
	FORCEINLINE FFixed64& operator[](int32 Index)
	{
		switch (Index)
		{
		case 0:
			return X;
		case 1:
			return Y;
		case 2:
			return Z;
		}
		return X;
		
	}

	/**
	 * Gets specific component of the vector.
	 *
	 * @param Index the index of vector component
	 * @return Copy of the component.
	 */
	FORCEINLINE FFixed64 operator[](int32 Index)const
	{
		{
			switch (Index)
			{
			case 0:
				return X;
			case 1:
				return Y;
			case 2:
				return Z;
			}
			return X;
		}
	}

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	*
	* @return Reference to the specified component.
	*/
	FORCEINLINE FFixed64& Component(int32 Index)
	{
		switch (Index)
		{
		case 0:
			return X;
		case 1:
			return Y;
		case 2:
			return Z;
		}
		return X;
	}

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	* @return Copy of the specified component.
	*/
	FORCEINLINE FFixed64 Component(int32 Index) const
	{
		switch (Index)
		{
		case 0:
			return X;
		case 1:
			return Y;
		case 2:
			return Z;
		}
		return X;
	}


	/** Get a specific component of the vector, given a specific axis by enum */
	FORCEINLINE FFixed64 GetComponentForAxis(EAxis::Type Axis) const
	{
		switch (Axis)
		{
		case EAxis::X:
			return X;
		case EAxis::Y:
			return Y;
		case EAxis::Z:
			return Z;
		}
		return X;
	}

	/** Set a specified componet of the vector, given a specific axis by enum */
	FORCEINLINE void SetComponentForAxis(EAxis::Type Axis, const FFixed64& Component)
	{
		switch (Axis)
		{
		case EAxis::X:
			X = Component;
			return;
		case EAxis::Y:
			Y = Component;
			return;
		case EAxis::Z:
			Z = Component;
			return;
		}
	}

	/**
	* Set the values of the vector directly.
	*
	* @param InX New X coordinate.
	* @param InY New Y coordinate.
	* @param InZ New Z coordinate.
	*/
	FORCEINLINE void Set(const FFixed64& InX, const FFixed64& InY, const FFixed64& InZ)
	{
		X = InX;
		Y = InY;
		Z = InZ;
	}

	/**
	 * Calculates normalized version of vector without checking for zero length.
	 *
	 * @return Normalized version of vector.
	 * @see GetSafeNormal()
	 */
	FORCEINLINE FFixedVector GetUnsafeNormal() const
	{
		const FFixed64 Scale = FFixedPointMath::InvSqrt(X * X + Y * Y + Z * Z);
		return FFixedVector(X * Scale, Y * Scale, Z * Scale);
	}

	/**
	 * Gets a normalized copy of the vector, checking it is safe to do so based on the length.
	 * Returns zero vector by default if vector length is too small to safely normalize.
	 *
	 * @param Tolerance Minimum squared vector length.
	 * @return A normalized copy if safe, ResultIfZero otherwise.
	 */
	FORCEINLINE FFixedVector GetSafeNormal(const FFixed64& Tolerance = FixedPoint::Constants::Fixed64::SmallNumber, const FFixedVector& ResultIfZero = ZeroVector) const
	{
		const FFixed64 SquareSum = X * X + Y * Y + Z * Z;

		// Not sure if it's safe to add tolerance in there. Might introduce too many errors
		if (SquareSum == FixedPoint::Constants::Fixed64::One)
		{
			return *this;
		}
		else if (SquareSum < Tolerance)
		{
			return ResultIfZero;
		}
		const FFixed64 Scale = FFixedPointMath::InvSqrt(SquareSum);
		return FFixedVector(X * Scale, Y * Scale, Z * Scale);
	}

	/**
	* Calculates normalized 2D version of vector without checking for zero length.
	*
	* @return Normalized version of vector.
	* @see GetSafeNormal2D()
	*/
	FORCEINLINE FFixedVector GetUnsafeNormal2D() const
	{
		const FFixed64 Scale = FFixedPointMath::InvSqrt(X * X + Y * Y);
		return FFixedVector(X * Scale, Y * Scale, FixedPoint::Constants::Fixed64::Zero);
	}

	/**
	 * Gets a normalized copy of the 2D components of the vector, checking it is safe to do so. Z is set to zero.
	 * Returns zero vector by default if vector length is too small to normalize.
	 *
	 * @param Tolerance Minimum squared vector length.
	 * @return Normalized copy if safe, otherwise returns ResultIfZero.
	 */
	FORCEINLINE FFixedVector GetSafeNormal2D(const FFixed64& Tolerance = FixedPoint::Constants::Fixed64::SmallNumber, const FFixedVector& ResultIfZero = ZeroVector) const
	{
		const FFixed64 SquareSum = X * X + Y * Y;

		// Not sure if it's safe to add tolerance in there. Might introduce too many errors
		if (SquareSum == FixedPoint::Constants::Fixed64::One)
		{
			if (Z == FixedPoint::Constants::Fixed64::Zero)
			{
				return *this;
			}
			else
			{
				return FFixedVector(X, Y, 0.f);
			}
		}
		else if (SquareSum < Tolerance)
		{
			return ResultIfZero;
		}

		const FFixed64 Scale = FFixedPointMath::InvSqrt(SquareSum);
		return FFixedVector(X * Scale, Y * Scale, 0.f);
	}

	/**
	 * Util to convert this vector into a unit direction vector and its original length.
	 *
	 * @param OutDir Reference passed in to store unit direction vector.
	 * @param OutLength Reference passed in to store length of the vector.
	 */
	FORCEINLINE void ToDirectionAndLength(FFixedVector& OutDir, FFixed64& OutLength) const
	{
		OutLength = Size();
		if (OutLength > FixedPoint::Constants::Fixed64::SmallNumber)
		{
			FFixed64 OneOverLength = FixedPoint::Constants::Fixed64::One / OutLength;
			OutDir = FFixedVector(X * OneOverLength, Y * OneOverLength, Z * OneOverLength);
		}
		else
		{
			OutDir = ZeroVector;
		}
	}

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