
#ifndef __LTPLANE_H__
#define __LTPLANE_H__



	class LTPlane
	{
	public:

		inline			LTPlane() {}

		inline			LTPlane(float x, float y, float z, float dist)
						{
							m_Normal.Init(x,y,z);
							m_Dist = dist;
						}

		inline			LTPlane(LTVector normal, float dist)
						{
							m_Normal = normal;
							m_Dist = dist;
						}

		inline void		Init(LTVector vec, float dist)
		{
			m_Normal = vec;
			m_Dist = dist;
		}

		inline float	DistTo(LTVector vec)
		{
			return m_Normal.Dot(vec) - m_Dist;
		}

		inline LTPlane	operator-()		{return LTPlane(-m_Normal, -m_Dist);}

		inline LTVector&	Normal()	{return m_Normal;}
		inline float&		Dist()		{return m_Dist;}


	public:

		LTVector	m_Normal;
		float		m_Dist;
	};


#endif  // __LTPLANE_H__
