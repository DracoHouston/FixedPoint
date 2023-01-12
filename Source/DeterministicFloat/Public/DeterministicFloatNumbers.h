// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatNumbers.generated.h"

/**
* FDeterministicNumber64
* This struct wraps a double and forces all flops to go through functions that can't be inlined
* It may be initialized based on the value of an integer, float or double.
* This number can then be used for deterministic maths when used with other DeterministicFloat types
* It can also be retrieved as a float, double or as a rounded integer (either 64 or 32 bit)
* Due to conversion constructors and overloaded cast operators this conversion can be done implicitly
* as if it were a basic number type.
*/
USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicNumber64
{
public:

	GENERATED_BODY()

	/**
	* Internal value, as double, use accessors, setters and operators to read and write it
	*/
	UPROPERTY(EditAnywhere)
	double Value;

	/**
	* Default constructor, initializes at 0
	*/
	FORCEINLINE FDeterministicNumber64()
	 {
		 Value = 0.0;
	 }
	
	/**
	* constexpr constructor, sets value to inValue directly. Able to make staticly initialized constants.
	* Second argument is ignored and only there to not collide with double->deterministic64 cast constructor.
	* Use FDeterministicNumber64::Make which uses this for the same purpose, to avoid confusion with other constructors.
	*/
	explicit constexpr FDeterministicNumber64(double inValue, bool bThisIsIgnored) : Value(inValue) {}

	/**
	* Constructor that casts int64 to FDeterministicNumber64
	*/
	FORCEINLINE FDeterministicNumber64(int32 Other)
	{
		Value = (double)Other;
	}

	/**
	* Constructor that casts int64 to FDeterministicNumber64
	*/
	FORCEINLINE FDeterministicNumber64(int64 Other)
	{
		Value = (double)Other;
	}

	/**
	* Constructor that casts FDeterministicNumber32 to FDeterministicNumber64
	*/
	FORCEINLINE FDeterministicNumber64(FDeterministicNumber32 Other);

	/**
	* Constructor that casts double to FDeterministicNumber64
	*/
	FORCEINLINE FDeterministicNumber64(double Other)
	{
		Value = Other;
	}

	/**
	* Constructor that casts float to FDeterministicNumber64
	*/
	FORCEINLINE FDeterministicNumber64(float Other)
	{
		Value = (double)Other;
	}

	/**
	* Static constexpr function that creates a new FDeterministicNumber64 and sets Value directly to the supplied value
	* This may be used for staticly initialized constexpr FDeterministicNumber64 constants. 
	* See DeterministicFloat::Constants::Fixed64 namespace below for examples.
	*/
	static constexpr FDeterministicNumber64 Make(double inValue)
	{
		return FDeterministicNumber64(inValue, true);
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("%f"), (double)*this);
	}

	FORCEINLINE constexpr bool operator==(const FDeterministicNumber64& Other) const
	{
		return Value == Other.Value;
	}

	FORCEINLINE constexpr bool operator!=(const FDeterministicNumber64& Other) const
	{
		return Value != Other.Value;
	}

	FORCEINLINE constexpr bool operator<=(const FDeterministicNumber64& Other) const
	{
		return Value <= Other.Value;
	}

	FORCEINLINE constexpr bool operator>=(const FDeterministicNumber64& Other) const
	{
		return Value >= Other.Value;
	}

	FORCEINLINE constexpr bool operator<(const FDeterministicNumber64& Other) const
	{
		return Value < Other.Value;
	}

	FORCEINLINE constexpr bool operator>(const FDeterministicNumber64& Other) const
	{
		return Value > Other.Value;
	}

	FORCEINLINE constexpr FDeterministicNumber64 operator-() const
	{
		return FDeterministicNumber64::Make(-Value);
	}

	FORCEINLINE static double AddFast(const FDeterministicNumber64& A, const FDeterministicNumber64& B)
	{
		return A.Value + B.Value;
	}

	FORCENOINLINE double static AddSlow(const FDeterministicNumber64& A, const FDeterministicNumber64& B);

	FORCEINLINE static double SubtractFast(const FDeterministicNumber64& A, const FDeterministicNumber64& B)
	{
		return A.Value - B.Value;
	}

	FORCENOINLINE double static SubtractSlow(const FDeterministicNumber64& A, const FDeterministicNumber64& B);

	FORCEINLINE static double MultiplyFast(const FDeterministicNumber64& A, const FDeterministicNumber64& B)
	{
		return A.Value * B.Value;
	}

	FORCENOINLINE double static MultiplySlow(const FDeterministicNumber64& A, const FDeterministicNumber64& B);

	FORCEINLINE static double DivideFast(const FDeterministicNumber64& A, const FDeterministicNumber64& B)
	{
		return A.Value / B.Value;
	}

	FORCENOINLINE double static DivideSlow(const FDeterministicNumber64& A, const FDeterministicNumber64& B);

	FORCEINLINE constexpr FDeterministicNumber64 operator+(const FDeterministicNumber64& Other) const
	{
		return FDeterministicNumber64::Make(AddSlow(*this, Other));
	}

	FORCEINLINE constexpr FDeterministicNumber64 operator-(const FDeterministicNumber64& Other) const
	{
		return FDeterministicNumber64::Make(SubtractSlow(*this, Other));
	}
	
	FORCEINLINE FDeterministicNumber64 operator*(const FDeterministicNumber64& Other) const
	{
		return FDeterministicNumber64::Make(MultiplySlow(*this, Other));
	}

	FORCEINLINE FDeterministicNumber64 operator/(const FDeterministicNumber64& Other) const
	{
		return FDeterministicNumber64::Make(DivideSlow(*this, Other));
	}

	FORCEINLINE FDeterministicNumber64 operator+=(const FDeterministicNumber64& Other)
	{
		Value = AddSlow(*this, Other);
		return *this;
	}

	FORCEINLINE FDeterministicNumber64 operator-=(const FDeterministicNumber64& Other)
	{
		Value = SubtractSlow(*this, Other);
		return *this;
	}

	FORCEINLINE FDeterministicNumber64 operator*=(const FDeterministicNumber64& Other)
	{
		Value = MultiplySlow(*this, Other);
		return *this;
	}

	FORCEINLINE FDeterministicNumber64 operator/=(const FDeterministicNumber64& Other)
	{
		Value = DivideSlow(*this, Other);
		return *this;
	}

	//Overrides for cast operators for basic number types.

	FORCEINLINE operator double() const
	{
		return Value;
	}

	FORCEINLINE operator float() const
	{
		return (float)Value;
	}

	FORCEINLINE operator int32() const
	{
		return (int32)Value;
	}

	FORCEINLINE operator int64() const
	{
		return (int64)Value;
	}
};

