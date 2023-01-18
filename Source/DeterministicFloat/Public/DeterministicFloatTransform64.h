// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatTransform64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicTransform64
{
public:
	GENERATED_BODY()

		FORCEINLINE void DiagnosticCheckNaN_Translate() const;
	FORCEINLINE void DiagnosticCheckNaN_Rotate() const;
	FORCEINLINE void DiagnosticCheckNaN_Scale3D() const;
	FORCEINLINE void DiagnosticCheckNaN_All() const;
	FORCEINLINE void DiagnosticCheck_IsValid() const;
protected:
	/** Rotation of this transformation, as a quaternion. */
	FDeterministicQuat64 Rotation;
	/** Translation of this transformation, as a vector. */
	FDeterministicVector64 Translation;
	/** 3D scale (always applied in local space) as a vector. */
	FDeterministicVector64 Scale3D;
public:
	/** Default constructor. */
	FORCEINLINE FDeterministicTransform64();

	FORCEINLINE FDeterministicTransform64(const FTransform& Other);

	/**
	* Constructor with an initial translation
	*
	* @param InTranslation The value to use for the translation component
	*/
	FORCEINLINE explicit FDeterministicTransform64(const FDeterministicVector64& InTranslation);

	/**
	* Constructor with leaving uninitialized memory
	*/
	FORCEINLINE explicit FDeterministicTransform64(ENoInit);

	/**
	* Constructor with an initial rotation
	*
	* @param InRotation The value to use for rotation component
	*/
	FORCEINLINE explicit FDeterministicTransform64(const FDeterministicQuat64& InRotation);

	/**
	* Constructor with an initial rotation
	*
	* @param InRotation The value to use for rotation component  (after being converted to a quaternion)
	*/
	FORCEINLINE explicit FDeterministicTransform64(const FDeterministicRotator64& InRotation);

	/**
	* Constructor with all components initialized
	*
	* @param InRotation The value to use for rotation component
	* @param InTranslation The value to use for the translation component
	* @param InScale3D The value to use for the scale component
	*/
	FORCEINLINE FDeterministicTransform64(const FDeterministicQuat64& InRotation, const FDeterministicVector64& InTranslation, const FDeterministicVector64& InScale3D = FDeterministicVector64::OneVector);

	/**
	* Constructor with all components initialized, taking a TRotator<T> as the rotation component
	*
	* @param InRotation The value to use for rotation component (after being converted to a quaternion)
	* @param InTranslation The value to use for the translation component
	* @param InScale3D The value to use for the scale component
	*/
	FORCEINLINE FDeterministicTransform64(const FDeterministicRotator64& InRotation, const FDeterministicVector64& InTranslation, const FDeterministicVector64& InScale3D = FDeterministicVector64::OneVector);

	/**
	* Constructor for converting a Matrix (including scale) into a FDeterministicTransform64.
	*/
	FORCEINLINE explicit FDeterministicTransform64(const FDeterministicMatrix64& InMatrix);

	/** Constructor that takes basis axes and translation */
	FORCEINLINE FDeterministicTransform64(const FDeterministicVector64& InX, const FDeterministicVector64& InY, const FDeterministicVector64& InZ, const FDeterministicVector64& InTranslation);

	static const FDeterministicTransform64 Identity;

	/**
	* Does a debugf of the contents of this Transform.
	*/
	void DebugPrint() const;

	/** Debug purpose only **/
	bool DebugEqualMatrix(const FDeterministicMatrix64& Matrix) const;

	/** Convert FDeterministicTransform64 contents to a string */
	FString ToHumanReadableString() const;

	FString ToString() const;

	/** Acceptable form: "%f,%f,%f|%f,%f,%f|%f,%f,%f" */
	bool InitFromString(const FString& InSourceString);

	/**
	* Convert this Transform to a transformation matrix with scaling.
	*/
	FORCEINLINE FDeterministicMatrix64 ToMatrixWithScale() const;

	/**
	* Convert this Transform to matrix with scaling and compute the inverse of that.
	*/
	FORCEINLINE FDeterministicMatrix64 ToInverseMatrixWithScale() const;

	/**
	* Convert this Transform to inverse.
	*/
	FORCEINLINE FDeterministicTransform64 Inverse() const;

	/**
	* Convert this Transform to a transformation matrix, ignoring its scaling
	*/
	FORCEINLINE FDeterministicMatrix64 ToMatrixNoScale() const;

	/** Set this transform to the weighted blend of the supplied two transforms. */
	FORCEINLINE void Blend(const FDeterministicTransform64& Atom1, const FDeterministicTransform64& Atom2, FDeterministicNumber64 Alpha);

	/** Set this Transform to the weighted blend of it and the supplied Transform. */
	FORCEINLINE void BlendWith(const FDeterministicTransform64& OtherAtom, FDeterministicNumber64 Alpha);

	/**
	* Quaternion addition is wrong here. This is just a special case for linear interpolation.
	* Use only within blends!!
	* Rotation part is NOT normalized!!
	*/
	FORCEINLINE FDeterministicTransform64 operator+(const FDeterministicTransform64& Atom) const;

	FORCEINLINE FDeterministicTransform64& operator+=(const FDeterministicTransform64& Atom);

	FORCEINLINE FDeterministicTransform64 operator*(FDeterministicNumber64 Mult) const;

	FORCEINLINE FDeterministicTransform64& operator*=(FDeterministicNumber64 Mult);

	/**
	* Return a transform that is the result of this multiplied by another transform.
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other transform by which to multiply.
	* @return new transform: this * Other
	*/
	FORCEINLINE FDeterministicTransform64 operator*(const FDeterministicTransform64& Other) const;

	/**
	* Sets this transform to the result of this multiplied by another transform.
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other transform by which to multiply.
	*/
	FORCEINLINE void operator*=(const FDeterministicTransform64& Other);

	/**
	* Return a transform that is the result of this multiplied by another transform (made only from a rotation).
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other quaternion rotation by which to multiply.
	* @return new transform: this * TTransform(Other)
	*/
	FORCEINLINE FDeterministicTransform64 operator*(const FDeterministicQuat64& Other) const;

	/**
	* Sets this transform to the result of this multiplied by another transform (made only from a rotation).
	* Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	*
	* @param  Other other quaternion rotation by which to multiply.
	*/
	FORCEINLINE void operator*=(const FDeterministicQuat64& Other);

	FORCEINLINE static bool AnyHasNegativeScale(const FDeterministicVector64& InScale3D, const FDeterministicVector64& InOtherScale3D);

	FORCEINLINE void ScaleTranslation(const FDeterministicVector64& InScale3D);

	FORCEINLINE void ScaleTranslation(const FDeterministicNumber64& Scale);

	FORCEINLINE void RemoveScaling(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber);

	FORCEINLINE FDeterministicNumber64 GetMaximumAxisScale() const;

	FORCEINLINE FDeterministicNumber64 GetMinimumAxisScale() const;

	// Inverse does not work well with VQS format(in particular non-uniform), so removing it, but made two below functions to be used instead. 

	/*******************************************************************************************
	* The below 2 functions are the ones to get delta transform and return FDeterministicTransform64 format that can be concatenated
	* Inverse itself can't concatenate with VQS format(since VQS always transform from S->Q->T, where inverse happens from T(-1)->Q(-1)->S(-1))
	* So these 2 provides ways to fix this
	* GetRelativeTransform returns this*Other(-1) and parameter is Other(not Other(-1))
	* GetRelativeTransformReverse returns this(-1)*Other, and parameter is Other.
	*******************************************************************************************/
	FDeterministicTransform64 GetRelativeTransform(const FDeterministicTransform64& Other) const;
	FDeterministicTransform64 GetRelativeTransformReverse(const FDeterministicTransform64& Other) const;

	/**
	* Set current transform and the relative to ParentTransform.
	* Equates to This = This->GetRelativeTransform(Parent), but saves the intermediate FDeterministicTransform64 storage and copy.
	*/
	void SetToRelativeTransform(const FDeterministicTransform64& ParentTransform);

	FORCEINLINE FDeterministicVector4D64 TransformFVector4(const FDeterministicVector4D64& V) const;

	FORCEINLINE FDeterministicVector4D64 TransformFVector4NoScale(const FDeterministicVector4D64& V) const;

	FORCEINLINE FDeterministicVector64 TransformPosition(const FDeterministicVector64& V) const;

	FORCEINLINE FDeterministicVector64 TransformPositionNoScale(const FDeterministicVector64& V) const;

	/** Inverts the transform and then transforms V - correctly handles scaling in this transform. */
	FORCEINLINE FDeterministicVector64 InverseTransformPosition(const FDeterministicVector64& V) const;


	FORCEINLINE FDeterministicVector64 InverseTransformPositionNoScale(const FDeterministicVector64& V) const;


	FORCEINLINE FDeterministicVector64 TransformVector(const FDeterministicVector64& V) const;

	FORCEINLINE FDeterministicVector64 TransformVectorNoScale(const FDeterministicVector64& V) const;

	/**
	*	Transform a direction vector by the inverse of this transform - will not take into account translation part.
	*	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
	*/
	FORCEINLINE FDeterministicVector64 InverseTransformVector(const FDeterministicVector64& V) const;

	FORCEINLINE FDeterministicVector64 InverseTransformVectorNoScale(const FDeterministicVector64& V) const;

	/**
	 * Transform a rotation.
	 * For example if this is a LocalToWorld transform, TransformRotation(Q) would transform Q from local to world space.
	 */
	FORCEINLINE FDeterministicQuat64 TransformRotation(const FDeterministicQuat64& Q) const;

	/**
	* Inverse transform a rotation.
	* For example if this is a LocalToWorld transform, InverseTransformRotation(Q) would transform Q from world to local space.
	*/
	FORCEINLINE FDeterministicQuat64 InverseTransformRotation(const FDeterministicQuat64& Q) const;

	FORCEINLINE FDeterministicTransform64 GetScaled(FDeterministicNumber64 InScale) const;

	FORCEINLINE FDeterministicTransform64 GetScaled(FDeterministicVector64 InScale) const;

	FORCEINLINE FDeterministicVector64 GetScaledAxis(EAxis::Type InAxis) const;

	FORCEINLINE FDeterministicVector64 GetUnitAxis(EAxis::Type InAxis) const;

	FORCEINLINE void Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis);

	FORCEINLINE static FDeterministicVector64 GetSafeScaleReciprocal(const FDeterministicVector64& InScale, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber);

	// temp function for easy conversion
	FORCEINLINE FDeterministicVector64 GetLocation() const;

	FORCEINLINE FDeterministicRotator64 Rotator() const;

	/** Calculate the determinant of this transformation */
	FORCEINLINE FDeterministicNumber64 GetDeterminant() const;

	/** Set the translation of this transformation */
	FORCEINLINE void SetLocation(const FDeterministicVector64& Origin);

	/**
	* Checks the components for non-finite values (NaN or Inf).
	* @return Returns true if any component (rotation, translation, or scale) is not finite.
	* Fixed point numbers can't be NaN
	*/
	FORCEINLINE bool ContainsNaN() const;

	inline bool IsValid() const;

