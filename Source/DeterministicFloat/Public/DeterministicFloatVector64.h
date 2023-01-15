// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DeterministicFloatFwd.h"
#include "DeterministicFloatNumbers.h"
#include "DeterministicFloatVector64.generated.h"

USTRUCT(BlueprintType)
struct DETERMINISTICFLOAT_API FDeterministicVector64
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 X;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Y;

	UPROPERTY(EditAnywhere)
	FDeterministicNumber64 Z;

	/**
	* Default constructor, no initialization
	*/
	FORCEINLINE FDeterministicVector64() {}
	
	/**
	* Constructor that casts FVector to FDeterministicVector64
	*/
	FORCEINLINE FDeterministicVector64(const FVector& inValue)
	{
		X = inValue.X;
		Y = inValue.Y;
		Z = inValue.Z;
	}

	/**
	* Sets all components to the supplied FDeterministicNumber64 value
	*/
	FORCEINLINE FDeterministicVector64(const FDeterministicNumber64& inValue)
	{
		X = inValue;
		Y = inValue;
		Z = inValue;
	}

	/**
	* Sets components to the supplied FDeterministicNumber64 values
	*/
	FORCEINLINE FDeterministicVector64(const FDeterministicNumber64& inX, const FDeterministicNumber64& inY, const FDeterministicNumber64& inZ) : X(inX), Y(inY), Z(inZ){}

	/**
	 * Constructs a vector from an TVector2<T> and Z value.
	 *
	 * @param V Vector to copy from.
	 * @param InZ Z Coordinate.
	 */
	explicit FORCEINLINE FDeterministicVector64(const FDeterministicVector2D64& V, const FDeterministicNumber64& InZ);

	/**
	 * Constructor using the XYZ components from a 4D vector.
	 *
	 * @param V 4D Vector to copy from.
	 */
	FORCEINLINE FDeterministicVector64(const FDeterministicVector4D64& V);

	explicit FORCEINLINE FDeterministicVector64(EForceInit) : X(DeterministicFloat::Constants::Number64::Zero), Y(DeterministicFloat::Constants::Number64::Zero), Z(DeterministicFloat::Constants::Number64::Zero) {}

	/** Zero vector (0,0,0) */
	static const FDeterministicVector64 ZeroVector;

	/** One vector (1,1,1) */
	static const FDeterministicVector64 OneVector;

	/** Unreal up vector (0,0,1) */
	static const FDeterministicVector64 UpVector;

	/** Unreal down vector (0,0,-1) */
	static const FDeterministicVector64 DownVector;

	/** Unreal forward vector (1,0,0) */
	static const FDeterministicVector64 ForwardVector;

	/** Unreal backward vector (-1,0,0) */
	static const FDeterministicVector64 BackwardVector;

	/** Unreal right vector (0,1,0) */
	static const FDeterministicVector64 RightVector;

	/** Unreal left vector (0,-1,0) */
	static const FDeterministicVector64 LeftVector;

	/** Unit X axis vector (1,0,0) */
	static const FDeterministicVector64 XAxisVector;

	/** Unit Y axis vector (0,1,0) */
	static const FDeterministicVector64 YAxisVector;

	/** Unit Z axis vector (0,0,1) */
	static const FDeterministicVector64 ZAxisVector;

	/** @return Zero Vector (0,0,0) */
	static inline FDeterministicVector64 Zero() { return ZeroVector; }

	/** @return One Vector (1,1,1) */
	static inline FDeterministicVector64 One() { return OneVector; }

	/** @return Unit X Vector (1,0,0)  */
	static inline FDeterministicVector64 UnitX() { return XAxisVector; }

	/** @return Unit Y Vector (0,1,0)  */
	static inline FDeterministicVector64 UnitY() { return YAxisVector; }

	/** @return Unit Z Vector (0,0,1)  */
	static inline FDeterministicVector64 UnitZ() { return ZAxisVector; }

	//for interoperability with epics classes, they do nothing, ints and fixed point numbers can't be nan

	FORCEINLINE void DiagnosticCheckNaN() const {}
	FORCEINLINE void DiagnosticCheckNaN(const TCHAR* Message) const {}

	/**
	* Equals, will find if this and Other are within supplied tolerance
	*/
	FORCEINLINE bool Equals(const FDeterministicVector64& Other, const FDeterministicNumber64& inTolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	/**
	* All Components Equal, will find if this vector's components are all equal, within supplied tolerance
	*/
	FORCEINLINE bool AllComponentsEqual(const FDeterministicNumber64& inTolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;


	/**
	 * Get the maximum value of the vector's components.
	 *
	 * @return The maximum value of the vector's components.
	 */
	FORCEINLINE FDeterministicNumber64 GetMax() const;

	/**
	 * Get the maximum absolute value of the vector's components.
	 *
	 * @return The maximum absolute value of the vector's components.
	 */
	FORCEINLINE FDeterministicNumber64 GetAbsMax() const;

	/**
	 * Get the minimum value of the vector's components.
	 *
	 * @return The minimum value of the vector's components.
	 */
	FORCEINLINE FDeterministicNumber64 GetMin() const;

	/**
	 * Get the minimum absolute value of the vector's components.
	 *
	 * @return The minimum absolute value of the vector's components.
	 */
	FORCEINLINE FDeterministicNumber64 GetAbsMin() const;

	/**
	 * Get a copy of this vector with absolute value of each component.
	 *
	 * @return A copy of this vector with absolute value of each component.
	 */
	FORCEINLINE FDeterministicVector64 GetAbs() const;

	/** Gets the component-wise min of two vectors. */
	FORCEINLINE FDeterministicVector64 ComponentMin(const FDeterministicVector64& Other) const;

	/** Gets the component-wise max of two vectors. */
	FORCEINLINE FDeterministicVector64 ComponentMax(const FDeterministicVector64& Other) const;

	FORCEINLINE FDeterministicNumber64 SizeSquared() const;

	FORCEINLINE FDeterministicNumber64 Size() const;

	/**
	 * Get the length of the 2D components of this vector.
	 *
	 * @return The 2D length of this vector.
	 */
	FORCEINLINE FDeterministicNumber64 Size2D() const;

	/**
	 * Get the squared length of the 2D components of this vector.
	 *
	 * @return The squared 2D length of this vector.
	 */
	FORCEINLINE FDeterministicNumber64 SizeSquared2D() const;

	/**
	 * Checks whether vector is near to zero within a specified tolerance.
	 *
	 * @param Tolerance Error tolerance.
	 * @return true if the vector is near to zero, false otherwise.
	 */
	FORCEINLINE bool IsNearlyZero(const FDeterministicNumber64& Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	/**
	 * Checks whether all components of the vector are exactly zero.
	 *
	 * @return true if the vector is exactly zero, false otherwise.
	 */
	FORCEINLINE bool IsZero() const;

	/**
	 * Check if the vector is of unit length, with specified tolerance.
	 *
	 * @param LengthSquaredTolerance Tolerance against squared length.
	 * @return true if the vector is a unit vector within the specified tolerance.
	 */
	FORCEINLINE bool IsUnit(const FDeterministicNumber64& LengthSquaredTolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	/**
	 * Checks whether vector is normalized.
	 *
	 * @return true if normalized, false otherwise.
	 */
	FORCEINLINE bool IsNormalized() const;

	/**
	 * Normalize this vector in-place if it is larger than a given tolerance. Leaves it unchanged if not.
	 *
	 * @param Tolerance Minimum squared length of vector for normalization.
	 * @return true if the vector was normalized correctly, false otherwise.
	 */
	FORCEINLINE bool Normalize(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::SmallNumber);

	/**
	 * Squared distance between two points.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The squared distance between two points.
	 */
	FORCEINLINE static FDeterministicNumber64 DistSquared(const FDeterministicVector64& A, const FDeterministicVector64& B);
	
	/**
	 * Euclidean distance between two points.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The distance between two points.
	 */
	FORCEINLINE static FDeterministicNumber64 Dist(const FDeterministicVector64& A, const FDeterministicVector64& B);
	static FORCEINLINE FDeterministicNumber64 Distance(const FDeterministicVector64& V1, const FDeterministicVector64& V2);

	/**
	 * Squared distance between two points in the XY plane only.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The squared distance between two points in the XY plane
	 */
	static FORCEINLINE FDeterministicNumber64 DistSquaredXY(const FDeterministicVector64& V1, const FDeterministicVector64& V2);
	static FORCEINLINE FDeterministicNumber64 DistSquared2D(const FDeterministicVector64& V1, const FDeterministicVector64& V2);

	/**
	* Euclidean distance between two points in the XY plane (ignoring Z).
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The distance between two points in the XY plane.
	*/
	static FORCEINLINE FDeterministicNumber64 DistXY(const FDeterministicVector64& V1, const FDeterministicVector64& V2);
	static FORCEINLINE FDeterministicNumber64 Dist2D(const FDeterministicVector64& V1, const FDeterministicVector64& V2);

	/**
	 * Calculate cross product between this and another vector.
	 *
	 * @param V The other vector.
	 * @return The cross product.
	 */
	FORCEINLINE FDeterministicVector64 Cross(const FDeterministicVector64& V2) const;

	FORCEINLINE static FDeterministicVector64 CrossProduct(const FDeterministicVector64& A, const FDeterministicVector64& B);

	FORCEINLINE static FDeterministicVector64 DotProduct(const FDeterministicVector64& A, const FDeterministicVector64& B);

	/**
	 * Triple product of three vectors: X dot (Y cross Z).
	 *
	 * @param X The first vector.
	 * @param Y The second vector.
	 * @param Z The third vector.
	 * @return The triple product: X dot (Y cross Z).
	 */
	FORCEINLINE static FDeterministicVector64 Triple(const FDeterministicVector64& X, const FDeterministicVector64& Y, const FDeterministicVector64& Z);

	FORCEINLINE bool operator==(const FDeterministicVector64& Other) const;

	FORCEINLINE bool operator!=(const FDeterministicVector64& Other) const;

	FORCEINLINE FDeterministicVector64 operator-() const;

	FORCEINLINE FDeterministicVector64 operator+(const FDeterministicVector64& Other) const;

	FORCEINLINE FDeterministicVector64 operator-(const FDeterministicVector64& Other) const;

	FORCEINLINE FDeterministicVector64 operator*(const FDeterministicVector64& Other) const;

	FORCEINLINE FDeterministicVector64 operator/(const FDeterministicVector64& Other) const;

	FORCEINLINE FDeterministicVector64 operator+(const FDeterministicNumber64& Other) const;

	FORCEINLINE FDeterministicVector64 operator-(const FDeterministicNumber64& Other) const;

	FORCEINLINE FDeterministicVector64 operator*(const FDeterministicNumber64& Other) const;

	FORCEINLINE FDeterministicVector64 operator/(const FDeterministicNumber64& Other) const;

	FORCEINLINE FDeterministicVector64 operator+=(const FDeterministicVector64& Other);

	FORCEINLINE FDeterministicVector64 operator-=(const FDeterministicVector64& Other);

	FORCEINLINE FDeterministicVector64 operator*=(const FDeterministicVector64& Other);

	FORCEINLINE FDeterministicVector64 operator/=(const FDeterministicVector64& Other);

	FORCEINLINE FDeterministicVector64 operator+=(const FDeterministicNumber64& Other);

	FORCEINLINE FDeterministicVector64 operator-=(const FDeterministicNumber64& Other);

	FORCEINLINE FDeterministicVector64 operator*=(const FDeterministicNumber64& Other);

	FORCEINLINE FDeterministicVector64 operator/=(const FDeterministicNumber64& Other);

	FORCEINLINE FDeterministicVector64 operator^(const FDeterministicVector64& Other) const;

	FORCEINLINE FDeterministicNumber64 operator|(const FDeterministicVector64& Other) const;

	/**
	 * Gets specific component of the vector.
	 *
	 * @param Index the index of vector component
	 * @return reference to component.
	 */
	FORCEINLINE FDeterministicNumber64& operator[](int32 Index);

	/**
	 * Gets specific component of the vector.
	 *
	 * @param Index the index of vector component
	 * @return Copy of the component.
	 */
	FORCEINLINE FDeterministicNumber64 operator[](int32 Index)const;

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	*
	* @return Reference to the specified component.
	*/
	FORCEINLINE FDeterministicNumber64& Component(int32 Index);

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	* @return Copy of the specified component.
	*/
	FORCEINLINE FDeterministicNumber64 Component(int32 Index) const;

	/** Get a specific component of the vector, given a specific axis by enum */
	FORCEINLINE FDeterministicNumber64 GetComponentForAxis(EAxis::Type Axis) const;

	/** Set a specified componet of the vector, given a specific axis by enum */
	FORCEINLINE void SetComponentForAxis(EAxis::Type Axis, const FDeterministicNumber64& Component);

	/**
	* Set the values of the vector directly.
	*
	* @param InX New X coordinate.
	* @param InY New Y coordinate.
	* @param InZ New Z coordinate.
	*/
	FORCEINLINE void Set(const FDeterministicNumber64& InX, const FDeterministicNumber64& InY, const FDeterministicNumber64& InZ);

	/**
	 * Calculates normalized version of vector without checking for zero length.
	 *
	 * @return Normalized version of vector.
	 * @see GetSafeNormal()
	 */
	FORCEINLINE FDeterministicVector64 GetUnsafeNormal() const;

	/**
	 * Gets a normalized copy of the vector, checking it is safe to do so based on the length.
	 * Returns zero vector by default if vector length is too small to safely normalize.
	 *
	 * @param Tolerance Minimum squared vector length.
	 * @return A normalized copy if safe, ResultIfZero otherwise.
	 */
	FORCEINLINE FDeterministicVector64 GetSafeNormal(const FDeterministicNumber64& Tolerance = DeterministicFloat::Constants::Number64::SmallNumber, const FDeterministicVector64& ResultIfZero = ZeroVector) const;

	/**
	* Calculates normalized 2D version of vector without checking for zero length.
	*
	* @return Normalized version of vector.
	* @see GetSafeNormal2D()
	*/
	FORCEINLINE FDeterministicVector64 GetUnsafeNormal2D() const;

	/**
	 * Gets a normalized copy of the 2D components of the vector, checking it is safe to do so. Z is set to zero.
	 * Returns zero vector by default if vector length is too small to normalize.
	 *
	 * @param Tolerance Minimum squared vector length.
	 * @return Normalized copy if safe, otherwise returns ResultIfZero.
	 */
	FORCEINLINE FDeterministicVector64 GetSafeNormal2D(const FDeterministicNumber64& Tolerance = DeterministicFloat::Constants::Number64::SmallNumber, const FDeterministicVector64& ResultIfZero = ZeroVector) const;

	/**
	 * Util to convert this vector into a unit direction vector and its original length.
	 *
	 * @param OutDir Reference passed in to store unit direction vector.
	 * @param OutLength Reference passed in to store length of the vector.
	 */
	FORCEINLINE void ToDirectionAndLength(FDeterministicVector64& OutDir, FDeterministicNumber64& OutLength) const;

	/**
	 * Get a copy of the vector as sign only.
	 * Each component is set to +1 or -1, with the sign of zero treated as +1.
	 *
	 * @param A copy of the vector with each component set to +1 or -1
	 */
	FORCEINLINE FDeterministicVector64 GetSignVector() const;

	/**
	 * Projects 2D components of vector based on Z.
	 *
	 * @return Projected version of vector based on Z.
	 */
	FORCEINLINE FDeterministicVector64 Projection() const;

	/**
	 * Gets a copy of this vector snapped to a grid.
	 *
	 * @param GridSz Grid dimension.
	 * @return A copy of this vector snapped to a grid.
	 * @see FMath::GridSnap()
	 */
	FORCEINLINE FDeterministicVector64 GridSnap(const FDeterministicNumber64& GridSz) const;

	/**
	 * Get a copy of this vector, clamped inside of a cube.
	 *
	 * @param Radius Half size of the cube.
	 * @return A copy of this vector, bound by cube.
	 */
	FORCEINLINE FDeterministicVector64 BoundToCube(FDeterministicNumber64 Radius) const;

	/** Get a copy of this vector, clamped inside of a cube. */
	FORCEINLINE FDeterministicVector64 BoundToBox(const FDeterministicVector64& Min, const FDeterministicVector64& Max) const;

	/** Create a copy of this vector, with its magnitude clamped between Min and Max. */
	FORCEINLINE FDeterministicVector64 GetClampedToSize(FDeterministicNumber64 Min, FDeterministicNumber64 Max) const;

	/** Create a copy of this vector, with the 2D magnitude clamped between Min and Max. Z is unchanged. */
	FORCEINLINE FDeterministicVector64 GetClampedToSize2D(FDeterministicNumber64 Min, FDeterministicNumber64 Max) const;

	/** Create a copy of this vector, with its maximum magnitude clamped to MaxSize. */
	FORCEINLINE FDeterministicVector64 GetClampedToMaxSize(FDeterministicNumber64 MaxSize) const;

	/** Create a copy of this vector, with the maximum 2D magnitude clamped to MaxSize. Z is unchanged. */
	FORCEINLINE FDeterministicVector64 GetClampedToMaxSize2D(FDeterministicNumber64 MaxSize) const;

	/**
	 * Add a vector to this and clamp the result in a cube.
	 *
	 * @param V Vector to add.
	 * @param Radius Half size of the cube.
	 */
	FORCEINLINE void AddBounded(const FDeterministicVector64& V, FDeterministicNumber64 Radius = MAX_int16);

	/**
	 * Gets the reciprocal of this vector, avoiding division by zero.
	 * Zero components are set to BIG_NUMBER.
	 *
	 * @return Reciprocal of this vector.
	 */
	FORCEINLINE FDeterministicVector64 Reciprocal() const;

	/**
	 * Check whether X, Y and Z are nearly equal.
	 *
	 * @param Tolerance Specified Tolerance.
	 * @return true if X == Y == Z within the specified tolerance.
	 */
	FORCEINLINE bool IsUniform(FDeterministicNumber64 Tolerance = DeterministicFloat::Constants::Number64::KindaSmallNumber) const;

	/**
	 * Mirror a vector about a normal vector.
	 *
	 * @param MirrorNormal Normal vector to mirror about.
	 * @return Mirrored vector.
	 */
	FORCEINLINE FDeterministicVector64 MirrorByVector(const FDeterministicVector64& MirrorNormal) const;

	/**
	 * Mirrors a vector about a plane.
	 *
	 * @param Plane Plane to mirror about.
	 * @return Mirrored vector.
	 */
	FDeterministicVector64 MirrorByPlane(const FDeterministicPlane64& Plane) const;

	/**
	 * Calculate the projection of a point on the given plane.
	 *
	 * @param Point The point to project onto the plane
	 * @param Plane The plane
	 * @return Projection of Point onto Plane
	 */
	static FDeterministicVector64 PointPlaneProject(const FDeterministicVector64& Point, const FDeterministicPlane64& Plane);

	/**
	 * Calculate the projection of a point on the plane defined by counter-clockwise (CCW) points A,B,C.
	 *
	 * @param Point The point to project onto the plane
	 * @param A 1st of three points in CCW order defining the plane
	 * @param B 2nd of three points in CCW order defining the plane
	 * @param C 3rd of three points in CCW order defining the plane
	 * @return Projection of Point onto plane ABC
	 */
	static FDeterministicVector64 PointPlaneProject(const FDeterministicVector64& Point, const FDeterministicVector64& A, const FDeterministicVector64& B, const FDeterministicVector64& C);

	/**
	 * Calculate the projection of a vector on the plane defined by PlaneNormal.
	 *
	 * @param  V The vector to project onto the plane.
	 * @param  PlaneNormal Normal of the plane (assumed to be unit length).
	 * @return Projection of V onto plane.
	 */
	FORCEINLINE static FDeterministicVector64 VectorPlaneProject(const FDeterministicVector64& V, const FDeterministicVector64& PlaneNormal);

	/**
	 * Rotates around Axis (assumes Axis.Size() == 1).
	 *
	 * @param AngleRad Angle to rotate (in radians).
	 * @param Axis Axis to rotate around.
	 * @return Rotated Vector.
	 */
	FORCEINLINE FDeterministicVector64 RotateAngleAxisRad(const FDeterministicNumber64 AngleRad, const FDeterministicVector64& Axis) const;

	/**
	 * Rotates around Axis (assumes Axis.Size() == 1).
	 *
	 * @param AngleDeg Angle to rotate (in degrees).
	 * @param Axis Axis to rotate around.
	 * @return Rotated Vector.
	 */
	FORCEINLINE FDeterministicVector64 RotateAngleAxis(const FDeterministicNumber64 AngleDeg, const FDeterministicVector64& Axis) const;

	/**
	 * Returns the cosine of the angle between this vector and another projected onto the XY plane (no Z).
	 *
	 * @param B the other vector to find the 2D cosine of the angle with.
	 * @return The cosine.
	 */
	FORCEINLINE FDeterministicNumber64 CosineAngle2D(FDeterministicVector64 B) const;

	/**
	 * Gets a copy of this vector projected onto the input vector.
	 *
	 * @param A	Vector to project onto, does not assume it is normalized.
	 * @return Projected vector.
	 */
	FORCEINLINE FDeterministicVector64 ProjectOnTo(const FDeterministicVector64& A) const;

	/**
	 * Gets a copy of this vector projected onto the input vector, which is assumed to be unit length.
	 *
	 * @param  Normal Vector to project onto (assumed to be unit length).
	 * @return Projected vector.
	 */
	FORCEINLINE FDeterministicVector64 ProjectOnToNormal(const FDeterministicVector64& Normal) const;

	/**
	 * Return the TRotator orientation corresponding to the direction in which the vector points.
	 * Sets Yaw and Pitch to the proper numbers, and sets Roll to zero because the roll can'T be determined from a vector.
	 *
	 * @return TRotator from the Vector's direction, without any roll.
	 * @see ToOrientationQuat()
	 */
	FDeterministicRotator64 ToOrientationRotator() const;

	/**
	 * Return the Quaternion orientation corresponding to the direction in which the vector points.
	 * Similar to the UE::Math::TRotator<T> version, returns a result without roll such that it preserves the up vector.
	 *
	 * @note If you don'T care about preserving the up vector and just want the most direct rotation, you can use the faster
	 * 'FQuat::FindBetweenVectors(FVector::ForwardVector, YourVector)' or 'FQuat::FindBetweenNormals(...)' if you know the vector is of unit length.
	 *
	 * @return Quaternion from the Vector's direction, without any roll.
	 * @see ToOrientationRotator(), FQuat::FindBetweenVectors()
	 */
	FDeterministicQuat64 ToOrientationQuat() const;

	/**
	 * Return the UE::Math::TRotator<T> orientation corresponding to the direction in which the vector points.
	 * Sets Yaw and Pitch to the proper numbers, and sets Roll to zero because the roll can't be determined from a vector.
	 * @note Identical to 'ToOrientationRotator()' and preserved for legacy reasons.
	 * @return UE::Math::TRotator<T> from the Vector's direction.
	 * @see ToOrientationRotator(), ToOrientationQuat()
	 */
	FORCEINLINE FDeterministicRotator64 Rotation() const;

	/**
	 * Find good arbitrary axis vectors to represent U and V axes of a plane,
	 * using this vector as the normal of the plane.
	 *
	 * @param Axis1 Reference to first axis.
	 * @param Axis2 Reference to second axis.
	 */
	void FindBestAxisVectors(FDeterministicVector64& Axis1, FDeterministicVector64& Axis2) const;

	/** When this vector contains Euler angles (degrees), ensure that angles are between +/-180 */
	void UnwindEuler();

	/**
	 * Utility to check if there are any non-finite values (NaN or Inf) in this vector.
	 *
	 * @return true if there are any non-finite values in this vector, false otherwise.
	 */
	FORCEINLINE bool ContainsNaN() const;

	/**
	 * Get a textual representation of this vector.
	 *
	 * @return A string describing the vector.
	 */
	FORCEINLINE FString ToString() const;

	/**
	* Get a locale aware textual representation of this vector.
	*
	* @return A string describing the vector.
	*/
	FORCEINLINE FText ToText() const;

	/** Get a short textural representation of this vector, for compact readable logging. */
	FORCEINLINE FString ToCompactString() const;

	/** Get a short locale aware textural representation of this vector, for compact readable logging. */
	FORCEINLINE FText ToCompactText() const;

	/**
	 * Initialize this Vector based on an FString. The String is expected to contain X=, Y=, Z=.
	 * The TVector<T> will be bogus when InitFromString returns false.
	 *
	 * @param	InSourceString	FString containing the vector values.
	 * @return true if the X,Y,Z values were read successfully; false otherwise.
	 */
	FORCEINLINE bool InitFromString(const FString& InSourceString);

	/**
	 * Initialize this Vector based on an FString. The String is expected to contain V(0)
	 * or at least one value X=, Y=, Z=, previously produced by ToCompactString()
	 * The TVector<T> will be bogus when InitFromString returns false.
	 *
	 * @param	InSourceString	FString containing the vector values.
	 * @return true if any of the X,Y,Z values were read successfully; false otherwise.
	 */
	FORCEINLINE bool InitFromCompactString(const FString& InSourceString);

	/**
	 * Converts a Cartesian unit vector into spherical coordinates on the unit sphere.
	 * @return Output Theta will be in the range [0, PI], and output Phi will be in the range [-PI, PI].
	 */
	FDeterministicVector2D64 UnitCartesianToSpherical() const;

	/**
	 * Convert a direction vector into a 'heading' angle.
	 *
	 * @return 'Heading' angle between +/-PI. 0 is pointing down +X.
	 */
	FDeterministicNumber64 HeadingAngle() const;

	/**
	 * Create an orthonormal basis from a basis with at least two orthogonal vectors.
	 * It may change the directions of the X and Y axes to make the basis orthogonal,
	 * but it won'T change the direction of the Z axis.
	 * All axes will be normalized.
	 *
	 * @param XAxis The input basis' XAxis, and upon return the orthonormal basis' XAxis.
	 * @param YAxis The input basis' YAxis, and upon return the orthonormal basis' YAxis.
	 * @param ZAxis The input basis' ZAxis, and upon return the orthonormal basis' ZAxis.
	 */
	static void CreateOrthonormalBasis(FDeterministicVector64& XAxis, FDeterministicVector64& YAxis, FDeterministicVector64& ZAxis);

	/**
	 * Compare two points and see if they're the same, using a threshold.
	 *
	 * @param P First vector.
	 * @param Q Second vector.
	 * @return Whether points are the same within a threshold. Uses fast distance approximation (linear per-component distance).
	 */
	FORCEINLINE static bool PointsAreSame(const FDeterministicVector64& P, const FDeterministicVector64& Q);

	/**
	 * Compare two points and see if they're within specified distance.
	 *
	 * @param Point1 First vector.
	 * @param Point2 Second vector.
	 * @param Dist Specified distance.
	 * @return Whether two points are within the specified distance. Uses fast distance approximation (linear per-component distance).
	 */
	static bool PointsAreNear(const FDeterministicVector64& Point1, const FDeterministicVector64& Point2, FDeterministicNumber64 Dist);

	/**
	 * Calculate the signed distance (in the direction of the normal) between a point and a plane.
	 *
	 * @param Point The Point we are checking.
	 * @param PlaneBase The Base Point in the plane.
	 * @param PlaneNormal The Normal of the plane (assumed to be unit length).
	 * @return Signed distance between point and plane.
	 */
	FORCEINLINE static FDeterministicNumber64 PointPlaneDist(const FDeterministicVector64& Point, const FDeterministicVector64& PlaneBase, const FDeterministicVector64& PlaneNormal);

	/**
	 * Compute pushout of a box from a plane.
	 *
	 * @param Normal The plane normal.
	 * @param Size The size of the box.
	 * @return Pushout required.
	 */
	static FORCEINLINE FDeterministicNumber64 BoxPushOut(const FDeterministicVector64& Normal, const FDeterministicVector64& Size);

	/**
	 * Min, Max, Min3, Max3 like FMath
	 */
	static FORCEINLINE FDeterministicVector64 Min(const FDeterministicVector64& A, const FDeterministicVector64& B);

	static FORCEINLINE FDeterministicVector64 Max(const FDeterministicVector64& A, const FDeterministicVector64& B);

	static FORCEINLINE FDeterministicVector64 Min3(const FDeterministicVector64& A, const FDeterministicVector64& B, const FDeterministicVector64& C);

	static FORCEINLINE FDeterministicVector64 Max3(const FDeterministicVector64& A, const FDeterministicVector64& B, const FDeterministicVector64& C);

	/**
	 * See if two normal vectors are nearly parallel, meaning the angle between them is close to 0 degrees.
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal1 Second normalized vector.
	 * @param  ParallelCosineThreshold Normals are parallel if absolute value of dot product (cosine of angle between them) is greater than or equal to this. For example: cos(1.0 degrees).
	 * @return true if vectors are nearly parallel, false otherwise.
	 */
	FORCEINLINE static bool Parallel(const FDeterministicVector64& Normal1, const FDeterministicVector64& Normal2, FDeterministicNumber64 ParallelCosineThreshold = DeterministicFloat::Constants::Number64::ThreshNormalsAreParallel);

	/**
	 * See if two normal vectors are coincident (nearly parallel and point in the same direction).
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal2 Second normalized vector.
	 * @param  ParallelCosineThreshold Normals are coincident if dot product (cosine of angle between them) is greater than or equal to this. For example: cos(1.0 degrees).
	 * @return true if vectors are coincident (nearly parallel and point in the same direction), false otherwise.
	 */
	FORCEINLINE static bool Coincident(const FDeterministicVector64& Normal1, const FDeterministicVector64& Normal2, FDeterministicNumber64 ParallelCosineThreshold = DeterministicFloat::Constants::Number64::ThreshNormalsAreParallel);

	/**
	 * See if two normal vectors are nearly orthogonal (perpendicular), meaning the angle between them is close to 90 degrees.
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal2 Second normalized vector.
	 * @param  OrthogonalCosineThreshold Normals are orthogonal if absolute value of dot product (cosine of angle between them) is less than or equal to this. For example: cos(89.0 degrees).
	 * @return true if vectors are orthogonal (perpendicular), false otherwise.
	 */
	FORCEINLINE static bool Orthogonal(const FDeterministicVector64& Normal1, const FDeterministicVector64& Normal2, FDeterministicNumber64 OrthogonalCosineThreshold = DeterministicFloat::Constants::Number64::ThreshNormalsAreOrthogonal);

	/**
	 * See if two planes are coplanar. They are coplanar if the normals are nearly parallel and the planes include the same set of points.
	 *
	 * @param Base1 The base point in the first plane.
	 * @param Normal1 The normal of the first plane.
	 * @param Base2 The base point in the second plane.
	 * @param Normal2 The normal of the second plane.
	 * @param ParallelCosineThreshold Normals are parallel if absolute value of dot product is greater than or equal to this.
	 * @return true if the planes are coplanar, false otherwise.
	 */
	static bool Coplanar(const FDeterministicVector64& Base1, const FDeterministicVector64& Normal1, const FDeterministicVector64& Base2, const FDeterministicVector64& Normal2, FDeterministicNumber64 ParallelCosineThreshold = DeterministicFloat::Constants::Number64::ThreshNormalsAreParallel);

	/**
	 * Generates a list of sample points on a Bezier curve defined by 2 points.
	 *
	 * @param ControlPoints	Array of 4 FVectors (vert1, controlpoint1, controlpoint2, vert2).
	 * @param NumPoints Number of samples.
	 * @param OutPoints Receives the output samples.
	 * @return The path length.
	 */
	FORCEINLINE static FDeterministicNumber64 EvaluateBezier(const FDeterministicVector64* ControlPoints, int32 NumPoints, TArray<FDeterministicVector64>& OutPoints);

	/**
	 * Converts a vector containing radian values to a vector containing degree values.
	 *
	 * @param RadVector	Vector containing radian values
	 * @return Vector  containing degree values
	 */
	FORCEINLINE static FDeterministicVector64 RadiansToDegrees(const FDeterministicVector64& RadVector);

	/**
	 * Converts a vector containing degree values to a vector containing radian values.
	 *
	 * @param DegVector	Vector containing degree values
	 * @return Vector containing radian values
	 */
	FORCEINLINE static FDeterministicVector64 DegreesToRadians(const FDeterministicVector64& DegVector);

	/**
	 * Given a current set of cluster centers, a set of points, iterate N times to move clusters to be central.
	 *
	 * @param Clusters Reference to array of Clusters.
	 * @param Points Set of points.
	 * @param NumIterations Number of iterations.
	 * @param NumConnectionsToBeValid Sometimes you will have long strings that come off the mass of points
	 * which happen to have been chosen as Cluster starting points.  You want to be able to disregard those.
	 */
	FORCEINLINE static void GenerateClusterCenters(TArray<FDeterministicVector64>& Clusters, const TArray<FDeterministicVector64>& Points, int32 NumIterations, int32 NumConnectionsToBeValid);

	FORCEINLINE operator FVector() const
	{
		return FVector((double)X,(double)Y,(double)Z);
	}
};

FORCEINLINE FDeterministicVector64 operator*(FDeterministicNumber64 Scale, const FDeterministicVector64& V)
{
	return V.operator*(Scale);
}

template<>
struct TCustomLerp<FDeterministicVector64>
{
	enum { Value = true };

	static FORCEINLINE_DEBUGGABLE FDeterministicVector64 Lerp(const FDeterministicVector64& A, const FDeterministicVector64& B, const FDeterministicNumber64& Alpha)
	{
		return A + Alpha * (B - A);
	}
};
