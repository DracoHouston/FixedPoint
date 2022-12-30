// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FixedPointTypes.h"
#include "Misc/AssertionMacros.h"
#include "FixedPointQuat.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedQuat64
{
public:
	GENERATED_BODY()

	/**
	* Default constructor, no initialization.
	*/
	FORCEINLINE FFixedQuat64() {}

	/**
	* Constructor that casts from FQuat to FFixedQuat64
	*/
	FORCEINLINE FFixedQuat64(FQuat Other)
	{
		X = (FFixed64)Other.X;
		Y = (FFixed64)Other.Y;
		Z = (FFixed64)Other.Z;
		W = (FFixed64)Other.W;
	}

	/**
	 * Creates and initializes a new quaternion, with the W component either 0 or 1.
	 *
	 * @param EForceInit Force init enum: if equal to ForceInitToZero then W is 0, otherwise W = 1 (creating an identity transform)
	 */
	explicit FORCEINLINE FFixedQuat64(EForceInit ZeroOrNot);

	FORCEINLINE FFixedQuat64(const FFixedVector64& inAxis, const FFixed64& inAngleRad);

	FORCEINLINE FFixedQuat64(const FFixed64& inValue);

	FORCEINLINE FFixedQuat64(const FFixed64& inX, const FFixed64& inY, const FFixed64& inZ, const FFixed64& inW);

	/**
	 * Creates and initializes a new quaternion from the given rotator.
	 *
	 * @param R The rotator to initialize from.
	 */
	explicit FFixedQuat64(const FFixedRotator64& R);

	/**
	 * Creates and initializes a new quaternion from the given rotator.
	 *
	 * @param R The rotator to initialize from.
	 */
	//explicit FFixedQuat64(const FFixedRotator64& R);
	//NEED ROTATOR CLASS!

	/**
	 * Creates and initializes a new quaternion from the given matrix.
	 *
	 * @param M The rotation matrix to initialize from.
	 */
	explicit FFixedQuat64(const FFixedMatrix& M);

	/*FFixedQuat64(int64 inX, int64 inY, int64 inZ, int64 inW);

	FFixedQuat64(float inX, float inY, float inZ, float inW);

	FFixedQuat64(double inX, double inY, double inZ, double inW);*/

	UPROPERTY(EditAnywhere)
	FFixed64 X;

	UPROPERTY(EditAnywhere)
	FFixed64 Y;

	UPROPERTY(EditAnywhere)
	FFixed64 Z;

	UPROPERTY(EditAnywhere)
	FFixed64 W;

	static const FFixedQuat64 Identity;

	/**
	 * Gets the result of adding a Quaternion to this.
	 * This is a component-wise addition; composing quaternions should be done via multiplication.
	 *
	 * @param Q The Quaternion to add.
	 * @return The result of addition.
	 */
	FORCEINLINE FFixedQuat64 operator+(const FFixedQuat64& Q) const;

	/**
	 * Adds to this quaternion.
	 * This is a component-wise addition; composing quaternions should be done via multiplication.
	 *
	 * @param Other The quaternion to add to this.
	 * @return Result after addition.
	 */
	FORCEINLINE FFixedQuat64 operator+=(const FFixedQuat64& Q);

	/**
	 * Gets the result of subtracting a Quaternion to this.
	 * This is a component-wise subtraction; composing quaternions should be done via multiplication.
	 *
	 * @param Q The Quaternion to subtract.
	 * @return The result of subtraction.
	 */
	FORCEINLINE FFixedQuat64 operator-(const FFixedQuat64& Q) const;

	/**
	* Negates the quaternion. Note that this represents the same rotation.
	*
	* @return The result of negation.
	*/
	FORCEINLINE FFixedQuat64 operator-() const;

	/**
	 * Checks whether another Quaternion is equal to this, within specified tolerance.
	 *
	 * @param Q The other Quaternion.
	 * @param Tolerance Error tolerance for comparison with other Quaternion.
	 * @return true if two Quaternions are equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FFixedQuat64& Q, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const;

	/**
	 * Checks whether this Quaternion is an Identity Quaternion.
	 * Assumes Quaternion tested is normalized.
	 *
	 * @param Tolerance Error tolerance for comparison with Identity Quaternion.
	 * @return true if Quaternion is a normalized Identity Quaternion.
	 */
	FORCEINLINE bool IsIdentity(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber) const;

	/**
	 * Subtracts another quaternion from this.
	 * This is a component-wise subtraction; composing quaternions should be done via multiplication.
	 *
	 * @param Q The other quaternion.
	 * @return reference to this after subtraction.
	 */
	FORCEINLINE FFixedQuat64 operator-=(const FFixedQuat64& Q);

	/**
	 * Gets the result of multiplying this by another quaternion (this * Q).
	 *
	 * Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	 * first applies B then A to any subsequent transformation (right first, then left).
	 *
	 * @param Q The Quaternion to multiply this by.
	 * @return The result of multiplication (this * Q).
	 */
	FORCEINLINE FFixedQuat64 operator*(const FFixedQuat64& Q) const;

	/**
	 * Multiply this by a quaternion (this = this * Q).
	 *
	 * Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	 * first applies B then A to any subsequent transformation (right first, then left).
	 *
	 * @param Q the quaternion to multiply this by.
	 * @return The result of multiplication (this * Q).
	 */
	FORCEINLINE FFixedQuat64 operator*=(const FFixedQuat64& Q);

	/**
	 * Rotate a vector by this quaternion.
	 *
	 * @param V the vector to be rotated
	 * @return vector after rotation
	 * @see RotateVector
	 */
	FFixedVector64 operator*(const FFixedVector64& V) const
	{
		return RotateVector(V);
	}

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

	FORCEINLINE FFixedQuat64 operator*=(const FFixed64& Scale)
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
	FORCEINLINE FFixedQuat64 operator*(const FFixed64& Scale) const
	{
		return FFixedQuat64(Scale * X, Scale * Y, Scale * Z, Scale * W);
	}

	/**
	 * Divide this quaternion by scale.
	 *
	 * @param Scale What to divide by.
	 * @return a reference to this after scaling.
	 */
	FORCEINLINE FFixedQuat64 operator/=(const FFixed64& Scale)
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
	FORCEINLINE FFixedQuat64 operator/(const FFixed64& Scale) const
	{
		const FFixed64 Recip = FFixed64((int64)1) / Scale;
		return FFixedQuat64(X * Recip, Y * Recip, Z * Recip, W * Recip);
	}

	/**
	 * Identical implementation for TQuat properties.
	 * Avoids intrinsics to remain consistent with previous per-property comparison.
	 */
	bool Identical(const FFixedQuat64* Q, const uint32 PortFlags) const;

	/**
	 * Checks whether two quaternions are identical.
	 * This is an exact comparison per-component;see Equals() for a comparison
	 * that allows for a small error tolerance and flipped axes of rotation.
	 *
	 * @param Q The other quaternion.
	 * @return true if two quaternion are identical, otherwise false.
	 * @see Equals
	 */
	bool operator==(const FFixedQuat64& Q) const;

	/**
	 * Checks whether two quaternions are not identical.
	 *
	 * @param Q The other quaternion.
	 * @return true if two quaternion are not identical, otherwise false.
	 */
	bool operator!=(const FFixedQuat64& Q) const;

	/**
	 * Calculates dot product of two quaternions.
	 *
	 * @param Q The other quaternions.
	 * @return The dot product.
	 */
	FFixed64 operator|(const FFixedQuat64& Q) const;

	FFixedRotator64 Rotator() const;

	// Return true if this quaternion is normalized
	FORCEINLINE bool IsNormalized() const
	{
		return (FFixedPointMath::Abs(FixedPoint::Constants::Fixed64::One - SizeSquared()) < FixedPoint::Constants::Fixed64::ThreshQuatNormalized);
	}

	/**
	 * Get the length of this quaternion.
	 *
	 * @return The length of this quaternion.
	 */
	FORCEINLINE FFixed64 Size() const
	{
		return FFixedPointMath::Sqrt(X * X + Y * Y + Z * Z + W * W);
	}

	/**
	 * Get the length squared of this quaternion.
	 *
	 * @return The length of this quaternion.
	 */
	FORCEINLINE FFixed64 SizeSquared() const
	{
		return (X * X + Y * Y + Z * Z + W * W);
	}

	/**
	 * @return inverse of this quaternion
	 * @warning : Requires this quaternion to be normalized.
	 */
	FORCEINLINE FFixedQuat64 Inverse() const
	{
		checkSlow(IsNormalized());

		return FFixedQuat64(-X, -Y, -Z, W);
	}

	/**
	 * Normalize this quaternion if it is large enough.
	 * If it is too small, returns an identity quaternion.
	 *
	 * @param Tolerance Minimum squared length of quaternion for normalization.
	 */
	FORCEINLINE void Normalize(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		const FFixed64 SquareSum = X * X + Y * Y + Z * Z + W * W;

		if (SquareSum >= Tolerance)
		{
			const FFixed64 Scale = FFixedPointMath::InvSqrt(SquareSum);

			X *= Scale;
			Y *= Scale;
			Z *= Scale;
			W *= Scale;
		}
		else
		{
			*this = FFixedQuat64::Identity;
		}
	}

	/**
	 * Get a textual representation of the vector.
	 *
	 * @return Text describing the vector.
	 */
	FString ToString() const
	{
		return FString::Printf(TEXT("X=%.9f Y=%.9f Z=%.9f W=%.9f"), (double)X, (double)Y, (double)Z, (double)W);
	}

	/**
	 * Rotate a vector by this quaternion.
	 *
	 * @param V the vector to be rotated
	 * @return vector after rotation
	 */
	FFixedVector64 RotateVector(FFixedVector64 V) const
	{
		// http://people.csail.mit.edu/bkph/articles/Quaternions.pdf
		// V' = V + 2w(Q x V) + (2Q x (Q x V))
		// refactor:
		// V' = V + w(2(Q x V)) + (Q x (2(Q x V)))
		// T = 2(Q x V);
		// V' = V + w*(T) + (Q x T)

		const FFixedVector64 Q(X, Y, Z);
		const FFixedVector64 TT = FFixedVector64::CrossProduct(Q, V) * FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2);
		const FFixedVector64 Result = V + (TT * W) + FFixedVector64::CrossProduct(Q, TT);
		return Result;
	}

	/**
	 * Rotate a vector by the inverse of this quaternion.
	 *
	 * @param V the vector to be rotated
	 * @return vector after rotation by the inverse of this quaternion.
	 */
	FFixedVector64 UnrotateVector(FFixedVector64 V) const
	{
		const FFixedVector64 Q(-X, -Y, -Z); // Inverse
		const FFixedVector64 TT = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2) * FFixedVector64::CrossProduct(Q, V);
		const FFixedVector64 Result = V + (W * TT) + FFixedVector64::CrossProduct(Q, TT);
		return Result;
	}

	/**
	 * Fast Linear Quaternion Interpolation.
	 * Result is NOT normalized.
	 */
	static FORCEINLINE FFixedQuat64 FastLerp(const FFixedQuat64& A, const FFixedQuat64& B, const FFixed64 Alpha)
	{
		// To ensure the 'shortest route', we make sure the dot product between the both rotations is positive.
		const FFixed64 DotResult = (A | B);
		const FFixed64 Bias = FFixedPointMath::FloatSelect(DotResult, FixedPoint::Constants::Fixed64::One, -FixedPoint::Constants::Fixed64::One);
		return (B * Alpha) + (A * (Bias * (FixedPoint::Constants::Fixed64::One - Alpha)));
	}

	FORCEINLINE operator FQuat() const
	{
		return FQuat((double)X, (double)Y, (double)Z, (double)W);
	}
};

