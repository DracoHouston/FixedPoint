// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DeterministicFloatMatrix64.h"


FORCEINLINE void FDeterministicMatrix64::DiagnosticCheckNaN() const 
{
}

FORCEINLINE FDeterministicMatrix64::FDeterministicMatrix64() 
{
}

FORCEINLINE FDeterministicMatrix64::FDeterministicMatrix64(EForceInit)
{
	FMemory::Memzero(this, sizeof(*this));
}

FORCEINLINE FDeterministicMatrix64::FDeterministicMatrix64(FMatrix inValue)
{
	M[0][0] = FDeterministicNumber64(inValue.M[0][0]); M[0][1] = FDeterministicNumber64(inValue.M[0][1]); M[0][2] = FDeterministicNumber64(inValue.M[0][2]); M[0][3] = FDeterministicNumber64(inValue.M[0][3]);
	M[1][0] = FDeterministicNumber64(inValue.M[1][0]); M[1][1] = FDeterministicNumber64(inValue.M[1][1]); M[1][2] = FDeterministicNumber64(inValue.M[1][2]); M[1][3] = FDeterministicNumber64(inValue.M[1][3]);
	M[2][0] = FDeterministicNumber64(inValue.M[2][0]); M[2][1] = FDeterministicNumber64(inValue.M[2][1]); M[2][2] = FDeterministicNumber64(inValue.M[2][2]); M[2][3] = FDeterministicNumber64(inValue.M[2][3]);
	M[3][0] = FDeterministicNumber64(inValue.M[3][0]); M[3][1] = FDeterministicNumber64(inValue.M[3][1]); M[3][2] = FDeterministicNumber64(inValue.M[3][2]); M[3][3] = FDeterministicNumber64(inValue.M[3][3]);
}

FORCEINLINE FDeterministicMatrix64::FDeterministicMatrix64(const FDeterministicPlane64& InX, const FDeterministicPlane64& InY, const FDeterministicPlane64& InZ, const FDeterministicPlane64& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = InW.W;
}

FORCEINLINE  FDeterministicMatrix64::FDeterministicMatrix64(const FDeterministicVector64& InX, const FDeterministicVector64& InY, const FDeterministicVector64& InZ, const FDeterministicVector64& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = DeterministicFloat::Constants::Number64::Zero;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = DeterministicFloat::Constants::Number64::Zero;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = DeterministicFloat::Constants::Number64::Zero;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = DeterministicFloat::Constants::Number64::One;
}


