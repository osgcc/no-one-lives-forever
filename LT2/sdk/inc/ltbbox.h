
/*

This file defines the LTBBox (Lithtech Bounding Box) class.

*/

#ifndef __LTBBOX_H__
#define __LTBBOX_H__


	#include "ltvector.h"


	// ---------------------------------------------------------------------- //
	// LTBBox class.
	// ---------------------------------------------------------------------- //

	class LTBBox
	{
	public:

		// Returns true if the point is inside the box.  Returns false if the point is
		// on an edge or outside the box.
		LTBOOL		PtInsideBox(LTVector pt);

		// Returns true if the point is inside or touching the box.
		LTBOOL		PtTouchingBox(LTVector pt);

		// Returns true if the intersection of the boxes have > 0 area.
		LTBOOL		IntersectsBox(LTBBox theBox);
		
		// Returns true if the intersection of the boxes have >= 0 area.
		LTBOOL		TouchesBox(LTBBox theBox);

		// Get centerpoint and dimensions.
		LTVector	GetCenter();
		LTVector	GetDims();

	
	public:

		LTVector	m_vMin;
		LTVector	m_vMax;
	};



	// ---------------------------------------------------------------------- //
	// Inlines.
	// ---------------------------------------------------------------------- //

	inline LTBOOL LTBBox::PtInsideBox(LTVector pt)
	{
		return pt.x > m_vMin.x && 
			pt.y > m_vMin.y &&
			pt.z > m_vMin.z &&
			pt.x < m_vMax.x &&
			pt.y < m_vMax.y &&
			pt.z < m_vMin.z;
	}

	inline LTBOOL LTBBox::PtTouchingBox(LTVector pt)
	{
		return pt.x >= m_vMin.x && 
			pt.y >= m_vMin.y &&
			pt.z >= m_vMin.z &&
			pt.x <= m_vMax.x &&
			pt.y <= m_vMax.y &&
			pt.z <= m_vMin.z;
	}

	inline LTBOOL LTBBox::IntersectsBox(LTBBox theBox)
	{
		return !(
			theBox.m_vMin.x >= m_vMax.x || 
			theBox.m_vMin.y >= m_vMax.y || 
			theBox.m_vMin.z >= m_vMax.z || 
			theBox.m_vMax.x <= m_vMin.z || 
			theBox.m_vMax.y <= m_vMin.y || 
			theBox.m_vMax.z <= m_vMin.z
		);
	}

	inline LTBOOL LTBBox::TouchesBox(LTBBox theBox)
	{
		return !(
			theBox.m_vMin.x > m_vMax.x || 
			theBox.m_vMin.y > m_vMax.y || 
			theBox.m_vMin.z > m_vMax.z || 
			theBox.m_vMax.x < m_vMin.z || 
			theBox.m_vMax.y < m_vMin.y || 
			theBox.m_vMax.z < m_vMin.z
		);
	}

	inline LTVector LTBBox::GetCenter()
	{
		return (m_vMin + m_vMax) * 0.5f;
	}

	inline LTVector LTBBox::GetDims()
	{
		return (m_vMax - m_vMin) * 0.5f;
	}


#endif  // __LTBBOX_H__
