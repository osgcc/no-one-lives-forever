
#ifndef __LTVECTOR_H__
#define __LTVECTOR_H__


	#include "iltstream.h"


	/////////////////////////////////////////////////////////////////////////////
	//
	// C++ Vector Class
	//
	//


	// Defines....
	#define	ZERO					0.0f
	#define ONE						1.0f
	#define	DIFF(x,y)				( (x)<(y) ? ((y)-(x)) : ((x)-(y)) )
	#define	ABS(x)					( (x)<0 ? (-(x)) : (x) )


	template<class T>
	class _CVector
	{
		public:
									

							_CVector() {}
							_CVector(T mx, T my, T mz) {x=mx; y=my; z=mz;}

			// Member Functions
			void				Init(T px=0.0f, T py=0.0f, T pz=0.0f) { x = px; y = py; z = pz; }
			void				Term();

			T					Dist(const _CVector<T> &vec) const {return (*this - vec).Mag();}
			T					DistSqr(const _CVector<T> &vec) const {return (*this - vec).MagSqr();}

			T					Mag() const { return (T)sqrt((x * x) + (y * y) + (z * z)); }
			T					MagSqr() const { return (x * x) + (y * y) + (z * z); }
			T					MagApprox() const;

			T					Dot(_CVector<T> v)	const { return (x * v.x) + (y * v.y) + (z * v.z); }

			void				Norm(T nVal = ONE);
			void				NormApprox(T nVal = ONE);
			_CVector<T>			Cross( const _CVector<T> v ) const;

			_CVector<float>		FVec() const {return _CVector<float>((float)x, (float)y, (float)z);}
			_CVector<double>	DVec() const {return _CVector<double>((double)x, (double)y, (double)z);}

			LTBOOL				Equals( const _CVector<T> &v, T variance=ZERO ) const;

			// Operators
			_CVector<T> operator		- () const { return _CVector<T>(-x, -y, -z); }

			_CVector<T> operator		+ (const _CVector<T> v) const { return _CVector<T>(x + v.x, y + v.y, z + v.z); }
			_CVector<T> operator		- (const _CVector<T> v) const { return _CVector<T>(x - v.x, y - v.y, z - v.z); }
			_CVector<T> operator		* (const _CVector<T> v) const { return _CVector<T>(x * v.x, y * v.y, z * v.z); }
			_CVector<T> operator		/ (const _CVector<T> v) const { return _CVector<T>(x / v.x, y / v.y, z / v.z); }
							
			_CVector<T> operator		+ (T v) const { return _CVector<T>(x + v, y + v, z + v); }
			_CVector<T> operator		- (T v) const { return _CVector<T>(x - v, y - v, z - v); }
			_CVector<T> operator		* (T v) const { return _CVector<T>(x * v, y * v, z * v); }
			_CVector<T> operator		/ (T v) const { return _CVector<T>(x / v, y / v, z / v); }

			_CVector<T>					Inverse() const
			{
				_CVector<T> temp;
				temp = *this;
				temp.Norm();
				temp *= 1.0f / Mag();
				return temp;
			}

			void operator			+= (const _CVector<T> v) { x += v.x; y += v.y; z += v.z; }
			void operator			-= (const _CVector<T> v) { x -= v.x; y -= v.y; z -= v.z; }
			void operator			*= (const _CVector<T> v) { x *= v.x; y *= v.y; z *= v.z; }
			void operator			/= (const _CVector<T> v) { x /= v.x; y /= v.y; z /= v.z; }
									
			void operator			+= (T v) { x += v; y += v; z += v; }
			void operator			-= (T v) { x -= v; y -= v; z -= v; }
			void operator			*= (T v) { x *= v; y *= v; z *= v; }
			void operator			/= (T v) { x /= v; y /= v; z /= v; }

			LTBOOL operator			> ( const _CVector<T> &other ) const { return ((x>other.x) && (y>other.y) && (z>other.z)); }
			LTBOOL operator			< ( const _CVector<T> &other ) const { return ((x<other.x) && (y<other.y) && (z<other.z)); }

			LTBOOL operator			>= ( const _CVector<T> &other ) const { return ((x>=other.x) && (y>=other.y) && (z>=other.z)); }
			LTBOOL operator			<= ( const _CVector<T> &other ) const { return ((x<=other.x) && (y<=other.y) && (z<=other.z)); }

			LTBOOL operator			== ( const _CVector<T> &other ) const { return ((x==other.x) && (y==other.y) && (z==other.z)); }
			LTBOOL operator			!= ( const _CVector<T> &other ) const { return ((x!=other.x) || (y!=other.y) || (z!=other.z)); }

			_CVector<T> operator		^ ( const _CVector<T> v ) const { return Cross(v); }
			T   &operator		[] ( uint32 i ) { return ((T*)this)[i]; }

			// Member Variables
			T	x;
			T	y;
			T	z;
	};


	//------------------------------------------------------------------
	// Read/write functions.
	//------------------------------------------------------------------

	template<class T>
	inline void LTStream_Read(ILTStream *pStream, _CVector<T> &vec)
	{
		STREAM_READ(vec.x);
		STREAM_READ(vec.y);
		STREAM_READ(vec.z);
	}

	template<class T>
	inline void LTStream_Write(ILTStream *pStream, const _CVector<T> &vec)
	{
		STREAM_WRITE(vec.x);
		STREAM_WRITE(vec.y);
		STREAM_WRITE(vec.z);
	}


	// Don't worry about all the template stuff, just always use this.
	typedef	_CVector<float> LTVector;
	

	//------------------------------------------------------------------
	//
	// Function	: CVector::Equals
	//
	// Purpose	: Returns if two vectors are equal (it sees if the
	//            difference between each coordinate is less than
	//            variance)
	//
	//------------------------------------------------------------------

	template<class T>
	inline LTBOOL _CVector<T>::Equals( const _CVector<T> &v, T variance ) const
	{
		return ((DIFF(x,v.x)<=variance) && (DIFF(y,v.y)<=variance) && (DIFF(z,v.z)<=variance));
	}



	//------------------------------------------------------------------
	//
	// Function	: MagApprox
	//
	// Purpose	: Approximate magnitude of vector (within 12%)
	//
	//------------------------------------------------------------------

	template<class T>
	inline T _CVector<T>::MagApprox () const
	{
		T	min, med, max;
		T	temp;

		max = ABS( x );
		med = ABS( y );
		min = ABS( z );

		if( max < med )
		{
			temp = max;
			max = med;
			med = temp;
		}
		
		if( max < min )
		{
			temp = max;
			max = min;
			min = temp;
		}

		return max + ((med + min) * 0.25f);
	}



	//------------------------------------------------------------------
	//
	// Function	: Norm
	//
	// Purpose	: Normalises a vector
	//
	//------------------------------------------------------------------

	template<class T>
	inline void _CVector<T>::Norm( T nVal )
	{
		T inv;
		T mag = Mag();

		if (mag == 0.0f) 
			return;

		inv = nVal / mag;
		x = x * inv;
		y = y * inv;
		z = z * inv;
	}



	//------------------------------------------------------------------
	//
	// Function	: NormApprox
	//
	// Purpose	: Normalises a vector using an approximation to the
	//            magnitude.
	//
	//------------------------------------------------------------------

	template<class T>
	inline void _CVector<T>::NormApprox( T nVal )
	{
		T inv;
		T mag = MagApprox();

		if (mag == 0.0f) 
			return;

		inv = nVal / mag;
		x = x * inv;
		y = y * inv;
		z = z * inv;
	}



	//------------------------------------------------------------------
	//
	// Function	: Cross
	//
	// Purpose	: Calculates cross product of vector
	//
	//------------------------------------------------------------------

	template<class T>
	inline _CVector<T> _CVector<T>::Cross ( const _CVector<T> v ) const
	{
		return _CVector<T>(
						((v.y * z) - (v.z * y)),
					   ((v.z * x) - (v.x * z)),
					   ((v.x * y) - (v.y * x)) 
						);
	}


	// Vector macros.
	
	// MAKE SURE NOT TO HAVE DEST BE SOURCE1 OR SOURCE2 or it'll screw up!
	#define VEC_CROSS(dest, v1, v2) \
		{\
		(dest).x = ((v2).y*(v1).z - (v2).z*(v1).y);\
		(dest).y = ((v2).z*(v1).x - (v2).x*(v1).z);\
		(dest).z = ((v2).x*(v1).y - (v2).y*(v1).x);\
		}
	
	
	#define VEC_ADD(d, v1, v2) \
		{\
		(d).x = (v1).x + (v2).x;\
		(d).y = (v1).y + (v2).y;\
		(d).z = (v1).z + (v2).z;\
		}

	#define VEC_ADDSCALED(d, v1, v2, s) \
		{\
		(d).x = (v1).x + ((v2).x * (s));\
		(d).y = (v1).y + ((v2).y * (s));\
		(d).z = (v1).z + ((v2).z * (s));\
		}

	#define VEC_SUB(d, v1, v2) \
		{\
		(d).x = (v1).x - (v2).x;\
		(d).y = (v1).y - (v2).y;\
		(d).z = (v1).z - (v2).z;\
		}

	#define VEC_MUL(d, v1, v2) \
		{\
		(d).x = (v1).x * (v2).x;\
		(d).y = (v1).y * (v2).y;\
		(d).z = (v1).z * (v2).z;\
		}

	#define VEC_DIV(d, v1, v2) \
		{\
		(d).x = (v1).x / (v2).x;\
		(d).y = (v1).y / (v2).y;\
		(d).z = (v1).z / (v2).z;\
		}

	#define VEC_MULSCALAR(d, v1, s) \
		{\
		(d).x = (v1).x * (s); \
		(d).y = (v1).y * (s); \
		(d).z = (v1).z * (s); \
		}

	#define VEC_DIVSCALAR(d, v1, s) \
		{\
		(d).x = (v1).x / (s); \
		(d).y = (v1).y / (s); \
		(d).z = (v1).z / (s);\
		}

	#define VEC_LERP(d, v1, v2, t) \
		{\
		(d).x = (v1).x + ((v2).x - (v1).x) * t;\
		(d).y = (v1).y + ((v2).y - (v1).y) * t;\
		(d).z = (v1).z + ((v2).z - (v1).z) * t;\
		}

	#define VEC_CLAMP(v, a, b) \
	{\
		(v).x = LTCLAMP((v).x, a, b);\
		(v).y = LTCLAMP((v).y, a, b);\
		(v).z = LTCLAMP((v).z, a, b);\
	}

	#define VEC_MIN(v, a, b) \
	{\
		(v).x = LTMIN((a).x, (b).x);\
		(v).y = LTMIN((a).y, (b).y);\
		(v).z = LTMIN((a).z, (b).z);\
	}

	#define VEC_MAX(v, a, b) \
	{\
		(v).x = LTMAX((a).x, (b).x);\
		(v).y = LTMAX((a).y, (b).y);\
		(v).z = LTMAX((a).z, (b).z);\
	}

	#define VEC_NEGATE(d, s) \
		{\
		(d).x = -(s).x; \
		(d).y = -(s).y; \
		(d).z = -(s).z; \
		}

	// Dot product of 2 vectors.
	#define VEC_DOT(v1, v2) ( (v1).x*(v2).x + (v1).y*(v2).y + (v1).z*(v2).z )

	// Expand the vector for function calls..
	#define EXPANDVEC(vec) (vec).x, (vec).y, (vec).z
	
	// Distance between 2 vectors.
	#define VEC_DISTSQR(v1, v2) ( \
		((v1).x-(v2).x) * ((v1).x-(v2).x) + \
		((v1).y-(v2).y) * ((v1).y-(v2).y) + \
		((v1).z-(v2).z) * ((v1).z-(v2).z) )

	#define VEC_DIST(v1, v2) ((float)sqrt(VEC_DISTSQR(v1, v2)))

	#define VEC_MAGSQR(v) ((v).x*(v).x + (v).y*(v).y + (v).z*(v).z)
	#define VEC_MAG(v) ((float)sqrt(VEC_MAGSQR(v)))

	#define VEC_INVMAG(v) (1.0f / VEC_MAG(v))

	#define VEC_NORM(v) \
		{\
			float __temp_normalizer_____;\
			__temp_normalizer_____ = 1.0f / VEC_MAG(v);\
			(v).x *= __temp_normalizer_____;\
			(v).y *= __temp_normalizer_____;\
			(v).z *= __temp_normalizer_____;\
		}

	#define VEC_COPY(dest, src) \
		{\
			(dest).x = (src).x; (dest).y = (src).y; (dest).z = (src).z;\
		}
	
	#define VEC_SET(v, vx, vy, vz) \
		{\
			(v).x = (float)(vx); (v).y = (float)(vy); (v).z = (float)(vz);\
		}
	
	#define VEC_EXPAND(v) (v).x, (v).y, (v).z
	#define VEC_INIT(v) (v).x = (v).y = (v).z = 0.0f;
	#define VEC_INDEX(v, i) (((float*)&(v))[i])


#endif  // __LTVECTOR_H__