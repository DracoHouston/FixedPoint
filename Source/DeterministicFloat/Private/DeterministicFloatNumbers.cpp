// Fill out your copyright notice in the Description page of Project Settings.

#include "DeterministicFloatNumbers.h"

FORCENOINLINE double FDeterministicNumber64::AddSlow(const FDeterministicNumber64& A, const FDeterministicNumber64& B)
{
	return A.Value + B.Value;
}

FORCENOINLINE double FDeterministicNumber64::SubtractSlow(const FDeterministicNumber64& A, const FDeterministicNumber64& B)
{
	return A.Value - B.Value;
}

FORCENOINLINE double FDeterministicNumber64::MultiplySlow(const FDeterministicNumber64& A, const FDeterministicNumber64& B)
{
	return A.Value * B.Value;
}

FORCENOINLINE double FDeterministicNumber64::DivideSlow(const FDeterministicNumber64& A, const FDeterministicNumber64& B)
{
	return A.Value / B.Value;
}

FORCENOINLINE float FDeterministicNumber32::AddSlow(const FDeterministicNumber32& A, const FDeterministicNumber32& B)
{
	return A.Value + B.Value;
}

FORCENOINLINE float FDeterministicNumber32::SubtractSlow(const FDeterministicNumber32& A, const FDeterministicNumber32& B)
{
	return A.Value - B.Value;
}

FORCENOINLINE float FDeterministicNumber32::MultiplySlow(const FDeterministicNumber32& A, const FDeterministicNumber32& B)
{
	return A.Value * B.Value;
}

FORCENOINLINE float FDeterministicNumber32::DivideSlow(const FDeterministicNumber32& A, const FDeterministicNumber32& B)
{
	return A.Value / B.Value;
}
