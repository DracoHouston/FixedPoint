// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FixedPointFwd.h"
#include "FixedPointMatrix.generated.h"

USTRUCT(BlueprintType)
struct FIXEDPOINT_API FFixedMatrix
{
public:
	GENERATED_BODY()

	FORCEINLINE void DiagnosticCheckNaN() const {}

	/**
	* Default constructor
	*/
	FORCEINLINE FFixedMatrix() {}

	/**
	 * Constructor.
	 *
	 * @param EForceInit Force Init Enum.
	 */
	explicit FORCEINLINE FFixedMatrix(EForceInit)
	{
		FMemory::Memzero(this, sizeof(*this));
	}

	/**
	* Constructor that casts FMatrix to FFixedMatrix
	*/
	FORCEINLINE FFixedMatrix(FMatrix inValue)
	{
		M[0][0] = FFixed64(inValue.M[0][0]); M[0][1] = FFixed64(inValue.M[0][1]); M[0][2] = FFixed64(inValue.M[0][2]); M[0][3] = FFixed64(inValue.M[0][3]);
		M[1][0] = FFixed64(inValue.M[1][0]); M[1][1] = FFixed64(inValue.M[1][1]); M[1][2] = FFixed64(inValue.M[1][2]); M[1][3] = FFixed64(inValue.M[1][3]);
		M[2][0] = FFixed64(inValue.M[2][0]); M[2][1] = FFixed64(inValue.M[2][1]); M[2][2] = FFixed64(inValue.M[2][2]); M[2][3] = FFixed64(inValue.M[2][3]);
		M[3][0] = FFixed64(inValue.M[3][0]); M[3][1] = FFixed64(inValue.M[3][1]); M[3][2] = FFixed64(inValue.M[3][2]); M[3][3] = FFixed64(inValue.M[3][3]);
	}

	/**
	 * Constructor.
	 *
	 * @param InX X plane
	 * @param InY Y plane
	 * @param InZ Z plane
	 * @param InW W plane
	 */
	FORCEINLINE FFixedMatrix(const FFixedPlane& InX, const FFixedPlane& InY, const FFixedPlane& InZ, const FFixedPlane& InW);

	/**
	 * Constructor.
	 *
	 * @param InX X vector
	 * @param InY Y vector
	 * @param InZ Z vector
	 * @param InW W vector
	 */
	FORCEINLINE FFixedMatrix(const FFixedVector& InX, const FFixedVector& InY, const FFixedVector& InZ, const FFixedVector& InW);

	FFixed64 M[4][4];

	static const FFixedMatrix Identity;

	static void Internal_MatrixInverse(FFixedMatrix& DstMatrix, const FFixedMatrix& SrcMatrix)
	{
		FFixed64 Det[4];
		FFixedMatrix Tmp;

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

		const FFixed64 Determinant = SrcMatrix.M[0][0] * Det[0] - SrcMatrix.M[1][0] * Det[1] + SrcMatrix.M[2][0] * Det[2] - SrcMatrix.M[3][0] * Det[3];
		const FFixed64	RDet = FixedPoint::Constants::Fixed64::One / Determinant;

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
		M[0][0] = FixedPoint::Constants::Fixed64::One;	M[0][1] = FixedPoint::Constants::Fixed64::Zero;	M[0][2] = FixedPoint::Constants::Fixed64::Zero;	M[0][3] = FixedPoint::Constants::Fixed64::Zero;
		M[1][0] = FixedPoint::Constants::Fixed64::Zero;	M[1][1] = FixedPoint::Constants::Fixed64::One;	M[1][2] = FixedPoint::Constants::Fixed64::Zero;	M[1][3] = FixedPoint::Constants::Fixed64::Zero;
		M[2][0] = FixedPoint::Constants::Fixed64::Zero;	M[2][1] = FixedPoint::Constants::Fixed64::Zero;	M[2][2] = FixedPoint::Constants::Fixed64::One;	M[2][3] = FixedPoint::Constants::Fixed64::Zero;
		M[3][0] = FixedPoint::Constants::Fixed64::Zero;	M[3][1] = FixedPoint::Constants::Fixed64::Zero;	M[3][2] = FixedPoint::Constants::Fixed64::Zero;	M[3][3] = FixedPoint::Constants::Fixed64::One;
	}

