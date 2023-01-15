// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatVector64.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatVector2D64.h"
#include "DeterministicFloatVector4D64.h"
#include "Misc/AssertionMacros.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatMathFuncs.h"
#include "DeterministicFloatRotator64Funcs.h"

FORCEINLINE FDeterministicVector64::FDeterministicVector64(const FDeterministicVector2D64& V, const FDeterministicNumber64& InZ)
{
	X = V.X;
	Y = V.Y;
	Z = InZ;
}

FORCEINLINE FDeterministicVector64::FDeterministicVector64(const FDeterministicVector4D64& V)
{
	X = V.X;
	Y = V.Y;
	Z = V.Z;
}

FORCEINLINE FDeterministicVector64 ClampVector(const FDeterministicVector64& V, const FDeterministicVector64& Min, const FDeterministicVector64& Max)
{
	return FDeterministicVector64(
		FDeterministicFloatMath::Clamp(V.X, Min.X, Max.X),
		FDeterministicFloatMath::Clamp(V.Y, Min.Y, Max.Y),
		FDeterministicFloatMath::Clamp(V.Z, Min.Z, Max.Z)
	);
}

FORCEINLINE FDeterministicNumber64 ComputeSquaredDistanceFromBoxToPoint(const FDeterministicVector64& Mins, const FDeterministicVector64& Maxs, const FDeterministicVector64& Point)
{
	// Accumulates the distance as we iterate axis
	FDeterministicNumber64 DistSquared = 0;

	// Check each axis for min/max and add the distance accordingly
	// NOTE: Loop manually unrolled for > 2x speed up
	if (Point.X < Mins.X)
	{
		DistSquared += FDeterministicFloatMath::Square(Point.X - Mins.X);
	}
	else if (Point.X > Maxs.X)
	{
		DistSquared += FDeterministicFloatMath::Square(Point.X - Maxs.X);
	}

	if (Point.Y < Mins.Y)
	{
		DistSquared += FDeterministicFloatMath::Square(Point.Y - Mins.Y);
	}
	else if (Point.Y > Maxs.Y)
	{
		DistSquared += FDeterministicFloatMath::Square(Point.Y - Maxs.Y);
	}

	if (Point.Z < Mins.Z)
	{
		DistSquared += FDeterministicFloatMath::Square(Point.Z - Mins.Z);
	}
	else if (Point.Z > Maxs.Z)
	{
		DistSquared += FDeterministicFloatMath::Square(Point.Z - Maxs.Z);
	}

	return DistSquared;
}

FORCEINLINE bool FDeterministicVector64::Equals(const FDeterministicVector64& Other, const FDeterministicNumber64& inTolerance) const
{
	return FDeterministicFloatMath::Abs(X - Other.X) <= inTolerance && FDeterministicFloatMath::Abs(Y - Other.Y) <= inTolerance && FDeterministicFloatMath::Abs(Z - Other.Z) <= inTolerance;
}

