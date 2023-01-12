// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Math/BigInt.h"
#include "FixedPointNumbers.generated.h"

namespace FixedPoint
{
	namespace Constants
	{
		//number of bits beyond the binary point for our fixed point number types. We shift by this much.
		constexpr uint8 BinaryPoint64 = 20;
		//number of bits beyond the binary point for our fixed point number types. We shift by this much.
		constexpr uint8 BinaryPoint32 = 16;
		//difference between 64 bit and 32 bit binary points, for conversion
		constexpr uint8 BinaryPointDifference = BinaryPoint64 - BinaryPoint32;

		namespace Raw64
		{
			//The value 1 in our 64 bit fixed point numbers
			constexpr int64 One = 1 << FixedPoint::Constants::BinaryPoint64;
			//The value 0.5 in our 64 bit fixed point numbers
			constexpr int64 Half = One >> 1;
			//The value 0.25 in our 64 bit fixed point numbers
			constexpr int64 Quarter = Half >> 1;
			//The value 0.125 in our 64 bit fixed point numbers
			constexpr int64 Eigth = Quarter >> 1;
			//The value 1 in our 64 bit fixed point numbers, cast to a double precision float
			constexpr double OneD = (double)One;

			//The value 180.0 in our 64 bit fixed point numbers
			constexpr int64 OneEighty = One * 180;
			//The value 360.0 in our 64 bit fixed point numbers
			constexpr int64 ThreeSixty = One * 360;

			constexpr int64 Pi = 3294198;
			constexpr int64 SmallNumber = 1;
			constexpr int64 KindaSmallNumber = 104;
			constexpr int64 BigNumber = 9223372036854775807;
			constexpr int64 EulersNumber = 2850325;
			constexpr int64 GoldenRatio = 1696631;
			constexpr int64 InvPi = 333772;
			constexpr int64 HalfPi = 1647099;
			constexpr int64 PiAndAHalf = HalfPi + Pi;
			constexpr int64 TwoPi = 6588397;
			constexpr int64 PiSquared = 10349030;
			constexpr int64 SQRT2 = 1482910;
			constexpr int64 SQRT3 = 1816186;
			constexpr int64 InvSQRT2 = 741455;
			constexpr int64 InvSQRT3 = 605395;
			constexpr int64 HalfSQRT2 = 741455;
			constexpr int64 HalfSQRT3 = 908093;
			constexpr int64 Delta = 10;
			constexpr int64 NormalThresh = 104;
			constexpr int64 ThreshPointOnPlane = 104857;
			constexpr int64 ThreshPointOnSide = 209715;
			constexpr int64 ThreshPointsAreSame = 20;
			constexpr int64 ThreshPointsAreNear = 15728;
			constexpr int64 ThreshNormalsAreSame = 20;
			constexpr int64 ThreshUVsAreSame = 1024;
			constexpr int64 ThreshVectorsAreNear = 419;
			constexpr int64 ThreshSplitPolyWithPlane = 262144;
			constexpr int64 ThreshSplitPolyPrecisely = 10485;
			constexpr int64 ThreshZeroNormSquared = 104;
			constexpr int64 ThreshNormalsAreParallel = 1048413;
			constexpr int64 ThreshNormalsAreOrthogonal = 18302;
			constexpr int64 ThreshVectorNormalized = 10485;
			constexpr int64 ThreshQuatNormalized = 10485;
		}
		namespace Raw32
		{

			//The value 1 in our 32 bit fixed point numbers
			constexpr int32 One = 1 << FixedPoint::Constants::BinaryPoint32;
			//The value 0.5 in our 32 bit fixed point numbers
			constexpr int32 Half = One >> 1;
			//The value 0.25 in our 32 bit fixed point numbers
			constexpr int32 Quarter = Half >> 1;
			//The value 0.125 in our 32 bit fixed point numbers
			constexpr int32 Eigth = Quarter >> 1;
			//The value 1 in our 32 bit fixed point numbers, cast to a double precision float
			constexpr double OneD = (double)One;

			//The value 180.0 in our 32 bit fixed point numbers
			constexpr int32 OneEighty = One * 180;
			//The value 360.0 in our 32 bit fixed point numbers
			constexpr int32 ThreeSixty = One * 360;

