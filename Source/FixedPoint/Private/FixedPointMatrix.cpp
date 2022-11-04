// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointMatrix.h"
#include "FixedPointNumbers.h"
#include "FixedPointVectors.h"

const FFixedMatrix FFixedMatrix::Identity(
	FFixedPlane(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero),
	FFixedPlane(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero),
	FFixedPlane(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero),
	FFixedPlane(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One));
