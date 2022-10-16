// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointTypes.h"
#include "FixedPointMath.h"
#include "FixedPointNumbers.h"
#include "FixedPointQuat.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedQuat
{
public:
	GENERATED_BODY()

	/**
	* Default constructor, no initialization.
	*/
	FORCEINLINE FFixedQuat() {}

	/**
	 * Creates and initializes a new quaternion, with the W component either 0 or 1.
	 *
	 * @param EForceInit Force init enum: if equal to ForceInitToZero then W is 0, otherwise W = 1 (creating an identity transform)
	 */
	explicit FORCEINLINE FFixedQuat(EForceInit ZeroOrNot);

	FORCEINLINE FFixedQuat(const FFixedVector& inAxis, const FFixed64& inAngleRad);

	FORCEINLINE FFixedQuat(const FFixed64& inValue);

	FORCEINLINE FFixedQuat(const FFixed64& inX, const FFixed64& inY, const FFixed64& inZ, const FFixed64& inW);

	/**
	 * Creates and initializes a new quaternion from the given rotator.
	 *
	 * @param R The rotator to initialize from.
	 */
	//explicit FFixedQuat(const FFixedRotator& R);
	//NEED ROTATOR CLASS!

	/**
	 * Creates and initializes a new quaternion from the given matrix.
	 *
	 * @param M The rotation matrix to initialize from.
	 */
	explicit FFixedQuat(const FFixedMatrix& M);

	/*FFixedQuat(int64 inX, int64 inY, int64 inZ, int64 inW);

	FFixedQuat(float inX, float inY, float inZ, float inW);

	FFixedQuat(double inX, double inY, double inZ, double inW);*/

	UPROPERTY(EditAnywhere)
	FFixed64 X;

	UPROPERTY(EditAnywhere)
	FFixed64 Y;

	UPROPERTY(EditAnywhere)
	FFixed64 Z;

	UPROPERTY(EditAnywhere)
	FFixed64 W;

	static const FFixedQuat Identity;

	/**
	 * Gets the result of adding a Quaternion to this.
	 * This is a component-wise addition; composing quaternions should be done via multiplication.
	 *
	 * @param Q The Quaternion to add.
	 * @return The result of addition.
	 */
	FORCEINLINE FFixedQuat operator+(const FFixedQuat& Q) const;

	/**
	 * Adds to this quaternion.
	 * This is a component-wise addition; composing quaternions should be done via multiplication.
	 *
	 * @param Other The quaternion to add to this.
	 * @return Result after addition.
	 */
	FORCEINLINE FFixedQuat operator+=(const FFixedQuat& Q);

	/**
	 * Gets the result of subtracting a Quaternion to this.
	 * This is a component-wise subtraction; composing quaternions should be done via multiplication.
	 *
	 * @param Q The Quaternion to subtract.
	 * @return The result of subtraction.
	 */
	FORCEINLINE FFixedQuat operator-(const FFixedQuat& Q) const;

	/**
	* Negates the quaternion. Note that this represents the same rotation.
	*
	* @return The result of negation.
	*/
	FORCEINLINE FFixedQuat operator-() const;

	/**
	 * Checks whether another Quaternion is equal to this, within specified tolerance.
	 *
	 * @param Q The other Quaternion.
	 * @param Tolerance Error tolerance for comparison with other Quaternion.
	 * @return true if two Quaternions are equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FFixedQuat& Q, FFixed64 Tolerance) const;

	/**
	 * Checks whether this Quaternion is an Identity Quaternion.
	 * Assumes Quaternion tested is normalized.
	 *
	 * @param Tolerance Error tolerance for comparison with Identity Quaternion.
	 * @return true if Quaternion is a normalized Identity Quaternion.
	 */
	FORCEINLINE bool IsIdentity(FFixed64 Tolerance) const;

	/**
	 * Checks whether another Quaternion is equal to this, within specified tolerance.
	 *
	 * @param Q The other Quaternion.
	 * @return true if two Quaternions are equal, within default tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FFixedQuat& Q) const;

	/**
	 * Checks whether this Quaternion is an Identity Quaternion.
	 * Assumes Quaternion tested is normalized.
	 *
	 * @return true if Quaternion is a normalized Identity Quaternion, within default tolerance.
	 */
	FORCEINLINE bool IsIdentity() const;

	/**
	 * Subtracts another quaternion from this.
	 * This is a component-wise subtraction; composing quaternions should be done via multiplication.
	 *
	 * @param Q The other quaternion.
	 * @return reference to this after subtraction.
	 */
	FORCEINLINE FFixedQuat operator-=(const FFixedQuat& Q);

	/**
	 * Gets the result of multiplying this by another quaternion (this * Q).
	 *
	 * Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	 * first applies B then A to any subsequent transformation (right first, then left).
	 *
	 * @param Q The Quaternion to multiply this by.
	 * @return The result of multiplication (this * Q).
	 */
	FORCEINLINE FFixedQuat operator*(const FFixedQuat& Q) const;

	/**
	 * Multiply this by a quaternion (this = this * Q).
	 *
	 * Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	 * first applies B then A to any subsequent transformation (right first, then left).
	 *
	 * @param Q the quaternion to multiply this by.
	 * @return The result of multiplication (this * Q).
	 */
	FORCEINLINE FFixedQuat operator*=(const FFixedQuat& Q);

	/**
	 * Rotate a vector by this quaternion.
	 *
	 * @param V the vector to be rotated
	 * @return vector after rotation
	 * @see RotateVector
	 */
	FFixedVector operator*(const FFixedVector& V) const;

	/**
	 * Multiply this by a matrix.
	 * This matrix conversion came from
	 * http://www.m-hikari.com/ija/ija-password-2008/ija-password17-20-2008/aristidouIJA17-20-2008.pdf
	 * used for non-uniform scaling transform.
	 *
	 * @param M Matrix to multiply by.
	 * @return Matrix result after multiplication.
	 */
	FFixedMatrix operator*(const FFixedMatrix& M) const;

	FORCEINLINE FFixedQuat operator*=(const FFixed64& Scale)
	{
		X *= Scale;
		Y *= Scale;
		Z *= Scale;
		W *= Scale;
		return *this;
	}

	/**
	 * Get the result of scaling this quaternion.
	 *
	 * @param Scale The scaling factor.
	 * @return The result of scaling.
	 */
	FORCEINLINE FFixedQuat operator*(const FFixed64& Scale) const
	{
		return FFixedQuat(Scale * X, Scale * Y, Scale * Z, Scale * W);
	}

	/**
	 * Divide this quaternion by scale.
	 *
	 * @param Scale What to divide by.
	 * @return a reference to this after scaling.
	 */
	FORCEINLINE FFixedQuat operator/=(const FFixed64& Scale)
	{
		const FFixed64 Recip = FFixed64((int64)1) / Scale;
		X *= Recip;
		Y *= Recip;
		Z *= Recip;
		W *= Recip;
		return *this;
	}

	/**
	 * Divide this quaternion by scale.
	 *
	 * @param Scale What to divide by.
	 * @return new Quaternion of this after division by scale.
	 */
	FORCEINLINE FFixedQuat operator/(const FFixed64& Scale) const
	{
		const FFixed64 Recip = FFixed64((int64)1) / Scale;
		return FFixedQuat(X * Recip, Y * Recip, Z * Recip, W * Recip);
	}

	/**
	 * Identical implementation for TQuat properties.
	 * Avoids intrinsics to remain consistent with previous per-property comparison.
	 */
	bool Identical(const FFixedQuat* Q, const uint32 PortFlags) const;

	/**
	 * Checks whether two quaternions are identical.
	 * This is an exact comparison per-component;see Equals() for a comparison
	 * that allows for a small error tolerance and flipped axes of rotation.
	 *
	 * @param Q The other quaternion.
	 * @return true if two quaternion are identical, otherwise false.
	 * @see Equals
	 */
	bool operator==(const FFixedQuat& Q) const;

	/**
	 * Checks whether two quaternions are not identical.
	 *
	 * @param Q The other quaternion.
	 * @return true if two quaternion are not identical, otherwise false.
	 */
	bool operator!=(const FFixedQuat& Q) const;

	/**
	 * Calculates dot product of two quaternions.
	 *
	 * @param Q The other quaternions.
	 * @return The dot product.
	 */
	FFixed64 operator|(const FFixedQuat& Q) const;
};

