// Fill out your copyright notice in the Description page of Project Settings.

#include "FixedPointRotator.h"

const FFixedRotator64 FFixedRotator64::ZeroRotator = FFixedRotator64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero);

void FFixedRotator64::GetWindingAndRemainder(FFixedRotator64& Winding, FFixedRotator64& Remainder) const
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

FFixedRotator64 FFixedRotator64::MakeFromEuler(const FFixedVector64& Euler)
{
	return FFixedRotator64(Euler.Y, Euler.Z, Euler.X);
}