			constexpr int32 Pi = 205887;
			constexpr int32 SmallNumber = 1;
			constexpr int32 KindaSmallNumber = 6;
			constexpr int32 BigNumber = 2147483647;
			constexpr int32 EulersNumber = 178145;
			constexpr int32 GoldenRatio = 106039;
			constexpr int32 InvPi = 20860;
			constexpr int32 HalfPi = 102943;
			constexpr int32 TwoPi = 411774;
			constexpr int32 PiSquared = 646814;
			constexpr int32 SQRT2 = 92681;
			constexpr int32 SQRT3 = 113511;
			constexpr int32 InvSQRT2 = 46340;
			constexpr int32 InvSQRT3 = 37837;
			constexpr int32 HalfSQRT2 = 46340;
			constexpr int32 HalfSQRT3 = 56755;
			constexpr int32 Delta = 2;
			constexpr int32 NormalThresh = 6;
			constexpr int32 ThreshPointOnPlane = 6553;
			constexpr int32 ThreshPointOnSide = 13107;
			constexpr int32 ThreshPointsAreSame = 1;
			constexpr int32 ThreshPointsAreNear = 983;
			constexpr int32 ThreshNormalsAreSame = 1;
			constexpr int32 ThreshUVsAreSame = 64;
			constexpr int32 ThreshVectorsAreNear = 26;
			constexpr int32 ThreshSplitPolyWithPlane = 16384;
			constexpr int32 ThreshSplitPolyPrecisely = 655;
			constexpr int32 ThreshZeroNormSquared = 6;
			constexpr int32 ThreshNormalsAreParallel = 65525;
			constexpr int32 ThreshNormalsAreOrthogonal = 1143;
			constexpr int32 ThreshVectorNormalized = 655;
			constexpr int32 ThreshQuatNormalized = 655;
		}
	}
}

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
		const bool thisisnegative = Value < 0;
		const bool otherisnegative = Other.Value < 0;
		TBigInt<128, true> IntermediateResult = thisisnegative ? TBigInt<128, true>(-Value) : TBigInt<128, true>(Value);
		TBigInt<128, true> IntermediateOther = otherisnegative ? TBigInt<128, true>(-Other.Value) : TBigInt<128, true>(Other.Value);
		IntermediateResult *= IntermediateOther;
		IntermediateResult.ShiftRight(FixedPoint::Constants::BinaryPoint64);
		return thisisnegative != otherisnegative ? -FFixed64::MakeFromRawInt(IntermediateResult.ToInt()) : FFixed64::MakeFromRawInt(IntermediateResult.ToInt());
	}

	FORCEINLINE FFixed64 operator/(const FFixed64& Other) const
	{
		const bool thisisnegative = Value < 0;
		const bool otherisnegative = Other.Value < 0;
		TBigInt<128, true> IntermediateResult = thisisnegative ? TBigInt<128, true>(-Value) : TBigInt<128, true>(Value);
		TBigInt<128, true> IntermediateOther = otherisnegative ? TBigInt<128, true>(-Other.Value) : TBigInt<128, true>(Other.Value);
		IntermediateResult.ShiftLeft(FixedPoint::Constants::BinaryPoint64);
		IntermediateResult /= IntermediateOther;
		//if ((thisisnegative && !otherisnegative) || (!thisisnegative && otherisnegative))
		/*if (thisisnegative != otherisnegative)
		{
			return -FFixed64::MakeFromRawInt(IntermediateResult.ToInt());
		}
		else
		{
			return FFixed64::MakeFromRawInt(IntermediateResult.ToInt());
		}*/
		return thisisnegative != otherisnegative ? -FFixed64::MakeFromRawInt(IntermediateResult.ToInt()) : FFixed64::MakeFromRawInt(IntermediateResult.ToInt());
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
		const bool thisisnegative = Value < 0;
		const bool otherisnegative = Other.Value < 0;
		TBigInt<128, true> IntermediateResult = thisisnegative ? TBigInt<128, true>(-Value) : TBigInt<128, true>(Value);
		TBigInt<128, true> IntermediateOther = otherisnegative ? TBigInt<128, true>(-Other.Value) : TBigInt<128, true>(Other.Value);
		IntermediateResult *= IntermediateOther;
		IntermediateResult.ShiftRight(FixedPoint::Constants::BinaryPoint64);
		Value = thisisnegative != otherisnegative ? -IntermediateResult.ToInt() : IntermediateResult.ToInt();
		return *this;
	}

	FORCEINLINE FFixed64 operator/=(const FFixed64& Other)
	{
		const bool thisisnegative = Value < 0;
		const bool otherisnegative = Other.Value < 0;
		TBigInt<128, true> IntermediateResult = thisisnegative ? TBigInt<128, true>(-Value) : TBigInt<128, true>(Value);
		TBigInt<128, true> IntermediateOther = otherisnegative ? TBigInt<128, true>(-Other.Value) : TBigInt<128, true>(Other.Value);
		IntermediateResult.ShiftLeft(FixedPoint::Constants::BinaryPoint64);
		IntermediateResult /= IntermediateOther;
		//if ((thisisnegative && !otherisnegative) || (!thisisnegative && otherisnegative))
		/*if (thisisnegative != otherisnegative)
		{
			Value = -IntermediateResult.ToInt();
		}
		else
		{
			Value = IntermediateResult.ToInt();
		}*/
		Value = thisisnegative != otherisnegative ? -IntermediateResult.ToInt() : IntermediateResult.ToInt();
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
		/*const bool thisisnegative = Value < 0;
		const bool otherisnegative = Other.Value < 0;
		int64 IntermediateResult = thisisnegative ? -Value : Value;
		int64 IntermediateOther = otherisnegative ? -Other.Value : Other.Value;
		IntermediateResult *= IntermediateOther;
		IntermediateResult >> FixedPoint::Constants::BinaryPoint32;
		return (int32)IntermediateResult;*/
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
		*this = *this * Other;
		return *this;
	}

	FORCEINLINE FFixed32 operator/=(const FFixed32& Other)
	{
		*this = *this / Other;
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
			constexpr FFixed64 PiAndAHalf = FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::PiAndAHalf);
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
			constexpr FFixed64 ZeroAnimWeightThresh = FFixed64::MakeFromRawInt(10);		//0.00001f

			constexpr FFixed64 InvTrigMagicOne = FFixed64::MakeFromRawInt(-19639);		//-0.0187293
			constexpr FFixed64 InvTrigMagicTwo = FFixed64::MakeFromRawInt(77868);		//0.0742610
			constexpr FFixed64 InvTrigMagicThree = FFixed64::MakeFromRawInt(222418);	//0.2121144
			constexpr FFixed64 AtanMagicOne = FFixed64::MakeFromRawInt(7563);			//+7.2128853633444123e-03f
			constexpr FFixed64 AtanMagicTwo = FFixed64::MakeFromRawInt(-36762);			//-3.5059680836411644e-02f
			constexpr FFixed64 AtanMagicThree = FFixed64::MakeFromRawInt(85643);		//+8.1675882859940430e-02f
			constexpr FFixed64 AtanMagicFour = FFixed64::MakeFromRawInt(-140243);		//-1.3374657325451267e-01f
			constexpr FFixed64 AtanMagicFive = FFixed64::MakeFromRawInt(208211);		//+1.9856563505717162e-01f
			constexpr FFixed64 AtanMagicSix = FFixed64::MakeFromRawInt(-349437);		//-3.3324998579202170e-01f
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
			constexpr FFixed32 ZeroAnimWeightThresh = FFixed32::MakeFromRawInt(1);  //too small for precision, so just Small Number
			constexpr FFixed32 InvTrigMagicOne = FFixed32::MakeFromRawInt(-1227);	//-0.0187293
			constexpr FFixed32 InvTrigMagicTwo = FFixed32::MakeFromRawInt(4866);	//0.0742610
			constexpr FFixed32 InvTrigMagicThree = FFixed32::MakeFromRawInt(13901);	//0.2121144
			constexpr FFixed32 AtanMagicOne = FFixed32::MakeFromRawInt(472);		//+7.2128853633444123e-03f
			constexpr FFixed32 AtanMagicTwo = FFixed32::MakeFromRawInt(-2297);		//-3.5059680836411644e-02f
			constexpr FFixed32 AtanMagicThree = FFixed32::MakeFromRawInt(5352);		//+8.1675882859940430e-02f
			constexpr FFixed32 AtanMagicFour = FFixed32::MakeFromRawInt(-8765);		//-1.3374657325451267e-01f
			constexpr FFixed32 AtanMagicFive = FFixed32::MakeFromRawInt(13013);		//+1.9856563505717162e-01f
			constexpr FFixed32 AtanMagicSix = FFixed32::MakeFromRawInt(-21839);		//-3.3324998579202170e-01f
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

template<>
struct TCustomLerp<FFixed64>
{
	enum { Value = true };

	static FORCEINLINE_DEBUGGABLE FFixed64 Lerp(const FFixed64& A, const FFixed64& B, const FFixed64& Alpha)
	{
		return A + Alpha * (B - A);
	}
};

template<>
struct TCustomLerp<FFixed32>
{
	enum { Value = true };

	static FORCEINLINE_DEBUGGABLE FFixed32 Lerp(const FFixed32& A, const FFixed32& B, const FFixed32& Alpha)
	{
		return A + Alpha * (B - A);
	}
};
