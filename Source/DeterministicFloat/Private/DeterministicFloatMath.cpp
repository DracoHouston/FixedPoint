// Fill out your copyright notice in the Description page of Project Settings.


#include "DeterministicFloatMath.h"
#include "Misc/AssertionMacros.h"

FDeterministicNumber64 FDeterministicFloatMath::Sqrt(const FDeterministicNumber64& inValue)
{
	if (inValue == DeterministicFloat::Constants::Number64::Zero)
	{
		return DeterministicFloat::Constants::Number64::Zero;
	}
	if (inValue < DeterministicFloat::Constants::Number64::Zero)
	{
		return DeterministicFloat::Constants::Number64::Zero;
	}
	/*We are using n itself as initial approximation
          This can definitely be improved */
	FDeterministicNumber64 x = inValue;
	FDeterministicNumber64 y = FDeterministicNumber64::Make(1.0);
	while (Abs(x - y) > DeterministicFloat::Constants::Number64::KindaSmallNumber) {
		x = (x + y) / FDeterministicNumber64::Make(2.0);
		y = inValue / x;
	}
	return x;
}

FDeterministicNumber64 FDeterministicFloatMath::InvSqrt(const FDeterministicNumber64& inValue)
{
	FDeterministicNumber64 valsqrt = Sqrt(inValue);
	return valsqrt <= DeterministicFloat::Constants::Number64::Zero ? DeterministicFloat::Constants::Number64::Zero : DeterministicFloat::Constants::Number64::One / valsqrt;
}

FDeterministicNumber32 FDeterministicFloatMath::Sqrt(const FDeterministicNumber32& inValue)
{
	if (inValue == DeterministicFloat::Constants::Number32::Zero)
	{
		return DeterministicFloat::Constants::Number32::Zero;
	}
	if (inValue < DeterministicFloat::Constants::Number32::Zero)
	{
		return DeterministicFloat::Constants::Number32::Zero;
	}
	/*We are using n itself as initial approximation
          This can definitely be improved */
	FDeterministicNumber64 x = inValue;
	FDeterministicNumber64 y = FDeterministicNumber64::Make(1.0);
	while (Abs(x - y) > DeterministicFloat::Constants::Number32::KindaSmallNumber) {
		x = (x + y) / FDeterministicNumber32::Make(2.0);
		y = inValue / x;
	}
	return x;
}

FDeterministicNumber32 FDeterministicFloatMath::InvSqrt(const FDeterministicNumber32& inValue)
{
	FDeterministicNumber32 valsqrt = Sqrt(inValue);
	return valsqrt <= DeterministicFloat::Constants::Number32::Zero ? DeterministicFloat::Constants::Number32::Zero : DeterministicFloat::Constants::Number32::One / valsqrt;
}

