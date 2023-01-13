// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatMatrix64.h"
#include "DeterministicFloatQuat64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicQuat64
{
public:
	GENERATED_BODY()

		/**
		* Default constructor, no initialization.
		*/
		FORCEINLINE FDeterministicQuat64();

	/**
	* Constructor that casts from FQuat to FDeterministicQuat64
	*/
	FORCEINLINE FDeterministicQuat64(FQuat Other);

	/**
	 * Creates and initializes a new quaternion, with the W component either 0 or 1.
	 *
	 * @param EForceInit Force init enum: if equal to ForceInitToZero then W is 0, otherwise W = 1 (creating an identity transform)
	 */
	explicit FORCEINLINE FDeterministicQuat64(EForceInit ZeroOrNot);

	FORCEINLINE FDeterministicQuat64(const FDeterministicVector64& inAxis, const FDeterministicNumber64& inAngleRad);

	FORCEINLINE FDeterministicQuat64(const FDeterministicNumber64& inValue);

	FORCEINLINE FDeterministicQuat64(const FDeterministicNumber64& inX, const FDeterministicNumber64& inY, const FDeterministicNumber64& inZ, const FDeterministicNumber64& inW);

	/**
	 * Creates and initializes a new quaternion from the given rotator.
	 *
	 * @param R The rotator to initialize from.
	 */
	explicit FDeterministicQuat64(const FDeterministicRotator64& R);

	/**
	 * Creates and initializes a new quaternion from the given rotator.
	 *
	 * @param R The rotator to initialize from.
	 */
	//explicit FDeterministicQuat64(const FDeterministicRotator64& R);
	//NEED ROTATOR CLASS!

	/**
	 * Creates and initializes a new quaternion from the given matrix.
	 *
	 * @param M The rotation matrix to initialize from.
	 */
	explicit FDeterministicQuat64(const FDeterministicMatrix64& M);

	/*FDeterministicQuat64(int64 inX, int64 inY, int64 inZ, int64 inW);

	FDeterministicQuat64(float inX, float inY, float inZ, float inW);

	FDeterministicQuat64(double inX, double inY, double inZ, double inW);*/

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 X;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Y;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Z;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 W;

	static const FDeterministicQuat64 Identity;

	/**
	 * Gets the result of adding a Quaternion to this.
	 * This is a component-wise addition; composing quaternions should be done via multiplication.
	 *
	 * @param Q The Quaternion to add.
	 * @return The result of addition.
	 */
	FORCEINLINE FDeterministicQuat64 operator+(const FDeterministicQuat64& Q) const;

	/**
	 * Adds to this quaternion.
	 * This is a component-wise addition; composing quaternions should be done via multiplication.
	 *
	 * @param Other The quaternion to add to this.
	 * @return Result after addition.
	 */
	FORCEINLINE FDeterministicQuat64 operator+=(const FDeterministicQuat64& Q);

	/**
	 * Gets the result of subtracting a Quaternion to this.
	 * This is a component-wise subtraction; composing quaternions should be done via multiplication.
	 *
	 * @param Q The Quaternion to subtract.
	 * @return The result of subtraction.
	 */
	FORCEINLINE FDeterministicQuat64 operator-(const FDeterministicQuat64& Q) const;

	/**
	* Negates the quaternion. Note that this represents the same rotation.
	*
	* @return The result of negation.
	*/
	FORCEINLINE FDeterministicQuat64 operator-() const;

	/**
	 * Checks whether another Quaternion is equal to this, within specified tolerance.
	 *
	 * @param Q The other Quaternion.
	 * @param Tolerance Error tolerance for comparison with other Quaternion.
	 * @return true if two Quaternions are equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FDeterministicQuat64& Q, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	/**
	 * Checks whether this Quaternion is an Identity Quaternion.
	 * Assumes Quaternion tested is normalized.
	 *
	 * @param Tolerance Error tolerance for comparison with Identity Quaternion.
	 * @return true if Quaternion is a normalized Identity Quaternion.
	 */
	FORCEINLINE bool IsIdentity(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber) const;

	/**
	 * Subtracts another quaternion from this.
	 * This is a component-wise subtraction; composing quaternions should be done via multiplication.
	 *
	 * @param Q The other quaternion.
	 * @return reference to this after subtraction.
	 */
	FORCEINLINE FDeterministicQuat64 operator-=(const FDeterministicQuat64& Q);

	/**
	 * Gets the result of multiplying this by another quaternion (this * Q).
	 *
	 * Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	 * first applies B then A to any subsequent transformation (right first, then left).
	 *
	 * @param Q The Quaternion to multiply this by.
	 * @return The result of multiplication (this * Q).
	 */
	FORCEINLINE FDeterministicQuat64 operator*(const FDeterministicQuat64& Q) const;

	/**
	 * Multiply this by a quaternion (this = this * Q).
	 *
	 * Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	 * first applies B then A to any subsequent transformation (right first, then left).
	 *
	 * @param Q the quaternion to multiply this by.
	 * @return The result of multiplication (this * Q).
	 */
	FORCEINLINE FDeterministicQuat64 operator*=(const FDeterministicQuat64& Q);

	/**
	 * Rotate a vector by this quaternion.
	 *
	 * @param V the vector to be rotated
	 * @return vector after rotation
	 * @see RotateVector
	 */
	FDeterministicVector64 operator*(const FDeterministicVector64& V) const;

	/**
	 * Multiply this by a matrix.
	 * This matrix conversion came from
	 * http://www.m-hikari.com/ija/ija-password-2008/ija-password17-20-2008/aristidouIJA17-20-2008.pdf
	 * used for non-uniform scaling transform.
	 *
	 * @param M Matrix to multiply by.
	 * @return Matrix result after multiplication.
	 */
	FDeterministicMatrix64 operator*(const FDeterministicMatrix64& M) const;

	FORCEINLINE FDeterministicQuat64 operator*=(const FDeterministicNumber64& Scale);

	/**
	 * Get the result of scaling this quaternion.
	 *
	 * @param Scale The scaling factor.
	 * @return The result of scaling.
	 */
	FORCEINLINE FDeterministicQuat64 operator*(const FDeterministicNumber64& Scale) const;

	/**
	 * Divide this quaternion by scale.
	 *
	 * @param Scale What to divide by.
	 * @return a reference to this after scaling.
	 */
	FORCEINLINE FDeterministicQuat64 operator/=(const FDeterministicNumber64& Scale);

	/**
	 * Divide this quaternion by scale.
	 *
	 * @param Scale What to divide by.
	 * @return new Quaternion of this after division by scale.
	 */
	FORCEINLINE FDeterministicQuat64 operator/(const FDeterministicNumber64& Scale) const;

	/**
	 * Identical implementation for TQuat properties.
	 * Avoids intrinsics to remain consistent with previous per-property comparison.
	 */
	bool Identical(const FDeterministicQuat64* Q, const uint32 PortFlags) const;

	/**
	 * Checks whether two quaternions are identical.
	 * This is an exact comparison per-component;see Equals() for a comparison
	 * that allows for a small error tolerance and flipped axes of rotation.
	 *
	 * @param Q The other quaternion.
	 * @return true if two quaternion are identical, otherwise false.
	 * @see Equals
	 */
	bool operator==(const FDeterministicQuat64& Q) const;

	/**
	 * Checks whether two quaternions are not identical.
	 *
	 * @param Q The other quaternion.
	 * @return true if two quaternion are not identical, otherwise false.
	 */
	bool operator!=(const FDeterministicQuat64& Q) const;

	/**
	 * Calculates dot product of two quaternions.
	 *
	 * @param Q The other quaternions.
	 * @return The dot product.
	 */
	FDeterministicNumber64 operator|(const FDeterministicQuat64& Q) const;

	FDeterministicRotator64 Rotator() const;

	// Return true if this quaternion is normalized
	FORCEINLINE bool IsNormalized() const;

	/**
	 * Get the length of this quaternion.
	 *
	 * @return The length of this quaternion.
	 */
	FORCEINLINE FDeterministicNumber64 Size() const;

	/**
	 * Get the length squared of this quaternion.
	 *
	 * @return The length of this quaternion.
	 */
	FORCEINLINE FDeterministicNumber64 SizeSquared() const;

	/**
	 * @return inverse of this quaternion
	 * @warning : Requires this quaternion to be normalized.
	 */
	FORCEINLINE FDeterministicQuat64 Inverse() const;

	/**
	 * Normalize this quaternion if it is large enough.
	 * If it is too small, returns an identity quaternion.
	 *
	 * @param Tolerance Minimum squared length of quaternion for normalization.
	 */
	FORCEINLINE void Normalize(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber);

	/**
	 * Get a textual representation of the vector.
	 *
	 * @return Text describing the vector.
	 */
	FString ToString() const;

	/**
	 * Rotate a vector by this quaternion.
	 *
	 * @param V the vector to be rotated
	 * @return vector after rotation
	 */
	FDeterministicVector64 RotateVector(FDeterministicVector64 V) const;

	/**
	 * Rotate a vector by the inverse of this quaternion.
	 *
	 * @param V the vector to be rotated
	 * @return vector after rotation by the inverse of this quaternion.
	 */
	FDeterministicVector64 UnrotateVector(FDeterministicVector64 V) const;

	/**
	 * Fast Linear Quaternion Interpolation.
	 * Result is NOT normalized.
	 */
	static FORCEINLINE FDeterministicQuat64 FastLerp(const FDeterministicQuat64& A, const FDeterministicQuat64& B, const FDeterministicNumber64 Alpha);

	FORCEINLINE operator FQuat() const;
};

// Global operator for (Number32 * Quat)
FORCEINLINE FDeterministicQuat64 operator*(const FDeterministicNumber32 Scale, const FDeterministicQuat64& Q)
{
	return Q.operator*(Scale);
}

// Global operator for (number64 * Quat)
FORCEINLINE FDeterministicQuat64 operator*(const FDeterministicNumber64 Scale, const FDeterministicQuat64& Q)
{
	return Q.operator*(Scale);
}
