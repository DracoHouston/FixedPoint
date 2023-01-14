// Fill out your copyright notice in the Description page of Project Settings.


#include "DeterministicFloatMatrix64.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatPlane64.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatRotationMatrix64.h"
#include "DeterministicFloatPlane64Funcs.h"
#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatRotator64Funcs.h"

const FDeterministicMatrix64 FDeterministicMatrix64::Identity(
	FDeterministicPlane64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero),
	FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero),
	FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero),
	FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One));

FDeterministicRotator64 FDeterministicMatrix64::Rotator() const
{
	const FDeterministicVector64	XAxis = GetScaledAxis(EAxis::X);
	const FDeterministicVector64	YAxis = GetScaledAxis(EAxis::Y);
	const FDeterministicVector64	ZAxis = GetScaledAxis(EAxis::Z);
	const FDeterministicNumber64 RadToDeg = DeterministicFloat::Constants::Number64::OneEighty / DeterministicFloat::Constants::Number64::Pi;

	FDeterministicRotator64 Rotator = FDeterministicRotator64(
		FDeterministicFloatMath::Atan2(XAxis.Z, FDeterministicFloatMath::Sqrt(FDeterministicFloatMath::Square(XAxis.X) + FDeterministicFloatMath::Square(XAxis.Y))) * RadToDeg,
		FDeterministicFloatMath::Atan2(XAxis.Y, XAxis.X) * RadToDeg,
		DeterministicFloat::Constants::Number64::Zero
	);

	const FDeterministicVector64	SYAxis = (FDeterministicVector64)FDeterministicRotationMatrix64(Rotator).GetScaledAxis(EAxis::Y);
	Rotator.Roll = FDeterministicFloatMath::Atan2(ZAxis | SYAxis, YAxis | SYAxis) * RadToDeg;

	return Rotator;
}