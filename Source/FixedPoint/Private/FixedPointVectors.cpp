// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointVectors.h"
#include "FixedPointNumbers.h"
#include "FixedPointMath.h"


const FFixedVector FFixedVector::ZeroVector =		FFixedVector((int64)0,	(int64)0,	(int64)0);
const FFixedVector FFixedVector::OneVector =		FFixedVector((int64)1,	(int64)1,	(int64)1);
const FFixedVector FFixedVector::UpVector =			FFixedVector((int64)0,	(int64)0,	(int64)1);
const FFixedVector FFixedVector::DownVector =		FFixedVector((int64)0,	(int64)0,	(int64)-1);
const FFixedVector FFixedVector::ForwardVector =	FFixedVector((int64)1,	(int64)0,	(int64)0);
const FFixedVector FFixedVector::BackwardVector =	FFixedVector((int64)-1, (int64)0,	(int64)0);
const FFixedVector FFixedVector::RightVector =		FFixedVector((int64)0,	(int64)1,	(int64)0);
const FFixedVector FFixedVector::LeftVector =		FFixedVector((int64)0,	(int64)-1,	(int64)0);
const FFixedVector FFixedVector::XAxisVector =		FFixedVector((int64)1,	(int64)0,	(int64)0);
const FFixedVector FFixedVector::YAxisVector =		FFixedVector((int64)0,	(int64)1,	(int64)0);
const FFixedVector FFixedVector::ZAxisVector =		FFixedVector((int64)0,	(int64)0,	(int64)1);



/**
* ACCESSORS
*/

//FFixedVector

bool FFixedVector::Equals(const FFixedVector& Other, const FFixed64& inTolerance)
{
	return FFixedVector::IsEqual(*this, Other, inTolerance);
}

bool FFixedVector::AllComponentsEqual(const FFixed64& inTolerance)
{
	return FFixedPointMath::IsEqual(X, Y, inTolerance) && FFixedPointMath::IsEqual(X, Z, inTolerance) && FFixedPointMath::IsEqual(Y, Z, inTolerance);
}

bool FFixedVector::IsUnit(const FFixed64& inTolerance)
{
	return FFixedPointMath::Abs(FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One) - SizeSquared()) <= inTolerance;
}

FFixed64 FFixedVector::GetMax()
{
	return FFixedPointMath::Max(FFixedPointMath::Max(X, Y), Z);
}

FFixed64 FFixedVector::GetAbsMax()
{
	return FFixedPointMath::Max(FFixedPointMath::Max(FFixedPointMath::Abs(X), FFixedPointMath::Abs(Y)), FFixedPointMath::Abs(Z));
}

FFixed64 FFixedVector::GetMin()
{
	return FFixedPointMath::Min(FFixedPointMath::Min(X, Y), Z);
}

FFixed64 FFixedVector::GetAbsMin()
{
	return FFixedPointMath::Min(FFixedPointMath::Min(FFixedPointMath::Abs(X), FFixedPointMath::Abs(Y)), FFixedPointMath::Abs(Z));
}

FFixedVector FFixedVector::GetAbs()
{
	return FFixedVector(FFixedPointMath::Abs(X), FFixedPointMath::Abs(Y), FFixedPointMath::Abs(Z));
}

FFixedVector FFixedVector::ComponentMin(const FFixedVector& Other)
{
	return FFixedVector(FFixedPointMath::Min(X, Other.X), FFixedPointMath::Min(Y, Other.Y), FFixedPointMath::Min(Z, Other.Z));
}

FFixedVector FFixedVector::ComponentMax(const FFixedVector& Other)
{
	return FFixedVector(FFixedPointMath::Max(X, Other.X), FFixedPointMath::Max(Y, Other.Y), FFixedPointMath::Max(Z, Other.Z));
}

FFixed64 FFixedVector::SizeSquared()
{
	return (X * X) + (Y * Y) + (Z * Z);
}

FFixed64 FFixedVector::Size()
{
	return FFixedPointMath::Sqrt(SizeSquared());
}

//FFixedVector2d

FVector2d FFixedVector2d::GetVector2d() const
{
	return FVector2d((double)X, (double)Y);
}

//FFixedVector4d

FVector4d FFixedVector4d::GetVector4d() const
{
	return FVector4d((double)X, (double)Y, (double)Z, (double)W);
}

/**
* SETTERS
*/

//FFixedVector2d

void FFixedVector2d::SetVector2d(const FVector2d& inValue)
{
	X = FFixed64(inValue.X);
	Y = FFixed64(inValue.Y);
}

