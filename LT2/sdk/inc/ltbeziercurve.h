
// This module contains functions to deal with 2D bezier curve segments.
// DEdit uses the same functions.

#ifndef __LTBEZIERCURVE_H__
#define __LTBEZIERCURVE_H__


	#include "ltbasetypes.h"
	#include "ltvector.h"


	// This number is quintessentially the right number.
	#define DEFAULT_BEZIER_SUBDIVISIONS 20


	// Evaluate the Bezier curve at the specified point.  t is between 0 and 1.
	inline void Bezier_Evaluate(LTVector &out,
		LTVector &pt1, LTVector &pt2,
		LTVector &pt3, LTVector &pt4,
		float t)
	{
		float oneMinusT[3];
		float tSquared;

		oneMinusT[0] = 1.0f - t;
		oneMinusT[1] = oneMinusT[0] * oneMinusT[0];
		oneMinusT[2] = oneMinusT[1] * oneMinusT[0];

		tSquared = t * t;

		out = pt1 * oneMinusT[2] +
			pt2 * (3.0f * t * oneMinusT[1]) +
			pt3 * (3.0f * tSquared * oneMinusT[0]) +
			pt4 * (tSquared * t);
	}


	// Returns the distance between two points on the curve.
	// The more subdivisions, the slower it is but the more accurate.
	// There must be at least 1 subdivision.
	// This function should use forward differencing in the future if there
	// are more than a few subdivisions.
	inline float Bezier_SubSegmentLength(
		LTVector &pt1, LTVector &pt2, LTVector &pt3, LTVector &pt4,
		float t1, float t2,
		uint32 nSubDivisions=DEFAULT_BEZIER_SUBDIVISIONS)
	{
		LTVector prevPt, curPt;
		float totalLen, tInc, tCur;

        nSubDivisions = LTMAX(nSubDivisions, 1);

		totalLen = 0.0f;
		Bezier_Evaluate(prevPt,
			pt1, pt2, pt3, pt4, t1);

		tInc = (t2 - t1) / nSubDivisions;
		tCur = t1 + tInc;
		while(nSubDivisions)
		{
			nSubDivisions--;

			Bezier_Evaluate(curPt,
				pt1, pt2, pt3, pt4, tCur);

			totalLen += (curPt - prevPt).Mag();
			tCur += tInc;
			prevPt = curPt;
		}

		return totalLen;
	}


	// Returns the (approximate) length of the curve segment.  This function is pretty slow.
	// The more subdivisions, the slower it is but the more accurate.
	// There must be at least 1 subdivision.
	inline float Bezier_SegmentLength(
		LTVector &pt1, LTVector &pt2, LTVector &pt3, LTVector &pt4,
		uint32 nSubDivisions=DEFAULT_BEZIER_SUBDIVISIONS)
	{
		return Bezier_SubSegmentLength(pt1, pt2, pt3, pt4, 0.0f, 1.0f, nSubDivisions);
	}


#endif  // __LTBEZIERCURVE_H__