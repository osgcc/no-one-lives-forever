
#ifndef __LTROTATION_H__
#define __LTROTATION_H__


	#include "ltbasetypes.h"
	#include "ltvector.h"
	#include "ltquatbase.h"
	#include "ltmatrix.h"


	class LTRotation
	{
	// Constructors.
	public:

						LTRotation() {}
						LTRotation(float a, float b, float c, float d);
						LTRotation(const LTRotation &other);

	// Operators.
	public:

		// Multiply two quaternions. Note: this is exactly the same as converting both
		// quaternions to matrices, multiplying the matrices (in the same order, a*b),
		// then converting back to a quaternion (except it's MUCH faster and more accurate).
		LTRotation		operator*(const LTRotation &other) const;
		float&			operator[](uint32 i);

		LTRotation&		operator=(const LTRotation &other);
		LTRotation&		operator=(const LTMatrix &mOther);

		// Be careful since it only returns TRUE if they're EXACTLY the same.
		LTBOOL			operator==(const LTRotation &other) const;

		// Gives the conjugate quaternion (which will produce the inverse, or transposed matrix).
		LTRotation		operator~() const;


	// Functions.
	public:

		// Initialize.  Using default parameters sets it to identity (facing down positive Z).
		void			Init(float a=0.0f, float b=0.0f, float c=0.0f, float d=1.0f);

		// Set to identity (facing down Z axis).
		void			Identity();

		// Returns TRUE if the rotation is at identity.
		LTBOOL			IsIdentity() const;

		// Convert to/from matrices.
		void			ConvertToMatrix(LTMatrix &mat) const;
		void			ConvertFromMatrix(const LTMatrix &mat);

		// Interpolate between two rotations (stores the result in this quaternion).
		void			Slerp(const LTRotation &q1, const LTRotation &q2, float t);

		// Gives the conjugate quaternion (which will produce the inverse, or transposed matrix).
		LTRotation		Conjugate() const;



	// Data.
	public:

		float		m_Quat[4];
	};


	// ------------------------------------------------------------------ //
	// Inlines.
	// ------------------------------------------------------------------ //

	inline LTRotation::LTRotation(const LTRotation &other)
	{
		m_Quat[0] = other.m_Quat[0];
		m_Quat[1] = other.m_Quat[1];
		m_Quat[2] = other.m_Quat[2];
		m_Quat[3] = other.m_Quat[3];
	}

	inline LTRotation::LTRotation(float qx, float qy, float qz, float qw)
	{
		m_Quat[QX] = qx;
		m_Quat[QY] = qy;
		m_Quat[QZ] = qz;
		m_Quat[QW] = qw;
	}

	inline LTRotation LTRotation::operator*(const LTRotation &other) const
	{
		LTRotation qTemp;
		quat_Mul(qTemp.m_Quat, m_Quat, other.m_Quat);
		return qTemp;
	}

	inline float& LTRotation::operator[](uint32 i)
	{
		return m_Quat[i];
	}

	inline LTRotation& LTRotation::operator=(const LTRotation &other)
	{
		m_Quat[0] = other.m_Quat[0];
		m_Quat[1] = other.m_Quat[1];
		m_Quat[2] = other.m_Quat[2];
		m_Quat[3] = other.m_Quat[3];
		return *this;
	}

	inline LTRotation& LTRotation::operator=(const LTMatrix &mOther)
	{
		ConvertFromMatrix(mOther);
		return *this;
	}

	inline LTBOOL LTRotation::operator==(const LTRotation &other) const
	{
		return m_Quat[0] == other.m_Quat[0] &&
			m_Quat[1] == other.m_Quat[1] &&
			m_Quat[2] == other.m_Quat[2] &&
			m_Quat[3] == other.m_Quat[3];
	}

	inline LTRotation LTRotation::operator~() const
	{
		return Conjugate();
	}

	inline void LTRotation::Init(float x, float y, float z, float w)
	{
		m_Quat[QX] = x;
		m_Quat[QY] = y;
		m_Quat[QZ] = z;
		m_Quat[QW] = w;
	}

	inline void LTRotation::Identity()
	{
		Init();
	}

	inline LTBOOL LTRotation::IsIdentity() const
	{
		return m_Quat[0] == 0.0f &&
			m_Quat[1] == 0.0f &&
			m_Quat[2] == 0.0f &&
			m_Quat[3] == 1.0f;
	}

	inline void LTRotation::ConvertToMatrix(LTMatrix &mat) const
	{
		quat_ConvertToMatrix(m_Quat, mat.m);
	}

	inline void LTRotation::ConvertFromMatrix(const LTMatrix &mat)
	{
		quat_ConvertFromMatrix(m_Quat, mat.m);
	}

	inline void LTRotation::Slerp(const LTRotation &q1, const LTRotation &q2, float t)
	{
		quat_Slerp(m_Quat, q1.m_Quat, q2.m_Quat, t);
	}

	inline LTRotation LTRotation::Conjugate() const
	{
		return LTRotation(-m_Quat[QX], -m_Quat[QY], -m_Quat[QZ], m_Quat[QW]);
	}


#endif  // __LTROTATION_H__