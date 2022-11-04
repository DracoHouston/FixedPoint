// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointMath.h"


FFixed64 FFixedPointMath::Sqrt(const FFixed64& inValue)
{
	if (inValue.Value == 0)
	{
		return FFixed64();
	}
	int64 a = (inValue.Value >> 1) + 1;
	int64 b = (a + (inValue.Value / a)) >> 1;
	while (b < a)
	{
		a = b;
		b = (a + (inValue.Value / a)) >> 1;
	}
	return FFixed64::MakeFromRawInt(a << (FixedPoint::Constants::BinaryPoint64 / 2));
}

FFixed64 FFixedPointMath::InvSqrt(const FFixed64& inValue)
{
	return FixedPoint::Constants::Fixed64::One / Sqrt(inValue);
}

FFixed32 FFixedPointMath::Sqrt(const FFixed32& inValue)
{
	if (inValue.Value == 0)
	{
		return FFixed32();
	}
	int64 a = (inValue.Value >> 1) + 1;
	int64 b = (a + (inValue.Value / a)) >> 1;
	while (b < a)
	{
		a = b;
		b = (a + (inValue.Value / a)) >> 1;
	}
	return FFixed32::MakeFromRawInt(a << (FixedPoint::Constants::BinaryPoint32 / 2));
}

FFixed32 FFixedPointMath::InvSqrt(const FFixed32& inValue)
{
	return FixedPoint::Constants::Fixed32::One / Sqrt(inValue);
}

FFixed64 FFixedPointMath::Sin(const FFixed64& inValue)
{
	const FFixed64 twopi = FixedPoint::Constants::Fixed64::TwoPi;
	const FFixed64 halfpi = FixedPoint::Constants::Fixed64::HalfPi;

	FFixed64 theta = FFixed64::Internal_Normalize(inValue, twopi);
	bool mirror = false;
	bool flip = false;
	int64 quadrant = (int64)(theta / halfpi);
	switch (quadrant)
	{
	case 0:
		break;
	case 1:
		mirror = true;
		break;
	case 2:
		flip = true;
		break;
	case 3:
		mirror = true;
		flip = true;
	default:
		break;
	}

	theta = FFixed64::Internal_Normalize(theta, halfpi);
	if (mirror)
	{
		theta = halfpi - theta;
	}
	FFixed64 thetasquared = theta * theta;
	FFixed64 result = theta;

	FFixed64 n = theta * theta * theta;
	const FFixed64 Factorial3 = FFixed64::MakeFromRawInt(3 * 2 * FixedPoint::Constants::Raw64::One);
	result -= n / Factorial3;

	n *= thetasquared;
	const FFixed64 Factorial5 = FFixed64::MakeFromRawInt(Factorial3.Value * 4 * 5);
	result += (n / Factorial5);

	n *= thetasquared;
	const FFixed64 Factorial7 = FFixed64::MakeFromRawInt(Factorial5.Value * 6 * 7);
	result -= n / Factorial7;

	//results in better precision, but at what cost?
	/*n *= thetasquared;
	const FFixed64 Factorial9 = FFixed64::MakeFromRawInt(Factorial7.Value * 8 * 9);;
	result += n / Factorial9;*/

	if (flip)
	{
		result.Value *= -1;
	}
	return result;
}

FFixed64 FFixedPointMath::Cos(const FFixed64& inValue)
{
	FFixed64 retval;
	FFixed64 sinval;
	FFixedPointMath::SinCos(&sinval, &retval, inValue);
	return retval;
}

FFixed64 FFixedPointMath::Tan(const FFixed64& inValue)
{
	FFixed64 sinval;
	FFixed64 cosval;
	FFixedPointMath::SinCos(&sinval, &cosval, inValue);
	return sinval / cosval;
}

void FFixedPointMath::SinCos(FFixed64* outSin, FFixed64* outCos, const FFixed64& inValue)
{
	*outSin = FFixedPointMath::Sin(inValue);
	*outCos = FFixedPointMath::Sqrt(FixedPoint::Constants::Fixed64::One - (*outSin * *outSin));
}

