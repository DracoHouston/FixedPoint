// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointVector.h"


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