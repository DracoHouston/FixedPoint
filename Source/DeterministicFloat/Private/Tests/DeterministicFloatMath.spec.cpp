// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/AutomationTest.h"
#include "DeterministicFloatTypes.h"

DEFINE_SPEC(FDeterministicFloatSpec, "DeterministicFloat.DeterministicFloatSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

void FDeterministicFloatSpec::Define()
{
    Describe("Fixed Point Maths", [this]()
    {
        It("Should not get zero for OneEighty divided by OneEighty", [this]()
        {
            const FDeterministicNumber64 result = DeterministicFloat::Constants::Number64::OneEighty / DeterministicFloat::Constants::Number64::OneEighty;
            TestTrue("equal to one", result == DeterministicFloat::Constants::Number64::One);
        });
        It("Should not get zero for -OneEighty divided by OneEighty", [this]()
        {
            const FDeterministicNumber64 result = -DeterministicFloat::Constants::Number64::OneEighty / DeterministicFloat::Constants::Number64::OneEighty;
            TestTrue("equal to negative one", result == -DeterministicFloat::Constants::Number64::One);
        });
        It("Should not get zero for OneEighty divided by -OneEighty", [this]()
        {
            const FDeterministicNumber64 result = DeterministicFloat::Constants::Number64::OneEighty / -DeterministicFloat::Constants::Number64::OneEighty;
            TestTrue("equal to negative one", result == -DeterministicFloat::Constants::Number64::One);
        });
        It("Should not get zero for -OneEighty divided by -OneEighty", [this]()
        {
            const FDeterministicNumber64 result = -DeterministicFloat::Constants::Number64::OneEighty / -DeterministicFloat::Constants::Number64::OneEighty;
            TestTrue("equal to one", result == DeterministicFloat::Constants::Number64::One);
        });
            //It("Should be equal to the constant One times 42", [this]()
            //{
            //    TestFixed64 = MakeShared<FDeterministicNumber64>((double)42.0);
            //    TestTrue("Is Equal to One times 42", ((DeterministicFloat::Constants::Raw64::One * 42) == (TestFixed64->Value)));
            //});
            //It("Should calculate square root of 16", [this]()
            //{
            //    //TestFixed64 = MakeShared<FDeterministicNumber64>(16);
            //    FDeterministicNumber64 result = FDeterministicFloatMath::Sqrt(FDeterministicNumber64((int64)16));
            //    TestTrue("Is Equal to One times 4", ((DeterministicFloat::Constants::Raw64::One * 4) == (result.Value)));
            //});
        
        Describe("Fixed Point Math Functions", [this]()
        {
            Describe("Fixed 64", [this]()
            {
                It("Should ceil, floor and trunc negative 5 point 5 and 5 point 5 and get same result as FMath.", [this]()
                {
                    const FDeterministicNumber64 fixednegfivepointfive = -5.5;
                    const FDeterministicNumber64 fixedfivepointfive = 5.5;
                    const double floatnegfivepointfive = -5.5;
                    const double floatfivepointfive = 5.5;
                    FDeterministicNumber64 fixedceilnegresult = FDeterministicFloatMath::CeilToNumber64(fixednegfivepointfive);
                    FDeterministicNumber64 fixedfloornegresult = FDeterministicFloatMath::Floor(fixednegfivepointfive);
                    FDeterministicNumber64 fixedtruncnegresult = FDeterministicFloatMath::TruncToNumber64(fixednegfivepointfive);
                    double floatceilnegresult = FMath::CeilToDouble(floatnegfivepointfive);
                    double floatfloornegresult = FMath::Floor(floatnegfivepointfive);
                    double floattruncnegresult = FMath::TruncToDouble(floatnegfivepointfive);
                    FDeterministicNumber64 fixedceilresult = FDeterministicFloatMath::CeilToNumber64(fixedfivepointfive);
                    FDeterministicNumber64 fixedfloorresult = FDeterministicFloatMath::Floor(fixedfivepointfive);
                    FDeterministicNumber64 fixedtruncresult = FDeterministicFloatMath::TruncToNumber64(fixedfivepointfive);
                    double floatceilresult = FMath::CeilToDouble(floatfivepointfive);
                    double floatfloorresult = FMath::Floor(floatfivepointfive);
                    double floattruncresult = FMath::TruncToDouble(floatfivepointfive);
                    bool result =
                        FDeterministicFloatMath::IsEqual(fixedceilnegresult, floatceilnegresult) &&
                        FDeterministicFloatMath::IsEqual(fixedceilresult, floatceilresult) &&
                        FDeterministicFloatMath::IsEqual(fixedfloornegresult, floatfloornegresult) &&
                        FDeterministicFloatMath::IsEqual(fixedfloorresult, floatfloorresult) &&
                        FDeterministicFloatMath::IsEqual(fixedtruncnegresult, floattruncnegresult) &&
                        FDeterministicFloatMath::IsEqual(fixedtruncresult, floattruncresult);
                    TestTrue("All are within Kinda Small Number of their float equivalents", result);
                });
                Describe("Sin", [this]()
                {
                    It("Should get a very similar result to FMath::Sin of negative pi", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::Pi;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 7));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 6));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 5));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 4));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 3));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 2));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 1));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of 0", [this]()
                    {
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(DeterministicFloat::Constants::Number64::Zero);
                        double floatresult = FMath::Sin((double)DeterministicFloat::Constants::Number64::Zero);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 1);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 2);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 3);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 4);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 5);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 6);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 7);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Sin of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = DeterministicFloat::Constants::Number64::Pi;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    }); 
                });
                Describe("Cos", [this]()
                {
                    It("Should get a very similar result to FMath::Cos of negative pi", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::Pi;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 7));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 6));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 5));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 4));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 3));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 2));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 1));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of 0", [this]()
                    {
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(DeterministicFloat::Constants::Number64::Zero);
                        double floatresult = FMath::Cos((double)DeterministicFloat::Constants::Number64::Zero);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 1);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 2);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 3);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 4);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 5);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 6);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 7);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Cos of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = DeterministicFloat::Constants::Number64::Pi;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });                    
                });
                Describe("Tan", [this]()
                {
                    It("Should get a very similar result to FMath::Tan of negative pi", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::Pi;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 7));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 6));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 5));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 4));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Both are below -1, indicating overflow", (fixedresult < -DeterministicFloat::Constants::Number64::One) && ((FDeterministicNumber64)floatresult < -DeterministicFloat::Constants::Number64::One));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 3));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));                        
                    });
                    It("Should get a very similar result to FMath::Tan of negative 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 2));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 1));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of 0", [this]()
                    {
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(DeterministicFloat::Constants::Number64::Zero);
                        double floatresult = FMath::Tan((double)DeterministicFloat::Constants::Number64::Zero);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 1);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 2);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 3);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                     It("Should get a very similar result to FMath::Tan of 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 4);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Both are above 1, indicating overflow", (fixedresult > DeterministicFloat::Constants::Number64::One) && ((FDeterministicNumber64)floatresult > DeterministicFloat::Constants::Number64::One)); 
                    });
                    It("Should get a very similar result to FMath::Tan of 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 5);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 6);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make((DeterministicFloat::Constants::Number64::Pi.Value / 8) * 7);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });
                    It("Should get a very similar result to FMath::Tan of pi", [this]()
                    {
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Tan(DeterministicFloat::Constants::Number64::Pi);
                        double floatresult = FMath::Tan((double)DeterministicFloat::Constants::Number64::Pi);
                        TestTrue("Is within FDeterministicNumber64::Make(0.000244) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000244)));
                    });                    
                });
                Describe("Asin", [this]()
                {
                    It("Should get a very similar result to FMath::Asin of negative one", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::One;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 7/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 7));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 6/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 6));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 5/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 5));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 4/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 4));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 3/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 3));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 2/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 2));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 1/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 1));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of zero", [this]()
                    {
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(DeterministicFloat::Constants::Number64::Zero);
                        double floatresult = FMath::Asin((double)DeterministicFloat::Constants::Number64::Zero);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of 1/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 1);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of 2/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 2);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of 3/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 3);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of 4/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 4);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of 5/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 5);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of 6/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 6);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of 7/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 7);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Asin of one", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::One;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                });
                Describe("Acos", [this]()
                {
                    It("Should get a very similar result to FMath::Acos of negative one", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::One;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 7/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 7));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 6/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 6));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 5/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 5));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 4/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 4));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 3/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 3));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 2/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 2));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 1/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 1));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of zero", [this]()
                    {
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(DeterministicFloat::Constants::Number64::Zero);
                        double floatresult = FMath::Acos((double)DeterministicFloat::Constants::Number64::Zero);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of 1/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 1);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of 2/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 2);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of 3/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 3);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of 4/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 4);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of 5/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 5);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of 6/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 6);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of 7/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 7);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Acos of one", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::One;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                });
                Describe("Atan", [this]()
                {
                    It("Should get a very similar result to FMath::Atan of negative two", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value * 2);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+7/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 7)));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+6/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 6)));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+5/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 5)));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+4/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 4)));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+3/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 3)));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+2/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 2)));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+1/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 1)));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative one", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::One;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 7/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 7));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 6/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 6));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 5/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 5));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 4/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 4));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 3/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 3));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 2/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 2));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 1));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of zero", [this]()
                    {
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(DeterministicFloat::Constants::Number64::Zero);
                        double floatresult = FMath::Atan((double)DeterministicFloat::Constants::Number64::Zero);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 1);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 2/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 2);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 3/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 3);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 4/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 4);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 5/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 5);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 6/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 6);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 7/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 7);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of one", [this]()
                    {
                        const FDeterministicNumber64 angle = -DeterministicFloat::Constants::Number64::One;
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+1/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 1));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+2/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 2));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+3/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 3));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+4/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 4));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+5/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 5));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+6/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 6));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+7/8", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * 7));
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                    It("Should get a very similar result to FMath::Atan of two", [this]()
                    {
                        const FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::One.Value * 2);
                        FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber64::Make(0.001430) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)));
                    });
                });
                Describe("Atan2", [this]()
                {
                    It("Should get a very similar result to FMath::Atan2 testing x = -1 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = -DeterministicFloat::Constants::Number64::One;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 7/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 7));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 6/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 6));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 5/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 5));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 4/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 4));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 3/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 3));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 2/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(-(DeterministicFloat::Constants::Number64::Eigth.Value * 2));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 1/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = -DeterministicFloat::Constants::Number64::Eigth;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 0 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = DeterministicFloat::Constants::Number64::Zero;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 1/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = DeterministicFloat::Constants::Number64::Eigth;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 2/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 2);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 3/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 3);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 4/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 4);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 5/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 5);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 6/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 6);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 7/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * 7);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 1 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber64 x = DeterministicFloat::Constants::Number64::One;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(-DeterministicFloat::Constants::Number64::One.Value + (DeterministicFloat::Constants::Number64::Eigth.Value * i));
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001430)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001430) of their float equivalents", result);
                    });
                });
                Describe("Sqrt", [this]()
                {
                    It("Should get a very similar result to FMath::Sqrt testing every value between 0 and 20 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        for (int64 i = 0; i < 161; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * i);
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::Sqrt(angle);
                            double floatresult = FMath::Sqrt((double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.000976)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.000976) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::InvSqrt testing every value between 0 and 20 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        for (int64 i = 1; i < 161; i++)
                        {
                            FDeterministicNumber64 angle = FDeterministicNumber64::Make(DeterministicFloat::Constants::Number64::Eigth.Value * i);
                            FDeterministicNumber64 fixedresult = FDeterministicFloatMath::InvSqrt(angle);
                            double floatresult = FMath::InvSqrt((double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber64)floatresult, FDeterministicNumber64::Make(0.001144)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber64::Make(0.001144) of their float equivalents", result);
                    });
                });
            });
            Describe("Fixed 32", [this]()
            {
                It("Should ceil, floor and trunc negative 5 point 5 and 5 point 5 and get same result as FMath.", [this]()
                {
                    const FDeterministicNumber32 fixednegfivepointfive = -5.5;
                    const FDeterministicNumber32 fixedfivepointfive = 5.5;
                    const double floatnegfivepointfive = -5.5;
                    const double floatfivepointfive = 5.5;
                    FDeterministicNumber32 fixedceilnegresult = FDeterministicFloatMath::CeilToNumber32(fixednegfivepointfive);
                    FDeterministicNumber32 fixedfloornegresult = FDeterministicFloatMath::Floor(fixednegfivepointfive);
                    FDeterministicNumber32 fixedtruncnegresult = FDeterministicFloatMath::TruncToNumber32(fixednegfivepointfive);
                    double floatceilnegresult = FMath::CeilToDouble(floatnegfivepointfive);
                    double floatfloornegresult = FMath::Floor(floatnegfivepointfive);
                    double floattruncnegresult = FMath::TruncToDouble(floatnegfivepointfive);
                    FDeterministicNumber32 fixedceilresult = FDeterministicFloatMath::CeilToNumber32(fixedfivepointfive);
                    FDeterministicNumber32 fixedfloorresult = FDeterministicFloatMath::Floor(fixedfivepointfive);
                    FDeterministicNumber32 fixedtruncresult = FDeterministicFloatMath::TruncToNumber32(fixedfivepointfive);
                    double floatceilresult = FMath::CeilToDouble(floatfivepointfive);
                    double floatfloorresult = FMath::Floor(floatfivepointfive);
                    double floattruncresult = FMath::TruncToDouble(floatfivepointfive);
                    bool result =
                        FDeterministicFloatMath::IsEqual(fixedceilnegresult, floatceilnegresult) &&
                        FDeterministicFloatMath::IsEqual(fixedceilresult, floatceilresult) &&
                        FDeterministicFloatMath::IsEqual(fixedfloornegresult, floatfloornegresult) &&
                        FDeterministicFloatMath::IsEqual(fixedfloorresult, floatfloorresult) &&
                        FDeterministicFloatMath::IsEqual(fixedtruncnegresult, floattruncnegresult) &&
                        FDeterministicFloatMath::IsEqual(fixedtruncresult, floattruncresult);
                    TestTrue("All are within Kinda Small Number of their float equivalents", result);
                });
                Describe("Sin", [this]()
                {
                    It("Should get a very similar result to FMath::Sin of negative pi", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::Pi;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 7));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 6));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 5));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 4));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 3));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 2));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of negative 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 1));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 0", [this]()
                    {
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(DeterministicFloat::Constants::Number32::Zero);
                        double floatresult = FMath::Sin((double)DeterministicFloat::Constants::Number32::Zero);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 1);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 2);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 3);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 4);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 5);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 6);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 7);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Sin of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = DeterministicFloat::Constants::Number32::Pi;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sin(angle);
                        double floatresult = FMath::Sin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    }); 
                });
                Describe("Cos", [this]()
                {
                    It("Should get a very similar result to FMath::Cos of negative pi", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::Pi;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 7));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 6));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 5));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 4));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 3));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 2));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of negative 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 1));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 0", [this]()
                    {
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(DeterministicFloat::Constants::Number32::Zero);
                        double floatresult = FMath::Cos((double)DeterministicFloat::Constants::Number32::Zero);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 1);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 2);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 3);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 4);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 5);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 6);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 7);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Cos of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = DeterministicFloat::Constants::Number32::Pi;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Cos(angle);
                        double floatresult = FMath::Cos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });                    
                });
                Describe("Tan", [this]()
                {
                    It("Should get a very similar result to FMath::Tan of negative pi", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::Pi;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 7));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 6));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 5));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 4));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        //TestTrue("Both are below -1, or above 1, indicating overflow", (fixedresult < -DeterministicFloat::Constants::Number32::One) && ((FDeterministicNumber32)floatresult < -DeterministicFloat::Constants::Number32::One));
                        TestTrue
                        (
                            "Both are above 1, or below -1, indicating overflow", 
                            (
                                (
                                    (fixedresult > DeterministicFloat::Constants::Number32::One) || 
                                    (fixedresult < -DeterministicFloat::Constants::Number32::One)
                                ) && 
                                (
                                    ((FDeterministicNumber32)floatresult > DeterministicFloat::Constants::Number32::One) || 
                                    ((FDeterministicNumber32)floatresult < -DeterministicFloat::Constants::Number32::One)
                                )
                            )
                        );
                    });
                    It("Should get a very similar result to FMath::Tan of negative 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 3));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));                        
                    });
                    It("Should get a very similar result to FMath::Tan of negative 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 2));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of negative 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 1));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 0", [this]()
                    {
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(DeterministicFloat::Constants::Number32::Zero);
                        double floatresult = FMath::Tan((double)DeterministicFloat::Constants::Number32::Zero);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 1/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 1);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 2/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 2);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 3/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 3);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                     It("Should get a very similar result to FMath::Tan of 4/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 4);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue
                        (
                            "Both are above 1, or below -1, indicating overflow", 
                            (
                                (
                                    (fixedresult > DeterministicFloat::Constants::Number32::One) || 
                                    (fixedresult < -DeterministicFloat::Constants::Number32::One)
                                ) && 
                                (
                                    ((FDeterministicNumber32)floatresult > DeterministicFloat::Constants::Number32::One) || 
                                    ((FDeterministicNumber32)floatresult < -DeterministicFloat::Constants::Number32::One)
                                )
                            )
                        );
                    });
                    It("Should get a very similar result to FMath::Tan of 5/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 5);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 6/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 6);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of 7/8ths of pi", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make((DeterministicFloat::Constants::Number32::Pi.Value / 8) * 7);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(angle);
                        double floatresult = FMath::Tan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });
                    It("Should get a very similar result to FMath::Tan of pi", [this]()
                    {
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Tan(DeterministicFloat::Constants::Number32::Pi);
                        double floatresult = FMath::Tan((double)DeterministicFloat::Constants::Number32::Pi);
                        TestTrue("Is within FDeterministicNumber32::Make(256) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(256)));
                    });                    
                });
                Describe("Asin", [this]()
                {
                    It("Should get a very similar result to FMath::Asin of negative one", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::One;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 7/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 7));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 6/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 6));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 5/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 5));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 4/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 4));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 3/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 3));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 2/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 2));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of negative 1/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 1));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within Kinda Small Number of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of zero", [this]()
                    {
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(DeterministicFloat::Constants::Number32::Zero);
                        double floatresult = FMath::Asin((double)DeterministicFloat::Constants::Number32::Zero);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 1/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 1);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 2/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 2);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 3/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 3);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 4/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 4);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 5/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 5);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 6/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 6);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of 7/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 7);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Asin of one", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::One;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Asin(angle);
                        double floatresult = FMath::Asin((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                });
                Describe("Acos", [this]()
                {
                    It("Should get a very similar result to FMath::Acos of negative one", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::One;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 7/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 7));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 6/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 6));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 5/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 5));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 4/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 4));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 3/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 3));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 2/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 2));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of negative 1/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 1));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of zero", [this]()
                    {
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(DeterministicFloat::Constants::Number32::Zero);
                        double floatresult = FMath::Acos((double)DeterministicFloat::Constants::Number32::Zero);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 1/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 1);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 2/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 2);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 3/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 3);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 4/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 4);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 5/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 5);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 6/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 6);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of 7/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 7);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Acos of one", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::One;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Acos(angle);
                        double floatresult = FMath::Acos((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                });
                Describe("Atan", [this]()
                {
                    It("Should get a very similar result to FMath::Atan of negative two", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value * 2);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+7/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 7)));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+6/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 6)));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+5/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 5)));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+4/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 4)));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+3/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 3)));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+2/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 2)));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1+1/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 1)));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative one", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::One;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 7/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 7));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 6/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 6));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 5/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 5));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 4/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 4));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 3/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 3));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 2/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 2));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of negative 1/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 1));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of zero", [this]()
                    {
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(DeterministicFloat::Constants::Number32::Zero);
                        double floatresult = FMath::Atan((double)DeterministicFloat::Constants::Number32::Zero);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 1);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 2/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 2);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 3/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 3);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 4/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 4);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 5/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 5);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 6/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 6);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 7/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 7);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of one", [this]()
                    {
                        const FDeterministicNumber32 angle = -DeterministicFloat::Constants::Number32::One;
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+1/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 1));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+2/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 2));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+3/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 3));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+4/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 4));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+5/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 5));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+6/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 6));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of 1+7/8", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * 7));
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                    It("Should get a very similar result to FMath::Atan of two", [this]()
                    {
                        const FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::One.Value * 2);
                        FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan(angle);
                        double floatresult = FMath::Atan((double)angle);
                        TestTrue("Is within FDeterministicNumber32::Make(1500) of their float equivalents", FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)));
                    });
                });
                Describe("Atan2", [this]()
                {
                    It("Should get a very similar result to FMath::Atan2 testing x = -1 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = -DeterministicFloat::Constants::Number32::One;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 7/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 7));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 6/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 6));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 5/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 5));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 4/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 4));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 3/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 3));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 2/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(-(DeterministicFloat::Constants::Number32::Eigth.Value * 2));
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = negative 1/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = -DeterministicFloat::Constants::Number32::Eigth;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 0 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = DeterministicFloat::Constants::Number32::Zero;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 1/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = DeterministicFloat::Constants::Number32::Eigth;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 2/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 2);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 3/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 3);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 4/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 4);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 5/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 5);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 6/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 6);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 7/8ths for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * 7);
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                    It("Should get a very similar result to FMath::Atan2 testing x = 1 for every value of y between -1 and 1 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        const FDeterministicNumber32 x = DeterministicFloat::Constants::Number32::One;
                        for (int64 i = 0; i < 17; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(-DeterministicFloat::Constants::Number32::One.Value + (DeterministicFloat::Constants::Number32::Eigth.Value * i));
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Atan2(x, angle);
                            double floatresult = FMath::Atan2((double)x, (double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(1500)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(1500) of their float equivalents", result);
                    });
                });
                Describe("Sqrt", [this]()
                {
                    It("Should get a very similar result to FMath::Sqrt testing every value between 0 and 20 in increments of 1/8th", [this]()
                    {
                        bool result = true;
                        for (int32 i = 0; i < 161; i++)
                        {
                            FDeterministicNumber32 angle = FDeterministicNumber32::Make(DeterministicFloat::Constants::Number32::Eigth.Value * i);
                            FDeterministicNumber32 fixedresult = FDeterministicFloatMath::Sqrt(angle);
                            double floatresult = FMath::Sqrt((double)angle);
                            if (!FDeterministicFloatMath::IsEqual(fixedresult, (FDeterministicNumber32)floatresult, FDeterministicNumber32::Make(512)))
                            {
                                result = false;
                                break;
                            }
                        }
                        TestTrue("All are within FDeterministicNumber32::Make(512) of their float equivalents", result);
                    });
                });
            });
        });
        Describe("Fixed Point Vector 3D", [this]()
        {
            It("Should rotate a vector starting as forward unit vector 90 degrees and it should be equal to epics vector doing the same", [this]()
            {
                FDeterministicVector64 testvec = FDeterministicVector64::ForwardVector;
                FDeterministicRotator64 testrot(DeterministicFloat::Constants::Number64::Zero, FDeterministicNumber64::Make(90.0), DeterministicFloat::Constants::Number64::Zero);
                FDeterministicQuat64 testquat = testrot.Quaternion();
                testvec = testquat * testvec;
                FVector testepicvec = FVector::ForwardVector;
                FRotator testepicrot(0, 90, 0);
                FQuat testepicquat = testepicrot.Quaternion();
                testepicvec = testepicquat * testepicvec;
                
                TestTrue("Is Equal to epics vector within FDeterministicNumber64::Make(0.000244) tolerance", testvec.Equals(FDeterministicVector64(testepicvec), FDeterministicNumber64::Make(0.000244)));
            });
        });
    });
}
