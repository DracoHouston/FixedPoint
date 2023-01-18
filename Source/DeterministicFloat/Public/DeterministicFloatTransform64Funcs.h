// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatTransform64.h"
#include "Misc/AssertionMacros.h"
#include "DeterministicFloatVector64.h"
#include "DeterministicFloatQuat64.h"
#include "DeterministicFloatRotator64.h"
#include "DeterministicFloatVector4D64.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatMathFuncs.h"
#include "DeterministicFloatVector64Funcs.h"
#include "DeterministicFloatQuat64Funcs.h"
#include "Math/VectorRegister.h"
#include "Math/ScalarRegister.h"

FORCEINLINE void FDeterministicTransform64::DiagnosticCheckNaN_Translate() const 
{
}
	
FORCEINLINE void FDeterministicTransform64::DiagnosticCheckNaN_Rotate() const 
{
}
	
FORCEINLINE void FDeterministicTransform64::DiagnosticCheckNaN_Scale3D() const 
{
}
	
FORCEINLINE void FDeterministicTransform64::DiagnosticCheckNaN_All() const 
{
}
	
FORCEINLINE void FDeterministicTransform64::DiagnosticCheck_IsValid() const 
{
}
	
FORCEINLINE FDeterministicTransform64::FDeterministicTransform64()
: Rotation(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One)
, Translation(DeterministicFloat::Constants::Number64::Zero)
, Scale3D(FDeterministicVector64::OneVector)
{
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(const FTransform& Other)
{
	Translation = Other.GetTranslation();
	Scale3D = Other.GetScale3D();
	Rotation = Other.GetRotation();
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(const FDeterministicVector64& InTranslation)
	: Rotation(FDeterministicQuat64::Identity),
	Translation(InTranslation),
	Scale3D(FDeterministicVector64::OneVector)
{
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(ENoInit)
{
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(const FDeterministicQuat64& InRotation)
	: Rotation(InRotation),
	Translation(FDeterministicVector64::ZeroVector),
	Scale3D(FDeterministicVector64::OneVector)
{
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(const FDeterministicRotator64& InRotation)
	: Rotation(InRotation),
	Translation(FDeterministicVector64::ZeroVector),
	Scale3D(FDeterministicVector64::OneVector)
{
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(const FDeterministicQuat64& InRotation, const FDeterministicVector64& InTranslation, const FDeterministicVector64& InScale3D)
	: Rotation(InRotation),
	Translation(InTranslation),
	Scale3D(InScale3D)
{
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(const FDeterministicRotator64& InRotation, const FDeterministicVector64& InTranslation, const FDeterministicVector64& InScale3D)
	: Rotation(InRotation),
	Translation(InTranslation),
	Scale3D(InScale3D)
{
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(const FDeterministicMatrix64& InMatrix)
{
	SetFromMatrix(InMatrix);
}

FORCEINLINE FDeterministicTransform64::FDeterministicTransform64(const FDeterministicVector64& InX, const FDeterministicVector64& InY, const FDeterministicVector64& InZ, const FDeterministicVector64& InTranslation)
{
	SetFromMatrix(FDeterministicMatrix64(InX, InY, InZ, InTranslation));
}

FORCEINLINE FDeterministicMatrix64 FDeterministicTransform64::ToMatrixWithScale() const
{
	FDeterministicMatrix64 OutMatrix;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
	// Make sure Rotation is normalized when we turn it into a matrix.
	check(IsRotationNormalized());
#endif
	OutMatrix.M[3][0] = Translation.X;
	OutMatrix.M[3][1] = Translation.Y;
	OutMatrix.M[3][2] = Translation.Z;

	const FDeterministicNumber64 x2 = Rotation.X + Rotation.X;
	const FDeterministicNumber64 y2 = Rotation.Y + Rotation.Y;
	const FDeterministicNumber64 z2 = Rotation.Z + Rotation.Z;
	{
		const FDeterministicNumber64 xx2 = Rotation.X * x2;
		const FDeterministicNumber64 yy2 = Rotation.Y * y2;
		const FDeterministicNumber64 zz2 = Rotation.Z * z2;

		OutMatrix.M[0][0] = (DeterministicFloat::Constants::Number64::One - (yy2 + zz2)) * Scale3D.X;
		OutMatrix.M[1][1] = (DeterministicFloat::Constants::Number64::One - (xx2 + zz2)) * Scale3D.Y;
		OutMatrix.M[2][2] = (DeterministicFloat::Constants::Number64::One - (xx2 + yy2)) * Scale3D.Z;
	}
	{
		const FDeterministicNumber64 yz2 = Rotation.Y * z2;
		const FDeterministicNumber64 wx2 = Rotation.W * x2;

		OutMatrix.M[2][1] = (yz2 - wx2) * Scale3D.Z;
		OutMatrix.M[1][2] = (yz2 + wx2) * Scale3D.Y;
	}
	{
		const FDeterministicNumber64 xy2 = Rotation.X * y2;
		const FDeterministicNumber64 wz2 = Rotation.W * z2;

		OutMatrix.M[1][0] = (xy2 - wz2) * Scale3D.Y;
		OutMatrix.M[0][1] = (xy2 + wz2) * Scale3D.X;
	}
	{
		const FDeterministicNumber64 xz2 = Rotation.X * z2;
		const FDeterministicNumber64 wy2 = Rotation.W * y2;

		OutMatrix.M[2][0] = (xz2 + wy2) * Scale3D.Z;
		OutMatrix.M[0][2] = (xz2 - wy2) * Scale3D.X;
	}

	OutMatrix.M[0][3] = DeterministicFloat::Constants::Number64::Zero;
	OutMatrix.M[1][3] = DeterministicFloat::Constants::Number64::Zero;
	OutMatrix.M[2][3] = DeterministicFloat::Constants::Number64::Zero;
	OutMatrix.M[3][3] = DeterministicFloat::Constants::Number64::One;

	return OutMatrix;
}

/**
* Convert this Transform to matrix with scaling and compute the inverse of that.
*/
FORCEINLINE FDeterministicMatrix64 FDeterministicTransform64::ToInverseMatrixWithScale() const
{
	// todo: optimize
	return ToMatrixWithScale().Inverse();
}

/**
* Convert this Transform to inverse.
*/
FORCEINLINE FDeterministicTransform64 FDeterministicTransform64::Inverse() const
{
	FDeterministicQuat64   InvRotation = Rotation.Inverse();
	// this used to cause NaN if Scale contained 0 
	FDeterministicVector64 InvScale3D = GetSafeScaleReciprocal(Scale3D);
	FDeterministicVector64 InvTranslation = InvRotation * (InvScale3D * -Translation);

	return FDeterministicTransform64(InvRotation, InvTranslation, InvScale3D);
}

/**
* Convert this Transform to a transformation matrix, ignoring its scaling
*/
FORCEINLINE FDeterministicMatrix64 FDeterministicTransform64::ToMatrixNoScale() const
{
	FDeterministicMatrix64 OutMatrix;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
	// Make sure Rotation is normalized when we turn it into a matrix.
	check(IsRotationNormalized());
#endif
	OutMatrix.M[3][0] = Translation.X;
	OutMatrix.M[3][1] = Translation.Y;
	OutMatrix.M[3][2] = Translation.Z;

	const FDeterministicNumber64 x2 = Rotation.X + Rotation.X;
	const FDeterministicNumber64 y2 = Rotation.Y + Rotation.Y;
	const FDeterministicNumber64 z2 = Rotation.Z + Rotation.Z;
	{
		const FDeterministicNumber64 xx2 = Rotation.X * x2;
		const FDeterministicNumber64 yy2 = Rotation.Y * y2;
		const FDeterministicNumber64 zz2 = Rotation.Z * z2;

		OutMatrix.M[0][0] = (DeterministicFloat::Constants::Number64::One - (yy2 + zz2));
		OutMatrix.M[1][1] = (DeterministicFloat::Constants::Number64::One - (xx2 + zz2));
		OutMatrix.M[2][2] = (DeterministicFloat::Constants::Number64::One - (xx2 + yy2));
	}
	{
		const FDeterministicNumber64 yz2 = Rotation.Y * z2;
		const FDeterministicNumber64 wx2 = Rotation.W * x2;

		OutMatrix.M[2][1] = (yz2 - wx2);
		OutMatrix.M[1][2] = (yz2 + wx2);
	}
	{
		const FDeterministicNumber64 xy2 = Rotation.X * y2;
		const FDeterministicNumber64 wz2 = Rotation.W * z2;

		OutMatrix.M[1][0] = (xy2 - wz2);
		OutMatrix.M[0][1] = (xy2 + wz2);
	}
	{
		const FDeterministicNumber64 xz2 = Rotation.X * z2;
		const FDeterministicNumber64 wy2 = Rotation.W * y2;

		OutMatrix.M[2][0] = (xz2 + wy2);
		OutMatrix.M[0][2] = (xz2 - wy2);
	}

	OutMatrix.M[0][3] = DeterministicFloat::Constants::Number64::Zero;
	OutMatrix.M[1][3] = DeterministicFloat::Constants::Number64::Zero;
	OutMatrix.M[2][3] = DeterministicFloat::Constants::Number64::Zero;
	OutMatrix.M[3][3] = DeterministicFloat::Constants::Number64::One;

	return OutMatrix;
}

/** Set this transform to the weighted blend of the supplied two transforms. */
FORCEINLINE void FDeterministicTransform64::Blend(const FDeterministicTransform64& Atom1, const FDeterministicTransform64& Atom2, FDeterministicNumber64 Alpha)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
	// Check that all bone atoms coming from animation are normalized
	check(Atom1.IsRotationNormalized());
	check(Atom2.IsRotationNormalized());
#endif
	if (Alpha <= DeterministicFloat::Constants::Number64::ZeroAnimWeightThresh)
	{
		// if blend is all the way for child1, then just copy its bone atoms
		(*this) = Atom1;
	}
	else if (Alpha >= DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::ZeroAnimWeightThresh)
	{
		// if blend is all the way for child2, then just copy its bone atoms
		(*this) = Atom2;
	}
	else
	{
		// Simple linear interpolation for translation and scale.
		Translation = FDeterministicFloatMath::Lerp(Atom1.Translation, Atom2.Translation, Alpha);
		Scale3D = FDeterministicFloatMath::Lerp(Atom1.Scale3D, Atom2.Scale3D, Alpha);
		Rotation = FDeterministicQuat64::FastLerp(Atom1.Rotation, Atom2.Rotation, Alpha);

		// ..and renormalize
		Rotation.Normalize();
	}
}

/** Set this Transform to the weighted blend of it and the supplied Transform. */
FORCEINLINE void FDeterministicTransform64::BlendWith(const FDeterministicTransform64& OtherAtom, FDeterministicNumber64 Alpha)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
	// Check that all bone atoms coming from animation are normalized
	check(IsRotationNormalized());
	check(OtherAtom.IsRotationNormalized());
#endif
	if (Alpha > DeterministicFloat::Constants::Number64::ZeroAnimWeightThresh)
	{
		if (Alpha >= DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::ZeroAnimWeightThresh)
		{
			// if blend is all the way for child2, then just copy its bone atoms
			(*this) = OtherAtom;
		}
		else
		{
			// Simple linear interpolation for translation and scale.
			Translation = FDeterministicFloatMath::Lerp(Translation, OtherAtom.Translation, Alpha);
			Scale3D = FDeterministicFloatMath::Lerp(Scale3D, OtherAtom.Scale3D, Alpha);
			Rotation = FDeterministicQuat64::FastLerp(Rotation, OtherAtom.Rotation, Alpha);

			// ..and renormalize
			Rotation.Normalize();
		}
	}
}

/**
* Quaternion addition is wrong here. This is just a special case for linear interpolation.
* Use only within blends!!
* Rotation part is NOT normalized!!
*/
FORCEINLINE FDeterministicTransform64 FDeterministicTransform64::operator+(const FDeterministicTransform64& Atom) const
{
	return FDeterministicTransform64(Rotation + Atom.Rotation, Translation + Atom.Translation, Scale3D + Atom.Scale3D);
}

FORCEINLINE FDeterministicTransform64& FDeterministicTransform64::operator+=(const FDeterministicTransform64& Atom)
{
	Translation += Atom.Translation;

	Rotation.X += Atom.Rotation.X;
	Rotation.Y += Atom.Rotation.Y;
	Rotation.Z += Atom.Rotation.Z;
	Rotation.W += Atom.Rotation.W;

	Scale3D += Atom.Scale3D;

	return *this;
}

FORCEINLINE FDeterministicTransform64 FDeterministicTransform64::operator*(FDeterministicNumber64 Mult) const
{
	return FDeterministicTransform64(Rotation * Mult, Translation * Mult, Scale3D * Mult);
}

FORCEINLINE FDeterministicTransform64& FDeterministicTransform64::operator*=(FDeterministicNumber64 Mult)
{
	Translation *= Mult;
	Rotation.X *= Mult;
	Rotation.Y *= Mult;
	Rotation.Z *= Mult;
	Rotation.W *= Mult;
	Scale3D *= Mult;

	return *this;
}

FORCEINLINE FDeterministicTransform64 FDeterministicTransform64::operator*(const FDeterministicTransform64& Other) const
{
	FDeterministicTransform64 Output;
	Multiply(&Output, this, &Other);
	return Output;
}

FORCEINLINE void FDeterministicTransform64::operator*=(const FDeterministicTransform64& Other)
{
	Multiply(this, this, &Other);
}

FORCEINLINE FDeterministicTransform64 FDeterministicTransform64::operator*(const FDeterministicQuat64& Other) const
{
	FDeterministicTransform64 Output, OtherTransform(Other, FDeterministicVector64::ZeroVector, FDeterministicVector64::OneVector);
	Multiply(&Output, this, &OtherTransform);
	return Output;
}

FORCEINLINE void FDeterministicTransform64::operator*=(const FDeterministicQuat64& Other)
{
	FDeterministicTransform64 OtherTransform(Other, FDeterministicVector64::ZeroVector, FDeterministicVector64::OneVector);
	Multiply(this, this, &OtherTransform);
}

FORCEINLINE bool FDeterministicTransform64::AnyHasNegativeScale(const FDeterministicVector64& InScale3D, const FDeterministicVector64& InOtherScale3D)
{
	return  (InScale3D.X < DeterministicFloat::Constants::Number64::Zero || InScale3D.Y < DeterministicFloat::Constants::Number64::Zero || InScale3D.Z < DeterministicFloat::Constants::Number64::Zero
		|| InOtherScale3D.X < DeterministicFloat::Constants::Number64::Zero || InOtherScale3D.Y < DeterministicFloat::Constants::Number64::Zero || InOtherScale3D.Z < DeterministicFloat::Constants::Number64::Zero);
}

FORCEINLINE void FDeterministicTransform64::ScaleTranslation(const FDeterministicVector64& InScale3D)
{
	Translation *= InScale3D;
}

FORCEINLINE void FDeterministicTransform64::ScaleTranslation(const FDeterministicNumber64& Scale)
{
	Translation *= Scale;
}

FORCEINLINE void FDeterministicTransform64::RemoveScaling(FDeterministicNumber64 Tolerance)
{
	Scale3D = FDeterministicVector64::OneVector;
	Rotation.Normalize();
}

FORCEINLINE FDeterministicNumber64 FDeterministicTransform64::GetMaximumAxisScale() const
{
	return Scale3D.GetAbsMax();
}

FORCEINLINE FDeterministicNumber64 FDeterministicTransform64::GetMinimumAxisScale() const
{
	return Scale3D.GetAbsMin();
}

FORCEINLINE FDeterministicVector4D64 FDeterministicTransform64::TransformFVector4(const FDeterministicVector4D64& V) const
{
	DiagnosticCheckNaN_All();

	// if not, this won't work
	checkSlow(V.W == DeterministicFloat::Constants::Number64::Zero || V.W == DeterministicFloat::Constants::Number64::One);

	//Transform using QST is following
	//QST(P) = Q*S*P*-Q + T where Q = quaternion, S = scale, T = translation

	FDeterministicVector4D64 Transform = FDeterministicVector4D64(Rotation.RotateVector(Scale3D * FDeterministicVector64(V)), DeterministicFloat::Constants::Number64::Zero);
	if (V.W == DeterministicFloat::Constants::Number64::One)
	{
		Transform += FDeterministicVector4D64(Translation, DeterministicFloat::Constants::Number64::One);
	}

	return Transform;
}

FORCEINLINE FDeterministicVector4D64 FDeterministicTransform64::TransformFVector4NoScale(const FDeterministicVector4D64& V) const
{
	DiagnosticCheckNaN_All();

	// if not, this won't work
	checkSlow(V.W == DeterministicFloat::Constants::Number64::Zero || V.W == DeterministicFloat::Constants::Number64::One);

	//Transform using QST is following
	//QST(P) = Q*S*P*-Q + T where Q = quaternion, S = scale, T = translation
	FDeterministicVector4D64 Transform = FDeterministicVector4D64(Rotation.RotateVector(FDeterministicVector64(V)), DeterministicFloat::Constants::Number64::Zero);
	if (V.W == DeterministicFloat::Constants::Number64::One)
	{
		Transform += FDeterministicVector4D64(Translation, DeterministicFloat::Constants::Number64::One);
	}

	return Transform;
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::TransformPosition(const FDeterministicVector64& V) const
{
	return Rotation.RotateVector(Scale3D * V) + Translation;
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::TransformPositionNoScale(const FDeterministicVector64& V) const
{
	return Rotation.RotateVector(V) + Translation;
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::InverseTransformPosition(const FDeterministicVector64& V) const
{
	return (Rotation.UnrotateVector(V - Translation)) * GetSafeScaleReciprocal(Scale3D);
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::InverseTransformPositionNoScale(const FDeterministicVector64& V) const
{
	return (Rotation.UnrotateVector(V - Translation));
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::TransformVector(const FDeterministicVector64& V) const
{
	return Rotation.RotateVector(Scale3D * V);
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::TransformVectorNoScale(const FDeterministicVector64& V) const
{
	return Rotation.RotateVector(V);
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::InverseTransformVector(const FDeterministicVector64& V) const
{
	return (Rotation.UnrotateVector(V)) * GetSafeScaleReciprocal(Scale3D);
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::InverseTransformVectorNoScale(const FDeterministicVector64& V) const
{
	return (Rotation.UnrotateVector(V));
}

/**
	* Transform a rotation.
	* For example if this is a LocalToWorld transform, TransformRotation(Q) would transform Q from local to world space.
	*/
FORCEINLINE FDeterministicQuat64 FDeterministicTransform64::TransformRotation(const FDeterministicQuat64& Q) const
{
	return GetRotation() * Q;
}

/**
* Inverse transform a rotation.
* For example if this is a LocalToWorld transform, InverseTransformRotation(Q) would transform Q from world to local space.
*/
FORCEINLINE FDeterministicQuat64 FDeterministicTransform64::InverseTransformRotation(const FDeterministicQuat64& Q) const
{
	return GetRotation().Inverse() * Q;
}

FORCEINLINE FDeterministicTransform64 FDeterministicTransform64::GetScaled(FDeterministicNumber64 InScale) const
{
	FDeterministicTransform64 A(*this);
	A.Scale3D *= InScale;

	return A;
}

FORCEINLINE FDeterministicTransform64 FDeterministicTransform64::GetScaled(FDeterministicVector64 InScale) const
{
	FDeterministicTransform64 A(*this);
	A.Scale3D *= InScale;

	return A;
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::GetScaledAxis(EAxis::Type InAxis) const
{
	if (InAxis == EAxis::X)
	{
		return TransformVector(FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero));
	}
	else if (InAxis == EAxis::Y)
	{
		return TransformVector(FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero));
	}

	return TransformVector(FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One));
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::GetUnitAxis(EAxis::Type InAxis) const
{
	if (InAxis == EAxis::X)
	{
		return TransformVectorNoScale(FDeterministicVector64(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero));
	}
	else if (InAxis == EAxis::Y)
	{
		return TransformVectorNoScale(FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::Zero));
	}

	return TransformVectorNoScale(FDeterministicVector64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One));
}

FORCEINLINE void FDeterministicTransform64::Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis)
{
	// We do convert to Matrix for mirroring. 
	FDeterministicMatrix64 M = ToMatrixWithScale();
	M.Mirror(MirrorAxis, FlipAxis);
	SetFromMatrix(M);
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::GetSafeScaleReciprocal(const FDeterministicVector64& InScale, FDeterministicNumber64 Tolerance)
{
	FDeterministicVector64 SafeReciprocalScale;
	if (FDeterministicFloatMath::Abs(InScale.X) <= Tolerance)
	{
		SafeReciprocalScale.X = DeterministicFloat::Constants::Number64::Zero;
	}
	else
	{
		SafeReciprocalScale.X = DeterministicFloat::Constants::Number64::One / InScale.X;
	}

	if (FDeterministicFloatMath::Abs(InScale.Y) <= Tolerance)
	{
		SafeReciprocalScale.Y = DeterministicFloat::Constants::Number64::Zero;
	}
	else
	{
		SafeReciprocalScale.Y = DeterministicFloat::Constants::Number64::One / InScale.Y;
	}

	if (FDeterministicFloatMath::Abs(InScale.Z) <= Tolerance)
	{
		SafeReciprocalScale.Z = DeterministicFloat::Constants::Number64::Zero;
	}
	else
	{
		SafeReciprocalScale.Z = DeterministicFloat::Constants::Number64::One / InScale.Z;
	}

	return SafeReciprocalScale;
}

// temp function for easy conversion
FORCEINLINE FDeterministicVector64 FDeterministicTransform64::GetLocation() const
{
	return GetTranslation();
}

FORCEINLINE FDeterministicRotator64 FDeterministicTransform64::Rotator() const
{
	return Rotation.Rotator();
}

/** Calculate the determinant of this transformation */
FORCEINLINE FDeterministicNumber64 FDeterministicTransform64::GetDeterminant() const
{
	return Scale3D.X * Scale3D.Y * Scale3D.Z;
}

/** Set the translation of this transformation */
FORCEINLINE void FDeterministicTransform64::SetLocation(const FDeterministicVector64& Origin)
{
	Translation = Origin;
}

/**
* Checks the components for non-finite values (NaN or Inf).
* @return Returns true if any component (rotation, translation, or scale) is not finite.
* Fixed point numbers can't be NaN
*/
FORCEINLINE bool FDeterministicTransform64::ContainsNaN() const
{
	return false;
}

inline bool FDeterministicTransform64::IsValid() const
{
	if (!Rotation.IsNormalized())
	{
		return false;
	}

	return true;
}

FORCEINLINE bool FDeterministicTransform64::Private_RotationEquals(const FDeterministicQuat64& InRotation, const FDeterministicNumber64 Tolerance) const
{
	return Rotation.Equals(InRotation, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::Private_TranslationEquals(const FDeterministicVector64& InTranslation, const FDeterministicNumber64 Tolerance) const
{
	return Translation.Equals(InTranslation, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::Private_Scale3DEquals(const FDeterministicVector64& InScale3D, const FDeterministicNumber64 Tolerance) const
{
	return Scale3D.Equals(InScale3D, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::AreRotationsEqual(const FDeterministicTransform64& A, const FDeterministicTransform64& B, FDeterministicNumber64 Tolerance)
{
	return A.Private_RotationEquals(B.Rotation, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::AreTranslationsEqual(const FDeterministicTransform64& A, const FDeterministicTransform64& B, FDeterministicNumber64 Tolerance)
{
	return A.Private_TranslationEquals(B.Translation, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::AreScale3DsEqual(const FDeterministicTransform64& A, const FDeterministicTransform64& B, FDeterministicNumber64 Tolerance)
{
	return A.Private_Scale3DEquals(B.Scale3D, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::RotationEquals(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance) const
{
	return AreRotationsEqual(*this, Other, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::TranslationEquals(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance) const
{
	return AreTranslationsEqual(*this, Other, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::Scale3DEquals(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance) const
{
	return AreScale3DsEqual(*this, Other, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::Equals(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance) const
{
	return Private_TranslationEquals(Other.Translation, Tolerance) && Private_RotationEquals(Other.Rotation, Tolerance) && Private_Scale3DEquals(Other.Scale3D, Tolerance);
}

FORCEINLINE bool FDeterministicTransform64::Identical(const FDeterministicTransform64* Other, uint32 PortFlags) const
{
	return Equals(*Other, DeterministicFloat::Constants::Number64::Zero);
}

FORCEINLINE bool FDeterministicTransform64::EqualsNoScale(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance) const
{
	return Private_TranslationEquals(Other.Translation, Tolerance) && Private_RotationEquals(Other.Rotation, Tolerance);
}

FORCEINLINE void FDeterministicTransform64::Multiply(FDeterministicTransform64* OutTransform, const FDeterministicTransform64* A, const FDeterministicTransform64* B)
{
	checkSlow(A->IsRotationNormalized());
	checkSlow(B->IsRotationNormalized());

	//	When Q = quaternion, S = single scalar scale, and T = translation
	//	QST(A) = Q(A), S(A), T(A), and QST(B) = Q(B), S(B), T(B)

	//	QST (AxB) 

	// QST(A) = Q(A)*S(A)*P*-Q(A) + T(A)
	// QST(AxB) = Q(B)*S(B)*QST(A)*-Q(B) + T(B)
	// QST(AxB) = Q(B)*S(B)*[Q(A)*S(A)*P*-Q(A) + T(A)]*-Q(B) + T(B)
	// QST(AxB) = Q(B)*S(B)*Q(A)*S(A)*P*-Q(A)*-Q(B) + Q(B)*S(B)*T(A)*-Q(B) + T(B)
	// QST(AxB) = [Q(B)*Q(A)]*[S(B)*S(A)]*P*-[Q(B)*Q(A)] + Q(B)*S(B)*T(A)*-Q(B) + T(B)

	//	Q(AxB) = Q(B)*Q(A)
	//	S(AxB) = S(A)*S(B)
	//	T(AxB) = Q(B)*S(B)*T(A)*-Q(B) + T(B)

	if (AnyHasNegativeScale(A->Scale3D, B->Scale3D))
	{
		// @note, if you have 0 scale with negative, you're going to lose rotation as it can't convert back to quat
		MultiplyUsingMatrixWithScale(OutTransform, A, B);
	}
	else
	{
		OutTransform->Rotation = B->Rotation * A->Rotation;
		OutTransform->Scale3D = A->Scale3D * B->Scale3D;
		OutTransform->Translation = B->Rotation * (B->Scale3D * A->Translation) + B->Translation;
	}

	// we do not support matrix transform when non-uniform
	// that was removed at rev 21 with UE4
}

FORCEINLINE void FDeterministicTransform64::SetComponents(const FDeterministicQuat64& InRotation, const FDeterministicVector64& InTranslation, const FDeterministicVector64& InScale3D)
{
	Rotation = InRotation;
	Translation = InTranslation;
	Scale3D = InScale3D;
}

FORCEINLINE void FDeterministicTransform64::SetIdentity()
{
	Rotation = FDeterministicQuat64::Identity;
	Translation = FDeterministicVector64::ZeroVector;
	Scale3D = FDeterministicVector64(1, 1, 1);
}

FORCEINLINE void FDeterministicTransform64::SetIdentityZeroScale()
{
	Rotation = FDeterministicQuat64::Identity;
	Translation = FDeterministicVector64::ZeroVector;
	Scale3D = FDeterministicVector64::ZeroVector;
}

FORCEINLINE void FDeterministicTransform64::MultiplyScale3D(const FDeterministicVector64& Scale3DMultiplier)
{
	Scale3D *= Scale3DMultiplier;
}

FORCEINLINE void FDeterministicTransform64::SetTranslation(const FDeterministicVector64& NewTranslation)
{
	Translation = NewTranslation;
}

FORCEINLINE void FDeterministicTransform64::CopyTranslation(const FDeterministicTransform64& Other)
{
	Translation = Other.Translation;
}

FORCEINLINE void FDeterministicTransform64::ConcatenateRotation(const FDeterministicQuat64& DeltaRotation)
{
	Rotation = Rotation * DeltaRotation;
}

FORCEINLINE void FDeterministicTransform64::AddToTranslation(const FDeterministicVector64& DeltaTranslation)
{
	Translation += DeltaTranslation;
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::AddTranslations(const FDeterministicTransform64& A, const FDeterministicTransform64& B)
{
	return A.Translation + B.Translation;
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::SubtractTranslations(const FDeterministicTransform64& A, const FDeterministicTransform64& B)
{
	return A.Translation - B.Translation;
}

FORCEINLINE void FDeterministicTransform64::SetRotation(const FDeterministicQuat64& NewRotation)
{
	Rotation = NewRotation;
}

FORCEINLINE void FDeterministicTransform64::CopyRotation(const FDeterministicTransform64& Other)
{
	Rotation = Other.Rotation;
}

FORCEINLINE void FDeterministicTransform64::SetScale3D(const FDeterministicVector64& NewScale3D)
{
	Scale3D = NewScale3D;
}

FORCEINLINE void FDeterministicTransform64::CopyScale3D(const FDeterministicTransform64& Other)
{
	Scale3D = Other.Scale3D;
}

FORCEINLINE void FDeterministicTransform64::SetTranslationAndScale3D(const FDeterministicVector64& NewTranslation, const FDeterministicVector64& NewScale3D)
{
	Translation = NewTranslation;
	Scale3D = NewScale3D;
}

FORCEINLINE TVectorRegisterType<double> FDeterministicTransform64::GetTranslationRegister() const
{
	FVector floattranslation = (FVector)Translation;
	return VectorLoadFloat3_W0(&floattranslation); 
}

FORCEINLINE TVectorRegisterType<double> FDeterministicTransform64::GetRotationRegister() const
{ 
	FQuat floatrotation = (FQuat)Rotation;
	return VectorLoad(&floatrotation); 
}

FORCEINLINE void FDeterministicTransform64::SetTranslationRegister(TVectorRegisterType<double> InTranslation)
{ 
	FVector newval;
	VectorStoreFloat3(InTranslation, &newval);
	Translation = (FDeterministicVector64)newval;
}

FORCEINLINE void FDeterministicTransform64::SetRotationRegister(TVectorRegisterType<double> InRotation)
{
	FQuat newval;
	VectorStore(InRotation, &newval);
	Rotation = (FDeterministicQuat64)newval;
}

FORCEINLINE void FDeterministicTransform64::Accumulate(const FDeterministicTransform64& SourceAtom)
{
	// Add ref pose relative animation to base animation, only if rotation is significant.
	if (FDeterministicFloatMath::Square(SourceAtom.Rotation.W) < FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value - DeterministicFloat::Constants::Number64::Delta.Value))
	{
		Rotation = SourceAtom.Rotation * Rotation;
	}

	Translation += SourceAtom.Translation;
	Scale3D *= SourceAtom.Scale3D;

	DiagnosticCheckNaN_All();

	checkSlow(IsRotationNormalized());
}

FORCEINLINE void FDeterministicTransform64::Accumulate(const FDeterministicTransform64& Atom, FDeterministicNumber64 BlendWeight/* default param doesn't work since vectorized version takes ref param */)
{
	FDeterministicTransform64 SourceAtom(Atom * BlendWeight);

	// Add ref pose relative animation to base animation, only if rotation is significant.
	if (FDeterministicFloatMath::Square(SourceAtom.Rotation.W) < FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value - DeterministicFloat::Constants::Number64::Delta.Value))
	{
		Rotation = SourceAtom.Rotation * Rotation;
	}

	Translation += SourceAtom.Translation;
	Scale3D *= SourceAtom.Scale3D;

	DiagnosticCheckNaN_All();
}

FORCEINLINE void FDeterministicTransform64::AccumulateWithShortestRotation(const FDeterministicTransform64& DeltaAtom, FDeterministicNumber64 BlendWeight/* default param doesn't work since vectorized version takes ref param */)
{
	FDeterministicTransform64 Atom(DeltaAtom * BlendWeight);

	// To ensure the 'shortest route', we make sure the dot product between the accumulator and the incoming child atom is positive.
	if ((Atom.Rotation | Rotation) < DeterministicFloat::Constants::Number64::Zero)
	{
		Rotation.X -= Atom.Rotation.X;
		Rotation.Y -= Atom.Rotation.Y;
		Rotation.Z -= Atom.Rotation.Z;
		Rotation.W -= Atom.Rotation.W;
	}
	else
	{
		Rotation.X += Atom.Rotation.X;
		Rotation.Y += Atom.Rotation.Y;
		Rotation.Z += Atom.Rotation.Z;
		Rotation.W += Atom.Rotation.W;
	}

	Translation += Atom.Translation;
	Scale3D += Atom.Scale3D;

	DiagnosticCheckNaN_All();
}

FORCEINLINE void FDeterministicTransform64::AccumulateWithAdditiveScale(const FDeterministicTransform64& Atom, FDeterministicNumber64 BlendWeight/* default param doesn't work since vectorized version takes ref param */)
{
	const FDeterministicVector64 DefaultScale(FDeterministicVector64::OneVector);

	FDeterministicTransform64 SourceAtom(Atom * BlendWeight);

	// Add ref pose relative animation to base animation, only if rotation is significant.
	if (FDeterministicFloatMath::Square(SourceAtom.Rotation.W) < FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value - DeterministicFloat::Constants::Number64::Delta.Value))
	{
		Rotation = SourceAtom.Rotation * Rotation;
	}

	Translation += SourceAtom.Translation;
	Scale3D *= (DefaultScale + SourceAtom.Scale3D);
}
	
FORCEINLINE void FDeterministicTransform64::LerpTranslationScale3D(const FDeterministicTransform64& SourceAtom1, const FDeterministicTransform64& SourceAtom2, FDeterministicNumber64 Alpha)
{
	Translation = FDeterministicFloatMath::Lerp(SourceAtom1.Translation, SourceAtom2.Translation, Alpha);
	Scale3D = FDeterministicFloatMath::Lerp(SourceAtom1.Scale3D, SourceAtom2.Scale3D, Alpha);
}

FORCEINLINE void FDeterministicTransform64::NormalizeRotation()
{
	Rotation.Normalize();
}

FORCEINLINE bool FDeterministicTransform64::IsRotationNormalized() const
{
	return Rotation.IsNormalized();
}

FORCEINLINE void FDeterministicTransform64::BlendFromIdentityAndAccumulate(FDeterministicTransform64& FinalAtom, const FDeterministicTransform64& SourceAtom, FDeterministicNumber64 BlendWeight)
{
	const FDeterministicTransform64 AdditiveIdentity(FDeterministicQuat64::Identity, FDeterministicVector64::ZeroVector, FDeterministicVector64::ZeroVector);
	const FDeterministicVector64 DefaultScale(FDeterministicVector64::OneVector);
	FDeterministicTransform64 DeltaAtom = SourceAtom;

	// Scale delta by weight
	if (BlendWeight < (DeterministicFloat::Constants::Number64::One - DeterministicFloat::Constants::Number64::ZeroAnimWeightThresh))
	{
		DeltaAtom.Blend(AdditiveIdentity, DeltaAtom, BlendWeight);
	}

	// Add ref pose relative animation to base animation, only if rotation is significant.
	if (FMath::Square(DeltaAtom.Rotation.W) < FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value - DeterministicFloat::Constants::Number64::Delta.Value))
	{
		FinalAtom.Rotation = DeltaAtom.Rotation * FinalAtom.Rotation;
	}

	FinalAtom.Translation += DeltaAtom.Translation;
	FinalAtom.Scale3D *= (DefaultScale + DeltaAtom.Scale3D);

	checkSlow(FinalAtom.IsRotationNormalized());
}

FORCEINLINE FDeterministicQuat64 FDeterministicTransform64::GetRotation() const
{
	return Rotation;
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::GetTranslation() const
{
	return Translation;
}

FORCEINLINE FDeterministicVector64 FDeterministicTransform64::GetScale3D() const
{
	return Scale3D;
}

FORCEINLINE void FDeterministicTransform64::CopyRotationPart(const FDeterministicTransform64& SrcBA)
{
	Rotation = SrcBA.Rotation;
	Scale3D = SrcBA.Scale3D;
}

FORCEINLINE void FDeterministicTransform64::CopyTranslationAndScale3D(const FDeterministicTransform64& SrcBA)
{
	Translation = SrcBA.Translation;
	Scale3D = SrcBA.Scale3D;
}

FORCEINLINE void FDeterministicTransform64::SetFromMatrix(const FDeterministicMatrix64& InMatrix)
{
	FDeterministicMatrix64 M = InMatrix;

	// Get the 3D scale from the matrix
	Scale3D = M.ExtractScaling();

	// If there is negative scaling going on, we handle that here
	if (InMatrix.Determinant() < DeterministicFloat::Constants::Number64::Zero)
	{
		// Assume it is along X and modify transform accordingly. 
		// It doesn't actually matter which axis we choose, the 'appearance' will be the same
		Scale3D.X *= -DeterministicFloat::Constants::Number64::One;
		M.SetAxis(DeterministicFloat::Constants::Number64::Zero, -M.GetScaledAxis(EAxis::X));
	}

	Rotation = FDeterministicQuat64(M);
	Translation = InMatrix.GetOrigin();

	// Normalize rotation
	Rotation.Normalize();
}

FORCEINLINE void FDeterministicTransform64::MultiplyUsingMatrixWithScale(FDeterministicTransform64* OutTransform, const FDeterministicTransform64* A, const FDeterministicTransform64* B)
{
	// the goal of using M is to get the correct orientation
	// but for translation, we still need scale
	ConstructTransformFromMatrixWithDesiredScale(A->ToMatrixWithScale(), B->ToMatrixWithScale(), A->Scale3D * B->Scale3D, *OutTransform);
}

FORCEINLINE void FDeterministicTransform64::ConstructTransformFromMatrixWithDesiredScale(const FDeterministicMatrix64& AMatrix, const FDeterministicMatrix64& BMatrix, const FDeterministicVector64& DesiredScale, FDeterministicTransform64& OutTransform)
{
	// the goal of using M is to get the correct orientation
	// but for translation, we still need scale
	FDeterministicMatrix64 M = AMatrix * BMatrix;
	M.RemoveScaling();

	// apply negative scale back to axes
	FDeterministicVector64 SignedScale = DesiredScale.GetSignVector();

	M.SetAxis(0, SignedScale.X * M.GetScaledAxis(EAxis::X));
	M.SetAxis(1, SignedScale.Y * M.GetScaledAxis(EAxis::Y));
	M.SetAxis(2, SignedScale.Z * M.GetScaledAxis(EAxis::Z));

	// @note: if you have negative with 0 scale, this will return rotation that is identity
	// since matrix loses that axes
	FDeterministicQuat64 Rotation = FDeterministicQuat64(M);
	Rotation.Normalize();

	// set values back to output
	OutTransform.Scale3D = DesiredScale;
	OutTransform.Rotation = Rotation;

	// technically I could calculate this using FDeterministicTransform64 but then it does more quat multiplication 
	// instead of using Scale in matrix multiplication
	// it's a question of between RemoveScaling vs using FDeterministicTransform64 to move translation
	OutTransform.Translation = M.GetOrigin();
}