private:
	FORCEINLINE bool Private_RotationEquals(const FDeterministicQuat64& InRotation, const FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	FORCEINLINE bool Private_TranslationEquals(const FDeterministicVector64& InTranslation, const FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	FORCEINLINE bool Private_Scale3DEquals(const FDeterministicVector64& InScale3D, const FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;
public:

	// Test if A's rotation equals B's rotation, within a tolerance. Preferred over "A.GetRotation().Equals(B.GetRotation())" because it is faster on some platforms.
	FORCEINLINE static bool AreRotationsEqual(const FDeterministicTransform64& A, const FDeterministicTransform64& B, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber);

	// Test if A's translation equals B's translation, within a tolerance. Preferred over "A.GetTranslation().Equals(B.GetTranslation())" because it is faster on some platforms.
	FORCEINLINE static bool AreTranslationsEqual(const FDeterministicTransform64& A, const FDeterministicTransform64& B, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber);

	// Test if A's scale equals B's scale, within a tolerance. Preferred over "A.GetScale3D().Equals(B.GetScale3D())" because it is faster on some platforms.
	FORCEINLINE static bool AreScale3DsEqual(const FDeterministicTransform64& A, const FDeterministicTransform64& B, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber);

	// Test if this Transform's rotation equals another's rotation, within a tolerance. Preferred over "GetRotation().Equals(Other.GetRotation())" because it is faster on some platforms.
	FORCEINLINE bool RotationEquals(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	// Test if this Transform's translation equals another's translation, within a tolerance. Preferred over "GetTranslation().Equals(Other.GetTranslation())" because it is faster on some platforms.
	FORCEINLINE bool TranslationEquals(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	// Test if this Transform's scale equals another's scale, within a tolerance. Preferred over "GetScale3D().Equals(Other.GetScale3D())" because it is faster on some platforms.
	FORCEINLINE bool Scale3DEquals(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	// Test if all components of the transforms are equal, within a tolerance.
	FORCEINLINE bool Equals(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	// Test if all components of the transform property are equal.
	FORCEINLINE bool Identical(const FDeterministicTransform64* Other, uint32 PortFlags) const;

	// Test if rotation and translation components of the transforms are equal, within a tolerance.
	FORCEINLINE bool EqualsNoScale(const FDeterministicTransform64& Other, FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	/**
	* Create a new transform: OutTransform = A * B.
	*
	* Order matters when composing transforms : A * B will yield a transform that logically first applies A then B to any subsequent transformation.
	*
	* @param  OutTransform pointer to transform that will store the result of A * B.
	* @param  A Transform A.
	* @param  B Transform B.
	*/
	FORCEINLINE static void Multiply(FDeterministicTransform64* OutTransform, const FDeterministicTransform64* A, const FDeterministicTransform64* B);

	/**
	* Sets the components
	* @param InRotation The new value for the Rotation component
	* @param InTranslation The new value for the Translation component
	* @param InScale3D The new value for the Scale3D component
	*/
	FORCEINLINE void SetComponents(const FDeterministicQuat64& InRotation, const FDeterministicVector64& InTranslation, const FDeterministicVector64& InScale3D);

	/**
	* Sets the components to the identity transform:
	*   Rotation = (0,0,0,1)
	*   Translation = (0,0,0)
	*   Scale3D = (1,1,1)
	*/
	FORCEINLINE void SetIdentity();

	/**
	* Sets the components to the 'additive' identity transform:
	*   Rotation = (0,0,0,1)
	*   Translation = (0,0,0)
	*   Scale3D = (0,0,0)
	*/
	FORCEINLINE void SetIdentityZeroScale();

	/**
	* Scales the Scale3D component by a new factor
	* @param Scale3DMultiplier The value to multiply Scale3D with
	*/
	FORCEINLINE void MultiplyScale3D(const FDeterministicVector64& Scale3DMultiplier);

	/**
	* Sets the translation component
	* @param NewTranslation The new value for the translation component
	*/
	FORCEINLINE void SetTranslation(const FDeterministicVector64& NewTranslation);

	/** Copy translation from another FDeterministicTransform64. */
	FORCEINLINE void CopyTranslation(const FDeterministicTransform64& Other);

	/**
	* Concatenates another rotation to this transformation
	* @param DeltaRotation The rotation to concatenate in the following fashion: Rotation = Rotation * DeltaRotation
	*/
	FORCEINLINE void ConcatenateRotation(const FDeterministicQuat64& DeltaRotation);

	/**
	* Adjusts the translation component of this transformation
	* @param DeltaTranslation The translation to add in the following fashion: Translation += DeltaTranslation
	*/
	FORCEINLINE void AddToTranslation(const FDeterministicVector64& DeltaTranslation);

	/**
	* Add the translations from two FFixedTransforms and return the result.
	* @return A.Translation + B.Translation
	*/
	FORCEINLINE static FDeterministicVector64 AddTranslations(const FDeterministicTransform64& A, const FDeterministicTransform64& B);

	/**
	* Subtract translations from two FFixedTransforms and return the difference.
	* @return A.Translation - B.Translation.
	*/
	FORCEINLINE static FDeterministicVector64 SubtractTranslations(const FDeterministicTransform64& A, const FDeterministicTransform64& B);

	/**
	* Sets the rotation component
	* @param NewRotation The new value for the rotation component
	*/
	FORCEINLINE void SetRotation(const FDeterministicQuat64& NewRotation);

	/** Copy rotation from another FDeterministicTransform64. */
	FORCEINLINE void CopyRotation(const FDeterministicTransform64& Other);

	/**
	* Sets the Scale3D component
	* @param NewScale3D The new value for the Scale3D component
	*/
	FORCEINLINE void SetScale3D(const FDeterministicVector64& NewScale3D);

	/** Copy scale from another FDeterministicTransform64. */
	FORCEINLINE void CopyScale3D(const FDeterministicTransform64& Other);

	/**
	* Sets both the translation and Scale3D components at the same time
	* @param NewTranslation The new value for the translation component
	* @param NewScale3D The new value for the Scale3D component
	*/
	FORCEINLINE void SetTranslationAndScale3D(const FDeterministicVector64& NewTranslation, const FDeterministicVector64& NewScale3D);

	// For low-level VectorRegister programming
	//NOTE: here so this type and epics type can be typedef'd interchangibly.
	//NOT a good idea to use these on code that uses this type, as it requires a lot of casting from fixed 64 to double!
	TVectorRegisterType<double> GetTranslationRegister() const;
	TVectorRegisterType<double> GetRotationRegister() const;
	void SetTranslationRegister(TVectorRegisterType<double> InTranslation);
	void SetRotationRegister(TVectorRegisterType<double> InRotation);

	/**
	* Accumulates another transform with this one
	*
	* Rotation is accumulated multiplicatively (Rotation = SourceAtom.Rotation * Rotation)
	* Translation is accumulated additively (Translation += SourceAtom.Translation)
	* Scale3D is accumulated multiplicatively (Scale3D *= SourceAtom.Scale3D)
	*
	* @param SourceAtom The other transform to accumulate into this one
	*/
	FORCEINLINE void Accumulate(const FDeterministicTransform64& SourceAtom);

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
	FORCEINLINE void Accumulate(const FDeterministicTransform64& Atom, FDeterministicNumber64 BlendWeight/* default param doesn't work since vectorized version takes ref param */);

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
	FORCEINLINE void AccumulateWithShortestRotation(const FDeterministicTransform64& DeltaAtom, FDeterministicNumber64 BlendWeight/* default param doesn't work since vectorized version takes ref param */);

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
	FORCEINLINE void AccumulateWithAdditiveScale(const FDeterministicTransform64& Atom, FDeterministicNumber64 BlendWeight/* default param doesn't work since vectorized version takes ref param */);
	
	/**
	* Set the translation and Scale3D components of this transform to a linearly interpolated combination of two other transforms
	*
	* Translation = FDeterministicFloatMath::Lerp(SourceAtom1.Translation, SourceAtom2.Translation, Alpha)
	* Scale3D = FDeterministicFloatMath::Lerp(SourceAtom1.Scale3D, SourceAtom2.Scale3D, Alpha)
	*
	* @param SourceAtom1 The starting point source atom (used 100% if Alpha is 0)
	* @param SourceAtom2 The ending point source atom (used 100% if Alpha is 1)
	* @param Alpha The blending weight between SourceAtom1 and SourceAtom2
	*/
	FORCEINLINE void LerpTranslationScale3D(const FDeterministicTransform64& SourceAtom1, const FDeterministicTransform64& SourceAtom2, FDeterministicNumber64 Alpha);

	/**
	* Normalize the rotation component of this transformation
	*/
	FORCEINLINE void NormalizeRotation();

	/**
	* Checks whether the rotation component is normalized or not
	*
	* @return true if the rotation component is normalized, and false otherwise.
	*/
	FORCEINLINE bool IsRotationNormalized() const;

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
	FORCEINLINE static void BlendFromIdentityAndAccumulate(FDeterministicTransform64& FinalAtom, const FDeterministicTransform64& SourceAtom, FDeterministicNumber64 BlendWeight);

	/**
	* Returns the rotation component
	*
	* @return The rotation component
	*/
	FORCEINLINE FDeterministicQuat64 GetRotation() const;

	/**
	* Returns the translation component
	*
	* @return The translation component
	*/
	FORCEINLINE FDeterministicVector64 GetTranslation() const;

	/**
	* Returns the Scale3D component
	*
	* @return The Scale3D component
	*/
	FORCEINLINE FDeterministicVector64 GetScale3D() const;

	/**
	* Sets the Rotation and Scale3D of this transformation from another transform
	*
	* @param SrcBA The transform to copy rotation and Scale3D from
	*/
	FORCEINLINE void CopyRotationPart(const FDeterministicTransform64& SrcBA);

	/**
	* Sets the Translation and Scale3D of this transformation from another transform
	*
	* @param SrcBA The transform to copy translation and Scale3D from
	*/
	FORCEINLINE void CopyTranslationAndScale3D(const FDeterministicTransform64& SrcBA);

	FORCEINLINE void SetFromMatrix(const FDeterministicMatrix64& InMatrix);
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
	FORCEINLINE static void MultiplyUsingMatrixWithScale(FDeterministicTransform64* OutTransform, const FDeterministicTransform64* A, const FDeterministicTransform64* B);

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

	FORCEINLINE static void ConstructTransformFromMatrixWithDesiredScale(const FDeterministicMatrix64& AMatrix, const FDeterministicMatrix64& BMatrix, const FDeterministicVector64& DesiredScale, FDeterministicTransform64& OutTransform);

	/**
	* Create a new transform: OutTransform = Base * Relative(-1) using the matrix while keeping the scale that's given by Base and Relative
	* Please note that this operation is a lot more expensive than normal GetRelativeTrnasform
	*
	* @param  OutTransform pointer to transform that will store the result of Base * Relative(-1).
	* @param  BAse Transform Base.
	* @param  Relative Transform Relative.
	*/
	static void GetRelativeTransformUsingMatrixWithScale(FDeterministicTransform64* OutTransform, const FDeterministicTransform64* Base, const FDeterministicTransform64* Relative);
public:
	FORCEINLINE operator FTransform() const
	{
		return FTransform((FQuat)Rotation, (FVector)Translation, (FVector)Scale3D);
	}
};
