// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/AssertionMacros.h"
#include "FixedPointFwd.h"
#include "FixedPointNumbers.h"
#include "FixedPointVector.h"
#include "FixedPointQuat.h"
#include "FixedPointRotator.h"
#include "FixedPointMath.h"
#include "FixedPointTransform.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedTransform
{
public:
	GENERATED_BODY()

	FORCEINLINE void DiagnosticCheckNaN_Translate() const {}
	FORCEINLINE void DiagnosticCheckNaN_Rotate() const {}
	FORCEINLINE void DiagnosticCheckNaN_Scale3D() const {}
	FORCEINLINE void DiagnosticCheckNaN_All() const {}
	FORCEINLINE void DiagnosticCheck_IsValid() const {}
protected:
	/** Rotation of this transformation, as a quaternion. */
	FFixedQuat Rotation;
	/** Translation of this transformation, as a vector. */
	FFixedVector Translation;
	/** 3D scale (always applied in local space) as a vector. */
	FFixedVector Scale3D;
public:
	/** Default constructor. */
	FORCEINLINE FFixedTransform()
	: Rotation(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One)
	, Translation(FixedPoint::Constants::Fixed64::Zero)
	, Scale3D(FFixedVector::OneVector)
	{
	}

	/**
	* Constructor with an initial translation
	*
	* @param InTranslation The value to use for the translation component
	*/
	FORCEINLINE explicit FFixedTransform(const FFixedVector& InTranslation)
		: Rotation(FFixedQuat::Identity),
		Translation(InTranslation),
		Scale3D(FFixedVector::OneVector)
	{
	}

	/**
	* Constructor with leaving uninitialized memory
	*/
	FORCEINLINE explicit FFixedTransform(ENoInit){}

	/**
	* Constructor with an initial rotation
	*
	* @param InRotation The value to use for rotation component
	*/
	FORCEINLINE explicit FFixedTransform(const FFixedQuat& InRotation)
		: Rotation(InRotation),
		Translation(FFixedVector::ZeroVector),
		Scale3D(FFixedVector::OneVector)
	{
	}

	/**
	* Constructor with an initial rotation
	*
	* @param InRotation The value to use for rotation component  (after being converted to a quaternion)
	*/
	FORCEINLINE explicit FFixedTransform(const FFixedRotator& InRotation)
		: Rotation(InRotation),
		Translation(FFixedVector::ZeroVector),
		Scale3D(FFixedVector::OneVector)
	{
	}

	/**
	* Constructor with all components initialized
	*
	* @param InRotation The value to use for rotation component
	* @param InTranslation The value to use for the translation component
	* @param InScale3D The value to use for the scale component
	*/
	FORCEINLINE FFixedTransform(const FFixedQuat& InRotation, const FFixedVector& InTranslation, const FFixedVector& InScale3D = FFixedVector::OneVector)
		: Rotation(InRotation),
		Translation(InTranslation),
		Scale3D(InScale3D)
	{
	}

	/**
	* Constructor with all components initialized, taking a TRotator<T> as the rotation component
	*
	* @param InRotation The value to use for rotation component (after being converted to a quaternion)
	* @param InTranslation The value to use for the translation component
	* @param InScale3D The value to use for the scale component
	*/
	FORCEINLINE FFixedTransform(const FFixedRotator& InRotation, const FFixedVector& InTranslation, const FFixedVector& InScale3D = FFixedVector::OneVector)
		: Rotation(InRotation),
		Translation(InTranslation),
		Scale3D(InScale3D)
	{
	}

	void SetFromMatrix(const FFixedMatrix& InMatrix)
	{
		FFixedMatrix M = InMatrix;

		// Get the 3D scale from the matrix
		Scale3D = M.ExtractScaling();

		// If there is negative scaling going on, we handle that here
		if (InMatrix.Determinant() < FixedPoint::Constants::Fixed64::Zero)
		{
			// Assume it is along X and modify transform accordingly. 
			// It doesn't actually matter which axis we choose, the 'appearance' will be the same
			Scale3D.X *= -FixedPoint::Constants::Fixed64::One;
			M.SetAxis(FixedPoint::Constants::Fixed64::Zero, -M.GetScaledAxis(EAxis::X));
		}

		Rotation = FFixedQuat(M);
		Translation = InMatrix.GetOrigin();

		// Normalize rotation
		Rotation.Normalize();
	}

	/**
	* Constructor for converting a Matrix (including scale) into a FFixedTransform.
	*/
	FORCEINLINE explicit FFixedTransform(const FFixedMatrix& InMatrix)
	{
		SetFromMatrix(InMatrix);
	}

	/** Constructor that takes basis axes and translation */
	FORCEINLINE FFixedTransform(const FFixedVector& InX, const FFixedVector& InY, const FFixedVector& InZ, const FFixedVector& InTranslation)
	{
		SetFromMatrix(FFixedMatrix(InX, InY, InZ, InTranslation));
	}

	static const FFixedTransform Identity;

	/**
	* Does a debugf of the contents of this Transform.
	*/
	void DebugPrint() const;

	/** Debug purpose only **/
	bool DebugEqualMatrix(const FFixedMatrix& Matrix) const;

	/** Convert FFixedTransform contents to a string */
	FString ToHumanReadableString() const;

	FString ToString() const;

	/** Acceptable form: "%f,%f,%f|%f,%f,%f|%f,%f,%f" */
	bool InitFromString(const FString& InSourceString);

	/**
	* Returns the rotation component
	*
	* @return The rotation component
	*/
	FORCEINLINE FFixedQuat GetRotation() const
	{
		return Rotation;
	}

	/**
	* Returns the translation component
	*
	* @return The translation component
	*/
	FORCEINLINE FFixedVector GetTranslation() const
	{
		return Translation;
	}

	/**
	* Returns the Scale3D component
	*
	* @return The Scale3D component
	*/
	FORCEINLINE FFixedVector GetScale3D() const
	{
		return Scale3D;
	}

private:
	FORCEINLINE bool Private_RotationEquals(const FFixedQuat& InRotation, const FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Rotation.Equals(InRotation, Tolerance);
	}

	FORCEINLINE bool Private_TranslationEquals(const FFixedVector& InTranslation, const FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Translation.Equals(InTranslation, Tolerance);
	}

	FORCEINLINE bool Private_Scale3DEquals(const FFixedVector& InScale3D, const FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Scale3D.Equals(InScale3D, Tolerance);
	}
public:

	// Test if A's rotation equals B's rotation, within a tolerance. Preferred over "A.GetRotation().Equals(B.GetRotation())" because it is faster on some platforms.
	FORCEINLINE static bool AreRotationsEqual(const FFixedTransform& A, const FFixedTransform& B, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber)
	{
		return A.Private_RotationEquals(B.Rotation, Tolerance);
	}

	// Test if A's translation equals B's translation, within a tolerance. Preferred over "A.GetTranslation().Equals(B.GetTranslation())" because it is faster on some platforms.
	FORCEINLINE static bool AreTranslationsEqual(const FFixedTransform& A, const FFixedTransform& B, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber)
	{
		return A.Private_TranslationEquals(B.Translation, Tolerance);
	}

	// Test if A's scale equals B's scale, within a tolerance. Preferred over "A.GetScale3D().Equals(B.GetScale3D())" because it is faster on some platforms.
	FORCEINLINE static bool AreScale3DsEqual(const FFixedTransform& A, const FFixedTransform& B, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber)
	{
		return A.Private_Scale3DEquals(B.Scale3D, Tolerance);
	}

	// Test if this Transform's rotation equals another's rotation, within a tolerance. Preferred over "GetRotation().Equals(Other.GetRotation())" because it is faster on some platforms.
	FORCEINLINE bool RotationEquals(const FFixedTransform& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return AreRotationsEqual(*this, Other, Tolerance);
	}

	// Test if this Transform's translation equals another's translation, within a tolerance. Preferred over "GetTranslation().Equals(Other.GetTranslation())" because it is faster on some platforms.
	FORCEINLINE bool TranslationEquals(const FFixedTransform& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return AreTranslationsEqual(*this, Other, Tolerance);
	}

	// Test if this Transform's scale equals another's scale, within a tolerance. Preferred over "GetScale3D().Equals(Other.GetScale3D())" because it is faster on some platforms.
	FORCEINLINE bool Scale3DEquals(const FFixedTransform& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return AreScale3DsEqual(*this, Other, Tolerance);
	}

	// Test if all components of the transforms are equal, within a tolerance.
	FORCEINLINE bool Equals(const FFixedTransform& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Private_TranslationEquals(Other.Translation, Tolerance) && Private_RotationEquals(Other.Rotation, Tolerance) && Private_Scale3DEquals(Other.Scale3D, Tolerance);
	}

	// Test if all components of the transform property are equal.
	FORCEINLINE bool Identical(const FFixedTransform* Other, uint32 PortFlags) const
	{
		return Equals(*Other, FixedPoint::Constants::Fixed64::Zero);
	}

	// Test if rotation and translation components of the transforms are equal, within a tolerance.
	FORCEINLINE bool EqualsNoScale(const FFixedTransform& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Private_TranslationEquals(Other.Translation, Tolerance) && Private_RotationEquals(Other.Rotation, Tolerance);
	}

	/**
	* Sets the components
	* @param InRotation The new value for the Rotation component
	* @param InTranslation The new value for the Translation component
	* @param InScale3D The new value for the Scale3D component
	*/
	FORCEINLINE void SetComponents(const FFixedQuat& InRotation, const FFixedVector& InTranslation, const FFixedVector& InScale3D)
	{
		Rotation = InRotation;
		Translation = InTranslation;
		Scale3D = InScale3D;
	}
};