FDeterministicNumber64 FDeterministicFloatMath::Sin(const FDeterministicNumber64& inValue)
{
	bool mirror = false;
	bool flip = false;
	int32 quadrant = GetQuadrantRadians(inValue);
	switch (quadrant)
	{
	case 0:
		break;
	case 1:
		/*if (inValue != DeterministicFloat::Constants::Number64::HalfPi)
		{*/
			mirror = true;
		//}
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
	FDeterministicNumber64 theta = inValue;
	while (theta > DeterministicFloat::Constants::Number64::HalfPi)
	{
		theta -= DeterministicFloat::Constants::Number64::HalfPi;
	}
	while (theta < DeterministicFloat::Constants::Number64::Zero)
	{
		theta += DeterministicFloat::Constants::Number64::HalfPi;
	}
	if (mirror)
	{
		theta = DeterministicFloat::Constants::Number64::HalfPi - theta;
	}
	FDeterministicNumber64 thetasquared = theta * theta;
	FDeterministicNumber64 result = theta;

	FDeterministicNumber64 n = theta * theta * theta;
	result -= (n / DeterministicFloat::Constants::Number64::FactorialThree);

	n *= thetasquared;
	result += (n / DeterministicFloat::Constants::Number64::FactorialFive);

	n *= thetasquared;
	result -= (n / DeterministicFloat::Constants::Number64::FactorialSeven);

	//results in better precision, but at what cost?
	/*n *= thetasquared;
	result -= (n / FDeterministicNumber64::Make(362880.0));*/

	if (flip)
	{
		result.Value = -result.Value;
	}
	return result;
}

FDeterministicNumber64 FDeterministicFloatMath::Cos(const FDeterministicNumber64& inValue)
{
	bool mirror = false;
	bool flip = false;
	int32 quadrant = GetQuadrantRadians(inValue);
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

	FDeterministicNumber64 theta = inValue;
	while (theta > DeterministicFloat::Constants::Number64::HalfPi)
	{
		theta -= DeterministicFloat::Constants::Number64::HalfPi;
	}
	while (theta < DeterministicFloat::Constants::Number64::Zero)
	{
		theta += DeterministicFloat::Constants::Number64::HalfPi;
	}
	if (mirror)
	{
		theta = DeterministicFloat::Constants::Number64::HalfPi - theta;
	}
	FDeterministicNumber64 thetasquared = theta * theta;
	FDeterministicNumber64 result = DeterministicFloat::Constants::Number64::One;

	FDeterministicNumber64 n = thetasquared;
	result -= (n / DeterministicFloat::Constants::Number64::FactorialTwo);

	n *= thetasquared;
	result += (n / DeterministicFloat::Constants::Number64::FactorialFour);

	n *= thetasquared;
	result -= (n / DeterministicFloat::Constants::Number64::FactorialSix);

	n *= thetasquared;
	result += (n / DeterministicFloat::Constants::Number64::FactorialEight);

	if (flip)
	{
		result.Value = -result.Value;
	}
	return result;
}

FDeterministicNumber64 FDeterministicFloatMath::Tan(const FDeterministicNumber64& inValue)
{
	const FDeterministicNumber64 unwoundtheta = FDeterministicFloatMath::UnwindRadians(inValue);
	if (FDeterministicFloatMath::IsEqual(unwoundtheta, DeterministicFloat::Constants::Number64::HalfPi))
	{
		return DeterministicFloat::Constants::Number64::BigNumber;
	}
	else if (FDeterministicFloatMath::IsEqual(unwoundtheta, -DeterministicFloat::Constants::Number64::HalfPi))
	{
		return -DeterministicFloat::Constants::Number64::BigNumber;
	}

	FDeterministicNumber64 sinval;
	FDeterministicNumber64 cosval;
	FDeterministicFloatMath::SinCos(&sinval, &cosval, inValue);
	
	return sinval / cosval;
}

void FDeterministicFloatMath::SinCos(FDeterministicNumber64* outSin, FDeterministicNumber64* outCos, const FDeterministicNumber64& inValue)
{
	*outSin = FDeterministicFloatMath::Sin(inValue);
	*outCos = FDeterministicFloatMath::Cos(inValue);
}

FDeterministicNumber32 FDeterministicFloatMath::Sin(const FDeterministicNumber32& inValue)
{
	bool mirror = false;
	bool flip = false;
	int32 quadrant = GetQuadrantRadians(inValue);
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

	FDeterministicNumber32 theta = inValue;
	while (theta > DeterministicFloat::Constants::Number32::HalfPi)
	{
		theta -= DeterministicFloat::Constants::Number32::HalfPi;
	}
	while (theta < DeterministicFloat::Constants::Number32::Zero)
	{
		theta += DeterministicFloat::Constants::Number32::HalfPi;
	}
	if (mirror)
	{
		theta = DeterministicFloat::Constants::Number32::HalfPi - theta;
	}
	FDeterministicNumber32 thetasquared = theta * theta;
	FDeterministicNumber32 result = theta;

	FDeterministicNumber32 n = theta * theta * theta;
	result -= (n / DeterministicFloat::Constants::Number32::FactorialThree);

	n *= thetasquared;
	result += (n / DeterministicFloat::Constants::Number32::FactorialFive);

	n *= thetasquared;
	result -= (n / DeterministicFloat::Constants::Number32::FactorialSeven);

	if (flip)
	{
		result.Value = -result.Value;
	}
	return result;
}

FDeterministicNumber32 FDeterministicFloatMath::Cos(const FDeterministicNumber32& inValue)
{
	bool mirror = false;
	bool flip = false;
	int32 quadrant = GetQuadrantRadians(inValue);
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

	FDeterministicNumber32 theta = inValue;
	while (theta > DeterministicFloat::Constants::Number32::HalfPi)
	{
		theta -= DeterministicFloat::Constants::Number32::HalfPi;
	}
	while (theta < DeterministicFloat::Constants::Number32::Zero)
	{
		theta += DeterministicFloat::Constants::Number32::HalfPi;
	}
	if (mirror)
	{
		theta = DeterministicFloat::Constants::Number32::HalfPi - theta;
	}
	FDeterministicNumber32 thetasquared = theta * theta;
	FDeterministicNumber32 result = DeterministicFloat::Constants::Number32::One;

	FDeterministicNumber32 n = thetasquared;
	result -= (n / DeterministicFloat::Constants::Number32::FactorialTwo);

	n *= thetasquared;
	result += (n / DeterministicFloat::Constants::Number32::FactorialFour);

	n *= thetasquared;
	result -= (n / DeterministicFloat::Constants::Number32::FactorialSix);

	n *= thetasquared;
	result += (n / DeterministicFloat::Constants::Number32::FactorialEight);

	if (flip)
	{
		result.Value = -result.Value;
	}
	return result;
}

FDeterministicNumber32 FDeterministicFloatMath::Tan(const FDeterministicNumber32& inValue)
{
	const FDeterministicNumber32 unwoundtheta = FDeterministicFloatMath::UnwindRadians(inValue);
	if (FDeterministicFloatMath::IsEqual(unwoundtheta, DeterministicFloat::Constants::Number32::HalfPi))
	{
		return DeterministicFloat::Constants::Number32::BigNumber;
	}
	else if (FDeterministicFloatMath::IsEqual(unwoundtheta, -DeterministicFloat::Constants::Number32::HalfPi))
	{
		return -DeterministicFloat::Constants::Number32::BigNumber;
	}
	FDeterministicNumber32 sinval;
	FDeterministicNumber32 cosval;
	FDeterministicFloatMath::SinCos(&sinval, &cosval, inValue);
	return sinval / cosval;
}

void FDeterministicFloatMath::SinCos(FDeterministicNumber32* outSin, FDeterministicNumber32* outCos, const FDeterministicNumber32& inValue)
{
	*outSin = FDeterministicFloatMath::Sin(inValue);
	*outCos = FDeterministicFloatMath::Cos(inValue);
}

bool FDeterministicFloatMath::IsEqual(const FDeterministicNumber32& A, const FDeterministicNumber32& B, const FDeterministicNumber32& inTolerance)
{
	return FDeterministicFloatMath::Abs(A - B) <= inTolerance;
}

bool FDeterministicFloatMath::IsEqual(const FDeterministicNumber64& A, const FDeterministicNumber64& B, const FDeterministicNumber64& inTolerance)
{
	return FDeterministicFloatMath::Abs(A - B) <= inTolerance;
}

FDeterministicNumber64 FDeterministicFloatMath::Fmod(FDeterministicNumber64 X, FDeterministicNumber64 Y)
{
	const FDeterministicNumber64 AbsY = Abs(Y);
	if (AbsY <= DeterministicFloat::Constants::Number64::SmallNumber) // Note: this constant should match that used by VectorMod() implementations
	{
		FmodReportError(X, Y);
		return 0.0;
	}
	const FDeterministicNumber64 quotient = X / Y;
	return X - (TruncToNumber64(quotient) * Y);
}

FDeterministicNumber32 FDeterministicFloatMath::Fmod(FDeterministicNumber32 X, FDeterministicNumber32 Y)
{
	const FDeterministicNumber32 AbsY = Abs(Y);
	if (AbsY <= DeterministicFloat::Constants::Number32::SmallNumber) // Note: this constant should match that used by VectorMod() implementations
	{
		FmodReportError(X, Y);
		return 0.0;
	}
	const FDeterministicNumber32 quotient = X / Y;
	return X - (TruncToNumber64(quotient) * Y);
}

void FDeterministicFloatMath::FmodReportError(FDeterministicNumber64 X, FDeterministicNumber64 Y)
{
	if (Y == DeterministicFloat::Constants::Number64::Zero)
	{
		ensureMsgf(Y != DeterministicFloat::Constants::Number64::Zero, TEXT("FDeterministicFloatMath::FMod(X=%f, Y=%f) : Y is zero, this is invalid and would result in NaN!"), (double)X, (double)Y);
	}
}

void FDeterministicFloatMath::FmodReportError(FDeterministicNumber32 X, FDeterministicNumber32 Y)
{
	if (Y == DeterministicFloat::Constants::Number32::Zero)
	{
		ensureMsgf(Y != DeterministicFloat::Constants::Number32::Zero, TEXT("FDeterministicFloatMath::FMod(X=%f, Y=%f) : Y is zero, this is invalid and would result in NaN!"), (double)X, (double)Y);
	}
}