FORCEINLINE FFixedQuat::FFixedQuat(EForceInit ZeroOrNot)
{ 
	X = FFixed64();
	Y = FFixed64();
	Z = FFixed64();
	W = ZeroOrNot == EForceInit::ForceInitToZero ? FFixed64() : FFixed64((int64)1);
}

FORCEINLINE FFixedQuat::FFixedQuat(const FFixedVector& inAxis, const FFixed64& inAngleRad)
{
	const FFixed64 half_a = FixedPoint::Constants::Fixed64::Half * inAngleRad;
	FFixed64 s, c;
	FFixedPointMath::SinCos(&s, &c, half_a);

	X = s * inAxis.X;
	Y = s * inAxis.Y;
	Z = s * inAxis.Z;
	W = c;
}

FORCEINLINE FFixedQuat::FFixedQuat(const FFixed64& inValue)
{
	X = inValue;
	Y = inValue;
	Z = inValue;
	W = inValue;
}

FORCEINLINE FFixedQuat::FFixedQuat(const FFixed64& inX, const FFixed64& inY, const FFixed64& inZ, const FFixed64& inW)
{
	X = inX;
	Y = inY;
	Z = inZ;
	W = inW;
}

inline FFixedQuat::FFixedQuat(const FFixedMatrix& M)
{
	// If Matrix is NULL, return Identity quaternion. If any of them is 0, you won't be able to construct rotation
	// if you have two plane at least, we can reconstruct the frame using cross product, but that's a bit expensive op to do here
	// for now, if you convert to matrix from 0 scale and convert back, you'll lose rotation. Don't do that. 
	/*if (M.GetScaledAxis(EAxis::X).IsNearlyZero() || M.GetScaledAxis(EAxis::Y).IsNearlyZero() || M.GetScaledAxis(EAxis::Z).IsNearlyZero())
	{
		*this = FFixedQuat::Identity;
		return;
	}*/

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// Make sure the Rotation part of the Matrix is unit length.
	// Changed to this (same as RemoveScaling) from RotDeterminant as using two different ways of checking unit length matrix caused inconsistency. 
	/*if (!ensure((FMath::Abs(1.f - M.GetScaledAxis(EAxis::X).SizeSquared()) <= UE_KINDA_SMALL_NUMBER) && (FMath::Abs(1.f - M.GetScaledAxis(EAxis::Y).SizeSquared()) <= UE_KINDA_SMALL_NUMBER) && (FMath::Abs(1.f - M.GetScaledAxis(EAxis::Z).SizeSquared()) <= UE_KINDA_SMALL_NUMBER)))
	{
		*this = TQuat<T>::Identity;
		return;
	}*/
#endif

	//const MeReal *const t = (MeReal *) tm;
	FFixed64 s;

	// Check diagonal (trace)
	const FFixed64 tr = M.M[0][0] + M.M[1][1] + M.M[2][2];

	if (tr > FFixed64(0.0f))
	{
		FFixed64 InvS = FFixed64();// = FMath::InvSqrt(tr + T(1.f));
		this->W = FFixed64(FFixed64(0.5f) * (FFixed64(1.f) / InvS));
		s = FFixed64(0.5f) * InvS;

		this->X = ((M.M[1][2] - M.M[2][1]) * s);
		this->Y = ((M.M[2][0] - M.M[0][2]) * s);
		this->Z = ((M.M[0][1] - M.M[1][0]) * s);
	}
	else
	{
		// diagonal is negative
		int32 i = 0;

		if (M.M[1][1] > M.M[0][0])
			i = 1;

		if (M.M[2][2] > M.M[i][i])
			i = 2;

		static constexpr int32 nxt[3] = { 1, 2, 0 };
		const int32 j = nxt[i];
		const int32 k = nxt[j];

		s = M.M[i][i] - M.M[j][j] - M.M[k][k] + FFixed64(1.0f);

		FFixed64 InvS = FFixed64((int64)1) / FFixedPointMath::Sqrt(s);

		FFixed64 qt[4];
		qt[i] = FFixed64(0.5f) * (FFixed64(1.f) / InvS);

		s = FFixed64(0.5f) * InvS;

		qt[3] = (M.M[j][k] - M.M[k][j]) * s;
		qt[j] = (M.M[i][j] + M.M[j][i]) * s;
		qt[k] = (M.M[i][k] + M.M[k][i]) * s;

		this->X = qt[0];
		this->Y = qt[1];
		this->Z = qt[2];
		this->W = qt[3];

	}
}

