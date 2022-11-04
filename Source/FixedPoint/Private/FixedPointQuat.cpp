// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPointQuat.h"
#include "FixedPointNumbers.h"
#include "FixedPointVectors.h"


const FFixedQuat FFixedQuat::Identity = FFixedQuat(FFixed64(), FFixed64(), FFixed64(), FFixed64((int64)1));

/**
* CONSTRUCTORS
*/

//FFixedQuat



//FFixedQuat::FFixedQuat(int64 inX, int64 inY, int64 inZ, int64 inW)
//{
//	X = FFixed64(inX);
//	Y = FFixed64(inY);
//	Z = FFixed64(inZ);
//	W = FFixed64(inW);
//}
//
//FFixedQuat::FFixedQuat(float inX, float inY, float inZ, float inW)
//{
//	X = FFixed64(inX);
//	Y = FFixed64(inY);
//	Z = FFixed64(inZ);
//	W = FFixed64(inW);
//}
//
//FFixedQuat::FFixedQuat(double inX, double inY, double inZ, double inW)
//{
//	X = FFixed64(inX);
//	Y = FFixed64(inY);
//	Z = FFixed64(inZ);
//	W = FFixed64(inW);
//}

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
