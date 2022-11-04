// Fill out your copyright notice in the Description page of Project Settings.

#include "FixedPointNumbers.h"



//
//FFixed64 FFixed64::Square(const FFixed64& inValue)
//{
//	return inValue * inValue;
//}
//
//FFixed64 FFixed64::Pow(const FFixed64& inValue, int32 inPower)
//{
//	FFixed64 retval = inValue;
//	for (int32 i = 0; i < inPower - 1; i++)
//	{
//		retval *= inValue;
//	}
//	return retval;
//}
//
//FFixed64 FFixed64::Max(const FFixed64& A, const FFixed64& B)
//{
//	return (B < A) ? A : B;
//}
//
//FFixed64 FFixed64::Min(const FFixed64& A, const FFixed64& B)
//{
//	return (A < B) ? A : B;
//}
//
//FFixed64 FFixed64::Abs(const FFixed64& inValue)
//{
//	return (inValue.Value > 0) ? -inValue : inValue;
//}
//
//FFixed64 FFixed64::Ceil(const FFixed64& inValue)
//{
//	return FFixed64::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::One64 - 1) >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
//}
//
//FFixed64 FFixed64::Floor(const FFixed64& inValue)
//{
//	return FFixed64::MakeFromRawInt((inValue.Value >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
//}
//
//FFixed64 FFixed64::Clamp(const FFixed64& inValue, const FFixed64& inMin, const FFixed64& inMax)
//{
//	if (inValue < inMin)
//	{
//		return inMin;
//	}
//	else if (inValue > inMax)
//	{
//		return inMax;
//	}
//	return inValue;
//}
//
//FFixed64 FFixed64::Lerp(const FFixed64& A, const FFixed64& B, const FFixed64& Alpha)
//{
//	return (A + (Alpha * (B - A)));
//}
//
//int32 FFixed64::Sign(const FFixed64& inValue)
//{
//	return FMath::Sign(inValue);
//	/*if (inValue.Value > 0)
//	{
//		return 1;
//	}
//	else if (inValue.Value == 0)
//	{
//		return 0;
//	}
//	return -1;*/
//}
//FFixed64 FFixed32::Square(const FFixed64& inValue)
//{
//	return inValue * inValue;
//}
//
//FFixed32 FFixed32::Pow(FFixed32 inValue, int32 inPower)
//{
//	FFixed32 retval = inValue;
//	for (int32 i = 0; i < inPower - 1; i++)
//	{
//		retval *= inValue;
//	}
//	return retval;
//}
//
//FFixed32 FFixed32::Max(const FFixed32& A, const FFixed32& B)
//{
//	return (B < A) ? A : B;
//}
//
//FFixed32 FFixed32::Min(const FFixed32& A, const FFixed32& B)
//{
//	return (A < B) ? A : B;
//}
//
//FFixed32 FFixed32::Abs(const FFixed32& inValue)
//{
//	return (inValue.Value > 0) ? -inValue : inValue;
//}
//
//FFixed32 FFixed32::Ceil(const FFixed32& inValue)
//{
//	return FFixed32::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::One32 - 1) >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
//}
//
//FFixed32 FFixed32::Floor(const FFixed32& inValue)
//{
//	return FFixed32::MakeFromRawInt((inValue.Value >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
//}
//
//FFixed32 FFixed32::Clamp(const FFixed32& inValue, const FFixed32& inMin, const FFixed32& inMax)
//{
//	if (inValue < inMin)
//	{
//		return inMin;
//	}
//	else if (inValue > inMax)
//	{
//		return inMax;
//	}
//	return inValue;
//}
//
//FFixed32 FFixed32::Lerp(const FFixed32& A, const FFixed32& B, const FFixed32& Alpha)
//{
//	return (A + (Alpha * (B - A)));
//}
//
//int32 FFixed32::Sign(const FFixed32& inValue)
//{
//	if (inValue.Value > 0)
//	{
//		return 1;
//	}
//	else if (inValue.Value == 0)
//	{
//		return 0;
//	}
//	return -1;
//}
