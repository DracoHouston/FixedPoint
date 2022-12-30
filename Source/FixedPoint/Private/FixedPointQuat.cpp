// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointQuat.h"
#include "FixedPointNumbers.h"
#include "FixedPointVector.h"


const FFixedQuat64 FFixedQuat64::Identity = FFixedQuat64(FFixed64(), FFixed64(), FFixed64(), FFixed64((int64)1));

FFixedRotator64 FFixedQuat64::Rotator() const
{
	const FFixed64 Two = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2);
	const FFixed64 Ninety = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 90);
	const FFixed64 SingularityTest = Z * X - W * Y;
	const FFixed64 YawY = Two * (W * Z + X * Y);
	const FFixed64 YawX = (FixedPoint::Constants::Fixed64::One - Two * (FFixedPointMath::Square(Y) + FFixedPointMath::Square(Z)));
	
	const FFixed64 SINGULARITY_THRESHOLD = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::Half - 1);
	const FFixed64 RAD_TO_DEG = (FixedPoint::Constants::Fixed64::OneEighty / FixedPoint::Constants::Fixed64::Pi);
	FFixed64 Pitch, Yaw, Roll;

	if (SingularityTest < -SINGULARITY_THRESHOLD)
	{
		Pitch = -Ninety;
		Yaw = FFixedPointMath::Atan2(YawY, YawX) * RAD_TO_DEG;
		Roll = FFixedRotator64::NormalizeAxis(-Yaw - (Two * FFixedPointMath::Atan2(X, W) * RAD_TO_DEG));
	}
	else if (SingularityTest > SINGULARITY_THRESHOLD)
	{
		Pitch = Ninety;
		Yaw = FFixedPointMath::Atan2(YawY, YawX) * RAD_TO_DEG;
		Roll = FFixedRotator64::NormalizeAxis(Yaw - (Two * FFixedPointMath::Atan2(X, W) * RAD_TO_DEG));
	}
	else
	{
		Pitch = (FFixedPointMath::Asin(Two * SingularityTest) * RAD_TO_DEG); 
		Yaw = (FFixedPointMath::Atan2(YawY, YawX) * RAD_TO_DEG);
		Roll = (FFixedPointMath::Atan2(-Two * (W * X + Y * Z), (FixedPoint::Constants::Fixed64::One - Two * (FFixedPointMath::Square(X) + FFixedPointMath::Square(Y)))) * RAD_TO_DEG);
	}

	return FFixedRotator64(Pitch, Yaw, Roll);
}

/**
* CONSTRUCTORS
*/

//FFixedQuat64



//FFixedQuat64::FFixedQuat64(int64 inX, int64 inY, int64 inZ, int64 inW)
//{
//	X = FFixed64(inX);
//	Y = FFixed64(inY);
//	Z = FFixed64(inZ);
//	W = FFixed64(inW);
//}
//
//FFixedQuat64::FFixedQuat64(float inX, float inY, float inZ, float inW)
//{
//	X = FFixed64(inX);
//	Y = FFixed64(inY);
//	Z = FFixed64(inZ);
//	W = FFixed64(inW);
//}
//
//FFixedQuat64::FFixedQuat64(double inX, double inY, double inZ, double inW)
//{
//	X = FFixed64(inX);
//	Y = FFixed64(inY);
//	Z = FFixed64(inZ);
//	W = FFixed64(inW);
//}

/**
* ACCESSORS
*/

/**
* SETTERS
*/

/**
* HELPERS
*/

/**
* COMPARISON OPERATORS
*/

/**
* ARITHMETIC OPERATORS
*/
