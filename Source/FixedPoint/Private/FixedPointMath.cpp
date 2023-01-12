// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointMath.h"
#include "Misc/AssertionMacros.h"

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
	FFixed64 valsqrt = Sqrt(inValue);
	return valsqrt <= FixedPoint::Constants::Fixed64::Zero ? FixedPoint::Constants::Fixed64::Zero : FixedPoint::Constants::Fixed64::One / valsqrt;
}

FFixed32 FFixedPointMath::Sqrt(const FFixed32& inValue)
{
	if (inValue.Value == 0)
	{
		return FixedPoint::Constants::Fixed64::Zero;
	}
	if (inValue < FixedPoint::Constants::Fixed64::Zero)
	{
		return FixedPoint::Constants::Fixed64::Zero;
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
	FFixed32 valsqrt = Sqrt(inValue);
	return valsqrt <= FixedPoint::Constants::Fixed32::Zero ? FixedPoint::Constants::Fixed32::Zero : FixedPoint::Constants::Fixed32::One / valsqrt;
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
		flip = true;
		break;
	case 2:
		flip = true;
		break;
	case 3:
		mirror = true;
	default:
		break;
	}

	theta = FFixed64::Internal_Normalize(theta, halfpi);
	if (mirror)
	{
		theta = halfpi - theta;
	}
	FFixed64 thetasquared = theta * theta;
	FFixed64 result = FixedPoint::Constants::Fixed64::One;

	FFixed64 n = thetasquared;
	const FFixed64 Factorial2 = FFixed64::MakeFromRawInt(2 * FixedPoint::Constants::Raw64::One);
	result -= n / Factorial2;

	n *= thetasquared;
	const FFixed64 Factorial4 = FFixed64::MakeFromRawInt(Factorial2.Value * 3 * 4);
	result += (n / Factorial4);

	n *= thetasquared;
	const FFixed64 Factorial6 = FFixed64::MakeFromRawInt(Factorial4.Value * 5 * 6);
	result -= n / Factorial6;

	//results in better precision, but at what cost?
	n *= thetasquared;
	const FFixed64 Factorial8 = FFixed64::MakeFromRawInt(Factorial6.Value * 7 * 8);
	result += n / Factorial8;

	if (flip)
	{
		result.Value *= -1;
	}
	return result;
}

FFixed64 FFixedPointMath::Tan(const FFixed64& inValue)
{
	const FFixed64 unwoundtheta = FFixedPointMath::UnwindRadians(inValue);
	if (FFixedPointMath::IsEqual(unwoundtheta, FixedPoint::Constants::Fixed64::HalfPi))
	{
		return FixedPoint::Constants::Fixed64::BigNumber;
	}
	else if (FFixedPointMath::IsEqual(unwoundtheta, -FixedPoint::Constants::Fixed64::HalfPi))
	{
		return -FixedPoint::Constants::Fixed64::BigNumber;
	}

	FFixed64 sinval;
	FFixed64 cosval;
	FFixedPointMath::SinCos(&sinval, &cosval, inValue);
	
	return sinval / cosval;
}

void FFixedPointMath::SinCos(FFixed64* outSin, FFixed64* outCos, const FFixed64& inValue)
{
	*outSin = FFixedPointMath::Sin(inValue);
	*outCos = FFixedPointMath::Cos(inValue);
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
	const FFixed32 twopi = FixedPoint::Constants::Fixed32::TwoPi;
	const FFixed32 halfpi = FixedPoint::Constants::Fixed32::HalfPi;

	FFixed32 theta = FFixed32::Internal_Normalize(inValue, twopi);
	bool mirror = false;
	bool flip = false;
	int64 quadrant = (int64)(theta / halfpi);
	switch (quadrant)
	{
	case 0:
		break;
	case 1:
		mirror = true;
		flip = true;
		break;
	case 2:
		flip = true;
		break;
	case 3:
		mirror = true;
	default:
		break;
	}

	theta = FFixed32::Internal_Normalize(theta, halfpi);
	if (mirror)
	{
		theta = halfpi - theta;
	}
	FFixed32 thetasquared = theta * theta;
	FFixed32 result = FixedPoint::Constants::Fixed32::One;

	FFixed32 n = thetasquared;
	const FFixed32 Factorial2 = FFixed32::MakeFromRawInt(2 * FixedPoint::Constants::Raw32::One);
	result -= n / Factorial2;

	n *= thetasquared;
	const FFixed32 Factorial4 = FFixed32::MakeFromRawInt(Factorial2.Value * 3 * 4);
	result += (n / Factorial4);

	n *= thetasquared;
	const FFixed32 Factorial6 = FFixed32::MakeFromRawInt(Factorial4.Value * 5 * 6);
	result -= n / Factorial6;

	//results in better precision, but at what cost?
	n *= thetasquared;
	const FFixed32 Factorial8 = FFixed32::MakeFromRawInt(Factorial6.Value * 7 * 8);
	result += n / Factorial8;

	if (flip)
	{
		result.Value *= -1;
	}
	return result;
	/*FFixed32 retval;
	FFixed32 sinval;
	FFixedPointMath::SinAndCos(inValue, sinval, retval);
	return retval;*/
}