FORCEINLINE void FDeterministicMatrix64::Internal_MatrixInverse(FDeterministicMatrix64& DstMatrix, const FDeterministicMatrix64& SrcMatrix)
{
	FDeterministicNumber64 Det[4];
	FDeterministicMatrix64 Tmp;

	Tmp.M[0][0] = SrcMatrix.M[2][2] * SrcMatrix.M[3][3] - SrcMatrix.M[2][3] * SrcMatrix.M[3][2];
	Tmp.M[0][1] = SrcMatrix.M[1][2] * SrcMatrix.M[3][3] - SrcMatrix.M[1][3] * SrcMatrix.M[3][2];
	Tmp.M[0][2] = SrcMatrix.M[1][2] * SrcMatrix.M[2][3] - SrcMatrix.M[1][3] * SrcMatrix.M[2][2];

	Tmp.M[1][0] = SrcMatrix.M[2][2] * SrcMatrix.M[3][3] - SrcMatrix.M[2][3] * SrcMatrix.M[3][2];
	Tmp.M[1][1] = SrcMatrix.M[0][2] * SrcMatrix.M[3][3] - SrcMatrix.M[0][3] * SrcMatrix.M[3][2];
	Tmp.M[1][2] = SrcMatrix.M[0][2] * SrcMatrix.M[2][3] - SrcMatrix.M[0][3] * SrcMatrix.M[2][2];

	Tmp.M[2][0] = SrcMatrix.M[1][2] * SrcMatrix.M[3][3] - SrcMatrix.M[1][3] * SrcMatrix.M[3][2];
	Tmp.M[2][1] = SrcMatrix.M[0][2] * SrcMatrix.M[3][3] - SrcMatrix.M[0][3] * SrcMatrix.M[3][2];
	Tmp.M[2][2] = SrcMatrix.M[0][2] * SrcMatrix.M[1][3] - SrcMatrix.M[0][3] * SrcMatrix.M[1][2];

	Tmp.M[3][0] = SrcMatrix.M[1][2] * SrcMatrix.M[2][3] - SrcMatrix.M[1][3] * SrcMatrix.M[2][2];
	Tmp.M[3][1] = SrcMatrix.M[0][2] * SrcMatrix.M[2][3] - SrcMatrix.M[0][3] * SrcMatrix.M[2][2];
	Tmp.M[3][2] = SrcMatrix.M[0][2] * SrcMatrix.M[1][3] - SrcMatrix.M[0][3] * SrcMatrix.M[1][2];

	Det[0] = SrcMatrix.M[1][1] * Tmp.M[0][0] - SrcMatrix.M[2][1] * Tmp.M[0][1] + SrcMatrix.M[3][1] * Tmp.M[0][2];
	Det[1] = SrcMatrix.M[0][1] * Tmp.M[1][0] - SrcMatrix.M[2][1] * Tmp.M[1][1] + SrcMatrix.M[3][1] * Tmp.M[1][2];
	Det[2] = SrcMatrix.M[0][1] * Tmp.M[2][0] - SrcMatrix.M[1][1] * Tmp.M[2][1] + SrcMatrix.M[3][1] * Tmp.M[2][2];
	Det[3] = SrcMatrix.M[0][1] * Tmp.M[3][0] - SrcMatrix.M[1][1] * Tmp.M[3][1] + SrcMatrix.M[2][1] * Tmp.M[3][2];

	const FDeterministicNumber64 Determinant = SrcMatrix.M[0][0] * Det[0] - SrcMatrix.M[1][0] * Det[1] + SrcMatrix.M[2][0] * Det[2] - SrcMatrix.M[3][0] * Det[3];
	const FDeterministicNumber64	RDet = DeterministicFloat::Constants::Number64::One / Determinant;

	DstMatrix.M[0][0] = RDet * Det[0];
	DstMatrix.M[0][1] = -RDet * Det[1];
	DstMatrix.M[0][2] = RDet * Det[2];
	DstMatrix.M[0][3] = -RDet * Det[3];
	DstMatrix.M[1][0] = -RDet * (SrcMatrix.M[1][0] * Tmp.M[0][0] - SrcMatrix.M[2][0] * Tmp.M[0][1] + SrcMatrix.M[3][0] * Tmp.M[0][2]);
	DstMatrix.M[1][1] = RDet * (SrcMatrix.M[0][0] * Tmp.M[1][0] - SrcMatrix.M[2][0] * Tmp.M[1][1] + SrcMatrix.M[3][0] * Tmp.M[1][2]);
	DstMatrix.M[1][2] = -RDet * (SrcMatrix.M[0][0] * Tmp.M[2][0] - SrcMatrix.M[1][0] * Tmp.M[2][1] + SrcMatrix.M[3][0] * Tmp.M[2][2]);
	DstMatrix.M[1][3] = RDet * (SrcMatrix.M[0][0] * Tmp.M[3][0] - SrcMatrix.M[1][0] * Tmp.M[3][1] + SrcMatrix.M[2][0] * Tmp.M[3][2]);
	DstMatrix.M[2][0] = RDet * (
		SrcMatrix.M[1][0] * (SrcMatrix.M[2][1] * SrcMatrix.M[3][3] - SrcMatrix.M[2][3] * SrcMatrix.M[3][1]) -
		SrcMatrix.M[2][0] * (SrcMatrix.M[1][1] * SrcMatrix.M[3][3] - SrcMatrix.M[1][3] * SrcMatrix.M[3][1]) +
		SrcMatrix.M[3][0] * (SrcMatrix.M[1][1] * SrcMatrix.M[2][3] - SrcMatrix.M[1][3] * SrcMatrix.M[2][1])
		);
	DstMatrix.M[2][1] = -RDet * (
		SrcMatrix.M[0][0] * (SrcMatrix.M[2][1] * SrcMatrix.M[3][3] - SrcMatrix.M[2][3] * SrcMatrix.M[3][1]) -
		SrcMatrix.M[2][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[3][3] - SrcMatrix.M[0][3] * SrcMatrix.M[3][1]) +
		SrcMatrix.M[3][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[2][3] - SrcMatrix.M[0][3] * SrcMatrix.M[2][1])
		);
	DstMatrix.M[2][2] = RDet * (
		SrcMatrix.M[0][0] * (SrcMatrix.M[1][1] * SrcMatrix.M[3][3] - SrcMatrix.M[1][3] * SrcMatrix.M[3][1]) -
		SrcMatrix.M[1][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[3][3] - SrcMatrix.M[0][3] * SrcMatrix.M[3][1]) +
		SrcMatrix.M[3][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[1][3] - SrcMatrix.M[0][3] * SrcMatrix.M[1][1])
		);
	DstMatrix.M[2][3] = -RDet * (
		SrcMatrix.M[0][0] * (SrcMatrix.M[1][1] * SrcMatrix.M[2][3] - SrcMatrix.M[1][3] * SrcMatrix.M[2][1]) -
		SrcMatrix.M[1][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[2][3] - SrcMatrix.M[0][3] * SrcMatrix.M[2][1]) +
		SrcMatrix.M[2][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[1][3] - SrcMatrix.M[0][3] * SrcMatrix.M[1][1])
		);
	DstMatrix.M[3][0] = -RDet * (
		SrcMatrix.M[1][0] * (SrcMatrix.M[2][1] * SrcMatrix.M[3][2] - SrcMatrix.M[2][2] * SrcMatrix.M[3][1]) -
		SrcMatrix.M[2][0] * (SrcMatrix.M[1][1] * SrcMatrix.M[3][2] - SrcMatrix.M[1][2] * SrcMatrix.M[3][1]) +
		SrcMatrix.M[3][0] * (SrcMatrix.M[1][1] * SrcMatrix.M[2][2] - SrcMatrix.M[1][2] * SrcMatrix.M[2][1])
		);
	DstMatrix.M[3][1] = RDet * (
		SrcMatrix.M[0][0] * (SrcMatrix.M[2][1] * SrcMatrix.M[3][2] - SrcMatrix.M[2][2] * SrcMatrix.M[3][1]) -
		SrcMatrix.M[2][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[3][2] - SrcMatrix.M[0][2] * SrcMatrix.M[3][1]) +
		SrcMatrix.M[3][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[2][2] - SrcMatrix.M[0][2] * SrcMatrix.M[2][1])
		);
	DstMatrix.M[3][2] = -RDet * (
		SrcMatrix.M[0][0] * (SrcMatrix.M[1][1] * SrcMatrix.M[3][2] - SrcMatrix.M[1][2] * SrcMatrix.M[3][1]) -
		SrcMatrix.M[1][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[3][2] - SrcMatrix.M[0][2] * SrcMatrix.M[3][1]) +
		SrcMatrix.M[3][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[1][2] - SrcMatrix.M[0][2] * SrcMatrix.M[1][1])
		);
	DstMatrix.M[3][3] = RDet * (
		SrcMatrix.M[0][0] * (SrcMatrix.M[1][1] * SrcMatrix.M[2][2] - SrcMatrix.M[1][2] * SrcMatrix.M[2][1]) -
		SrcMatrix.M[1][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[2][2] - SrcMatrix.M[0][2] * SrcMatrix.M[2][1]) +
		SrcMatrix.M[2][0] * (SrcMatrix.M[0][1] * SrcMatrix.M[1][2] - SrcMatrix.M[0][2] * SrcMatrix.M[1][1])
		);
}

