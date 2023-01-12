// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatMath.h"
#include "DeterministicFloatMatrix64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicMatrix64
{
public:
	GENERATED_BODY()

	FORCEINLINE void DiagnosticCheckNaN() const {}

	/**
	* Default constructor
	*/
	FORCEINLINE FDeterministicMatrix64() {}

	/**
	 * Constructor.
	 *
	 * @param EForceInit Force Init Enum.
	 */
	explicit FORCEINLINE FDeterministicMatrix64(EForceInit)
	{
		FMemory::Memzero(this, sizeof(*this));
	}

	/**
	* Constructor that casts FMatrix to FDeterministicMatrix64
	*/
	FORCEINLINE FDeterministicMatrix64(FMatrix inValue)
	{
		M[0][0] = FDeterministicNumber64(inValue.M[0][0]); M[0][1] = FDeterministicNumber64(inValue.M[0][1]); M[0][2] = FDeterministicNumber64(inValue.M[0][2]); M[0][3] = FDeterministicNumber64(inValue.M[0][3]);
		M[1][0] = FDeterministicNumber64(inValue.M[1][0]); M[1][1] = FDeterministicNumber64(inValue.M[1][1]); M[1][2] = FDeterministicNumber64(inValue.M[1][2]); M[1][3] = FDeterministicNumber64(inValue.M[1][3]);
		M[2][0] = FDeterministicNumber64(inValue.M[2][0]); M[2][1] = FDeterministicNumber64(inValue.M[2][1]); M[2][2] = FDeterministicNumber64(inValue.M[2][2]); M[2][3] = FDeterministicNumber64(inValue.M[2][3]);
		M[3][0] = FDeterministicNumber64(inValue.M[3][0]); M[3][1] = FDeterministicNumber64(inValue.M[3][1]); M[3][2] = FDeterministicNumber64(inValue.M[3][2]); M[3][3] = FDeterministicNumber64(inValue.M[3][3]);
	}

	/**
	 * Constructor.
	 *
	 * @param InX X plane
	 * @param InY Y plane
	 * @param InZ Z plane
	 * @param InW W plane
	 */
	FORCEINLINE FDeterministicMatrix64(const FDeterministicPlane64& InX, const FDeterministicPlane64& InY, const FDeterministicPlane64& InZ, const FDeterministicPlane64& InW);

	/**
	 * Constructor.
	 *
	 * @param InX X vector
	 * @param InY Y vector
	 * @param InZ Z vector
	 * @param InW W vector
	 */
	FORCEINLINE FDeterministicMatrix64(const FDeterministicVector64& InX, const FDeterministicVector64& InY, const FDeterministicVector64& InZ, const FDeterministicVector64& InW);

	FDeterministicNumber64 M[4][4];

	static const FDeterministicMatrix64 Identity;

	static void Internal_MatrixInverse(FDeterministicMatrix64& DstMatrix, const FDeterministicMatrix64& SrcMatrix)
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

	// Set this to the identity matrix
	FORCEINLINE void SetIdentity()
	{
		M[0][0] = DeterministicFloat::Constants::Number64::One;	M[0][1] = DeterministicFloat::Constants::Number64::Zero;	M[0][2] = DeterministicFloat::Constants::Number64::Zero;	M[0][3] = DeterministicFloat::Constants::Number64::Zero;
		M[1][0] = DeterministicFloat::Constants::Number64::Zero;	M[1][1] = DeterministicFloat::Constants::Number64::One;	M[1][2] = DeterministicFloat::Constants::Number64::Zero;	M[1][3] = DeterministicFloat::Constants::Number64::Zero;
		M[2][0] = DeterministicFloat::Constants::Number64::Zero;	M[2][1] = DeterministicFloat::Constants::Number64::Zero;	M[2][2] = DeterministicFloat::Constants::Number64::One;	M[2][3] = DeterministicFloat::Constants::Number64::Zero;
		M[3][0] = DeterministicFloat::Constants::Number64::Zero;	M[3][1] = DeterministicFloat::Constants::Number64::Zero;	M[3][2] = DeterministicFloat::Constants::Number64::Zero;	M[3][3] = DeterministicFloat::Constants::Number64::One;
	}

	/**
	 * Gets the result of multiplying a Matrix to this.
	 *
	 * @param Other The matrix to multiply this by.
	 * @return The result of multiplication.
	 */
	FORCEINLINE FDeterministicMatrix64 operator* (const FDeterministicMatrix64& Other) const
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

	/**
	 * Multiply this by a matrix.
	 *
	 * @param Other the matrix to multiply by this.
	 * @return reference to this after multiply.
	 */
	FORCEINLINE void operator*=(const FDeterministicMatrix64& Other)
	{
		*this = *this * Other;
	}

	/**
	 * Gets the result of adding a matrix to this.
	 *
	 * @param Other The Matrix to add.
	 * @return The result of addition.
	 */
	FORCEINLINE FDeterministicMatrix64 operator+ (const FDeterministicMatrix64& Other) const
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

	/**
	 * Adds to this matrix.
	 *
	 * @param Other The matrix to add to this.
	 * @return Reference to this after addition.
	 */
	FORCEINLINE void operator+=(const FDeterministicMatrix64& Other)
	{
		*this = *this + Other;
	}

	/**
	  * This isn't applying SCALE, just multiplying the value to all members - i.e. weighting
	  */
	FORCEINLINE FDeterministicMatrix64 operator* (FDeterministicNumber64 Other) const
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

	/**
	 * Multiply this matrix by a weighting factor.
	 *
	 * @param other The weight.
	 * @return a reference to this after weighting.
	 */
	FORCEINLINE void operator*=(FDeterministicNumber64 Other)
	{
		*this = *this * Other;
	}

	/**
	 * Checks whether two matrix are identical.
	 *
	 * @param Other The other matrix.
	 * @return true if two matrix are identical, otherwise false.
	 */
	FORCEINLINE bool operator==(const FDeterministicMatrix64& Other) const
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

	/**
	 * Checks whether another Matrix is equal to this, within specified tolerance.
	 *
	 * @param Other The other Matrix.
	 * @param Tolerance Error Tolerance.
	 * @return true if two Matrix are equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FDeterministicMatrix64& Other, FDeterministicNumber64 Tolerance) const
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

	/**
	 * Checks whether another Matrix is not equal to this, within specified tolerance.
	 *
	 * @param Other The other Matrix.
	 * @return true if two Matrix are not equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool operator!=(const FDeterministicMatrix64& Other) const
	{
		return !(*this == Other);
	}

	// Homogeneous transform.
	FORCEINLINE FDeterministicVector4D64 TransformFVector4(const FDeterministicVector4D64& V) const;

	/** Transform a location - will take into account translation part of the FDeterministicMatrix64. */
	FORCEINLINE FDeterministicVector4D64 TransformPosition(const FDeterministicVector64& V) const;

	/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
	FORCEINLINE FDeterministicVector64 InverseTransformPosition(const FDeterministicVector64& V) const;

	/**
	 *	Transform a direction vector - will not take into account translation part of the FDeterministicMatrix64.
	 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
	 */
	FORCEINLINE FDeterministicVector4D64 TransformVector(const FDeterministicVector64& V) const;

	/**
	 *	Transform a direction vector by the inverse of this matrix - will not take into account translation part.
	 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
	 */
	FORCEINLINE FDeterministicVector64 InverseTransformVector(const FDeterministicVector64& V) const;

	// Transpose.

	FORCEINLINE FDeterministicMatrix64 GetTransposed() const
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

	// @return determinant of this matrix.

	FORCEINLINE FDeterministicNumber64 Determinant() const
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

	/** @return the determinant of rotation 3x3 matrix */
	FORCEINLINE FDeterministicNumber64 RotDeterminant() const
	{
		return
			M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
			M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
			M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
	}

	/** Fast path, doesn't check for nil matrices in final release builds */
	FORCEINLINE FDeterministicMatrix64 InverseFast() const;

	/** Fast path, and handles nil matrices. */
	FORCEINLINE FDeterministicMatrix64 Inverse() const;

	FORCEINLINE FDeterministicMatrix64 TransposeAdjoint() const
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

	// NOTE: There is some compiler optimization issues with WIN64 that cause FORCEINLINE to cause a crash
	// Remove any scaling from this matrix (ie magnitude of each row is 1) with error Tolerance
	inline void RemoveScaling(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber)
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

	// Returns matrix after RemoveScaling with error Tolerance
	inline FDeterministicMatrix64 GetMatrixWithoutScale(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber) const
	{
		FDeterministicMatrix64 Result = *this;
		Result.RemoveScaling(Tolerance);
		return Result;
	}

	/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present with error Tolerance */
	inline FDeterministicVector64 ExtractScaling(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber);

	/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector) with error Tolerance. */
	inline FDeterministicVector64 GetScaleVector(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber) const;

	// Remove any translation from this matrix
	inline FDeterministicMatrix64 RemoveTranslation() const
	{
		FDeterministicMatrix64 Result = *this;
		Result.M[3][0] = 0.0f;
		Result.M[3][1] = 0.0f;
		Result.M[3][2] = 0.0f;
		return Result;
	}

	/** Returns a matrix with an additional translation concatenated. */
	inline FDeterministicMatrix64 ConcatTranslation(const FDeterministicVector64& Translation) const;

	/** Returns true if any element of this matrix is NaN */
	inline bool ContainsNaN() const
	{
		return false;
	}

	/** Scale the translation part of the matrix by the supplied vector. */
	inline void ScaleTranslation(const FDeterministicVector64& Scale3D);

	/** @return the minimum magnitude of any row of the matrix. */
	inline FDeterministicNumber64 GetMinimumAxisScale() const;

	/** @return the maximum magnitude of any row of the matrix. */
	inline FDeterministicNumber64 GetMaximumAxisScale() const;

	/** Apply Scale to this matrix **/
	inline FDeterministicMatrix64 ApplyScale(FDeterministicNumber64 Scale) const;

	// @return the origin of the co-ordinate system
	inline FDeterministicVector64 GetOrigin() const;

	/**
	 * get axis of this matrix scaled by the scale of the matrix
	 *
	 * @param i index into the axis of the matrix
	 * @ return vector of the axis
	 */
	FORCEINLINE FDeterministicVector64 GetScaledAxis(EAxis::Type Axis) const;

	/**
	 * get axes of this matrix scaled by the scale of the matrix
	 *
	 * @param X axes returned to this param
	 * @param Y axes returned to this param
	 * @param Z axes returned to this param
	 */
	inline void GetScaledAxes(FDeterministicVector64& X, FDeterministicVector64& Y, FDeterministicVector64& Z) const;

	/**
	 * get unit length axis of this matrix
	 *
	 * @param i index into the axis of the matrix
	 * @return vector of the axis
	 */
	inline FDeterministicVector64 GetUnitAxis(EAxis::Type Axis) const;

	/**
	 * get unit length axes of this matrix
	 *
	 * @param X axes returned to this param
	 * @param Y axes returned to this param
	 * @param Z axes returned to this param
	 */
	inline void GetUnitAxes(FDeterministicVector64& X, FDeterministicVector64& Y, FDeterministicVector64& Z) const;

	/**
	 * set an axis of this matrix
	 *
	 * @param i index into the axis of the matrix
	 * @param Axis vector of the axis
	 */
	inline void SetAxis(int32 i, const FDeterministicVector64& Axis);

	// Set the origin of the coordinate system to the given vector
	inline void SetOrigin(const FDeterministicVector64& NewOrigin);

	/**
	 * Update the axes of the matrix if any value is NULL do not update that axis
	 *
	 * @param Axis0 set matrix row 0
	 * @param Axis1 set matrix row 1
	 * @param Axis2 set matrix row 2
	 * @param Origin set matrix row 3
	 */
	inline void SetAxes(const FDeterministicVector64* Axis0 = NULL, const FDeterministicVector64* Axis1 = NULL, const FDeterministicVector64* Axis2 = NULL, const FDeterministicVector64* Origin = NULL);

	/**
	 * get a column of this matrix
	 *
	 * @param i index into the column of the matrix
	 * @return vector of the column
	 */
	inline FDeterministicVector64 GetColumn(int32 i) const;

	/**
	 * Set a column of this matrix
	 *
	 * @param i index of the matrix column
	 * @param Value new value of the column
	 */
	inline void SetColumn(int32 i, FDeterministicVector64 Value);

	/** @return rotator representation of this matrix */
	FDeterministicRotator64 Rotator() const;

	/**
	 * Utility for mirroring this transform across a certain plane, and flipping one of the axis as well.
	 */
	inline void Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis)
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

	private:
		/**
	 * Output an error message and trigger an ensure
	 */
		static void ErrorEnsure(const TCHAR* Message)
		{
			UE_LOG(LogUnrealMath, Error, TEXT("%s"), Message);
			ensureMsgf(false, TEXT("%s"), Message);
		}
};