FFixed32 FFixedPointMath::Tan(const FFixed32& inValue)
{
	const FFixed32 unwoundtheta = FFixedPointMath::UnwindRadians(inValue);
	if (FFixedPointMath::IsEqual(unwoundtheta, FixedPoint::Constants::Fixed32::HalfPi))
	{
		return FixedPoint::Constants::Fixed32::BigNumber;
	}
	else if (FFixedPointMath::IsEqual(unwoundtheta, -FixedPoint::Constants::Fixed32::HalfPi))
	{
		return -FixedPoint::Constants::Fixed32::BigNumber;
	}
	FFixed32 sinval;
	FFixed32 cosval;
	FFixedPointMath::SinCos(&sinval, &cosval, inValue);
	return sinval / cosval;
}

void FFixedPointMath::SinCos(FFixed32* outSin, FFixed32* outCos, const FFixed32& inValue)
{
	//outSin = FFixedPointMath::Sin(inValue);
	//outCos = FFixedPointMath::Sqrt(FixedPoint::Constants::Fixed32::One - (outSin * outSin));
	*outSin = FFixedPointMath::Sin(inValue);
	*outCos = FFixedPointMath::Cos(inValue);
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
/*
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
*/
FFixed64 FFixedPointMath::Fmod(FFixed64 X, FFixed64 Y)
{
	const FFixed64 AbsY = Abs(Y);
	if (AbsY <= FixedPoint::Constants::Fixed64::SmallNumber) // Note: this constant should match that used by VectorMod() implementations
	{
		FmodReportError(X, Y);
		return 0.0;
	}
	const FFixed64 quotient = X / Y;
	return X - (TruncToFixed64(quotient) * Y);
	//return FFixed64::MakeFromRawInt(((X / Y).Value << (63 - FixedPoint::Constants::BinaryPoint64)) >> (63 - FixedPoint::Constants::BinaryPoint64));
}

FFixed32 FFixedPointMath::Fmod(FFixed32 X, FFixed32 Y)
{
	const FFixed32 AbsY = Abs(Y);
	if (AbsY <= FixedPoint::Constants::Fixed32::SmallNumber) // Note: this constant should match that used by VectorMod() implementations
	{
		FmodReportError(X, Y);
		return 0.0;
	}
	const FFixed32 quotient = X / Y;
	return X - (TruncToFixed64(quotient) * Y);
	//return FFixed32::MakeFromRawInt(((X / Y).Value << (31 - FixedPoint::Constants::BinaryPoint32)) >> (31 - FixedPoint::Constants::BinaryPoint32));
}

void FFixedPointMath::FmodReportError(FFixed64 X, FFixed64 Y)
{
	if (Y == FixedPoint::Constants::Fixed64::Zero)
	{
		ensureMsgf(Y != FixedPoint::Constants::Fixed64::Zero, TEXT("FFixedPointMath::FMod(X=%f, Y=%f) : Y is zero, this is invalid and would result in NaN!"), (double)X, (double)Y);
	}
}

void FFixedPointMath::FmodReportError(FFixed32 X, FFixed32 Y)
{
	if (Y == FixedPoint::Constants::Fixed32::Zero)
	{
		ensureMsgf(Y != FixedPoint::Constants::Fixed32::Zero, TEXT("FFixedPointMath::FMod(X=%f, Y=%f) : Y is zero, this is invalid and would result in NaN!"), (double)X, (double)Y);
	}
}
