// Fill out your copyright notice in the Description page of Project Settings.

#include "FixedPointRotator.h"

const FFixedRotator FFixedRotator::ZeroRotator = FFixedRotator(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);

void FFixedRotator::GetWindingAndRemainder(FFixedRotator& Winding, FFixedRotator& Remainder) const
{
	//// YAW
	Remainder.Yaw = NormalizeAxis(Yaw);

	Winding.Yaw = Yaw - Remainder.Yaw;

	//// PITCH
	Remainder.Pitch = NormalizeAxis(Pitch);

	Winding.Pitch = Pitch - Remainder.Pitch;

	//// ROLL
	Remainder.Roll = NormalizeAxis(Roll);

	Winding.Roll = Roll - Remainder.Roll;
}