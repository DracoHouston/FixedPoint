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
                    It("Should get a very similar result to FMath::Sin of negative pi", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::Pi;
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 7/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 7));
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 6/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 6));
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 5/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 5));
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 4/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 4));
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 3/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 3));
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 2/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 2));
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 1/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 1));
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 0", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Sin(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Sin((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 1/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 1);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 2/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 2);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 3/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 3);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 4/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 4);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 5/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 5);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 6/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 6);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 7/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 7);
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of pi", [this]()
                    {
                        const FFixed64 angle = FixedPoint::Constants::Fixed64::Pi;
                        FFixed64 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
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
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });                    
                });
                Describe("Tan", [this]()
                {
                    It("Should get a very similar result to FMath::Tan of negative pi", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::Pi;
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 7/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 7));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 6/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 6));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 5/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 5));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
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
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));                        
                    });
                    It("Should get a very similar result to FMath::Tan of negative 2/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 2));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 1/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 1));
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 0", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Tan(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Tan((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 1/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 1);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 2/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 2);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 3/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 3);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
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
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 7/8ths of pi", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt((FixedPoint::Constants::Fixed64::Pi.Value / 8) * 7);
                        FFixed64 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of pi", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Tan(FixedPoint::Constants::Fixed64::Pi);
                        double floatresult = FMath::Tan((double)FixedPoint::Constants::Fixed64::Pi);
                        TestTrue("Is within FFixed64::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(256)));
                    });                    
                });
                Describe("Asin", [this]()
                {
                    It("Should get a very similar result to FMath::Asin of negative one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 7));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
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
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
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
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 2));
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
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
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 1);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 2);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 3);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 4);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 5);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 6);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 7);
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                });
                Describe("Acos", [this]()
                {
                    It("Should get a very similar result to FMath::Acos of negative one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 7));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 6));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 5));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 4));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 3));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 2));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 1));
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of zero", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Acos(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Acos((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 1);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 2);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 3);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 4);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 5);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 6);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 7);
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                });
                Describe("Atan", [this]()
                {
                    It("Should get a very similar result to FMath::Atan of negative two", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value * 2);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 7)));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 6)));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 5)));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 4)));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 3)));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 2)));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 1)));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 7));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 6));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 5));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 4));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 3));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 2));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 1));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of zero", [this]()
                    {
                        FFixed64 fixedresult = FFixedPointMath::Atan(FixedPoint::Constants::Fixed64::Zero);
                        double floatresult = FMath::Atan((double)FixedPoint::Constants::Fixed64::Zero);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 1);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 2);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 3);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 4);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 5);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 6);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 7);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of one", [this]()
                    {
                        const FFixed64 angle = -FixedPoint::Constants::Fixed64::One;
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+1/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 1));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+2/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 2));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+3/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 3));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+4/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 4));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+5/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 5));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+6/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 6));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+7/8", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * 7));
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of two", [this]()
                    {
                        const FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::One.Value * 2);
                        FFixed64 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed64::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)));
                    });
                });
                Describe("Atan2", [this]()
                {
                    It("Should get a very similar result to FMath::Atan2 testing x = -1 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = -FixedPoint::Constants::Fixed64::One;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 7/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 7));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 6/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 6));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 5/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 5));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 4/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 4));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 3/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 3));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 2/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(-(FixedPoint::Constants::Fixed64::Eigth.Value * 2));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 1/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = -FixedPoint::Constants::Fixed64::Eigth;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 0 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FixedPoint::Constants::Fixed64::Zero;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 1/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FixedPoint::Constants::Fixed64::Eigth;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 2/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 2);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 3/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 3);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 4/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 4);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 5/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 5);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 6/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 6);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 7/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * 7);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 1 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed64 x = FixedPoint::Constants::Fixed64::One;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(-FixedPoint::Constants::Fixed64::One.Value + (FixedPoint::Constants::Fixed64::Eigth.Value * i));
                            FFixed64 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                });
                Describe("Sqrt", [this]()
                {
                    It("Should get a very similar result to FMath::Sqrt testing every value between 0 and 20 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        for (int64 i = 0; i < 161; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * i);
                            FFixed64 fixedresult = FFixedPointMath::Sqrt(angle);
                            double floatresult = FMath::Sqrt((double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1024)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1024) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::InvSqrt testing every value between 0 and 20 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        for (int64 i = 1; i < 161; i++)
                        {
                            FFixed64 angle = FFixed64::MakeFromRawInt(FixedPoint::Constants::Fixed64::Eigth.Value * i);
                            FFixed64 fixedresult = FFixedPointMath::InvSqrt(angle);
                            double floatresult = FMath::InvSqrt((double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed64)floatresult, FFixed64::MakeFromRawInt(1200)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed64::MakeFromRawInt(1024) of their float equivalents", result);
                    });
                });
            });
            Describe("Fixed 32", [this]()
            {
                It("Should ceil, floor and trunc negative 5 point 5 and 5 point 5 and get same result as FMath.", [this]()
                {
                    const FFixed32 fixednegfivepointfive = -5.5;
                    const FFixed32 fixedfivepointfive = 5.5;
                    const double floatnegfivepointfive = -5.5;
                    const double floatfivepointfive = 5.5;
                    FFixed32 fixedceilnegresult = FFixedPointMath::CeilToFixed32(fixednegfivepointfive);
                    FFixed32 fixedfloornegresult = FFixedPointMath::Floor(fixednegfivepointfive);
                    FFixed32 fixedtruncnegresult = FFixedPointMath::TruncToFixed32(fixednegfivepointfive);
                    double floatceilnegresult = FMath::CeilToDouble(floatnegfivepointfive);
                    double floatfloornegresult = FMath::Floor(floatnegfivepointfive);
                    double floattruncnegresult = FMath::TruncToDouble(floatnegfivepointfive);
                    FFixed32 fixedceilresult = FFixedPointMath::CeilToFixed32(fixedfivepointfive);
                    FFixed32 fixedfloorresult = FFixedPointMath::Floor(fixedfivepointfive);
                    FFixed32 fixedtruncresult = FFixedPointMath::TruncToFixed32(fixedfivepointfive);
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
                    It("Should get a very similar result to FMath::Sin of negative pi", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::Pi;
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 7/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 7));
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 6/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 6));
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 5/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 5));
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 4/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 4));
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 3/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 3));
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 2/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 2));
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 1/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 1));
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 0", [this]()
                    {
                        FFixed32 fixedresult = FFixedPointMath::Sin(FixedPoint::Constants::Fixed32::Zero);
                        double floatresult = FMath::Sin((double)FixedPoint::Constants::Fixed32::Zero);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 1/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 1);
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 2/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 2);
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 3/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 3);
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 4/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 4);
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 5/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 5);
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 6/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 6);
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 7/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 7);
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of pi", [this]()
                    {
                        const FFixed32 angle = FixedPoint::Constants::Fixed32::Pi;
                        FFixed32 fixedresult = FFixedPointMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    }); 
                });
                Describe("Cos", [this]()
                {
                    It("Should get a very similar result to FMath::Cos of negative pi", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::Pi;
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 7/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 7));
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 6/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 6));
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 5/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 5));
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 4/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 4));
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 3/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 3));
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 2/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 2));
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 1/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 1));
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 0", [this]()
                    {
                        FFixed32 fixedresult = FFixedPointMath::Cos(FixedPoint::Constants::Fixed32::Zero);
                        double floatresult = FMath::Cos((double)FixedPoint::Constants::Fixed32::Zero);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 1/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 1);
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 2/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 2);
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 3/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 3);
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 4/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 4);
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 5/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 5);
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 6/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 6);
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 7/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 7);
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of pi", [this]()
                    {
                        const FFixed32 angle = FixedPoint::Constants::Fixed32::Pi;
                        FFixed32 fixedresult = FFixedPointMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });                    
                });
                Describe("Tan", [this]()
                {
                    It("Should get a very similar result to FMath::Tan of negative pi", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::Pi;
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 7/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 7));
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 6/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 6));
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 5/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 5));
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 4/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 4));
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Both are below -1, indicating overflow", (fixedresult < -FixedPoint::Constants::Fixed32::One) && ((FFixed32)floatresult < -FixedPoint::Constants::Fixed32::One));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 3/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 3));
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));                        
                    });
                    It("Should get a very similar result to FMath::Tan of negative 2/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 2));
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 1/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 1));
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 0", [this]()
                    {
                        FFixed32 fixedresult = FFixedPointMath::Tan(FixedPoint::Constants::Fixed32::Zero);
                        double floatresult = FMath::Tan((double)FixedPoint::Constants::Fixed32::Zero);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 1/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 1);
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 2/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 2);
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 3/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 3);
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                     It("Should get a very similar result to FMath::Tan of 4/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 4);
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Both are above 1, indicating overflow", (fixedresult > FixedPoint::Constants::Fixed32::One) && ((FFixed32)floatresult > FixedPoint::Constants::Fixed32::One)); 
                    });
                    It("Should get a very similar result to FMath::Tan of 5/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 5);
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 6/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 6);
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 7/8ths of pi", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt((FixedPoint::Constants::Fixed32::Pi.Value / 8) * 7);
                        FFixed32 fixedresult = FFixedPointMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of pi", [this]()
                    {
                        FFixed32 fixedresult = FFixedPointMath::Tan(FixedPoint::Constants::Fixed32::Pi);
                        double floatresult = FMath::Tan((double)FixedPoint::Constants::Fixed32::Pi);
                        TestTrue("Is within FFixed32::MakeFromRawInt(256) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(256)));
                    });                    
                });
                Describe("Asin", [this]()
                {
                    It("Should get a very similar result to FMath::Asin of negative one", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::One;
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 7/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 7));
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 6/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 6));
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 5/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 5));
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 4/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 4));
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 3/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 3));
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 2/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 2));
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 1/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 1));
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of zero", [this]()
                    {
                        FFixed32 fixedresult = FFixedPointMath::Asin(FixedPoint::Constants::Fixed32::Zero);
                        double floatresult = FMath::Asin((double)FixedPoint::Constants::Fixed32::Zero);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 1/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 1);
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 2/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 2);
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 3/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 3);
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 4/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 4);
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 5/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 5);
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 6/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 6);
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 7/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 7);
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of one", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::One;
                        FFixed32 fixedresult = FFixedPointMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                });
                Describe("Acos", [this]()
                {
                    It("Should get a very similar result to FMath::Acos of negative one", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::One;
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 7/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 7));
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 6/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 6));
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 5/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 5));
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 4/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 4));
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 3/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 3));
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 2/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 2));
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 1/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 1));
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of zero", [this]()
                    {
                        FFixed32 fixedresult = FFixedPointMath::Acos(FixedPoint::Constants::Fixed32::Zero);
                        double floatresult = FMath::Acos((double)FixedPoint::Constants::Fixed32::Zero);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 1/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 1);
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 2/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 2);
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 3/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 3);
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 4/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 4);
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 5/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 5);
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 6/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 6);
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 7/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 7);
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of one", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::One;
                        FFixed32 fixedresult = FFixedPointMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                });
                Describe("Atan", [this]()
                {
                    It("Should get a very similar result to FMath::Atan of negative two", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value * 2);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+7/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 7)));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+6/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 6)));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+5/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 5)));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+4/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 4)));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+3/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 3)));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+2/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 2)));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+1/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 1)));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative one", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::One;
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 7/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 7));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 6/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 6));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 5/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 5));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 4/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 4));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 3/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 3));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 2/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 2));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 1));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of zero", [this]()
                    {
                        FFixed32 fixedresult = FFixedPointMath::Atan(FixedPoint::Constants::Fixed32::Zero);
                        double floatresult = FMath::Atan((double)FixedPoint::Constants::Fixed32::Zero);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 1);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 2/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 2);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 3/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 3);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 4/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 4);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 5/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 5);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 6/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 6);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 7/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 7);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of one", [this]()
                    {
                        const FFixed32 angle = -FixedPoint::Constants::Fixed32::One;
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+1/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 1));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+2/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 2));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+3/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 3));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+4/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 4));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+5/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 5));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+6/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 6));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+7/8", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * 7));
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of two", [this]()
                    {
                        const FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::One.Value * 2);
                        FFixed32 fixedresult = FFixedPointMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FFixed32::MakeFromRawInt(1500) of their float equivalents", FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)));
                    });
                });
                Describe("Atan2", [this]()
                {
                    It("Should get a very similar result to FMath::Atan2 testing x = -1 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = -FixedPoint::Constants::Fixed32::One;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 7/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 7));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 6/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 6));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 5/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 5));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 4/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 4));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 3/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 3));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 2/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(-(FixedPoint::Constants::Fixed32::Eigth.Value * 2));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 1/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = -FixedPoint::Constants::Fixed32::Eigth;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 0 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FixedPoint::Constants::Fixed32::Zero;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 1/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FixedPoint::Constants::Fixed32::Eigth;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 2/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 2);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 3/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 3);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 4/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 4);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 5/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 5);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 6/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 6);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 7/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * 7);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 1 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FFixed32 x = FixedPoint::Constants::Fixed32::One;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(-FixedPoint::Constants::Fixed32::One.Value + (FixedPoint::Constants::Fixed32::Eigth.Value * i));
                            FFixed32 fixedresult = FFixedPointMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(1500) of their float equivalents", result);
                    });
                });
                Describe("Sqrt", [this]()
                {
                    It("Should get a very similar result to FMath::Sqrt testing every value between 0 and 20 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        for (int32 i = 0; i < 161; i++)
                        {
                            FFixed32 angle = FFixed32::MakeFromRawInt(FixedPoint::Constants::Fixed32::Eigth.Value * i);
                            FFixed32 fixedresult = FFixedPointMath::Sqrt(angle);
                            double floatresult = FMath::Sqrt((double)angle);
                            if (!FFixedPointMath::IsEqual(fixedresult, (FFixed32)floatresult, FFixed32::MakeFromRawInt(512)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FFixed32::MakeFromRawInt(512) of their float equivalents", result);
                    });
                });
            });
        });
        Describe("Fixed Point Vector 3D", [this]()
        {
            It("Should rotate a vector starting as forward unit vector 90 degrees and it should be equal to epics vector doing the same", [this]()
            {
                FFixedVector64 testvec = FFixedVector64::ForwardVector;
                FFixedRotator64 testrot(FixedPoint::Constants::Fixed64::Zero, FFixed64::MakeFromRawInt(FixedPoint::Constants::Raw64::One * 90), FixedPoint::Constants::Fixed64::Zero);
                FFixedQuat64 testquat = testrot.Quaternion();
                testvec = testquat * testvec;
                FVector testepicvec = FVector::ForwardVector;
                FRotator testepicrot(0, 90, 0);
                FQuat testepicquat = testepicrot.Quaternion();
                testepicvec = testepicquat * testepicvec;
                
                TestTrue("Is Equal to epics vector within FFixed64::MakeFromRawInt(256) tolerance", testvec.Equals(FFixedVector64(testepicvec), FFixed64::MakeFromRawInt(256)));
            });
        });
    });
}
