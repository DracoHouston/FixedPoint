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
	* Convert this Transform to a transformation matrix with scaling.
	*/
	FORCEINLINE FFixedMatrix ToMatrixWithScale() const
	{
		FFixedMatrix OutMatrix;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
		// Make sure Rotation is normalized when we turn it into a matrix.
		check(IsRotationNormalized());
#endif
		OutMatrix.M[3][0] = Translation.X;
		OutMatrix.M[3][1] = Translation.Y;
		OutMatrix.M[3][2] = Translation.Z;

		const FFixed64 x2 = Rotation.X + Rotation.X;
		const FFixed64 y2 = Rotation.Y + Rotation.Y;
		const FFixed64 z2 = Rotation.Z + Rotation.Z;
		{
			const FFixed64 xx2 = Rotation.X * x2;
			const FFixed64 yy2 = Rotation.Y * y2;
			const FFixed64 zz2 = Rotation.Z * z2;

			OutMatrix.M[0][0] = (FixedPoint::Constants::Fixed64::One - (yy2 + zz2)) * Scale3D.X;
			OutMatrix.M[1][1] = (FixedPoint::Constants::Fixed64::One - (xx2 + zz2)) * Scale3D.Y;
			OutMatrix.M[2][2] = (FixedPoint::Constants::Fixed64::One - (xx2 + yy2)) * Scale3D.Z;
		}
		{
			const FFixed64 yz2 = Rotation.Y * z2;
			const FFixed64 wx2 = Rotation.W * x2;

			OutMatrix.M[2][1] = (yz2 - wx2) * Scale3D.Z;
			OutMatrix.M[1][2] = (yz2 + wx2) * Scale3D.Y;
		}
		{
			const FFixed64 xy2 = Rotation.X * y2;
			const FFixed64 wz2 = Rotation.W * z2;

			OutMatrix.M[1][0] = (xy2 - wz2) * Scale3D.Y;
			OutMatrix.M[0][1] = (xy2 + wz2) * Scale3D.X;
		}
		{
			const FFixed64 xz2 = Rotation.X * z2;
			const FFixed64 wy2 = Rotation.W * y2;

			OutMatrix.M[2][0] = (xz2 + wy2) * Scale3D.Z;
			OutMatrix.M[0][2] = (xz2 - wy2) * Scale3D.X;
		}

		OutMatrix.M[0][3] = FixedPoint::Constants::Fixed64::Zero;
		OutMatrix.M[1][3] = FixedPoint::Constants::Fixed64::Zero;
		OutMatrix.M[2][3] = FixedPoint::Constants::Fixed64::Zero;
		OutMatrix.M[3][3] = FixedPoint::Constants::Fixed64::One;

		return OutMatrix;
	}

	/**
	* Convert this Transform to matrix with scaling and compute the inverse of that.
	*/
	FORCEINLINE FFixedMatrix ToInverseMatrixWithScale() const
	{
		// todo: optimize
		return ToMatrixWithScale().Inverse();
	}

	/**
	* Convert this Transform to inverse.
	*/
	FORCEINLINE FFixedTransform Inverse() const
	{
		FFixedQuat   InvRotation = Rotation.Inverse();
		// this used to cause NaN if Scale contained 0 
		FFixedVector InvScale3D = GetSafeScaleReciprocal(Scale3D);
		FFixedVector InvTranslation = InvRotation * (InvScale3D * -Translation);

		return FFixedTransform(InvRotation, InvTranslation, InvScale3D);
	}

	/**
	* Convert this Transform to a transformation matrix, ignoring its scaling
	*/
	FORCEINLINE FFixedMatrix ToMatrixNoScale() const
	{
		FFixedMatrix OutMatrix;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
		// Make sure Rotation is normalized when we turn it into a matrix.
		check(IsRotationNormalized());
#endif
		OutMatrix.M[3][0] = Translation.X;
		OutMatrix.M[3][1] = Translation.Y;
		OutMatrix.M[3][2] = Translation.Z;

		const FFixed64 x2 = Rotation.X + Rotation.X;
		const FFixed64 y2 = Rotation.Y + Rotation.Y;
		const FFixed64 z2 = Rotation.Z + Rotation.Z;
		{
			const FFixed64 xx2 = Rotation.X * x2;
			const FFixed64 yy2 = Rotation.Y * y2;
			const FFixed64 zz2 = Rotation.Z * z2;

			OutMatrix.M[0][0] = (FixedPoint::Constants::Fixed64::One - (yy2 + zz2));
			OutMatrix.M[1][1] = (FixedPoint::Constants::Fixed64::One - (xx2 + zz2));
			OutMatrix.M[2][2] = (FixedPoint::Constants::Fixed64::One - (xx2 + yy2));
		}
		{
			const FFixed64 yz2 = Rotation.Y * z2;
			const FFixed64 wx2 = Rotation.W * x2;

			OutMatrix.M[2][1] = (yz2 - wx2);
			OutMatrix.M[1][2] = (yz2 + wx2);
		}
		{
			const FFixed64 xy2 = Rotation.X * y2;
			const FFixed64 wz2 = Rotation.W * z2;

			OutMatrix.M[1][0] = (xy2 - wz2);
			OutMatrix.M[0][1] = (xy2 + wz2);
		}
		{
			const FFixed64 xz2 = Rotation.X * z2;
			const FFixed64 wy2 = Rotation.W * y2;

			OutMatrix.M[2][0] = (xz2 + wy2);
			OutMatrix.M[0][2] = (xz2 - wy2);
		}

		OutMatrix.M[0][3] = FixedPoint::Constants::Fixed64::Zero;
		OutMatrix.M[1][3] = FixedPoint::Constants::Fixed64::Zero;
		OutMatrix.M[2][3] = FixedPoint::Constants::Fixed64::Zero;
		OutMatrix.M[3][3] = FixedPoint::Constants::Fixed64::One;

		return OutMatrix;
	}

	/** Set this transform to the weighted blend of the supplied two transforms. */
	FORCEINLINE void Blend(const FFixedTransform& Atom1, const FFixedTransform& Atom2, FFixed64 Alpha)
	{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
		// Check that all bone atoms coming from animation are normalized
		check(Atom1.IsRotationNormalized());
		check(Atom2.IsRotationNormalized());
#endif
		if (Alpha <= FixedPoint::Constants::Fixed64::ZeroAnimWeightThresh)
		{
			// if blend is all the way for child1, then just copy its bone atoms
			(*this) = Atom1;
		}
		else if (Alpha >= FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::ZeroAnimWeightThresh)
		{
			// if blend is all the way for child2, then just copy its bone atoms
			(*this) = Atom2;
		}
		else
		{
			// Simple linear interpolation for translation and scale.
			Translation = FFixedPointMath::Lerp(Atom1.Translation, Atom2.Translation, Alpha);
			Scale3D = FFixedPointMath::Lerp(Atom1.Scale3D, Atom2.Scale3D, Alpha);
			Rotation = FFixedQuat::FastLerp(Atom1.Rotation, Atom2.Rotation, Alpha);

			// ..and renormalize
			Rotation.Normalize();
		}
	}

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

	/**
	* Normalize the rotation component of this transformation
	*/
	FORCEINLINE void NormalizeRotation()
	{
		Rotation.Normalize();
	}

	/**
	* Checks whether the rotation component is normalized or not
	*
	* @return true if the rotation component is normalized, and false otherwise.
	*/
	FORCEINLINE bool IsRotationNormalized() const
	{
		return Rotation.IsNormalized();
	}

	FORCEINLINE static FFixedVector GetSafeScaleReciprocal(const FFixedVector& InScale, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		FFixedVector SafeReciprocalScale;
		if (FFixedPointMath::Abs(InScale.X) <= Tolerance)
		{
			SafeReciprocalScale.X = FixedPoint::Constants::Fixed64::Zero;
		}
		else
		{
			SafeReciprocalScale.X = FixedPoint::Constants::Fixed64::One / InScale.X;
		}

		if (FFixedPointMath::Abs(InScale.Y) <= Tolerance)
		{
			SafeReciprocalScale.Y = FixedPoint::Constants::Fixed64::Zero;
		}
		else
		{
			SafeReciprocalScale.Y = FixedPoint::Constants::Fixed64::One / InScale.Y;
		}

		if (FFixedPointMath::Abs(InScale.Z) <= Tolerance)
		{
			SafeReciprocalScale.Z = FixedPoint::Constants::Fixed64::Zero;
		}
		else
		{
			SafeReciprocalScale.Z = FixedPoint::Constants::Fixed64::One / InScale.Z;
		}

		return SafeReciprocalScale;
	}
};