FORCEINLINE void FDeterministicMatrix64::SetIdentity()
{
	M[0][0] = DeterministicFloat::Constants::Number64::One;		M[0][1] = DeterministicFloat::Constants::Number64::Zero;	M[0][2] = DeterministicFloat::Constants::Number64::Zero;	M[0][3] = DeterministicFloat::Constants::Number64::Zero;
	M[1][0] = DeterministicFloat::Constants::Number64::Zero;	M[1][1] = DeterministicFloat::Constants::Number64::One;		M[1][2] = DeterministicFloat::Constants::Number64::Zero;	M[1][3] = DeterministicFloat::Constants::Number64::Zero;
	M[2][0] = DeterministicFloat::Constants::Number64::Zero;	M[2][1] = DeterministicFloat::Constants::Number64::Zero;	M[2][2] = DeterministicFloat::Constants::Number64::One;		M[2][3] = DeterministicFloat::Constants::Number64::Zero;
	M[3][0] = DeterministicFloat::Constants::Number64::Zero;	M[3][1] = DeterministicFloat::Constants::Number64::Zero;	M[3][2] = DeterministicFloat::Constants::Number64::Zero;	M[3][3] = DeterministicFloat::Constants::Number64::One;
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::operator* (const FDeterministicMatrix64& Other) const
{
	FDeterministicMatrix64 Result;
	Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
	Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
	Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
	Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];

	Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
	Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
	Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
	Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];

	Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
	Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
	Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
	Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];

	Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
	Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
	Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
	Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];
	return Result;
}

