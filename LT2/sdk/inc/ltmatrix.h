
// Defines all the matrix operations.

#ifndef __LTMATRIX_H__
#define __LTMATRIX_H__


	#include <math.h>
	#include "ltplane.h"
	

	/*
	
	Matrices are indexed by (y,x), so a translation matrix looks like:
	1 0 0 tx  (tx is in m[0][3])
	0 1 0 ty  (ty is in m[1][3])
	0 0 1 tz  (tz is in m[2][3])
	0 0 0 1

	Useful theorems (~ = matrix inverse):
	~(A*B) = ~B * ~A
	
	*/


	#define PN	thePlane.m_Normal
	#define PD	thePlane.m_Dist


	class LTMatrix
	{
	public:

		// Initialize the values.
		void	Init(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);			

		void	Identity();

		// Removes scale from the matrix.
		void	Normalize();

		// Scale the basis vectors by the specified amount.
		void	Scale(float x, float y, float z);


		// Computes the general inverse.  Use InverseTransform if possible because 
		// it's faster and less prone to numerical accuracy errors.
		LTBOOL		Inverse(); // Returns FALSE if there is no inverse.
		LTMatrix	MakeInverse();

		// Get/set translation.
		void	GetTranslation(LTVector &vec);
		void	SetTranslation(LTVector vec);
		void	SetTranslation(float x, float y, float z);

		// Get the scale of the matrix's basis vectors.
		LTVector	GetScale();

		// Get the basis vectors.
		void	GetBasisVectors(LTVector *pRight, LTVector *pUp, LTVector *pForward);

		// Sets the basis vectors and clears translation.
		void	SetBasisVectors(LTVector *pRight, LTVector *pUp, LTVector *pForward);

		// Sets the basis vectors without clearing translation.
		void	SetBasisVectors2(LTVector *pRight, LTVector *pUp, LTVector *pForward);

		// Transform the plane (in case you hadn't guessed)..
		LTPlane	TransformPlane(LTPlane &thePlane);

		// For b/w compatibility.
		void	Apply(LTVector &theVec);
		void	Apply(const LTVector &in, LTVector &out);
		void	Apply3x3(LTVector &vec);
		void	Apply3x3(const LTVector &in, LTVector &out);
		void	Apply4x4(const LTVector &in, LTVector &out);
		void	Apply(LTMatrix &mTarget);

	
	// These set the matrix up as a certain type of matrix.
	public:

		void	SetupScalingMatrix(LTVector &scale);
		
		// Set it up to reflect along the specified plane.
		void	SetupReflectionMatrix(LTVector normal, LTVector refPt);

		// Setup as a projection matrix.  The matrix will project points from vOrigin
		// onto the specified plane.
		void	SetupProjectionMatrix(LTVector vOrigin, LTPlane thePlane);

		// Setup to rotation around the specified vector by the specified angle (in radians).
		void	SetupRot(LTVector vVec, float fRadians);


	// Helps to make pretty expressions (like mGlobal = mParent * mLocal * mSomethingElse).
	public:

		// Return an inverse transformation.  Assumes there is no scaling in the matrix.  
		// Call Normalize to ensure there is no scaling.
		LTMatrix	MakeInverseTransform();
		
		// Returns the inverse transform.
		// Note: this just calls MakeInverseTransform.
		LTMatrix	operator~();
		
		LTMatrix	operator*(LTMatrix &other);
		LTVector	operator*(LTVector other);
		inline float&	El(uint32 i, uint32 j) {return m[i][j];}

		
	public:

		float	m[4][4];
	};



	inline void Mat_Identity(LTMatrix *pMat)
	{
		pMat->Identity();
	}


	inline void Mat_GetTranslation(LTMatrix &mat, LTVector &vec)
	{
		mat.GetTranslation(vec);
	}


	inline void Mat_SetTranslation(LTMatrix &mat, LTVector &vec)
	{
		mat.SetTranslation(vec);
	}


	// Transpose the upper left 3x3.
	inline void MatTranspose3x3(LTMatrix *pMat)
	{
		float temp;
		float *d = (float*)pMat->m;

		temp = d[1]; d[1] = d[4]; d[4] = temp;
		temp = d[2]; d[2] = d[8]; d[8] = temp;
		temp = d[9]; d[9] = d[6]; d[6] = temp;
	}

	// Transpose the whole matrix.
	inline void MatTranspose(LTMatrix *pMat)
	{
		float temp;
		float *d = (float*)pMat->m;

		temp = d[1]; d[1] = d[4]; d[4] = temp;
		temp = d[2]; d[2] = d[8]; d[8] = temp;
		temp = d[9]; d[9] = d[6]; d[6] = temp;

		temp = d[3];  d[3] =  d[12]; d[12] = temp;
		temp = d[7];  d[7] =  d[13]; d[13] = temp;
		temp = d[11]; d[11] = d[14]; d[14] = temp;
	}


	// Mat3 = Mat1 * Mat2
	#define M1 pMat1->m
	#define M2 pMat2->m

	inline void MatMul(LTMatrix *pDest, LTMatrix *pMat1, LTMatrix *pMat2)
	{
		pDest->m[0][0] = M1[0][0]*M2[0][0] + M1[0][1]*M2[1][0] + M1[0][2]*M2[2][0] + M1[0][3]*M2[3][0];
		pDest->m[1][0] = M1[1][0]*M2[0][0] + M1[1][1]*M2[1][0] + M1[1][2]*M2[2][0] + M1[1][3]*M2[3][0];
		pDest->m[2][0] = M1[2][0]*M2[0][0] + M1[2][1]*M2[1][0] + M1[2][2]*M2[2][0] + M1[2][3]*M2[3][0];
		pDest->m[3][0] = M1[3][0]*M2[0][0] + M1[3][1]*M2[1][0] + M1[3][2]*M2[2][0] + M1[3][3]*M2[3][0];

		pDest->m[0][1] = M1[0][0]*M2[0][1] + M1[0][1]*M2[1][1] + M1[0][2]*M2[2][1] + M1[0][3]*M2[3][1];
		pDest->m[1][1] = M1[1][0]*M2[0][1] + M1[1][1]*M2[1][1] + M1[1][2]*M2[2][1] + M1[1][3]*M2[3][1];
		pDest->m[2][1] = M1[2][0]*M2[0][1] + M1[2][1]*M2[1][1] + M1[2][2]*M2[2][1] + M1[2][3]*M2[3][1];
		pDest->m[3][1] = M1[3][0]*M2[0][1] + M1[3][1]*M2[1][1] + M1[3][2]*M2[2][1] + M1[3][3]*M2[3][1];

		pDest->m[0][2] = M1[0][0]*M2[0][2] + M1[0][1]*M2[1][2] + M1[0][2]*M2[2][2] + M1[0][3]*M2[3][2];
		pDest->m[1][2] = M1[1][0]*M2[0][2] + M1[1][1]*M2[1][2] + M1[1][2]*M2[2][2] + M1[1][3]*M2[3][2];
		pDest->m[2][2] = M1[2][0]*M2[0][2] + M1[2][1]*M2[1][2] + M1[2][2]*M2[2][2] + M1[2][3]*M2[3][2];
		pDest->m[3][2] = M1[3][0]*M2[0][2] + M1[3][1]*M2[1][2] + M1[3][2]*M2[2][2] + M1[3][3]*M2[3][2];

		pDest->m[0][3] = M1[0][0]*M2[0][3] + M1[0][1]*M2[1][3] + M1[0][2]*M2[2][3] + M1[0][3]*M2[3][3];
		pDest->m[1][3] = M1[1][0]*M2[0][3] + M1[1][1]*M2[1][3] + M1[1][2]*M2[2][3] + M1[1][3]*M2[3][3];
		pDest->m[2][3] = M1[2][0]*M2[0][3] + M1[2][1]*M2[1][3] + M1[2][2]*M2[2][3] + M1[2][3]*M2[3][3];
		pDest->m[3][3] = M1[3][0]*M2[0][3] + M1[3][1]*M2[1][3] + M1[3][2]*M2[2][3] + M1[3][3]*M2[3][3];
	}


	// Mat2 = Mat1 * Mat2
	inline void MatMul_InPlace(LTMatrix *pMat1, LTMatrix *pMat2)
	{
		LTMatrix temp;
		MatMul(&temp, pMat1, pMat2);
		*pMat2 = temp;
	}


	// Non-homogenous matrix multiply.
	inline void MatVMul(LTVector *pDest, LTMatrix *pMat, LTVector *pSrc)
	{
		pDest->x = pMat->m[0][0]*pSrc->x + pMat->m[0][1]*pSrc->y + pMat->m[0][2]*pSrc->z + pMat->m[0][3];
		pDest->y = pMat->m[1][0]*pSrc->x + pMat->m[1][1]*pSrc->y + pMat->m[1][2]*pSrc->z + pMat->m[1][3];
		pDest->z = pMat->m[2][0]*pSrc->x + pMat->m[2][1]*pSrc->y + pMat->m[2][2]*pSrc->z + pMat->m[2][3];
	}

	inline void MatVMul_InPlace(LTMatrix *pMat, LTVector *pSrc)
	{
		LTVector temp;
		MatVMul(&temp, pMat, pSrc);
		*pSrc = temp;
	}


	// Matrix multiply with the homogenous divide.
	inline float MatVMul_H(LTVector *pDest, LTMatrix *pMat, LTVector *pSrc)
	{
		float one_over_w = 1.0f / (pMat->m[3][0]*pSrc->x + pMat->m[3][1]*pSrc->y + pMat->m[3][2]*pSrc->z + pMat->m[3][3]);

		pDest->x = one_over_w * (pMat->m[0][0]*pSrc->x + pMat->m[0][1]*pSrc->y + pMat->m[0][2]*pSrc->z + pMat->m[0][3]);
		pDest->y = one_over_w * (pMat->m[1][0]*pSrc->x + pMat->m[1][1]*pSrc->y + pMat->m[1][2]*pSrc->z + pMat->m[1][3]);
		pDest->z = one_over_w * (pMat->m[2][0]*pSrc->x + pMat->m[2][1]*pSrc->y + pMat->m[2][2]*pSrc->z + pMat->m[2][3]);
	
		return one_over_w;
	}

	inline float MatVMul_InPlace_H(LTMatrix *pMat, LTVector *pSrc)
	{
		float one_over_w = 1.0f / (pMat->m[3][0]*pSrc->x + pMat->m[3][1]*pSrc->y + pMat->m[3][2]*pSrc->z + pMat->m[3][3]);
		LTVector temp;

		temp.x = one_over_w * (pMat->m[0][0]*pSrc->x + pMat->m[0][1]*pSrc->y + pMat->m[0][2]*pSrc->z + pMat->m[0][3]);
		temp.y = one_over_w * (pMat->m[1][0]*pSrc->x + pMat->m[1][1]*pSrc->y + pMat->m[1][2]*pSrc->z + pMat->m[1][3]);
		temp.z = one_over_w * (pMat->m[2][0]*pSrc->x + pMat->m[2][1]*pSrc->y + pMat->m[2][2]*pSrc->z + pMat->m[2][3]);
	
		*pSrc = temp;
		return one_over_w;
	}


	// Does a full 'normal' 4x4 matrix multiply without dividing by w.
	inline void MatVMul_Add(float *pOut, LTMatrix *pMat, float *pVec)
	{
		pOut[0] += pMat->m[0][0]*pVec[0] + pMat->m[0][1]*pVec[1] + pMat->m[0][2]*pVec[2] + pMat->m[0][3]*pVec[3];
		pOut[1] += pMat->m[1][0]*pVec[0] + pMat->m[1][1]*pVec[1] + pMat->m[1][2]*pVec[2] + pMat->m[1][3]*pVec[3];
		pOut[2] += pMat->m[2][0]*pVec[0] + pMat->m[2][1]*pVec[1] + pMat->m[2][2]*pVec[2] + pMat->m[2][3]*pVec[3];
		pOut[3] += pMat->m[3][0]*pVec[0] + pMat->m[3][1]*pVec[1] + pMat->m[3][2]*pVec[2] + pMat->m[3][3]*pVec[3];
	}
	
	// Does a full 'normal' 3x4 matrix multiply without dividing by w.
	inline void MatVMul_Add_3x3(float *pOut, LTMatrix *pMat, float *pVec)
	{
		pOut[0] += pMat->m[0][0]*pVec[0] + pMat->m[0][1]*pVec[1] + pMat->m[0][2]*pVec[2];
		pOut[1] += pMat->m[1][0]*pVec[0] + pMat->m[1][1]*pVec[1] + pMat->m[1][2]*pVec[2];
		pOut[2] += pMat->m[2][0]*pVec[0] + pMat->m[2][1]*pVec[1] + pMat->m[2][2]*pVec[2];
		pOut[3] += pMat->m[3][0]*pVec[0] + pMat->m[3][1]*pVec[1] + pMat->m[3][2]*pVec[2] + pMat->m[3][3]*pVec[3];
	}
	

	// Matrix multiply using upper left 3x3.
	inline void MatVMul_3x3(LTVector *pDest, LTMatrix *pMat, LTVector *pSrc)
	{
		pDest->x = pMat->m[0][0]*pSrc->x + pMat->m[0][1]*pSrc->y + pMat->m[0][2]*pSrc->z;
		pDest->y = pMat->m[1][0]*pSrc->x + pMat->m[1][1]*pSrc->y + pMat->m[1][2]*pSrc->z;
		pDest->z = pMat->m[2][0]*pSrc->x + pMat->m[2][1]*pSrc->y + pMat->m[2][2]*pSrc->z;
	}

	inline void MatVMul_InPlace_3x3(LTMatrix *pMat, LTVector *pSrc)
	{
		LTVector temp;
		MatVMul_3x3(&temp, pMat, pSrc);
		*pSrc = temp;
	}

	
	// Transposed matrix multiply (using upper left 3x3).
	inline void MatVMul_Transposed3x3(LTVector *pDest, LTMatrix *pMat, LTVector *pSrc)
	{
		pDest->x = pMat->m[0][0]*pSrc->x + pMat->m[1][0]*pSrc->y + pMat->m[2][0]*pSrc->z;
		pDest->y = pMat->m[0][1]*pSrc->x + pMat->m[1][1]*pSrc->y + pMat->m[2][1]*pSrc->z;
		pDest->z = pMat->m[0][2]*pSrc->x + pMat->m[1][2]*pSrc->y + pMat->m[2][2]*pSrc->z;
	}

	inline void MatVMul_InPlace_Transposed3x3(LTMatrix *pMat, LTVector *pSrc)
	{
		LTVector temp;

		temp.x = pMat->m[0][0]*pSrc->x + pMat->m[1][0]*pSrc->y + pMat->m[2][0]*pSrc->z;
		temp.y = pMat->m[0][1]*pSrc->x + pMat->m[1][1]*pSrc->y + pMat->m[2][1]*pSrc->z;
		temp.z = pMat->m[0][2]*pSrc->x + pMat->m[1][2]*pSrc->y + pMat->m[2][2]*pSrc->z;
	
		*pSrc = temp;
	}


	// Takes a transformation matrix and returns the inverse.
	// The transformation matrix can only have rotation and translation, NO SCALING.
	inline void Mat_InverseTransformation(LTMatrix *pSrc, LTMatrix *pDest)
	{
		LTVector trans, newTrans;

		trans.x = pSrc->m[0][3];
		trans.y = pSrc->m[1][3];
		trans.z = pSrc->m[2][3];

		// Transpose the upper 3x3.
		pDest->m[0][0] = pSrc->m[0][0];  pDest->m[0][1] = pSrc->m[1][0]; pDest->m[0][2] = pSrc->m[2][0];
		pDest->m[1][0] = pSrc->m[0][1];  pDest->m[1][1] = pSrc->m[1][1]; pDest->m[1][2] = pSrc->m[2][1];
		pDest->m[2][0] = pSrc->m[0][2];  pDest->m[2][1] = pSrc->m[1][2]; pDest->m[2][2] = pSrc->m[2][2];

		MatVMul_3x3(&newTrans, pDest, &trans);
		pDest->m[0][3] = -newTrans.x;
		pDest->m[1][3] = -newTrans.y;
		pDest->m[2][3] = -newTrans.z;

		// Fill in the bottom row.
		pDest->m[3][0] = pDest->m[3][1] = pDest->m[3][2] = 0.0f;
		pDest->m[3][3] = 1.0f;
	}


	// Set the matrix up to rotate 'amount' radians around the given axis.
	inline void Mat_SetupRot(LTMatrix *pMat, LTVector *pVec, float amount)
	{
		float s, c, t;
		float tx, ty, tz;
		float sx, sy, sz;
		
		s = (float)sin(amount);
		c = (float)cos(amount);
		t = 1.0f - c;

		tx = t * pVec->x;	ty = t * pVec->y;	tz = t * pVec->z;
		sx = s * pVec->x;	sy = s * pVec->y;	sz = s * pVec->z;

		pMat->m[0][0] = tx*pVec->x + c;
		pMat->m[1][0]  = tx*pVec->y + sz;
		pMat->m[2][0] = tx*pVec->z - sy;

		pMat->m[0][1] = tx*pVec->y - sz;
		pMat->m[1][1] = ty*pVec->y + c;
		pMat->m[2][1] = ty*pVec->z + sx;

		pMat->m[0][2] = tx*pVec->z + sy;
		pMat->m[1][2] = ty*pVec->z - sx;
		pMat->m[2][2] = tz*pVec->z + c;

		// Make the unfulled parts identity.
		pMat->m[3][0] = 0.0f; 	pMat->m[3][1] = 0.0f;	pMat->m[3][2] = 0.0f;
		pMat->m[0][3] = 0.0f;	pMat->m[1][3] = 0.0f;	pMat->m[2][3] = 0.0f;
		pMat->m[3][3] = 1.0f;	
	}



	inline void LTMatrix::Init(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		m[0][0] = m00;  m[0][1] = m01;  m[0][2] = m02;  m[0][3] = m03;
		m[1][0] = m10;  m[1][1] = m11;  m[1][2] = m12;  m[1][3] = m13;
		m[2][0] = m20;  m[2][1] = m21;  m[2][2] = m22;  m[2][3] = m23;
		m[3][0] = m30;  m[3][1] = m31;  m[3][2] = m32;  m[3][3] = m33;
	}


	inline void LTMatrix::Identity()
	{
		Init( 
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}


	inline void LTMatrix::Normalize()
	{
		LTVector right, up, forward;
		float len;


		GetBasisVectors(&right, &up, &forward);
		
		len = VEC_MAG(right);
		VEC_DIVSCALAR(right, right, len);
		
		len = VEC_MAG(up);
		VEC_DIVSCALAR(up, up, len);
		
		VEC_CROSS( forward, up, right );
		SetBasisVectors2(&right, &up, &forward);
	}


	inline LTBOOL LTMatrix::Inverse()
	{
		int iRow, i, j, iTemp, iTest;
		float mul, fTest, fLargest;
		float mat[4][8];
		int rowMap[4], iLargest;
		float *pIn, *pOut, *pRow, *pScaleRow;


		// How it's done.
		// AX = I
		// A = this
		// X = the matrix we're looking for
		// I = identity

		// Setup AI
		for(i=0; i < 4; i++)
		{
			pIn = m[i];
			pOut = mat[i];

			for(j=0; j < 4; j++)
			{
				pOut[j] = pIn[j];
			}

			pOut[4] = 0.0f;
			pOut[5] = 0.0f;
			pOut[6] = 0.0f;
			pOut[7] = 0.0f;
			pOut[i+4] = 1.0f;

			rowMap[i] = i;
		}

		// Use row operations to get to reduced row-echelon form using these rules:
		// 1. Multiply or divide a row by a nonzero number.
		// 2. Add a multiple of one row to another.
		// 3. Interchange two rows.

		for(iRow=0; iRow < 4; iRow++)
		{
			// Find the row with the largest element in this column.
			fLargest = 0.001f;
			iLargest = -1;
			for(iTest=iRow; iTest < 4; iTest++)
			{
				fTest = (float)fabs(mat[rowMap[iTest]][iRow]);
				if(fTest > fLargest)
				{
					iLargest = iTest;
					fLargest = fTest;
				}
			}

			// They're all too small.. sorry.
			if(iLargest == -1)
			{
				return LTFALSE;
			}

			// Swap the rows.
			iTemp = rowMap[iLargest];
			rowMap[iLargest] = rowMap[iRow];
			rowMap[iRow] = iTemp;

			pRow = mat[rowMap[iRow]];

			// Divide this row by the element.
			mul = 1.0f / pRow[iRow];
			for(j=0; j < 8; j++)
				pRow[j] *= mul;

			pRow[iRow] = 1.0f; // Preserve accuracy...
			
			// Eliminate this element from the other rows using operation 2.
			for(i=0; i < 4; i++)
			{
				if(i == iRow)
					continue;

				pScaleRow = mat[rowMap[i]];
			
				// Multiply this row by -(iRow*the element).
				mul = -pScaleRow[iRow];
				for(j=0; j < 8; j++)
				{
					pScaleRow[j] += pRow[j] * mul;
				}

				pScaleRow[iRow] = 0.0f; // Preserve accuracy...
			}
		}

		// The inverse is on the right side of AX now (the identity is on the left).
		for(i=0; i < 4; i++)
		{
			pIn = mat[rowMap[i]] + 4;
			pOut = m[i];

			for(j=0; j < 4; j++)
			{
				pOut[j] = pIn[j];
			}
		}

		return LTTRUE;
	}


	inline LTMatrix LTMatrix::MakeInverse()
	{
		LTMatrix ret;

		ret = *this;
		ret.Inverse();
		return ret;
	}


	inline void LTMatrix::Scale(float x, float y, float z)
	{
		m[0][0] *= x;
		m[1][0] *= x;
		m[2][0] *= x;

		m[0][1] *= y;
		m[1][1] *= y;
		m[2][1] *= y;

		m[0][2] *= z;
		m[1][2] *= z;
		m[2][2] *= z;
	}


	inline void	LTMatrix::SetupScalingMatrix(LTVector &scale)
	{
		Init(
			scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}


	inline void LTMatrix::SetupReflectionMatrix(LTVector N, LTVector vOrigin)
	{
		LTMatrix mReflect, mBack, mForward;

		/*
			How it works:
				N = normal
				V = vector
				R = reflected vector
			
				R = V - N(2NV)
			so...

				R.x = V.x - 2*N.x*N.x*V.x - 2*N.x*N.y*V.y - 2*N.x*N.z*V.z
			or...
				R.x = V.x + (-2*N.x*N.x)*V.x + (-2*N.x*N.y)*V.y + (-2*N.x*N.z)*V.z
			and to get rid of the extra V.x on the left, add 1 to the multiplier like this:
				R.x = ((-2*N.x*N.x) + 1)*V.x + (-2*N.x*N.y)*V.y + (-2*N.x*N.z)*V.z

			Then just put those coefficients in the matrix.
		*/

		mReflect.Init( 
			-2.0f*N.x*N.x + 1.0f,	-2.0f*N.x*N.y,			-2.0f*N.x*N.z,			0.0f,
			-2.0f*N.y*N.x,			-2.0f*N.y*N.y + 1.0f,	-2.0f*N.y*N.z,			0.0f,
			-2.0f*N.z*N.x,			-2.0f*N.z*N.y,			-2.0f*N.z*N.z + 1.0f,	0.0f,
			0.0f,					0.0f,					0.0f,					1.0f);

		mBack.Identity();
		mBack.SetTranslation(-vOrigin);

		mForward.Identity();
		mForward.SetTranslation(vOrigin);

		// (multiplied in reverse order, so it translates to the origin point,
		// reflects, and translates back).
		*this = mForward * mReflect * mBack;
	}


	inline void LTMatrix::SetupProjectionMatrix(LTVector vOrigin, LTPlane thePlane)
	{
		float dot;


		// Find dot product between light position RVector and ground plane normal.
		dot = PN[0]*vOrigin.x + PN[1]*vOrigin.y + PN[2]*vOrigin.z - PD;

		m[0][0] = dot - vOrigin.x * PN[0];
		m[0][1] = -vOrigin.x * PN[1];
		m[0][2] = -vOrigin.x * PN[2];
		m[0][3] = -vOrigin.x * -PD;

		m[1][0] = -vOrigin.y * PN[0];
		m[1][1] = dot - vOrigin.y * PN[1];
		m[1][2] = -vOrigin.y * PN[2];
		m[1][3] = -vOrigin.y * -PD;

		m[2][0] = -vOrigin.z * PN[0];
		m[2][1] = -vOrigin.z * PN[1];
		m[2][2] = dot - vOrigin.z * PN[2];
		m[2][3] = -vOrigin.z * -PD;

		m[3][0] = -PN[0];
		m[3][1] = -PN[1];
		m[3][2] = -PN[2];
		m[3][3] = dot + PD;
	}


	inline void LTMatrix::SetupRot(LTVector vVec, float fRadians)
	{
		float s, c, t;
		float tx, ty, tz;
		float sx, sy, sz;
		
		
		s = (float)sin(fRadians);
		c = (float)cos(fRadians);
		t = 1.0f - c;

		tx = t * vVec.x;	ty = t * vVec.y;	tz = t * vVec.z;
		sx = s * vVec.x;	sy = s * vVec.y;	sz = s * vVec.z;

		m[0][0] = tx*vVec.x + c;
		m[1][0] = tx*vVec.y + sz;
		m[2][0] = tx*vVec.z - sy;

		m[0][1] = tx*vVec.y - sz;
		m[1][1] = ty*vVec.y + c;
		m[2][1] = ty*vVec.z + sx;

		m[0][2] = tx*vVec.z + sy;
		m[1][2] = ty*vVec.z - sx;
		m[2][2] = tz*vVec.z + c;

		// Make the unfilled parts identity.
		m[3][0] = 0.0f; 	m[3][1] = 0.0f;		m[3][2] = 0.0f;
		m[0][3] = 0.0f;		m[1][3] = 0.0f;		m[2][3] = 0.0f;
		m[3][3] = 1.0f;	
	}


	inline LTVector LTMatrix::GetScale()
	{
		return LTVector(
			(float)sqrt(m[0][0]*m[0][0] + m[1][0]*m[1][0] + m[2][0]*m[2][0]),
			(float)sqrt(m[0][1]*m[0][1] + m[1][1]*m[1][1] + m[2][1]*m[2][1]),
			(float)sqrt(m[0][2]*m[0][2] + m[1][2]*m[1][2] + m[2][2]*m[2][2])
			);
	}

	
	inline void LTMatrix::GetBasisVectors(LTVector *pRight, LTVector *pUp, LTVector *pForward)
	{
		pRight->x = m[0][0];
		pRight->y = m[1][0];
		pRight->z = m[2][0];

		pUp->x = m[0][1];
		pUp->y = m[1][1];
		pUp->z = m[2][1];

		pForward->x = m[0][2];
		pForward->y = m[1][2];
		pForward->z = m[2][2];
	}

	
	inline void LTMatrix::SetBasisVectors(LTVector *pRight, LTVector *pUp, LTVector *pForward)
	{
		Init(
			pRight->x, pUp->x, pForward->x, 0.0f, 
			pRight->y, pUp->y, pForward->y, 0.0f, 
			pRight->z, pUp->z, pForward->z, 0.0f, 
			0.0f, 0.0f, 0.0f, 1.0f);
	}


	inline void LTMatrix::SetBasisVectors2(LTVector *pRight, LTVector *pUp, LTVector *pForward)
	{
		m[0][0] = pRight->x;
		m[1][0] = pRight->y;
		m[2][0] = pRight->z;

		m[0][1] = pUp->x;
		m[1][1] = pUp->y;
		m[2][1] = pUp->z;
		
		m[0][2] = pForward->x;
		m[1][2] = pForward->y;
		m[2][2] = pForward->z;
	}

	inline LTPlane LTMatrix::TransformPlane(LTPlane &thePlane)
	{
		LTVector startPt;
		LTPlane ret;

		startPt = thePlane.m_Normal * thePlane.m_Dist;
		MatVMul_3x3(&ret.m_Normal, this, &thePlane.m_Normal);
		MatVMul_InPlace_H(this, &startPt);
		ret.m_Dist = ret.m_Normal.Dot(startPt);

		return ret;
	}

	inline void LTMatrix::Apply(LTVector &s)
	{
		float x, y, z;

		x = s.x*m[0][0] + s.y*m[0][1] + s.z*m[0][2] + m[0][3];
		y = s.x*m[1][0] + s.y*m[1][1] + s.z*m[1][2] + m[1][3];
		z = s.x*m[2][0] + s.y*m[2][1] + s.z*m[2][2] + m[2][3];
	
		s.x = x;
		s.y = y;
		s.z = z;
	}

	inline void LTMatrix::Apply(const LTVector &s, LTVector &d)
	{
		d.x = s.x*m[0][0] + s.y*m[0][1] + s.z*m[0][2] + m[0][3];
		d.y = s.x*m[1][0] + s.y*m[1][1] + s.z*m[1][2] + m[1][3];
		d.z = s.x*m[2][0] + s.y*m[2][1] + s.z*m[2][2] + m[2][3];
	}

	inline void LTMatrix::Apply3x3(LTVector &vec)
	{
		LTVector temp;
		
		Apply3x3(vec, temp);
		vec = temp;
	}

	inline void LTMatrix::Apply3x3(const LTVector &s, LTVector &d)
	{
		d.x = s.x*m[0][0] + s.y*m[0][1] + s.z*m[0][2];
		d.y = s.x*m[1][0] + s.y*m[1][1] + s.z*m[1][2];
		d.z = s.x*m[2][0] + s.y*m[2][1] + s.z*m[2][2];
	}

	inline void LTMatrix::Apply4x4(const LTVector &s, LTVector &d )
	{
		float w, oneOverW;

		w = s.x*m[3][0] + s.y*m[3][1] + s.z*m[3][2] + m[3][3];
		oneOverW = 1.0f / w;

		d.x = (s.x*m[0][0] + s.y*m[0][1] + s.z*m[0][2] + m[0][3]) * oneOverW;
		d.y = (s.x*m[1][0] + s.y*m[1][1] + s.z*m[1][2] + m[1][3]) * oneOverW;
		d.z = (s.x*m[2][0] + s.y*m[2][1] + s.z*m[2][2] + m[2][3]) * oneOverW;
	}

	inline void LTMatrix::Apply(LTMatrix &mTarget)
	{
		mTarget = *this * mTarget;
	}

	inline void LTMatrix::GetTranslation(LTVector &vec)
	{
		vec.x = m[0][3];
		vec.y = m[1][3];
		vec.z = m[2][3];
	}

	inline void LTMatrix::SetTranslation(LTVector vec)
	{
		SetTranslation(VEC_EXPAND(vec));
	}

	inline void LTMatrix::SetTranslation(float x, float y, float z)
	{
		m[0][3] = x;
		m[1][3] = y;
		m[2][3] = z;
	}

	inline LTMatrix LTMatrix::MakeInverseTransform()
	{
		LTMatrix mRet;

		Mat_InverseTransformation(this, &mRet);
		return mRet;
	}

	inline LTMatrix LTMatrix::operator~()
	{
		return MakeInverseTransform();
	}

	inline LTMatrix LTMatrix::operator*(LTMatrix &other)
	{
		LTMatrix mRet;

		MatMul(&mRet, this, &other);
		return mRet;
	}

	inline LTVector LTMatrix::operator*(LTVector other)
	{
		LTVector vRet;
		MatVMul_H(&vRet, this, &other);
		return vRet;
	}


	// For backwards compatibility.
	inline void Mat_GetBasisVectors(LTMatrix *pMat, LTVector *pRight, LTVector *pUp, LTVector *pForward)
	{
		pMat->GetBasisVectors(pRight, pUp, pForward);
	}

	inline void Mat_SetBasisVectors(LTMatrix *pMat, LTVector *pRight, LTVector *pUp, LTVector *pForward)
	{
		pMat->SetBasisVectors(pRight, pUp, pForward);
	}
		


#endif  // __LTMATRIX_H__
