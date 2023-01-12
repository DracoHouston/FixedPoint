// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"

struct DETERMINISTICFLOAT_API FDeterministicFloatMath : public FMath
{
	/**
	* Degrees To Radians
	*/
	static FORCEINLINE FDeterministicNumber32 DegreesToRadians(const FDeterministicNumber32& inValue)
	{
		return inValue * DeterministicFloat::Constants::Number32::PiOverOneEighty;
	}

	/**
	* Radians To Degrees
	*/
	static FORCEINLINE FDeterministicNumber32 RadiansToDegrees(const FDeterministicNumber32& inValue)
	{
		return inValue * DeterministicFloat::Constants::Number32::OneEightyOverPi;
	}

	/**
	* Degrees To Radians
	*/
	static FORCEINLINE FDeterministicNumber64 DegreesToRadians(const FDeterministicNumber64& inValue)
	{
		return inValue * DeterministicFloat::Constants::Number64::PiOverOneEighty;
	}

	/**
	* Radians To Degrees
	*/
	static FORCEINLINE FDeterministicNumber64 RadiansToDegrees(const FDeterministicNumber64& inValue)
	{
		return inValue * DeterministicFloat::Constants::Number64::OneEightyOverPi;
	}

	/**
	* Floor, returns a whole number value, rounded down, as FDeterministicNumber64
	*/
	static FDeterministicNumber64 FloorToNumber64(const FDeterministicNumber64& inValue)
	{
		return FDeterministicNumber64::Make(FMath::FloorToDouble(inValue.Value));
	}

	/**
	* Floor, returns a whole number value, rounded down, as FDeterministicNumber32
	*/
	static FDeterministicNumber32 FloorToNumber32(const FDeterministicNumber32& inValue)
	{
		return FDeterministicNumber32::Make(FMath::FloorToFloat(inValue.Value));
	}

	/**
	* Floor, returns a whole number value, rounded down, as FDeterministicNumber64
	*/
	static FDeterministicNumber64 Floor(const FDeterministicNumber64& inValue)
	{
		return FloorToNumber64(inValue);
	}

	/**
	* Floor, returns a whole number value, rounded down, as FDeterministicNumber32
	*/
	static FDeterministicNumber32 Floor(const FDeterministicNumber32& inValue)
	{
		return FloorToNumber32(inValue);
	}

	/**
	 * Converts a float to a nearest less or equal integer.
	 * @param F		Floating point value to convert
	 * @return		An integer less or equal to 'F'.
	 */
	static FORCEINLINE int32 FloorToInt32(FDeterministicNumber32 F)
	{
		return (int32)FloorToNumber32(F);
	}
	static FORCEINLINE int32 FloorToInt32(FDeterministicNumber64 F)
	{
		return (int32)FloorToNumber64(F);
	}
	static FORCEINLINE int64 FloorToInt64(FDeterministicNumber64 F)
	{
		return (int64)FloorToNumber64(F);
	}

	static FORCEINLINE int32 FloorToInt(FDeterministicNumber32 F) { return FloorToInt32(F); }
	static FORCEINLINE int64 FloorToInt(FDeterministicNumber64 F) { return FloorToInt64(F); }


	/**
	* Converts a float to the nearest less or equal integer.
	* @param F		Floating point value to convert
	* @return		An integer less or equal to 'F'.
	*/
	static FORCEINLINE float FloorToFloat(FDeterministicNumber32 F)
	{
		return (float)FloorToNumber32(F);
	}

	/**
	* Converts a double to a less or equal integer.
	* @param F		Floating point value to convert
	* @return		The nearest integer value to 'F'.
	*/
	static FORCEINLINE double FloorToDouble(FDeterministicNumber64 F)
	{
		return (double)FloorToNumber64(F);
	}

	static FORCEINLINE float FloorToFloat(FDeterministicNumber64 F)
	{
		return (float)FloorToDouble(F);
	}

	static FORCEINLINE int32 RoundToNumber32(FDeterministicNumber32 F)
	{
		return FDeterministicNumber32::Make(FMath::RoundToFloat(F.Value));
	}
	static FORCEINLINE int32 RoundToNumber64(FDeterministicNumber64 F)
	{
		return FDeterministicNumber64::Make(FMath::RoundToDouble(F.Value));
	}

