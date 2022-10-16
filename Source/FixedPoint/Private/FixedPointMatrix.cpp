// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointMatrix.h"
#include "FixedPointNumbers.h"
#include "FixedPointVectors.h"

/**
* CONSTRUCTORS
*/

//FFixedMatrix

FFixedMatrix::FFixedMatrix(FMatrix inValue)
{
	M[0][0] = FFixed64(inValue.M[0][0]); M[0][1] = FFixed64(inValue.M[0][1]); M[0][2] = FFixed64(inValue.M[0][2]); M[0][3] = FFixed64(inValue.M[0][3]);
	M[1][0] = FFixed64(inValue.M[1][0]); M[1][1] = FFixed64(inValue.M[1][1]); M[1][2] = FFixed64(inValue.M[1][2]); M[1][3] = FFixed64(inValue.M[1][3]);
	M[2][0] = FFixed64(inValue.M[2][0]); M[2][1] = FFixed64(inValue.M[2][1]); M[2][2] = FFixed64(inValue.M[2][2]); M[2][3] = FFixed64(inValue.M[2][3]);
	M[3][0] = FFixed64(inValue.M[3][0]); M[3][1] = FFixed64(inValue.M[3][1]); M[3][2] = FFixed64(inValue.M[3][2]); M[3][3] = FFixed64(inValue.M[3][3]);
}

/**
* ACCESSORS
*/

/**
* SETTERS
*/

/**
* HELPERS
*/

/**
* COMPARISON OPERATORS
*/

/**
* ARITHMETIC OPERATORS
*/