FORCEINLINE void FDeterministicMatrix64::operator*=(const FDeterministicMatrix64& Other)
{
	*this = *this * Other;
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::operator+ (const FDeterministicMatrix64& Other) const
{
	FDeterministicMatrix64 ResultMat;

	for (int32 X = 0; X < 4; X++)
	{
		ResultMat.M[X][0] = M[X][0] + Other.M[X][0];
		ResultMat.M[X][1] = M[X][1] + Other.M[X][1];
		ResultMat.M[X][2] = M[X][2] + Other.M[X][2];
		ResultMat.M[X][3] = M[X][3] + Other.M[X][3];
	}

	return ResultMat;
}

FORCEINLINE void FDeterministicMatrix64::operator+=(const FDeterministicMatrix64& Other)
{
	*this = *this + Other;
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::operator* (FDeterministicNumber64 Other) const
{
	FDeterministicMatrix64 ResultMat;

	for (int32 X = 0; X < 4; X++)
	{
		ResultMat.M[X][0] = M[X][0] * Other;
		ResultMat.M[X][1] = M[X][1] * Other;
		ResultMat.M[X][2] = M[X][2] * Other;
		ResultMat.M[X][3] = M[X][3] * Other;
	}

	return ResultMat;
}

FORCEINLINE void FDeterministicMatrix64::operator*=(FDeterministicNumber64 Other)
{
	*this = *this * Other;
}

FORCEINLINE bool FDeterministicMatrix64::operator==(const FDeterministicMatrix64& Other) const
{
	for (int32 X = 0; X < 4; X++)
	{
		for (int32 Y = 0; Y < 4; Y++)
		{
			if (M[X][Y] != Other.M[X][Y])
			{
				return false;
			}
		}
	}

	return true;
}

FORCEINLINE bool FDeterministicMatrix64::Equals(const FDeterministicMatrix64& Other, FDeterministicNumber64 Tolerance) const
{
	for (int32 X = 0; X < 4; X++)
	{
		for (int32 Y = 0; Y < 4; Y++)
		{
			if (FDeterministicFloatMath::Abs(M[X][Y] - Other.M[X][Y]) > Tolerance)
			{
				return false;
			}
		}
	}

	return true;
}


FORCEINLINE bool FDeterministicMatrix64::operator!=(const FDeterministicMatrix64& Other) const
{
	return !(*this == Other);
}

FORCEINLINE FDeterministicVector4D64 FDeterministicMatrix64::TransformFVector4(const FDeterministicVector4D64& P) const
{
	FDeterministicVector4D64 VOurX = FDeterministicVector4D64(M[0][0], M[0][1], M[0][2], M[0][3]);
	FDeterministicVector4D64 VOurY = FDeterministicVector4D64(M[1][0], M[1][1], M[1][2], M[1][3]);
	FDeterministicVector4D64 VOurZ = FDeterministicVector4D64(M[2][0], M[2][1], M[2][2], M[2][3]);
	FDeterministicVector4D64 VOurW = FDeterministicVector4D64(M[3][0], M[3][1], M[3][2], M[3][3]);

	FDeterministicVector4D64 VTempX = FDeterministicVector4D64(P.X);
	FDeterministicVector4D64 VTempY = FDeterministicVector4D64(P.Y);
	FDeterministicVector4D64 VTempZ = FDeterministicVector4D64(P.Z);
	FDeterministicVector4D64 VTempW = FDeterministicVector4D64(P.W);

	VTempX = VTempX * VOurX;
	VTempX = (VTempY * VOurY) + VTempX;
	VTempX = (VTempZ * VOurZ) + VTempX;
	VTempX = (VTempW * VOurW) + VTempX;

	return VTempX;
}

FORCEINLINE FDeterministicVector4D64 FDeterministicMatrix64::TransformPosition(const FDeterministicVector64& V) const
{
	return TransformFVector4(FDeterministicVector4D64(V.X, V.Y, V.Z, DeterministicFloat::Constants::Number64::One));
}

FORCEINLINE FDeterministicVector64 FDeterministicMatrix64::InverseTransformPosition(const FDeterministicVector64& V) const
{
	FDeterministicMatrix64 InvSelf = this->InverseFast();
	return InvSelf.TransformPosition(V);
	return FDeterministicVector64();
}

FORCEINLINE FDeterministicVector4D64 FDeterministicMatrix64::TransformVector(const FDeterministicVector64& V) const
{
	return TransformFVector4(FDeterministicVector4D64(V.X, V.Y, V.Z, FDeterministicNumber64()));
}

FORCEINLINE FDeterministicVector64 FDeterministicMatrix64::InverseTransformVector(const FDeterministicVector64& V) const
{
	FDeterministicMatrix64 InvSelf = this->InverseFast();
	return InvSelf.TransformVector(V);
	return FDeterministicVector64();
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::GetTransposed() const
{
	FDeterministicMatrix64 Result;

	Result.M[0][0] = M[0][0];
	Result.M[0][1] = M[1][0];
	Result.M[0][2] = M[2][0];
	Result.M[0][3] = M[3][0];

	Result.M[1][0] = M[0][1];
	Result.M[1][1] = M[1][1];
	Result.M[1][2] = M[2][1];
	Result.M[1][3] = M[3][1];

	Result.M[2][0] = M[0][2];
	Result.M[2][1] = M[1][2];
	Result.M[2][2] = M[2][2];
	Result.M[2][3] = M[3][2];

	Result.M[3][0] = M[0][3];
	Result.M[3][1] = M[1][3];
	Result.M[3][2] = M[2][3];
	Result.M[3][3] = M[3][3];

	return Result;
}

FORCEINLINE FDeterministicNumber64 FDeterministicMatrix64::Determinant() const
{
	return	M[0][0] * (
		M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
		M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
		M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
		) -
		M[1][0] * (
			M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
			M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
			M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
			) +
		M[2][0] * (
			M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
			M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
			M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
			) -
		M[3][0] * (
			M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
			M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
			M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
			);
}

FORCEINLINE FDeterministicNumber64 FDeterministicMatrix64::RotDeterminant() const
{
	return
		M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
		M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
		M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::InverseFast() const
{
	// If we're in non final release, then make sure we're not creating NaNs
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber))
	{
		ErrorEnsure(TEXT("FDeterministicMatrix64::InverseFast(), trying to invert a NIL matrix, garbage in, garbage out! Use Inverse() instead."));
	}
	else
	{
		const FDeterministicNumber64	Det = Determinant();

		if (Det == DeterministicFloat::Constants::Number64::Zero)
		{
			ErrorEnsure(TEXT("FDeterministicMatrix64::InverseFast(), trying to invert a non-invertible matrix, garbage in, garbage out! Use Inverse() instead."));
		}
	}
#endif
	FDeterministicMatrix64 Result;
	Internal_MatrixInverse(Result, *this);
	return Result;
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::Inverse() const
{
	FDeterministicMatrix64 Result;

	//Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(DeterministicFloat::Constants::Number64::SmallNumber))
	{
		// just set to zero - avoids unsafe inverse of zero and duplicates what QNANs were resulting in before (scaling away all children)
		Result = Identity;
	}
	else
	{
		const FDeterministicNumber64	Det = Determinant();

		if (Det == DeterministicFloat::Constants::Number64::Zero)
		{
			Result = Identity;
		}
		else
		{
			Internal_MatrixInverse(Result, *this);
		}
	}

	return Result;
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::TransposeAdjoint() const
{
	FDeterministicMatrix64 TA;

	TA.M[0][0] = this->M[1][1] * this->M[2][2] - this->M[1][2] * this->M[2][1];
	TA.M[0][1] = this->M[1][2] * this->M[2][0] - this->M[1][0] * this->M[2][2];
	TA.M[0][2] = this->M[1][0] * this->M[2][1] - this->M[1][1] * this->M[2][0];
	TA.M[0][3] = DeterministicFloat::Constants::Number64::Zero;

	TA.M[1][0] = this->M[2][1] * this->M[0][2] - this->M[2][2] * this->M[0][1];
	TA.M[1][1] = this->M[2][2] * this->M[0][0] - this->M[2][0] * this->M[0][2];
	TA.M[1][2] = this->M[2][0] * this->M[0][1] - this->M[2][1] * this->M[0][0];
	TA.M[1][3] = DeterministicFloat::Constants::Number64::Zero;

	TA.M[2][0] = this->M[0][1] * this->M[1][2] - this->M[0][2] * this->M[1][1];
	TA.M[2][1] = this->M[0][2] * this->M[1][0] - this->M[0][0] * this->M[1][2];
	TA.M[2][2] = this->M[0][0] * this->M[1][1] - this->M[0][1] * this->M[1][0];
	TA.M[2][3] = DeterministicFloat::Constants::Number64::Zero;

	TA.M[3][0] = DeterministicFloat::Constants::Number64::Zero;
	TA.M[3][1] = DeterministicFloat::Constants::Number64::Zero;
	TA.M[3][2] = DeterministicFloat::Constants::Number64::Zero;
	TA.M[3][3] = DeterministicFloat::Constants::Number64::One;

	return TA;
}

inline void FDeterministicMatrix64::RemoveScaling(FDeterministicNumber64 Tolerance)
{
	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	const FDeterministicNumber64 SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
	const FDeterministicNumber64 SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
	const FDeterministicNumber64 SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);
	const FDeterministicNumber64 Scale0 = FDeterministicFloatMath::FloatSelect(SquareSum0 - Tolerance, FDeterministicFloatMath::InvSqrt(SquareSum0), FDeterministicNumber64(1));
	const FDeterministicNumber64 Scale1 = FDeterministicFloatMath::FloatSelect(SquareSum1 - Tolerance, FDeterministicFloatMath::InvSqrt(SquareSum1), FDeterministicNumber64(1));
	const FDeterministicNumber64 Scale2 = FDeterministicFloatMath::FloatSelect(SquareSum2 - Tolerance, FDeterministicFloatMath::InvSqrt(SquareSum2), FDeterministicNumber64(1));
	M[0][0] *= Scale0;
	M[0][1] *= Scale0;
	M[0][2] *= Scale0;
	M[1][0] *= Scale1;
	M[1][1] *= Scale1;
	M[1][2] *= Scale1;
	M[2][0] *= Scale2;
	M[2][1] *= Scale2;
	M[2][2] *= Scale2;
}

inline FDeterministicMatrix64 FDeterministicMatrix64::GetMatrixWithoutScale(FDeterministicNumber64 Tolerance) const
{
	FDeterministicMatrix64 Result = *this;
	Result.RemoveScaling(Tolerance);
	return Result;
}

inline FDeterministicVector64 FDeterministicMatrix64::ExtractScaling(FDeterministicNumber64 Tolerance/*=UE_SMALL_NUMBER*/)
{
	FDeterministicVector64 Scale3D(0, 0, 0);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	const FDeterministicNumber64 SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
	const FDeterministicNumber64 SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
	const FDeterministicNumber64 SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);

	if (SquareSum0 > Tolerance)
	{
		FDeterministicNumber64 Scale0 = FDeterministicFloatMath::Sqrt(SquareSum0);
		Scale3D[0] = Scale0;
		FDeterministicNumber64 InvScale0 = DeterministicFloat::Constants::Number64::One / Scale0;
		M[0][0] *= InvScale0;
		M[0][1] *= InvScale0;
		M[0][2] *= InvScale0;
	}
	else
	{
		Scale3D[0] = DeterministicFloat::Constants::Number64::Zero;
	}

	if (SquareSum1 > Tolerance)
	{
		FDeterministicNumber64 Scale1 = FDeterministicFloatMath::Sqrt(SquareSum1);
		Scale3D[1] = Scale1;
		FDeterministicNumber64 InvScale1 = DeterministicFloat::Constants::Number64::One / Scale1;
		M[1][0] *= InvScale1;
		M[1][1] *= InvScale1;
		M[1][2] *= InvScale1;
	}
	else
	{
		Scale3D[1] = DeterministicFloat::Constants::Number64::Zero;
	}

	if (SquareSum2 > Tolerance)
	{
		FDeterministicNumber64 Scale2 = FDeterministicFloatMath::Sqrt(SquareSum2);
		Scale3D[2] = Scale2;
		FDeterministicNumber64 InvScale2 = DeterministicFloat::Constants::Number64::One / Scale2;
		M[2][0] *= InvScale2;
		M[2][1] *= InvScale2;
		M[2][2] *= InvScale2;
	}
	else
	{
		Scale3D[2] = DeterministicFloat::Constants::Number64::Zero;
	}

	return Scale3D;
}

inline FDeterministicVector64 FDeterministicMatrix64::GetScaleVector(FDeterministicNumber64 Tolerance) const
{
	FDeterministicVector64 Scale3D(DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::One, DeterministicFloat::Constants::Number64::One);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	for (int32 i = 0; i < 3; i++)
	{
		const FDeterministicNumber64 SquareSum = (M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]);
		if (SquareSum > Tolerance)
		{
			Scale3D[i] = FDeterministicFloatMath::Sqrt(SquareSum);
		}
		else
		{
			Scale3D[i] = DeterministicFloat::Constants::Number64::Zero;
		}
	}

	return Scale3D;
}

inline FDeterministicMatrix64 FDeterministicMatrix64::RemoveTranslation() const
{
	FDeterministicMatrix64 Result = *this;
	Result.M[3][0] = 0.0f;
	Result.M[3][1] = 0.0f;
	Result.M[3][2] = 0.0f;
	return Result;
}

FORCEINLINE FDeterministicMatrix64 FDeterministicMatrix64::ConcatTranslation(const FDeterministicVector64& Translation) const
{
	FDeterministicMatrix64 Result;

	FDeterministicNumber64* RESTRICT Dest = &Result.M[0][0];
	const FDeterministicNumber64* RESTRICT Src = &M[0][0];
	const FDeterministicNumber64* RESTRICT Trans = &Translation.X;

	Dest[0] = Src[0];
	Dest[1] = Src[1];
	Dest[2] = Src[2];
	Dest[3] = Src[3];
	Dest[4] = Src[4];
	Dest[5] = Src[5];
	Dest[6] = Src[6];
	Dest[7] = Src[7];
	Dest[8] = Src[8];
	Dest[9] = Src[9];
	Dest[10] = Src[10];
	Dest[11] = Src[11];
	Dest[12] = Src[12] + Trans[0];
	Dest[13] = Src[13] + Trans[1];
	Dest[14] = Src[14] + Trans[2];
	Dest[15] = Src[15];

	return Result;
}

inline bool FDeterministicMatrix64::ContainsNaN() const
{
	return false;
}

inline void FDeterministicMatrix64::ScaleTranslation(const FDeterministicVector64& InScale3D)
{
	M[3][0] *= InScale3D.X;
	M[3][1] *= InScale3D.Y;
	M[3][2] *= InScale3D.Z;
}

inline FDeterministicNumber64 FDeterministicMatrix64::GetMinimumAxisScale() const
{
	const FDeterministicNumber64 MaxRowScaleSquared = FDeterministicFloatMath::Min(
		GetScaledAxis(EAxis::X).SizeSquared(),
		FDeterministicFloatMath::Min(
			GetScaledAxis(EAxis::Y).SizeSquared(),
			GetScaledAxis(EAxis::Z).SizeSquared()
		)
	);
	return FDeterministicFloatMath::Sqrt(MaxRowScaleSquared);
}

inline FDeterministicNumber64 FDeterministicMatrix64::GetMaximumAxisScale() const
{
	const FDeterministicNumber64 MaxRowScaleSquared = FDeterministicFloatMath::Max(
		GetScaledAxis(EAxis::X).SizeSquared(),
		FDeterministicFloatMath::Max(
			GetScaledAxis(EAxis::Y).SizeSquared(),
			GetScaledAxis(EAxis::Z).SizeSquared()
		)
	);
	return FDeterministicFloatMath::Sqrt(MaxRowScaleSquared);
}

inline FDeterministicMatrix64 FDeterministicMatrix64::ApplyScale(FDeterministicNumber64 Scale) const
{
	FDeterministicMatrix64 ScaleMatrix(
		FDeterministicPlane64(Scale, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero),
		FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, Scale, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero),
		FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, Scale, DeterministicFloat::Constants::Number64::Zero),
		FDeterministicPlane64(DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::Zero, DeterministicFloat::Constants::Number64::One)
	);
	return ScaleMatrix * *this;
}