FFixed32 FFixedPointMath::Sin(const FFixed32& inValue)
{
	FFixed32 twopi = FixedPoint::Constants::Fixed32::TwoPi;
	FFixed32 halfpi = FixedPoint::Constants::Fixed32::HalfPi;

	FFixed32 theta = FFixed32::Internal_Normalize(inValue, twopi);
	bool mirror = false;
	bool flip = false;
	int32 quadrant = (int32)(theta / halfpi);
	switch (quadrant)
	{
	case 0:
		break;
	case 1:
		mirror = true;
		break;
	case 2:
		flip = true;
		break;
	case 3:
		mirror = true;
		flip = true;
	default:
		break;
	}

	theta = FFixed32::Internal_Normalize(theta, halfpi);
	if (mirror)
	{
		theta = halfpi - theta;
	}
	FFixed32 thetasquared = theta * theta;
	FFixed32 result = theta;

	FFixed32 n = theta * theta * theta;
	const FFixed32 Factorial3 = FFixed32::MakeFromRawInt(3 * 2 * FixedPoint::Constants::Raw32::One);
	result -= n / Factorial3;

	n *= thetasquared;
	const FFixed32 Factorial5 = FFixed32::MakeFromRawInt(Factorial3.Value * 4 * 5);
	result += (n / Factorial5);

	n *= thetasquared;
	const FFixed32 Factorial7 = FFixed32::MakeFromRawInt(Factorial5.Value * 6 * 7);
	result -= n / Factorial7;

	//results in better precision, but at what cost?
	/*n *= thetasquared;
	const FFixed32 Factorial9 = FFixed32::MakeFromRawInt(Factorial7.Value * 8 * 9);;
	result += n / Factorial9;*/

	if (flip)
	{
		result.Value *= -1;
	}
	return result;
}

FFixed32 FFixedPointMath::Cos(const FFixed32& inValue)
{
	FFixed32 retval;
	FFixed32 sinval;
	FFixedPointMath::SinAndCos(inValue, sinval, retval);
	return retval;
}

FFixed32 FFixedPointMath::Tan(const FFixed32& inValue)
{
	FFixed32 sinval;
	FFixed32 cosval;
	FFixedPointMath::SinAndCos(inValue, sinval, cosval);
	return sinval / cosval;
}

void FFixedPointMath::SinAndCos(const FFixed32& inValue, FFixed32& outSin, FFixed32& outCos)
{
	outSin = FFixedPointMath::Sin(inValue);
	outCos = FFixedPointMath::Sqrt(FixedPoint::Constants::Fixed32::One - (outSin * outSin));
}


//bool FFixedPointMath::IsEqual(const FFixed32& A, const FFixed32& B)
//{
//	FFixed32 tolerance = FFixed32::MakeFromRawInt(FixedPoint::Constants::EqualityThreshold32);
//	return FFixedPointMath::IsEqual(A, B, tolerance);
//}

bool FFixedPointMath::IsEqual(const FFixed32& A, const FFixed32& B, const FFixed32& inTolerance)
{
	return FFixedPointMath::Abs(A - B) <= inTolerance;
}

//bool FFixedPointMath::IsEqual(const FFixed64& A, const FFixed64& B)
//{
//	FFixed64 tolerance = FFixed64::MakeFromRawInt(FixedPoint::Constants::EqualityThreshold64);
//	return FFixedPointMath::IsEqual(A, B, tolerance);
//}

bool FFixedPointMath::IsEqual(const FFixed64& A, const FFixed64& B, const FFixed64& inTolerance)
{
	return FFixedPointMath::Abs(A - B) <= inTolerance;
}

FFixed32 FFixedPointMath::Pow(FFixed32 inValue, int32 inPower)
{
	FFixed32 retval = inValue;
	for (int32 i = 0; i < inPower - 1; i++)
	{
		retval *= inValue;
	}
	return retval;
}

FFixed64 FFixedPointMath::Pow(const FFixed64& inValue, int32 inPower)
{
	FFixed64 retval = inValue;
	for (int32 i = 0; i < inPower - 1; i++)
	{
		retval *= inValue;
	}
	return retval;
}

FFixed64 FFixedPointMath::Floor(const FFixed64& inValue)
{
	return FFixed64::MakeFromRawInt((inValue.Value >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
}

FFixed32 FFixedPointMath::Floor(const FFixed32& inValue)
{
	return FFixed32::MakeFromRawInt((inValue.Value >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
}

FFixed32 FFixedPointMath::CeilToFixed32(const FFixed32& inValue)
{
	return FFixed32::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
}

FFixed64 FFixedPointMath::CeilToFixed64(const FFixed64& inValue)
{
	return FFixed64::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw64::One - 1) >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
}

int32 FFixedPointMath::CeilToInt(const FFixed32& inValue)
{
	return (inValue.Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32;
}

int64 FFixedPointMath::CeilToInt(const FFixed64& inValue)
{
	return (inValue.Value + FixedPoint::Constants::Raw64::One - 1) >> FixedPoint::Constants::BinaryPoint64;
}

float FFixedPointMath::CeilToFloat(const FFixed32& inValue)
{
	return (float)FFixed32::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
}

float FFixedPointMath::CeilToFloat(const FFixed64& inValue)
{
	return (float)FFixed64::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw64::One - 1) >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
}

double FFixedPointMath::CeilToDouble(const FFixed32& inValue)
{
	return (double)FFixed32::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
}

double FFixedPointMath::CeilToDouble(const FFixed64& inValue)
{
	return (double)FFixed64::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw64::One - 1) >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
}
