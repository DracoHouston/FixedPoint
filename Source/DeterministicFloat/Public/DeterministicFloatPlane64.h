// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatVector4D64.h"
#include "DeterministicFloatPlane64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicPlane64 : public FDeterministicVector64
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 W;

	/** Default constructor (no initialization). */
	FORCEINLINE FDeterministicPlane64();

	/**
	 * Constructor.
	 *
	 * @param V 4D vector to set up plane.
	 */
	FORCEINLINE FDeterministicPlane64(const FDeterministicVector4D64& V);

	/**
	 * Constructor.
	 *
	 * @param InX X-coefficient.
	 * @param InY Y-coefficient.
	 * @param InZ Z-coefficient.
	 * @param InW W-coefficient.
	 */
	FORCEINLINE FDeterministicPlane64(FDeterministicNumber64 InX, FDeterministicNumber64 InY, FDeterministicNumber64 InZ, FDeterministicNumber64 InW);

	/**
	 * Constructor.
	 *
	 * @param InNormal Plane Normal Vector.
	 * @param InW Plane W-coefficient.
	 */
	FORCEINLINE FDeterministicPlane64(FDeterministicVector64 InNormal, FDeterministicNumber64 InW);

	/**
	 * Constructor.
	 *
	 * @param InBase Base point in plane.
	 * @param InNormal Plane Normal Vector.
	 */
	FORCEINLINE FDeterministicPlane64(FDeterministicVector64 InBase, const FDeterministicVector64& InNormal);

	/**
	 * Constructor.
	 *
	 * @param A First point in the plane.
	 * @param B Second point in the plane.
	 * @param C Third point in the plane.
	 */
	FDeterministicPlane64(FDeterministicVector64 A, FDeterministicVector64 B, FDeterministicVector64 C);

	/**
	 * Constructor
	 *
	 * @param EForceInit Force Init Enum.
	 */
	explicit FORCEINLINE FDeterministicPlane64(EForceInit);

	/**
	 * Checks if this plane is valid (ie: if it has a non-zero normal).
	 *
	 * @return true if the plane is well-defined (has a non-zero normal), otherwise false.
	 */
	FORCEINLINE bool IsValid() const;

	/**
	 * Get the origin of this plane.
	 *
	 * @return The origin (base point) of this plane.
	 */
	FORCEINLINE FDeterministicVector64 GetOrigin() const;

	/**
	 * Get the normal of this plane.
	 *
	 * @return The normal of this plane.
	 */
	FORCEINLINE const FDeterministicVector64& GetNormal() const;


	/**
	 * Calculates distance between plane and a point.
	 *
	 * @param P The other point.
	 * @return The distance from the plane to the point. 0: Point is on the plane. >0: Point is in front of the plane. <0: Point is behind the plane.
	 */
	FORCEINLINE FDeterministicNumber64 PlaneDot(const FDeterministicVector64& P) const;

	/**
	 * Normalize this plane in-place if it is larger than a given tolerance. Leaves it unchanged if not.
	 *
	 * @param Tolerance Minimum squared length of vector for normalization.
	 * @return true if the plane was normalized correctly, false otherwise.
	 */
	bool Normalize(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber);

	/**
	 * Get a flipped version of the plane.
	 *
	 * @return A flipped version of the plane.
	 */
	FDeterministicPlane64 Flip() const;

	/**
	 * Get the result of transforming the plane by a Matrix.
	 *
	 * @param M The matrix to transform plane with.
	 * @return The result of transform.
	 */
	FORCEINLINE FDeterministicPlane64 TransformBy(const FDeterministicMatrix64& M) const;

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
	FORCEINLINE FDeterministicPlane64 TransformByUsingAdjointT(const FDeterministicMatrix64& M, FDeterministicNumber64 DetM, const FDeterministicMatrix64& TA) const;

	/**
	 * Get the result of translating the plane by the given offset
	 *
	 * @param V The translation amount
	 * @return The result of transform.
	 */
	FORCEINLINE FDeterministicPlane64 TranslateBy(const FDeterministicVector64& V) const;

	/**
	 * Check if two planes are identical.
	 *
	 * @param V The other plane.
	 * @return true if planes are identical, otherwise false.
	 */
	FORCEINLINE bool operator==(const FDeterministicPlane64& V) const;

	/**
	 * Check if two planes are different.
	 *
	 * @param V The other plane.
	 * @return true if planes are different, otherwise false.
	 */
	FORCEINLINE bool operator!=(const FDeterministicPlane64& V) const;

	/**
	 * Checks whether two planes are equal within specified tolerance.
	 *
	 * @param V The other plane.
	 * @param Tolerance Error Tolerance.
	 * @return true if the two planes are equal within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FDeterministicPlane64& V, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	/**
	 * Calculates dot product of two planes.
	 *
	 * @param V The other plane.
	 * @return The dot product.
	 */
	FORCEINLINE FDeterministicNumber64 operator|(const FDeterministicPlane64& V) const;

	/**
	 * Gets result of adding a plane to this.
	 *
	 * @param V The other plane.
	 * @return The result of adding a plane to this.
	 */
	FORCEINLINE FDeterministicPlane64 operator+(const FDeterministicPlane64& V) const;

	/**
	 * Gets result of subtracting a plane from this.
	 *
	 * @param V The other plane.
	 * @return The result of subtracting a plane from this.
	 */
	FORCEINLINE FDeterministicPlane64 operator-(const FDeterministicPlane64& V) const;

	/**
	 * Gets result of dividing a plane.
	 *
	 * @param Scale What to divide by.
	 * @return The result of division.
	 */
	FORCEINLINE FDeterministicPlane64 operator/(FDeterministicNumber64 Scale) const;

	/**
	 * Gets result of scaling a plane.
	 *
	 * @param Scale The scaling factor.
	 * @return The result of scaling.
	 */
	FORCEINLINE FDeterministicPlane64 operator*(FDeterministicNumber64 Scale) const;

	/**
	 * Gets result of multiplying a plane with this.
	 *
	 * @param V The other plane.
	 * @return The result of multiplying a plane with this.
	 */
	FORCEINLINE FDeterministicPlane64 operator*(const FDeterministicPlane64& V);

	/**
	 * Add another plane to this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after addition.
	 */
	FORCEINLINE FDeterministicPlane64 operator+=(const FDeterministicPlane64& V);

	/**
	 * Subtract another plane from this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after subtraction.
	 */
	FORCEINLINE FDeterministicPlane64 operator-=(const FDeterministicPlane64& V);

	/**
	 * Scale this plane.
	 *
	 * @param Scale The scaling factor.
	 * @return Copy of plane after scaling.
	 */
	FORCEINLINE FDeterministicPlane64 operator*=(FDeterministicNumber64 Scale);

	/**
	 * Multiply another plane with this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after multiplication.
	 */
	FORCEINLINE FDeterministicPlane64 operator*=(const FDeterministicPlane64& V);

	/**
	 * Divide this plane.
	 *
	 * @param V What to divide by.
	 * @return Copy of plane after division.
	 */
	FORCEINLINE FDeterministicPlane64 operator/=(FDeterministicNumber64 V);
};
