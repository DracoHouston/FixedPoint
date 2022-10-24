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


//FFixedVector FFixedVector::MirrorByPlane(const FFixedPlane& Plane) const
//{
//	return *this - Plane * (2.f * Plane.PlaneDot(*this));
//}
//
//FFixedVector FFixedVector::PointPlaneProject(const FFixedVector& Point, const FFixedPlane& Plane)
//{
//	//Find the distance of X from the plane
//	//Add the distance back along the normal from the point
//	return Point - Plane.PlaneDot(Point) * Plane;
//}
//
//FFixedVector FFixedVector::PointPlaneProject(const FFixedVector& Point, const FFixedVector& A, const FFixedVector& B, const FFixedVector& C)
//{
//	//Compute the plane normal from ABC
//	FFixedPlane Plane(A, B, C);
//
//	//Find the distance of X from the plane
//	//Add the distance back along the normal from the point
//	return Point - Plane.PlaneDot(Point) * Plane;
//}


/**
* ACCESSORS
*/

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
* COMPARISON OPERATORS
*/

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