/**
* FDeterministicNumber32
* This struct wraps a float and forces all flops to go through functions that can't be inlined
* It may be initialized based on the value of an integer, float or double.
* This number can then be used for deterministic maths when used with other DeterministicFloat types
* It can also be retrieved as a float, double or as a rounded integer (either 64 or 32 bit)
* Due to conversion constructors and overloaded cast operators this conversion can be done implicitly
* as if it were a basic number type.
*/
USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicNumber32
{
public:

	GENERATED_BODY()

	/**
	* Internal value, as float, use accessors, setters and operators to read and write it
	*/
	UPROPERTY(EditAnywhere)
	float Value;

	/**
	* Default constructor, initializes to 0
	*/
	FORCEINLINE FDeterministicNumber32()
	{
		Value = 0.0f;
	}

	/**
	* constexpr constructor, sets value to inValue directly. Able to make staticly initialized constants.
	* Second argument is ignored and only there to not collide with float->number32 cast constructor.
	* Use FDeterministicNumber32::Make which uses this for the same purpose, to avoid confusion with other constructors.
	*/
	explicit constexpr FDeterministicNumber32(float inValue, bool bThisIsIgnored) : Value(inValue) {}

	/**
	* Constructor that casts int32 to FDeterministicNumber32
	*/
	FORCEINLINE FDeterministicNumber32(int32 Other)
	{
		Value = (float)Other;
	}

	/**
	* Constructor that casts int64 to FDeterministicNumber32
	*/
	FORCEINLINE FDeterministicNumber32(int64 Other)
	{
		Value = (float)Other;
	}

	/**
	* Constructor that casts FDeterministicNumber64 to FDeterministicNumber32
	*/
	FORCEINLINE FDeterministicNumber32(FDeterministicNumber64 Other);

	/**
	* Constructor that casts double to FDeterministicNumber32
	*/
	FORCEINLINE FDeterministicNumber32(double Other)
	{
		Value = (float)Other;
	}

	/**
	* Constructor that casts float to FDeterministicNumber32
	*/
	FORCEINLINE FDeterministicNumber32(float Other)
	{
		Value = Other;
	}

	/**
	* Static constexpr function that creates a new FDeterministicNumber32 and sets Value directly to the supplied value
	* This may be used for staticly initialized constexpr FDeterministicNumber32 constants.
	* See DeterministicFloat::Constants::Fixed32 namespace below for examples.
	*/
	static constexpr FDeterministicNumber32 Make(float inValue)
	{
		return FDeterministicNumber32(inValue, true);
	}	

	FString ToString() const
	{
		return FString::Printf(TEXT("%f"), (float)*this);
	}

	FORCEINLINE constexpr bool operator==(const FDeterministicNumber32& Other) const
	{
		return Value == Other.Value;
	}

	FORCEINLINE constexpr bool operator!=(const FDeterministicNumber32& Other) const
	{
		return Value != Other.Value;
	}

	FORCEINLINE constexpr bool operator<=(const FDeterministicNumber32& Other) const
	{
		return Value <= Other.Value;
	}

	FORCEINLINE constexpr bool operator>=(const FDeterministicNumber32& Other) const
	{
		return Value >= Other.Value;
	}

	FORCEINLINE constexpr bool operator<(const FDeterministicNumber32& Other) const
	{
		return Value < Other.Value;
	}

	FORCEINLINE constexpr bool operator>(const FDeterministicNumber32& Other) const
	{
		return Value > Other.Value;
	}

	FORCEINLINE constexpr FDeterministicNumber32 operator-() const
	{
		return FDeterministicNumber32::Make(-Value);
	}

	FORCEINLINE static float AddFast(const FDeterministicNumber32& A, const FDeterministicNumber32& B)
	{
		return A.Value + B.Value;
	}

	FORCENOINLINE static float AddSlow(const FDeterministicNumber32& A, const FDeterministicNumber32& B);

	FORCEINLINE static float SubtractFast(const FDeterministicNumber32& A, const FDeterministicNumber32& B)
	{
		return A.Value - B.Value;
	}

	FORCENOINLINE static float SubtractSlow(const FDeterministicNumber32& A, const FDeterministicNumber32& B);

	FORCEINLINE static float MultiplyFast(const FDeterministicNumber32& A, const FDeterministicNumber32& B)
	{
		return A.Value * B.Value;
	}

	FORCENOINLINE static float MultiplySlow(const FDeterministicNumber32& A, const FDeterministicNumber32& B);

	FORCEINLINE static float DivideFast(const FDeterministicNumber32& A, const FDeterministicNumber32& B)
	{
		return A.Value / B.Value;
	}

	FORCENOINLINE static float DivideSlow(const FDeterministicNumber32& A, const FDeterministicNumber32& B);

	FORCEINLINE constexpr FDeterministicNumber32 operator+(const FDeterministicNumber32& Other) const
	{
		return FDeterministicNumber32::Make(AddSlow(*this, Other));
	}

	FORCEINLINE constexpr FDeterministicNumber32 operator-(const FDeterministicNumber32& Other) const
	{
		return FDeterministicNumber32::Make(SubtractSlow(*this, Other));
	}

	FORCEINLINE FDeterministicNumber32 operator*(const FDeterministicNumber32& Other) const
	{
		return FDeterministicNumber32::Make(MultiplySlow(*this, Other));
	}

	FORCEINLINE FDeterministicNumber32 operator/(const FDeterministicNumber32& Other) const
	{
		return FDeterministicNumber32::Make(DivideSlow(*this, Other));
	}

	FORCEINLINE FDeterministicNumber32 operator+=(const FDeterministicNumber32& Other)
	{
		Value = AddSlow(*this, Other);
		return *this;
	}

	FORCEINLINE FDeterministicNumber32 operator-=(const FDeterministicNumber32& Other)
	{
		Value = SubtractSlow(*this, Other);
		return *this;
	}

	FORCEINLINE FDeterministicNumber32 operator*=(const FDeterministicNumber32& Other)
	{
		Value = MultiplySlow(*this, Other);
		return *this;
	}

	FORCEINLINE FDeterministicNumber32 operator/=(const FDeterministicNumber32& Other)
	{
		Value = DivideSlow(*this, Other);
		return *this;
	}

	FORCEINLINE operator double() const
	{
		return (double)Value;
	}

	FORCEINLINE operator float() const
	{
		return Value;
	}

	FORCEINLINE operator int32() const
	{
		return (int32)Value;
	}

	FORCEINLINE operator int64() const
	{
		return (int64)Value;
	}
};