inline FDeterministicVector64 FDeterministicMatrix64::GetOrigin() const
{
	return FDeterministicVector64(M[3][0], M[3][1], M[3][2]);
}

inline FDeterministicVector64 FDeterministicMatrix64::GetScaledAxis(EAxis::Type InAxis) const
{
	switch (InAxis)
	{
	case EAxis::X:
		return FDeterministicVector64(M[0][0], M[0][1], M[0][2]);

	case EAxis::Y:
		return FDeterministicVector64(M[1][0], M[1][1], M[1][2]);

	case EAxis::Z:
		return FDeterministicVector64(M[2][0], M[2][1], M[2][2]);

	default:
		ensure(0);
		return FDeterministicVector64::ZeroVector;
	}
}

inline void FDeterministicMatrix64::GetScaledAxes(FDeterministicVector64& X, FDeterministicVector64& Y, FDeterministicVector64& Z) const
{
	X.X = M[0][0]; X.Y = M[0][1]; X.Z = M[0][2];
	Y.X = M[1][0]; Y.Y = M[1][1]; Y.Z = M[1][2];
	Z.X = M[2][0]; Z.Y = M[2][1]; Z.Z = M[2][2];
}

inline FDeterministicVector64 FDeterministicMatrix64::GetUnitAxis(EAxis::Type InAxis) const
{
	return GetScaledAxis(InAxis).GetSafeNormal();
}