//FFixedVector4d

void FFixedVector4d::SetVector4d(const FVector4d& inValue)
{
	X = FFixed64(inValue.X);
	Y = FFixed64(inValue.Y);
	Z = FFixed64(inValue.Z);
	W = FFixed64(inValue.W);
}

/**
* HELPERS
*/

//FFixedVector


bool FFixedVector::IsEqual(const FFixedVector& A, const FFixedVector& B, const FFixed64& inTolerance)
{
	return FFixedPointMath::IsEqual(A.X, B.X, inTolerance) && FFixedPointMath::IsEqual(A.Y, B.Y, inTolerance) && FFixedPointMath::IsEqual(A.Z, B.Z, inTolerance);
}

FFixedVector FFixedVector::Normalize(const FFixedVector& inValue)
{
	FFixed64 SquareSum = (inValue.X * inValue.X) + (inValue.Y * inValue.Y) + (inValue.Z * inValue.Z);
	if ((SquareSum.Value == FixedPoint::Constants::Raw64::One) || (SquareSum.Value <= 2))
	{
		return inValue;
	}
	FFixed64 Scale = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One) / FFixedPointMath::Sqrt(SquareSum);
	return FFixedVector(inValue.X * Scale, inValue.Y * Scale, inValue.Z * Scale);
}

FFixed64 FFixedVector::DistSquared(const FFixedVector& A, const FFixedVector& B)
{
	return FFixedPointMath::Square(B.X - A.X) + FFixedPointMath::Square(B.Y - A.Y) + FFixedPointMath::Square(B.Z - A.Z);
}

FFixed64 FFixedVector::Dist(const FFixedVector& A, const FFixedVector& B)
{
	return FFixedPointMath::Sqrt(FFixedVector::DistSquared(A, B));
}

FFixedVector FFixedVector::CrossProduct(const FFixedVector& A, const FFixedVector& B)
{
	return A ^ B;
}

FFixedVector FFixedVector::DotProduct(const FFixedVector& A, const FFixedVector& B)
{
	return A | B;
}

FFixedVector FFixedVector::TripleProduct(const FFixedVector& X, const FFixedVector& Y, const FFixedVector& Z)
{
	return
		((X.X * (Y.Y * Z.Z - Y.Z * Z.Y))
		+ (X.Y * (Y.Z * Z.X - Y.X * Z.Z))
		+ (X.Z * (Y.X * Z.Y - Y.Y * Z.X)));
}

/**
* COMPARISON OPERATORS
*/

//FFixedVector-FFixedVector

bool FFixedVector::operator==(const FFixedVector& Other) const
{
	return ((X == Other.X) && (Y == Other.Y) &&	(Z == Other.Z));
}

bool FFixedVector::operator!=(const FFixedVector& Other) const
{
	return ((X != Other.X) && (Y != Other.Y) && (Z != Other.Z));
}

FFixedVector FFixedVector::operator-() const
{
	return FFixedVector(-X, -Y, -Z);
}

//FFixedVector2d-FFixedVector2d

bool FFixedVector2d::operator==(const FFixedVector2d& Other) const
{
	return ((X == Other.X) && (Y == Other.Y));
}

bool FFixedVector2d::operator!=(const FFixedVector2d& Other) const
{
	return ((X != Other.X) && (Y != Other.Y));
}

//FFixedVector4d-FFixedVector4d

bool FFixedVector4d::operator==(const FFixedVector4d& Other) const
{
	return ((X == Other.X) && (Y == Other.Y) && (Z == Other.Z) && (W == Other.W));
}

bool FFixedVector4d::operator!=(const FFixedVector4d& Other) const
{
	return ((X != Other.X) && (Y != Other.Y) && (Z != Other.Z) && (W != Other.W));
}

/**
* ARITHMETIC OPERATORS
*/

//FFixedVector-FFixedVector

FFixedVector FFixedVector::operator+(const FFixedVector& Other) const
{
	return FFixedVector(X + Other.X, Y + Other.Y, Z + Other.Z);
}

FFixedVector FFixedVector::operator-(const FFixedVector& Other) const
{
	return FFixedVector(X - Other.X, Y - Other.Y, Z - Other.Z);
}

FFixedVector FFixedVector::operator*(const FFixedVector& Other) const
{
	return FFixedVector(X * Other.X, Y * Other.Y, Z * Other.Z);
}

FFixedVector FFixedVector::operator/(const FFixedVector& Other) const
{
	return FFixedVector(X / Other.X, Y / Other.Y, Z / Other.Z);
}

