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
	static FORCEINLINE FDeterministicNumber32 DegreesToRadians(const FDeterministicNumber32& inValue);

	/**
	* Radians To Degrees
	*/
	static FORCEINLINE FDeterministicNumber32 RadiansToDegrees(const FDeterministicNumber32& inValue);

	/**
	* Degrees To Radians
	*/
	static FORCEINLINE FDeterministicNumber64 DegreesToRadians(const FDeterministicNumber64& inValue);

	/**
	* Radians To Degrees
	*/
	static FORCEINLINE FDeterministicNumber64 RadiansToDegrees(const FDeterministicNumber64& inValue);

	/**
	* Floor, returns a whole number value, rounded down, as FDeterministicNumber64
	*/
	FORCEINLINE static FDeterministicNumber64 FloorToNumber64(const FDeterministicNumber64& inValue);

	/**
	* Floor, returns a whole number value, rounded down, as FDeterministicNumber32
	*/
	FORCEINLINE static FDeterministicNumber32 FloorToNumber32(const FDeterministicNumber32& inValue);

	/**
	* Floor, returns a whole number value, rounded down, as FDeterministicNumber64
	*/
	FORCEINLINE static FDeterministicNumber64 Floor(const FDeterministicNumber64& inValue);

	/**
	* Floor, returns a whole number value, rounded down, as FDeterministicNumber32
	*/
	FORCEINLINE static FDeterministicNumber32 Floor(const FDeterministicNumber32& inValue);

	/**
	 * Converts a float to a nearest less or equal integer.
	 * @param F		Floating point value to convert
	 * @return		An integer less or equal to 'F'.
	 */
	static FORCEINLINE int32 FloorToInt32(FDeterministicNumber32 F);
	static FORCEINLINE int32 FloorToInt32(FDeterministicNumber64 F);
	static FORCEINLINE int64 FloorToInt64(FDeterministicNumber64 F);

	static FORCEINLINE int32 FloorToInt(FDeterministicNumber32 F);
	static FORCEINLINE int64 FloorToInt(FDeterministicNumber64 F);


	/**
	* Converts a float to the nearest less or equal integer.
	* @param F		Floating point value to convert
	* @return		An integer less or equal to 'F'.
	*/
	static FORCEINLINE float FloorToFloat(FDeterministicNumber32 F);

	/**
	* Converts a double to a less or equal integer.
	* @param F		Floating point value to convert
	* @return		The nearest integer value to 'F'.
	*/
	static FORCEINLINE double FloorToDouble(FDeterministicNumber64 F);

	static FORCEINLINE float FloorToFloat(FDeterministicNumber64 F);

	static FORCEINLINE int32 RoundToNumber32(FDeterministicNumber32 F);
	static FORCEINLINE int32 RoundToNumber64(FDeterministicNumber64 F);
	static FORCEINLINE int32 RoundToFloat(FDeterministicNumber32 F);
	static FORCEINLINE int32 RoundToDouble(FDeterministicNumber64 F);
	static FORCEINLINE int32 RoundToFloat(FDeterministicNumber64 F);

	/**
	 * Converts a float to the nearest integer. Rounds up when the fraction is .5
	 * @param F		Floating point value to convert
	 * @return		The nearest integer to 'F'.
	 */
	static FORCEINLINE int32 RoundToInt32(FDeterministicNumber32 F);
	static FORCEINLINE int32 RoundToInt32(FDeterministicNumber64 F);
	static FORCEINLINE int64 RoundToInt64(FDeterministicNumber64 F);
	static FORCEINLINE int32 RoundToInt(FDeterministicNumber32 F);
	static FORCEINLINE int64 RoundToInt(FDeterministicNumber64 F);

	/**
	* Ceil, returns a whole number value, rounded up, as FDeterministicNumber32
	*/
	static FORCEINLINE FDeterministicNumber32 CeilToNumber32(const FDeterministicNumber32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as FDeterministicNumber32
	*/
	static FORCEINLINE FDeterministicNumber64 CeilToNumber64(const FDeterministicNumber64& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as int32
	*/
	static FORCEINLINE int32 CeilToInt(const FDeterministicNumber32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as int64
	*/
	static FORCEINLINE int64 CeilToInt(const FDeterministicNumber64& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as float
	*/
	static FORCEINLINE float CeilToFloat(const FDeterministicNumber32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as float
	*/
	static FORCEINLINE float CeilToFloat(const FDeterministicNumber64& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as double
	*/
	static FORCEINLINE double CeilToDouble(const FDeterministicNumber32& inValue);

	/**
	* Ceil, returns a whole number value, rounded up, as double
	*/
	static FORCEINLINE double CeilToDouble(const FDeterministicNumber64& inValue);

	/**
	* Trunc, returns a whole number value, rounded towards 0, as FDeterministicNumber32
	*/
	static FORCEINLINE FDeterministicNumber32 TruncToNumber32(const FDeterministicNumber32& inValue);

	/**
	* Trunc, returns a whole number value, rounded towards 0, as FDeterministicNumber32
	*/
	static FORCEINLINE FDeterministicNumber64 TruncToNumber64(const FDeterministicNumber64& inValue);

	/**
	* Trunc, returns a whole number value, rounded towards 0, as int32
	*/
	static FORCEINLINE int32 TruncToInt(const FDeterministicNumber32& inValue);

	/**
	* Trunc, returns a whole number value, rounded towards 0, as int64
	*/
	static FORCEINLINE int64 TruncToInt(const FDeterministicNumber64& inValue);

	/**
	* Trunc, returns a whole number value, rounded towards 0, as float
	*/
	static FORCEINLINE float TruncToFloat(const FDeterministicNumber32& inValue);

	/**
	* Trunc, returns a whole number value, rounded towards 0, as float
	*/
	static FORCEINLINE float TruncToFloat(const FDeterministicNumber64& inValue);

	/**
	* Trunc, returns a whole number value, rounded towards 0, as double
	*/
	static FORCEINLINE double TruncToDouble(const FDeterministicNumber32& inValue);

	/**
	* Trunc, returns a whole number value, rounded towards 0, as double
	*/
	static FORCEINLINE double TruncToDouble(const FDeterministicNumber64& inValue);

	/**
	* Is Equal, will find if 2 FDeterministicNumber64s are within supplied tolerance
	*/
	FORCEINLINE static bool IsEqual(const FDeterministicNumber64& A, const FDeterministicNumber64& B, const FDeterministicNumber64& inTolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber);

	/**
	* Is Equal, will find if 2 FDeterministicNumber32s are within supplied tolerance
	*/
	FORCEINLINE static bool IsEqual(const FDeterministicNumber32& A, const FDeterministicNumber32& B, const FDeterministicNumber32& inTolerance = DeterministicFloat::Constants::Number32::KindaSmallNumber);

	UE_NODISCARD static FORCEINLINE bool IsNearlyEqual(FDeterministicNumber32 A, FDeterministicNumber32 B, FDeterministicNumber32 ErrorTolerance = DeterministicFloat::Constants::Number32::KindaSmallNumber);

	UE_NODISCARD static FORCEINLINE bool IsNearlyEqual(FDeterministicNumber64 A, FDeterministicNumber64 B, FDeterministicNumber64 ErrorTolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber);

	UE_NODISCARD static FORCEINLINE bool IsNearlyZero(FDeterministicNumber32 Value, FDeterministicNumber32 ErrorTolerance = DeterministicFloat::Constants::Number64::SmallNumber);

	UE_NODISCARD static FORCEINLINE bool IsNearlyZero(FDeterministicNumber64 Value, FDeterministicNumber64 ErrorTolerance = DeterministicFloat::Constants::Number64::SmallNumber);

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

	FORCEINLINE static FDeterministicNumber64 Acos(FDeterministicNumber64 x);

	FORCEINLINE static FDeterministicNumber64 Asin(FDeterministicNumber64 x);

	FORCEINLINE static FDeterministicNumber64 Atan(FDeterministicNumber64 X);

	FORCEINLINE static FDeterministicNumber64 Atan2(FDeterministicNumber64 Y, FDeterministicNumber64 X);

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

	FORCEINLINE static FDeterministicNumber32 Acos(FDeterministicNumber32 x);

	FORCEINLINE static FDeterministicNumber32 Asin(FDeterministicNumber32 x);

	FORCEINLINE static FDeterministicNumber32 Atan(FDeterministicNumber32 X);

	FORCEINLINE static FDeterministicNumber32 Atan2(FDeterministicNumber32 Y, FDeterministicNumber32 X);

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
	static constexpr FORCEINLINE FDeterministicNumber64 FloatSelect(FDeterministicNumber64 Comparand, FDeterministicNumber64 ValueGEZero, FDeterministicNumber64 ValueLTZero);
	static constexpr FORCEINLINE FDeterministicNumber32 FloatSelect(FDeterministicNumber32 Comparand, FDeterministicNumber32 ValueGEZero, FDeterministicNumber32 ValueLTZero);

	UE_NODISCARD static constexpr FORCEINLINE FDeterministicNumber64 GridSnap(FDeterministicNumber64 Location, FDeterministicNumber64 Grid);

	UE_NODISCARD static constexpr FORCEINLINE FDeterministicNumber32 GridSnap(FDeterministicNumber32 Location, FDeterministicNumber32 Grid);

	UE_NODISCARD static constexpr FDeterministicNumber32 UnwindDegrees(FDeterministicNumber32 A);

	UE_NODISCARD static constexpr FDeterministicNumber64 UnwindDegrees(FDeterministicNumber64 A);

	UE_NODISCARD static constexpr FDeterministicNumber64 UnwindRadians(FDeterministicNumber64 A);

	UE_NODISCARD static constexpr FDeterministicNumber32 UnwindRadians(FDeterministicNumber32 A);

	FORCEINLINE static int32 GetQuadrantRadians(const FDeterministicNumber64& inValue);

	FORCEINLINE static int32 GetQuadrantRadians(const FDeterministicNumber32& inValue);

	static FORCEINLINE bool IsNaN(FDeterministicNumber32 A);
	static FORCEINLINE bool IsNaN(FDeterministicNumber64 A);
	static FORCEINLINE bool IsFinite(FDeterministicNumber32 A);
	static FORCEINLINE bool IsFinite(FDeterministicNumber64 A);

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