inline void FDeterministicMatrix64::GetUnitAxes(FDeterministicVector64& X, FDeterministicVector64& Y, FDeterministicVector64& Z) const
{
	GetScaledAxes(X, Y, Z);
	X.Normalize();
	Y.Normalize();
	Z.Normalize();
}

inline void FDeterministicMatrix64::SetAxis(int32 i, const FDeterministicVector64& Axis)
{
	checkSlow(i >= 0 && i <= 2);
	M[i][0] = Axis.X;
	M[i][1] = Axis.Y;
	M[i][2] = Axis.Z;
}

inline void FDeterministicMatrix64::SetOrigin(const FDeterministicVector64& NewOrigin)
{
	M[3][0] = NewOrigin.X;
	M[3][1] = NewOrigin.Y;
	M[3][2] = NewOrigin.Z;
}

inline void FDeterministicMatrix64::SetAxes(const FDeterministicVector64* Axis0 /*= NULL*/, const FDeterministicVector64* Axis1 /*= NULL*/, const FDeterministicVector64* Axis2 /*= NULL*/, const FDeterministicVector64* Origin /*= NULL*/)
{
	if (Axis0 != NULL)
	{
		M[0][0] = Axis0->X;
		M[0][1] = Axis0->Y;
		M[0][2] = Axis0->Z;
	}
	if (Axis1 != NULL)
	{
		M[1][0] = Axis1->X;
		M[1][1] = Axis1->Y;
		M[1][2] = Axis1->Z;
	}
	if (Axis2 != NULL)
	{
		M[2][0] = Axis2->X;
		M[2][1] = Axis2->Y;
		M[2][2] = Axis2->Z;
	}
	if (Origin != NULL)
	{
		M[3][0] = Origin->X;
		M[3][1] = Origin->Y;
		M[3][2] = Origin->Z;
	}
}

