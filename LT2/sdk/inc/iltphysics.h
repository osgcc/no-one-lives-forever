
// This interface implements physics functionality.

#ifndef __ILTPHYSICS_H__
#define __ILTPHYSICS_H__


	// Sets the dims as large as it can by testing to see what's around the object.
	// The object will get touch notifications if it hits anything while resizing.
	#define SETDIMS_PUSHOBJECTS	(1<<0)

	
	// Teleport the object to its destination.
	#define MOVEOBJECT_TELEPORT	(1<<0)


	class MoveInfo
	{
	public:
		HOBJECT	m_hObject;
		float	m_dt;
		LTVector	m_Offset;
	};


	class ILTPhysics
	{
	public:
		
		// Get/Set friction coefficient.
		virtual LTRESULT GetFrictionCoefficient(HOBJECT hObj, float &coeff);
		virtual LTRESULT SetFrictionCoefficient(HOBJECT hObj, float coeff);

		// Get/set force ignore limit.
		virtual LTRESULT GetForceIgnoreLimit(HOBJECT hObj, float &limit);
		virtual LTRESULT SetForceIgnoreLimit(HOBJECT hObj, float limit);
		
		// Get/Set acceleration and velocity
		virtual LTRESULT GetVelocity(HOBJECT hObj, LTVector *pVel);
		virtual LTRESULT SetVelocity(HOBJECT hObj, LTVector *pVel)=0;
		
		virtual LTRESULT GetAcceleration(HOBJECT hObj, LTVector *pAccel);
		virtual LTRESULT SetAcceleration(HOBJECT hObj, LTVector *pAccel)=0;

		// Get/Set an object's mass (default is 30).
		virtual LTRESULT GetObjectMass(HOBJECT hObj, float &mass);
		virtual LTRESULT SetObjectMass(HOBJECT hObj, float mass);

		// Get the object's current dimensions.
		virtual LTRESULT GetObjectDims(HOBJECT hObj, LTVector *pNewDims);
		
		// Changes the object's dimensions without pushing against objects and world.
		// Flags is a combination of SETDIMS_ flags above.
		virtual LTRESULT SetObjectDims(HOBJECT hObj, LTVector *pNewDims, uint32 flags)=0;

		// This function moves an object, colliding/pushing/crushing objects
		// in its way (if it's solid..)  Flags is a combination of MOVEOBJECT_ flags.
		virtual LTRESULT MoveObject(HOBJECT hObj, LTVector *pPos, uint32 flags)=0;

		// Find out what the object is standing on.
		virtual LTRESULT GetStandingOn(HOBJECT hObj, CollisionInfo *pInfo);

		// Returns LT_YES if hObj is a main world object and LT_NO otherwise.
		virtual LTRESULT IsWorldObject(HOBJECT hObj);

		// Get/set global force.  This is an acceleration applied to all objects
		// when they move.  Default is (0,-2000,0) which simulates gravity.
		virtual LTRESULT GetGlobalForce(LTVector &vec)=0;
		virtual LTRESULT SetGlobalForce(LTVector &vec)=0;

		// Get/set the stair-stepping height.  -1 will use 1/2 the object's bounding box
		virtual LTRESULT GetStairHeight(float &fHeight)=0;
		virtual LTRESULT SetStairHeight(float fHeight)=0;

	protected:
		ClientServerType m_ClientServerType; // Tells if this is on the client or server.
	};


	// Client-specific physics stuff.
	class ILTClientPhysics : public ILTPhysics
	{
	public:
		// Updates the object's movement using its velocity, acceleration, and the
		// time delta passed in (usually the frame time).  Fills in m_Offset with the
		// position delta you should apply.
		virtual LTRESULT UpdateMovement(MoveInfo *pInfo)=0;

		// Move the specified object but only test for collisions/pushing on
		// the objects specified.  It'll carry things standing on it.
		virtual LTRESULT MovePushObjects(HOBJECT hToMove, LTVector &newPos, 
			HOBJECT *hPushObjects, uint32 nPushObjects)=0;
		
		// Rotate the specified object but only test for collisions/pushing on
		// the objects specified.  It'll carry things standing on it.
		// This only works on world models.
		virtual LTRESULT RotatePushObjects(HOBJECT hToMove, LTRotation &newRot, 
			HOBJECT *hPushObjects, uint32 nPushObjects)=0;
	};


#endif // __ILTPHYSICS_H__