// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatPlane64.h"
#include "DeterministicFloatVector64Funcs.h"

FORCEINLINE FDeterministicPlane64::FDeterministicPlane64()
{
}

FORCEINLINE FDeterministicPlane64::FDeterministicPlane64(const FDeterministicVector4D64& V)
	: FDeterministicVector64(V), W(V.W) 
{
}

FORCEINLINE FDeterministicPlane64::FDeterministicPlane64(FDeterministicNumber64 InX, FDeterministicNumber64 InY, FDeterministicNumber64 InZ, FDeterministicNumber64 InW) 
	: FDeterministicVector64(InX, InY, InZ), W(InW)
{
}

FORCEINLINE FDeterministicPlane64::FDeterministicPlane64(FDeterministicVector64 InNormal, FDeterministicNumber64 InW) 
	: FDeterministicVector64(InNormal), W(InW)
{
}

FORCEINLINE FDeterministicPlane64::FDeterministicPlane64(FDeterministicVector64 InBase, const FDeterministicVector64& InNormal) 
	: FDeterministicVector64(InNormal), W(InBase | InNormal)
{
}

FORCEINLINE FDeterministicPlane64::FDeterministicPlane64(FDeterministicVector64 A, FDeterministicVector64 B, FDeterministicVector64 C) 
	: FDeterministicVector64(((B - A) ^ (C - A)).GetSafeNormal())
{
	W = A | (FDeterministicVector64)(*this);
}

FORCEINLINE FDeterministicPlane64::FDeterministicPlane64(EForceInit)
	: FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero), W(DeterministicFloat::Constants::Number64::Zero)
{}

FORCEINLINE bool FDeterministicPlane64::IsValid() const
{
	return !this->IsNearlyZero();
}

FORCEINLINE FDeterministicVector64 FDeterministicPlane64::GetOrigin() const
{
	return GetNormal() * W;
}

FORCEINLINE const FDeterministicVector64& FDeterministicPlane64::GetNormal() const
{
	return *this;
}

FORCEINLINE FDeterministicNumber64 FDeterministicPlane64::PlaneDot(const FDeterministicVector64& P) const
{
	return X * P.X + Y * P.Y + Z * P.Z - W;
}

FORCEINLINE bool FDeterministicPlane64::Normalize(FDeterministicNumber64 Tolerance)
{
	const FDeterministicNumber64 SquareSum = X * X + Y * Y + Z * Z;
	if (SquareSum > Tolerance)
	{
		const FDeterministicNumber64 Scale = FDeterministicFloatMath::InvSqrt(SquareSum);
		X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
		return true;
	}
	return false;
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::Flip() const
{
	return FDeterministicPlane64(-X, -Y, -Z, -W);
}

inline FDeterministicPlane64 FDeterministicPlane64::TransformBy(const FDeterministicMatrix64& M) const
{
	const FDeterministicMatrix64 tmpTA = M.TransposeAdjoint();
	const FDeterministicNumber64 DetM = M.Determinant();
	return this->TransformByUsingAdjointT(M, DetM, tmpTA);
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::TransformByUsingAdjointT(const FDeterministicMatrix64& M, FDeterministicNumber64 DetM, const FDeterministicMatrix64& TA) const 
{
	FDeterministicVector64 newNorm = TA.TransformVector(*this).GetSafeNormal();

	if (DetM < DeterministicFloat::Constants::Number64::Zero)
	{
		newNorm *= -DeterministicFloat::Constants::Number64::One;
	}

	return FDeterministicPlane64(M.TransformPosition(*this * W), newNorm);
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::TranslateBy(const FDeterministicVector64& V) const
{
	return FDeterministicPlane64(GetOrigin() + V, GetNormal());
}

FORCEINLINE bool FDeterministicPlane64::operator==(const FDeterministicPlane64& V) const
{
	return (X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W);
}

FORCEINLINE bool FDeterministicPlane64::operator!=(const FDeterministicPlane64& V) const
{
	return (X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W);
}

FORCEINLINE bool FDeterministicPlane64::Equals(const FDeterministicPlane64& V, FDeterministicNumber64 Tolerance) const
{
	return (FDeterministicFloatMath::Abs(X - V.X) < Tolerance) && (FDeterministicFloatMath::Abs(Y - V.Y) < Tolerance) && (FDeterministicFloatMath::Abs(Z - V.Z) < Tolerance) && (FDeterministicFloatMath::Abs(W - V.W) < Tolerance);
}

FORCEINLINE FDeterministicNumber64 FDeterministicPlane64::operator|(const FDeterministicPlane64& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator+(const FDeterministicPlane64& V) const
{
	return FDeterministicPlane64(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator-(const FDeterministicPlane64& V) const
{
	return FDeterministicPlane64(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator/(FDeterministicNumber64 Scale) const
{
	const FDeterministicNumber64 RScale = DeterministicFloat::Constants::Number64::One / Scale;
	return FDeterministicPlane64(X * RScale, Y * RScale, Z * RScale, W * RScale);
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator*(FDeterministicNumber64 Scale) const
{
	return FDeterministicPlane64(X * Scale, Y * Scale, Z * Scale, W * Scale);
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator*(const FDeterministicPlane64& V)
{
	return FDeterministicPlane64(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator+=(const FDeterministicPlane64& V)
{
	X += V.X; Y += V.Y; Z += V.Z; W += V.W;
	return *this;
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator-=(const FDeterministicPlane64& V)
{
	X -= V.X; Y -= V.Y; Z -= V.Z; W -= V.W;
	return *this;
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator*=(FDeterministicNumber64 Scale)
{
	X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
	return *this;
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator*=(const FDeterministicPlane64& V)
{
	X *= V.X; Y *= V.Y; Z *= V.Z; W *= V.W;
	return *this;
}

FORCEINLINE FDeterministicPlane64 FDeterministicPlane64::operator/=(FDeterministicNumber64 V)
{
	const FDeterministicNumber64 RV = DeterministicFloat::Constants::Number64::One / V;
	X *= RV; Y *= RV; Z *= RV; W *= RV;
	return *this;
}
