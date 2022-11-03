// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FixedPointTypes.h"
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
		FFixedMatrix() {}

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
	FFixedMatrix(FMatrix inValue);

	FFixed64 M[4][4];

	static const FFixedMatrix Identity;

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
	FORCEINLINE void SetIdentity();

	/**
	 * Gets the result of multiplying a Matrix to this.
	 *
	 * @param Other The matrix to multiply this by.
	 * @return The result of multiplication.
	 */
	FORCEINLINE FFixedMatrix operator* (const FFixedMatrix& Other) const;

	/**
	 * Multiply this by a matrix.
	 *
	 * @param Other the matrix to multiply by this.
	 * @return reference to this after multiply.
	 */
	FORCEINLINE void operator*=(const FFixedMatrix& Other);

	/**
	 * Gets the result of adding a matrix to this.
	 *
	 * @param Other The Matrix to add.
	 * @return The result of addition.
	 */
	FORCEINLINE FFixedMatrix operator+ (const FFixedMatrix& Other) const;

	/**
	 * Adds to this matrix.
	 *
	 * @param Other The matrix to add to this.
	 * @return Reference to this after addition.
	 */
	FORCEINLINE void operator+=(const FFixedMatrix& Other);

	/**
	  * This isn't applying SCALE, just multiplying the value to all members - i.e. weighting
	  */
	FORCEINLINE FFixedMatrix operator* (FFixed64 Other) const;

	/**
	 * Multiply this matrix by a weighting factor.
	 *
	 * @param other The weight.
	 * @return a reference to this after weighting.
	 */
	FORCEINLINE void operator*=(FFixed64 Other);

	/**
	 * Checks whether two matrix are identical.
	 *
	 * @param Other The other matrix.
	 * @return true if two matrix are identical, otherwise false.
	 */
	FORCEINLINE bool operator==(const FFixedMatrix& Other) const;

	/**
	 * Checks whether another Matrix is equal to this, within specified tolerance.
	 *
	 * @param Other The other Matrix.
	 * @param Tolerance Error Tolerance.
	 * @return true if two Matrix are equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool Equals(const FFixedMatrix& Other, FFixed64 Tolerance) const;

	/**
	 * Checks whether another Matrix is not equal to this, within specified tolerance.
	 *
	 * @param Other The other Matrix.
	 * @return true if two Matrix are not equal, within specified tolerance, otherwise false.
	 */
	FORCEINLINE bool operator!=(const FFixedMatrix& Other) const;

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

	FORCEINLINE FFixedMatrix GetTransposed() const;

	// @return determinant of this matrix.

	FORCEINLINE FFixed64 Determinant() const;

	/** @return the determinant of rotation 3x3 matrix */
	FORCEINLINE FFixed64 RotDeterminant() const;

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

	/**
	 * get axis of this matrix scaled by the scale of the matrix
	 *
	 * @param i index into the axis of the matrix
	 * @ return vector of the axis
	 */
	FORCEINLINE FFixedVector GetScaledAxis(EAxis::Type Axis) const;

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



FORCEINLINE  FFixedMatrix::FFixedMatrix(const FFixedVector& InX, const FFixedVector& InY, const FFixedVector& InZ, const FFixedVector& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = FixedPoint::Constants::Fixed64::Zero;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = FixedPoint::Constants::Fixed64::Zero;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = FixedPoint::Constants::Fixed64::Zero;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = FixedPoint::Constants::Fixed64::One;
}

FORCEINLINE void  FFixedMatrix::SetIdentity()
{
	M[0][0] = FixedPoint::Constants::Fixed64::One;	M[0][1] = FixedPoint::Constants::Fixed64::Zero;	M[0][2] = FixedPoint::Constants::Fixed64::Zero;	M[0][3] = FixedPoint::Constants::Fixed64::Zero;
	M[1][0] = FixedPoint::Constants::Fixed64::Zero;	M[1][1] = FixedPoint::Constants::Fixed64::One;	M[1][2] = FixedPoint::Constants::Fixed64::Zero;	M[1][3] = FixedPoint::Constants::Fixed64::Zero;
	M[2][0] = FixedPoint::Constants::Fixed64::Zero;	M[2][1] = FixedPoint::Constants::Fixed64::Zero;	M[2][2] = FixedPoint::Constants::Fixed64::One;	M[2][3] = FixedPoint::Constants::Fixed64::Zero;
	M[3][0] = FixedPoint::Constants::Fixed64::Zero;	M[3][1] = FixedPoint::Constants::Fixed64::Zero;	M[3][2] = FixedPoint::Constants::Fixed64::Zero;	M[3][3] = FixedPoint::Constants::Fixed64::One;
}

