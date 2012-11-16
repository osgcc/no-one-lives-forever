
#ifndef __ILTTRANSFORM_H__
#define __ILTTRANSFORM_H__

	
	#include "ltbasedefs.h"


	// The ILTTransform class provides functionality to operate on LTransforms.
	class ILTTransform
	{
	public:

		// Setup a LTransform.
		virtual LTRESULT Get(LTransform &transform, LTVector &pos, LTRotation &rot);
		virtual LTRESULT Set(LTransform &transform, LTVector &pos, LTRotation &rot);

		// Get just position and rotation.
		virtual LTRESULT GetPos(LTransform &transform, LTVector &pos);
		virtual LTRESULT GetRot(LTransform &transform, LTRotation &rot);
		
		// Convert LTransforms to/from matrices.
		virtual LTRESULT ToMatrix(LTransform &transform, LTMatrix &mat);
		virtual LTRESULT FromMatrix(LTransform &transform, LTMatrix &mat);

		// (transform * inverse = identity)
		virtual LTRESULT Inverse(LTransform &inverse, LTransform &transform);

		// Like an add.
		virtual LTRESULT Multiply(LTransform &out, LTransform &t1, LTransform &t2);

		// Like a subtract. (ie: diff = t1 - t2  so  t2 + diff = t1)
		virtual LTRESULT Difference(LTransform &diff, LTransform &t1, LTransform &t2);
	};


#endif  // __ILTTRANSFORM_H__