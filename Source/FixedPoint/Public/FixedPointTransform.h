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
#include "Math/VectorRegister.h"
#include "Math/ScalarRegister.h"
#include "FixedPointTransform.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedTransform64
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
	FFixedQuat64 Rotation;
	/** Translation of this transformation, as a vector. */
	FFixedVector64 Translation;
	/** 3D scale (always applied in local space) as a vector. */
	FFixedVector64 Scale3D;
public:
	/** Default constructor. */
	FORCEINLINE FFixedTransform64()
	: Rotation(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One)
	, Translation(FixedPoint::Constants::Fixed64::Zero)
	, Scale3D(FFixedVector64::OneVector)
	{
	}

	FORCEINLINE FFixedTransform64(const FTransform& Other)
	{
		Translation = Other.GetTranslation();
		Scale3D = Other.GetScale3D();
		Rotation = Other.GetRotation();
	}

	/**
	* Constructor with an initial translation
	*
	* @param InTranslation The value to use for the translation component
	*/
	FORCEINLINE explicit FFixedTransform64(const FFixedVector64& InTranslation)
		: Rotation(FFixedQuat64::Identity),
		Translation(InTranslation),
		Scale3D(FFixedVector64::OneVector)
	{
	}

	/**
	* Constructor with leaving uninitialized memory
	*/
	FORCEINLINE explicit FFixedTransform64(ENoInit){}

	/**
	* Constructor with an initial rotation
	*
	* @param InRotation The value to use for rotation component
	*/
	FORCEINLINE explicit FFixedTransform64(const FFixedQuat64& InRotation)
		: Rotation(InRotation),
		Translation(FFixedVector64::ZeroVector),
		Scale3D(FFixedVector64::OneVector)
	{
	}

	/**
	* Constructor with an initial rotation
	*
	* @param InRotation The value to use for rotation component  (after being converted to a quaternion)
	*/
	FORCEINLINE explicit FFixedTransform64(const FFixedRotator64& InRotation)
		: Rotation(InRotation),
		Translation(FFixedVector64::ZeroVector),
		Scale3D(FFixedVector64::OneVector)
	{
	}

	/**
	* Constructor with all components initialized
	*
	* @param InRotation The value to use for rotation component
	* @param InTranslation The value to use for the translation component
	* @param InScale3D The value to use for the scale component
	*/
	FORCEINLINE FFixedTransform64(const FFixedQuat64& InRotation, const FFixedVector64& InTranslation, const FFixedVector64& InScale3D = FFixedVector64::OneVector)
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
	FORCEINLINE FFixedTransform64(const FFixedRotator64& InRotation, const FFixedVector64& InTranslation, const FFixedVector64& InScale3D = FFixedVector64::OneVector)
		: Rotation(InRotation),
		Translation(InTranslation),
		Scale3D(InScale3D)
	{
	}

	/**
	* Constructor for converting a Matrix (including scale) into a FFixedTransform64.
	*/
	FORCEINLINE explicit FFixedTransform64(const FFixedMatrix& InMatrix)
	{
		SetFromMatrix(InMatrix);
	}

	/** Constructor that takes basis axes and translation */
	FORCEINLINE FFixedTransform64(const FFixedVector64& InX, const FFixedVector64& InY, const FFixedVector64& InZ, const FFixedVector64& InTranslation)
	{
		SetFromMatrix(FFixedMatrix(InX, InY, InZ, InTranslation));
	}

	static const FFixedTransform64 Identity;

	/**
	* Does a debugf of the contents of this Transform.
	*/
	void DebugPrint() const;

	/** Debug purpose only **/
	bool DebugEqualMatrix(const FFixedMatrix& Matrix) const;

	/** Convert FFixedTransform64 contents to a string */
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
	FORCEINLINE FFixedTransform64 Inverse() const
	{
		FFixedQuat64   InvRotation = Rotation.Inverse();
		// this used to cause NaN if Scale contained 0 
		FFixedVector64 InvScale3D = GetSafeScaleReciprocal(Scale3D);
		FFixedVector64 InvTranslation = InvRotation * (InvScale3D * -Translation);

		return FFixedTransform64(InvRotation, InvTranslation, InvScale3D);
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
	FORCEINLINE void Blend(const FFixedTransform64& Atom1, const FFixedTransform64& Atom2, FFixed64 Alpha)
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
			Rotation = FFixedQuat64::FastLerp(Atom1.Rotation, Atom2.Rotation, Alpha);

			// ..and renormalize
			Rotation.Normalize();
		}
	}

	/** Set this Transform to the weighted blend of it and the supplied Transform. */
	FORCEINLINE void BlendWith(const FFixedTransform64& OtherAtom, FFixed64 Alpha)
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
				Rotation = FFixedQuat64::FastLerp(Rotation, OtherAtom.Rotation, Alpha);

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
	FORCEINLINE FFixedTransform64 operator+(const FFixedTransform64& Atom) const
	{
		return FFixedTransform64(Rotation + Atom.Rotation, Translation + Atom.Translation, Scale3D + Atom.Scale3D);
	}

	FORCEINLINE FFixedTransform64& operator+=(const FFixedTransform64& Atom)
	{
		Translation += Atom.Translation;

		Rotation.X += Atom.Rotation.X;
		Rotation.Y += Atom.Rotation.Y;
		Rotation.Z += Atom.Rotation.Z;
		Rotation.W += Atom.Rotation.W;

		Scale3D += Atom.Scale3D;

		return *this;
	}

	FORCEINLINE FFixedTransform64 operator*(FFixed64 Mult) const
	{
		return FFixedTransform64(Rotation * Mult, Translation * Mult, Scale3D * Mult);
	}

	FORCEINLINE FFixedTransform64& operator*=(FFixed64 Mult)
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
	FORCEINLINE FFixedTransform64 operator*(const FFixedTransform64& Other) const
	{
		FFixedTransform64 Output;
		Multiply(&Output, this, &Other);
		return Output;
	}

	/**
	* Sets this transform to the result of this multiplied by another transform.
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other transform by which to multiply.
	*/
	FORCEINLINE void operator*=(const FFixedTransform64& Other)
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
	FORCEINLINE FFixedTransform64 operator*(const FFixedQuat64& Other) const
	{
		FFixedTransform64 Output, OtherTransform(Other, FFixedVector64::ZeroVector, FFixedVector64::OneVector);
		Multiply(&Output, this, &OtherTransform);
		return Output;
	}

	/**
	* Sets this transform to the result of this multiplied by another transform (made only from a rotation).
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other quaternion rotation by which to multiply.
	*/
	FORCEINLINE void operator*=(const FFixedQuat64& Other)
	{
		FFixedTransform64 OtherTransform(Other, FFixedVector64::ZeroVector, FFixedVector64::OneVector);
		Multiply(this, this, &OtherTransform);
	}

	FORCEINLINE static bool AnyHasNegativeScale(const FFixedVector64& InScale3D, const FFixedVector64& InOtherScale3D)
	{
		return  (InScale3D.X < FixedPoint::Constants::Fixed64::Zero || InScale3D.Y < FixedPoint::Constants::Fixed64::Zero || InScale3D.Z < FixedPoint::Constants::Fixed64::Zero
			|| InOtherScale3D.X < FixedPoint::Constants::Fixed64::Zero || InOtherScale3D.Y < FixedPoint::Constants::Fixed64::Zero || InOtherScale3D.Z < FixedPoint::Constants::Fixed64::Zero);
	}

	FORCEINLINE void ScaleTranslation(const FFixedVector64& InScale3D)
	{
		Translation *= InScale3D;
	}

	FORCEINLINE void ScaleTranslation(const FFixed64& Scale)
	{
		Translation *= Scale;
	}

	FORCEINLINE void RemoveScaling(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		Scale3D = FFixedVector64::OneVector;
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
	* The below 2 functions are the ones to get delta transform and return FFixedTransform64 format that can be concatenated
	* Inverse itself can't concatenate with VQS format(since VQS always transform from S->Q->T, where inverse happens from T(-1)->Q(-1)->S(-1))
	* So these 2 provides ways to fix this
	* GetRelativeTransform returns this*Other(-1) and parameter is Other(not Other(-1))
	* GetRelativeTransformReverse returns this(-1)*Other, and parameter is Other.
	*******************************************************************************************/
	FFixedTransform64 GetRelativeTransform(const FFixedTransform64& Other) const;
	FFixedTransform64 GetRelativeTransformReverse(const FFixedTransform64& Other) const;

	/**
	* Set current transform and the relative to ParentTransform.
	* Equates to This = This->GetRelativeTransform(Parent), but saves the intermediate FFixedTransform64 storage and copy.
	*/
	void SetToRelativeTransform(const FFixedTransform64& ParentTransform);

	FORCEINLINE FFixedVector4d TransformFVector4(const FFixedVector4d& V) const
	{
		DiagnosticCheckNaN_All();

		// if not, this won't work
		checkSlow(V.W == FixedPoint::Constants::Fixed64::Zero || V.W == FixedPoint::Constants::Fixed64::One);

		//Transform using QST is following
		//QST(P) = Q*S*P*-Q + T where Q = quaternion, S = scale, T = translation

		FFixedVector4d Transform = FFixedVector4d(Rotation.RotateVector(Scale3D * FFixedVector64(V)), FixedPoint::Constants::Fixed64::Zero);
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
		checkSlow(V.W == FixedPoint::Constants::Fixed64::Zero || V.W == FixedPoint::Constants::Fixed64::One);

		//Transform using QST is following
		//QST(P) = Q*S*P*-Q + T where Q = quaternion, S = scale, T = translation
		FFixedVector4d Transform = FFixedVector4d(Rotation.RotateVector(FFixedVector64(V)), FixedPoint::Constants::Fixed64::Zero);
		if (V.W == FixedPoint::Constants::Fixed64::One)
		{
			Transform += FFixedVector4d(Translation, FixedPoint::Constants::Fixed64::One);
		}

		return Transform;
	}

	FORCEINLINE FFixedVector64 TransformPosition(const FFixedVector64& V) const
	{
		return Rotation.RotateVector(Scale3D * V) + Translation;
	}

	FORCEINLINE FFixedVector64 TransformPositionNoScale(const FFixedVector64& V) const
	{
		return Rotation.RotateVector(V) + Translation;
	}

	/** Inverts the transform and then transforms V - correctly handles scaling in this transform. */
	FORCEINLINE FFixedVector64 InverseTransformPosition(const FFixedVector64& V) const
	{
		return (Rotation.UnrotateVector(V - Translation)) * GetSafeScaleReciprocal(Scale3D);
	}


	FORCEINLINE FFixedVector64 InverseTransformPositionNoScale(const FFixedVector64& V) const
	{
		return (Rotation.UnrotateVector(V - Translation));
	}


	FORCEINLINE FFixedVector64 TransformVector(const FFixedVector64& V) const
	{
		return Rotation.RotateVector(Scale3D * V);
	}

	FORCEINLINE FFixedVector64 TransformVectorNoScale(const FFixedVector64& V) const
	{
		return Rotation.RotateVector(V);
	}

	/**
	*	Transform a direction vector by the inverse of this transform - will not take into account translation part.
	*	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
	*/
	FORCEINLINE FFixedVector64 InverseTransformVector(const FFixedVector64& V) const
	{
		return (Rotation.UnrotateVector(V)) * GetSafeScaleReciprocal(Scale3D);
	}

	FORCEINLINE FFixedVector64 InverseTransformVectorNoScale(const FFixedVector64& V) const
	{
		return (Rotation.UnrotateVector(V));
	}

	/**
	 * Transform a rotation.
	 * For example if this is a LocalToWorld transform, TransformRotation(Q) would transform Q from local to world space.
	 */
	FORCEINLINE FFixedQuat64 TransformRotation(const FFixedQuat64& Q) const
	{
		return GetRotation() * Q;
	}

	/**
	* Inverse transform a rotation.
	* For example if this is a LocalToWorld transform, InverseTransformRotation(Q) would transform Q from world to local space.
	*/
	FORCEINLINE FFixedQuat64 InverseTransformRotation(const FFixedQuat64& Q) const
	{
		return GetRotation().Inverse() * Q;
	}

	FORCEINLINE FFixedTransform64 GetScaled(FFixed64 InScale) const
	{
		FFixedTransform64 A(*this);
		A.Scale3D *= InScale;

		return A;
	}

	FORCEINLINE FFixedTransform64 GetScaled(FFixedVector64 InScale) const
	{
		FFixedTransform64 A(*this);
		A.Scale3D *= InScale;

		return A;
	}

	FORCEINLINE FFixedVector64 GetScaledAxis(EAxis::Type InAxis) const
	{
		if (InAxis == EAxis::X)
		{
			return TransformVector(FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero));
		}
		else if (InAxis == EAxis::Y)
		{
			return TransformVector(FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero));
		}

		return TransformVector(FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One));
	}

	FORCEINLINE FFixedVector64 GetUnitAxis(EAxis::Type InAxis) const
	{
		if (InAxis == EAxis::X)
		{
			return TransformVectorNoScale(FFixedVector64(FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero));
		}
		else if (InAxis == EAxis::Y)
		{
			return TransformVectorNoScale(FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One, FixedPoint::Constants::Fixed64::Zero));
		}

		return TransformVectorNoScale(FFixedVector64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One));
	}

	FORCEINLINE void Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis)
	{
		// We do convert to Matrix for mirroring. 
		FFixedMatrix M = ToMatrixWithScale();
		M.Mirror(MirrorAxis, FlipAxis);
		SetFromMatrix(M);
	}

	FORCEINLINE static FFixedVector64 GetSafeScaleReciprocal(const FFixedVector64& InScale, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		FFixedVector64 SafeReciprocalScale;
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

	// temp function for easy conversion
	FORCEINLINE FFixedVector64 GetLocation() const
	{
		return GetTranslation();
	}

	FORCEINLINE FFixedRotator64 Rotator() const
	{
		return Rotation.Rotator();
	}

	/** Calculate the determinant of this transformation */
	FORCEINLINE FFixed64 GetDeterminant() const
	{
		return Scale3D.X * Scale3D.Y * Scale3D.Z;
	}

	/** Set the translation of this transformation */
	FORCEINLINE void SetLocation(const FFixedVector64& Origin)
	{
		Translation = Origin;
	}

	/**
	* Checks the components for non-finite values (NaN or Inf).
	* @return Returns true if any component (rotation, translation, or scale) is not finite.
	* Fixed point numbers can't be NaN
	*/
	bool ContainsNaN() const
	{
		return false;
	}

	inline bool IsValid() const
	{
		if (!Rotation.IsNormalized())
		{
			return false;
		}

		return true;
	}

private:
	FORCEINLINE bool Private_RotationEquals(const FFixedQuat64& InRotation, const FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Rotation.Equals(InRotation, Tolerance);
	}

	FORCEINLINE bool Private_TranslationEquals(const FFixedVector64& InTranslation, const FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Translation.Equals(InTranslation, Tolerance);
	}

	FORCEINLINE bool Private_Scale3DEquals(const FFixedVector64& InScale3D, const FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Scale3D.Equals(InScale3D, Tolerance);
	}
public:

	// Test if A's rotation equals B's rotation, within a tolerance. Preferred over "A.GetRotation().Equals(B.GetRotation())" because it is faster on some platforms.
	FORCEINLINE static bool AreRotationsEqual(const FFixedTransform64& A, const FFixedTransform64& B, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber)
	{
		return A.Private_RotationEquals(B.Rotation, Tolerance);
	}

	// Test if A's translation equals B's translation, within a tolerance. Preferred over "A.GetTranslation().Equals(B.GetTranslation())" because it is faster on some platforms.
	FORCEINLINE static bool AreTranslationsEqual(const FFixedTransform64& A, const FFixedTransform64& B, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber)
	{
		return A.Private_TranslationEquals(B.Translation, Tolerance);
	}

	// Test if A's scale equals B's scale, within a tolerance. Preferred over "A.GetScale3D().Equals(B.GetScale3D())" because it is faster on some platforms.
	FORCEINLINE static bool AreScale3DsEqual(const FFixedTransform64& A, const FFixedTransform64& B, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber)
	{
		return A.Private_Scale3DEquals(B.Scale3D, Tolerance);
	}

	// Test if this Transform's rotation equals another's rotation, within a tolerance. Preferred over "GetRotation().Equals(Other.GetRotation())" because it is faster on some platforms.
	FORCEINLINE bool RotationEquals(const FFixedTransform64& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return AreRotationsEqual(*this, Other, Tolerance);
	}

	// Test if this Transform's translation equals another's translation, within a tolerance. Preferred over "GetTranslation().Equals(Other.GetTranslation())" because it is faster on some platforms.
	FORCEINLINE bool TranslationEquals(const FFixedTransform64& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return AreTranslationsEqual(*this, Other, Tolerance);
	}

	// Test if this Transform's scale equals another's scale, within a tolerance. Preferred over "GetScale3D().Equals(Other.GetScale3D())" because it is faster on some platforms.
	FORCEINLINE bool Scale3DEquals(const FFixedTransform64& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return AreScale3DsEqual(*this, Other, Tolerance);
	}

	// Test if all components of the transforms are equal, within a tolerance.
	FORCEINLINE bool Equals(const FFixedTransform64& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
	{
		return Private_TranslationEquals(Other.Translation, Tolerance) && Private_RotationEquals(Other.Rotation, Tolerance) && Private_Scale3DEquals(Other.Scale3D, Tolerance);
	}

	// Test if all components of the transform property are equal.
	FORCEINLINE bool Identical(const FFixedTransform64* Other, uint32 PortFlags) const
	{
		return Equals(*Other, FixedPoint::Constants::Fixed64::Zero);
	}

	// Test if rotation and translation components of the transforms are equal, within a tolerance.
	FORCEINLINE bool EqualsNoScale(const FFixedTransform64& Other, FFixed64 Tolerance = FixedPoint::Constants::Fixed64::KindaSmallNumber) const
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
	FORCEINLINE static void Multiply(FFixedTransform64* OutTransform, const FFixedTransform64* A, const FFixedTransform64* B)
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
	FORCEINLINE void SetComponents(const FFixedQuat64& InRotation, const FFixedVector64& InTranslation, const FFixedVector64& InScale3D)
	{
		Rotation = InRotation;
		Translation = InTranslation;
		Scale3D = InScale3D;
	}

	/**
	* Sets the components to the identity transform:
	*   Rotation = (0,0,0,1)
	*   Translation = (0,0,0)
	*   Scale3D = (1,1,1)
	*/
	FORCEINLINE void SetIdentity()
	{
		Rotation = FFixedQuat64::Identity;
		Translation = FFixedVector64::ZeroVector;
		Scale3D = FFixedVector64(1, 1, 1);
	}

	/**
	* Sets the components to the 'additive' identity transform:
	*   Rotation = (0,0,0,1)
	*   Translation = (0,0,0)
	*   Scale3D = (0,0,0)
	*/
	FORCEINLINE void SetIdentityZeroScale()
	{
		Rotation = FFixedQuat64::Identity;
		Translation = FFixedVector64::ZeroVector;
		Scale3D = FFixedVector64::ZeroVector;
	}

	/**
	* Scales the Scale3D component by a new factor
	* @param Scale3DMultiplier The value to multiply Scale3D with
	*/
	FORCEINLINE void MultiplyScale3D(const FFixedVector64& Scale3DMultiplier)
	{
		Scale3D *= Scale3DMultiplier;
	}

	/**
	* Sets the translation component
	* @param NewTranslation The new value for the translation component
	*/
	FORCEINLINE void SetTranslation(const FFixedVector64& NewTranslation)
	{
		Translation = NewTranslation;
	}

	/** Copy translation from another FFixedTransform64. */
	FORCEINLINE void CopyTranslation(const FFixedTransform64& Other)
	{
		Translation = Other.Translation;
	}

	/**
	* Concatenates another rotation to this transformation
	* @param DeltaRotation The rotation to concatenate in the following fashion: Rotation = Rotation * DeltaRotation
	*/
	FORCEINLINE void ConcatenateRotation(const FFixedQuat64& DeltaRotation)
	{
		Rotation = Rotation * DeltaRotation;
	}

	/**
	* Adjusts the translation component of this transformation
	* @param DeltaTranslation The translation to add in the following fashion: Translation += DeltaTranslation
	*/
	FORCEINLINE void AddToTranslation(const FFixedVector64& DeltaTranslation)
	{
		Translation += DeltaTranslation;
	}

	/**
	* Add the translations from two FFixedTransforms and return the result.
	* @return A.Translation + B.Translation
	*/
	FORCEINLINE static FFixedVector64 AddTranslations(const FFixedTransform64& A, const FFixedTransform64& B)
	{
		return A.Translation + B.Translation;
	}

	/**
	* Subtract translations from two FFixedTransforms and return the difference.
	* @return A.Translation - B.Translation.
	*/
	FORCEINLINE static FFixedVector64 SubtractTranslations(const FFixedTransform64& A, const FFixedTransform64& B)
	{
		return A.Translation - B.Translation;
	}

	/**
	* Sets the rotation component
	* @param NewRotation The new value for the rotation component
	*/
	FORCEINLINE void SetRotation(const FFixedQuat64& NewRotation)
	{
		Rotation = NewRotation;
	}

	/** Copy rotation from another FFixedTransform64. */
	FORCEINLINE void CopyRotation(const FFixedTransform64& Other)
	{
		Rotation = Other.Rotation;
	}

	/**
	* Sets the Scale3D component
	* @param NewScale3D The new value for the Scale3D component
	*/
	FORCEINLINE void SetScale3D(const FFixedVector64& NewScale3D)
	{
		Scale3D = NewScale3D;
	}

	/** Copy scale from another FFixedTransform64. */
	FORCEINLINE void CopyScale3D(const FFixedTransform64& Other)
	{
		Scale3D = Other.Scale3D;
	}

	/**
	* Sets both the translation and Scale3D components at the same time
	* @param NewTranslation The new value for the translation component
	* @param NewScale3D The new value for the Scale3D component
	*/
	FORCEINLINE void SetTranslationAndScale3D(const FFixedVector64& NewTranslation, const FFixedVector64& NewScale3D)
	{
		Translation = NewTranslation;
		Scale3D = NewScale3D;
	}

	// For low-level VectorRegister programming
	//NOTE: here so this type and epics type can be typedef'd interchangibly.
	//NOT a good idea to use these on code that uses this type, as it requires a lot of casting from fixed 64 to double!
	TVectorRegisterType<double> GetTranslationRegister() const 
	{
		FVector floattranslation = (FVector)Translation;
		return VectorLoadFloat3_W0(&floattranslation); 
	}
	TVectorRegisterType<double> GetRotationRegister() const 
	{ 
		FQuat floatrotation = (FQuat)Rotation;
		return VectorLoad(&floatrotation); 
	}
	void SetTranslationRegister(TVectorRegisterType<double> InTranslation) 
	{ 
		FVector newval;
		VectorStoreFloat3(InTranslation, &newval);
		Translation = (FFixedVector64)newval;
	}
	void SetRotationRegister(TVectorRegisterType<double> InRotation) 
	{
		FQuat newval;
		VectorStore(InRotation, &newval);
		Rotation = (FFixedQuat64)newval;
	}

	/**
	* Accumulates another transform with this one
	*
	* Rotation is accumulated multiplicatively (Rotation = SourceAtom.Rotation * Rotation)
	* Translation is accumulated additively (Translation += SourceAtom.Translation)
	* Scale3D is accumulated multiplicatively (Scale3D *= SourceAtom.Scale3D)
	*
	* @param SourceAtom The other transform to accumulate into this one
	*/
	FORCEINLINE void Accumulate(const FFixedTransform64& SourceAtom)
	{
		// Add ref pose relative animation to base animation, only if rotation is significant.
		if (FFixedPointMath::Square(SourceAtom.Rotation.W) < FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One - 1))
		{
			Rotation = SourceAtom.Rotation * Rotation;
		}

		Translation += SourceAtom.Translation;
		Scale3D *= SourceAtom.Scale3D;

		DiagnosticCheckNaN_All();

		checkSlow(IsRotationNormalized());
	}

	/** Accumulates another transform with this one, with a blending weight
	*
	* Let SourceAtom = Atom * BlendWeight
	* Rotation is accumulated multiplicatively (Rotation = SourceAtom.Rotation * Rotation).
	* Translation is accumulated additively (Translation += SourceAtom.Translation)
	* Scale3D is accumulated multiplicatively (Scale3D *= SourceAtom.Scale3D)
	*
	* Note: Rotation will not be normalized! Will have to be done manually.
	*
	* @param Atom The other transform to accumulate into this one
	* @param BlendWeight The weight to multiply Atom by before it is accumulated.
	*/
	FORCEINLINE void Accumulate(const FFixedTransform64& Atom, FFixed64 BlendWeight/* default param doesn't work since vectorized version takes ref param */)
	{
		FFixedTransform64 SourceAtom(Atom * BlendWeight);

		// Add ref pose relative animation to base animation, only if rotation is significant.
		if (FFixedPointMath::Square(SourceAtom.Rotation.W) < FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One - 1))
		{
			Rotation = SourceAtom.Rotation * Rotation;
		}

		Translation += SourceAtom.Translation;
		Scale3D *= SourceAtom.Scale3D;

		DiagnosticCheckNaN_All();
	}

	/**
	* Accumulates another transform with this one, with an optional blending weight
	*
	* Rotation is accumulated additively, in the shortest direction (Rotation = Rotation +/- DeltaAtom.Rotation * Weight)
	* Translation is accumulated additively (Translation += DeltaAtom.Translation * Weight)
	* Scale3D is accumulated additively (Scale3D += DeltaAtom.Scale3D * Weight)
	*
	* @param DeltaAtom The other transform to accumulate into this one
	* @param Weight The weight to multiply DeltaAtom by before it is accumulated.
	*/
	FORCEINLINE void AccumulateWithShortestRotation(const FFixedTransform64& DeltaAtom, FFixed64 BlendWeight/* default param doesn't work since vectorized version takes ref param */)
	{
		FFixedTransform64 Atom(DeltaAtom * BlendWeight);

		// To ensure the 'shortest route', we make sure the dot product between the accumulator and the incoming child atom is positive.
		if ((Atom.Rotation | Rotation) < FixedPoint::Constants::Fixed64::Zero)
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

	/** Accumulates another transform with this one, with a blending weight
	*
	* Let SourceAtom = Atom * BlendWeight
	* Rotation is accumulated multiplicatively (Rotation = SourceAtom.Rotation * Rotation).
	* Translation is accumulated additively (Translation += SourceAtom.Translation)
	* Scale3D is accumulated assuming incoming scale is additive scale (Scale3D *= (1 + SourceAtom.Scale3D))
	*
	* When we create additive, we create additive scale based on [TargetScale/SourceScale -1]
	* because that way when you apply weight of 0.3, you don't shrink. We only saves the % of grow/shrink
	* when we apply that back to it, we add back the 1, so that it goes back to it.
	* This solves issue where you blend two additives with 0.3, you don't come back to 0.6 scale, but 1 scale at the end
	* because [1 + [1-1]*0.3 + [1-1]*0.3] becomes 1, so you don't shrink by applying additive scale
	*
	* Note: Rotation will not be normalized! Will have to be done manually.
	*
	* @param Atom The other transform to accumulate into this one
	* @param BlendWeight The weight to multiply Atom by before it is accumulated.
	*/
	FORCEINLINE void AccumulateWithAdditiveScale(const FFixedTransform64& Atom, FFixed64 BlendWeight/* default param doesn't work since vectorized version takes ref param */)
	{
		const FFixedVector64 DefaultScale(FFixedVector64::OneVector);

		FFixedTransform64 SourceAtom(Atom * BlendWeight);

		// Add ref pose relative animation to base animation, only if rotation is significant.
		if (FFixedPointMath::Square(SourceAtom.Rotation.W) < FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One - 1))
		{
			Rotation = SourceAtom.Rotation * Rotation;
		}

		Translation += SourceAtom.Translation;
		Scale3D *= (DefaultScale + SourceAtom.Scale3D);
	}
	/**
	* Set the translation and Scale3D components of this transform to a linearly interpolated combination of two other transforms
	*
	* Translation = FFixedPointMath::Lerp(SourceAtom1.Translation, SourceAtom2.Translation, Alpha)
	* Scale3D = FFixedPointMath::Lerp(SourceAtom1.Scale3D, SourceAtom2.Scale3D, Alpha)
	*
	* @param SourceAtom1 The starting point source atom (used 100% if Alpha is 0)
	* @param SourceAtom2 The ending point source atom (used 100% if Alpha is 1)
	* @param Alpha The blending weight between SourceAtom1 and SourceAtom2
	*/
	FORCEINLINE void LerpTranslationScale3D(const FFixedTransform64& SourceAtom1, const FFixedTransform64& SourceAtom2, FFixed64 Alpha)
	{
		Translation = FFixedPointMath::Lerp(SourceAtom1.Translation, SourceAtom2.Translation, Alpha);
		Scale3D = FFixedPointMath::Lerp(SourceAtom1.Scale3D, SourceAtom2.Scale3D, Alpha);
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

	/**
	* Blends the Identity transform with a weighted source transform and accumulates that into a destination transform
	*
	* DeltaAtom = Blend(Identity, SourceAtom, BlendWeight)
	* FinalAtom.Rotation = DeltaAtom.Rotation * FinalAtom.Rotation
	* FinalAtom.Translation += DeltaAtom.Translation
	* FinalAtom.Scale3D *= DeltaAtom.Scale3D
	*
	* @param FinalAtom [in/out] The atom to accumulate the blended source atom into
	* @param SourceAtom The target transformation (used when BlendWeight = 1); this is modified during the process
	* @param BlendWeight The blend weight between Identity and SourceAtom
	*/
	FORCEINLINE static void BlendFromIdentityAndAccumulate(FFixedTransform64& FinalAtom, const FFixedTransform64& SourceAtom, FFixed64 BlendWeight)
	{
		const FFixedTransform64 AdditiveIdentity(FFixedQuat64::Identity, FFixedVector64::ZeroVector, FFixedVector64::ZeroVector);
		const FFixedVector64 DefaultScale(FFixedVector64::OneVector);
		FFixedTransform64 DeltaAtom = SourceAtom;

		// Scale delta by weight
		if (BlendWeight < (FixedPoint::Constants::Fixed64::One - FixedPoint::Constants::Fixed64::ZeroAnimWeightThresh))
		{
			DeltaAtom.Blend(AdditiveIdentity, DeltaAtom, BlendWeight);
		}

		// Add ref pose relative animation to base animation, only if rotation is significant.
		if (FMath::Square(DeltaAtom.Rotation.W) < FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One - 1))
		{
			FinalAtom.Rotation = DeltaAtom.Rotation * FinalAtom.Rotation;
		}

		FinalAtom.Translation += DeltaAtom.Translation;
		FinalAtom.Scale3D *= (DefaultScale + DeltaAtom.Scale3D);

		checkSlow(FinalAtom.IsRotationNormalized());
	}

	/**
	* Returns the rotation component
	*
	* @return The rotation component
	*/
	FORCEINLINE FFixedQuat64 GetRotation() const
	{
		return Rotation;
	}

	/**
	* Returns the translation component
	*
	* @return The translation component
	*/
	FORCEINLINE FFixedVector64 GetTranslation() const
	{
		return Translation;
	}

	/**
	* Returns the Scale3D component
	*
	* @return The Scale3D component
	*/
	FORCEINLINE FFixedVector64 GetScale3D() const
	{
		return Scale3D;
	}

	/**
	* Sets the Rotation and Scale3D of this transformation from another transform
	*
	* @param SrcBA The transform to copy rotation and Scale3D from
	*/
	FORCEINLINE void CopyRotationPart(const FFixedTransform64& SrcBA)
	{
		Rotation = SrcBA.Rotation;
		Scale3D = SrcBA.Scale3D;
	}

	/**
	* Sets the Translation and Scale3D of this transformation from another transform
	*
	* @param SrcBA The transform to copy translation and Scale3D from
	*/
	FORCEINLINE void CopyTranslationAndScale3D(const FFixedTransform64& SrcBA)
	{
		Translation = SrcBA.Translation;
		Scale3D = SrcBA.Scale3D;
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

		Rotation = FFixedQuat64(M);
		Translation = InMatrix.GetOrigin();

		// Normalize rotation
		Rotation.Normalize();
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
	FORCEINLINE static void MultiplyUsingMatrixWithScale(FFixedTransform64* OutTransform, const FFixedTransform64* A, const FFixedTransform64* B)
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

	FORCEINLINE static void ConstructTransformFromMatrixWithDesiredScale(const FFixedMatrix& AMatrix, const FFixedMatrix& BMatrix, const FFixedVector64& DesiredScale, FFixedTransform64& OutTransform)
	{
		// the goal of using M is to get the correct orientation
		// but for translation, we still need scale
		FFixedMatrix M = AMatrix * BMatrix;
		M.RemoveScaling();

		// apply negative scale back to axes
		FFixedVector64 SignedScale = DesiredScale.GetSignVector();

		M.SetAxis(0, SignedScale.X * M.GetScaledAxis(EAxis::X));
		M.SetAxis(1, SignedScale.Y * M.GetScaledAxis(EAxis::Y));
		M.SetAxis(2, SignedScale.Z * M.GetScaledAxis(EAxis::Z));

		// @note: if you have negative with 0 scale, this will return rotation that is identity
		// since matrix loses that axes
		FFixedQuat64 Rotation = FFixedQuat64(M);
		Rotation.Normalize();

		// set values back to output
		OutTransform.Scale3D = DesiredScale;
		OutTransform.Rotation = Rotation;

		// technically I could calculate this using FFixedTransform64 but then it does more quat multiplication 
		// instead of using Scale in matrix multiplication
		// it's a question of between RemoveScaling vs using FFixedTransform64 to move translation
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
	static void GetRelativeTransformUsingMatrixWithScale(FFixedTransform64* OutTransform, const FFixedTransform64* Base, const FFixedTransform64* Relative);
public:
	FORCEINLINE operator FTransform() const
	{
		return FTransform((FQuat)Rotation, (FVector)Translation, (FVector)Scale3D);
	}
};
