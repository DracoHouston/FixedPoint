// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FixedPointTypes.h"
#include "FixedPointRotator.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedRotator
{
public:
	GENERATED_BODY()

	/** Rotation around the right axis (around Y axis), Looking up and down (0=Straight Ahead, +Up, -Down) */
	UPROPERTY(EditAnywhere)
	FFixed64 Pitch;

	/** Rotation around the up axis (around Z axis), Turning around (0=Forward, +Right, -Left)*/
	UPROPERTY(EditAnywhere)
	FFixed64 Yaw;

	/** Rotation around the forward axis (around X axis), Tilting your head, (0=Straight, +Clockwise, -CCW) */
	UPROPERTY(EditAnywhere)
	FFixed64 Roll;

	/** A rotator of zero degrees on each axis. */
	static const FFixedRotator ZeroRotator;

	FORCEINLINE void DiagnosticCheckNaN() const {}
	FORCEINLINE void DiagnosticCheckNaN(const TCHAR* Message) const {}

	/** Default constructor (no initialization). */
	FORCEINLINE FFixedRotator() {}

	/**
	 * Constructor
	 *
	 * @param InF Value to set all components to.
	 */
	FORCEINLINE FFixedRotator(FFixed64 InF) : Pitch(InF), Yaw(InF), Roll(InF) {}

	/**
	 * Constructor.
	 *
	 * @param InPitch Pitch in degrees.
	 * @param InYaw Yaw in degrees.
	 * @param InRoll Roll in degrees.
	 */
	FORCEINLINE FFixedRotator(FFixed64 InPitch, FFixed64 InYaw, FFixed64 InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll)	{}

	/**
	 * Constructor
	 *
	 * @param EForceInit Force Init Enum.
	 */
	explicit FORCEINLINE FFixedRotator(EForceInit) : Pitch(FixedPoint::Constants::Fixed64::Zero), Yaw(FixedPoint::Constants::Fixed64::Zero), Roll(FixedPoint::Constants::Fixed64::Zero) {}

	/**
	 * Constructor.
	 *
	 * @param Quat Quaternion used to specify rotation.
	 */
	explicit FORCEINLINE FFixedRotator(const FFixedQuat& Quat);

	// Binary arithmetic operators.

	/**
	 * Get the result of adding a rotator to this.
	 *
	 * @param R The other rotator.
	 * @return The result of adding a rotator to this.
	 */
	FORCEINLINE FFixedRotator operator+(const FFixedRotator& R) const
	{
		return FFixedRotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll);
	}

	/**
	 * Get the result of subtracting a rotator from this.
	 *
	 * @param R The other rotator.
	 * @return The result of subtracting a rotator from this.
	 */
	FORCEINLINE FFixedRotator operator-(const FFixedRotator& R) const
	{
		return FFixedRotator(Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll);
	}

	/**
	 * Get the result of scaling this rotator.
	 *
	 * @param Scale The scaling factor.
	 * @return The result of scaling.
	 */
	FORCEINLINE FFixedRotator operator*(FFixed64 Scale) const
	{
		return FFixedRotator(Pitch * Scale, Yaw * Scale, Roll * Scale);
	}

	/**
	 * Multiply this rotator by a scaling factor.
	 *
	 * @param Scale The scaling factor.
	 * @return Copy of the rotator after scaling.
	 */
	FORCEINLINE FFixedRotator operator*=(FFixed64 Scale)
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
	FORCEINLINE bool operator==(const FFixedRotator& R) const
	{
		return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll;
	}

	/**
	 * Checks whether two rotators are different.
	 *
	 * @param V The other rotator.
	 * @return true if two rotators are different, otherwise false.
	 */
	FORCEINLINE bool operator!=(const FFixedRotator& V) const
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
	FORCEINLINE FFixedRotator operator+=(const FFixedRotator& R)
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
	FORCEINLINE FFixedRotator operator-=(const FFixedRotator& R)
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
	FORCEINLINE bool IsNearlyZero(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return
			FFixedPointMath::Abs(NormalizeAxis(Pitch)) <= Tolerance
			&& FFixedPointMath::Abs(NormalizeAxis(Yaw)) <= Tolerance
			&& FFixedPointMath::Abs(NormalizeAxis(Roll)) <= Tolerance;
	}

	/**
	 * Checks whether this has exactly zero rotation, when treated as an orientation.
	 * This means that TRotator(0, 0, 360) is "zero", because it is the same final orientation as the zero rotator.
	 *
	 * @return true if this has exactly zero rotation, otherwise false.
	 */
	FORCEINLINE bool IsZero() const
	{
		return (ClampAxis(Pitch) == FixedPoint::Constants::Fixed64::Zero) && (ClampAxis(Yaw) == FixedPoint::Constants::Fixed64::Zero) && (ClampAxis(Roll) == FixedPoint::Constants::Fixed64::Zero);
	}

	/**
	 * Checks whether two rotators are equal within specified tolerance, when treated as an orientation.
	 * This means that TRotator(0, 0, 360).Equals(TRotator(0,0,0)) is true, because they represent the same final orientation.
	 *
	 * @param R The other rotator.
	 * @param Tolerance Error Tolerance.
	 * @return true if two rotators are equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FFixedRotator& R, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return (FFixedPointMath::Abs(NormalizeAxis(Pitch - R.Pitch)) <= Tolerance)
			&& (FFixedPointMath::Abs(NormalizeAxis(Yaw - R.Yaw)) <= Tolerance)
			&& (FFixedPointMath::Abs(NormalizeAxis(Roll - R.Roll)) <= Tolerance);
	}

	/**
	 * Adds to each component of the rotator.
	 *
	 * @param DeltaPitch Change in pitch. (+/-)
	 * @param DeltaYaw Change in yaw. (+/-)
	 * @param DeltaRoll Change in roll. (+/-)
	 * @return Copy of rotator after addition.
	 */
	FORCEINLINE FFixedRotator Add(FFixed64 DeltaPitch, FFixed64 DeltaYaw, FFixed64 DeltaRoll)
	{
		Yaw += DeltaYaw;
		Pitch += DeltaPitch;
		Roll += DeltaRoll;
		return *this;
	}

	/**
	 * Returns the inverse of the rotator.
	 */
	FORCEINLINE FFixedRotator GetInverse() const;



	/**
	 * Get Rotation as a quaternion.
	 *
	 * @return Rotation as a quaternion.
	 */
	FORCEINLINE FFixedQuat Quaternion() const;




	/**
	 * Clamps an angle to the range of [0, 360).
	 *
	 * @param Angle The angle to clamp.
	 * @return The clamped angle.
	 */
	static FFixed64 ClampAxis(FFixed64 Angle)
	{
		// returns Angle in the range (-360,360)
		Angle = FFixedPointMath::Fmod(Angle, FixedPoint::Constants::Fixed64::ThreeSixty);

		if (Angle < FixedPoint::Constants::Fixed64::Zero)
		{
			// shift to [0,360) range
			Angle += FixedPoint::Constants::Fixed64::ThreeSixty;
		}

		return Angle;
	}

	/**
	 * Clamps an angle to the range of (-180, 180].
	 *
	 * @param Angle The Angle to clamp.
	 * @return The clamped angle.
	 */
	static FFixed64 NormalizeAxis(FFixed64 Angle)
	{
		// returns Angle in the range [0,360)
		Angle = ClampAxis(Angle);

		if (Angle > FixedPoint::Constants::Fixed64::OneEighty)
		{
			// shift to (-180,180]
			Angle -= FixedPoint::Constants::Fixed64::ThreeSixty;
		}

		return Angle;
	}
};

FORCEINLINE FFixedRotator operator*(FFixed64 Scale, const FFixedRotator& R)
{
	return R.operator*(Scale);
}