FORCEINLINE void FFixedMatrix::operator*=(const FFixedMatrix& Other)
{
	*this = *this * Other;
}


FORCEINLINE FFixedMatrix FFixedMatrix::operator*(const FFixedMatrix& Other) const
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

FORCEINLINE FFixedMatrix FFixedMatrix::operator+(const FFixedMatrix& Other) const
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

FORCEINLINE void FFixedMatrix::operator+=(const FFixedMatrix& Other)
{
	*this = *this + Other;
}

FORCEINLINE FFixedMatrix FFixedMatrix::operator*(FFixed64 Other) const
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

FORCEINLINE void FFixedMatrix::operator*=(FFixed64 Other)
{
	*this = *this * Other;
}

// Comparison operators.

FORCEINLINE bool FFixedMatrix::operator==(const FFixedMatrix& Other) const
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

inline bool FFixedMatrix::Equals(const FFixedMatrix& Other, FFixed64 Tolerance) const
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

inline bool FFixedMatrix::operator!=(const FFixedMatrix& Other) const
{
	return !(*this == Other);
}

FORCEINLINE FFixedVector4d FFixedMatrix::TransformFVector4(const FFixedVector4d& P) const
{
	FFixedVector4d VOurX = FFixedVector4d(M[0][0], M[0][1], M[0][2], M[0][3]);
	FFixedVector4d VOurY = FFixedVector4d(M[1][0], M[1][1], M[1][2], M[1][3]);
	FFixedVector4d VOurZ = FFixedVector4d(M[2][0], M[2][1], M[2][2], M[2][3]);
	FFixedVector4d VOurW = FFixedVector4d(M[3][0], M[3][1], M[3][2], M[3][3]);

	FFixedVector4d VTempX = FFixedVector4d(P.X);
	FFixedVector4d VTempY = FFixedVector4d(P.Y);
	FFixedVector4d VTempZ = FFixedVector4d(P.Z);
	FFixedVector4d VTempW = FFixedVector4d(P.W);

	VTempX = VTempX * VOurX;
	VTempX = (VTempY * VOurY) + VTempX;
	VTempX = (VTempZ * VOurZ) + VTempX;
	VTempX = (VTempW * VOurW) + VTempX;

	return VTempX;
}

FORCEINLINE FFixedVector4d FFixedMatrix::TransformPosition(const FFixedVector& V) const
{
	return TransformFVector4(FFixedVector4d(V.X, V.Y, V.Z, FixedPoint::Constants::Fixed64::One));
}

FORCEINLINE FFixedVector FFixedMatrix::InverseTransformPosition(const FFixedVector& V) const
{
	FFixedMatrix InvSelf = this->InverseFast();
	//return InvSelf.TransformPosition(V);
	return FFixedVector();
}

FORCEINLINE FFixedVector4d FFixedMatrix::TransformVector(const FFixedVector& V) const
{
	return TransformFVector4(FFixedVector4d(V.X, V.Y, V.Z, FFixed64()));
}

FORCEINLINE FFixedVector FFixedMatrix::InverseTransformVector(const FFixedVector& V) const
{
	FFixedMatrix InvSelf = this->InverseFast();
	//return InvSelf.TransformVector(V);
	return FFixedVector();
}

FORCEINLINE FFixedMatrix FFixedMatrix::GetTransposed() const
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

FORCEINLINE FFixed64 FFixedMatrix::Determinant() const
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

FORCEINLINE FFixed64 FFixedMatrix::RotDeterminant() const
{
	return
		M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
		M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
		M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
}

FORCEINLINE FFixedMatrix FFixedMatrix::InverseFast() const
{
	// If we're in non final release, then make sure we're not creating NaNs
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber))
	{
		ErrorEnsure(TEXT("FFixedMatrix::InverseFast(), trying to invert a NIL matrix, garbage in, garbage out! Use Inverse() instead."));
	}
	else
	{
		const FFixed64	Det = Determinant();

		if (Det == FixedPoint::Constants::Fixed64::Zero)
		{
			ErrorEnsure(TEXT("FFixedMatrix::InverseFast(), trying to invert a non-invertible matrix, garbage in, garbage out! Use Inverse() instead."));
		}
	}
#endif
	FFixedMatrix Result;
	Internal_MatrixInverse(Result, *this);
	return Result;
}

FORCEINLINE FFixedMatrix FFixedMatrix::Inverse() const
{
	FFixedMatrix Result;

	//Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(FixedPoint::Constants::Fixed64::SmallNumber))
	{
		// just set to zero - avoids unsafe inverse of zero and duplicates what QNANs were resulting in before (scaling away all children)
		Result = Identity;
	}
	else
	{
		const FFixed64	Det = Determinant();

		if (Det == FixedPoint::Constants::Fixed64::Zero)
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