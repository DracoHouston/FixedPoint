// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointBP.h"
#include "FixedPointNumbers.h"
#include "FixedPointMath.h"

FFixed64 UFixedPointBP::Fixed64FromDouble(const double& inValue)
{
    return FFixed64(inValue);
}

double UFixedPointBP::DoubleFromFixed64(const FFixed64& inValue)
{
    return (double)inValue;
}

FFixed64 UFixedPointBP::Fixed64FromFloat(const float& inValue)
{
    return FFixed64(inValue);
}

float UFixedPointBP::FloatFromFixed64(const FFixed64& inValue)
{
    return (float)inValue;
}

FFixed64 UFixedPointBP::Fixed64FromInt64(const int64& inValue)
{
    return FFixed64(inValue);
}

int64 UFixedPointBP::Int64FromFixed64(const FFixed64& inValue, bool bCeil)
{
    return bCeil ? (int64)inValue : FFixedPointMath::CeilToInt(inValue);
}

FFixed64 UFixedPointBP::Fixed64FromFixed32(const FFixed32& inValue)
{
    return FFixed64(inValue);
}

FFixed64 UFixedPointBP::AddFixed64(const FFixed64& A, const FFixed64& B)
{
    return A + B;
}

FFixed64 UFixedPointBP::SubtractFixed64(const FFixed64& A, const FFixed64& B)
{
    return A - B;
}

FFixed64 UFixedPointBP::MultiplyFixed64(const FFixed64& A, const FFixed64& B)
{
    return A * B;
}

FFixed64 UFixedPointBP::DivideFixed64(const FFixed64& A, const FFixed64& B)
{
    return A / B;
}

FFixed64 UFixedPointBP::NegateFixed64(const FFixed64& inValue)
{
    return -inValue;
}

FFixed64 UFixedPointBP::SquareRootFixed64(const FFixed64& inValue)
{
    return FFixedPointMath::Sqrt(inValue);
}

//FFixed64 UFixedPointBP::PowFixed64(const FFixed64& inValue, const int32& inPower)
//{
//    return FFixedPointMath::Pow(inValue, inPower);
//}

FFixed64 UFixedPointBP::MaxFixed64(const FFixed64& A, const FFixed64& B)
{
    return FFixedPointMath::Max(A, B);
}

FFixed64 UFixedPointBP::MinFixed64(const FFixed64& A, const FFixed64& B)
{
    return FFixedPointMath::Min(A, B);
}

FFixed64 UFixedPointBP::AbsFixed64(const FFixed64& inValue)
{
    return FFixedPointMath::Abs(inValue);
}

FFixed64 UFixedPointBP::CeilFixed64(const FFixed64& inValue)
{
    return FFixedPointMath::CeilToFixed64(inValue);
}

FFixed64 UFixedPointBP::FloorFixed64(const FFixed64& inValue)
{
    return FFixedPointMath::Floor(inValue);
}

FFixed64 UFixedPointBP::ClampFixed64(const FFixed64& inValue, const FFixed64& inMin, const FFixed64& inMax)
{
    return FFixedPointMath::Clamp(inValue, inMin, inMax);
}

FFixed64 UFixedPointBP::LerpFixed64(const FFixed64& A, const FFixed64& B, const FFixed64& Alpha)
{
    return FFixedPointMath::Lerp(A, B, Alpha);
}

int32 UFixedPointBP::SignFixed64(const FFixed64& inValue)
{
    return FFixedPointMath::Sign(inValue);
}

FFixed64 UFixedPointBP::PiFixed64()
{
    return FixedPoint::Constants::Fixed64::Pi;
}

FFixed64 UFixedPointBP::NormalizeFixed64(const FFixed64& inValue, const FFixed64& inRange)
{
    return FFixed64::Internal_Normalize(inValue, inRange);
}

FFixed64 UFixedPointBP::SinFixed64(const FFixed64& inValue)
{
    return FFixedPointMath::Sin(inValue);
}

FFixed32 UFixedPointBP::Fixed32FromDouble(const double& inValue)
{
    return FFixed32(inValue);
}

double UFixedPointBP::DoubleFromFixed32(const FFixed32& inValue)
{
    return (double)inValue;
}

FFixed32 UFixedPointBP::Fixed32FromFloat(const float& inValue)
{
    return FFixed32(inValue);
}

float UFixedPointBP::FloatFromFixed32(const FFixed32& inValue)
{
    return (float)inValue;
}

FFixed32 UFixedPointBP::Fixed32FromInt32(const int32& inValue)
{
    return FFixed32(inValue);
}

int32 UFixedPointBP::Int32FromFixed32(const FFixed32& inValue, bool bCeil)
{
    return bCeil ? (int32)inValue : FFixedPointMath::CeilToInt(inValue);
}

FFixed32 UFixedPointBP::Fixed32FromFixed64(const FFixed64& inValue)
{
    return FFixed32(inValue);
}

FFixed32 UFixedPointBP::AddFixed32(const FFixed32& A, const FFixed32& B)
{
    return A + B;
}

FFixed32 UFixedPointBP::SubtractFixed32(const FFixed32& A, const FFixed32& B)
{
    return A - B;
}

FFixed32 UFixedPointBP::MultiplyFixed32(const FFixed32& A, const FFixed32& B)
{
    return A * B;
}

FFixed32 UFixedPointBP::DivideFixed32(const FFixed32& A, const FFixed32& B)
{
    return A / B;
}

FFixed32 UFixedPointBP::NegateFixed32(const FFixed32& inValue)
{
    return -inValue;
}

FFixed32 UFixedPointBP::SquareRootFixed32(const FFixed32& inValue)
{
    return FFixedPointMath::Sqrt(inValue);
}

//FFixed32 UFixedPointBP::PowFixed32(const FFixed32& inValue, const int32& inPower)
//{
//    return FFixedPointMath::Pow(inValue, inPower);
//}

FFixed32 UFixedPointBP::MaxFixed32(const FFixed32& A, const FFixed32& B)
{
    return FFixedPointMath::Max(A, B);
}

FFixed32 UFixedPointBP::MinFixed32(const FFixed32& A, const FFixed32& B)
{
    return FFixedPointMath::Min(A, B);
}

FFixed32 UFixedPointBP::AbsFixed32(const FFixed32& inValue)
{
    return FFixedPointMath::Abs(inValue);
}

FFixed32 UFixedPointBP::CeilFixed32(const FFixed32& inValue)
{
    return FFixedPointMath::CeilToFixed32(inValue);
}

FFixed32 UFixedPointBP::FloorFixed32(const FFixed32& inValue)
{
    return FFixedPointMath::Floor(inValue);
}

FFixed32 UFixedPointBP::ClampFixed32(const FFixed32& inValue, const FFixed32& inMin, const FFixed32& inMax)
{
    return FFixedPointMath::Clamp(inValue, inMin, inMax);
}

FFixed32 UFixedPointBP::LerpFixed32(const FFixed32& A, const FFixed32& B, const FFixed32& Alpha)
{
    return FFixedPointMath::Lerp(A, B, Alpha);
}

int32 UFixedPointBP::SignFixed32(const FFixed32& inValue)
{
    return FFixedPointMath::Sign(inValue);
}
