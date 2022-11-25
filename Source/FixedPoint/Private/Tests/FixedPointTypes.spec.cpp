// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/AutomationTest.h"
#include "FixedPointTypes.h"

BEGIN_DEFINE_SPEC(FFixedPointSpec, "FixedPoint.FixedPointSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
    TSharedPtr<FFixed64> TestFixed64;
    TSharedPtr<FFixed32> TestFixed32;
END_DEFINE_SPEC(FFixedPointSpec);

void FFixedPointSpec::Define()
{
    Describe("Fixed Point Maths", [this]()
    {
        Describe("Fixed Point Numbers", [this]()
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
        Describe("Fixed Point Math Functions", [this]()
        {
            It("Should ceil, floor and trunc negative 5 point 5 and 5 point 5 and get same result as FMath.", [this]()
            {
                const FFixed64 fixednegfivepointfive = -5.5;
                const FFixed64 fixedfivepointfive = 5.5;
                const double floatnegfivepointfive = -5.5;
                const double floatfivepointfive = 5.5;
                FFixed64 fixedceilnegresult = FFixedPointMath::CeilToFixed64(fixednegfivepointfive);
                FFixed64 fixedfloornegresult = FFixedPointMath::Floor(fixednegfivepointfive);
                FFixed64 fixedtruncnegresult = FFixedPointMath::TruncToFixed64(fixednegfivepointfive);
                double floatceilnegresult = FMath::CeilToDouble(floatnegfivepointfive);
                double floatfloornegresult = FMath::Floor(floatnegfivepointfive);
                double floattruncnegresult = FMath::TruncToDouble(floatnegfivepointfive);
                FFixed64 fixedceilresult = FFixedPointMath::CeilToFixed64(fixedfivepointfive);
                FFixed64 fixedfloorresult = FFixedPointMath::Floor(fixedfivepointfive);
                FFixed64 fixedtruncresult = FFixedPointMath::TruncToFixed64(fixedfivepointfive);
                double floatceilresult = FMath::CeilToDouble(floatfivepointfive);
                double floatfloorresult = FMath::Floor(floatfivepointfive);
                double floattruncresult = FMath::TruncToDouble(floatfivepointfive);
                bool result =
                    FFixedPointMath::IsEqual(fixedceilnegresult, floatceilnegresult) &&
                    FFixedPointMath::IsEqual(fixedceilresult, floatceilresult) &&
                    FFixedPointMath::IsEqual(fixedfloornegresult, floatfloornegresult) &&
                    FFixedPointMath::IsEqual(fixedfloorresult, floatfloorresult) &&
                    FFixedPointMath::IsEqual(fixedtruncnegresult, floattruncnegresult) &&
                    FFixedPointMath::IsEqual(fixedtruncresult, floattruncresult);
                TestTrue("All are within Kinda Small Number of their float equivalents", result);
            });
        });
        Describe("Fixed Point Vector 3D", [this]()
        {
            It("Should rotate a vector starting as forward unit vector 90 degrees and it should be equal to epics vector doing the same", [this]()
            {
                FFixedVector testvec = FFixedVector::ForwardVector;
                FFixedRotator testrot(FixedPoint::Constants::Fixed64::Zero, FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 90), FixedPoint::Constants::Fixed64::Zero);
                FFixedQuat testquat = testrot.Quaternion();
                testvec = testquat * testvec;
                FVector testepicvec = FVector::ForwardVector;
                FRotator testepicrot(0, 90, 0);
                FQuat testepicquat = testepicrot.Quaternion();
                testepicvec = testepicquat * testepicvec;
                
                TestTrue("Is Equal to epics vector", testvec.Equals(FFixedVector(testepicvec), FFixed64::MakeFromRawInt(256)));
            });
        });
    });
}
