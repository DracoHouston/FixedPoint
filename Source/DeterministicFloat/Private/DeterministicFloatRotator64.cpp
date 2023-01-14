// Fill out your copyright notice in the Description page of Project Settings.

#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatRotator64Funcs.h"

const FDeterministicRotator64 FDeterministicRotator64::ZeroRotator = FDeterministicRotator64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero);

void FDeterministicRotator64::GetWindingAndRemainder(FDeterministicRotator64& Winding, FDeterministicRotator64& Remainder) const
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

FDeterministicRotator64 FDeterministicRotator64::MakeFromEuler(const FDeterministicVector64& Euler)
{
	return FDeterministicRotator64(Euler.Y, Euler.Z, Euler.X);
}
