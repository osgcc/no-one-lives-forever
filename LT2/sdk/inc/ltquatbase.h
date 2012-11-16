//
//	Quaternion identities
//
//	Q = [ X Y Z W ]
//
//
//        |       2     2                                |
//        | 1 - 2Y  - 2Z    2XY - 2ZW      2XZ + 2YW     |
//        |                                              |
//        |                       2     2                |
//    M = | 2XY + 2ZW       1 - 2X  - 2Z   2YZ - 2XW     |
//        |                                              |
//        |                                      2     2 |
//        | 2XZ - 2YW       2YZ + 2XW      1 - 2X  - 2Y  |
//        |                                              |
//
//	X^2 + Y^2 + Z^2 + W^2 = 1
//
//	Trace = sum of matrix diagonal
//		  = 4 - 4( X^2 + Y^2 + Z^2 )
//		  = 4 - 4( 1 - W^2 )
//		  = 4W^2
//	
//	X = ( M(1,2) - M(2,1)) / 4W
//  Y = ( M(0,2) - M(0,2)) / 4W
//	Z = ( M(0,1) - M(1,0)) / 4W
//
// Implements base quaternion routines without a class.

#ifndef __LTQUATBASE_H__
#define __LTQUATBASE_H__


	// ------------------------------------------------------------------------ //
	// Definitions.
	// ------------------------------------------------------------------------ //

	#include <math.h>


	#define HALFPI				1.570796326794895
	#define QUAT_TOLERANCE		0.00001f
	#define QUAT_HIGH_TOLERANCE	(1.0f - QUAT_TOLERANCE)
	#define QUAT_LOW_TOLERANCE	(-QUAT_HIGH_TOLERANCE)

	#define QX	0
	#define QY	1
	#define QZ  2
	#define QW  3


	// ------------------------------------------------------------------------ //
	// Functions.
	// ------------------------------------------------------------------------ //

	// Convert a quaternion to a matrix.
	void quat_ConvertToMatrix(const float *pQuat, float mat[4][4]);

	
	// Gets orientation vectors for the quaternion.
	void quat_GetVectors(const float *pQuat, float *pRight, float *pUp, float *pForward);


	// Get a quaternion from a matrix.
	void quat_ConvertFromMatrix(float *pQuat, const float mat[4][4]);

	
	// Linear interpolate between two quaternions.
	void quat_Slerp(float *pDest, const float *pQ1, const float *pQ2, float t);



	// ------------------------------------------------------------------------ //
	// Inlines.
	// ------------------------------------------------------------------------ //

	inline void quat_Identity(float *pQuat)
	{
		pQuat[0] = pQuat[1] = pQuat[2] = 0.0f;
		pQuat[3] = 1.0f;
	}


	inline void quat_Set(float *pQuat, float x, float y, float z, float w)
	{
		pQuat[0] = x;
		pQuat[1] = y;
		pQuat[2] = z;
		pQuat[3] = w;
	}


	// Multiply two quaternions. Note: this is exactly the same as converting both
	// quaternions to matrices, multiplying the matrices (in the same order, a*b),
	// then converting back to a quaternion (except it's MUCH faster and more accurate).
	inline void quat_Mul(float *out, const float *a, const float *b)
	{
		// Note: this can be simplified when the quaternions are written 
		// as a scalar and vector:
		// s1 = a[QW]
		// v1 = (a[QX], a[QY], a[QZ])
		// s2 = b[QW]
		// v2 = (b[QX], b[QY], b[QZ])
		// a = [s1,v1]
		// b = [s2,v2]
		// The quaternion product is then [s1*s2 - v1*v2, s1*v2 + s2*v1 + v1.Cross(v2)]

		out[QX] = a[QW]*b[QX] + a[QX]*b[QW] + a[QY]*b[QZ] - a[QZ]*b[QY];
		out[QY] = a[QW]*b[QY] - a[QX]*b[QZ] + a[QY]*b[QW] + a[QZ]*b[QX];
		out[QZ] = a[QW]*b[QZ] + a[QX]*b[QY] - a[QY]*b[QX] + a[QZ]*b[QW];
		out[QW] = a[QW]*b[QW] - a[QX]*b[QX] - a[QY]*b[QY] - a[QZ]*b[QZ];
	}


	// Gives the conjugate quaternion (which will produce the inverse, or transposed matrix).
	inline void quat_Conjugate(float *pOut, const float *pQuat)
	{
		pOut[QX] = -pQuat[QX];
		pOut[QY] = -pQuat[QY];
		pOut[QZ] = -pQuat[QZ];
		pOut[QW] = pQuat[QW];
	}


#endif  // __LTQUATBASE_H__