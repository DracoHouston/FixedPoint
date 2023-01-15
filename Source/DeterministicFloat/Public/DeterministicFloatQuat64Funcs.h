// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatQuat64.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatMatrix64.h"
#include "Misc/AssertionMacros.h"
#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatRotator64Funcs.h"
#include "DeterministicFloatMatrix64Funcs.h"

FORCEINLINE FDeterministicQuat64::FDeterministicQuat64() {}

FORCEINLINE FDeterministicQuat64::FDeterministicQuat64(FQuat Other)
{
	X = (FDeterministicNumber64)Other.X;
	Y = (FDeterministicNumber64)Other.Y;
	Z = (FDeterministicNumber64)Other.Z;
	W = (FDeterministicNumber64)Other.W;
}

FORCEINLINE FDeterministicQuat64::FDeterministicQuat64(EForceInit ZeroOrNot)
{
	X = FDeterministicNumber64();
	Y = FDeterministicNumber64();
	Z = FDeterministicNumber64();
	W = ZeroOrNot == EForceInit::ForceInitToZero ? FDeterministicNumber64() : FDeterministicNumber64((int64)1);
}

FORCEINLINE FDeterministicQuat64::FDeterministicQuat64(const FDeterministicVector64& inAxis, const FDeterministicNumber64& inAngleRad)
{
	const FDeterministicNumber64 half_a = DeterministicFloat::Constants::Number64::Half * inAngleRad;
	FDeterministicNumber64 s, c;
	FDeterministicFloatMath::SinCos(&s, &c, half_a);

	X = s * inAxis.X;
	Y = s * inAxis.Y;
	Z = s * inAxis.Z;
	W = c;
}

FORCEINLINE FDeterministicQuat64::FDeterministicQuat64(const FDeterministicNumber64& inValue)
{
	X = inValue;
	Y = inValue;
	Z = inValue;
	W = inValue;
}

FORCEINLINE FDeterministicQuat64::FDeterministicQuat64(const FDeterministicNumber64& inX, const FDeterministicNumber64& inY, const FDeterministicNumber64& inZ, const FDeterministicNumber64& inW)
{
	X = inX;
	Y = inY;
	Z = inZ;
	W = inW;
}

FORCEINLINE FDeterministicQuat64::FDeterministicQuat64(const FDeterministicRotator64& R)
{
	*this = R.Quaternion();
}

