// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatRotator64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicRotator64
{
public:
	GENERATED_BODY()

	/** Rotation around the right axis (around Y axis), Looking up and down (0=Straight Ahead, +Up, -Down) */
	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Pitch;

	/** Rotation around the up axis (around Z axis), Turning around (0=Forward, +Right, -Left)*/
	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Yaw;

	/** Rotation around the forward axis (around X axis), Tilting your head, (0=Straight, +Clockwise, -CCW) */
	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Roll;

	/** A rotator of zero degrees on each axis. */
	static const FDeterministicRotator64 ZeroRotator;

	FORCEINLINE void DiagnosticCheckNaN() const {}
	FORCEINLINE void DiagnosticCheckNaN(const TCHAR* Message) const {}

	/** Default constructor (no initialization). */
	FORCEINLINE FDeterministicRotator64() {}

	/**
	 * Constructor
	 *
	 * @param InF Value to set all components to.
	 */
	FORCEINLINE FDeterministicRotator64(FDeterministicNumber64 InF) : Pitch(InF), Yaw(InF), Roll(InF) {}

	/**
	 * Constructor.
	 *
	 * @param InPitch Pitch in degrees.
	 * @param InYaw Yaw in degrees.
	 * @param InRoll Roll in degrees.
	 */
	FORCEINLINE FDeterministicRotator64(FDeterministicNumber64 InPitch, FDeterministicNumber64 InYaw, FDeterministicNumber64 InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll)	{}

	/**
	 * Constructor
	 *
	 * @param EForceInit Force Init Enum.
	 */
	explicit FORCEINLINE FDeterministicRotator64(EForceInit) : Pitch(DeterministicFloat::Constants::Number64::Zero), Yaw(DeterministicFloat::Constants::Number64::Zero), Roll(DeterministicFloat::Constants::Number64::Zero) {}

	/**
	 * Constructor.
	 *
	 * @param Quat Quaternion used to specify rotation.
	 */
	explicit FORCEINLINE FDeterministicRotator64(const FDeterministicQuat64& Quat);

	FORCEINLINE FDeterministicRotator64(const FRotator& Rot)
	{
		Pitch = Rot.Pitch;
		Yaw = Rot.Yaw;
		Roll = Rot.Roll;
	}

	// Binary arithmetic operators.

	/**
	 * Get the result of adding a rotator to this.
	 *
	 * @param R The other rotator.
	 * @return The result of adding a rotator to this.
	 */
	FORCEINLINE FDeterministicRotator64 operator+(const FDeterministicRotator64& R) const
	{
		return FDeterministicRotator64(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll);
	}

	/**
	 * Get the result of subtracting a rotator from this.
	 *
	 * @param R The other rotator.
	 * @return The result of subtracting a rotator from this.
	 */
	FORCEINLINE FDeterministicRotator64 operator-(const FDeterministicRotator64& R) const
	{
		return FDeterministicRotator64(Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll);
	}

	/**
	 * Get the result of scaling this rotator.
	 *
	 * @param Scale The scaling factor.
	 * @return The result of scaling.
	 */
	FORCEINLINE FDeterministicRotator64 operator*(FDeterministicNumber64 Scale) const
	{
		return FDeterministicRotator64(Pitch * Scale, Yaw * Scale, Roll * Scale);
	}

	/**
	 * Multiply this rotator by a scaling factor.
	 *
	 * @param Scale The scaling factor.
	 * @return Copy of the rotator after scaling.
	 */
	FORCEINLINE FDeterministicRotator64 operator*=(FDeterministicNumber64 Scale)
	{
		Pitch = Pitch * Scale; Yaw = Yaw * Scale; Roll = Roll * Scale;
		return *this;
	}

	// Binary comparison operators.

	/**
	 * Checks whether two rotators are identical. This checks each component for exact equality.
	 *
	 * @param R The other rotator.
	 * @return true if two rotators are identical, otherwise false.
	 * @see Equals()
	 */
	FORCEINLINE bool operator==(const FDeterministicRotator64& R) const
	{
		return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll;
	}

	/**
	 * Checks whether two rotators are different.
	 *
	 * @param V The other rotator.
	 * @return true if two rotators are different, otherwise false.
	 */
	FORCEINLINE bool operator!=(const FDeterministicRotator64& V) const
	{
		return Pitch != V.Pitch || Yaw != V.Yaw || Roll != V.Roll;
	}

	// Assignment operators.

	/**
	 * Adds another rotator to this.
	 *
	 * @param R The other rotator.
	 * @return Copy of rotator after addition.
	 */
	FORCEINLINE FDeterministicRotator64 operator+=(const FDeterministicRotator64& R)
	{
		Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
		return *this;
	}

	/**
	 * Subtracts another rotator from this.
	 *
	 * @param R The other rotator.
	 * @return Copy of rotator after subtraction.
	 */
	FORCEINLINE FDeterministicRotator64 operator-=(const FDeterministicRotator64& R)
	{
		Pitch -= R.Pitch; Yaw -= R.Yaw; Roll -= R.Roll;
		return *this;
	}

	/**
	 * Checks whether rotator is nearly zero within specified tolerance, when treated as an orientation.
	 * This means that TRotator(0, 0, 360) is "zero", because it is the same final orientation as the zero rotator.
	 *
	 * @param Tolerance Error Tolerance.
	 * @return true if rotator is nearly zero, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool IsNearlyZero(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const
	{
		return
			FDeterministicFloatMath::Abs(NormalizeAxis(Pitch)) <= Tolerance
			&& FDeterministicFloatMath::Abs(NormalizeAxis(Yaw)) <= Tolerance
			&& FDeterministicFloatMath::Abs(NormalizeAxis(Roll)) <= Tolerance;
	}

	/**
	 * Checks whether this has exactly zero rotation, when treated as an orientation.
	 * This means that TRotator(0, 0, 360) is "zero", because it is the same final orientation as the zero rotator.
	 *
	 * @return true if this has exactly zero rotation, otherwise false.
	 */
	FORCEINLINE bool IsZero() const
	{
		return (ClampAxis(Pitch) == DeterministicFloat::Constants::Number64::Zero) && (ClampAxis(Yaw) == DeterministicFloat::Constants::Number64::Zero) && (ClampAxis(Roll) == DeterministicFloat::Constants::Number64::Zero);
	}

	/**
	 * Checks whether two rotators are equal within specified tolerance, when treated as an orientation.
	 * This means that TRotator(0, 0, 360).Equals(TRotator(0,0,0)) is true, because they represent the same final orientation.
	 *
	 * @param R The other rotator.
	 * @param Tolerance Error Tolerance.
	 * @return true if two rotators are equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FDeterministicRotator64& R, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const
	{
		return (FDeterministicFloatMath::Abs(NormalizeAxis(Pitch - R.Pitch)) <= Tolerance)
			&& (FDeterministicFloatMath::Abs(NormalizeAxis(Yaw - R.Yaw)) <= Tolerance)
			&& (FDeterministicFloatMath::Abs(NormalizeAxis(Roll - R.Roll)) <= Tolerance);
	}

	/**
	 * Adds to each component of the rotator.
	 *
	 * @param DeltaPitch Change in pitch. (+/-)
	 * @param DeltaYaw Change in yaw. (+/-)
	 * @param DeltaRoll Change in roll. (+/-)
	 * @return Copy of rotator after addition.
	 */
	FORCEINLINE FDeterministicRotator64 Add(FDeterministicNumber64 DeltaPitch, FDeterministicNumber64 DeltaYaw, FDeterministicNumber64 DeltaRoll)
	{
		Yaw += DeltaYaw;
		Pitch += DeltaPitch;
		Roll += DeltaRoll;
		return *this;
	}

	/**
	 * Returns the inverse of the rotator.
	 */
	FORCEINLINE FDeterministicRotator64 GetInverse() const;

	/**
	 * Get the rotation, snapped to specified degree segments.
	 *
	 * @param RotGrid A Rotator specifying how to snap each component.
	 * @return Snapped version of rotation.
	 */
	FORCEINLINE FDeterministicRotator64 GridSnap(const FDeterministicRotator64& RotGrid) const
	{
		return FDeterministicRotator64
		(
			FDeterministicFloatMath::GridSnap(Pitch, RotGrid.Pitch),
			FDeterministicFloatMath::GridSnap(Yaw, RotGrid.Yaw),
			FDeterministicFloatMath::GridSnap(Roll, RotGrid.Roll)
		);
	}

	/**
	 * Convert a rotation into a unit vector facing in its direction.
	 *
	 * @return Rotation as a unit direction vector.
	 */
	FORCEINLINE FDeterministicVector64 Vector() const;

	/**
	 * Get Rotation as a quaternion.
	 *
	 * @return Rotation as a quaternion.
	 */
	FORCEINLINE FDeterministicQuat64 Quaternion() const;

	/**
	 * Convert a Rotator into floating-point Euler angles (in degrees). Rotator now stored in degrees.
	 *
	 * @return Rotation as a Euler angle vector.
	 */
	FORCEINLINE FDeterministicVector64 Euler() const;

	/**
	 * Rotate a vector rotated by this rotator.
	 *
	 * @param V The vector to rotate.
	 * @return The rotated vector.
	 */
	FORCEINLINE FDeterministicVector64 RotateVector(const FDeterministicVector64& V) const;
	
	/**
	 * Returns the vector rotated by the inverse of this rotator.
	 *
	 * @param V The vector to rotate.
	 * @return The rotated vector.
	 */
	FORCEINLINE FDeterministicVector64 UnrotateVector(const FDeterministicVector64& V) const;

	/**
	 * Gets the rotation values so they fall within the range [0,360]
	 *
	 * @return Clamped version of rotator.
	 */
	FORCEINLINE FDeterministicRotator64 Clamp() const
	{
		return FDeterministicRotator64(ClampAxis(Pitch), ClampAxis(Yaw), ClampAxis(Roll));
	}

	/**
	 * Create a copy of this rotator and normalize, removes all winding and creates the "shortest route" rotation.
	 *
	 * @return Normalized copy of this rotator
	 */
	FORCEINLINE FDeterministicRotator64 GetNormalized() const
	{
		FDeterministicRotator64 Rot = *this;
		Rot.Normalize();
		return Rot;
	}

	/**
	 * Create a copy of this rotator and denormalize, clamping each axis to 0 - 360.
	 *
	 * @return Denormalized copy of this rotator
	 */
	FORCEINLINE FDeterministicRotator64 GetDenormalized() const
	{
		FDeterministicRotator64 Rot = *this;
		Rot.Pitch = ClampAxis(Rot.Pitch);
		Rot.Yaw = ClampAxis(Rot.Yaw);
		Rot.Roll = ClampAxis(Rot.Roll);
		return Rot;
	}

	/** Get a specific component of the vector, given a specific axis by enum */
	FORCEINLINE FDeterministicNumber64 GetComponentForAxis(EAxis::Type Axis) const
	{
		switch (Axis)
		{
		case EAxis::X:
			return Roll;
		case EAxis::Y:
			return Pitch;
		case EAxis::Z:
			return Yaw;
		default:
			return DeterministicFloat::Constants::Number64::Zero;
		}
	}

	/** Set a specified componet of the vector, given a specific axis by enum */
	FORCEINLINE void SetComponentForAxis(EAxis::Type Axis, FDeterministicNumber64 Component)
	{
		switch (Axis)
		{
		case EAxis::X:
			Roll = Component;
			break;
		case EAxis::Y:
			Pitch = Component;
			break;
		case EAxis::Z:
			Yaw = Component;
			break;
		}
	}

	/**
	 * In-place normalize, removes all winding and creates the "shortest route" rotation.
	 */
	void Normalize()
	{
		Pitch = NormalizeAxis(Pitch);
		Yaw = NormalizeAxis(Yaw);
		Roll = NormalizeAxis(Roll);
	}

	/**
	 * Decompose this Rotator into a Winding part (multiples of 360) and a Remainder part.
	 * Remainder will always be in [-180, 180] range.
	 *
	 * @param Winding[Out] the Winding part of this Rotator
	 * @param Remainder[Out] the Remainder
	 */
	void GetWindingAndRemainder(FDeterministicRotator64& Winding, FDeterministicRotator64& Remainder) const;

	/**
	* Return the manhattan distance in degrees between this Rotator and the passed in one.
	* @param Rotator[In] the Rotator we are comparing with.
	* @return Distance(Manhattan) between the two rotators.
	*/
	FORCEINLINE FDeterministicNumber64 GetManhattanDistance(const FDeterministicRotator64& Rotator) const
	{
		return FDeterministicFloatMath::Abs(Yaw - Rotator.Yaw) + FDeterministicFloatMath::Abs(Pitch - Rotator.Pitch) + FDeterministicFloatMath::Abs(Roll - Rotator.Roll);
	}

	/**
	* Return a Rotator that has the same rotation but has different degree values for Yaw, Pitch, and Roll.
	* This rotator should be within -180,180 range,
	* @return A Rotator with the same rotation but different degrees.
	*/
	FORCEINLINE FDeterministicRotator64 GetEquivalentRotator() const
	{
		return FDeterministicRotator64(DeterministicFloat::Constants::Number64::OneEighty - Pitch, Yaw + DeterministicFloat::Constants::Number64::OneEighty, Roll + DeterministicFloat::Constants::Number64::OneEighty);
	}

	/**
	* Modify if necessary the passed in rotator to be the closest rotator to it based upon it's equivalent.
	* This Rotator should be within (-180, 180], usually just constructed from a Matrix or a Quaternion.
	*
	* @param MakeClosest[In/Out] the Rotator we want to make closest to us. Should be between
	* (-180, 180]. This Rotator may change if we need to use different degree values to make it closer.
	*/
	FORCEINLINE void SetClosestToMe(FDeterministicRotator64& MakeClosest) const
	{
		FDeterministicRotator64 OtherChoice = MakeClosest.GetEquivalentRotator();
		FDeterministicNumber64 FirstDiff = GetManhattanDistance(MakeClosest);
		FDeterministicNumber64 SecondDiff = GetManhattanDistance(OtherChoice);
		if (SecondDiff < FirstDiff)
			MakeClosest = OtherChoice;
	}

	/**
	 * Get a textual representation of the vector.
	 *
	 * @return Text describing the vector.
	 */
	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("P=%f Y=%f R=%f"), (double)Pitch, (double)Yaw, (double)Roll);
	}

	/** Get a short textural representation of this vector, for compact readable logging. */
	FORCEINLINE FString ToCompactString() const
	{
		if (IsNearlyZero())
		{
			return FString::Printf(TEXT("R(0)"));
		}

		FString ReturnString(TEXT("R("));
		bool bIsEmptyString = true;
		if (!FDeterministicFloatMath::IsNearlyZero(Pitch))
		{
			ReturnString += FString::Printf(TEXT("P=%.2f"), (double)Pitch);
			bIsEmptyString = false;
		}
		if (!FDeterministicFloatMath::IsNearlyZero(Yaw))
		{
			if (!bIsEmptyString)
			{
				ReturnString += FString(TEXT(", "));
			}
			ReturnString += FString::Printf(TEXT("Y=%.2f"), (double)Yaw);
			bIsEmptyString = false;
		}
		if (!FDeterministicFloatMath::IsNearlyZero(Roll))
		{
			if (!bIsEmptyString)
			{
				ReturnString += FString(TEXT(", "));
			}
			ReturnString += FString::Printf(TEXT("R=%.2f"), (double)Roll);
			bIsEmptyString = false;
		}
		ReturnString += FString(TEXT(")"));
		return ReturnString;
	}

	/**
	 * Initialize this Rotator based on an FString. The String is expected to contain P=, Y=, R=.
	 * The TRotator will be bogus when InitFromString returns false.
	 *
	 * @param InSourceString	FString containing the rotator values.
	 * @return true if the P,Y,R values were read successfully; false otherwise.
	 */
	FORCEINLINE bool InitFromString(const FString& InSourceString)
	{
		Pitch = Yaw = Roll = 0;

		// The initialization is only successful if the X, Y, and Z values can all be parsed from the string
		double p = 0.0;
		double y = 0.0;
		double r = 0.0;
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("P="), p) && FParse::Value(*InSourceString, TEXT("Y="), y) && FParse::Value(*InSourceString, TEXT("R="), r);
		Pitch = (FDeterministicNumber64)p;
		Yaw = (FDeterministicNumber64)y;
		Roll = (FDeterministicNumber64)r;

		DiagnosticCheckNaN();
		return bSuccessful;
	}

	/**
	 * Utility to check if there are any non-finite values (NaN or Inf) in this Rotator.
	 *
	 * @return true if there are any non-finite values in this Rotator, otherwise false.
	 */
	FORCEINLINE bool ContainsNaN() const
	{
		return false;
	}

	/**
	 * Clamps an angle to the range of [0, 360).
	 *
	 * @param Angle The angle to clamp.
	 * @return The clamped angle.
	 */
	static FDeterministicNumber64 ClampAxis(FDeterministicNumber64 Angle)
	{
		// returns Angle in the range (-360,360)
		Angle = FDeterministicFloatMath::Fmod(Angle, DeterministicFloat::Constants::Number64::ThreeSixty);

		if (Angle < DeterministicFloat::Constants::Number64::Zero)
		{
			// shift to [0,360) range
			Angle += DeterministicFloat::Constants::Number64::ThreeSixty;
		}

		return Angle;
	}

	/**
	 * Clamps an angle to the range of (-180, 180].
	 *
	 * @param Angle The Angle to clamp.
	 * @return The clamped angle.
	 */
	static FDeterministicNumber64 NormalizeAxis(FDeterministicNumber64 Angle)
	{
		// returns Angle in the range [0,360)
		Angle = ClampAxis(Angle);

		if (Angle > DeterministicFloat::Constants::Number64::OneEighty)
		{
			// shift to (-180,180]
			Angle -= DeterministicFloat::Constants::Number64::ThreeSixty;
		}

		return Angle;
	}

	/**
	 * Compresses a floating point angle into a byte.
	 *
	 * @param Angle The angle to compress.
	 * @return The angle as a byte.
	 */
	static uint8 CompressAxisToByte(FDeterministicNumber64 Angle)
	{
		// map [0->360) to [0->256) and mask off any winding
		return (uint8)((int64)FDeterministicFloatMath::RoundToInt(Angle * FDeterministicNumber64::Make(256.0) / DeterministicFloat::Constants::Number64::ThreeSixty) & 0xFF);
	}

	/**
	 * Decompress a word into a floating point angle.
	 *
	 * @param Angle The word angle.
	 * @return The decompressed angle.
	 */
	static FDeterministicNumber64 DecompressAxisFromByte(uint8 Angle)
	{
		// map [0->256) to [0->360)
		return (FDeterministicNumber64)((double)(Angle * (360.0 / 256.0)));
	}

	/**
	 * Compress a floating point angle into a word.
	 *
	 * @param Angle The angle to compress.
	 * @return The decompressed angle.
	 */
	static uint16 CompressAxisToShort(FDeterministicNumber64 Angle)
	{
		// map [0->360) to [0->65536) and mask off any winding
		return (uint8)((int64)FDeterministicFloatMath::RoundToInt(Angle * FDeterministicNumber64::Make(65536.0) / DeterministicFloat::Constants::Number64::ThreeSixty) & 0xFFFF);
	}

	/**
	 * Decompress a short into a floating point angle.
	 *
	 * @param Angle The word angle.
	 * @return The decompressed angle.
	 */
	static FDeterministicNumber64 DecompressAxisFromShort(uint16 Angle)
	{
		// map [0->65536) to [0->360)
		return (FDeterministicNumber64((int64)Angle) * DeterministicFloat::Constants::Number64::ThreeSixty / FDeterministicNumber64::Make(65536.0));
	}

	/**
	 * Convert a vector of floating-point Euler angles (in degrees) into a Rotator. Rotator now stored in degrees
	 *
	 * @param Euler Euler angle vector.
	 * @return A rotator from a Euler angle.
	 */
	static FDeterministicRotator64 MakeFromEuler(const FDeterministicVector64& Euler);
};

FORCEINLINE FDeterministicRotator64 operator*(FDeterministicNumber64 Scale, const FDeterministicRotator64& R)
{
	return R.operator*(Scale);
}

template<>
struct TCustomLerp<FDeterministicRotator64>
{
	enum { Value = true };

	static FORCEINLINE_DEBUGGABLE FDeterministicRotator64 Lerp(const FDeterministicRotator64& A, const FDeterministicRotator64& B, const FDeterministicNumber64& Alpha)
	{
		return A + (B - A).GetNormalized() * Alpha;
	}
};