	static FORCEINLINE int32 RoundToFloat(FDeterministicNumber32 F)
	{
		return (float)RoundToNumber32(F);
	}
	static FORCEINLINE int32 RoundToDouble(FDeterministicNumber64 F)
	{
		return (double)RoundToNumber64(F);
	}
	static FORCEINLINE int32 RoundToFloat(FDeterministicNumber64 F)
	{
		return (float)RoundToDouble(F);
	}

	/**
	 * Converts a float to the nearest integer. Rounds up when the fraction is .5
	 * @param F		Floating point value to convert
	 * @return		The nearest integer to 'F'.
	 */
	static FORCEINLINE int32 RoundToInt32(FDeterministicNumber32 F)
	{
		return (float)RoundToNumber32(F);
	}
	static FORCEINLINE int32 RoundToInt32(FDeterministicNumber64 F)
	{
		return (int32)RoundToNumber64(F);
	}
	static FORCEINLINE int64 RoundToInt64(FDeterministicNumber64 F)
	{
		return (int64)RoundToNumber64(F);
	}

	static FORCEINLINE int32 RoundToInt(FDeterministicNumber32 F) { return RoundToInt32(F); }
	static FORCEINLINE int64 RoundToInt(FDeterministicNumber64 F) { return RoundToInt64(F); }

	/**
	* Ceil, returns a whole number value, rounded up, as FDeterministicNumber32
	*/
	static FORCEINLINE FDeterministicNumber32 CeilToNumber32(const FDeterministicNumber32& inValue)
	{
		return FDeterministicNumber32::Make(FMath::CeilToFloat(inValue.Value));
	}

	/**
	* Ceil, returns a whole number value, rounded up, as FDeterministicNumber32
	*/
	static FORCEINLINE FDeterministicNumber64 CeilToNumber64(const FDeterministicNumber64& inValue)
	{
		return FDeterministicNumber64::Make(FMath::CeilToDouble(inValue.Value));
	}

