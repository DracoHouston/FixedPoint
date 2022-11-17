// Fill out your copyright notice in the Description page of Project Settings.

#include "FixedPointTransform.h"
#include "Misc/DefaultValueHelper.h"

DEFINE_LOG_CATEGORY_STATIC(LogTransform, Log, All);

const FFixedTransform FFixedTransform::Identity(
	FFixedQuat(FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::Zero, FixedPoint::Constants::Fixed64::One), 
	FFixedVector(FixedPoint::Constants::Fixed64::Zero), 
	FFixedVector(FixedPoint::Constants::Fixed64::One));

bool FFixedTransform::DebugEqualMatrix(const FFixedMatrix& Matrix) const
{
	FFixedTransform TestResult(Matrix);
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

void FFixedTransform::DebugPrint() const
{
	UE_LOG(LogTransform, Log, TEXT("%s"), *ToHumanReadableString());
}

FString FFixedTransform::ToHumanReadableString() const
{
	FFixedRotator R(GetRotation());
	FFixedVector TT(GetTranslation());
	FFixedVector S(GetScale3D());

	FString Output = FString::Printf(TEXT("Rotation: Pitch %f Yaw %f Roll %f\r\n"), (double)R.Pitch, (double)R.Yaw, (double)R.Roll);
	Output += FString::Printf(TEXT("Translation: %f %f %f\r\n"), (double)TT.X, (double)TT.Y, (double)TT.Z);
	Output += FString::Printf(TEXT("Scale3D: %f %f %f\r\n"), (double)S.X, (double)S.Y, (double)S.Z);

	return Output;
}

FString FFixedTransform::ToString() const
{
	const FFixedRotator R(GetRotation());
	const FFixedVector TT(GetTranslation());
	const FFixedVector S(GetScale3D());

	return FString::Printf(TEXT("%f,%f,%f|%f,%f,%f|%f,%f,%f"), (double)TT.X, (double)TT.Y, (double)TT.Z, (double)R.Pitch, (double)R.Yaw, (double)R.Roll, (double)S.X, (double)S.Y, (double)S.Z);
}

bool FFixedTransform::InitFromString(const FString& Source)
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

	SetComponents(FFixedQuat(FFixedRotator(ParsedRotation)), FFixedVector(ParsedTranslation), FFixedVector(ParsedScale));

	return true;
}

void FFixedTransform::GetRelativeTransformUsingMatrixWithScale(FFixedTransform* OutTransform, const FFixedTransform* Base, const FFixedTransform* Relative)
{
	// the goal of using M is to get the correct orientation
	// but for translation, we still need scale
	FFixedMatrix AM = Base->ToMatrixWithScale();
	FFixedMatrix BM = Relative->ToMatrixWithScale();
	// get combined scale
	FFixedVector SafeRecipScale3D = GetSafeScaleReciprocal(Relative->Scale3D, FixedPoint::Constants::Fixed64::SmallNumber);
	FFixedVector DesiredScale3D = Base->Scale3D * SafeRecipScale3D;
	ConstructTransformFromMatrixWithDesiredScale(AM, BM.Inverse(), DesiredScale3D, *OutTransform);
}