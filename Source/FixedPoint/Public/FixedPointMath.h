// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointNumbers.h"

struct FIXEDPOINT_API FFixedPointMath : public FMath
{
	/**
	* Degrees To Radians
	*/
	static FORCEINLINE FFixed32 DegreesToRadians(const FFixed32& inValue)
	{
		return inValue * (FixedPoint::Constants::Fixed64::Pi / FixedPoint::Constants::Fixed64::OneEighty);
	}

	/**
	* Radians To Degrees
	*/
	static FORCEINLINE FFixed32 RadiansToDegrees(const FFixed32& inValue)
	{
		return inValue * (FixedPoint::Constants::Fixed64::OneEighty / FixedPoint::Constants::Fixed64::Pi);
	}

	static FORCEINLINE FFixed64 DegreesToRadians(const FFixed64& inValue)
	{
		return inValue * (FixedPoint::Constants::Fixed64::Pi / FixedPoint::Constants::Fixed64::OneEighty);
	}

	static FORCEINLINE FFixed64 RadiansToDegrees(const FFixed64& inValue)
	{
		return inValue * (FixedPoint::Constants::Fixed64::OneEighty / FixedPoint::Constants::Fixed64::Pi);
	}

	static FFixed32 Pow(FFixed32 inValue, int32 inPower);

	static FFixed64 Pow(const FFixed64& inValue, int32 inPower);

	/**
	* Floor, returns a whole number value, rounded down, as FFixed64
	*/
	static FFixed64 Floor(const FFixed64& inValue);