FORCEINLINE FFixedQuat FFixedQuat::operator+(const FFixedQuat& Q) const
{
	return FFixedQuat(X + Q.X, Y + Q.Y, Z + Q.Z, W + Q.W);
}

FORCEINLINE FFixedQuat FFixedQuat::operator+=(const FFixedQuat& Q)
{
	this->X += Q.X;
	this->Y += Q.Y;
	this->Z += Q.Z;
	this->W += Q.W;

	return *this;
}

FORCEINLINE FFixedQuat FFixedQuat::operator-(const FFixedQuat& Q) const
{
	return FFixedQuat(X - Q.X, Y - Q.Y, Z - Q.Z, W - Q.W);
}

FORCEINLINE FFixedQuat FFixedQuat::operator-() const
{
	return FFixedQuat(-X, -Y, -Z, -W);
}

FORCEINLINE bool FFixedQuat::Equals(const FFixedQuat& Q, FFixed64 Tolerance) const
{
	return (FFixedPointMath::Abs(X - Q.X) <= Tolerance && FFixedPointMath::Abs(Y - Q.Y) <= Tolerance && FFixedPointMath::Abs(Z - Q.Z) <= Tolerance && FFixedPointMath::Abs(W - Q.W) <= Tolerance)
		|| (FFixedPointMath::Abs(X + Q.X) <= Tolerance && FFixedPointMath::Abs(Y + Q.Y) <= Tolerance && FFixedPointMath::Abs(Z + Q.Z) <= Tolerance && FFixedPointMath::Abs(W + Q.W) <= Tolerance);
}

