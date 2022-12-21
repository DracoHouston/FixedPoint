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
            It("Should not get zero for OneEighty divided by OneEighty", [this]()
            {
                const FFixed64 result = FixedPoint::Constants::Fixed64::OneEighty / FixedPoint::Constants::Fixed64::OneEighty;
                TestTrue("equal to one", result == FixedPoint::Constants::Fixed64::One);
            });
            It("Should not get zero for -OneEighty divided by OneEighty", [this]()
            {
                const FFixed64 result = -FixedPoint::Constants::Fixed64::OneEighty / FixedPoint::Constants::Fixed64::OneEighty;
                TestTrue("equal to negative one", result == -FixedPoint::Constants::Fixed64::One);
            });
            It("Should not get zero for OneEighty divided by -OneEighty", [this]()
            {
                const FFixed64 result = FixedPoint::Constants::Fixed64::OneEighty / -FixedPoint::Constants::Fixed64::OneEighty;
                TestTrue("equal to negative one", result == -FixedPoint::Constants::Fixed64::One);
            });
            It("Should not get zero for -OneEighty divided by -OneEighty", [this]()
            {
                const FFixed64 result = -FixedPoint::Constants::Fixed64::OneEighty / -FixedPoint::Constants::Fixed64::OneEighty;
                TestTrue("equal to one", result == FixedPoint::Constants::Fixed64::One);
            });
            //It("Should be equal to the constant One times 42", [this]()
            //{
            //    TestFixed64 = MakeShared<FFixed64>((double)42.0);
            //    TestTrue("Is Equal to One times 42", ((FixedPoint::Constants::Raw64::One * 42) == (TestFixed64->Value)));
            //});
            //It("Should calculate square root of 16", [this]()
            //{
            //    //TestFixed64 = MakeShared<FFixed64>(16);
            //    FFixed64 result = FFixedPointMath::Sqrt(FFixed64((int64)16));
            //    TestTrue("Is Equal to One times 4", ((FixedPoint::Constants::Raw64::One * 4) == (result.Value)));
            //});
        
        Describe("Fixed Point Math Functions", [this]()
        {
            Describe("Fixed 64", [this]()
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
                Describe("Sin", [this]()
                {
                    It("Should get a very similar result to FMath::Sin of 0", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Sin(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Sin((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 1/4th of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 4) * 1);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 2/4th of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 4) * 2);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 3/4th of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 4) * 3);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of pi", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Sin(FixedPoint::Constants::Fixed64::Pi);
                        double floatresult = FMath::Sin((double)FixedPoint::Constants::Fixed64::Pi);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 5/4th of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 4) * 5);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 6/4th of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 4) * 6);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 7/4th of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 4) * 7);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 2 pi", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Sin(FixedPoint::Constants::Fixed64::TwoPi);
                        double floatresult = FMath::Sin((double)FixedPoint::Constants::Fixed64::TwoPi);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                });
                Describe("Cos", [this]()
                {
                    It("Should get a very similar result to FMath::Cos of negative pi", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::Pi;
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 7/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 7));
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 6/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 6));
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 5/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 5));
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 4/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 4));
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 3/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 3));
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 2/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 2));
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 1/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 1));
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 0", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Cos(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Cos((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 1/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 1);
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 2/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 2);
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 3/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 3);
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 4/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 4);
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 5/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 5);
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 6/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 6);
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 7/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 7);
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of pi", [this]()
                    {
                        const FFixed64 angle = FixedPoint::Constants::Fixed64::Pi;
                        FFixed64 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });                    
                });
                Describe("Tan", [this]()
                {
                    It("Should get a very similar result to FMath::Tan of negative pi", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::Pi;
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 7/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 7));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 6/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 6));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 5/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 5));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 4/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 4));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Both are below -1, indicating overflow", (fixedresult < -FixedPoint::Constants::Fixed64::One) && ((FFixed64)floatresult < -FixedPoint::Constants::Fixed64::One));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 3/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 3));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));                        
                    });
                    It("Should get a very similar result to FMath::Tan of negative 2/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 2));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 1/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 1));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 0", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Tan(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Tan((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 1/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 1);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 2/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 2);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 3/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 3);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                     It("Should get a very similar result to FMath::Tan of 4/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 4);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Both are above 1, indicating overflow", (fixedresult > FixedPoint::Constants::Fixed64::One) && ((FFixed64)floatresult > FixedPoint::Constants::Fixed64::One)); 
                    });
                    It("Should get a very similar result to FMath::Tan of 5/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 5);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 6/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 6);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 7/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 7);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of pi", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Tan(FixedPoint::Constants::Fixed64::Pi);
                        double floatresult = FMath::Tan((double)FixedPoint::Constants::Fixed64::Pi);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });                    
                });
                Describe("Asin", [this]()
                {
                    It("Should get a very similar result to FMath::Asin of negative one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 7));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 6));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 5));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 4));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 3));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 2));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 1));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of zero", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Asin(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Asin((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 1);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 2);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 3);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 4);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 5);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 6);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 7);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                });
                Describe("Acos", [this]()
                {
                    It("Should get a very similar result to FMath::Acos of negative one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 7));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 6));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 5));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 4));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 3));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 2));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 1));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of zero", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Acos(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Acos((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 1);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 2);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 3);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 4);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 5);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 6);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 7);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                });
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