	/**
	* Floor, returns a whole number value, rounded down, as FFixed32
	*/
	static FFixed32 Floor(const FFixed32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as FFixed32
	*/
	static FFixed32 CeilToFixed32(const FFixed32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as FFixed32
	*/
	static FFixed64 CeilToFixed64(const FFixed64& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as int32
	*/
	static int32 CeilToInt(const FFixed32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as int64
	*/
	static int64 CeilToInt(const FFixed64& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as float
	*/
	static float CeilToFloat(const FFixed32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as float
	*/
	static float CeilToFloat(const FFixed64& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as double
	*/
	static double CeilToDouble(const FFixed32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as double
	*/
	static double CeilToDouble(const FFixed64& inValue);

	/**
	* Is Equal, will find if 2 FFixed64s are within default tolerance
	*/
	//static bool IsEqual(const FFixed64& A, const FFixed64& B);

	/**
	* Is Equal, will find if 2 FFixed64s are within supplied tolerance
	*/
	static bool IsEqual(const FFixed64& A, const FFixed64& B, const FFixed64& inTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber);

	/**
	* Is Equal, will find if 2 FFixed32s are within default tolerance
	*/
	//static bool IsEqual(const FFixed32& A, const FFixed32& B);

	/**
	* Is Equal, will find if 2 FFixed32s are within supplied tolerance
	*/
	static bool IsEqual(const FFixed32& A, const FFixed32& B, const FFixed32& inTolerance = FixedPoint::Constants::Fixed32::KindaSmallNumber);

	/**
	* Square Root
	*/
	static FFixed32 Sqrt(const FFixed32& inValue);

	static FFixed32 InvSqrt(const FFixed32& inValue);
	/**
	* Square Root
	*/
	static FFixed64 Sqrt(const FFixed64& inValue);

	static FFixed64 InvSqrt(const FFixed64& inValue);

	/**
	* Sin, returns the sine of a FFixed64 angle in radians
	*/
	static FFixed64 Sin(const FFixed64& inValue);

	/**
	* Cos, returns the cosine of a FFixed64 angle in radians
	*/
	static FFixed64 Cos(const FFixed64& inValue);

	/**
	* Tan, returns the tangent of a FFixed64 angle in radians
	*/
	static FFixed64 Tan(const FFixed64& inValue);

	/**
	* SinAndCos, gets the sine of a FFixed64 angle in radians, and its cosine, and returns both
	* Note: this avoids calling FFixed64::Sin twice over calling FFixed64::Sin then FFixed64::Cos, which uses this!
	*/
	static void SinCos(FFixed64* outSin, FFixed64* outCos, const FFixed64& inValue);

	static FFixed64 Acos(FFixed64 x)
	{
		//copied from nvidias cg language reference implementation, full of magic numbers, i'm scared too.
		FFixed64 negate = FFixed64((int64)(x < FixedPoint::Constants::Fixed64::Zero));
		x = Abs(x);
		FFixed64 ret = FixedPoint::Constants::Fixed64::AcosMagicOne;
		ret = ret * x;
		ret = ret + FixedPoint::Constants::Fixed64::AcosMagicTwo;
		ret = ret * x;
		ret = ret - FixedPoint::Constants::Fixed64::AcosMagicThree;
		ret = ret * x;
		ret = ret + FixedPoint::Constants::Fixed64::HalfPi;
		ret = ret * Sqrt(FixedPoint::Constants::Fixed64::One - x);
		ret = ret - FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2) * negate * ret;
		return negate * FixedPoint::Constants::Fixed64::Pi + ret;
	}

	/**
	* Sin, returns the sine of a FFixed32 angle in radians
	*/
	static FFixed32 Sin(const FFixed32& inValue);

	/**
	* Cos, returns the cosine of a FFixed32 angle in radians
	*/
	static FFixed32 Cos(const FFixed32& inValue);

	/**
	* Tan, returns the tangent of a FFixed32 angle in radians
	*/
	static FFixed32 Tan(const FFixed32& inValue);

	/**
	* SinAndCos, gets the sine of a FFixed32 angle in radians, and its cosine, and returns both
	* Note: this avoids calling FFixed32::Sin twice over calling FFixed32::Sin then FFixed32::Cos, which uses this!
	*/
	static void SinAndCos(const FFixed32& inValue, FFixed32& outSin, FFixed32& outCos);

	static FFixed32 Acos(FFixed32 x)
	{
		//copied from nvidias cg language reference implementation, full of magic numbers, i'm scared too.
		FFixed32 negate = FFixed32((int32)(x < FixedPoint::Constants::Fixed32::Zero));
		x = Abs(x);
		FFixed32 ret = FixedPoint::Constants::Fixed32::AcosMagicOne;
		ret = ret * x;
		ret = ret + FixedPoint::Constants::Fixed32::AcosMagicTwo;
		ret = ret * x;
		ret = ret - FixedPoint::Constants::Fixed32::AcosMagicThree;
		ret = ret * x;
		ret = ret + FixedPoint::Constants::Fixed32::HalfPi;
		ret = ret * Sqrt(FixedPoint::Constants::Fixed32::One - x);
		ret = ret - FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::One * 2) * negate * ret;
		return negate * FixedPoint::Constants::Fixed32::Pi + ret;
	}

	/**
	 * Returns value based on comparand. The main purpose of this function is to avoid
	 * branching based on floating point comparison which can be avoided via compiler
	 * intrinsics.
	 *
	 * Please note that we don't define what happens in the case of NaNs as there might
	 * be platform specific differences.
	 *
	 * @param	Comparand		Comparand the results are based on
	 * @param	ValueGEZero		Return value if Comparand >= 0
	 * @param	ValueLTZero		Return value if Comparand < 0
	 *
	 * @return	ValueGEZero if Comparand >= 0, ValueLTZero otherwise
	 */
	static constexpr FORCEINLINE FFixed64 FloatSelect(FFixed64 Comparand, FFixed64 ValueGEZero, FFixed64 ValueLTZero)
	{
		return Comparand >= FixedPoint::Constants::Fixed64::Zero ? ValueGEZero : ValueLTZero;
	}
	static constexpr FORCEINLINE FFixed32 FloatSelect(FFixed32 Comparand, FFixed32 ValueGEZero, FFixed32 ValueLTZero)
	{
		return Comparand >= FixedPoint::Constants::Fixed32::Zero ? ValueGEZero : ValueLTZero;
	}

	UE_NODISCARD static constexpr FORCEINLINE FFixed64 GridSnap(FFixed64 Location, FFixed64 Grid)
	{
		return (Grid == FixedPoint::Constants::Fixed64::Zero) ? Location : (Floor((Location + (Grid / FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2))) / Grid) * Grid);
	}

	UE_NODISCARD static constexpr FORCEINLINE FFixed32 GridSnap(FFixed32 Location, FFixed32 Grid)
	{
		return (Grid == FixedPoint::Constants::Fixed32::Zero) ? Location : (Floor((Location + (Grid / FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::One * 2))) / Grid) * Grid);
	}

	UE_NODISCARD static constexpr FFixed32 UnwindDegrees(FFixed32 A)
	{
		while (A > FixedPoint::Constants::Fixed32::OneEighty)
		{
			A -= FixedPoint::Constants::Fixed32::ThreeSixty;
		}

		while (A < -FixedPoint::Constants::Fixed32::OneEighty)
		{
			A += FixedPoint::Constants::Fixed32::ThreeSixty;
		}

		return A;
	}

	UE_NODISCARD static constexpr FFixed64 UnwindDegrees(FFixed64 A)
	{
		while (A > FixedPoint::Constants::Fixed64::OneEighty)
		{
			A -= FixedPoint::Constants::Fixed64::ThreeSixty;
		}

		while (A < -FixedPoint::Constants::Fixed64::OneEighty)
		{
			A += FixedPoint::Constants::Fixed64::ThreeSixty;
		}

		return A;
	}

	UE_NODISCARD static constexpr FFixed64 UnwindRadians(FFixed64 A)
	{
		while (A > FixedPoint::Constants::Fixed64::Pi)
		{
			A -= FixedPoint::Constants::Fixed64::TwoPi;
		}

		while (A < -FixedPoint::Constants::Fixed64::Pi)
		{
			A += FixedPoint::Constants::Fixed64::TwoPi;
		}

		return A;
	}

	UE_NODISCARD static constexpr FFixed32 UnwindRadians(FFixed32 A)
	{
		while (A > FixedPoint::Constants::Fixed32::Pi)
		{
			A -= FixedPoint::Constants::Fixed32::TwoPi;
		}

		while (A < -FixedPoint::Constants::Fixed32::Pi)
		{
			A += FixedPoint::Constants::Fixed32::TwoPi;
		}

		return A;
	}

	static FORCEINLINE bool IsNaN(FFixed32 A) { return false; }//these all return false because fixed point numbers cant nan or inf, just here for compatibility
	static FORCEINLINE bool IsNaN(FFixed64 A) { return false; }
	static FORCEINLINE bool IsFinite(FFixed32 A) { return false; }
	static FORCEINLINE bool IsFinite(FFixed64 A) { return false; }
};