	/**
	 * Gets the result of multiplying a Matrix to this.
	 *
	 * @param Other The matrix to multiply this by.
	 * @return The result of multiplication.
	 */
	FORCEINLINE FFixedMatrix operator* (const FFixedMatrix& Other) const
	{
		FFixedMatrix Result;
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
	FORCEINLINE void operator*=(const FFixedMatrix& Other)
	{
		*this = *this * Other;
	}

	/**
	 * Gets the result of adding a matrix to this.
	 *
	 * @param Other The Matrix to add.
	 * @return The result of addition.
	 */
	FORCEINLINE FFixedMatrix operator+ (const FFixedMatrix& Other) const
	{
		FFixedMatrix ResultMat;

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
	FORCEINLINE void operator+=(const FFixedMatrix& Other)
	{
		*this = *this + Other;
	}

	/**
	  * This isn't applying SCALE, just multiplying the value to all members - i.e. weighting
	  */
	FORCEINLINE FFixedMatrix operator* (FFixed64 Other) const
	{
		FFixedMatrix ResultMat;

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
	FORCEINLINE void operator*=(FFixed64 Other)
	{
		*this = *this * Other;
	}

	/**
	 * Checks whether two matrix are identical.
	 *
	 * @param Other The other matrix.
	 * @return true if two matrix are identical, otherwise false.
	 */
	FORCEINLINE bool operator==(const FFixedMatrix& Other) const
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
	FORCEINLINE bool Equals(const FFixedMatrix& Other, FFixed64 Tolerance) const
	{
		for (int32 X = 0; X < 4; X++)
		{
			for (int32 Y = 0; Y < 4; Y++)
			{
				if (FFixedPointMath::Abs(M[X][Y] - Other.M[X][Y]) > Tolerance)
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
	FORCEINLINE bool operator!=(const FFixedMatrix& Other) const
	{
		return !(*this == Other);
	}

	// Homogeneous transform.
	FORCEINLINE FFixedVector4d TransformFVector4(const FFixedVector4d& V) const;

	/** Transform a location - will take into account translation part of the FFixedMatrix. */
	FORCEINLINE FFixedVector4d TransformPosition(const FFixedVector& V) const;

	/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
	FORCEINLINE FFixedVector InverseTransformPosition(const FFixedVector& V) const;

	/**
	 *	Transform a direction vector - will not take into account translation part of the FFixedMatrix.
	 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
	 */
	FORCEINLINE FFixedVector4d TransformVector(const FFixedVector& V) const;

	/**
	 *	Transform a direction vector by the inverse of this matrix - will not take into account translation part.
	 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
	 */
	FORCEINLINE FFixedVector InverseTransformVector(const FFixedVector& V) const;

	// Transpose.

	FORCEINLINE FFixedMatrix GetTransposed() const
	{
		FFixedMatrix Result;

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

	FORCEINLINE FFixed64 Determinant() const
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
	FORCEINLINE FFixed64 RotDeterminant() const
	{
		return
			M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
			M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
			M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
	}

	/** Fast path, doesn't check for nil matrices in final release builds */
	FORCEINLINE FFixedMatrix InverseFast() const;

	/** Fast path, and handles nil matrices. */
	FORCEINLINE FFixedMatrix Inverse() const;

	FORCEINLINE FFixedMatrix TransposeAdjoint() const
	{
		FFixedMatrix TA;

		TA.M[0][0] = this->M[1][1] * this->M[2][2] - this->M[1][2] * this->M[2][1];
		TA.M[0][1] = this->M[1][2] * this->M[2][0] - this->M[1][0] * this->M[2][2];
		TA.M[0][2] = this->M[1][0] * this->M[2][1] - this->M[1][1] * this->M[2][0];
		TA.M[0][3] = FixedPoint::Constants::Fixed64::Zero;

		TA.M[1][0] = this->M[2][1] * this->M[0][2] - this->M[2][2] * this->M[0][1];
		TA.M[1][1] = this->M[2][2] * this->M[0][0] - this->M[2][0] * this->M[0][2];
		TA.M[1][2] = this->M[2][0] * this->M[0][1] - this->M[2][1] * this->M[0][0];
		TA.M[1][3] = FixedPoint::Constants::Fixed64::Zero;

		TA.M[2][0] = this->M[0][1] * this->M[1][2] - this->M[0][2] * this->M[1][1];
		TA.M[2][1] = this->M[0][2] * this->M[1][0] - this->M[0][0] * this->M[1][2];
		TA.M[2][2] = this->M[0][0] * this->M[1][1] - this->M[0][1] * this->M[1][0];
		TA.M[2][3] = FixedPoint::Constants::Fixed64::Zero;

		TA.M[3][0] = FixedPoint::Constants::Fixed64::Zero;
		TA.M[3][1] = FixedPoint::Constants::Fixed64::Zero;
		TA.M[3][2] = FixedPoint::Constants::Fixed64::Zero;
		TA.M[3][3] = FixedPoint::Constants::Fixed64::One;

		return TA;
	}

	// NOTE: There is some compiler optimization issues with WIN64 that cause FORCEINLINE to cause a crash
	// Remove any scaling from this matrix (ie magnitude of each row is 1) with error Tolerance
	inline void RemoveScaling(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber)
	{
		// For each row, find magnitude, and if its non-zero re-scale so its unit length.
		const FFixed64 SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
		const FFixed64 SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
		const FFixed64 SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);
		const FFixed64 Scale0 = FFixedPointMath::FloatSelect(SquareSum0 - Tolerance, FFixedPointMath::InvSqrt(SquareSum0), FFixed64(1));
		const FFixed64 Scale1 = FFixedPointMath::FloatSelect(SquareSum1 - Tolerance, FFixedPointMath::InvSqrt(SquareSum1), FFixed64(1));
		const FFixed64 Scale2 = FFixedPointMath::FloatSelect(SquareSum2 - Tolerance, FFixedPointMath::InvSqrt(SquareSum2), FFixed64(1));
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
	inline FFixedMatrix GetMatrixWithoutScale(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber) const
	{
		FFixedMatrix Result = *this;
		Result.RemoveScaling(Tolerance);
		return Result;
	}

	/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present with error Tolerance */
	inline FFixedVector ExtractScaling(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber);

	/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector) with error Tolerance. */
	inline FFixedVector GetScaleVector(FFixed64 Tolerance = FixedPoint::Constants::Fixed64::SmallNumber) const;

	// Remove any translation from this matrix
	inline FFixedMatrix RemoveTranslation() const
	{
		FFixedMatrix Result = *this;
		Result.M[3][0] = 0.0f;
		Result.M[3][1] = 0.0f;
		Result.M[3][2] = 0.0f;
		return Result;
	}

	/** Returns a matrix with an additional translation concatenated. */
	inline FFixedMatrix ConcatTranslation(const FFixedVector& Translation) const;

	/** Returns true if any element of this matrix is NaN */
	inline bool ContainsNaN() const
	{
		return false;
	}

	/** Scale the translation part of the matrix by the supplied vector. */
	inline void ScaleTranslation(const FFixedVector& Scale3D);

	/** @return the minimum magnitude of any row of the matrix. */
	inline FFixed64 GetMinimumAxisScale() const
	{
		const FFixed64 MaxRowScaleSquared = FFixedPointMath::Min(
			GetScaledAxis(EAxis::X).SizeSquared(),
			FFixedPointMath::Min(
				GetScaledAxis(EAxis::Y).SizeSquared(),
				GetScaledAxis(EAxis::Z).SizeSquared()
			)
		);
		return FFixedPointMath::Sqrt(MaxRowScaleSquared);
	}

	/** @return the maximum magnitude of any row of the matrix. */
	inline FFixed64 GetMaximumAxisScale() const
	{
		const FFixed64 MaxRowScaleSquared = FFixedPointMath::Max(
			GetScaledAxis(EAxis::X).SizeSquared(),
			FFixedPointMath::Max(
				GetScaledAxis(EAxis::Y).SizeSquared(),
				GetScaledAxis(EAxis::Z).SizeSquared()
			)
		);
		return FFixedPointMath::Sqrt(MaxRowScaleSquared);
	}

	/** Apply Scale to this matrix **/
	inline FFixedMatrix ApplyScale(FFixed64 Scale) const;

	// @return the origin of the co-ordinate system
	inline FFixedVector GetOrigin() const;

	/**
	 * get axis of this matrix scaled by the scale of the matrix
	 *
	 * @param i index into the axis of the matrix
	 * @ return vector of the axis
	 */
	FORCEINLINE FFixedVector GetScaledAxis(EAxis::Type Axis) const;

	/**
	 * get axes of this matrix scaled by the scale of the matrix
	 *
	 * @param X axes returned to this param
	 * @param Y axes returned to this param
	 * @param Z axes returned to this param
	 */
	inline void GetScaledAxes(FFixedVector& X, FFixedVector& Y, FFixedVector& Z) const;

	/**
	 * get unit length axis of this matrix
	 *
	 * @param i index into the axis of the matrix
	 * @return vector of the axis
	 */
	inline FFixedVector GetUnitAxis(EAxis::Type Axis) const;

	/**
	 * get unit length axes of this matrix
	 *
	 * @param X axes returned to this param
	 * @param Y axes returned to this param
	 * @param Z axes returned to this param
	 */
	inline void GetUnitAxes(FFixedVector& X, FFixedVector& Y, FFixedVector& Z) const;

	/**
	 * set an axis of this matrix
	 *
	 * @param i index into the axis of the matrix
	 * @param Axis vector of the axis
	 */
	inline void SetAxis(int32 i, const FFixedVector& Axis);

	// Set the origin of the coordinate system to the given vector
	inline void SetOrigin(const FFixedVector& NewOrigin);

	/**
	 * Update the axes of the matrix if any value is NULL do not update that axis
	 *
	 * @param Axis0 set matrix row 0
	 * @param Axis1 set matrix row 1
	 * @param Axis2 set matrix row 2
	 * @param Origin set matrix row 3
	 */
	inline void SetAxes(const FFixedVector* Axis0 = NULL, const FFixedVector* Axis1 = NULL, const FFixedVector* Axis2 = NULL, const FFixedVector* Origin = NULL);

	/**
	 * get a column of this matrix
	 *
	 * @param i index into the column of the matrix
	 * @return vector of the column
	 */
	inline FFixedVector GetColumn(int32 i) const;

	/**
	 * Set a column of this matrix
	 *
	 * @param i index of the matrix column
	 * @param Value new value of the column
	 */
	inline void SetColumn(int32 i, FFixedVector Value);

	/** @return rotator representation of this matrix */
	FFixedRotator Rotator() const;

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
