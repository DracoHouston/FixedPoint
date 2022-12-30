// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointVector.h"


const FFixedVector64 FFixedVector64::ZeroVector =		FFixedVector64((int64)0,	(int64)0,	(int64)0);
const FFixedVector64 FFixedVector64::OneVector =		FFixedVector64((int64)1,	(int64)1,	(int64)1);
const FFixedVector64 FFixedVector64::UpVector =			FFixedVector64((int64)0,	(int64)0,	(int64)1);
const FFixedVector64 FFixedVector64::DownVector =		FFixedVector64((int64)0,	(int64)0,	(int64)-1);
const FFixedVector64 FFixedVector64::ForwardVector =	FFixedVector64((int64)1,	(int64)0,	(int64)0);
const FFixedVector64 FFixedVector64::BackwardVector =	FFixedVector64((int64)-1, (int64)0,	(int64)0);
const FFixedVector64 FFixedVector64::RightVector =		FFixedVector64((int64)0,	(int64)1,	(int64)0);
const FFixedVector64 FFixedVector64::LeftVector =		FFixedVector64((int64)0,	(int64)-1,	(int64)0);
const FFixedVector64 FFixedVector64::XAxisVector =		FFixedVector64((int64)1,	(int64)0,	(int64)0);
const FFixedVector64 FFixedVector64::YAxisVector =		FFixedVector64((int64)0,	(int64)1,	(int64)0);
const FFixedVector64 FFixedVector64::ZAxisVector =		FFixedVector64((int64)0,	(int64)0,	(int64)1);


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