	/**
	* Ceil, returns a whole number value, rounded up, as int32
	*/
	static FORCEINLINE int32 CeilToInt(const FDeterministicNumber32& inValue)
	{
		return (int32)CeilToNumber32(inValue);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as int64
	*/
	static FORCEINLINE int64 CeilToInt(const FDeterministicNumber64& inValue)
	{
		return (int64)CeilToNumber64(inValue);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as float
	*/
	static FORCEINLINE float CeilToFloat(const FDeterministicNumber32& inValue)
	{
		return (float)CeilToNumber32(inValue);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as float
	*/
	static FORCEINLINE float CeilToFloat(const FDeterministicNumber64& inValue)
	{
		return (float)CeilToNumber64(inValue);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as double
	*/
	static FORCEINLINE double CeilToDouble(const FDeterministicNumber32& inValue)
	{
		return (double)CeilToNumber32(inValue);
	}

	/**
	* Ceil, returns a whole number value, rounded up, as double
	*/
	static FORCEINLINE double CeilToDouble(const FDeterministicNumber64& inValue)
	{
		return (double)CeilToNumber64(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as FDeterministicNumber32
	*/
	static FORCEINLINE FDeterministicNumber32 TruncToNumber32(const FDeterministicNumber32& inValue)
	{
		return FDeterministicNumber32::Make(FMath::TruncToFloat(inValue.Value));
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as FDeterministicNumber32
	*/
	static FORCEINLINE FDeterministicNumber64 TruncToNumber64(const FDeterministicNumber64& inValue)
	{
		return FDeterministicNumber32::Make(FMath::TruncToDouble(inValue.Value));
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as int32
	*/
	static FORCEINLINE int32 TruncToInt(const FDeterministicNumber32& inValue)
	{
		return (int32)TruncToNumber32(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as int64
	*/
	static FORCEINLINE int64 TruncToInt(const FDeterministicNumber64& inValue)
	{
		return (int64)TruncToNumber64(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as float
	*/
	static FORCEINLINE float TruncToFloat(const FDeterministicNumber32& inValue)
	{
		return (float)TruncToNumber32(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as float
	*/
	static FORCEINLINE float TruncToFloat(const FDeterministicNumber64& inValue)
	{
		return (float)TruncToNumber64(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as double
	*/
	static FORCEINLINE double TruncToDouble(const FDeterministicNumber32& inValue)
	{
		return (double)TruncToNumber32(inValue);
	}

	/**
	* Trunc, returns a whole number value, rounded towards 0, as double
	*/
	static FORCEINLINE double TruncToDouble(const FDeterministicNumber64& inValue)
	{
		return (double)TruncToNumber64(inValue);
	}

	/**
	* Is Equal, will find if 2 FDeterministicNumber64s are within supplied tolerance
	*/
	static bool IsEqual(const FDeterministicNumber64& A, const FDeterministicNumber64& B, const FDeterministicNumber64& inTolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber);

	/**
	* Is Equal, will find if 2 FDeterministicNumber32s are within supplied tolerance
	*/
	static bool IsEqual(const FDeterministicNumber32& A, const FDeterministicNumber32& B, const FDeterministicNumber32& inTolerance = DeterministicFloat::Constants::Number32::KindaSmallNumber);

	UE_NODISCARD static FORCEINLINE bool IsNearlyEqual(FDeterministicNumber32 A, FDeterministicNumber32 B, FDeterministicNumber32 ErrorTolerance = DeterministicFloat::Constants::Number32::KindaSmallNumber)
	{
		return Abs(A - B) <= ErrorTolerance;
	}

	UE_NODISCARD static FORCEINLINE bool IsNearlyEqual(FDeterministicNumber64 A, FDeterministicNumber64 B, FDeterministicNumber64 ErrorTolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber)
	{
		return Abs(A - B) <= ErrorTolerance;
	}

	UE_NODISCARD static FORCEINLINE bool IsNearlyZero(FDeterministicNumber32 Value, FDeterministicNumber32 ErrorTolerance = DeterministicFloat::Constants::Number64::SmallNumber)
	{
		return Abs(Value) <= ErrorTolerance;
	}

	UE_NODISCARD static FORCEINLINE bool IsNearlyZero(FDeterministicNumber64 Value, FDeterministicNumber64 ErrorTolerance = DeterministicFloat::Constants::Number64::SmallNumber)
	{
		return Abs(Value) <= ErrorTolerance;
	}

	/**
	* Square Root
	*/
	static FDeterministicNumber32 Sqrt(const FDeterministicNumber32& inValue);

	static FDeterministicNumber32 InvSqrt(const FDeterministicNumber32& inValue);
	/**
	* Square Root
	*/
	static FDeterministicNumber64 Sqrt(const FDeterministicNumber64& inValue);

	static FDeterministicNumber64 InvSqrt(const FDeterministicNumber64& inValue);

	/**
	* Sin, returns the sine of a FDeterministicNumber64 angle in radians
	*/
	static FDeterministicNumber64 Sin(const FDeterministicNumber64& inValue);

	/**
	* Cos, returns the cosine of a FDeterministicNumber64 angle in radians
	*/
	static FDeterministicNumber64 Cos(const FDeterministicNumber64& inValue);

	/**
	* Tan, returns the tangent of a FDeterministicNumber64 angle in radians
	*/
	static FDeterministicNumber64 Tan(const FDeterministicNumber64& inValue);

	/**
	* SinAndCos, gets the sine of a FDeterministicNumber64 angle in radians, and its cosine, and returns both
	* Note: this avoids calling FDeterministicNumber64::Sin twice over calling FDeterministicNumber64::Sin then FDeterministicNumber64::Cos, which uses this!
	*/
	static void SinCos(FDeterministicNumber64* outSin, FDeterministicNumber64* outCos, const FDeterministicNumber64& inValue);

	static FDeterministicNumber64 Acos(FDeterministicNumber64 x)
	{
		//copied from nvidias cg language reference implementation, full of magic numbers, i'm scared too.
		FDeterministicNumber64 negate = FDeterministicNumber64((int64)(x < DeterministicFloat::Constants::Number64::Zero));
		x = Abs(x);
		FDeterministicNumber64 ret = DeterministicFloat::Constants::Number64::InvTrigMagicOne;
		ret = ret * x;
		ret = ret + DeterministicFloat::Constants::Number64::InvTrigMagicTwo;
		ret = ret * x;
		ret = ret - DeterministicFloat::Constants::Number64::InvTrigMagicThree;
		ret = ret * x;
		ret = ret + DeterministicFloat::Constants::Number64::HalfPi;
		ret = ret * Sqrt(DeterministicFloat::Constants::Number64::One - x);
		ret = ret - FDeterministicNumber64::Make(2.0) * negate * ret;
		return negate * DeterministicFloat::Constants::Number64::Pi + ret;
	}

	static FDeterministicNumber64 Asin(FDeterministicNumber64 x) {
		FDeterministicNumber64 negate = FDeterministicNumber64((int64)(x < DeterministicFloat::Constants::Number64::Zero));
		x = Abs(x);
		FDeterministicNumber64 ret = DeterministicFloat::Constants::Number64::InvTrigMagicOne;
		ret *= x;
		ret += DeterministicFloat::Constants::Number64::InvTrigMagicTwo;
		ret *= x;
		ret -= DeterministicFloat::Constants::Number64::InvTrigMagicThree;
		ret *= x;
		ret += DeterministicFloat::Constants::Number64::HalfPi;
		ret = DeterministicFloat::Constants::Number64::Pi * DeterministicFloat::Constants::Number64::Half - Sqrt(DeterministicFloat::Constants::Number64::One - x) * ret;
		return ret - FDeterministicNumber64::Make(2.0) * negate * ret;
	}

	static FDeterministicNumber64 Atan(FDeterministicNumber64 X)
	{
		return Atan2(X, DeterministicFloat::Constants::Number64::One);
	}

	static FDeterministicNumber64 Atan2(FDeterministicNumber64 Y, FDeterministicNumber64 X)
	{
		const FDeterministicNumber64 absX = Abs(X);
		const FDeterministicNumber64 absY = Abs(Y);
		const bool yAbsBigger = (absY > absX);
		FDeterministicNumber64 t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
		FDeterministicNumber64 t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

		if (t0 == DeterministicFloat::Constants::Number64::Zero)
			return DeterministicFloat::Constants::Number64::Zero;

		FDeterministicNumber64 t3 = t1 / t0;
		FDeterministicNumber64 t4 = t3 * t3;

		static const FDeterministicNumber64 c[7] = {
			DeterministicFloat::Constants::Number64::AtanMagicOne,
			DeterministicFloat::Constants::Number64::AtanMagicTwo,
			DeterministicFloat::Constants::Number64::AtanMagicThree,
			DeterministicFloat::Constants::Number64::AtanMagicFour,
			DeterministicFloat::Constants::Number64::AtanMagicFive,
			DeterministicFloat::Constants::Number64::AtanMagicSix,
			DeterministicFloat::Constants::Number64::One
		};

		t0 = c[0];
		t0 = t0 * t4 + c[1];
		t0 = t0 * t4 + c[2];
		t0 = t0 * t4 + c[3];
		t0 = t0 * t4 + c[4];
		t0 = t0 * t4 + c[5];
		t0 = t0 * t4 + c[6];
		t3 = t0 * t3;

		t3 = yAbsBigger ? DeterministicFloat::Constants::Number64::HalfPi - t3 : t3;
		t3 = (X < DeterministicFloat::Constants::Number64::Zero) ? DeterministicFloat::Constants::Number64::Pi - t3 : t3;
		t3 = (Y < DeterministicFloat::Constants::Number64::Zero) ? -t3 : t3;

		return t3;
	}

	/**
	* Sin, returns the sine of a FDeterministicNumber32 angle in radians
	*/
	static FDeterministicNumber32 Sin(const FDeterministicNumber32& inValue);

	/**
	* Cos, returns the cosine of a FDeterministicNumber32 angle in radians
	*/
	static FDeterministicNumber32 Cos(const FDeterministicNumber32& inValue);

	/**
	* Tan, returns the tangent of a FDeterministicNumber32 angle in radians
	*/
	static FDeterministicNumber32 Tan(const FDeterministicNumber32& inValue);

	/**
	* SinAndCos, gets the sine of a FDeterministicNumber32 angle in radians, and its cosine, and returns both
	* Note: this avoids calling FDeterministicNumber32::Sin twice over calling FDeterministicNumber32::Sin then FDeterministicNumber32::Cos, which uses this!
	*/
	static void SinCos(FDeterministicNumber32* outSin, FDeterministicNumber32* outCos, const FDeterministicNumber32& inValue);

	static FDeterministicNumber32 Acos(FDeterministicNumber32 x)
	{
		//copied from nvidias cg language reference implementation, full of magic numbers, i'm scared too.
		FDeterministicNumber32 negate = FDeterministicNumber32((int32)(x < DeterministicFloat::Constants::Number32::Zero));
		x = Abs(x);
		FDeterministicNumber32 ret = DeterministicFloat::Constants::Number32::InvTrigMagicOne;
		ret = ret * x;
		ret = ret + DeterministicFloat::Constants::Number32::InvTrigMagicTwo;
		ret = ret * x;
		ret = ret - DeterministicFloat::Constants::Number32::InvTrigMagicThree;
		ret = ret * x;
		ret = ret + DeterministicFloat::Constants::Number32::HalfPi;
		ret = ret * Sqrt(DeterministicFloat::Constants::Number32::One - x);
		ret = ret - FDeterministicNumber32::Make(2.0) * negate * ret;
		return negate * DeterministicFloat::Constants::Number32::Pi + ret;
	}

	static FDeterministicNumber32 Asin(FDeterministicNumber32 x) {
		FDeterministicNumber32 negate = FDeterministicNumber32((int32)(x < DeterministicFloat::Constants::Number32::Zero));
		x = Abs(x);
		FDeterministicNumber32 ret = DeterministicFloat::Constants::Number32::InvTrigMagicOne;
		ret *= x;
		ret += DeterministicFloat::Constants::Number32::InvTrigMagicTwo;
		ret *= x;
		ret -= DeterministicFloat::Constants::Number32::InvTrigMagicThree;
		ret *= x;
		ret += DeterministicFloat::Constants::Number32::HalfPi;
		ret = DeterministicFloat::Constants::Number32::Pi * DeterministicFloat::Constants::Number32::Half - Sqrt(DeterministicFloat::Constants::Number32::One - x) * ret;
		return ret - FDeterministicNumber32::Make(2.0) * negate * ret;
	}

	static FDeterministicNumber32 Atan(FDeterministicNumber32 X)
	{
		return Atan2(X, DeterministicFloat::Constants::Number32::One);
	}

	static FDeterministicNumber32 Atan2(FDeterministicNumber32 Y, FDeterministicNumber32 X)
	{
		const FDeterministicNumber32 absX = Abs(X);
		const FDeterministicNumber32 absY = Abs(Y);
		const bool yAbsBigger = (absY > absX);
		FDeterministicNumber32 t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
		FDeterministicNumber32 t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

		if (t0 == DeterministicFloat::Constants::Number32::Zero)
			return DeterministicFloat::Constants::Number32::Zero;

		FDeterministicNumber32 t3 = t1 / t0;
		FDeterministicNumber32 t4 = t3 * t3;

		static const FDeterministicNumber32 c[7] = {
			DeterministicFloat::Constants::Number32::AtanMagicOne,
			DeterministicFloat::Constants::Number32::AtanMagicTwo,
			DeterministicFloat::Constants::Number32::AtanMagicThree,
			DeterministicFloat::Constants::Number32::AtanMagicFour,
			DeterministicFloat::Constants::Number32::AtanMagicFive,
			DeterministicFloat::Constants::Number32::AtanMagicSix,
			DeterministicFloat::Constants::Number32::One
		};

		t0 = c[0];
		t0 = t0 * t4 + c[1];
		t0 = t0 * t4 + c[2];
		t0 = t0 * t4 + c[3];
		t0 = t0 * t4 + c[4];
		t0 = t0 * t4 + c[5];
		t0 = t0 * t4 + c[6];
		t3 = t0 * t3;

		t3 = yAbsBigger ? DeterministicFloat::Constants::Number32::HalfPi - t3 : t3;
		t3 = (X < DeterministicFloat::Constants::Number32::Zero) ? DeterministicFloat::Constants::Number32::Pi - t3 : t3;
		t3 = (Y < DeterministicFloat::Constants::Number32::Zero) ? -t3 : t3;

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
	static constexpr FORCEINLINE FDeterministicNumber64 FloatSelect(FDeterministicNumber64 Comparand, FDeterministicNumber64 ValueGEZero, FDeterministicNumber64 ValueLTZero)
	{
		return Comparand >= DeterministicFloat::Constants::Number64::Zero ? ValueGEZero : ValueLTZero;
	}
	static constexpr FORCEINLINE FDeterministicNumber32 FloatSelect(FDeterministicNumber32 Comparand, FDeterministicNumber32 ValueGEZero, FDeterministicNumber32 ValueLTZero)
	{
		return Comparand >= DeterministicFloat::Constants::Number32::Zero ? ValueGEZero : ValueLTZero;
	}

	UE_NODISCARD static constexpr FORCEINLINE FDeterministicNumber64 GridSnap(FDeterministicNumber64 Location, FDeterministicNumber64 Grid)
	{
		return (Grid == DeterministicFloat::Constants::Number64::Zero) ? Location : (Floor((Location + (Grid / FDeterministicNumber64::Make(2.0))) / Grid) * Grid);
	}

	UE_NODISCARD static constexpr FORCEINLINE FDeterministicNumber32 GridSnap(FDeterministicNumber32 Location, FDeterministicNumber32 Grid)
	{
		return (Grid == DeterministicFloat::Constants::Number32::Zero) ? Location : (Floor((Location + (Grid / FDeterministicNumber32::Make(2.0))) / Grid) * Grid);
	}

	UE_NODISCARD static constexpr FDeterministicNumber32 UnwindDegrees(FDeterministicNumber32 A)
	{
		while (A > DeterministicFloat::Constants::Number32::OneEighty)
		{
			A -= DeterministicFloat::Constants::Number32::ThreeSixty;
		}

		while (A < -DeterministicFloat::Constants::Number32::OneEighty)
		{
			A += DeterministicFloat::Constants::Number32::ThreeSixty;
		}

		return A;
	}

	UE_NODISCARD static constexpr FDeterministicNumber64 UnwindDegrees(FDeterministicNumber64 A)
	{
		while (A > DeterministicFloat::Constants::Number64::OneEighty)
		{
			A -= DeterministicFloat::Constants::Number64::ThreeSixty;
		}

		while (A < -DeterministicFloat::Constants::Number64::OneEighty)
		{
			A += DeterministicFloat::Constants::Number64::ThreeSixty;
		}

		return A;
	}

	UE_NODISCARD static constexpr FDeterministicNumber64 UnwindRadians(FDeterministicNumber64 A)
	{
		while (A > DeterministicFloat::Constants::Number64::Pi)
		{
			A -= DeterministicFloat::Constants::Number64::TwoPi;
		}

		while (A < -DeterministicFloat::Constants::Number64::Pi)
		{
			A += DeterministicFloat::Constants::Number64::TwoPi;
		}

		return A;
	}

	UE_NODISCARD static constexpr FDeterministicNumber32 UnwindRadians(FDeterministicNumber32 A)
	{
		while (A > DeterministicFloat::Constants::Number32::Pi)
		{
			A -= DeterministicFloat::Constants::Number32::TwoPi;
		}

		while (A < -DeterministicFloat::Constants::Number32::Pi)
		{
			A += DeterministicFloat::Constants::Number32::TwoPi;
		}

		return A;
	}

	FORCEINLINE static int32 GetQuadrantRadians(const FDeterministicNumber64& inValue)
	{
		FDeterministicNumber64 val = UnwindRadians(inValue);

		val = val < DeterministicFloat::Constants::Number64::Zero ? val + DeterministicFloat::Constants::Number64::TwoPi : val;

		if ((inValue > DeterministicFloat::Constants::Number64::Zero) && (val == DeterministicFloat::Constants::Number64::HalfPi))
		{
			return 0;
		}
		else if ((inValue > DeterministicFloat::Constants::Number64::Zero) && (val == DeterministicFloat::Constants::Number64::Pi))
		{
			return 1;
		}
		
		val /= DeterministicFloat::Constants::Number64::HalfPi;
		return (int32)val;
	}

	FORCEINLINE static int32 GetQuadrantRadians(const FDeterministicNumber32& inValue)
	{
		/*inValue = UnwindRadians(inValue);
		inValue = inValue < DeterministicFloat::Constants::Number32::Zero ? -inValue : inValue;
		inValue /= DeterministicFloat::Constants::Number32::HalfPi;
		return (int32)inValue;*/
		FDeterministicNumber32 val = UnwindRadians(inValue);

		val = val < DeterministicFloat::Constants::Number32::Zero ? val + DeterministicFloat::Constants::Number32::TwoPi : val;

		if ((inValue > DeterministicFloat::Constants::Number32::Zero) && (val == DeterministicFloat::Constants::Number32::HalfPi))
		{
			return 0;
		}
		else if ((inValue > DeterministicFloat::Constants::Number32::Zero) && (val == DeterministicFloat::Constants::Number32::Pi))
		{
			return 1;
		}

		val /= DeterministicFloat::Constants::Number32::HalfPi;
		return (int32)val;
	}

	static FORCEINLINE bool IsNaN(FDeterministicNumber32 A) { return false; }//these all return false because fixed point numbers cant nan or inf, just here for compatibility
	static FORCEINLINE bool IsNaN(FDeterministicNumber64 A) { return false; }
	static FORCEINLINE bool IsFinite(FDeterministicNumber32 A) { return false; }
	static FORCEINLINE bool IsFinite(FDeterministicNumber64 A) { return false; }

	/**
	 * Returns the fixed-point remainder of X / Y
	 * This is forced to *NOT* inline so that divisions by constant Y does not get optimized in to an inverse scalar multiply,
	 * which is not consistent with the intent nor with the vectorized version.
	 */
	static FORCENOINLINE FDeterministicNumber64 Fmod(FDeterministicNumber64 X, FDeterministicNumber64 Y);
	static FORCENOINLINE FDeterministicNumber32 Fmod(FDeterministicNumber32 X, FDeterministicNumber32 Y);

	static void FmodReportError(FDeterministicNumber64 X, FDeterministicNumber64 Y);
	static void FmodReportError(FDeterministicNumber32 X, FDeterministicNumber32 Y);

	UE_NODISCARD FORCEINLINE_DEBUGGABLE static FDeterministicRotator64 LerpRange(const FDeterministicRotator64& A, const FDeterministicRotator64& B, FDeterministicNumber64 Alpha);

	UE_NODISCARD FORCEINLINE_DEBUGGABLE static FDeterministicNumber64 ClampAngle(FDeterministicNumber64 AngleDegrees, FDeterministicNumber64 MinAngleDegrees, FDeterministicNumber64 MaxAngleDegrees);
	UE_NODISCARD FORCEINLINE_DEBUGGABLE static FDeterministicNumber32 ClampAngle(FDeterministicNumber32 AngleDegrees, FDeterministicNumber32 MinAngleDegrees, FDeterministicNumber32 MaxAngleDegrees);

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
	UE_NODISCARD static FDeterministicVector64 LinePlaneIntersection(const FDeterministicVector64& Point1, const FDeterministicVector64& Point2, const FDeterministicVector64& PlaneOrigin, const FDeterministicVector64& PlaneNormal);

	/** Determines whether a line intersects a sphere. */
	UE_NODISCARD static bool LineSphereIntersection(const FDeterministicVector64& Start, const FDeterministicVector64& Dir, FDeterministicNumber64 Length, const FDeterministicVector64& Origin, FDeterministicNumber64 Radius);

	/** Return a uniformly distributed random unit length vector = point on the unit sphere surface. */
	UE_NODISCARD static FDeterministicVector64 VRand();
};
