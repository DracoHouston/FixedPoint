// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointMatrix.h"
#include "FixedPointNumbers.h"
#include "FixedPointPlane.h"
#include "FixedPointVector.h"
#include "FixedPointMath.h"
#include "FixedPointRotator.h"
#include "FixedPointRotationMatrix.h"

const FFixedMatrix FFixedMatrix::Identity(
	FFixedPlane(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero),
	FFixedPlane(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero),
	FFixedPlane(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero),
	FFixedPlane(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One));

FFixedRotator64 FFixedMatrix::Rotator() const
{
	const FFixedVector64	XAxis = GetScaledAxis(EAxis::X);
	const FFixedVector64	YAxis = GetScaledAxis(EAxis::Y);
	const FFixedVector64	ZAxis = GetScaledAxis(EAxis::Z);
	const FFixed64 RadToDeg = FixedPoint::Constants::Fixed64::OneEighty / FixedPoint::Constants::Fixed64::Pi;

	FFixedRotator64 Rotator = FFixedRotator64(
		FFixedPointMath::Atan2(XAxis.Z, FFixedPointMath::Sqrt(FFixedPointMath::Square(XAxis.X) + FFixedPointMath::Square(XAxis.Y))) * RadToDeg,
		FFixedPointMath::Atan2(XAxis.Y, XAxis.X) * RadToDeg,
		FixedPoint::Constants::Fixed64::Zero
	);

	const FFixedVector64	SYAxis = (FFixedVector64)FFixedRotationMatrix(Rotator).GetScaledAxis(EAxis::Y);
	Rotator.Roll = FFixedPointMath::Atan2(ZAxis | SYAxis, YAxis | SYAxis) * RadToDeg;

	return Rotator;
}