inline FDeterministicQuat64::FDeterministicQuat64(const FDeterministicMatrix64& M)
{
	// If Matrix is NULL, return Identity quaternion. If any of them is 0, you won't be able to construct rotation
	// if you have two plane at least, we can reconstruct the frame using cross product, but that's a bit expensive op to do here
	// for now, if you convert to matrix from 0 scale and convert back, you'll lose rotation. Don't do that. 
	if (M.GetScaledAxis(EAxis::X).IsNearlyZero() || M.GetScaledAxis(EAxis::Y).IsNearlyZero() || M.GetScaledAxis(EAxis::Z).IsNearlyZero())
	{
		*this = FDeterministicQuat64::Identity;
		return;
	}

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// Make sure the Rotation part of the Matrix is unit length.
	// Changed to this (same as RemoveScaling) from RotDeterminant as using two different ways of checking unit length matrix caused inconsistency. 
	if (!ensure((FDeterministicFloatMath::Abs(DeterministicFloat::Constants::Number64::One - M.GetScaledAxis(EAxis::X).SizeSquared()) <= DeterministicFloat::Constants::Number64::KindaSmallNumber) && (FDeterministicFloatMath::Abs(DeterministicFloat::Constants::Number64::One - M.GetScaledAxis(EAxis::Y).SizeSquared()) <= DeterministicFloat::Constants::Number64::KindaSmallNumber) && (FDeterministicFloatMath::Abs(DeterministicFloat::Constants::Number64::One - M.GetScaledAxis(EAxis::Z).SizeSquared()) <= DeterministicFloat::Constants::Number64::KindaSmallNumber)))
	{
		*this = FDeterministicQuat64::Identity;
		return;
	}
#endif

	//const MeReal *const t = (MeReal *) tm;
	FDeterministicNumber64 s;

	// Check diagonal (trace)
	const FDeterministicNumber64 tr = M.M[0][0] + M.M[1][1] + M.M[2][2];

	if (tr > FDeterministicNumber64(0.0f))
	{
		FDeterministicNumber64 InvS = FDeterministicNumber64();// = FMath::InvSqrt(tr + T(1.f));
		this->W = FDeterministicNumber64(FDeterministicNumber64(0.5f) * (FDeterministicNumber64(1.f) / InvS));
		s = FDeterministicNumber64(0.5f) * InvS;

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

		s = M.M[i][i] - M.M[j][j] - M.M[k][k] + FDeterministicNumber64(1.0f);

		FDeterministicNumber64 InvS = FDeterministicNumber64((int64)1) / FDeterministicFloatMath::Sqrt(s);

		FDeterministicNumber64 qt[4];
		qt[i] = FDeterministicNumber64(0.5f) * (FDeterministicNumber64(1.f) / InvS);

		s = FDeterministicNumber64(0.5f) * InvS;

		qt[3] = (M.M[j][k] - M.M[k][j]) * s;
		qt[j] = (M.M[i][j] + M.M[j][i]) * s;
		qt[k] = (M.M[i][k] + M.M[k][i]) * s;

		this->X = qt[0];
		this->Y = qt[1];
		this->Z = qt[2];
		this->W = qt[3];

	}
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator+(const FDeterministicQuat64& Q) const
{
	return FDeterministicQuat64(X + Q.X, Y + Q.Y, Z + Q.Z, W + Q.W);
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator+=(const FDeterministicQuat64& Q)
{
	this->X += Q.X;
	this->Y += Q.Y;
	this->Z += Q.Z;
	this->W += Q.W;

	return *this;
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator-(const FDeterministicQuat64& Q) const
{
	return FDeterministicQuat64(X - Q.X, Y - Q.Y, Z - Q.Z, W - Q.W);
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator-() const
{
	return FDeterministicQuat64(-X, -Y, -Z, -W);
}

FORCEINLINE bool FDeterministicQuat64::Equals(const FDeterministicQuat64& Q, FDeterministicNumber64 Tolerance) const
{
	return (FDeterministicFloatMath::Abs(X - Q.X) <= Tolerance && FDeterministicFloatMath::Abs(Y - Q.Y) <= Tolerance && FDeterministicFloatMath::Abs(Z - Q.Z) <= Tolerance && FDeterministicFloatMath::Abs(W - Q.W) <= Tolerance)
		|| (FDeterministicFloatMath::Abs(X + Q.X) <= Tolerance && FDeterministicFloatMath::Abs(Y + Q.Y) <= Tolerance && FDeterministicFloatMath::Abs(Z + Q.Z) <= Tolerance && FDeterministicFloatMath::Abs(W + Q.W) <= Tolerance);
}

FORCEINLINE bool FDeterministicQuat64::IsIdentity(FDeterministicNumber64 Tolerance) const
{
	return Equals(FDeterministicQuat64::Identity, Tolerance);
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator-=(const FDeterministicQuat64& Q)
{
	this->X -= Q.X;
	this->Y -= Q.Y;
	this->Z -= Q.Z;
	this->W -= Q.W;

	return *this;
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator*(const FDeterministicQuat64& Q) const
{
	return FDeterministicQuat64(
		W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z,  // 1
		W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,  // i
		W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,  // j
		W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W   // k
	);
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator*=(const FDeterministicQuat64& Q)
{
	this->X = W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z;  // 1
	this->Y = W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y;  // i
	this->Z = W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X;  // j
	this->W = W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W;   // k

	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicQuat64::operator*(const FDeterministicVector64& V) const
{
	return RotateVector(V);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicQuat64::operator*(const FDeterministicMatrix64& M) const
{
	FDeterministicMatrix64 Result;
	const FDeterministicQuat64 Inv = Inverse();
	for (int32 I = 0; I < 4; ++I)
	{
		FDeterministicQuat64 VT, VR;
		const FDeterministicQuat64 VQ(M.M[I][0], M.M[I][1], M.M[I][2], M.M[I][3]);
		VT = *this * VQ;
		VR = VT * Inv;
		Result.M[I][0] = VR.X;
		Result.M[I][1] = VR.Y;
		Result.M[I][2] = VR.Z;
		Result.M[I][3] = VR.W;
	}

	return Result;
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator*=(const FDeterministicNumber64& Scale)
{
	X *= Scale;
	Y *= Scale;
	Z *= Scale;
	W *= Scale;
	return *this;
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator*(const FDeterministicNumber64& Scale) const
{
	return FDeterministicQuat64(Scale * X, Scale * Y, Scale * Z, Scale * W);
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator/=(const FDeterministicNumber64& Scale)
{
	const FDeterministicNumber64 Recip = FDeterministicNumber64((int64)1) / Scale;
	X *= Recip;
	Y *= Recip;
	Z *= Recip;
	W *= Recip;
	return *this;
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::operator/(const FDeterministicNumber64& Scale) const
{
	const FDeterministicNumber64 Recip = FDeterministicNumber64((int64)1) / Scale;
	return FDeterministicQuat64(X * Recip, Y * Recip, Z * Recip, W * Recip);
}

FORCEINLINE bool FDeterministicQuat64::Identical(const FDeterministicQuat64* Q, const uint32 PortFlags) const
{
	return X == Q->X && Y == Q->Y && Z == Q->Z && W == Q->W;
}

FORCEINLINE bool FDeterministicQuat64::operator==(const FDeterministicQuat64& Q) const
{
	return X == Q.X && Y == Q.Y && Z == Q.Z && W == Q.W;
}

FORCEINLINE bool FDeterministicQuat64::operator!=(const FDeterministicQuat64& Q) const
{
	return X != Q.X || Y != Q.Y || Z != Q.Z || W != Q.W;
}

FORCEINLINE FDeterministicNumber64 FDeterministicQuat64::operator|(const FDeterministicQuat64& Q) const
{
	return X * Q.X + Y * Q.Y + Z * Q.Z + W * Q.W;
}

FORCEINLINE bool FDeterministicQuat64::IsNormalized() const
{
	return (FDeterministicFloatMath::Abs(DeterministicFloat::Constants::Number64::One - SizeSquared()) < DeterministicFloat::Constants::Number64::ThreshQuatNormalized);
}

FORCEINLINE FDeterministicNumber64 FDeterministicQuat64::Size() const
{
	return FDeterministicFloatMath::Sqrt(X * X + Y * Y + Z * Z + W * W);
}

FORCEINLINE FDeterministicNumber64 FDeterministicQuat64::SizeSquared() const
{
	return (X * X + Y * Y + Z * Z + W * W);
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::Inverse() const
{
	checkSlow(IsNormalized());

	return FDeterministicQuat64(-X, -Y, -Z, W);
}

FORCEINLINE void FDeterministicQuat64::Normalize(FDeterministicNumber64 Tolerance)
{
	const FDeterministicNumber64 SquareSum = X * X + Y * Y + Z * Z + W * W;

	if (SquareSum >= Tolerance)
	{
		const FDeterministicNumber64 Scale = FDeterministicFloatMath::InvSqrt(SquareSum);

		X *= Scale;
		Y *= Scale;
		Z *= Scale;
		W *= Scale;
	}
	else
	{
		*this = FDeterministicQuat64::Identity;
	}
}

FORCEINLINE FString FDeterministicQuat64::ToString() const
{
	return FString::Printf(TEXT("X=%.9f Y=%.9f Z=%.9f W=%.9f"), (double)X, (double)Y, (double)Z, (double)W);
}

FORCEINLINE FDeterministicVector64 FDeterministicQuat64::RotateVector(FDeterministicVector64 V) const
{
	// http://people.csail.mit.edu/bkph/articles/Quaternions.pdf
	// V' = V + 2w(Q x V) + (2Q x (Q x V))
	// refactor:
	// V' = V + w(2(Q x V)) + (Q x (2(Q x V)))
	// T = 2(Q x V);
	// V' = V + w*(T) + (Q x T)

	const FDeterministicVector64 Q(X, Y, Z);
	const FDeterministicVector64 TT = FDeterministicVector64::CrossProduct(Q, V) * FDeterministicNumber64::Make(2.0);
	const FDeterministicVector64 Result = V + (TT * W) + FDeterministicVector64::CrossProduct(Q, TT);
	return Result;
}

FORCEINLINE FDeterministicVector64 FDeterministicQuat64::UnrotateVector(FDeterministicVector64 V) const
{
	const FDeterministicVector64 Q(-X, -Y, -Z); // Inverse
	const FDeterministicVector64 TT = FDeterministicNumber64::Make(2.0) * FDeterministicVector64::CrossProduct(Q, V);
	const FDeterministicVector64 Result = V + (W * TT) + FDeterministicVector64::CrossProduct(Q, TT);
	return Result;
}

FORCEINLINE FDeterministicQuat64 FDeterministicQuat64::FastLerp(const FDeterministicQuat64& A, const FDeterministicQuat64& B, const FDeterministicNumber64 Alpha)
{
	// To ensure the 'shortest route', we make sure the dot product between the both rotations is positive.
	const FDeterministicNumber64 DotResult = (A | B);
	const FDeterministicNumber64 Bias = FDeterministicFloatMath::FloatSelect(DotResult, DeterministicFloat::Constants::Number64::One, -DeterministicFloat::Constants::Number64::One);
	return (B * Alpha) + (A * (Bias * (DeterministicFloat::Constants::Number64::One - Alpha)));
}

FORCEINLINE FDeterministicQuat64::operator FQuat() const
{
	return FQuat((double)X, (double)Y, (double)Z, (double)W);
}