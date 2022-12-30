// Fill out your copyright notice in the Description page of Project Settings.

#include "FixedPointTransform.h"
#include "Misc/DefaultValueHelper.h"

DEFINE_LOG_CATEGORY_STATIC(LogTransform, Log, All);

const FFixedTransform64 FFixedTransform64::Identity(
	FFixedQuat64(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One), 
	FFixedVector64(FixedPoint::Constants::Fixed64::Zero), 
	FFixedVector64(FixedPoint::Constants::Fixed64::One));

bool FFixedTransform64::DebugEqualMatrix(const FFixedMatrix& Matrix) const
{
	FFixedTransform64 TestResult(Matrix);
	if (!Equals(TestResult))
	{
		// see now which one isn't equal
		if (!Scale3D.Equals(TestResult.Scale3D, 0.01f))
		{
			UE_LOG(LogTransform, Log, TEXT("Matrix(S)\t%s"), *TestResult.Scale3D.ToString());
			UE_LOG(LogTransform, Log, TEXT("VQS(S)\t%s"), *Scale3D.ToString());
		}

		// see now which one isn't equal
		if (!Rotation.Equals(TestResult.Rotation))
		{
			UE_LOG(LogTransform, Log, TEXT("Matrix(R)\t%s"), *TestResult.Rotation.ToString());
			UE_LOG(LogTransform, Log, TEXT("VQS(R)\t%s"), *Rotation.ToString());
		}

		// see now which one isn't equal
		if (!Translation.Equals(TestResult.Translation, 0.01f))
		{
			UE_LOG(LogTransform, Log, TEXT("Matrix(T)\t%s"), *TestResult.Translation.ToString());
			UE_LOG(LogTransform, Log, TEXT("VQS(T)\t%s"), *Translation.ToString());
		}
		return false;
	}

	return true;
}

void FFixedTransform64::DebugPrint() const
{
	UE_LOG(LogTransform, Log, TEXT("%s"), *ToHumanReadableString());
}

FString FFixedTransform64::ToHumanReadableString() const
{
	FFixedRotator64 R(GetRotation());
	FFixedVector64 TT(GetTranslation());
	FFixedVector64 S(GetScale3D());

	FString Output = FString::Printf(TEXT("Rotation: Pitch %f Yaw %f Roll %f\r\n"), (double)R.Pitch, (double)R.Yaw, (double)R.Roll);
	Output += FString::Printf(TEXT("Translation: %f %f %f\r\n"), (double)TT.X, (double)TT.Y, (double)TT.Z);
	Output += FString::Printf(TEXT("Scale3D: %f %f %f\r\n"), (double)S.X, (double)S.Y, (double)S.Z);

	return Output;
}

FString FFixedTransform64::ToString() const
{
	const FFixedRotator64 R(GetRotation());
	const FFixedVector64 TT(GetTranslation());
	const FFixedVector64 S(GetScale3D());

	return FString::Printf(TEXT("%f,%f,%f|%f,%f,%f|%f,%f,%f"), (double)TT.X, (double)TT.Y, (double)TT.Z, (double)R.Pitch, (double)R.Yaw, (double)R.Roll, (double)S.X, (double)S.Y, (double)S.Z);
}

bool FFixedTransform64::InitFromString(const FString& Source)
{
	TArray<FString> ComponentStrings;
	Source.ParseIntoArray(ComponentStrings, TEXT("|"), true);
	const int32 NumComponents = ComponentStrings.Num();
	if (3 != NumComponents)
	{
		return false;
	}

	// Translation
	FVector ParsedTranslation = FVector::ZeroVector;
	if (!FDefaultValueHelper::ParseVector(ComponentStrings[0], ParsedTranslation))
	{
		return false;
	}

	// Rotation
	FRotator ParsedRotation = FRotator::ZeroRotator;
	if (!FDefaultValueHelper::ParseRotator(ComponentStrings[1], ParsedRotation))
	{
		return false;
	}

	// Scale
	FVector ParsedScale = FVector::OneVector;
	if (!FDefaultValueHelper::ParseVector(ComponentStrings[2], ParsedScale))
	{
		return false;
	}

	SetComponents(FFixedQuat64(FFixedRotator64(ParsedRotation)), FFixedVector64(ParsedTranslation), FFixedVector64(ParsedScale));

	return true;
}

