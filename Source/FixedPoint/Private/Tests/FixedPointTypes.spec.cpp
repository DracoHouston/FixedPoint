// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/AutomationTest.h"
#include "FixedPointNumbers.h"
#include "FixedPointMath.h"

BEGIN_DEFINE_SPEC(FFixedPointSpec, "FixedPoint.FixedPointSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
    TSharedPtr<FFixed64> TestFixed64;
    TSharedPtr<FFixed32> TestFixed32;
END_DEFINE_SPEC(FFixedPointSpec);

void FFixedPointSpec::Define()
{
    Describe("Fixed Point Maths", [this]()
    {
        It("Should be equal to the constant One times 42", [this]()
        {
            TestFixed64 = MakeShared<FFixed64>((double)42.0);
            TestTrue("Is Equal to One times 42", ((FixedPoint::Constants::Raw64::One * 42) == (TestFixed64->Value)));
        });
        It("Should calculate square root of 16", [this]()
        {
            //TestFixed64 = MakeShared<FFixed64>(16);
            FFixed64 result = FFixedPointMath::Sqrt(FFixed64((int64)16));
            TestTrue("Is Equal to One times 4", ((FixedPoint::Constants::Raw64::One * 4) == (result.Value)));
        });
    });
}
