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
		return inValue * (FixedPoint::Constants::Fixed32::Pi / FixedPoint::Constants::Fixed32::OneEighty);
	}

	/**
	* Radians To Degrees
	*/
	static FORCEINLINE FFixed32 RadiansToDegrees(const FFixed32& inValue)
	{
		return inValue * (FixedPoint::Constants::Fixed32::OneEighty / FixedPoint::Constants::Fixed32::Pi);
	}

	static FORCEINLINE FFixed64 DegreesToRadians(const FFixed64& inValue)
	{
		return inValue * (FixedPoint::Constants::Fixed64::Pi / FixedPoint::Constants::Fixed64::OneEighty);
	}

	static FORCEINLINE FFixed64 RadiansToDegrees(const FFixed64& inValue)
	{
		return inValue * (FixedPoint::Constants::Fixed64::OneEighty / FixedPoint::Constants::Fixed64::Pi);
	}
	/*
	static FORCEINLINE FFixed64 Exp(FFixed64 Value) 
	{ 
		FFixed64 retval = FixedPoint::Constants::Fixed64::One + Value;
		FFixed64 x = Value * Value;
		const FFixed64 Factorial2 = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value * 2);
		retval += (x / Factorial2);
		x = x * Value;
		const FFixed64 Factorial3 = FFixed64::MakeFromRawInt(Factorial2.Value * 3);
		retval += (x / Factorial3);
		x = x * Value;
		const FFixed64 Factorial4 = FFixed64::MakeFromRawInt(Factorial3.Value * 4);
		retval += (x / Factorial4);
		x = x * Value;
		const FFixed64 Factorial5 = FFixed64::MakeFromRawInt(Factorial4.Value * 5);
		retval += (x / Factorial5);
		x = x * Value;
		const FFixed64 Factorial6 = FFixed64::MakeFromRawInt(Factorial5.Value * 6);
		retval += (x / Factorial6);
		x = x * Value;
		const FFixed64 Factorial7 = FFixed64::MakeFromRawInt(Factorial6.Value * 7);
		retval += (x / Factorial7);
		x = x * Value;
		const FFixed64 Factorial8 = FFixed64::MakeFromRawInt(Factorial7.Value * 8);
		retval += (x / Factorial8);
		x = x * Value;
		
		return retval; 
	}
	*/
	//static FFixed32 Pow(FFixed32 inValue, int32 inPower);

	//static FFixed64 Pow(const FFixed64& inValue, int32 inPower);

	/**
	* Floor, returns a whole number value, rounded down, as FFixed64
	*/
	static FFixed64 Floor(const FFixed64& inValue)
	{
		return FFixed64::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw64::Half - 1) >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
	}

	/**
	* Floor, returns a whole number value, rounded down, as FFixed32
	*/
	static FFixed32 Floor(const FFixed32& inValue)
	{
		return FFixed32::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw32::Half - 1) >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
	}

	/**
	 * Converts a float to a nearest less or equal integer.
	 * @param F		Floating point value to convert
	 * @return		An integer less or equal to 'F'.
	 */
	static FORCEINLINE int32 FloorToInt32(FFixed32 F)
	{
		return (int32)Floor(F);
	}
	static FORCEINLINE int32 FloorToInt32(FFixed64 F)
	{
		return (int32)Floor(F);
	}
	static FORCEINLINE int64 FloorToInt64(FFixed64 F)
	{
		return (int64)Floor(F);
	}

	static FORCEINLINE int32 FloorToInt(FFixed32 F) { return FloorToInt32(F); }
	static FORCEINLINE int64 FloorToInt(FFixed64 F) { return FloorToInt64(F); }


	/**
	* Converts a float to the nearest less or equal integer.
	* @param F		Floating point value to convert
	* @return		An integer less or equal to 'F'.
	*/
	static FORCEINLINE float FloorToFloat(FFixed32 F)
	{
		return (float)Floor(F);
	}

	/**
	* Converts a double to a less or equal integer.
	* @param F		Floating point value to convert
	* @return		The nearest integer value to 'F'.
	*/
	static FORCEINLINE double FloorToDouble(FFixed64 F)
	{
		return (double)Floor(F);
	}

	static FORCEINLINE float FloorToFloat(FFixed64 F)
	{
		return (float)FloorToDouble(F);
	}

	/**
	 * Converts a float to the nearest integer. Rounds up when the fraction is .5
	 * @param F		Floating point value to convert
	 * @return		The nearest integer to 'F'.
	 */
	static FORCEINLINE int32 RoundToInt32(FFixed32 F)
	{
		return FloorToInt32(F + FixedPoint::Constants::Fixed64::Half);
	}
	static FORCEINLINE int32 RoundToInt32(FFixed64 F)
	{
		return FloorToInt32(F + FixedPoint::Constants::Fixed64::Half);
	}
	static FORCEINLINE int64 RoundToInt64(FFixed64 F)
	{
		return FloorToInt64(F + FixedPoint::Constants::Fixed64::Half);
	}

	static FORCEINLINE int32 RoundToInt(FFixed32 F) { return RoundToInt32(F); }
	static FORCEINLINE int64 RoundToInt(FFixed64 F) { return RoundToInt64(F); }

	/**
	* Ceil, returns a whole number value, rounded up, as FFixed32
	*/
	static FORCEINLINE FFixed32 CeilToFixed32(const FFixed32& inValue)
	{
		return FFixed32::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as FFixed32
	*/
	static FORCEINLINE FFixed64 CeilToFixed64(const FFixed64& inValue)
	{
		return FFixed64::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw64::One - 1) >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as int32
	*/
	static FORCEINLINE int32 CeilToInt(const FFixed32& inValue)
	{
		return (inValue.Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32;
	}

	/**
	* Ceil, returns a whole number value, rounded up, as int64
	*/
	static FORCEINLINE int64 CeilToInt(const FFixed64& inValue)
	{
		return (inValue.Value + FixedPoint::Constants::Raw64::One - 1) >> FixedPoint::Constants::BinaryPoint64;
	}

	/**
	* Ceil, returns a whole number value, rounded up, as float
	*/
	static FORCEINLINE float CeilToFloat(const FFixed32& inValue)
	{
		return (float)FFixed32::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as float
	*/
	static FORCEINLINE float CeilToFloat(const FFixed64& inValue)
	{
		return (float)FFixed64::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw64::One - 1) >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as double
	*/
	static FORCEINLINE double CeilToDouble(const FFixed32& inValue)
	{
		return (double)FFixed32::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32) << FixedPoint::Constants::BinaryPoint32);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as double
	*/
	static FORCEINLINE double CeilToDouble(const FFixed64& inValue)
	{
		return (double)FFixed64::MakeFromRawInt(((inValue.Value + FixedPoint::Constants::Raw64::One - 1) >> FixedPoint::Constants::BinaryPoint64) << FixedPoint::Constants::BinaryPoint64);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as FFixed32
	*/
	static FORCEINLINE FFixed32 TruncToFixed32(const FFixed32& inValue)
	{
		return FFixed32::MakeFromRawInt((inValue.Value / FixedPoint::Constants::Raw32::One) << FixedPoint::Constants::BinaryPoint32);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as FFixed32
	*/
	static FORCEINLINE FFixed64 TruncToFixed64(const FFixed64& inValue)
	{
		return FFixed64::MakeFromRawInt((inValue.Value / FixedPoint::Constants::Raw64::One) << FixedPoint::Constants::BinaryPoint64);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as int32
	*/
	static FORCEINLINE int32 TruncToInt(const FFixed32& inValue)
	{
		return (int32)TruncToFixed32(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as int64
	*/
	static FORCEINLINE int64 TruncToInt(const FFixed64& inValue)
	{
		return (int64)TruncToFixed64(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as float
	*/
	static FORCEINLINE float TruncToFloat(const FFixed32& inValue)
	{
		return (float)TruncToFixed32(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as float
	*/
	static FORCEINLINE float TruncToFloat(const FFixed64& inValue)
	{
		return (float)TruncToFixed64(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as double
	*/
	static FORCEINLINE double TruncToDouble(const FFixed32& inValue)
	{
		return (double)TruncToFixed32(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as double
	*/
	static FORCEINLINE double TruncToDouble(const FFixed64& inValue)
	{
		return (double)TruncToFixed64(inValue);
	}

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

	UE_NODISCARD static FORCEINLINE bool IsNearlyEqual(FFixed32 A, FFixed32 B, FFixed32 ErrorTolerance = FixedPoint::Constants::Fixed32::KindaSmallNumber)
	{
		return Abs(A - B) <= ErrorTolerance;
	}

	UE_NODISCARD static FORCEINLINE bool IsNearlyEqual(FFixed64 A, FFixed64 B, FFixed64 ErrorTolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber)
	{
		return Abs(A - B) <= ErrorTolerance;
	}

	UE_NODISCARD static FORCEINLINE bool IsNearlyZero(FFixed32 Value, FFixed32 ErrorTolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		return Abs(Value) <= ErrorTolerance;
	}

	UE_NODISCARD static FORCEINLINE bool IsNearlyZero(FFixed64 Value, FFixed64 ErrorTolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		return Abs(Value) <= ErrorTolerance;
	}

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
		FFixed64 ret = FixedPoint::Constants::Fixed64::InvTrigMagicOne;
		ret = ret * x;
		ret = ret + FixedPoint::Constants::Fixed64::InvTrigMagicTwo;
		ret = ret * x;
		ret = ret - FixedPoint::Constants::Fixed64::InvTrigMagicThree;
		ret = ret * x;
		ret = ret + FixedPoint::Constants::Fixed64::HalfPi;
		ret = ret * Sqrt(FixedPoint::Constants::Fixed64::One - x);
		ret = ret - FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2) * negate * ret;
		return negate * FixedPoint::Constants::Fixed64::Pi + ret;
	}

	static FFixed64 Asin(FFixed64 x) {
		FFixed64 negate = FFixed64((int64)(x < FixedPoint::Constants::Fixed64::Zero));
		x = Abs(x);
		FFixed64 ret = FixedPoint::Constants::Fixed64::InvTrigMagicOne;
		ret *= x;
		ret += FixedPoint::Constants::Fixed64::InvTrigMagicTwo;
		ret *= x;
		ret -= FixedPoint::Constants::Fixed64::InvTrigMagicThree;
		ret *= x;
		ret += FixedPoint::Constants::Fixed64::HalfPi;
		ret = FixedPoint::Constants::Fixed64::Pi * FixedPoint::Constants::Fixed64::Half - Sqrt(FixedPoint::Constants::Fixed64::One - x) * ret;
		return ret - FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 2) * negate * ret;
	}

	static FFixed64 Atan(FFixed64 X)
	{
		return Atan2(X, FixedPoint::Constants::Fixed64::One);
	}

	static FFixed64 Atan2(FFixed64 Y, FFixed64 X)
	{
		const FFixed64 absX = Abs(X);
		const FFixed64 absY = Abs(Y);
		const bool yAbsBigger = (absY > absX);
		FFixed64 t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
		FFixed64 t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

		if (t0 == FixedPoint::Constants::Fixed64::Zero)
			return FixedPoint::Constants::Fixed64::Zero;

		FFixed64 t3 = t1 / t0;
		FFixed64 t4 = t3 * t3;

		static const FFixed64 c[7] = {
			FixedPoint::Constants::Fixed64::AtanMagicOne,
			FixedPoint::Constants::Fixed64::AtanMagicTwo,
			FixedPoint::Constants::Fixed64::AtanMagicThree,
			FixedPoint::Constants::Fixed64::AtanMagicFour,
			FixedPoint::Constants::Fixed64::AtanMagicFive,
			FixedPoint::Constants::Fixed64::AtanMagicSix,
			FixedPoint::Constants::Fixed64::One
		};

		t0 = c[0];
		t0 = t0 * t4 + c[1];
		t0 = t0 * t4 + c[2];
		t0 = t0 * t4 + c[3];
		t0 = t0 * t4 + c[4];
		t0 = t0 * t4 + c[5];
		t0 = t0 * t4 + c[6];
		t3 = t0 * t3;

		t3 = yAbsBigger ? FixedPoint::Constants::Fixed64::HalfPi - t3 : t3;
		t3 = (X < FixedPoint::Constants::Fixed64::Zero) ? FixedPoint::Constants::Fixed64::Pi - t3 : t3;
		t3 = (Y < FixedPoint::Constants::Fixed64::Zero) ? -t3 : t3;

		return t3;
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
	static void SinCos(FFixed32* outSin, FFixed32* outCos, const FFixed32& inValue);

	static FFixed32 Acos(FFixed32 x)
	{
		//copied from nvidias cg language reference implementation, full of magic numbers, i'm scared too.
		FFixed32 negate = FFixed32((int32)(x < FixedPoint::Constants::Fixed32::Zero));
		x = Abs(x);
		FFixed32 ret = FixedPoint::Constants::Fixed32::InvTrigMagicOne;
		ret = ret * x;
		ret = ret + FixedPoint::Constants::Fixed32::InvTrigMagicTwo;
		ret = ret * x;
		ret = ret - FixedPoint::Constants::Fixed32::InvTrigMagicThree;
		ret = ret * x;
		ret = ret + FixedPoint::Constants::Fixed32::HalfPi;
		ret = ret * Sqrt(FixedPoint::Constants::Fixed32::One - x);
		ret = ret - FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::One * 2) * negate * ret;
		return negate * FixedPoint::Constants::Fixed32::Pi + ret;
	}

	static FFixed32 Asin(FFixed32 x) {
		FFixed32 negate = FFixed32((int32)(x < FixedPoint::Constants::Fixed32::Zero));
		x = Abs(x);
		FFixed32 ret = FixedPoint::Constants::Fixed32::InvTrigMagicOne;
		ret *= x;
		ret += FixedPoint::Constants::Fixed32::InvTrigMagicTwo;
		ret *= x;
		ret -= FixedPoint::Constants::Fixed32::InvTrigMagicThree;
		ret *= x;
		ret += FixedPoint::Constants::Fixed32::HalfPi;
		ret = FixedPoint::Constants::Fixed32::Pi * FixedPoint::Constants::Fixed32::Half - Sqrt(FixedPoint::Constants::Fixed32::One - x) * ret;
		return ret - FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::One * 2) * negate * ret;
	}

	static FFixed32 Atan(FFixed32 X)
	{
		return Atan2(X, FixedPoint::Constants::Fixed32::One);
	}

	static FFixed32 Atan2(FFixed32 Y, FFixed32 X)
	{
		const FFixed32 absX = Abs(X);
		const FFixed32 absY = Abs(Y);
		const bool yAbsBigger = (absY > absX);
		FFixed32 t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
		FFixed32 t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

		if (t0 == FixedPoint::Constants::Fixed32::Zero)
			return FixedPoint::Constants::Fixed32::Zero;

		FFixed32 t3 = t1 / t0;
		FFixed32 t4 = t3 * t3;

		static const FFixed32 c[7] = {
			FixedPoint::Constants::Fixed32::AtanMagicOne,
			FixedPoint::Constants::Fixed32::AtanMagicTwo,
			FixedPoint::Constants::Fixed32::AtanMagicThree,
			FixedPoint::Constants::Fixed32::AtanMagicFour,
			FixedPoint::Constants::Fixed32::AtanMagicFive,
			FixedPoint::Constants::Fixed32::AtanMagicSix,
			FixedPoint::Constants::Fixed32::One
		};

		t0 = c[0];
		t0 = t0 * t4 + c[1];
		t0 = t0 * t4 + c[2];
		t0 = t0 * t4 + c[3];
		t0 = t0 * t4 + c[4];
		t0 = t0 * t4 + c[5];
		t0 = t0 * t4 + c[6];
		t3 = t0 * t3;

		t3 = yAbsBigger ? FixedPoint::Constants::Fixed32::HalfPi - t3 : t3;
		t3 = (X < FixedPoint::Constants::Fixed32::Zero) ? FixedPoint::Constants::Fixed32::Pi - t3 : t3;
		t3 = (Y < FixedPoint::Constants::Fixed32::Zero) ? -t3 : t3;

		return t3;
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

	/**
	 * Returns the fixed-point remainder of X / Y
	 * This is forced to *NOT* inline so that divisions by constant Y does not get optimized in to an inverse scalar multiply,
	 * which is not consistent with the intent nor with the vectorized version.
	 */
	static FORCENOINLINE FFixed64 Fmod(FFixed64 X, FFixed64 Y);
	static FORCENOINLINE FFixed32 Fmod(FFixed32 X, FFixed32 Y);

	static void FmodReportError(FFixed64 X, FFixed64 Y);
	static void FmodReportError(FFixed32 X, FFixed32 Y);

	UE_NODISCARD FORCEINLINE_DEBUGGABLE static FFixedRotator64 LerpRange(const FFixedRotator64& A, const FFixedRotator64& B, FFixed64 Alpha);

	UE_NODISCARD FORCEINLINE_DEBUGGABLE static FFixed64 ClampAngle(FFixed64 AngleDegrees, FFixed64 MinAngleDegrees, FFixed64 MaxAngleDegrees);
	UE_NODISCARD FORCEINLINE_DEBUGGABLE static FFixed32 ClampAngle(FFixed32 AngleDegrees, FFixed32 MinAngleDegrees, FFixed32 MaxAngleDegrees);

	/**
	 * Find the intersection of a line and an offset plane. Assumes that the
	 * line and plane do indeed intersect; you must make sure they're not
	 * parallel before calling.
	 *
	 * @param Point1 the first point defining the line
	 * @param Point2 the second point defining the line
	 * @param PlaneOrigin the origin of the plane
	 * @param PlaneNormal the normal of the plane
	 *
	 * @return The point of intersection between the line and the plane.
	 */
	UE_NODISCARD static FFixedVector64 LinePlaneIntersection(const FFixedVector64& Point1, const FFixedVector64& Point2, const FFixedVector64& PlaneOrigin, const FFixedVector64& PlaneNormal);

	/** Determines whether a line intersects a sphere. */
	UE_NODISCARD static bool LineSphereIntersection(const FFixedVector64& Start, const FFixedVector64& Dir, FFixed64 Length, const FFixedVector64& Origin, FFixed64 Radius);

	/** Return a uniformly distributed random unit length vector = point on the unit sphere surface. */
	UE_NODISCARD static FFixedVector64 VRand();
};
