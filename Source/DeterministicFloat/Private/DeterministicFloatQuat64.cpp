// Fill out your copyright notice in the Description page of Project Settings.


#include "DeterministicFloatQuat64.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatQuat64Funcs.h"


const FDeterministicQuat64 FDeterministicQuat64::Identity = FDeterministicQuat64(FDeterministicNumber64(), FDeterministicNumber64(), FDeterministicNumber64(), FDeterministicNumber64((int64)1));

FDeterministicRotator64 FDeterministicQuat64::Rotator() const
{
	const FDeterministicNumber64 Two = FDeterministicNumber64::Make(2.0);
	const FDeterministicNumber64 Ninety = FDeterministicNumber64::Make(90.0);
	const FDeterministicNumber64 SingularityTest = Z * X - W * Y;
	const FDeterministicNumber64 YawY = Two * (W * Z + X * Y);
	const FDeterministicNumber64 YawX = (DeterministicFloat::Constants::Number64::One - Two * (FDeterministicFloatMath::Square(Y) + FDeterministicFloatMath::Square(Z)));
	
	const FDeterministicNumber64 SINGULARITY_THRESHOLD = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Half.Value - DeterministicFloat::Constants::Number64::Delta.Value);
	const FDeterministicNumber64 RAD_TO_DEG = DeterministicFloat::Constants::Number64::OneEightyOverPi;
	FDeterministicNumber64 Pitch, Yaw, Roll;

	if (SingularityTest < -SINGULARITY_THRESHOLD)
	{
		Pitch = -Ninety;
		Yaw = FDeterministicFloatMath::Atan2(YawY, YawX) * RAD_TO_DEG;
		Roll = FDeterministicRotator64::NormalizeAxis(-Yaw - (Two * FDeterministicFloatMath::Atan2(X, W) * RAD_TO_DEG));
	}
	else if (SingularityTest > SINGULARITY_THRESHOLD)
	{
		Pitch = Ninety;
		Yaw = FDeterministicFloatMath::Atan2(YawY, YawX) * RAD_TO_DEG;
		Roll = FDeterministicRotator64::NormalizeAxis(Yaw - (Two * FDeterministicFloatMath::Atan2(X, W) * RAD_TO_DEG));
	}
	else
	{
		Pitch = (FDeterministicFloatMath::Asin(Two * SingularityTest) * RAD_TO_DEG); 
		Yaw = (FDeterministicFloatMath::Atan2(YawY, YawX) * RAD_TO_DEG);
		Roll = (FDeterministicFloatMath::Atan2(-Two * (W * X + Y * Z), (DeterministicFloat::Constants::Number64::One - Two * (FDeterministicFloatMath::Square(X) + FDeterministicFloatMath::Square(Y)))) * RAD_TO_DEG);
	}

	return FDeterministicRotator64(Pitch, Yaw, Roll);
}
