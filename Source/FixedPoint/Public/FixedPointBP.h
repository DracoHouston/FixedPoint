// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FixedPointTypes.h"
#include "FixedPointBP.generated.h"

/**
 * Static BP function library for FixedPoint plugin
 */
UCLASS()
class FIXEDPOINT_API UFixedPointBP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 Fixed64FromDouble(const double& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static double DoubleFromFixed64(const FFixed64& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 Fixed64FromFloat(const float& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static float FloatFromFixed64(const FFixed64& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 Fixed64FromInt64(const int64& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static int64 Int64FromFixed64(const FFixed64& inValue, bool bCeil);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 Fixed64FromFixed32(const FFixed32& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 AddFixed64(const FFixed64& A, const FFixed64& B);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 SubtractFixed64(const FFixed64& A, const FFixed64& B);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 MultiplyFixed64(const FFixed64& A, const FFixed64& B);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 DivideFixed64(const FFixed64& A, const FFixed64& B);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 NegateFixed64(const FFixed64& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 SquareRootFixed64(const FFixed64& inValue);

	/**
	* Power, multiplies inValue to the power of InPower
	*/
	//UFUNCTION(BlueprintCallable, BlueprintPure)
		//static FFixed64 PowFixed64(const FFixed64& inValue, const int32& inPower);

	/**
	* Max, returns the greater of 2 FFixed64s
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 MaxFixed64(const FFixed64& A, const FFixed64& B);

	/**
	* Min, returns the lesser of 2 FFixed64s
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 MinFixed64(const FFixed64& A, const FFixed64& B);

	/**
	* Absolute value, returns a positive FFixed64 equal to the magnitude of the supplied FFixed64
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 AbsFixed64(const FFixed64& inValue);

	/**
	* Ceil, returns a whole number, rounded up, as FFixed64
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 CeilFixed64(const FFixed64& inValue);

	/**
	* Floor, returns a whole number, rounded down, as FFixed64
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 FloorFixed64(const FFixed64& inValue);

	/**
	* Clamp, returns a FFixed64 that is clamped within the range.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 ClampFixed64(const FFixed64& inValue, const FFixed64& inMin, const FFixed64& inMax);

	/**
	* Lerp, linear interpolation from A to B by Alpha percent, which should be between 0 and 1
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 LerpFixed64(const FFixed64& A, const FFixed64& B, const FFixed64& Alpha);

	/**
	* Sign, returns 1 if the value is positive, -1 if the value is negative, 0 if the value is 0
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static int32 SignFixed64(const FFixed64& inValue);

	/**
	*
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 PiFixed64();

	/**
	* 
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 NormalizeFixed64(const FFixed64& inValue, const FFixed64& inRange);

	/**
	*
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed64 SinFixed64(const FFixed64& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 Fixed32FromDouble(const double& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static double DoubleFromFixed32(const FFixed32& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 Fixed32FromFloat(const float& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static float FloatFromFixed32(const FFixed32& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 Fixed32FromInt32(const int32& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static int32 Int32FromFixed32(const FFixed32& inValue, bool bCeil);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 Fixed32FromFixed64(const FFixed64& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 AddFixed32(const FFixed32& A, const FFixed32& B);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 SubtractFixed32(const FFixed32& A, const FFixed32& B);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 MultiplyFixed32(const FFixed32& A, const FFixed32& B);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 DivideFixed32(const FFixed32& A, const FFixed32& B);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 NegateFixed32(const FFixed32& inValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 SquareRootFixed32(const FFixed32& inValue);

	/**
	* Power, multiplies inValue to the power of InPower
	*/
	/*UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 PowFixed32(const FFixed32& inValue, const int32& inPower);*/

	/**
	* Max, returns the greater of 2 FFixed32s
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 MaxFixed32(const FFixed32& A, const FFixed32& B);

	/**
	* Min, returns the lesser of 2 FFixed32s
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 MinFixed32(const FFixed32& A, const FFixed32& B);

	/**
	* Absolute value, returns a positive FFixed32 equal to the magnitude of the supplied FFixed32
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 AbsFixed32(const FFixed32& inValue);

	/**
	* Ceil, returns a whole number, rounded up, as FFixed32
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 CeilFixed32(const FFixed32& inValue);

	/**
	* Floor, returns a whole number, rounded down, as FFixed32
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 FloorFixed32(const FFixed32& inValue);

	/**
	* Clamp, returns a FFixed32 that is clamped within the range.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 ClampFixed32(const FFixed32& inValue, const FFixed32& inMin, const FFixed32& inMax);

	/**
	* Lerp, linear interpolation from A to B by Alpha percent, which should be between 0 and 1
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static FFixed32 LerpFixed32(const FFixed32& A, const FFixed32& B, const FFixed32& Alpha);

	/**
	* Sign, returns 1 if the value is positive, -1 if the value is negative, 0 if the value is 0
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static int32 SignFixed32(const FFixed32& inValue);
};
