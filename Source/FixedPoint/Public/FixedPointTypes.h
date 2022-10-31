// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "CoreMinimal.h"

namespace FixedPoint
{
	namespace Constants
	{

		//number of bits beyond the binary point for our fixed point number types. We shift by this much.
		constexpr uint8 BinaryPoint64 = 20;
		//number of bits beyond the binary point for our fixed point number types. We shift by this much.
		constexpr uint8 BinaryPoint32 = 16;
		//difference between 64 bit and 32 bit binary points, for conversion
		constexpr uint8 BinaryPointDifference = BinaryPoint64 - BinaryPoint32;

		namespace Raw64
		{
			//The value 1 in our 64 bit fixed point numbers
			constexpr int64 One = 1 << FixedPoint::Constants::BinaryPoint64;
			//The value 0.5 in our 64 bit fixed point numbers
			constexpr int64 Half = One >> 1;
			//The value 0.25 in our 64 bit fixed point numbers
			constexpr int64 Quarter = Half >> 1;
			//The value 0.125 in our 64 bit fixed point numbers
			constexpr int64 Eigth = Quarter >> 1;
			//The value 1 in our 64 bit fixed point numbers, cast to a double precision float
			constexpr double OneD = (double)One;

			//The value 180.0 in our 64 bit fixed point numbers
			constexpr int64 OneEighty = One * 180;
			//The value 360.0 in our 64 bit fixed point numbers
			constexpr int64 ThreeSixty = One * 360;

			constexpr int64 Pi = 3294198;
			constexpr int64 SmallNumber = 1;
			constexpr int64 KindaSmallNumber = 104;
			constexpr int64 BigNumber = 9223372036854775807;
			constexpr int64 EulersNumber = 2850325;
			constexpr int64 GoldenRatio = 1696631;
			constexpr int64 InvPi = 333772;
			constexpr int64 HalfPi = 1647099;
			constexpr int64 TwoPi = 6588397;
			constexpr int64 PiSquared = 10349030;
			constexpr int64 SQRT2 = 1482910;
			constexpr int64 SQRT3 = 1816186;
			constexpr int64 InvSQRT2 = 741455;
			constexpr int64 InvSQRT3 = 605395;
			constexpr int64 HalfSQRT2 = 741455;
			constexpr int64 HalfSQRT3 = 908093;
			constexpr int64 Delta = 10;
			constexpr int64 NormalThresh = 104;
			constexpr int64 ThreshPointOnPlane = 104857;
			constexpr int64 ThreshPointOnSide = 209715;
			constexpr int64 ThreshPointsAreSame = 20;
			constexpr int64 ThreshPointsAreNear = 15728;
			constexpr int64 ThreshNormalsAreSame = 20;
			constexpr int64 ThreshUVsAreSame = 1024;
			constexpr int64 ThreshVectorsAreNear = 419;
			constexpr int64 ThreshSplitPolyWithPlane = 262144;
			constexpr int64 ThreshSplitPolyPrecisely = 10485;
			constexpr int64 ThreshZeroNormSquared = 104;
			constexpr int64 ThreshNormalsAreParallel = 1048413;
			constexpr int64 ThreshNormalsAreOrthogonal = 18302;
			constexpr int64 ThreshVectorNormalized = 10485;
			constexpr int64 ThreshQuatNormalized = 10485;
			constexpr int64 AcosMagicOne = -19639;
			constexpr int64 AcosMagicTwo = 77868;
			constexpr int64 AcosMagicThree = 222418;
		}
		namespace Raw32
		{
			
			//The value 1 in our 32 bit fixed point numbers
			constexpr int32 One = 1 << FixedPoint::Constants::BinaryPoint32;
			//The value 0.5 in our 32 bit fixed point numbers
			constexpr int32 Half = One >> 1;
			//The value 0.25 in our 32 bit fixed point numbers
			constexpr int32 Quarter = Half >> 1;
			//The value 0.125 in our 32 bit fixed point numbers
			constexpr int32 Eigth = Quarter >> 1;
			//The value 1 in our 32 bit fixed point numbers, cast to a double precision float
			constexpr double OneD = (double)One;

			//The value 180.0 in our 32 bit fixed point numbers
			constexpr int32 OneEighty = One * 180;
			//The value 360.0 in our 32 bit fixed point numbers
			constexpr int32 ThreeSixty = One * 360;

			constexpr int32 Pi = 205887;
			constexpr int32 SmallNumber = 1;
			constexpr int32 KindaSmallNumber = 6;
			constexpr int32 BigNumber = 2147483647;
			constexpr int32 EulersNumber = 178145;
			constexpr int32 GoldenRatio = 106039;
			constexpr int32 InvPi = 20860;
			constexpr int32 HalfPi = 102943;
			constexpr int32 TwoPi = 411774;
			constexpr int32 PiSquared = 646814;
			constexpr int32 SQRT2 = 92681;
			constexpr int32 SQRT3 = 113511;
			constexpr int32 InvSQRT2 = 46340;
			constexpr int32 InvSQRT3 = 37837;
			constexpr int32 HalfSQRT2 = 46340;
			constexpr int32 HalfSQRT3 = 56755;
			constexpr int32 Delta = 2;
			constexpr int32 NormalThresh = 6;
			constexpr int32 ThreshPointOnPlane = 6553;
			constexpr int32 ThreshPointOnSide = 13107;
			constexpr int32 ThreshPointsAreSame = 1;
			constexpr int32 ThreshPointsAreNear = 983;
			constexpr int32 ThreshNormalsAreSame = 1;
			constexpr int32 ThreshUVsAreSame = 64;
			constexpr int32 ThreshVectorsAreNear = 26;
			constexpr int32 ThreshSplitPolyWithPlane = 16384;
			constexpr int32 ThreshSplitPolyPrecisely = 655;
			constexpr int32 ThreshZeroNormSquared = 6;
			constexpr int32 ThreshNormalsAreParallel = 65525;
			constexpr int32 ThreshNormalsAreOrthogonal = 1143;
			constexpr int32 ThreshVectorNormalized = 655;
			constexpr int32 ThreshQuatNormalized = 655;
			constexpr int32 AcosMagicOne = -1227;
			constexpr int32 AcosMagicTwo = 4866;
			constexpr int32 AcosMagicThree = 13901;
		}
	}
}

struct FFixed64;
struct FFixed32;
struct FFixedVector;
struct FFixedVector2d;
struct FFixedVector4d;
struct FFixedMatrix;
struct FFixedQuat;