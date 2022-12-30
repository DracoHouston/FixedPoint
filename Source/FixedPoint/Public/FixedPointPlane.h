// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointVector.h"
#include "FixedPointPlane.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedPlane : public FFixedVector64
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FFixed64 W;

	/** Default constructor (no initialization). */
	FORCEINLINE FFixedPlane() {}

	/**
	 * Constructor.
	 *
	 * @param V 4D vector to set up plane.
	 */
	FORCEINLINE FFixedPlane(const FFixedVector4d& V) : FFixedVector64(V), W(V.W) {}

	/**
	 * Constructor.
	 *
	 * @param InX X-coefficient.
	 * @param InY Y-coefficient.
	 * @param InZ Z-coefficient.
	 * @param InW W-coefficient.
	 */
	FORCEINLINE FFixedPlane(FFixed64 InX, FFixed64 InY, FFixed64 InZ, FFixed64 InW) : FFixedVector64(InX, InY, InZ), W(InW)
	{
	}

	/**
	 * Constructor.
	 *
	 * @param InNormal Plane Normal Vector.
	 * @param InW Plane W-coefficient.
	 */
	FORCEINLINE FFixedPlane(FFixedVector64 InNormal, FFixed64 InW) : FFixedVector64(InNormal), W(InW)
	{
	}

	/**
	 * Constructor.
	 *
	 * @param InBase Base point in plane.
	 * @param InNormal Plane Normal Vector.
	 */
	FORCEINLINE FFixedPlane(FFixedVector64 InBase, const FFixedVector64& InNormal) : FFixedVector64(InNormal), W(InBase | InNormal)
	{
	}

	/**
	 * Constructor.
	 *
	 * @param A First point in the plane.
	 * @param B Second point in the plane.
	 * @param C Third point in the plane.
	 */
	FFixedPlane(FFixedVector64 A, FFixedVector64 B, FFixedVector64 C) : FFixedVector64(((B - A) ^ (C - A)).GetSafeNormal())
	{
		W = A | (FFixedVector64)(*this);
	}

	/**
	 * Constructor
	 *
	 * @param EForceInit Force Init Enum.
	 */
	explicit FORCEINLINE FFixedPlane(EForceInit)
		: FFixedVector64(FixedPoint::Constants::Fixed64::Zero), W(FixedPoint::Constants::Fixed64::Zero)
	{}

	/**
	 * Checks if this plane is valid (ie: if it has a non-zero normal).
	 *
	 * @return true if the plane is well-defined (has a non-zero normal), otherwise false.
	 */
	FORCEINLINE bool IsValid() const
	{
		return !this->IsNearlyZero();
	}

	/**
	 * Get the origin of this plane.
	 *
	 * @return The origin (base point) of this plane.
	 */
	FORCEINLINE FFixedVector64 GetOrigin() const
	{
		return GetNormal() * W;
	}

	/**
	 * Get the normal of this plane.
	 *
	 * @return The normal of this plane.
	 */
	FORCEINLINE const FFixedVector64& GetNormal() const
	{
		return *this;
	}


	/**
	 * Calculates distance between plane and a point.
	 *
	 * @param P The other point.
	 * @return The distance from the plane to the point. 0: Point is on the plane. >0: Point is in front of the plane. <0: Point is behind the plane.
	 */
	FORCEINLINE FFixed64 PlaneDot(const FFixedVector64& P) const
	{
		return X * P.X + Y * P.Y + Z * P.Z - W;
	}

	/**
	 * Normalize this plane in-place if it is larger than a given tolerance. Leaves it unchanged if not.
	 *
	 * @param Tolerance Minimum squared length of vector for normalization.
	 * @return true if the plane was normalized correctly, false otherwise.
	 */
	bool Normalize(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		const FFixed64 SquareSum = X * X + Y * Y + Z * Z;
		if (SquareSum > Tolerance)
		{
			const FFixed64 Scale = FFixedPointMath::InvSqrt(SquareSum);
			X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
			return true;
		}
		return false;
	}

	/**
	 * Get a flipped version of the plane.
	 *
	 * @return A flipped version of the plane.
	 */
	FFixedPlane Flip() const
	{
		return FFixedPlane(-X, -Y, -Z, -W);
	}

	/**
	 * Get the result of transforming the plane by a Matrix.
	 *
	 * @param M The matrix to transform plane with.
	 * @return The result of transform.
	 */
	FORCEINLINE FFixedPlane TransformBy(const FFixedMatrix& M) const;

	/**
	 * You can optionally pass in the matrices transpose-adjoint, which save it recalculating it.
	 * MSM: If we are going to save the transpose-adjoint we should also save the more expensive
	 * determinant.
	 *
	 * @param M The Matrix to transform plane with.
	 * @param DetM Determinant of Matrix.
	 * @param TA Transpose-adjoint of Matrix.
	 * @return The result of transform.
	 */
	FORCEINLINE FFixedPlane TransformByUsingAdjointT(const FFixedMatrix& M, FFixed64 DetM, const FFixedMatrix& TA) const { return FFixedPlane(); }

	/**
	 * Get the result of translating the plane by the given offset
	 *
	 * @param V The translation amount
	 * @return The result of transform.
	 */
	FORCEINLINE FFixedPlane TranslateBy(const FFixedVector64& V) const
	{
		return FFixedPlane(GetOrigin() + V, GetNormal());
	}

	/**
	 * Check if two planes are identical.
	 *
	 * @param V The other plane.
	 * @return true if planes are identical, otherwise false.
	 */
	FORCEINLINE bool operator==(const FFixedPlane& V) const
	{
		return (X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W);
	}

	/**
	 * Check if two planes are different.
	 *
	 * @param V The other plane.
	 * @return true if planes are different, otherwise false.
	 */
	FORCEINLINE bool operator!=(const FFixedPlane& V) const
	{
		return (X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W);
	}

	/**
	 * Checks whether two planes are equal within specified tolerance.
	 *
	 * @param V The other plane.
	 * @param Tolerance Error Tolerance.
	 * @return true if the two planes are equal within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FFixedPlane& V, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return (FFixedPointMath::Abs(X - V.X) < Tolerance) && (FFixedPointMath::Abs(Y - V.Y) < Tolerance) && (FFixedPointMath::Abs(Z - V.Z) < Tolerance) && (FFixedPointMath::Abs(W - V.W) < Tolerance);
	}

	/**
	 * Calculates dot product of two planes.
	 *
	 * @param V The other plane.
	 * @return The dot product.
	 */
	FORCEINLINE FFixed64 operator|(const FFixedPlane& V) const
	{
		return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
	}

	/**
	 * Gets result of adding a plane to this.
	 *
	 * @param V The other plane.
	 * @return The result of adding a plane to this.
	 */
	FORCEINLINE FFixedPlane operator+(const FFixedPlane& V) const
	{
		return FFixedPlane(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
	}

	/**
	 * Gets result of subtracting a plane from this.
	 *
	 * @param V The other plane.
	 * @return The result of subtracting a plane from this.
	 */
	FORCEINLINE FFixedPlane operator-(const FFixedPlane& V) const
	{
		return FFixedPlane(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
	}

	/**
	 * Gets result of dividing a plane.
	 *
	 * @param Scale What to divide by.
	 * @return The result of division.
	 */
	FORCEINLINE FFixedPlane operator/(FFixed64 Scale) const
	{
		const FFixed64 RScale = FixedPoint::Constants::Fixed64::One / Scale;
		return FFixedPlane(X * RScale, Y * RScale, Z * RScale, W * RScale);
	}

	/**
	 * Gets result of scaling a plane.
	 *
	 * @param Scale The scaling factor.
	 * @return The result of scaling.
	 */
	FORCEINLINE FFixedPlane operator*(FFixed64 Scale) const
	{
		return FFixedPlane(X * Scale, Y * Scale, Z * Scale, W * Scale);
	}

	/**
	 * Gets result of multiplying a plane with this.
	 *
	 * @param V The other plane.
	 * @return The result of multiplying a plane with this.
	 */
	FORCEINLINE FFixedPlane operator*(const FFixedPlane& V)
	{
		return FFixedPlane(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
	}

	/**
	 * Add another plane to this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after addition.
	 */
	FORCEINLINE FFixedPlane operator+=(const FFixedPlane& V)
	{
		X += V.X; Y += V.Y; Z += V.Z; W += V.W;
		return *this;
	}

	/**
	 * Subtract another plane from this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after subtraction.
	 */
	FORCEINLINE FFixedPlane operator-=(const FFixedPlane& V)
	{
		X -= V.X; Y -= V.Y; Z -= V.Z; W -= V.W;
		return *this;
	}

	/**
	 * Scale this plane.
	 *
	 * @param Scale The scaling factor.
	 * @return Copy of plane after scaling.
	 */
	FORCEINLINE FFixedPlane operator*=(FFixed64 Scale)
	{
		X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
		return *this;
	}

	/**
	 * Multiply another plane with this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after multiplication.
	 */
	FORCEINLINE FFixedPlane operator*=(const FFixedPlane& V)
	{
		X *= V.X; Y *= V.Y; Z *= V.Z; W *= V.W;
		return *this;
	}

	/**
	 * Divide this plane.
	 *
	 * @param V What to divide by.
	 * @return Copy of plane after division.
	 */
	FORCEINLINE FFixedPlane operator/=(FFixed64 V)
	{
		const FFixed64 RV = FixedPoint::Constants::Fixed64::One / V;
		X *= RV; Y *= RV; Z *= RV; W *= RV;
		return *this;
	}
};
