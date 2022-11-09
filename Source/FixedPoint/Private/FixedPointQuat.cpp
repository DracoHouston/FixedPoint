// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointQuat.h"
#include "FixedPointNumbers.h"
#include "FixedPointVector.h"


const FFixedQuat FFixedQuat::Identity = FFixedQuat(FFixed64(), FFixed64(), FFixed64(), FFixed64((int64)1));

FFixedRotator FFixedQuat::Rotator() const
{
	const FFixed64 SingularityTest = Z * X - W * Y;
	const FFixed64 YawY = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2) * (W * Z + X * Y);
	const FFixed64 YawX = (FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One) - FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2) * (FFixedPointMath::Square(Y) + FFixedPointMath::Square(Z)));

	const FFixed64 SINGULARITY_THRESHOLD = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::Half - 1);
	const FFixed64 RAD_TO_DEG = (FixedPoint::Constants::Fixed64::OneEighty / FixedPoint::Constants::Fixed64::Pi);
	FFixed64 Pitch, Yaw, Roll;

	//if (SingularityTest < -SINGULARITY_THRESHOLD)
	//{
	//	Pitch = -FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 90);
	//	Yaw = (FMath::Atan2((double)YawY, (double)YawX) * (double)RAD_TO_DEG);
	//	Roll = FFixedRotator::NormalizeAxis(-Yaw - (2.0 * FMath::Atan2(X, W) * (double)RAD_TO_DEG));
	//}
	//else if (SingularityTest > SINGULARITY_THRESHOLD)
	//{
	//	Pitch = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 90);
	//	Yaw = (FMath::Atan2((double)YawY, (double)YawX) * (double)RAD_TO_DEG);
	//	Roll = FFixedRotator::NormalizeAxis((double)Yaw - (2.0 * FMath::Atan2(X, W) * (double)RAD_TO_DEG));
	//}
	//else
	//{
	//	Pitch = (FMath::Asin(2.0 * (double)SingularityTest) * (double)RAD_TO_DEG); // Note: not FastAsin like float implementation
	//	Yaw = (FMath::Atan2((double)YawY, (double)YawX) * (double)RAD_TO_DEG);
	//	Roll = (FMath::Atan2(-2.0 * ((double)W * (double)X + (double)Y * (double)Z), (1.0 - 2.0 * (FMath::Square((double)X) + FMath::Square((double)Y)))) * (double)RAD_TO_DEG);
	//}

	return FFixedRotator(Pitch, Yaw, Roll);
}

/**
* CONSTRUCTORS
*/

//FFixedQuat



//FFixedQuat::FFixedQuat(int64 inX, int64 inY, int64 inZ, int64 inW)
//{
//	X = FFixed64(inX);
//	Y = FFixed64(inY);
//	Z = FFixed64(inZ);
//	W = FFixed64(inW);
//}
//
//FFixedQuat::FFixedQuat(float inX, float inY, float inZ, float inW)
//{
//	X = FFixed64(inX);
//	Y = FFixed64(inY);
//	Z = FFixed64(inZ);
//	W = FFixed64(inW);
//}
//
//FFixedQuat::FFixedQuat(double inX, double inY, double inZ, double inW)
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