FORCEINLINE FFixedQuat64::FFixedQuat64(EForceInit ZeroOrNot)
{ 
	X = FFixed64();
	Y = FFixed64();
	Z = FFixed64();
	W = ZeroOrNot == EForceInit::ForceInitToZero ? FFixed64() : FFixed64((int64)1);
}

FORCEINLINE FFixedQuat64::FFixedQuat64(const FFixedVector64& inAxis, const FFixed64& inAngleRad)
{
	const FFixed64 half_a = FixedPoint::Constants::Fixed64::Half * inAngleRad;
	FFixed64 s, c;
	FFixedPointMath::SinCos(&s, &c, half_a);

	X = s * inAxis.X;
	Y = s * inAxis.Y;
	Z = s * inAxis.Z;
	W = c;
}

FORCEINLINE FFixedQuat64::FFixedQuat64(const FFixed64& inValue)
{
	X = inValue;
	Y = inValue;
	Z = inValue;
	W = inValue;
}

FORCEINLINE FFixedQuat64::FFixedQuat64(const FFixed64& inX, const FFixed64& inY, const FFixed64& inZ, const FFixed64& inW)
{
	X = inX;
	Y = inY;
	Z = inZ;
	W = inW;
}

inline FFixedQuat64::FFixedQuat64(const FFixedMatrix& M)
{
	// If Matrix is NULL, return Identity quaternion. If any of them is 0, you won't be able to construct rotation
	// if you have two plane at least, we can reconstruct the frame using cross product, but that's a bit expensive op to do here
	// for now, if you convert to matrix from 0 scale and convert back, you'll lose rotation. Don't do that. 
	if (M.GetScaledAxis(EAxis::X).IsNearlyZero() || M.GetScaledAxis(EAxis::Y).IsNearlyZero() || M.GetScaledAxis(EAxis::Z).IsNearlyZero())
	{
		*this = FFixedQuat64::Identity;
		return;
	}

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// Make sure the Rotation part of the Matrix is unit length.
	// Changed to this (same as RemoveScaling) from RotDeterminant as using two different ways of checking unit length matrix caused inconsistency. 
	if (!ensure((FFixedPointMath::Abs(FixedPoint::Constants::Fixed64::One - M.GetScaledAxis(EAxis::X).SizeSquared()) <= FixedPoint::Constants::Fixed64::KindaSmallNumber) && (FFixedPointMath::Abs(FixedPoint::Constants::Fixed64::One - M.GetScaledAxis(EAxis::Y).SizeSquared()) <= FixedPoint::Constants::Fixed64::KindaSmallNumber) && (FFixedPointMath::Abs(FixedPoint::Constants::Fixed64::One - M.GetScaledAxis(EAxis::Z).SizeSquared()) <= FixedPoint::Constants::Fixed64::KindaSmallNumber)))
	{
		*this = FFixedQuat64::Identity;
		return;
	}
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

FORCEINLINE FFixedQuat64 FFixedQuat64::operator+(const FFixedQuat64& Q) const
{
	return FFixedQuat64(X + Q.X, Y + Q.Y, Z + Q.Z, W + Q.W);
}

FORCEINLINE FFixedQuat64 FFixedQuat64::operator+=(const FFixedQuat64& Q)
{
	this->X += Q.X;
	this->Y += Q.Y;
	this->Z += Q.Z;
	this->W += Q.W;

	return *this;
}

FORCEINLINE FFixedQuat64 FFixedQuat64::operator-(const FFixedQuat64& Q) const
{
	return FFixedQuat64(X - Q.X, Y - Q.Y, Z - Q.Z, W - Q.W);
}

FORCEINLINE FFixedQuat64 FFixedQuat64::operator-() const
{
	return FFixedQuat64(-X, -Y, -Z, -W);
}

FORCEINLINE bool FFixedQuat64::Equals(const FFixedQuat64& Q, FFixed64 Tolerance) const
{
	return (FFixedPointMath::Abs(X - Q.X) <= Tolerance && FFixedPointMath::Abs(Y - Q.Y) <= Tolerance && FFixedPointMath::Abs(Z - Q.Z) <= Tolerance && FFixedPointMath::Abs(W - Q.W) <= Tolerance)
		|| (FFixedPointMath::Abs(X + Q.X) <= Tolerance && FFixedPointMath::Abs(Y + Q.Y) <= Tolerance && FFixedPointMath::Abs(Z + Q.Z) <= Tolerance && FFixedPointMath::Abs(W + Q.W) <= Tolerance);
}

FORCEINLINE bool FFixedQuat64::IsIdentity(FFixed64 Tolerance) const
{
	return Equals(FFixedQuat64::Identity, Tolerance);
}

FORCEINLINE FFixedQuat64 FFixedQuat64::operator-=(const FFixedQuat64& Q)
{
	this->X -= Q.X;
	this->Y -= Q.Y;
	this->Z -= Q.Z;
	this->W -= Q.W;

	return *this;
}

FORCEINLINE FFixedQuat64 FFixedQuat64::operator*(const FFixedQuat64& Q) const
{
	return FFixedQuat64(
		W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z,  // 1
		W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,  // i
		W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,  // j
		W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W   // k
	);
}

FORCEINLINE FFixedQuat64 FFixedQuat64::operator*=(const FFixedQuat64& Q)
{
	this->X = W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z;  // 1
	this->Y = W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y;  // i
	this->Z = W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X;  // j
	this->W = W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W;   // k

	return *this;
}

FORCEINLINE bool FFixedQuat64::Identical(const FFixedQuat64* Q, const uint32 PortFlags) const
{
	return X == Q->X && Y == Q->Y && Z == Q->Z && W == Q->W;
}

FORCEINLINE bool FFixedQuat64::operator==(const FFixedQuat64& Q) const
{
	return X == Q.X && Y == Q.Y && Z == Q.Z && W == Q.W;
}

FORCEINLINE bool FFixedQuat64::operator!=(const FFixedQuat64& Q) const
{
	return X != Q.X || Y != Q.Y || Z != Q.Z || W != Q.W;
}

FORCEINLINE FFixed64 FFixedQuat64::operator|(const FFixedQuat64& Q) const
{
	return X * Q.X + Y * Q.Y + Z * Q.Z + W * Q.W;
}
// Global operator for (fixed32 * Quat)
FORCEINLINE FFixedQuat64 operator*(const FFixed32 Scale, const FFixedQuat64& Q)
{
	return Q.operator*(Scale);
}

// Global operator for (double * Quat)
FORCEINLINE FFixedQuat64 operator*(const FFixed64 Scale, const FFixedQuat64& Q)
{
	return Q.operator*(Scale);
}