void FFixedTransform64::GetRelativeTransformUsingMatrixWithScale(FFixedTransform64* OutTransform, const FFixedTransform64* Base, const FFixedTransform64* Relative)
{
	// the goal of using M is to get the correct orientation
	// but for translation, we still need scale
	FFixedMatrix AM = Base->ToMatrixWithScale();
	FFixedMatrix BM = Relative->ToMatrixWithScale();
	// get combined scale
	FFixedVector64 SafeRecipScale3D = GetSafeScaleReciprocal(Relative->Scale3D, FixedPoint::Constants::Fixed64::SmallNumber);
	FFixedVector64 DesiredScale3D = Base->Scale3D * SafeRecipScale3D;
	ConstructTransformFromMatrixWithDesiredScale(AM, BM.Inverse(), DesiredScale3D, *OutTransform);
}

FFixedTransform64 FFixedTransform64::GetRelativeTransform(const FFixedTransform64& Other) const
{
	// A * B(-1) = VQS(B)(-1) (VQS (A))
	// 
	// Scale = S(A)/S(B)
	// Rotation = Q(B)(-1) * Q(A)
	// Translation = 1/S(B) *[Q(B)(-1)*(T(A)-T(B))*Q(B)]
	// where A = this, B = Other
	FFixedTransform64 Result;

	if (AnyHasNegativeScale(Scale3D, Other.GetScale3D()))
	{
		// @note, if you have 0 scale with negative, you're going to lose rotation as it can't convert back to quat
		GetRelativeTransformUsingMatrixWithScale(&Result, this, &Other);
	}
	else
	{
		FFixedVector64 SafeRecipScale3D = GetSafeScaleReciprocal(Other.Scale3D, FixedPoint::Constants::Fixed64::SmallNumber);
		Result.Scale3D = Scale3D * SafeRecipScale3D;

		if (Other.Rotation.IsNormalized() == false)
		{
			return FFixedTransform64::Identity;
		}

		FFixedQuat64 Inverse = Other.Rotation.Inverse();
		Result.Rotation = Inverse * Rotation;

		Result.Translation = (Inverse * (Translation - Other.Translation)) * (SafeRecipScale3D);
	}

	return Result;
}

FFixedTransform64 FFixedTransform64::GetRelativeTransformReverse(const FFixedTransform64& Other) const
{
	// A (-1) * B = VQS(B)(VQS (A)(-1))
	// 
	// Scale = S(B)/S(A)
	// Rotation = Q(B) * Q(A)(-1)
	// Translation = T(B)-S(B)/S(A) *[Q(B)*Q(A)(-1)*T(A)*Q(A)*Q(B)(-1)]
	// where A = this, and B = Other
	FFixedTransform64 Result;

	FFixedVector64 SafeRecipScale3D = GetSafeScaleReciprocal(Scale3D);
	Result.Scale3D = Other.Scale3D * SafeRecipScale3D;

	Result.Rotation = Other.Rotation * Rotation.Inverse();

	Result.Translation = Other.Translation - Result.Scale3D * (Result.Rotation * Translation);

	return Result;
}

/**
 * Set current transform and the relative to ParentTransform.
 * Equates to This = This->GetRelativeTransform(Parent), but saves the intermediate TTransform<T> storage and copy.
 */
void FFixedTransform64::SetToRelativeTransform(const FFixedTransform64& ParentTransform)
{
	// A * B(-1) = VQS(B)(-1) (VQS (A))
	// 
	// Scale = S(A)/S(B)
	// Rotation = Q(B)(-1) * Q(A)
	// Translation = 1/S(B) *[Q(B)(-1)*(T(A)-T(B))*Q(B)]
	// where A = this, B = Other

	const FFixedVector64 SafeRecipScale3D = GetSafeScaleReciprocal(ParentTransform.Scale3D, FixedPoint::Constants::Fixed64::SmallNumber);
	const FFixedQuat64 InverseRot = ParentTransform.Rotation.Inverse();

	Scale3D *= SafeRecipScale3D;
	Translation = (InverseRot * (Translation - ParentTransform.Translation)) * SafeRecipScale3D;
	Rotation = InverseRot * Rotation;
}