FFixedVector FFixedVector::operator+=(const FFixedVector& Other)
{
	X += Other.X;
	Y += Other.Y;
	Z += Other.Z;
	return *this;
}

FFixedVector FFixedVector::operator-=(const FFixedVector& Other)
{
	X -= Other.X;
	Y -= Other.Y;
	Z -= Other.Z;
	return *this;
}

FFixedVector FFixedVector::operator*=(const FFixedVector& Other)
{
	X *= Other.X;
	Y *= Other.Y;
	Z *= Other.Z;
	return *this;
}

FFixedVector FFixedVector::operator/=(const FFixedVector& Other)
{
	X /= Other.X;
	Y /= Other.Y;
	Z /= Other.Z;
	return *this;
}

FFixedVector FFixedVector::operator^(const FFixedVector& Other) const
{
	return FFixedVector
	(
		(Y * Other.Z) - (Z * Other.Y),
		(Z * Other.X) - (X * Other.Z),
		(X * Other.Y) - (Y * Other.X)
	);
}

//FFixedVector-FFixed64

FFixedVector FFixedVector::operator+(const FFixed64& Other) const
{
	return FFixedVector(X + Other, Y + Other, Z + Other);
}

FFixedVector FFixedVector::operator-(const FFixed64& Other) const
{
	return FFixedVector(X - Other, Y - Other, Z - Other);
}

FFixedVector FFixedVector::operator*(const FFixed64& Other) const
{
	return FFixedVector(X * Other, Y * Other, Z * Other);
}

FFixedVector FFixedVector::operator/(const FFixed64& Other) const
{
	return FFixedVector(X / Other, Y / Other, Z / Other);
}

FFixedVector FFixedVector::operator+=(const FFixed64& Other)
{
	X += Other;
	Y += Other;
	Z += Other;
	return *this;
}

FFixedVector FFixedVector::operator-=(const FFixed64& Other)
{
	X -= Other;
	Y -= Other;
	Z -= Other;
	return *this;
}

FFixedVector FFixedVector::operator*=(const FFixed64& Other)
{
	X *= Other;
	Y *= Other;
	Z *= Other;
	return *this;
}

FFixedVector FFixedVector::operator/=(const FFixed64& Other)
{
	X /= Other;
	Y /= Other;
	Z /= Other;
	return *this;
}

FFixed64 FFixedVector::operator|(const FFixedVector& Other) const
{
	return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z);
}

//FFixedVector2d-FFixedVector2d

FFixedVector2d FFixedVector2d::operator+(const FFixedVector2d& Other) const
{
	return FFixedVector2d(X + Other.X, Y + Other.Y);
}

FFixedVector2d FFixedVector2d::operator-(const FFixedVector2d& Other) const
{
	return FFixedVector2d(X - Other.X, Y - Other.Y);
}

FFixedVector2d FFixedVector2d::operator*(const FFixedVector2d& Other) const
{
	return FFixedVector2d((X * Other.X).Value, (Y * Other.Y).Value);
}

FFixedVector2d FFixedVector2d::operator/(const FFixedVector2d& Other) const
{
	return FFixedVector2d((X / Other.X).Value, (Y / Other.Y).Value);
}

FFixedVector2d FFixedVector2d::operator+=(const FFixedVector2d& Other)
{
	X += Other.X;
	Y += Other.Y;
	return *this;
}

FFixedVector2d FFixedVector2d::operator-=(const FFixedVector2d& Other)
{
	X -= Other.X;
	Y -= Other.Y;
	return *this;
}

FFixedVector2d FFixedVector2d::operator*=(const FFixedVector2d& Other)
{
	X *= Other.X;
	Y *= Other.Y;
	return *this;
}

FFixedVector2d FFixedVector2d::operator/=(const FFixedVector2d& Other)
{
	X /= Other.X;
	Y /= Other.Y;
	return *this;
}

//FFixedVector2d-FFixed64

FFixedVector2d FFixedVector2d::operator+(const FFixed64& Other) const
{
	return FFixedVector2d(X + Other, Y + Other);
}

FFixedVector2d FFixedVector2d::operator-(const FFixed64& Other) const
{
	return FFixedVector2d(X - Other, Y - Other);
}

FFixedVector2d FFixedVector2d::operator*(const FFixed64& Other) const
{
	return FFixedVector2d(X * Other, Y * Other);
}

FFixedVector2d FFixedVector2d::operator/(const FFixed64& Other) const
{
	return FFixedVector2d(X / Other, Y / Other);
}

