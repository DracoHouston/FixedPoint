// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointTypes.h"
#include "Math/BigInt.h"
#include "FixedPointNumbers.generated.h"

/**
* FFixed64
* This struct wraps an int64 and treats it as a fixed point number with a binary point of 20.
* It may be initialized based on the value of an integer, float or double.
* This number can then be used for fixed point maths when used with other FixedPoint types
* It can also be retrieved as a float, double or as a rounded integer (either 64 or 32 bit)
* Due to conversion constructors and overloaded cast operators this conversion can be done implicitly
* as if it were a basic number type.
*/
USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixed64
{
public:

	GENERATED_BODY()

	/**
	* Internal value, as int64, use accessors, setters and operators to read and write it
	*/
	UPROPERTY(EditAnywhere)
	int64 Value;

	/**
	* Default constructor, initializes at 0
	*/
	FORCEINLINE FFixed64()
	 {
		 Value = 0;
	 }
	
	/**
	* constexpr constructor, sets value to inValue directly. Able to make staticly initialized constants.
	* Second argument is ignored and only there to not collide with int64->fixed64 cast constructor.
	* Use FFixed64::MakeWithRawInt which uses this for the same purpose, to avoid confusion with other constructors.
	*/
	explicit constexpr FFixed64(int64 inValue, bool bThisIsIgnored) : Value(inValue) {}

	/**
	* Constructor that casts int64 to FFixed64
	*/
	FORCEINLINE FFixed64(int32 Other)
	{
		Value = (int64)Other << FixedPoint::Constants::BinaryPoint64;
	}

	/**
	* Constructor that casts int64 to FFixed64
	*/
	FORCEINLINE FFixed64(int64 Other)
	{
		Value = Other << FixedPoint::Constants::BinaryPoint64;
	}

	/**
	* Constructor that casts FFixed32 to FFixed64
	*/
	FORCEINLINE FFixed64(FFixed32 Other);

	/**
	* Constructor that casts double to FFixed64
	*/
	FORCEINLINE FFixed64(double Other)
	{
		Value = (int64)(Other * FixedPoint::Constants::Raw64::OneD);
	}

	/**
	* Constructor that casts float to FFixed64
	*/
	FORCEINLINE FFixed64(float Other)
	{
		Value = (int64)(Other * FixedPoint::Constants::Raw64::OneD);
	}

	/**
	* Static constexpr function that creates a new FFixed64 and sets Value directly to the supplied value
	* This may be used for staticly initialized constexpr FFixed64 constants. 
	* See FixedPoint::Constants::Fixed64 namespace below for examples.
	*/
	static constexpr FFixed64 MakeFromRawInt(int64 inValue)
	{
		return FFixed64(inValue, true);
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("%f"), (double)*this);
	}

	/**
	* Internal function to normalize within range, returns inValue if it is less than inRange and greater than 0
	* if less than 0 it adds inRange to inValue until this is no longer true, then returns that if it is less than inRange
	* in any case, if inValue is greater than or equal to inRange it will return a FFixed64 whose value is equal to inValue.Value % inRange.value
	* NOTE: this means if inValue == inRange then you will get 0
	* See: FFixed64::Sin
	*/
	static FFixed64 Internal_Normalize(const FFixed64& inValue, const FFixed64& inRange)
	{
		FFixed64 retval = inValue;
		while (retval.Value < 0)
		{
			retval += inRange;
		}
		if (retval >= inRange)
		{
			retval.Value = retval.Value % inRange.Value;
		}
		return retval;
	}

	FORCEINLINE constexpr bool operator==(const FFixed64& Other) const
	{
		return Value == Other.Value;
	}

	FORCEINLINE constexpr bool operator!=(const FFixed64& Other) const
	{
		return Value != Other.Value;
	}

	FORCEINLINE constexpr bool operator<=(const FFixed64& Other) const
	{
		return Value <= Other.Value;
	}

	FORCEINLINE constexpr bool operator>=(const FFixed64& Other) const
	{
		return Value >= Other.Value;
	}

	FORCEINLINE constexpr bool operator<(const FFixed64& Other) const
	{
		return Value < Other.Value;
	}

	FORCEINLINE constexpr bool operator>(const FFixed64& Other) const
	{
		return Value > Other.Value;
	}

	FORCEINLINE constexpr FFixed64 operator-() const
	{
		return FFixed64::MakeFromRawInt(-Value);
	}

	FORCEINLINE constexpr FFixed64 operator+(const FFixed64& Other) const
	{
		return FFixed64::MakeFromRawInt(Value + Other.Value);
	}

	FORCEINLINE constexpr FFixed64 operator-(const FFixed64& Other) const
	{
		return FFixed64::MakeFromRawInt(Value - Other.Value);
	}

	FORCEINLINE FFixed64 operator*(const FFixed64& Other) const
	{
		TBigInt<128, true> IntermediateResult = TBigInt<128, true>(Value);
		TBigInt<128, true> IntermediateOther = TBigInt<128, true>(Other.Value);
		IntermediateResult *= IntermediateOther;
		IntermediateResult.ShiftRight(FixedPoint::Constants::BinaryPoint64);
		return FFixed64::MakeFromRawInt(IntermediateResult.ToInt());
	}

	FORCEINLINE FFixed64 operator/(const FFixed64& Other) const
	{
		TBigInt<128, true> IntermediateResult = TBigInt<128, true>(Value);
		TBigInt<128, true> IntermediateOther = TBigInt<128, true>(Other.Value);
		IntermediateResult.ShiftLeft(FixedPoint::Constants::BinaryPoint64);
		IntermediateResult /= IntermediateOther;
		return FFixed64::MakeFromRawInt(IntermediateResult.ToInt());
	}

	FORCEINLINE FFixed64 operator+=(const FFixed64& Other)
	{
		Value += Other.Value;
		return *this;
	}

	FORCEINLINE FFixed64 operator-=(const FFixed64& Other)
	{
		Value -= Other.Value;
		return *this;
	}

	FORCEINLINE FFixed64 operator*=(const FFixed64& Other)
	{
		TBigInt<128, true> IntermediateResult = TBigInt<128, true>(Value);
		TBigInt<128, true> IntermediateOther = TBigInt<128, true>(Other.Value);
		IntermediateResult *= IntermediateOther;
		IntermediateResult.ShiftRight(FixedPoint::Constants::BinaryPoint64);
		Value = IntermediateResult.ToInt();
		return *this;
	}

	FORCEINLINE FFixed64 operator/=(const FFixed64& Other)
	{
		TBigInt<128, true> IntermediateResult = TBigInt<128, true>(Value);
		TBigInt<128, true> IntermediateOther = TBigInt<128, true>(Other.Value);
		IntermediateResult.ShiftLeft(FixedPoint::Constants::BinaryPoint64);
		IntermediateResult /= IntermediateOther;
		Value = IntermediateResult.ToInt();
		return *this;
	}

	//Overrides for cast operators for basic number types.

	FORCEINLINE operator double() const
	{
		return (double)(Value / FixedPoint::Constants::Raw64::OneD);
	}

	FORCEINLINE operator float() const
	{
		return (float)(Value / FixedPoint::Constants::Raw64::OneD);
	}

	FORCEINLINE operator int32() const
	{
		return (int32)(Value >> FixedPoint::Constants::BinaryPoint64);
	}

	FORCEINLINE operator int64() const
	{
		return Value >> FixedPoint::Constants::BinaryPoint64;
	}
};

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixed32
{
public:

	GENERATED_BODY()

	/**
	* Internal value, as int32, use accessors, setters and operators to read and write it
	*/
	UPROPERTY(EditAnywhere)
	int32 Value;

	/**
	* Default constructor, initializes to 0
	*/
	FORCEINLINE FFixed32()
	{
		Value = 0;
	}

	/**
	* constexpr constructor, sets value to inValue directly. Able to make staticly initialized constants.
	* Second argument is ignored and only there to not collide with int64->fixed64 cast constructor.
	* Use FFixed64::MakeWithRawInt which uses this for the same purpose, to avoid confusion with other constructors.
	*/
	explicit constexpr FFixed32(int32 inValue, bool bThisIsIgnored) : Value(inValue) {}

	/**
	* Constructor that casts int32 to FFixed32
	*/
	FORCEINLINE FFixed32(int32 Other)
	{
		Value = Other << FixedPoint::Constants::BinaryPoint32;
	}

	/**
	* Constructor that casts int64 to FFixed32
	*/
	FORCEINLINE FFixed32(int64 Other)
	{
		Value = (int32)Other << FixedPoint::Constants::BinaryPoint32;
	}

	/**
	* Constructor that casts FFixed64 to FFixed32
	*/
	FORCEINLINE FFixed32(FFixed64 Other);

	/**
	* Constructor that casts double to FFixed32
	*/
	FORCEINLINE FFixed32(double Other)
	{
		Value = (int32)(Other * FixedPoint::Constants::Raw32::OneD);
	}

	/**
	* Constructor that casts float to FFixed32
	*/
	FORCEINLINE FFixed32(float Other)
	{
		Value = (int32)(Other * FixedPoint::Constants::Raw32::OneD);
	}

	/**
	* Static constexpr function that creates a new FFixed32 and sets Value directly to the supplied value
	* This may be used for staticly initialized constexpr FFixed32 constants.
	* See FixedPoint::Constants::Fixed32 namespace below for examples.
	*/
	static constexpr FFixed32 MakeFromRawInt(int32 inValue)
	{
		return FFixed32(inValue, true);
	}	

	FString ToString() const
	{
		return FString::Printf(TEXT("%f"), (double)*this);
	}

	/**
	* Internal function to normalize within range, returns inValue if it is less than inRange and greater than 0
	* if less than 0 it adds inRange to inValue until this is no longer true, then returns that if it is less than inRange
	* in any case, if inValue is greater than or equal to inRange it will return a FFixed32 whose value is equal to inValue.Value % inRange.value
	* NOTE: this means if inValue == inRange then you will get 0
	* See: FFixed32::Sin
	*/
	static FFixed32 Internal_Normalize(const FFixed32& inValue, const FFixed32& inRange)
	{
		FFixed32 retval = inValue;
		while (retval.Value < 0)
		{
			retval += inRange;
		}
		if (retval >= inRange)
		{
			retval.Value = retval.Value % inRange.Value;
		}
		return retval;
	}

	FORCEINLINE constexpr bool operator==(const FFixed32& Other) const
	{
		return Value == Other.Value;
	}

	FORCEINLINE constexpr bool operator!=(const FFixed32& Other) const
	{
		return Value != Other.Value;
	}

	FORCEINLINE constexpr bool operator<=(const FFixed32& Other) const
	{
		return Value <= Other.Value;
	}

	FORCEINLINE constexpr bool operator>=(const FFixed32& Other) const
	{
		return Value >= Other.Value;
	}

	FORCEINLINE constexpr bool operator<(const FFixed32& Other) const
	{
		return Value < Other.Value;
	}

	FORCEINLINE constexpr bool operator>(const FFixed32& Other) const
	{
		return Value > Other.Value;
	}

	FORCEINLINE constexpr FFixed32 operator-() const
	{
		return FFixed32::MakeFromRawInt(-Value);
	}

	FORCEINLINE constexpr FFixed32 operator+(const FFixed32& Other) const
	{
		return FFixed32::MakeFromRawInt(Value + Other.Value);
	}

	FORCEINLINE constexpr FFixed32 operator-(const FFixed32& Other) const
	{
		return FFixed32::MakeFromRawInt(Value - Other.Value);
	}

	FORCEINLINE FFixed32 operator*(const FFixed32& Other) const
	{
		return FFixed32::MakeFromRawInt((int32)(((int64)Value * (int64)Other.Value) >> FixedPoint::Constants::BinaryPoint32));
	}

	FORCEINLINE FFixed32 operator/(const FFixed32& Other) const
	{
		return FFixed32::MakeFromRawInt((int32)(((int64)Value << FixedPoint::Constants::BinaryPoint32) / (int64)Other.Value));
	}

	FORCEINLINE FFixed32 operator+=(const FFixed32& Other)
	{
		Value += Other.Value;
		return *this;
	}

	FORCEINLINE FFixed32 operator-=(const FFixed32& Other)
	{
		Value -= Other.Value;
		return *this;
	}

	FORCEINLINE FFixed32 operator*=(const FFixed32& Other)
	{
		Value *= Other.Value;
		return *this;
	}

	FORCEINLINE FFixed32 operator/=(const FFixed32& Other)
	{
		Value /= Other.Value;
		return *this;
	}

	FORCEINLINE operator double() const
	{
		return (double)(Value / FixedPoint::Constants::Raw32::OneD);
	}

	FORCEINLINE operator float() const
	{
		return (float)(Value / FixedPoint::Constants::Raw32::OneD);
	}

	FORCEINLINE operator int32() const
	{
		/*if (bCeil)
		{
			return (Value + FixedPoint::Constants::Raw32::One - 1) >> FixedPoint::Constants::BinaryPoint32;
		}*/
		return Value >> FixedPoint::Constants::BinaryPoint32;
	}

	FORCEINLINE operator int64() const
	{
		return (int64)(Value >> FixedPoint::Constants::BinaryPoint32);
	}
};