FORCEINLINE bool FDeterministicVector64::AllComponentsEqual(const FDeterministicNumber64& inTolerance) const
{
	return FDeterministicFloatMath::IsEqual(X, Y, inTolerance) && FDeterministicFloatMath::IsEqual(X, Z, inTolerance) && FDeterministicFloatMath::IsEqual(Y, Z, inTolerance);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::GetMax() const
{
	return FDeterministicFloatMath::Max(FDeterministicFloatMath::Max(X, Y), Z);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::GetAbsMax() const
{
	return FDeterministicFloatMath::Max(FDeterministicFloatMath::Max(FDeterministicFloatMath::Abs(X), FDeterministicFloatMath::Abs(Y)), FDeterministicFloatMath::Abs(Z));
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::GetMin() const
{
	return FDeterministicFloatMath::Min(FDeterministicFloatMath::Min(X, Y), Z);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::GetAbsMin() const
{
	return FDeterministicFloatMath::Min(FDeterministicFloatMath::Min(FDeterministicFloatMath::Abs(X), FDeterministicFloatMath::Abs(Y)), FDeterministicFloatMath::Abs(Z));
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetAbs() const
{
	return FDeterministicVector64(FDeterministicFloatMath::Abs(X), FDeterministicFloatMath::Abs(Y), FDeterministicFloatMath::Abs(Z));
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::ComponentMin(const FDeterministicVector64& Other) const
{
	return FDeterministicVector64(FDeterministicFloatMath::Min(X, Other.X), FDeterministicFloatMath::Min(Y, Other.Y), FDeterministicFloatMath::Min(Z, Other.Z));
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::ComponentMax(const FDeterministicVector64& Other) const
{
	return FDeterministicVector64(FDeterministicFloatMath::Max(X, Other.X), FDeterministicFloatMath::Max(Y, Other.Y), FDeterministicFloatMath::Max(Z, Other.Z));
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::SizeSquared() const
{
	return (X * X) + (Y * Y) + (Z * Z);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::Size() const
{
	return FDeterministicFloatMath::Sqrt(SizeSquared());
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::Size2D() const
{
	return FDeterministicFloatMath::Sqrt(X * X + Y * Y);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::SizeSquared2D() const
{
	return X * X + Y * Y;
}

FORCEINLINE bool FDeterministicVector64::IsNearlyZero(const FDeterministicNumber64& Tolerance) const
{
	return
		FDeterministicFloatMath::Abs(X) <= Tolerance
		&& FDeterministicFloatMath::Abs(Y) <= Tolerance
		&& FDeterministicFloatMath::Abs(Z) <= Tolerance;
}

FORCEINLINE bool FDeterministicVector64::IsZero() const
{
	return X == DeterministicFloat::Constants::Number64::Zero && Y == DeterministicFloat::Constants::Number64::Zero && Z == DeterministicFloat::Constants::Number64::Zero;
}

FORCEINLINE bool FDeterministicVector64::IsUnit(const FDeterministicNumber64& LengthSquaredTolerance) const
{
	return FDeterministicFloatMath::Abs(DeterministicFloat::Constants::Number64::One - SizeSquared()) < LengthSquaredTolerance;
}

FORCEINLINE bool FDeterministicVector64::IsNormalized() const
{
	return (FDeterministicFloatMath::Abs(DeterministicFloat::Constants::Number64::One - SizeSquared()) < DeterministicFloat::Constants::Number64::ThreshVectorNormalized);
}

FORCEINLINE bool FDeterministicVector64::Normalize(FDeterministicNumber64 Tolerance)
{
	const FDeterministicNumber64 SquareSum = (X * X) + (Y * Y) + (Z * Z);
	if (SquareSum > Tolerance)
	{
		const FDeterministicNumber64 Scale = FDeterministicFloatMath::InvSqrt(SquareSum);
		X *= Scale; Y *= Scale; Z *= Scale;
		return true;
	}
	return false;
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::DistSquared(const FDeterministicVector64& A, const FDeterministicVector64& B)
{
	return FDeterministicFloatMath::Square(B.X - A.X) + FDeterministicFloatMath::Square(B.Y - A.Y) + FDeterministicFloatMath::Square(B.Z - A.Z);
}
	
FORCEINLINE FDeterministicNumber64 FDeterministicVector64::Dist(const FDeterministicVector64& A, const FDeterministicVector64& B)
{
	return FDeterministicFloatMath::Sqrt(FDeterministicVector64::DistSquared(A, B));
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::Distance(const FDeterministicVector64& V1, const FDeterministicVector64& V2) 
{ 
	return Dist(V1, V2); 
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::DistSquaredXY(const FDeterministicVector64& V1, const FDeterministicVector64& V2)
{
	return FMath::Square(V2.X - V1.X) + FMath::Square(V2.Y - V1.Y);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::DistSquared2D(const FDeterministicVector64& V1, const FDeterministicVector64& V2) 
{ 
	return DistSquaredXY(V1, V2); 
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::DistXY(const FDeterministicVector64& V1, const FDeterministicVector64& V2)
{
	return FDeterministicFloatMath::Sqrt(DistSquaredXY(V1, V2));
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::Dist2D(const FDeterministicVector64& V1, const FDeterministicVector64& V2) 
{ 
	return DistXY(V1, V2); 
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::Cross(const FDeterministicVector64& V2) const
{
	return *this ^ V2;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::CrossProduct(const FDeterministicVector64& A, const FDeterministicVector64& B)
{
	return A ^ B;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::DotProduct(const FDeterministicVector64& A, const FDeterministicVector64& B)
{
	return A | B;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::Triple(const FDeterministicVector64& X, const FDeterministicVector64& Y, const FDeterministicVector64& Z)
{
	return
		((X.X * (Y.Y * Z.Z - Y.Z * Z.Y))
			+ (X.Y * (Y.Z * Z.X - Y.X * Z.Z))
			+ (X.Z * (Y.X * Z.Y - Y.Y * Z.X)));
}

FORCEINLINE bool FDeterministicVector64::operator==(const FDeterministicVector64& Other) const
{
	return ((X == Other.X) && (Y == Other.Y) && (Z == Other.Z));
}

FORCEINLINE bool FDeterministicVector64::operator!=(const FDeterministicVector64& Other) const
{
	return ((X != Other.X) && (Y != Other.Y) && (Z != Other.Z));
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator-() const
{
	return FDeterministicVector64(-X, -Y, -Z);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator+(const FDeterministicVector64& Other) const
{
	return FDeterministicVector64(X + Other.X, Y + Other.Y, Z + Other.Z);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator-(const FDeterministicVector64& Other) const
{
	return FDeterministicVector64(X - Other.X, Y - Other.Y, Z - Other.Z);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator*(const FDeterministicVector64& Other) const
{
	return FDeterministicVector64(X * Other.X, Y * Other.Y, Z * Other.Z);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator/(const FDeterministicVector64& Other) const
{
	return FDeterministicVector64(X / Other.X, Y / Other.Y, Z / Other.Z);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator+(const FDeterministicNumber64& Other) const
{
	return FDeterministicVector64(X + Other, Y + Other, Z + Other);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator-(const FDeterministicNumber64& Other) const
{
	return FDeterministicVector64(X - Other, Y - Other, Z - Other);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator*(const FDeterministicNumber64& Other) const
{
	return FDeterministicVector64(X * Other, Y * Other, Z * Other);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator/(const FDeterministicNumber64& Other) const
{
	return FDeterministicVector64(X / Other, Y / Other, Z / Other);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator+=(const FDeterministicVector64& Other)
{
	X += Other.X;
	Y += Other.Y;
	Z += Other.Z;
	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator-=(const FDeterministicVector64& Other)
{
	X -= Other.X;
	Y -= Other.Y;
	Z -= Other.Z;
	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator*=(const FDeterministicVector64& Other)
{
	X *= Other.X;
	Y *= Other.Y;
	Z *= Other.Z;
	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator/=(const FDeterministicVector64& Other)
{
	X /= Other.X;
	Y /= Other.Y;
	Z /= Other.Z;
	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator+=(const FDeterministicNumber64& Other)
{
	X += Other;
	Y += Other;
	Z += Other;
	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator-=(const FDeterministicNumber64& Other)
{
	X -= Other;
	Y -= Other;
	Z -= Other;
	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator*=(const FDeterministicNumber64& Other)
{
	X *= Other;
	Y *= Other;
	Z *= Other;
	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator/=(const FDeterministicNumber64& Other)
{
	X /= Other;
	Y /= Other;
	Z /= Other;
	return *this;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::operator^(const FDeterministicVector64& Other) const
{
	return FDeterministicVector64
	(
		(Y * Other.Z) - (Z * Other.Y),
		(Z * Other.X) - (X * Other.Z),
		(X * Other.Y) - (Y * Other.X)
	);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::operator|(const FDeterministicVector64& Other) const
{
	return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z);
}

FORCEINLINE FDeterministicNumber64& FDeterministicVector64::operator[](int32 Index)
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

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::operator[](int32 Index)const
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

FORCEINLINE FDeterministicNumber64& FDeterministicVector64::Component(int32 Index)
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

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::Component(int32 Index) const
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

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::GetComponentForAxis(EAxis::Type Axis) const
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

FORCEINLINE void FDeterministicVector64::SetComponentForAxis(EAxis::Type Axis, const FDeterministicNumber64& Component)
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

FORCEINLINE void FDeterministicVector64::Set(const FDeterministicNumber64& InX, const FDeterministicNumber64& InY, const FDeterministicNumber64& InZ)
{
	X = InX;
	Y = InY;
	Z = InZ;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetUnsafeNormal() const
{
	const FDeterministicNumber64 Scale = FDeterministicFloatMath::InvSqrt(X * X + Y * Y + Z * Z);
	return FDeterministicVector64(X * Scale, Y * Scale, Z * Scale);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetSafeNormal(const FDeterministicNumber64& Tolerance, const FDeterministicVector64& ResultIfZero) const
{
	const FDeterministicNumber64 SquareSum = X * X + Y * Y + Z * Z;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (SquareSum == DeterministicFloat::Constants::Number64::One)
	{
		return *this;
	}
	else if (SquareSum < Tolerance)
	{
		return ResultIfZero;
	}
	const FDeterministicNumber64 Scale = FDeterministicFloatMath::InvSqrt(SquareSum);
	return FDeterministicVector64(X * Scale, Y * Scale, Z * Scale);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetUnsafeNormal2D() const
{
	const FDeterministicNumber64 Scale = FDeterministicFloatMath::InvSqrt(X * X + Y * Y);
	return FDeterministicVector64(X * Scale, Y * Scale, DeterministicFloat::Constants::Number64::Zero);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetSafeNormal2D(const FDeterministicNumber64& Tolerance, const FDeterministicVector64& ResultIfZero) const
{
	const FDeterministicNumber64 SquareSum = X * X + Y * Y;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (SquareSum == DeterministicFloat::Constants::Number64::One)
	{
		if (Z == DeterministicFloat::Constants::Number64::Zero)
		{
			return *this;
		}
		else
		{
			return FDeterministicVector64(X, Y, 0.f);
		}
	}
	else if (SquareSum < Tolerance)
	{
		return ResultIfZero;
	}

	const FDeterministicNumber64 Scale = FDeterministicFloatMath::InvSqrt(SquareSum);
	return FDeterministicVector64(X * Scale, Y * Scale, 0.f);
}

FORCEINLINE void FDeterministicVector64::ToDirectionAndLength(FDeterministicVector64& OutDir, FDeterministicNumber64& OutLength) const
{
	OutLength = Size();
	if (OutLength > DeterministicFloat::Constants::Number64::SmallNumber)
	{
		FDeterministicNumber64 OneOverLength = DeterministicFloat::Constants::Number64::One / OutLength;
		OutDir = FDeterministicVector64(X * OneOverLength, Y * OneOverLength, Z * OneOverLength);
	}
	else
	{
		OutDir = ZeroVector;
	}
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetSignVector() const
{
	return FDeterministicVector64
		(
			FDeterministicFloatMath::FloatSelect(X, DeterministicFloat::Constants::Number64::One, -DeterministicFloat::Constants::Number64::One),
			FDeterministicFloatMath::FloatSelect(Y, DeterministicFloat::Constants::Number64::One, -DeterministicFloat::Constants::Number64::One),
			FDeterministicFloatMath::FloatSelect(Z, DeterministicFloat::Constants::Number64::One, -DeterministicFloat::Constants::Number64::One)
		);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::Projection() const
{
	const FDeterministicNumber64 RZ = DeterministicFloat::Constants::Number64::One / Z;
	return FDeterministicVector64(X * RZ, Y * RZ, DeterministicFloat::Constants::Number64::One);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GridSnap(const FDeterministicNumber64& GridSz) const
{
	return FDeterministicVector64(FDeterministicFloatMath::GridSnap(X, GridSz), FDeterministicFloatMath::GridSnap(Y, GridSz), FDeterministicFloatMath::GridSnap(Z, GridSz));
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::BoundToCube(FDeterministicNumber64 Radius) const
{
	return FDeterministicVector64
		(
			FDeterministicFloatMath::Clamp(X, -Radius, Radius),
			FDeterministicFloatMath::Clamp(Y, -Radius, Radius),
			FDeterministicFloatMath::Clamp(Z, -Radius, Radius)
		);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::BoundToBox(const FDeterministicVector64& Min, const FDeterministicVector64& Max) const
{
	return FDeterministicVector64
		(
			FDeterministicFloatMath::Clamp(X, Min.X, Max.X),
			FDeterministicFloatMath::Clamp(Y, Min.Y, Max.Y),
			FDeterministicFloatMath::Clamp(Z, Min.Z, Max.Z)
		);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetClampedToSize(FDeterministicNumber64 Min, FDeterministicNumber64 Max) const
{
	FDeterministicNumber64 VecSize = Size();
	const FDeterministicVector64 VecDir = (VecSize > DeterministicFloat::Constants::Number64::SmallNumber) ? (*this / VecSize) : ZeroVector;

	VecSize = FDeterministicFloatMath::Clamp(VecSize, Min, Max);

	return VecDir * VecSize;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetClampedToSize2D(FDeterministicNumber64 Min, FDeterministicNumber64 Max) const
{
	FDeterministicNumber64 VecSize2D = Size2D();
	const FDeterministicVector64 VecDir = (VecSize2D > DeterministicFloat::Constants::Number64::SmallNumber) ? (*this / VecSize2D) : ZeroVector;

	VecSize2D = FDeterministicFloatMath::Clamp(VecSize2D, Min, Max);

	return FDeterministicVector64(VecSize2D * VecDir.X, VecSize2D * VecDir.Y, Z);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetClampedToMaxSize(FDeterministicNumber64 MaxSize) const
{
	if (MaxSize < DeterministicFloat::Constants::Number64::KindaSmallNumber)
	{
		return ZeroVector;
	}

	const FDeterministicNumber64 VSq = SizeSquared();
	if (VSq > FDeterministicFloatMath::Square(MaxSize))
	{
		const FDeterministicNumber64 Scale = MaxSize * FDeterministicFloatMath::InvSqrt(VSq);
		return FDeterministicVector64(X * Scale, Y * Scale, Z * Scale);
	}
	else
	{
		return *this;
	}
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::GetClampedToMaxSize2D(FDeterministicNumber64 MaxSize) const
{
	if (MaxSize < DeterministicFloat::Constants::Number64::KindaSmallNumber)
	{
		return FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, Z);
	}

	const FDeterministicNumber64 VSq2D = SizeSquared2D();
	if (VSq2D > FDeterministicFloatMath::Square(MaxSize))
	{
		const FDeterministicNumber64 Scale = MaxSize * FDeterministicFloatMath::InvSqrt(VSq2D);
		return FDeterministicVector64(X * Scale, Y * Scale, Z);
	}
	else
	{
		return *this;
	}
}

FORCEINLINE void FDeterministicVector64::AddBounded(const FDeterministicVector64& V, FDeterministicNumber64 Radius)
{
	*this = (*this + V).BoundToCube(Radius);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::Reciprocal() const
{
	FDeterministicVector64 RecVector;
	if (X != DeterministicFloat::Constants::Number64::Zero)
	{
		RecVector.X = DeterministicFloat::Constants::Number64::One / X;
	}
	else
	{
		RecVector.X = DeterministicFloat::Constants::Number64::BigNumber;
	}
	if (Y != DeterministicFloat::Constants::Number64::Zero)
	{
		RecVector.Y = DeterministicFloat::Constants::Number64::One / Y;
	}
	else
	{
		RecVector.Y = DeterministicFloat::Constants::Number64::BigNumber;
	}
	if (Z != DeterministicFloat::Constants::Number64::Zero)
	{
		RecVector.Z = DeterministicFloat::Constants::Number64::One / Z;
	}
	else
	{
		RecVector.Z = DeterministicFloat::Constants::Number64::BigNumber;
	}

	return RecVector;
}

FORCEINLINE bool FDeterministicVector64::IsUniform(FDeterministicNumber64 Tolerance) const
{
	return AllComponentsEqual(Tolerance);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::MirrorByVector(const FDeterministicVector64& MirrorNormal) const
{
	return *this - MirrorNormal * (FDeterministicNumber64::Make(2.0) * (*this | MirrorNormal));
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::PointPlaneProject(const FDeterministicVector64& Point, const FDeterministicVector64& A, const FDeterministicVector64& B, const FDeterministicVector64& C)
{
	//Compute the plane normal from ABC
	FDeterministicPlane64 Plane(A, B, C);

	//Find the distance of X from the plane
	//Add the distance back along the normal from the point
	return Point - Plane.PlaneDot(Point) * Plane;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::VectorPlaneProject(const FDeterministicVector64& V, const FDeterministicVector64& PlaneNormal)
{
	return V - V.ProjectOnToNormal(PlaneNormal);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::RotateAngleAxisRad(const FDeterministicNumber64 AngleRad, const FDeterministicVector64& Axis) const
{
	FDeterministicNumber64 S, C;
	FDeterministicFloatMath::SinCos(&S, &C, AngleRad);

	const FDeterministicNumber64 XX = Axis.X * Axis.X;
	const FDeterministicNumber64 YY = Axis.Y * Axis.Y;
	const FDeterministicNumber64 ZZ = Axis.Z * Axis.Z;
			  
	const FDeterministicNumber64 XY = Axis.X * Axis.Y;
	const FDeterministicNumber64 YZ = Axis.Y * Axis.Z;
	const FDeterministicNumber64 ZX = Axis.Z * Axis.X;
			  
	const FDeterministicNumber64 XS = Axis.X * S;
	const FDeterministicNumber64 YS = Axis.Y * S;
	const FDeterministicNumber64 ZS = Axis.Z * S;
			  
	const FDeterministicNumber64 OMC = DeterministicFloat::Constants::Number64::One - C;

	return FDeterministicVector64(
		(OMC * XX + C) * X + (OMC * XY - ZS) * Y + (OMC * ZX + YS) * Z,
		(OMC * XY + ZS) * X + (OMC * YY + C) * Y + (OMC * YZ - XS) * Z,
		(OMC * ZX - YS) * X + (OMC * YZ + XS) * Y + (OMC * ZZ + C) * Z
		);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::RotateAngleAxis(const FDeterministicNumber64 AngleDeg, const FDeterministicVector64& Axis) const
{
	return RotateAngleAxisRad(FDeterministicFloatMath::DegreesToRadians(AngleDeg), Axis);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::CosineAngle2D(FDeterministicVector64 B) const
{
	FDeterministicVector64 A(*this);
	A.Z = 0.0f;
	B.Z = 0.0f;
	A.Normalize();
	B.Normalize();
	return A | B;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::ProjectOnTo(const FDeterministicVector64& A) const
{
	return (A * ((*this | A) / (A | A)));
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::ProjectOnToNormal(const FDeterministicVector64& Normal) const
{
	return (Normal * (*this | Normal));
}

FORCEINLINE FDeterministicRotator64 FDeterministicVector64::Rotation() const
{
	return ToOrientationRotator();
}

FORCEINLINE void FDeterministicVector64::FindBestAxisVectors(FDeterministicVector64& Axis1, FDeterministicVector64& Axis2) const
{
	const FDeterministicNumber64 NX = FDeterministicFloatMath::Abs(X);
	const FDeterministicNumber64 NY = FDeterministicFloatMath::Abs(Y);
	const FDeterministicNumber64 NZ = FDeterministicFloatMath::Abs(Z);

	// Find best basis vectors.
	if (NZ > NX && NZ > NY)	Axis1 = FDeterministicVector64(1, 0, 0);
	else					Axis1 = FDeterministicVector64(0, 0, 1);

	FDeterministicVector64 Tmp = Axis1 - *this * (Axis1 | *this);
	Axis1 = Tmp.GetSafeNormal();
	Axis2 = Axis1 ^ *this;
}

FORCEINLINE void FDeterministicVector64::UnwindEuler()
{
	X = FDeterministicFloatMath::UnwindDegrees(X);
	Y = FDeterministicFloatMath::UnwindDegrees(Y);
	Z = FDeterministicFloatMath::UnwindDegrees(Z);
}

FORCEINLINE bool FDeterministicVector64::ContainsNaN() const
{
	return false;//no such thing as a nan fixed point number, friend.
}

FORCEINLINE FString FDeterministicVector64::ToString() const
{
	return ((FVector)*this).ToString();
}

FORCEINLINE FText FDeterministicVector64::ToText() const
{
	return ((FVector)*this).ToText();
}

FORCEINLINE FString FDeterministicVector64::ToCompactString() const
{
	return ((FVector)*this).ToCompactString();
}

FORCEINLINE FText FDeterministicVector64::ToCompactText() const
{
	return ((FVector)*this).ToCompactText();
}

FORCEINLINE bool FDeterministicVector64::InitFromString(const FString& InSourceString)
{
	FVector parsedvector;
	if (parsedvector.InitFromString(InSourceString))
	{
		*this = FDeterministicVector64(parsedvector);
		return true;
	}
	return false;
}

FORCEINLINE bool FDeterministicVector64::InitFromCompactString(const FString& InSourceString)
{
	FVector parsedvector;
	if (parsedvector.InitFromCompactString(InSourceString))
	{
		*this = FDeterministicVector64(parsedvector);
		return true;
	}
	return false;
}

FORCEINLINE FDeterministicVector2D64 FDeterministicVector64::UnitCartesianToSpherical() const
{
	checkSlow(IsUnit());
	//not safe for deterministic sims
	const FDeterministicNumber64 Theta = FDeterministicFloatMath::Acos(Z / Size());
	const FDeterministicNumber64 Phi = FDeterministicFloatMath::Atan2(Y, X);
	return FDeterministicVector2D64(Theta, Phi);
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::HeadingAngle() const
{
	// Project Dir into Z plane.
	FDeterministicVector64 PlaneDir = *this;
	PlaneDir.Z = 0.f;
	PlaneDir = PlaneDir.GetSafeNormal();

	FDeterministicNumber64 Angle = FDeterministicFloatMath::Acos(PlaneDir.X);

	if (PlaneDir.Y < DeterministicFloat::Constants::Number64::Zero)
	{
		Angle *= -DeterministicFloat::Constants::Number64::One;
	}

	return Angle;
}

FORCEINLINE void FDeterministicVector64::CreateOrthonormalBasis(FDeterministicVector64& XAxis, FDeterministicVector64& YAxis, FDeterministicVector64& ZAxis)
{
	// Project the X and Y axes onto the plane perpendicular to the Z axis.
	XAxis -= ZAxis * (ZAxis | ZAxis) / (XAxis | ZAxis);
	YAxis -= ZAxis * (ZAxis | ZAxis) / (YAxis | ZAxis);

	// If the X axis was parallel to the Z axis, choose a vector which is orthogonal to the Y and Z axes.
	if (XAxis.SizeSquared() <= DeterministicFloat::Constants::Number64::SmallNumber)
	{
		XAxis = YAxis ^ ZAxis;
	}

	// If the Y axis was parallel to the Z axis, choose a vector which is orthogonal to the X and Z axes.
	if (YAxis.SizeSquared() <= DeterministicFloat::Constants::Number64::SmallNumber)
	{
		YAxis = XAxis ^ ZAxis;
	}

	// Normalize the basis vectors.
	XAxis.Normalize();
	YAxis.Normalize();
	ZAxis.Normalize();
}

FORCEINLINE bool FDeterministicVector64::PointsAreSame(const FDeterministicVector64& P, const FDeterministicVector64& Q)
{
	FDeterministicNumber64 Temp;
	Temp = P.X - Q.X;
	if ((Temp > -DeterministicFloat::Constants::Number64::ThreshPointsAreSame) && (Temp < DeterministicFloat::Constants::Number64::ThreshPointsAreSame))
	{
		Temp = P.Y - Q.Y;
		if ((Temp > -DeterministicFloat::Constants::Number64::ThreshPointsAreSame) && (Temp < DeterministicFloat::Constants::Number64::ThreshPointsAreSame))
		{
			Temp = P.Z - Q.Z;
			if ((Temp > -DeterministicFloat::Constants::Number64::ThreshPointsAreSame) && (Temp < DeterministicFloat::Constants::Number64::ThreshPointsAreSame))
			{
				return true;
			}
		}
	}
	return false;
}

FORCEINLINE bool FDeterministicVector64::PointsAreNear(const FDeterministicVector64& Point1, const FDeterministicVector64& Point2, FDeterministicNumber64 Dist)
{
	FDeterministicNumber64 Temp;
	Temp = (Point1.X - Point2.X); if (FDeterministicFloatMath::Abs(Temp) >= Dist) return false;
	Temp = (Point1.Y - Point2.Y); if (FDeterministicFloatMath::Abs(Temp) >= Dist) return false;
	Temp = (Point1.Z - Point2.Z); if (FDeterministicFloatMath::Abs(Temp) >= Dist) return false;
	return true;
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::PointPlaneDist(const FDeterministicVector64& Point, const FDeterministicVector64& PlaneBase, const FDeterministicVector64& PlaneNormal)
{
	return (Point - PlaneBase) | PlaneNormal;
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::BoxPushOut(const FDeterministicVector64& Normal, const FDeterministicVector64& Size)
{
	return FDeterministicFloatMath::Abs(Normal.X * Size.X) + FDeterministicFloatMath::Abs(Normal.Y * Size.Y) + FDeterministicFloatMath::Abs(Normal.Z * Size.Z);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::Min(const FDeterministicVector64& A, const FDeterministicVector64& B)
{
	return FDeterministicVector64(
		FDeterministicFloatMath::Min(A.X, B.X),
		FDeterministicFloatMath::Min(A.Y, B.Y),
		FDeterministicFloatMath::Min(A.Z, B.Z)
		);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::Max(const FDeterministicVector64& A, const FDeterministicVector64& B)
{
	return FDeterministicVector64(
		FDeterministicFloatMath::Max(A.X, B.X),
		FDeterministicFloatMath::Max(A.Y, B.Y),
		FDeterministicFloatMath::Max(A.Z, B.Z)
		);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::Min3(const FDeterministicVector64& A, const FDeterministicVector64& B, const FDeterministicVector64& C)
{
	return FDeterministicVector64(
		FDeterministicFloatMath::Min3(A.X, B.X, C.X),
		FDeterministicFloatMath::Min3(A.Y, B.Y, C.Y),
		FDeterministicFloatMath::Min3(A.Z, B.Z, C.Z)
		);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::Max3(const FDeterministicVector64& A, const FDeterministicVector64& B, const FDeterministicVector64& C)
{
	return FDeterministicVector64(
		FDeterministicFloatMath::Max3(A.X, B.X, C.X),
		FDeterministicFloatMath::Max3(A.Y, B.Y, C.Y),
		FDeterministicFloatMath::Max3(A.Z, B.Z, C.Z)
		);
}

FORCEINLINE bool FDeterministicVector64::Parallel(const FDeterministicVector64& Normal1, const FDeterministicVector64& Normal2, FDeterministicNumber64 ParallelCosineThreshold)
{
	const FDeterministicNumber64 NormalDot = Normal1 | Normal2;
	return FDeterministicFloatMath::Abs(NormalDot) >= ParallelCosineThreshold;
}

FORCEINLINE bool FDeterministicVector64::Coincident(const FDeterministicVector64& Normal1, const FDeterministicVector64& Normal2, FDeterministicNumber64 ParallelCosineThreshold)
{
	const FDeterministicNumber64 NormalDot = Normal1 | Normal2;
	return NormalDot >= ParallelCosineThreshold;
}

FORCEINLINE bool FDeterministicVector64::Orthogonal(const FDeterministicVector64& Normal1, const FDeterministicVector64& Normal2, FDeterministicNumber64 OrthogonalCosineThreshold)
{
	const FDeterministicNumber64 NormalDot = Normal1 | Normal2;
	return FDeterministicFloatMath::Abs(NormalDot) <= OrthogonalCosineThreshold;
}

FORCEINLINE bool FDeterministicVector64::Coplanar(const FDeterministicVector64& Base1, const FDeterministicVector64& Normal1, const FDeterministicVector64& Base2, const FDeterministicVector64& Normal2, FDeterministicNumber64 ParallelCosineThreshold)
{
	if (!FDeterministicVector64::Parallel(Normal1, Normal2, ParallelCosineThreshold)) return false;
	else if (FDeterministicFloatMath::Abs(FDeterministicVector64::PointPlaneDist(Base2, Base1, Normal1)) > DeterministicFloat::Constants::Number64::ThreshPointOnPlane) return false;
	else return true;
}

FORCEINLINE FDeterministicNumber64 FDeterministicVector64::EvaluateBezier(const FDeterministicVector64* ControlPoints, int32 NumPoints, TArray<FDeterministicVector64>& OutPoints)
{
	check(ControlPoints);
	check(NumPoints >= 2);

	// var q is the change in t between successive evaluations.
	const FDeterministicNumber64 q = DeterministicFloat::Constants::Number64::One / (FDeterministicNumber64)(NumPoints - 1); // q is dependent on the number of GAPS = POINTS-1

	// recreate the names used in the derivation
	const FDeterministicVector64& P0 = ControlPoints[0];
	const FDeterministicVector64& P1 = ControlPoints[1];
	const FDeterministicVector64& P2 = ControlPoints[2];
	const FDeterministicVector64& P3 = ControlPoints[3];

	// coefficients of the cubic polynomial that we're FDing -
	const FDeterministicVector64 a = P0;
	const FDeterministicVector64 b = FDeterministicNumber64((int64)3) * (P1 - P0);
	const FDeterministicVector64 c = FDeterministicNumber64((int64)3) * (P2 - FDeterministicNumber64((int64)2) * P1 + P0);
	const FDeterministicVector64 d = P3 - FDeterministicNumber64((int64)3) * P2 + FDeterministicNumber64((int64)3) * P1 - P0;

	// initial values of the poly and the 3 diffs -
	FDeterministicVector64 S = a;						// the poly value
	FDeterministicVector64 U = b * q + c * q * q + d * q * q * q;	// 1st order diff (quadratic)
	FDeterministicVector64 V = 2 * c * q * q + 6 * d * q * q * q;	// 2nd order diff (linear)
	FDeterministicVector64 W = 6 * d * q * q * q;				// 3rd order diff (constant)

	// Path length.
	FDeterministicNumber64 Length = 0;

	FDeterministicVector64 OldPos = P0;
	OutPoints.Add(P0);	// first point on the curve is always P0.

	for (int32 i = 1; i < NumPoints; ++i)
	{
		// calculate the next value and update the deltas
		S += U;			// update poly value
		U += V;			// update 1st order diff value
		V += W;			// update 2st order diff value
		// 3rd order diff is constant => no update needed.

		// Update Length.
		Length += FDeterministicVector64::Dist(S, OldPos);
		OldPos = S;

		OutPoints.Add(S);
	}

	// Return path length as experienced in sequence (linear interpolation between points).
	return Length;
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::RadiansToDegrees(const FDeterministicVector64& RadVector)
{
	return RadVector * (DeterministicFloat::Constants::Number64::OneEighty / DeterministicFloat::Constants::Number64::Pi);
}

FORCEINLINE FDeterministicVector64 FDeterministicVector64::DegreesToRadians(const FDeterministicVector64& DegVector)
{
	return DegVector * (DeterministicFloat::Constants::Number64::Pi / DeterministicFloat::Constants::Number64::OneEighty);
}

FORCEINLINE void FDeterministicVector64::GenerateClusterCenters(TArray<FDeterministicVector64>& Clusters, const TArray<FDeterministicVector64>& Points, int32 NumIterations, int32 NumConnectionsToBeValid)
{
	struct FClusterMovedHereToMakeCompile
	{
		FDeterministicVector64 ClusterPosAccum;
		int32 ClusterSize;
	};

	// Check we have >0 points and clusters
	if (Points.Num() == 0 || Clusters.Num() == 0)
	{
		return;
	}

	// Temp storage for each cluster that mirrors the order of the passed in Clusters array
	TArray<FClusterMovedHereToMakeCompile> ClusterData;
	ClusterData.AddZeroed(Clusters.Num());

	// Then iterate
	for (int32 ItCount = 0; ItCount < NumIterations; ItCount++)
	{
		// Classify each point - find closest cluster center
		for (int32 i = 0; i < Points.Num(); i++)
		{
			const FDeterministicVector64& Pos = Points[i];

			// Iterate over all clusters to find closes one
			int32 NearestClusterIndex = INDEX_NONE;
			FDeterministicNumber64 NearestClusterDistSqr = DeterministicFloat::Constants::Number64::BigNumber;
			for (int32 j = 0; j < Clusters.Num(); j++)
			{
				const FDeterministicNumber64 DistSqr = (Pos - Clusters[j]).SizeSquared();
				if (DistSqr < NearestClusterDistSqr)
				{
					NearestClusterDistSqr = DistSqr;
					NearestClusterIndex = j;
				}
			}
			// Update its info with this point
			if (NearestClusterIndex != INDEX_NONE)
			{
				ClusterData[NearestClusterIndex].ClusterPosAccum += Pos;
				ClusterData[NearestClusterIndex].ClusterSize++;
			}
		}

		// All points classified - update cluster center as average of membership
		for (int32 i = 0; i < Clusters.Num(); i++)
		{
			if (ClusterData[i].ClusterSize > 0)
			{
				Clusters[i] = ClusterData[i].ClusterPosAccum / FDeterministicNumber64((int64)ClusterData[i].ClusterSize);
			}
		}
	}

	// so now after we have possible cluster centers we want to remove the ones that are outliers and not part of the main cluster
	for (int32 i = 0; i < ClusterData.Num(); i++)
	{
		if (ClusterData[i].ClusterSize < NumConnectionsToBeValid)
		{
			Clusters.RemoveAt(i);
		}
	}
}
