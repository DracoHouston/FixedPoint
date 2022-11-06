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
};

FORCEINLINE FFixedRotator operator*(FFixed64 Scale, const FFixedRotator& R)
{
	return R.operator*(Scale);
}