namespace FixedPoint
{
	namespace Constants
	{
		namespace Fixed64
		{
			constexpr FFixed64 Zero = FFixed64::MakeFromRawInt(0);
			constexpr FFixed64 One =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One);
			constexpr FFixed64 Half =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::Half);
			constexpr FFixed64 Quarter =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::Quarter);
			constexpr FFixed64 Eigth =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::Eigth);
			constexpr FFixed64 OneEighty =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::OneEighty);
			constexpr FFixed64 ThreeSixty =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreeSixty);
			constexpr FFixed64 Pi =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::Pi);
			constexpr FFixed64 SmallNumber =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::SmallNumber);
			constexpr FFixed64 KindaSmallNumber =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::KindaSmallNumber);
			constexpr FFixed64 BigNumber =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::BigNumber);
			constexpr FFixed64 EulersNumber =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::EulersNumber);
			constexpr FFixed64 GoldenRatio =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::GoldenRatio);
			constexpr FFixed64 InvPi =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::InvPi);
			constexpr FFixed64 HalfPi =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::HalfPi);
			constexpr FFixed64 TwoPi =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::TwoPi);
			constexpr FFixed64 PiSquared =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::PiSquared);
			constexpr FFixed64 SQRT2 =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::SQRT2);
			constexpr FFixed64 SQRT3 =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::SQRT3);
			constexpr FFixed64 InvSQRT2 =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::InvSQRT2);
			constexpr FFixed64 InvSQRT3 =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::InvSQRT3);
			constexpr FFixed64 HalfSQRT2 =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::HalfSQRT2);
			constexpr FFixed64 HalfSQRT3 =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::HalfSQRT3);
			constexpr FFixed64 Delta =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::Delta);
			constexpr FFixed64 NormalThresh =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::NormalThresh);
			constexpr FFixed64 ThreshPointOnPlane =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshPointOnPlane);
			constexpr FFixed64 ThreshPointOnSide =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshPointOnSide);
			constexpr FFixed64 ThreshPointsAreSame =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshPointsAreSame);
			constexpr FFixed64 ThreshPointsAreNear =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshPointsAreNear);
			constexpr FFixed64 ThreshNormalsAreSame =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshNormalsAreSame);
			constexpr FFixed64 ThreshUVsAreSame =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshUVsAreSame);
			constexpr FFixed64 ThreshVectorsAreNear =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshVectorsAreNear);
			constexpr FFixed64 ThreshSplitPolyWithPlane =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshSplitPolyWithPlane);
			constexpr FFixed64 ThreshSplitPolyPrecisely =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshSplitPolyPrecisely);
			constexpr FFixed64 ThreshZeroNormSquared =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshZeroNormSquared);
			constexpr FFixed64 ThreshNormalsAreParallel =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshNormalsAreParallel);
			constexpr FFixed64 ThreshNormalsAreOrthogonal =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshNormalsAreOrthogonal);
			constexpr FFixed64 ThreshVectorNormalized =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshVectorNormalized);
			constexpr FFixed64 ThreshQuatNormalized =  FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::ThreshQuatNormalized);

			constexpr FFixed64 AcosMagicOne = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::AcosMagicOne);
			constexpr FFixed64 AcosMagicTwo = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::AcosMagicTwo);
			constexpr FFixed64 AcosMagicThree = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::AcosMagicThree);
		}
		namespace Fixed32
		{
			constexpr FFixed32 Zero = FFixed32::MakeFromRawInt(0);
			constexpr FFixed32 One = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::One);
			constexpr FFixed32 Half = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::Half);
			constexpr FFixed32 Quarter = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::Quarter);
			constexpr FFixed32 Eigth = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::Eigth);
			constexpr FFixed32 OneEighty = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::OneEighty);
			constexpr FFixed32 ThreeSixty = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreeSixty);
			constexpr FFixed32 Pi = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::Pi);
			constexpr FFixed32 SmallNumber = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::SmallNumber);
			constexpr FFixed32 KindaSmallNumber = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::KindaSmallNumber);
			constexpr FFixed32 BigNumber = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::BigNumber);
			constexpr FFixed32 EulersNumber = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::EulersNumber);
			constexpr FFixed32 GoldenRatio = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::GoldenRatio);
			constexpr FFixed32 InvPi = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::InvPi);
			constexpr FFixed32 HalfPi = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::HalfPi);
			constexpr FFixed32 TwoPi = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::TwoPi);
			constexpr FFixed32 PiSquared = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::PiSquared);
			constexpr FFixed32 SQRT2 = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::SQRT2);
			constexpr FFixed32 SQRT3 = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::SQRT3);
			constexpr FFixed32 InvSQRT2 = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::InvSQRT2);
			constexpr FFixed32 InvSQRT3 = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::InvSQRT3);
			constexpr FFixed32 HalfSQRT2 = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::HalfSQRT2);
			constexpr FFixed32 HalfSQRT3 = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::HalfSQRT3);
			constexpr FFixed32 Delta = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::Delta);
			constexpr FFixed32 NormalThresh = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::NormalThresh);
			constexpr FFixed32 ThreshPointOnPlane = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshPointOnPlane);
			constexpr FFixed32 ThreshPointOnSide = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshPointOnSide);
			constexpr FFixed32 ThreshPointsAreSame = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshPointsAreSame);
			constexpr FFixed32 ThreshPointsAreNear = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshPointsAreNear);
			constexpr FFixed32 ThreshNormalsAreSame = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshNormalsAreSame);
			constexpr FFixed32 ThreshUVsAreSame = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshUVsAreSame);
			constexpr FFixed32 ThreshVectorsAreNear = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshVectorsAreNear);
			constexpr FFixed32 ThreshSplitPolyWithPlane = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshSplitPolyWithPlane);
			constexpr FFixed32 ThreshSplitPolyPrecisely = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshSplitPolyPrecisely);
			constexpr FFixed32 ThreshZeroNormSquared = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshZeroNormSquared);
			constexpr FFixed32 ThreshNormalsAreParallel = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshNormalsAreParallel);
			constexpr FFixed32 ThreshNormalsAreOrthogonal = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshNormalsAreOrthogonal);
			constexpr FFixed32 ThreshVectorNormalized = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshVectorNormalized);
			constexpr FFixed32 ThreshQuatNormalized = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::ThreshQuatNormalized);
			constexpr FFixed32 AcosMagicOne = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::AcosMagicOne);
			constexpr FFixed32 AcosMagicTwo = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::AcosMagicTwo);
			constexpr FFixed32 AcosMagicThree = FFixed32::MakeFromRawInt(FixedPoint::Constants::Raw32::AcosMagicThree);
		}
	}
}

FORCEINLINE FFixed64::FFixed64(FFixed32 Other)
{
	Value = (int64)(Other.Value) << FixedPoint::Constants::BinaryPointDifference;
}

FORCEINLINE FFixed32::FFixed32(FFixed64 Other)
{
	Value = (int32)((Other.Value) >> FixedPoint::Constants::BinaryPointDifference);
}