FORCEINLINE bool FFixedQuat::IsIdentity(FFixed64 Tolerance) const
{
	return Equals(FFixedQuat::Identity, Tolerance);
}

FORCEINLINE FFixedQuat FFixedQuat::operator-=(const FFixedQuat& Q)
{
	this->X -= Q.X;
	this->Y -= Q.Y;
	this->Z -= Q.Z;
	this->W -= Q.W;

	return *this;
}

FORCEINLINE FFixedQuat FFixedQuat::operator*(const FFixedQuat& Q) const
{
	return FFixedQuat(
		W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z,  // 1
		W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,  // i
		W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,  // j
		W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W   // k
	);
}

FORCEINLINE FFixedQuat FFixedQuat::operator*=(const FFixedQuat& Q)
{
	this->X = W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z;  // 1
	this->Y = W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y;  // i
	this->Z = W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X;  // j
	this->W = W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W;   // k

	return *this;
}

FORCEINLINE bool FFixedQuat::Identical(const FFixedQuat* Q, const uint32 PortFlags) const
{
	return X == Q->X && Y == Q->Y && Z == Q->Z && W == Q->W;
}

FORCEINLINE bool FFixedQuat::operator==(const FFixedQuat& Q) const
{
	return X == Q.X && Y == Q.Y && Z == Q.Z && W == Q.W;
}

FORCEINLINE bool FFixedQuat::operator!=(const FFixedQuat& Q) const
{
	return X != Q.X || Y != Q.Y || Z != Q.Z || W != Q.W;
}

FORCEINLINE FFixed64 FFixedQuat::operator|(const FFixedQuat& Q) const
{
	return X * Q.X + Y * Q.Y + Z * Q.Z + W * Q.W;
}
// Global operator for (float * Quat)
//template<typename T>
//FORCEINLINE TQuat<T> operator*(const float Scale, const TQuat<T>& Q)
//{
//	return Q.operator*(Scale);
//}
//
//// Global operator for (double * Quat)
//template<typename T>
//FORCEINLINE TQuat<T> operator*(const double Scale, const TQuat<T>& Q)
//{
//	return Q.operator*(Scale);
//}