namespace DeterministicFloat
{
	namespace Constants
	{
		namespace Number64
		{
			constexpr FDeterministicNumber64 Zero = FDeterministicNumber64::Make(0.0);
			constexpr FDeterministicNumber64 One =  FDeterministicNumber64::Make(1.0);
			constexpr FDeterministicNumber64 Half =  FDeterministicNumber64::Make(0.5);
			constexpr FDeterministicNumber64 Quarter =  FDeterministicNumber64::Make(0.25);
			constexpr FDeterministicNumber64 Eigth =  FDeterministicNumber64::Make(0.125);
			constexpr FDeterministicNumber64 OneEightyOverPi = FDeterministicNumber64::Make(180.0/UE_DOUBLE_PI);
			constexpr FDeterministicNumber64 PiOverOneEighty = FDeterministicNumber64::Make(UE_DOUBLE_PI / 180.0);
			constexpr FDeterministicNumber64 OneEighty =  FDeterministicNumber64::Make(180.0);
			constexpr FDeterministicNumber64 ThreeSixty =  FDeterministicNumber64::Make(360.0);
			constexpr FDeterministicNumber64 Pi =  FDeterministicNumber64::Make(UE_DOUBLE_PI);
			constexpr FDeterministicNumber64 SmallNumber =  FDeterministicNumber64::Make(UE_DOUBLE_SMALL_NUMBER);
			constexpr FDeterministicNumber64 KindaSmallNumber =  FDeterministicNumber64::Make(UE_DOUBLE_KINDA_SMALL_NUMBER);
			constexpr FDeterministicNumber64 BigNumber =  FDeterministicNumber64::Make(UE_DOUBLE_BIG_NUMBER);
			constexpr FDeterministicNumber64 EulersNumber =  FDeterministicNumber64::Make(UE_DOUBLE_EULERS_NUMBER);
			constexpr FDeterministicNumber64 GoldenRatio =  FDeterministicNumber64::Make(UE_DOUBLE_GOLDEN_RATIO);
			constexpr FDeterministicNumber64 InvPi =  FDeterministicNumber64::Make(UE_DOUBLE_INV_PI);
			constexpr FDeterministicNumber64 HalfPi =  FDeterministicNumber64::Make(UE_DOUBLE_HALF_PI);
			constexpr FDeterministicNumber64 PiAndAHalf = FDeterministicNumber64::Make(UE_DOUBLE_PI + UE_DOUBLE_HALF_PI);
			constexpr FDeterministicNumber64 TwoPi =  FDeterministicNumber64::Make(UE_DOUBLE_TWO_PI);
			constexpr FDeterministicNumber64 PiSquared =  FDeterministicNumber64::Make(UE_DOUBLE_PI_SQUARED);
			constexpr FDeterministicNumber64 SQRT2 =  FDeterministicNumber64::Make(UE_DOUBLE_SQRT_2);
			constexpr FDeterministicNumber64 SQRT3 =  FDeterministicNumber64::Make(UE_DOUBLE_SQRT_3);
			constexpr FDeterministicNumber64 InvSQRT2 =  FDeterministicNumber64::Make(UE_DOUBLE_INV_SQRT_2);
			constexpr FDeterministicNumber64 InvSQRT3 =  FDeterministicNumber64::Make(UE_DOUBLE_INV_SQRT_3);
			constexpr FDeterministicNumber64 HalfSQRT2 =  FDeterministicNumber64::Make(UE_DOUBLE_HALF_SQRT_2);
			constexpr FDeterministicNumber64 HalfSQRT3 =  FDeterministicNumber64::Make(UE_DOUBLE_HALF_SQRT_3);
			constexpr FDeterministicNumber64 Delta =  FDeterministicNumber64::Make(UE_DOUBLE_DELTA);
			constexpr FDeterministicNumber64 NormalThresh =  FDeterministicNumber64::Make(UE_DOUBLE_NORMAL_THRESH);
			constexpr FDeterministicNumber64 ThreshPointOnPlane =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_POINT_ON_PLANE);
			constexpr FDeterministicNumber64 ThreshPointOnSide =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_POINT_ON_SIDE);
			constexpr FDeterministicNumber64 ThreshPointsAreSame =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_POINTS_ARE_SAME);
			constexpr FDeterministicNumber64 ThreshPointsAreNear =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_POINTS_ARE_NEAR);
			constexpr FDeterministicNumber64 ThreshNormalsAreSame =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_NORMALS_ARE_SAME);
			constexpr FDeterministicNumber64 ThreshUVsAreSame =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_UVS_ARE_SAME);
			constexpr FDeterministicNumber64 ThreshVectorsAreNear =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_VECTORS_ARE_NEAR);
			constexpr FDeterministicNumber64 ThreshSplitPolyWithPlane =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_SPLIT_POLY_WITH_PLANE);
			constexpr FDeterministicNumber64 ThreshSplitPolyPrecisely =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_SPLIT_POLY_PRECISELY);
			constexpr FDeterministicNumber64 ThreshZeroNormSquared =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_ZERO_NORM_SQUARED);
			constexpr FDeterministicNumber64 ThreshNormalsAreParallel =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_NORMALS_ARE_PARALLEL);
			constexpr FDeterministicNumber64 ThreshNormalsAreOrthogonal =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_NORMALS_ARE_ORTHOGONAL);
			constexpr FDeterministicNumber64 ThreshVectorNormalized =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_VECTOR_NORMALIZED);
			constexpr FDeterministicNumber64 ThreshQuatNormalized =  FDeterministicNumber64::Make(UE_DOUBLE_THRESH_QUAT_NORMALIZED);
			constexpr FDeterministicNumber64 ZeroAnimWeightThresh = FDeterministicNumber64::Make(0.00001);

			constexpr FDeterministicNumber64 FactorialOne = FDeterministicNumber64::Make(1.0);
			constexpr FDeterministicNumber64 FactorialTwo = FDeterministicNumber64::Make(2.0);
			constexpr FDeterministicNumber64 FactorialThree = FDeterministicNumber64::Make(6.0);
			constexpr FDeterministicNumber64 FactorialFour = FDeterministicNumber64::Make(24.0);
			constexpr FDeterministicNumber64 FactorialFive = FDeterministicNumber64::Make(120.0);
			constexpr FDeterministicNumber64 FactorialSix = FDeterministicNumber64::Make(720.0);
			constexpr FDeterministicNumber64 FactorialSeven = FDeterministicNumber64::Make(5040.0);
			constexpr FDeterministicNumber64 FactorialEight = FDeterministicNumber64::Make(40320.0);
			constexpr FDeterministicNumber64 InvTrigMagicOne = FDeterministicNumber64::Make(-0.0187293);		//-0.0187293
			constexpr FDeterministicNumber64 InvTrigMagicTwo = FDeterministicNumber64::Make(0.0742610);		//0.0742610
			constexpr FDeterministicNumber64 InvTrigMagicThree = FDeterministicNumber64::Make(0.2121144);	//0.2121144
			constexpr FDeterministicNumber64 AtanMagicOne = FDeterministicNumber64::Make(+7.2128853633444123e-03);			//+7.2128853633444123e-03f
			constexpr FDeterministicNumber64 AtanMagicTwo = FDeterministicNumber64::Make(-3.5059680836411644e-02);			//-3.5059680836411644e-02f
			constexpr FDeterministicNumber64 AtanMagicThree = FDeterministicNumber64::Make(+8.1675882859940430e-02);		//+8.1675882859940430e-02f
			constexpr FDeterministicNumber64 AtanMagicFour = FDeterministicNumber64::Make(-1.3374657325451267e-01);		//-1.3374657325451267e-01f
			constexpr FDeterministicNumber64 AtanMagicFive = FDeterministicNumber64::Make(+1.9856563505717162e-01);		//+1.9856563505717162e-01f
			constexpr FDeterministicNumber64 AtanMagicSix = FDeterministicNumber64::Make(-3.3324998579202170e-01);		//-3.3324998579202170e-01f
		}
		namespace Number32
		{
			constexpr FDeterministicNumber32 Zero = FDeterministicNumber32::Make(0.0f);
			constexpr FDeterministicNumber32 One = FDeterministicNumber32::Make(1.0f);
			constexpr FDeterministicNumber32 Half = FDeterministicNumber32::Make(0.5f);
			constexpr FDeterministicNumber32 Quarter = FDeterministicNumber32::Make(0.25f);
			constexpr FDeterministicNumber32 Eigth = FDeterministicNumber32::Make(0.125f);
			constexpr FDeterministicNumber32 OneEightyOverPi = FDeterministicNumber32::Make(180.0f / UE_PI);
			constexpr FDeterministicNumber32 PiOverOneEighty = FDeterministicNumber32::Make(UE_PI / 180.0f);
			constexpr FDeterministicNumber32 OneEighty = FDeterministicNumber32::Make(180.0f);
			constexpr FDeterministicNumber32 ThreeSixty = FDeterministicNumber32::Make(360.0f);
			constexpr FDeterministicNumber32 Pi = FDeterministicNumber32::Make(UE_PI);
			constexpr FDeterministicNumber32 SmallNumber = FDeterministicNumber32::Make(UE_SMALL_NUMBER);
			constexpr FDeterministicNumber32 KindaSmallNumber = FDeterministicNumber32::Make(UE_KINDA_SMALL_NUMBER);
			constexpr FDeterministicNumber32 BigNumber = FDeterministicNumber32::Make(UE_BIG_NUMBER);
			constexpr FDeterministicNumber32 EulersNumber = FDeterministicNumber32::Make(UE_EULERS_NUMBER);
			constexpr FDeterministicNumber32 GoldenRatio = FDeterministicNumber32::Make(UE_GOLDEN_RATIO);
			constexpr FDeterministicNumber32 InvPi = FDeterministicNumber32::Make(UE_INV_PI);
			constexpr FDeterministicNumber32 HalfPi = FDeterministicNumber32::Make(UE_HALF_PI);
			constexpr FDeterministicNumber32 TwoPi = FDeterministicNumber32::Make(UE_TWO_PI);
			constexpr FDeterministicNumber32 PiSquared = FDeterministicNumber32::Make(UE_PI_SQUARED);
			constexpr FDeterministicNumber32 SQRT2 = FDeterministicNumber32::Make(UE_SQRT_2);
			constexpr FDeterministicNumber32 SQRT3 = FDeterministicNumber32::Make(UE_SQRT_3);
			constexpr FDeterministicNumber32 InvSQRT2 = FDeterministicNumber32::Make(UE_INV_SQRT_2);
			constexpr FDeterministicNumber32 InvSQRT3 = FDeterministicNumber32::Make(UE_INV_SQRT_3);
			constexpr FDeterministicNumber32 HalfSQRT2 = FDeterministicNumber32::Make(UE_HALF_SQRT_2);
			constexpr FDeterministicNumber32 HalfSQRT3 = FDeterministicNumber32::Make(UE_HALF_SQRT_3);
			constexpr FDeterministicNumber32 Delta = FDeterministicNumber32::Make(UE_DELTA);
			constexpr FDeterministicNumber32 NormalThresh = FDeterministicNumber32::Make(FLOAT_NORMAL_THRESH);
			constexpr FDeterministicNumber32 ThreshPointOnPlane = FDeterministicNumber32::Make(UE_THRESH_POINT_ON_PLANE);
			constexpr FDeterministicNumber32 ThreshPointOnSide = FDeterministicNumber32::Make(UE_THRESH_POINT_ON_SIDE);
			constexpr FDeterministicNumber32 ThreshPointsAreSame = FDeterministicNumber32::Make(UE_THRESH_POINTS_ARE_SAME);
			constexpr FDeterministicNumber32 ThreshPointsAreNear = FDeterministicNumber32::Make(UE_THRESH_POINTS_ARE_NEAR);
			constexpr FDeterministicNumber32 ThreshNormalsAreSame = FDeterministicNumber32::Make(UE_THRESH_NORMALS_ARE_SAME);
			constexpr FDeterministicNumber32 ThreshUVsAreSame = FDeterministicNumber32::Make(UE_THRESH_UVS_ARE_SAME);
			constexpr FDeterministicNumber32 ThreshVectorsAreNear = FDeterministicNumber32::Make(UE_THRESH_VECTORS_ARE_NEAR);
			constexpr FDeterministicNumber32 ThreshSplitPolyWithPlane = FDeterministicNumber32::Make(UE_THRESH_SPLIT_POLY_WITH_PLANE);
			constexpr FDeterministicNumber32 ThreshSplitPolyPrecisely = FDeterministicNumber32::Make(UE_THRESH_SPLIT_POLY_PRECISELY);
			constexpr FDeterministicNumber32 ThreshZeroNormSquared = FDeterministicNumber32::Make(UE_THRESH_ZERO_NORM_SQUARED);
			constexpr FDeterministicNumber32 ThreshNormalsAreParallel = FDeterministicNumber32::Make(UE_THRESH_NORMALS_ARE_PARALLEL);
			constexpr FDeterministicNumber32 ThreshNormalsAreOrthogonal = FDeterministicNumber32::Make(UE_THRESH_NORMALS_ARE_ORTHOGONAL);
			constexpr FDeterministicNumber32 ThreshVectorNormalized = FDeterministicNumber32::Make(UE_THRESH_VECTOR_NORMALIZED);
			constexpr FDeterministicNumber32 ThreshQuatNormalized = FDeterministicNumber32::Make(UE_THRESH_QUAT_NORMALIZED);
			constexpr FDeterministicNumber32 ZeroAnimWeightThresh = FDeterministicNumber32::Make(0.00001f);  

			constexpr FDeterministicNumber32 FactorialOne = FDeterministicNumber32::Make(1.0f);
			constexpr FDeterministicNumber32 FactorialTwo = FDeterministicNumber32::Make(2.0f);
			constexpr FDeterministicNumber32 FactorialThree = FDeterministicNumber32::Make(6.0f);
			constexpr FDeterministicNumber32 FactorialFour = FDeterministicNumber32::Make(24.0f);
			constexpr FDeterministicNumber32 FactorialFive = FDeterministicNumber32::Make(120.0f);
			constexpr FDeterministicNumber32 FactorialSix = FDeterministicNumber32::Make(720.0f);
			constexpr FDeterministicNumber32 FactorialSeven = FDeterministicNumber32::Make(5040.0f);
			constexpr FDeterministicNumber32 FactorialEight = FDeterministicNumber32::Make(40320.0f);
			constexpr FDeterministicNumber32 InvTrigMagicOne = FDeterministicNumber32::Make(-0.0187293f);	//-0.0187293
			constexpr FDeterministicNumber32 InvTrigMagicTwo = FDeterministicNumber32::Make(0.0742610f);	//0.0742610
			constexpr FDeterministicNumber32 InvTrigMagicThree = FDeterministicNumber32::Make(0.2121144f);	//0.2121144
			constexpr FDeterministicNumber32 AtanMagicOne = FDeterministicNumber32::Make(+7.2128853633444123e-03f);		//+7.2128853633444123e-03f
			constexpr FDeterministicNumber32 AtanMagicTwo = FDeterministicNumber32::Make(-3.5059680836411644e-02f);		//-3.5059680836411644e-02f
			constexpr FDeterministicNumber32 AtanMagicThree = FDeterministicNumber32::Make(+8.1675882859940430e-02f);		//+8.1675882859940430e-02f
			constexpr FDeterministicNumber32 AtanMagicFour = FDeterministicNumber32::Make(-1.3374657325451267e-01f);		//-1.3374657325451267e-01f
			constexpr FDeterministicNumber32 AtanMagicFive = FDeterministicNumber32::Make(+1.9856563505717162e-01f);		//+1.9856563505717162e-01f
			constexpr FDeterministicNumber32 AtanMagicSix = FDeterministicNumber32::Make(-3.3324998579202170e-01f);		//-3.3324998579202170e-01f
		}
	}
}

FORCEINLINE FDeterministicNumber64::FDeterministicNumber64(FDeterministicNumber32 Other)
{
	Value = (double)Other.Value;
}

FORCEINLINE FDeterministicNumber32::FDeterministicNumber32(FDeterministicNumber64 Other)
{
	Value = (float)Other.Value;
}

template<>
struct TCustomLerp<FDeterministicNumber64>
{
	enum { Value = true };

	static FORCEINLINE_DEBUGGABLE FDeterministicNumber64 Lerp(const FDeterministicNumber64& A, const FDeterministicNumber64& B, const FDeterministicNumber64& Alpha)
	{
		return A + Alpha * (B - A);
	}
};

template<>
struct TCustomLerp<FDeterministicNumber32>
{
	enum { Value = true };

	static FORCEINLINE_DEBUGGABLE FDeterministicNumber32 Lerp(const FDeterministicNumber32& A, const FDeterministicNumber32& B, const FDeterministicNumber32& Alpha)
	{
		return A + Alpha * (B - A);
	}
};