FFixedVector2d FFixedVector2d::operator+=(const FFixed64& Other)
{
	X += Other;
	Y += Other;
	return *this;
}

FFixedVector2d FFixedVector2d::operator-=(const FFixed64& Other)
{
	X -= Other;
	Y -= Other;
	return *this;
}

FFixedVector2d FFixedVector2d::operator*=(const FFixed64& Other)
{
	X *= Other;
	Y *= Other;
	return *this;
}

FFixedVector2d FFixedVector2d::operator/=(const FFixed64& Other)
{
	X /= Other;
	Y /= Other;
	return *this;
}

FFixed64 FFixedVector2d::operator|(const FFixedVector2d& Other)
{
	return (X * Other.X) + (Y * Other.Y);
}

FFixed64 FFixedVector2d::operator^(const FFixedVector2d& Other)
{
	return (X * Other.Y) - (Y * Other.X);
}

//FFixedVector4d-FFixedVector4d

FFixedVector4d FFixedVector4d::operator+(const FFixedVector4d& Other) const
{
	return FFixedVector4d(X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W);
}

FFixedVector4d FFixedVector4d::operator-(const FFixedVector4d& Other) const
{
	return FFixedVector4d(X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W);
}

FFixedVector4d FFixedVector4d::operator*(const FFixedVector4d& Other) const
{
	return FFixedVector4d(X * Other.X, Y * Other.Y, Z * Other.Z, W * Other.W);
}

FFixedVector4d FFixedVector4d::operator/(const FFixedVector4d& Other) const
{
	return FFixedVector4d(X / Other.X, Y / Other.Y, Z / Other.Z, W / Other.W);
}

FFixedVector4d FFixedVector4d::operator+=(const FFixedVector4d& Other)
{
	X += Other.X;
	Y += Other.Y;
	Z += Other.Z;
	W += Other.W;
	return *this;
}

FFixedVector4d FFixedVector4d::operator-=(const FFixedVector4d& Other)
{
	X -= Other.X;
	Y -= Other.Y;
	Z -= Other.Z;
	W -= Other.W;
	return *this;
}

FFixedVector4d FFixedVector4d::operator*=(const FFixedVector4d& Other)
{
	X *= Other.X;
	Y *= Other.Y;
	Z *= Other.Z;
	W *= Other.W;
	return *this;
}

FFixedVector4d FFixedVector4d::operator/=(const FFixedVector4d& Other)
{
	X /= Other.X;
	Y /= Other.Y;
	Z /= Other.Z;
	W /= Other.W;
	return *this;
}

FFixedVector4d FFixedVector4d::operator^(const FFixedVector4d& Other)
{
	return FFixedVector4d
	(
		(Y * Other.Z) - (Z * Other.Y),
		(Z * Other.X) - (X * Other.Z),
		(X * Other.Y) - (Y * Other.X),
		FFixed64()
	);
}

//FFixedVector4d-FFixed64

FFixedVector4d FFixedVector4d::operator+(const FFixed64& Other) const
{
	return FFixedVector4d
	(
		X + Other,
		Y + Other,
		Z + Other,
		W + Other
	);
}

FFixedVector4d FFixedVector4d::operator-(const FFixed64& Other) const
{
	return FFixedVector4d
	(
		X - Other,
		Y - Other,
		Z - Other,
		W - Other
	);
}

FFixedVector4d FFixedVector4d::operator*(const FFixed64& Other) const
{
	return FFixedVector4d
	(
		X * Other,
		Y * Other,
		Z * Other,
		W * Other
	);
}

FFixedVector4d FFixedVector4d::operator/(const FFixed64& Other) const
{
	return FFixedVector4d
	(
		X / Other,
		Y / Other,
		Z / Other,
		W / Other
	);
}

FFixedVector4d FFixedVector4d::operator+=(const FFixed64& Other)
{
	X += Other;
	Y += Other;
	Z += Other;
	W += Other;
	return *this;
}

FFixedVector4d FFixedVector4d::operator-=(const FFixed64& Other)
{
	X -= Other;
	Y -= Other;
	Z -= Other;
	W -= Other;
	return *this;
}

FFixedVector4d FFixedVector4d::operator*=(const FFixed64& Other)
{
	X *= Other;
	Y *= Other;
	Z *= Other;
	W *= Other;
	return *this;
}

FFixedVector4d FFixedVector4d::operator/=(const FFixed64& Other)
{
	X /= Other;
	Y /= Other;
	Z /= Other;
	W /= Other;
	return *this;
}
