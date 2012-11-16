
// The ILTMath interface has some useful math functionality.

#ifndef __ILTMATH_H__
#define __ILTMATH_H__



	class ILTMath
	{
	public:
		
		// Get the vectors from a rotation.
		virtual LTRESULT GetRotationVectors(LTRotation &rot, LTVector &right, LTVector &up, LTVector &forward);
		
		// Interpolate between two rotations.
		virtual LTRESULT InterpolateRotation(LTRotation &rDest, LTRotation &rot1, LTRotation &rot2, float t);
	
		// Setup the rotation based on euler angles 
		// pitch = rotation around X
		// yaw = rotation around Y
		// roll = rotation around Z
		virtual LTRESULT SetupEuler(LTRotation &rRot, float pitch, float yaw, float roll);

		// Create a transformation matrix from a translation, rotation.
		virtual LTRESULT SetupTransformationMatrix(LTMatrix &mMat, LTVector &vTranslation, LTRotation &rRotation);
		
		// Create a translation matrix for the given translation.
		virtual LTRESULT SetupTranslationMatrix(LTMatrix &mMat, LTVector &vTranslation);
		
		// Create a rotation matrix for the given rotation.
		virtual LTRESULT SetupRotationMatrix(LTMatrix &mMat, LTRotation &rRot);
		
		// Create a translation vector from a tranformation matrix.
		virtual LTRESULT SetupTranslationFromMatrix(LTVector &vTranslation, LTMatrix &mMat);
		
		// Create a rotation for the given tranformation matrix.
		virtual LTRESULT SetupRotationFromMatrix(LTRotation &rRot, LTMatrix &mMat);

		// Setup a matrix to rotate around a point.
		virtual LTRESULT SetupRotationAroundPoint(LTMatrix &mMat, LTRotation &rRot, LTVector &vPoint);

		// Align a rotation to a normal and spin it.
		// Use pUp to set the frame of reference.
		// If pUp is NULL or the same direction as pVector, then it
		// will kludge an up vector.
		virtual LTRESULT AlignRotation(LTRotation &rOutRot, LTVector &vVector, LTVector &vUp);

		// Treat the rotation like Euler angles...
		virtual LTRESULT EulerRotateX(LTRotation &rRot, float amount);
		virtual LTRESULT EulerRotateY(LTRotation &rRot, float amount);
		virtual LTRESULT EulerRotateZ(LTRotation &rRot, float amount);

		// Rotate this rotation around the given axis by a certain amount.
		virtual LTRESULT RotateAroundAxis(LTRotation &rRot, LTVector &vAxis, float amount);

		// Gets orientation vectors from the matrix.
		virtual LTRESULT GetRotationVectorsFromMatrix(LTMatrix &mMat, 
				LTVector &vRight, LTVector &vUp, LTVector &vForward);
	};


#endif // __ILTMATH_H__
