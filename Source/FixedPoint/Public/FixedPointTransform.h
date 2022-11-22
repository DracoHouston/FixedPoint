// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/AssertionMacros.h"
#include "FixedPointFwd.h"
#include "FixedPointNumbers.h"
#include "FixedPointVector.h"
#include "FixedPointQuat.h"
#include "FixedPointRotator.h"
#include "FixedPointVector4.h"
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

	/** Set this Transform to the weighted blend of it and the supplied Transform. */
	FORCEINLINE void BlendWith(const FFixedTransform& OtherAtom, FFixed64 Alpha)
	{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) && WITH_EDITORONLY_DATA
		// Check that all bone atoms coming from animation are normalized
		check(IsRotationNormalized());
		check(OtherAtom.IsRotationNormalized());
#endif
		if (Alpha > FixedPoint::Constants::Fixed64::ZeroAnimWeightThresh)
		{
			if (Alpha >= FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::ZeroAnimWeightThresh)
			{
				// if blend is all the way for child2, then just copy its bone atoms
				(*this) = OtherAtom;
			}
			else
			{
				// Simple linear interpolation for translation and scale.
				Translation = FFixedPointMath::Lerp(Translation, OtherAtom.Translation, Alpha);
				Scale3D = FFixedPointMath::Lerp(Scale3D, OtherAtom.Scale3D, Alpha);
				Rotation = FFixedQuat::FastLerp(Rotation, OtherAtom.Rotation, Alpha);

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
	FORCEINLINE FFixedTransform operator+(const FFixedTransform& Atom) const
	{
		return FFixedTransform(Rotation + Atom.Rotation, Translation + Atom.Translation, Scale3D + Atom.Scale3D);
	}

	FORCEINLINE FFixedTransform& operator+=(const FFixedTransform& Atom)
	{
		Translation += Atom.Translation;

		Rotation.X += Atom.Rotation.X;
		Rotation.Y += Atom.Rotation.Y;
		Rotation.Z += Atom.Rotation.Z;
		Rotation.W += Atom.Rotation.W;

		Scale3D += Atom.Scale3D;

		return *this;
	}

	FORCEINLINE FFixedTransform operator*(FFixed64 Mult) const
	{
		return FFixedTransform(Rotation * Mult, Translation * Mult, Scale3D * Mult);
	}

	FORCEINLINE FFixedTransform& operator*=(FFixed64 Mult)
	{
		Translation *= Mult;
		Rotation.X *= Mult;
		Rotation.Y *= Mult;
		Rotation.Z *= Mult;
		Rotation.W *= Mult;
		Scale3D *= Mult;

		return *this;
	}

	/**
	* Return a transform that is the result of this multiplied by another transform.
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other transform by which to multiply.
	* @return new transform: this * Other
	*/
	FORCEINLINE FFixedTransform operator*(const FFixedTransform& Other) const
	{
		FFixedTransform Output;
		Multiply(&Output, this, &Other);
		return Output;
	}

	/**
	* Sets this transform to the result of this multiplied by another transform.
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other transform by which to multiply.
	*/
	FORCEINLINE void operator*=(const FFixedTransform& Other)
	{
		Multiply(this, this, &Other);
	}

	/**
	* Return a transform that is the result of this multiplied by another transform (made only from a rotation).
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other quaternion rotation by which to multiply.
	* @return new transform: this * TTransform(Other)
	*/
	FORCEINLINE FFixedTransform operator*(const FFixedQuat& Other) const
	{
		FFixedTransform Output, OtherTransform(Other, FFixedVector::ZeroVector, FFixedVector::OneVector);
		Multiply(&Output, this, &OtherTransform);
		return Output;
	}

	/**
	* Sets this transform to the result of this multiplied by another transform (made only from a rotation).
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other quaternion rotation by which to multiply.
	*/
	FORCEINLINE void operator*=(const FFixedQuat& Other)
	{
		FFixedTransform OtherTransform(Other, FFixedVector::ZeroVector, FFixedVector::OneVector);
		Multiply(this, this, &OtherTransform);
	}

	FORCEINLINE static bool AnyHasNegativeScale(const FFixedVector& InScale3D, const FFixedVector& InOtherScale3D)
	{
		return  (InScale3D.X < FixedPoint::Constants::Fixed64::Zero || InScale3D.Y < FixedPoint::Constants::Fixed64::Zero || InScale3D.Z < FixedPoint::Constants::Fixed64::Zero
			|| InOtherScale3D.X < FixedPoint::Constants::Fixed64::Zero || InOtherScale3D.Y < FixedPoint::Constants::Fixed64::Zero || InOtherScale3D.Z < FixedPoint::Constants::Fixed64::Zero);
	}

	FORCEINLINE void ScaleTranslation(const FFixedVector& InScale3D)
	{
		Translation *= InScale3D;
	}

	FORCEINLINE void ScaleTranslation(const FFixed64& Scale)
	{
		Translation *= Scale;
	}

	FORCEINLINE void RemoveScaling(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		Scale3D = FFixedVector::OneVector;
		Rotation.Normalize();
	}

	FORCEINLINE FFixed64 GetMaximumAxisScale() const
	{
		return Scale3D.GetAbsMax();
	}

	FORCEINLINE FFixed64 GetMinimumAxisScale() const
	{
		return Scale3D.GetAbsMin();
	}

	// Inverse does not work well with VQS format(in particular non-uniform), so removing it, but made two below functions to be used instead. 

	/*******************************************************************************************
	* The below 2 functions are the ones to get delta transform and return TTransform<T> format that can be concatenated
	* Inverse itself can't concatenate with VQS format(since VQS always transform from S->Q->T, where inverse happens from T(-1)->Q(-1)->S(-1))
	* So these 2 provides ways to fix this
	* GetRelativeTransform returns this*Other(-1) and parameter is Other(not Other(-1))
	* GetRelativeTransformReverse returns this(-1)*Other, and parameter is Other.
	*******************************************************************************************/
	FFixedTransform GetRelativeTransform(const FFixedTransform& Other) const;
	FFixedTransform GetRelativeTransformReverse(const FFixedTransform& Other) const;

	/**
	* Set current transform and the relative to ParentTransform.
	* Equates to This = This->GetRelativeTransform(Parent), but saves the intermediate TTransform<T> storage and copy.
	*/
	void SetToRelativeTransform(const FFixedTransform& ParentTransform);

	FORCEINLINE FFixedVector4d TransformFVector4(const FFixedVector4d& V) const
	{
		DiagnosticCheckNaN_All();

		// if not, this won't work
		checkSlow(V.W == FixedPoint::Constants::Fixed64::Zero || V.W == FixedPoint::Constants::Fixed64::One);

		//Transform using QST is following
		//QST(P) = Q*S*P*-Q + T where Q = quaternion, S = scale, T = translation

		FFixedVector4d Transform = FFixedVector4d(Rotation.RotateVector(Scale3D * FFixedVector(V)), FixedPoint::Constants::Fixed64::Zero);
		if (V.W == FixedPoint::Constants::Fixed64::One)
		{
			Transform += FFixedVector4d(Translation, FixedPoint::Constants::Fixed64::One);
		}

		return Transform;
	}

	FORCEINLINE FFixedVector4d TransformFVector4NoScale(const FFixedVector4d& V) const
	{
		DiagnosticCheckNaN_All();

		// if not, this won't work
		checkSlow(V.W == 0.f || V.W == 1.f);

		//Transform using QST is following
		//QST(P) = Q*S*P*-Q + T where Q = quaternion, S = scale, T = translation
		FFixedVector4d Transform = FFixedVector4d(Rotation.RotateVector(FFixedVector(V)), FixedPoint::Constants::Fixed64::Zero);
		if (V.W == FixedPoint::Constants::Fixed64::One)
		{
			Transform += FFixedVector4d(Translation, FixedPoint::Constants::Fixed64::One);
		}

		return Transform;
	}

	FORCEINLINE FFixedVector TransformPosition(const FFixedVector& V) const
	{
		return Rotation.RotateVector(Scale3D * V) + Translation;
	}

	FORCEINLINE FFixedVector TransformPositionNoScale(const FFixedVector& V) const
	{
		return Rotation.RotateVector(V) + Translation;
	}

	/** Inverts the transform and then transforms V - correctly handles scaling in this transform. */
	FORCEINLINE FFixedVector InverseTransformPosition(const FFixedVector& V) const
	{
		return (Rotation.UnrotateVector(V - Translation)) * GetSafeScaleReciprocal(Scale3D);
	}


	FORCEINLINE FFixedVector InverseTransformPositionNoScale(const FFixedVector& V) const
	{
		return (Rotation.UnrotateVector(V - Translation));
	}


	FORCEINLINE FFixedVector TransformVector(const FFixedVector& V) const
	{
		return Rotation.RotateVector(Scale3D * V);
	}

	FORCEINLINE FFixedVector TransformVectorNoScale(const FFixedVector& V) const
	{
		return Rotation.RotateVector(V);
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
	* Create a new transform: OutTransform = A * B.
	*
	* Order matters when composing transforms : A * B will yield a transform that logically first applies A then B to any subsequent transformation.
	*
	* @param  OutTransform pointer to transform that will store the result of A * B.
	* @param  A Transform A.
	* @param  B Transform B.
	*/
	FORCEINLINE static void Multiply(FFixedTransform* OutTransform, const FFixedTransform* A, const FFixedTransform* B)
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
private:
	/**
	* Create a new transform: OutTransform = A * B using the matrix while keeping the scale that's given by A and B
	* Please note that this operation is a lot more expensive than normal Multiply
	*
	* Order matters when composing transforms : A * B will yield a transform that logically first applies A then B to any subsequent transformation.
	*
	* @param  OutTransform pointer to transform that will store the result of A * B.
	* @param  A Transform A.
	* @param  B Transform B.
	*/
	FORCEINLINE static void MultiplyUsingMatrixWithScale(FFixedTransform* OutTransform, const FFixedTransform* A, const FFixedTransform* B)
	{
		// the goal of using M is to get the correct orientation
		// but for translation, we still need scale
		ConstructTransformFromMatrixWithDesiredScale(A->ToMatrixWithScale(), B->ToMatrixWithScale(), A->Scale3D * B->Scale3D, *OutTransform);
	}

	/**
	* Create a new transform from multiplications of given to matrices (AMatrix*BMatrix) using desired scale
	* This is used by MultiplyUsingMatrixWithScale and GetRelativeTransformUsingMatrixWithScale
	* This is only used to handle negative scale
	*
	* @param	AMatrix first Matrix of operation
	* @param	BMatrix second Matrix of operation
	* @param	DesiredScale - there is no check on if the magnitude is correct here. It assumes that is correct.
	* @param	OutTransform the constructed transform
	*/

	FORCEINLINE static void ConstructTransformFromMatrixWithDesiredScale(const FFixedMatrix& AMatrix, const FFixedMatrix& BMatrix, const FFixedVector& DesiredScale, FFixedTransform& OutTransform)
	{
		// the goal of using M is to get the correct orientation
		// but for translation, we still need scale
		FFixedMatrix M = AMatrix * BMatrix;
		M.RemoveScaling();

		// apply negative scale back to axes
		FFixedVector SignedScale = DesiredScale.GetSignVector();

		M.SetAxis(0, SignedScale.X * M.GetScaledAxis(EAxis::X));
		M.SetAxis(1, SignedScale.Y * M.GetScaledAxis(EAxis::Y));
		M.SetAxis(2, SignedScale.Z * M.GetScaledAxis(EAxis::Z));

		// @note: if you have negative with 0 scale, this will return rotation that is identity
		// since matrix loses that axes
		FFixedQuat Rotation = FFixedQuat(M);
		Rotation.Normalize();

		// set values back to output
		OutTransform.Scale3D = DesiredScale;
		OutTransform.Rotation = Rotation;

		// technically I could calculate this using TTransform<T> but then it does more quat multiplication 
		// instead of using Scale in matrix multiplication
		// it's a question of between RemoveScaling vs using TTransform<T> to move translation
		OutTransform.Translation = M.GetOrigin();
	}

	/**
	* Create a new transform: OutTransform = Base * Relative(-1) using the matrix while keeping the scale that's given by Base and Relative
	* Please note that this operation is a lot more expensive than normal GetRelativeTrnasform
	*
	* @param  OutTransform pointer to transform that will store the result of Base * Relative(-1).
	* @param  BAse Transform Base.
	* @param  Relative Transform Relative.
	*/
	static void GetRelativeTransformUsingMatrixWithScale(FFixedTransform* OutTransform, const FFixedTransform* Base, const FFixedTransform* Relative);
};
