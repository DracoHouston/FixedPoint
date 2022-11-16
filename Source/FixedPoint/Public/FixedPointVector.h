// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointFwd.h"
#include "FixedPointNumbers.h"
#include "FixedPointVector.generated.h"

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

	/**
	 * Get a copy of the vector as sign only.
	 * Each component is set to +1 or -1, with the sign of zero treated as +1.
	 *
	 * @param A copy of the vector with each component set to +1 or -1
	 */
	FORCEINLINE FFixedVector GetSignVector() const
	{
		return FFixedVector
			(
				FFixedPointMath::FloatSelect(X, FixedPoint::Constants::Fixed64::One, -FixedPoint::Constants::Fixed64::One),
				FFixedPointMath::FloatSelect(Y, FixedPoint::Constants::Fixed64::One, -FixedPoint::Constants::Fixed64::One),
				FFixedPointMath::FloatSelect(Z, FixedPoint::Constants::Fixed64::One, -FixedPoint::Constants::Fixed64::One)
			);
	}

	/**
	 * Projects 2D components of vector based on Z.
	 *
	 * @return Projected version of vector based on Z.
	 */
	FORCEINLINE FFixedVector Projection() const
	{
		const FFixed64 RZ = FixedPoint::Constants::Fixed64::One / Z;
		return FFixedVector(X * RZ, Y * RZ, FixedPoint::Constants::Fixed64::One);
	}

	/**
	 * Gets a copy of this vector snapped to a grid.
	 *
	 * @param GridSz Grid dimension.
	 * @return A copy of this vector snapped to a grid.
	 * @see FMath::GridSnap()
	 */
	FORCEINLINE FFixedVector GridSnap(const FFixed64& GridSz) const
	{
		return FFixedVector(FFixedPointMath::GridSnap(X, GridSz), FFixedPointMath::GridSnap(Y, GridSz), FFixedPointMath::GridSnap(Z, GridSz));
	}

	/**
	 * Get a copy of this vector, clamped inside of a cube.
	 *
	 * @param Radius Half size of the cube.
	 * @return A copy of this vector, bound by cube.
	 */
	FORCEINLINE FFixedVector BoundToCube(FFixed64 Radius) const
	{
		return FFixedVector
			(
				FFixedPointMath::Clamp(X, -Radius, Radius),
				FFixedPointMath::Clamp(Y, -Radius, Radius),
				FFixedPointMath::Clamp(Z, -Radius, Radius)
			);
	}

	/** Get a copy of this vector, clamped inside of a cube. */
	FORCEINLINE FFixedVector BoundToBox(const FFixedVector& Min, const FFixedVector& Max) const
	{
		return FFixedVector
			(
				FFixedPointMath::Clamp(X, Min.X, Max.X),
				FFixedPointMath::Clamp(Y, Min.Y, Max.Y),
				FFixedPointMath::Clamp(Z, Min.Z, Max.Z)
			);
	}

	/** Create a copy of this vector, with its magnitude clamped between Min and Max. */
	FORCEINLINE FFixedVector GetClampedToSize(FFixed64 Min, FFixed64 Max) const
	{
		FFixed64 VecSize = Size();
		const FFixedVector VecDir = (VecSize > FixedPoint::Constants::Fixed64::SmallNumber) ? (*this / VecSize) : ZeroVector;

		VecSize = FFixedPointMath::Clamp(VecSize, Min, Max);

		return VecDir * VecSize;
	}

	/** Create a copy of this vector, with the 2D magnitude clamped between Min and Max. Z is unchanged. */
	FORCEINLINE FFixedVector GetClampedToSize2D(FFixed64 Min, FFixed64 Max) const
	{
		FFixed64 VecSize2D = Size2D();
		const FFixedVector VecDir = (VecSize2D > FixedPoint::Constants::Fixed64::SmallNumber) ? (*this / VecSize2D) : ZeroVector;

		VecSize2D = FFixedPointMath::Clamp(VecSize2D, Min, Max);

		return FFixedVector(VecSize2D * VecDir.X, VecSize2D * VecDir.Y, Z);
	}

	/** Create a copy of this vector, with its maximum magnitude clamped to MaxSize. */
	FORCEINLINE FFixedVector GetClampedToMaxSize(FFixed64 MaxSize) const
	{
		if (MaxSize < FixedPoint::Constants::Fixed64::KindaSmallNumber)
		{
			return ZeroVector;
		}

		const FFixed64 VSq = SizeSquared();
		if (VSq > FFixedPointMath::Square(MaxSize))
		{
			const FFixed64 Scale = MaxSize * FFixedPointMath::InvSqrt(VSq);
			return FFixedVector(X * Scale, Y * Scale, Z * Scale);
		}
		else
		{
			return *this;
		}
	}

	/** Create a copy of this vector, with the maximum 2D magnitude clamped to MaxSize. Z is unchanged. */
	FORCEINLINE FFixedVector GetClampedToMaxSize2D(FFixed64 MaxSize) const
	{
		if (MaxSize < FixedPoint::Constants::Fixed64::KindaSmallNumber)
		{
			return FFixedVector(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, Z);
		}

		const FFixed64 VSq2D = SizeSquared2D();
		if (VSq2D > FFixedPointMath::Square(MaxSize))
		{
			const FFixed64 Scale = MaxSize * FFixedPointMath::InvSqrt(VSq2D);
			return FFixedVector(X * Scale, Y * Scale, Z);
		}
		else
		{
			return *this;
		}
	}

	/**
	 * Add a vector to this and clamp the result in a cube.
	 *
	 * @param V Vector to add.
	 * @param Radius Half size of the cube.
	 */
	FORCEINLINE void AddBounded(const FFixedVector& V, FFixed64 Radius = MAX_int16)
	{
		*this = (*this + V).BoundToCube(Radius);
	}

	/**
	 * Gets the reciprocal of this vector, avoiding division by zero.
	 * Zero components are set to BIG_NUMBER.
	 *
	 * @return Reciprocal of this vector.
	 */
	FORCEINLINE FFixedVector Reciprocal() const
	{
		FFixedVector RecVector;
		if (X != FixedPoint::Constants::Fixed64::Zero)
		{
			RecVector.X = FixedPoint::Constants::Fixed64::One / X;
		}
		else
		{
			RecVector.X = FixedPoint::Constants::Fixed64::BigNumber;
		}
		if (Y != FixedPoint::Constants::Fixed64::Zero)
		{
			RecVector.Y = FixedPoint::Constants::Fixed64::One / Y;
		}
		else
		{
			RecVector.Y = FixedPoint::Constants::Fixed64::BigNumber;
		}
		if (Z != FixedPoint::Constants::Fixed64::Zero)
		{
			RecVector.Z = FixedPoint::Constants::Fixed64::One / Z;
		}
		else
		{
			RecVector.Z = FixedPoint::Constants::Fixed64::BigNumber;
		}

		return RecVector;
	}

	/**
	 * Check whether X, Y and Z are nearly equal.
	 *
	 * @param Tolerance Specified Tolerance.
	 * @return true if X == Y == Z within the specified tolerance.
	 */
	FORCEINLINE bool IsUniform(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return AllComponentsEqual(Tolerance);
	}

	//FIXME: NEED FIXED PLANE STRUCT

	/**
	 * Mirrors a vector about a plane.
	 *
	 * @param Plane Plane to mirror about.
	 * @return Mirrored vector.
	 */
	//FFixedVector MirrorByPlane(const FFixedPlane& Plane) const;

	/**
	 * Calculate the projection of a point on the given plane.
	 *
	 * @param Point The point to project onto the plane
	 * @param Plane The plane
	 * @return Projection of Point onto Plane
	 */
	//static FFixedVector PointPlaneProject(const FFixedVector& Point, const FFixedPlane& Plane);

	/**
	 * Calculate the projection of a point on the plane defined by counter-clockwise (CCW) points A,B,C.
	 *
	 * @param Point The point to project onto the plane
	 * @param A 1st of three points in CCW order defining the plane
	 * @param B 2nd of three points in CCW order defining the plane
	 * @param C 3rd of three points in CCW order defining the plane
	 * @return Projection of Point onto plane ABC
	 */
	//static FFixedVector PointPlaneProject(const FFixedVector& Point, const FFixedVector& A, const FFixedVector& B, const FFixedVector& C);

	/**
	 * Rotates around Axis (assumes Axis.Size() == 1).
	 *
	 * @param AngleRad Angle to rotate (in radians).
	 * @param Axis Axis to rotate around.
	 * @return Rotated Vector.
	 */
	FORCEINLINE FFixedVector RotateAngleAxisRad(const FFixed64 AngleRad, const FFixedVector& Axis) const
	{
		FFixed64 S, C;
		FFixedPointMath::SinCos(&S, &C, AngleRad);

		const FFixed64 XX = Axis.X * Axis.X;
		const FFixed64 YY = Axis.Y * Axis.Y;
		const FFixed64 ZZ = Axis.Z * Axis.Z;
			  
		const FFixed64 XY = Axis.X * Axis.Y;
		const FFixed64 YZ = Axis.Y * Axis.Z;
		const FFixed64 ZX = Axis.Z * Axis.X;
			  
		const FFixed64 XS = Axis.X * S;
		const FFixed64 YS = Axis.Y * S;
		const FFixed64 ZS = Axis.Z * S;
			  
		const FFixed64 OMC = FixedPoint::Constants::Fixed64::One - C;

		return FFixedVector(
			(OMC * XX + C) * X + (OMC * XY - ZS) * Y + (OMC * ZX + YS) * Z,
			(OMC * XY + ZS) * X + (OMC * YY + C) * Y + (OMC * YZ - XS) * Z,
			(OMC * ZX - YS) * X + (OMC * YZ + XS) * Y + (OMC * ZZ + C) * Z
			);
	}

	/**
	 * Rotates around Axis (assumes Axis.Size() == 1).
	 *
	 * @param AngleDeg Angle to rotate (in degrees).
	 * @param Axis Axis to rotate around.
	 * @return Rotated Vector.
	 */
	FORCEINLINE FFixedVector RotateAngleAxis(const FFixed64 AngleDeg, const FFixedVector& Axis) const
	{
		return RotateAngleAxisRad(FFixedPointMath::DegreesToRadians(AngleDeg), Axis);
	}

	/**
	 * Returns the cosine of the angle between this vector and another projected onto the XY plane (no Z).
	 *
	 * @param B the other vector to find the 2D cosine of the angle with.
	 * @return The cosine.
	 */
	FORCEINLINE FFixed64 CosineAngle2D(FFixedVector B) const
	{
		FFixedVector A(*this);
		A.Z = 0.0f;
		B.Z = 0.0f;
		A.Normalize();
		B.Normalize();
		return A | B;
	}

	/**
	 * Gets a copy of this vector projected onto the input vector.
	 *
	 * @param A	Vector to project onto, does not assume it is normalized.
	 * @return Projected vector.
	 */
	FORCEINLINE FFixedVector ProjectOnTo(const FFixedVector& A) const
	{
		return (A * ((*this | A) / (A | A)));
	}

	/**
	 * Gets a copy of this vector projected onto the input vector, which is assumed to be unit length.
	 *
	 * @param  Normal Vector to project onto (assumed to be unit length).
	 * @return Projected vector.
	 */
	FORCEINLINE FFixedVector ProjectOnToNormal(const FFixedVector& Normal) const
	{
		return (Normal * (*this | Normal));
	}

	/**
	 * Return the TRotator orientation corresponding to the direction in which the vector points.
	 * Sets Yaw and Pitch to the proper numbers, and sets Roll to zero because the roll can'T be determined from a vector.
	 *
	 * @return TRotator from the Vector's direction, without any roll.
	 * @see ToOrientationQuat()
	 */
	//CORE_API TRotator<T> ToOrientationRotator() const;

	/**
	 * Return the Quaternion orientation corresponding to the direction in which the vector points.
	 * Similar to the UE::Math::TRotator<T> version, returns a result without roll such that it preserves the up vector.
	 *
	 * @note If you don'T care about preserving the up vector and just want the most direct rotation, you can use the faster
	 * 'FQuat::FindBetweenVectors(FVector::ForwardVector, YourVector)' or 'FQuat::FindBetweenNormals(...)' if you know the vector is of unit length.
	 *
	 * @return Quaternion from the Vector's direction, without any roll.
	 * @see ToOrientationRotator(), FQuat::FindBetweenVectors()
	 */
	//CORE_API TQuat<T> ToOrientationQuat() const;

	/**
	 * Return the UE::Math::TRotator<T> orientation corresponding to the direction in which the vector points.
	 * Sets Yaw and Pitch to the proper numbers, and sets Roll to zero because the roll can't be determined from a vector.
	 * @note Identical to 'ToOrientationRotator()' and preserved for legacy reasons.
	 * @return UE::Math::TRotator<T> from the Vector's direction.
	 * @see ToOrientationRotator(), ToOrientationQuat()
	 */
	/*FORCEINLINE UE::Math::TRotator<T> Rotation() const
	{
		return ToOrientationRotator();
	}*/

	/**
	 * Find good arbitrary axis vectors to represent U and V axes of a plane,
	 * using this vector as the normal of the plane.
	 *
	 * @param Axis1 Reference to first axis.
	 * @param Axis2 Reference to second axis.
	 */
	void FindBestAxisVectors(FFixedVector& Axis1, FFixedVector& Axis2) const
	{
		const FFixed64 NX = FFixedPointMath::Abs(X);
		const FFixed64 NY = FFixedPointMath::Abs(Y);
		const FFixed64 NZ = FFixedPointMath::Abs(Z);

		// Find best basis vectors.
		if (NZ > NX && NZ > NY)	Axis1 = FFixedVector(1, 0, 0);
		else					Axis1 = FFixedVector(0, 0, 1);

		FFixedVector Tmp = Axis1 - *this * (Axis1 | *this);
		Axis1 = Tmp.GetSafeNormal();
		Axis2 = Axis1 ^ *this;
	}

	/** When this vector contains Euler angles (degrees), ensure that angles are between +/-180 */
	void UnwindEuler()
	{
		X = FFixedPointMath::UnwindDegrees(X);
		Y = FFixedPointMath::UnwindDegrees(Y);
		Z = FFixedPointMath::UnwindDegrees(Z);
	}

	/**
	 * Utility to check if there are any non-finite values (NaN or Inf) in this vector.
	 *
	 * @return true if there are any non-finite values in this vector, false otherwise.
	 */
	FORCEINLINE bool ContainsNaN() const
	{
		return false;//no such thing as a nan fixed point number, friend.
	}

	/**
	 * Get a textual representation of this vector.
	 *
	 * @return A string describing the vector.
	 */
	FORCEINLINE FString ToString() const
	{
		return ((FVector)*this).ToString();
	}

	/**
	* Get a locale aware textual representation of this vector.
	*
	* @return A string describing the vector.
	*/
	FORCEINLINE FText ToText() const
	{
		return ((FVector)*this).ToText();
	}

	/** Get a short textural representation of this vector, for compact readable logging. */
	FORCEINLINE FString ToCompactString() const
	{
		return ((FVector)*this).ToCompactString();
	}

	/** Get a short locale aware textural representation of this vector, for compact readable logging. */
	FORCEINLINE FText ToCompactText() const
	{
		return ((FVector)*this).ToCompactText();
	}

	/**
	 * Initialize this Vector based on an FString. The String is expected to contain X=, Y=, Z=.
	 * The TVector<T> will be bogus when InitFromString returns false.
	 *
	 * @param	InSourceString	FString containing the vector values.
	 * @return true if the X,Y,Z values were read successfully; false otherwise.
	 */
	FORCEINLINE bool InitFromString(const FString& InSourceString)
	{
		FVector parsedvector;
		if (parsedvector.InitFromString(InSourceString))
		{
			*this = FFixedVector(parsedvector);
			return true;
		}
		return false;
	}

	/**
	 * Initialize this Vector based on an FString. The String is expected to contain V(0)
	 * or at least one value X=, Y=, Z=, previously produced by ToCompactString()
	 * The TVector<T> will be bogus when InitFromString returns false.
	 *
	 * @param	InSourceString	FString containing the vector values.
	 * @return true if any of the X,Y,Z values were read successfully; false otherwise.
	 */
	FORCEINLINE bool InitFromCompactString(const FString& InSourceString)
	{
		FVector parsedvector;
		if (parsedvector.InitFromCompactString(InSourceString))
		{
			*this = FFixedVector(parsedvector);
			return true;
		}
		return false;
	}

	/**
	 * Converts a Cartesian unit vector into spherical coordinates on the unit sphere.
	 * @return Output Theta will be in the range [0, PI], and output Phi will be in the range [-PI, PI].
	 */
	FFixedVector2d UnitCartesianToSpherical() const;

	/**
	 * Convert a direction vector into a 'heading' angle.
	 *
	 * @return 'Heading' angle between +/-PI. 0 is pointing down +X.
	 */
	FFixed64 HeadingAngle() const
	{
		// Project Dir into Z plane.
		FFixedVector PlaneDir = *this;
		PlaneDir.Z = 0.f;
		PlaneDir = PlaneDir.GetSafeNormal();

		FFixed64 Angle = FFixedPointMath::Acos(PlaneDir.X);

		if (PlaneDir.Y < FixedPoint::Constants::Fixed64::Zero)
		{
			Angle *= -FixedPoint::Constants::Fixed64::One;
		}

		return Angle;
	}

	/**
	 * Create an orthonormal basis from a basis with at least two orthogonal vectors.
	 * It may change the directions of the X and Y axes to make the basis orthogonal,
	 * but it won'T change the direction of the Z axis.
	 * All axes will be normalized.
	 *
	 * @param XAxis The input basis' XAxis, and upon return the orthonormal basis' XAxis.
	 * @param YAxis The input basis' YAxis, and upon return the orthonormal basis' YAxis.
	 * @param ZAxis The input basis' ZAxis, and upon return the orthonormal basis' ZAxis.
	 */
	static void CreateOrthonormalBasis(FFixedVector& XAxis, FFixedVector& YAxis, FFixedVector& ZAxis)
	{
		// Project the X and Y axes onto the plane perpendicular to the Z axis.
		XAxis -= ZAxis * (ZAxis | ZAxis) / (XAxis | ZAxis);
		YAxis -= ZAxis * (ZAxis | ZAxis) / (YAxis | ZAxis);

		// If the X axis was parallel to the Z axis, choose a vector which is orthogonal to the Y and Z axes.
		if (XAxis.SizeSquared() <= FixedPoint::Constants::Fixed64::SmallNumber)
		{
			XAxis = YAxis ^ ZAxis;
		}

		// If the Y axis was parallel to the Z axis, choose a vector which is orthogonal to the X and Z axes.
		if (YAxis.SizeSquared() <= FixedPoint::Constants::Fixed64::SmallNumber)
		{
			YAxis = XAxis ^ ZAxis;
		}

		// Normalize the basis vectors.
		XAxis.Normalize();
		YAxis.Normalize();
		ZAxis.Normalize();
	}

	/**
	 * Compare two points and see if they're the same, using a threshold.
	 *
	 * @param P First vector.
	 * @param Q Second vector.
	 * @return Whether points are the same within a threshold. Uses fast distance approximation (linear per-component distance).
	 */
	FORCEINLINE static bool PointsAreSame(const FFixedVector& P, const FFixedVector& Q)
	{
		FFixed64 Temp;
		Temp = P.X - Q.X;
		if ((Temp > -FixedPoint::Constants::Fixed64::ThreshPointsAreSame) && (Temp < FixedPoint::Constants::Fixed64::ThreshPointsAreSame))
		{
			Temp = P.Y - Q.Y;
			if ((Temp > -FixedPoint::Constants::Fixed64::ThreshPointsAreSame) && (Temp < FixedPoint::Constants::Fixed64::ThreshPointsAreSame))
			{
				Temp = P.Z - Q.Z;
				if ((Temp > -FixedPoint::Constants::Fixed64::ThreshPointsAreSame) && (Temp < FixedPoint::Constants::Fixed64::ThreshPointsAreSame))
				{
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Compare two points and see if they're within specified distance.
	 *
	 * @param Point1 First vector.
	 * @param Point2 Second vector.
	 * @param Dist Specified distance.
	 * @return Whether two points are within the specified distance. Uses fast distance approximation (linear per-component distance).
	 */
	static bool PointsAreNear(const FFixedVector& Point1, const FFixedVector& Point2, FFixed64 Dist)
	{
		FFixed64 Temp;
		Temp = (Point1.X - Point2.X); if (FFixedPointMath::Abs(Temp) >= Dist) return false;
		Temp = (Point1.Y - Point2.Y); if (FFixedPointMath::Abs(Temp) >= Dist) return false;
		Temp = (Point1.Z - Point2.Z); if (FFixedPointMath::Abs(Temp) >= Dist) return false;
		return true;
	}

	/**
	 * Calculate the signed distance (in the direction of the normal) between a point and a plane.
	 *
	 * @param Point The Point we are checking.
	 * @param PlaneBase The Base Point in the plane.
	 * @param PlaneNormal The Normal of the plane (assumed to be unit length).
	 * @return Signed distance between point and plane.
	 */
	FORCEINLINE static FFixed64 PointPlaneDist(const FFixedVector& Point, const FFixedVector& PlaneBase, const FFixedVector& PlaneNormal)
	{
		return (Point - PlaneBase) | PlaneNormal;
	}

	/**
	 * Compute pushout of a box from a plane.
	 *
	 * @param Normal The plane normal.
	 * @param Size The size of the box.
	 * @return Pushout required.
	 */
	static FORCEINLINE FFixed64 BoxPushOut(const FFixedVector& Normal, const FFixedVector& Size)
	{
		return FFixedPointMath::Abs(Normal.X * Size.X) + FFixedPointMath::Abs(Normal.Y * Size.Y) + FFixedPointMath::Abs(Normal.Z * Size.Z);
	}

	/**
	 * Min, Max, Min3, Max3 like FMath
	 */
	static FORCEINLINE FFixedVector Min(const FFixedVector& A, const FFixedVector& B)
	{
		return FFixedVector(
			FFixedPointMath::Min(A.X, B.X),
			FFixedPointMath::Min(A.Y, B.Y),
			FFixedPointMath::Min(A.Z, B.Z)
			);
	}

	static FORCEINLINE FFixedVector Max(const FFixedVector& A, const FFixedVector& B)
	{
		return FFixedVector(
			FFixedPointMath::Max(A.X, B.X),
			FFixedPointMath::Max(A.Y, B.Y),
			FFixedPointMath::Max(A.Z, B.Z)
			);
	}

	static FORCEINLINE FFixedVector Min3(const FFixedVector& A, const FFixedVector& B, const FFixedVector& C)
	{
		return FFixedVector(
			FFixedPointMath::Min3(A.X, B.X, C.X),
			FFixedPointMath::Min3(A.Y, B.Y, C.Y),
			FFixedPointMath::Min3(A.Z, B.Z, C.Z)
			);
	}

	static FORCEINLINE FFixedVector Max3(const FFixedVector& A, const FFixedVector& B, const FFixedVector& C)
	{
		return FFixedVector(
			FFixedPointMath::Max3(A.X, B.X, C.X),
			FFixedPointMath::Max3(A.Y, B.Y, C.Y),
			FFixedPointMath::Max3(A.Z, B.Z, C.Z)
			);
	}

	/**
	 * See if two normal vectors are nearly parallel, meaning the angle between them is close to 0 degrees.
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal1 Second normalized vector.
	 * @param  ParallelCosineThreshold Normals are parallel if absolute value of dot product (cosine of angle between them) is greater than or equal to this. For example: cos(1.0 degrees).
	 * @return true if vectors are nearly parallel, false otherwise.
	 */
	FORCEINLINE static bool Parallel(const FFixedVector& Normal1, const FFixedVector& Normal2, FFixed64 ParallelCosineThreshold = FixedPoint::Constants::Fixed64::ThreshNormalsAreParallel)
	{
		const FFixed64 NormalDot = Normal1 | Normal2;
		return FFixedPointMath::Abs(NormalDot) >= ParallelCosineThreshold;
	}

	/**
	 * See if two normal vectors are coincident (nearly parallel and point in the same direction).
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal2 Second normalized vector.
	 * @param  ParallelCosineThreshold Normals are coincident if dot product (cosine of angle between them) is greater than or equal to this. For example: cos(1.0 degrees).
	 * @return true if vectors are coincident (nearly parallel and point in the same direction), false otherwise.
	 */
	FORCEINLINE static bool Coincident(const FFixedVector& Normal1, const FFixedVector& Normal2, FFixed64 ParallelCosineThreshold = FixedPoint::Constants::Fixed64::ThreshNormalsAreParallel)
	{
		const FFixed64 NormalDot = Normal1 | Normal2;
		return NormalDot >= ParallelCosineThreshold;
	}

	/**
	 * See if two normal vectors are nearly orthogonal (perpendicular), meaning the angle between them is close to 90 degrees.
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal2 Second normalized vector.
	 * @param  OrthogonalCosineThreshold Normals are orthogonal if absolute value of dot product (cosine of angle between them) is less than or equal to this. For example: cos(89.0 degrees).
	 * @return true if vectors are orthogonal (perpendicular), false otherwise.
	 */
	FORCEINLINE static bool Orthogonal(const FFixedVector& Normal1, const FFixedVector& Normal2, FFixed64 OrthogonalCosineThreshold = FixedPoint::Constants::Fixed64::ThreshNormalsAreOrthogonal)
	{
		const FFixed64 NormalDot = Normal1 | Normal2;
		return FFixedPointMath::Abs(NormalDot) <= OrthogonalCosineThreshold;
	}

	/**
	 * See if two planes are coplanar. They are coplanar if the normals are nearly parallel and the planes include the same set of points.
	 *
	 * @param Base1 The base point in the first plane.
	 * @param Normal1 The normal of the first plane.
	 * @param Base2 The base point in the second plane.
	 * @param Normal2 The normal of the second plane.
	 * @param ParallelCosineThreshold Normals are parallel if absolute value of dot product is greater than or equal to this.
	 * @return true if the planes are coplanar, false otherwise.
	 */
	static bool Coplanar(const FFixedVector& Base1, const FFixedVector& Normal1, const FFixedVector& Base2, const FFixedVector& Normal2, FFixed64 ParallelCosineThreshold = FixedPoint::Constants::Fixed64::ThreshNormalsAreParallel)
	{
		if (!FFixedVector::Parallel(Normal1, Normal2, ParallelCosineThreshold)) return false;
		else if (FFixedPointMath::Abs(FFixedVector::PointPlaneDist(Base2, Base1, Normal1)) > FixedPoint::Constants::Fixed64::ThreshPointOnPlane) return false;
		else return true;
	}

	FORCEINLINE operator FVector() const
	{
		return FVector((double)X,(double)Y,(double)Z);
	}
};

FORCEINLINE FFixedVector operator*(FFixed64 Scale, const FFixedVector& V)
{
	return V.operator*(Scale);
}

template<>
struct TCustomLerp<FFixedVector>
{
	enum { Value = true };

	static FORCEINLINE_DEBUGGABLE FFixedVector Lerp(const FFixedVector& A, const FFixedVector& B, const FFixed64& Alpha)
	{
		return A + Alpha * (B - A);
	}
};