inline FDeterministicVector64 FDeterministicMatrix64::GetColumn(int32 i) const
{
	checkSlow(i >= 0 && i <= 3);
	return FDeterministicVector64(M[0][i], M[1][i], M[2][i]);
}

inline void FDeterministicMatrix64::SetColumn(int32 i, FDeterministicVector64 Value)
{
	checkSlow(i >= 0 && i <= 3);
	M[0][i] = Value.X;
	M[1][i] = Value.Y;
	M[2][i] = Value.Z;
}

inline void FDeterministicMatrix64::Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis)
{
	if (MirrorAxis == EAxis::X)
	{
		M[0][0] *= -DeterministicFloat::Constants::Number64::One;
		M[1][0] *= -DeterministicFloat::Constants::Number64::One;
		M[2][0] *= -DeterministicFloat::Constants::Number64::One;

		M[3][0] *= -DeterministicFloat::Constants::Number64::One;
	}
	else if (MirrorAxis == EAxis::Y)
	{
		M[0][1] *= -DeterministicFloat::Constants::Number64::One;
		M[1][1] *= -DeterministicFloat::Constants::Number64::One;
		M[2][1] *= -DeterministicFloat::Constants::Number64::One;

		M[3][1] *= -DeterministicFloat::Constants::Number64::One;
	}
	else if (MirrorAxis == EAxis::Z)
	{
		M[0][2] *= -DeterministicFloat::Constants::Number64::One;
		M[1][2] *= -DeterministicFloat::Constants::Number64::One;
		M[2][2] *= -DeterministicFloat::Constants::Number64::One;

		M[3][2] *= -DeterministicFloat::Constants::Number64::One;
	}

	if (FlipAxis == EAxis::X)
	{
		M[0][0] *= -DeterministicFloat::Constants::Number64::One;
		M[0][1] *= -DeterministicFloat::Constants::Number64::One;
		M[0][2] *= -DeterministicFloat::Constants::Number64::One;
	}
	else if (FlipAxis == EAxis::Y)
	{
		M[1][0] *= -DeterministicFloat::Constants::Number64::One;
		M[1][1] *= -DeterministicFloat::Constants::Number64::One;
		M[1][2] *= -DeterministicFloat::Constants::Number64::One;
	}
	else if (FlipAxis == EAxis::Z)
	{
		M[2][0] *= -DeterministicFloat::Constants::Number64::One;
		M[2][1] *= -DeterministicFloat::Constants::Number64::One;
		M[2][2] *= -DeterministicFloat::Constants::Number64::One;
	}
}

FORCEINLINE void FDeterministicMatrix64::ErrorEnsure(const TCHAR* Message)
{
	UE_LOG(LogUnrealMath, Error, TEXT("%s"), Message);
	ensureMsgf(false, TEXT("%s"), Message);
}
