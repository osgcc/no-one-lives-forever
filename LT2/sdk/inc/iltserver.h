
// server_de defines the ILTServer interface, which consists of all the
// server-side DirectEngine functionality.

#ifndef __ILTSERVER_H__
#define __ILTSERVER_H__

	
	#include "ltbasedefs.h"
	#include "ltserverobj.h"
	#include "iltcommon.h"
	#include "iltcsbase.h"
	#include "iltmath.h"
	#include "iltsoundmgr.h"


	// Typedef to deal with the fact that there were two different versions of a console variable handle
	typedef HCONSOLEVAR HCONVAR;
	DEFINE_HANDLE_TYPE(HCLIENTREF);


	// Load world flags.
	#define LOADWORLD_LOADWORLDOBJECTS	(1<<0)	// Load objects from the world file?
	#define LOADWORLD_RUNWORLD			(1<<1)	// Start running world immediately?
	#define LOADWORLD_NORELOADGEOMETRY	(1<<2)	// Don't reload geometry if the world filename
												// is the same as the currently loaded one.

	// ---------------------------------------------------------------------- //
	// Load/Save objects flags.
	// ---------------------------------------------------------------------- //

	#define RESTOREOBJECTS_RESTORETIME	1	// Restore time information?

	#define SAVEOBJECTS_SAVEGAMECONSOLE	1	// Save the game console state?
	#define SAVEOBJECTS_SAVEPORTALS		2	// Save the portal states?


	// ---------------------------------------------------------------------- //
	// Client info flags.
	//
	// CIF_LOCAL and CIF_PLAYBACK are not settable with SetClientInfoFlags.
	// ---------------------------------------------------------------------- //

	#define CIF_LOCAL				(1<<0)	// Client is local (non-network) connection.
	#define CIF_PLAYBACK			(1<<1)	// Virtual client from a demo playback.
	#define CIF_FULLRES				(1<<2)	// Client object is sent with full position resolution.
	#define CIF_SENDCOBJROTATION	(1<<3)	// Client object rotations are sent to client.
	#define CIF_FORCENEXTUPDATE		(1<<4)	// Force the server to update the client on the state
											// of the world as soon as it can.  In multiplayer 
											// games, it doesn't update the clients every frame
											// and this can be used if you send a message to the client
											// that needs to arrive in sync with object changes (like
											// animation changes).
	#define CIF_AUTOACTIVATEOBJECTS	(1<<5)	// Use this instead of PingObjectsFromObject whenever possible.
											// This activates objects from the client's view position
											// when determining what to send to the client (so activating
											// objects is free).
								

	// ---------------------------------------------------------------------- //
	// Object states.
	//
	// OBJSTATE_INACTIVE and OBJSTATE_INACTIVE_TOUCH override the effect of 
	// PingObjects.  OBJSTATE_ACTIVE clears the effect of OBJSTATE_INACTIVE
	// or OBJSTATE_INACTIVE_TOUCH, but the object can be autodeactivated.
	// ---------------------------------------------------------------------- //
							

	#define OBJSTATE_ACTIVE					0	// Normal healthy object.
	#define OBJSTATE_INACTIVE				1	// Inactive (no updates, physics, or touch notifies).
	#define OBJSTATE_INACTIVE_TOUCH			2	// Inactive, but gets touch notifies.
	#define	OBJSTATE_AUTODEACTIVATE_NOW		3	// Autodeactivate now, can reactivate thru PingObjects call.



	// ---------------------------------------------------------------------- //
	// Server state flags.
	// ---------------------------------------------------------------------- //
	
	#define SS_PAUSED		(1<<0)	// Server is paused.
	#define SS_DEMOPLAYBACK	(1<<1)	// We're running in 'demo playback' mode (read only).
	#define SS_CACHING		(1<<2)	// Server can pre-cache files.
	#define SS_LASTFLAG		SS_DEMOPLAYBACK

	
	// ---------------------------------------------------------------------- //
	// Object lists.
	// ---------------------------------------------------------------------- //
	
	struct ObjectLink
	{
		HOBJECT		m_hObject;
		ObjectLink	*m_pNext;
	};
	
	struct ObjectList
	{
		ObjectLink	*m_pFirstLink;
		int			m_nInList;
	};


	#define MAX_CLASSPROPINFONAME_LEN	128

	// Used by ILTServer::GetClassProp.
	class ClassPropInfo
	{
	public:
		char		m_PropName[MAX_CLASSPROPINFONAME_LEN];
		short		m_PropType;		// PT_ define from serverobj_de.h.
	};


	class ILTPhysics;
	class ILTModel;
	class ILTTransform;
	class ILTLightAnim;
	class ILTSoundMgr;


	// ---------------------------------------------------------------------- //
	// ILTServer interface. This is your interface to most DirectEngine
	// functionality. 
	// ---------------------------------------------------------------------- //

	class ILTServer : public ILTCSBase
	{	
	friend class CServerMgr;

	protected:

		virtual		~ILTServer() {}

	
	public:		

	// Main functions.

		// Gives you access to the m_pGameInfo from the StartGameRequest structure.
		// Note: this is a copy of the data and the pointer filled in can be NULL
		// if there is no game info data.
		LTRESULT	(*GetGameInfo)(void **ppData, uint32 *pLen);

		// Returns LTNULL if the class doesn't exist.
		HCLASS		(*GetClass)(char *pName);

		// Get the ClassDef info from a class.  This is useful if you want to
		// get at the class's property names.
		virtual LTRESULT GetNumClassProps(const HCLASS hClass, 
			uint32 &count)=0;
		
		virtual LTRESULT GetClassProp(const HCLASS hClass, 
			const uint32 iProp, ClassPropInfo &info)=0;

		// Get a class's name.
		virtual LTRESULT GetClassName(const HCLASS hClass,
			char *pName, uint32 maxNameBytes)=0;

		// Get a class's static object.  Returns LT_NOTFOUND if the server
		// doesn't have a static object of this class.
		LTRESULT	(*GetStaticObject)(HCLASS hClass, HOBJECT *obj);

		// Get an object's class.
		HCLASS		(*GetObjectClass)(HOBJECT hObject);

		// Tells if hClass is the class of hTest (or is derived from hTest).
		// If you pass in LTNULL for hTest (like if GetClass returns LTNULL in 
		// IsKindOf(hClass, GetClass("TestClass"))), it will return FALSE.
		LTBOOL		(*IsKindOf)(HCLASS hClass, HCLASS hTest);
		

		// Creates an object using the object's default object type.
		LPBASECLASS	(*CreateObject)(HCLASS hClass, ObjectCreateStruct *pStruct);

		// Creates an object using string to specify properties.
		LPBASECLASS	(*CreateObjectProps)(HCLASS hClass, ObjectCreateStruct *pStruct, char *pszProps );


		// OBSOLETE.  Use PhysicsLT functions.
		virtual LTRESULT GetGlobalForce(LTVector *pVec)=0;
		virtual LTRESULT SetGlobalForce(LTVector *pVec)=0;

		
		// Server state flags.  (Combination of the SS_ flags above).
		// SetServerFlags returns the new flags (some may not be accepted).
		uint32		(*GetServerFlags)();
		uint32		(*SetServerFlags)(uint32 flags);

		// Cache in the given file.  Only call this from ServerShell::CacheFiles.
		// fileType is one of the FT_ defines in de_codes.
		// Returns LT_NOTFOUND if it can't find the file.
		LTRESULT	(*CacheFile)(uint32 fileType, char *pFilename);
		

		// Load the specified file in the loader thread. 
		// Also sends a message to clients saying to do the same.  When the 
		// operation is completed it calls IServerShell::FileLoadNotify with a result 
		// (which can be an error if the file is missing).  Objects can be created 
		// using this file but they won't be visible until all files they need are loaded.
		// Types currently supported are FT_MODEL and FT_TEXTURE.
		// (Textures aren't loaded on the server.  A message is sent to the clients 
		// to load the texture in their thread).
		// LT_UNSUPPORTED is returned if you pass an invalid type.
		// LT_MISSINGFILE is returned if the file is missing.
		// LT_ALREADYEXISTS is returned if the file is already in memory.
		// LT_INPROGRESS is returned if it's already loading in the thread.
		// (Note: a lot of these returns don't signify errors...)
		virtual LTRESULT ThreadLoadFile(char *pFilename, uint32 type)=0;

		// Unload the data.  Returns LT_ERROR if the file is being used and can't be 
		// unloaded.  Returns LT_NOTFOUND if the file isn't currently loaded.
		virtual LTRESULT UnloadFile(char *pFilename, uint32 type)=0;
																	   		
		
	// Helpers..

		// Use this to iterate over all the polies in the world.  
		// Returns LT_FINISHED when there are no more polies to look at.
		// Returns LT_NOTINITIALIZED if there is no world loaded.
		// Iterate like this:
		// HPOLY hPoly = INVALID_HPOLY;
		// while(pServerLT->GetNextPoly(&hPoly) == LT_OK)
		// {
		//     ... do something with hPoly ...
		// }
		LTRESULT	(*GetNextPoly)(HPOLY *hPoly);

		// Get the world object that a particular HPOLY comes from.
		// NOTE: This will NOT work on terrains because one HPOLY may be shared
		// among multiple TerrainSection WorldModels.
		virtual LTRESULT	GetHPolyObject(
			const HPOLY hPoly,
			HOBJECT &hObject
			)=0;

		// Use these to time sections of code.  Timing is done in microseconds
		// (1,000,000 counts per second).
		void		(*StartCounter)(LTCounter *pCounter);
		uint32		(*EndCounter)(LTCounter *pCounter);
		
		// Returns a random number in the given range.
		LTFLOAT		(*Random)(LTFLOAT min, LTFLOAT max);

		// Returns an integer number in the given range.
		int			(*IntRandom)(int min, int max);

		// Returns a number from 0 to scale.
		LTFLOAT		(*RandomScale)(LTFLOAT scale);

		// Only use this for debugging.. sends an STC_BPRINT message
		// with the string in it.
		void		(*BPrint)(char *pMsg, ...);

		// Used to output a TRACE message to the Debug Output window.  Newlines must be explicitly used.
		void	(*DebugOut)( char *pMsg, ... );

		// Get/Set the sky definition.
		LTRESULT	(*GetSkyDef)(SkyDef *pDef);
		LTRESULT	(*SetSkyDef)(SkyDef *pDef);

		// Add/Remove objects from the sky list.
		// Each object should have a unique index.
		LTRESULT	(*AddObjectToSky)(HOBJECT hObj, uint32 index);
		LTRESULT	(*RemoveObjectFromSky)(HOBJECT hObj);

		// Get/set the global light object
		LTRESULT	(*GetGlobalLightObject)(HOBJECT *hObj);
		LTRESULT	(*SetGlobalLightObject)(HOBJECT hObj);


	// World control.

		// Portal flags are a combination of PORTAL_ flags in de_codes.
		// Returns LT_OK, LT_NOTFOUND, or LT_NOTINWORLD.  This is
		// case sensitive.
		LTRESULT		(*GetPortalFlags)(char *pPortalName, uint32 *pFlags);
		LTRESULT		(*SetPortalFlags)(char *pPortalName, uint32 flags);

		// Intersect a line segment.. (used to be raycast, but line segments are WAY faster).
		// Returns TRUE and fills in pInfo if it hit something.
		LTBOOL		(*IntersectSegment)(IntersectQuery *pQuery, IntersectInfo *pInfo);

		// Same as IntersectSegment, except for it casts a ray from pQuery->m_From
		// in the direction of pQuery->m_Dir.
		LTBOOL		(*CastRay)(IntersectQuery *pQuery, IntersectInfo *pInfo);
		
		// Find out what's at a given point (is it inside the world, outside, what
		// area brushes is it inside..)  You must give back the list to the engine
		// with RelinquishList()!
		ObjectList*	(*GetPointAreas)(LTVector *pPoint);

		// Find the objects intersecting this box.
		ObjectList*	(*GetBoxIntersecters)(LTVector *pMin, LTVector *pMax);

		// Get the shade (RGB, 0-255) at the point you specify.
		// Returns DFALSE if the point is outside the world.
		LTBOOL		(*GetPointShade)(LTVector *pPoint, LTVector *pColor);
		
		// Gets all the objects with the given name.
		virtual LTRESULT FindNamedObjects(char *pName,	
										 BaseObjArray<HOBJECT> &objArray,
										 uint32 *nTotalFound=NULL)=0;

		// Find all the objects that interesect the passed in world model
		// if the world model is moved/rotated to the new position/rotation.

		virtual LTRESULT FindWorldModelObjectIntersections(
			HOBJECT hWorldModel, 
			LTVector vNewPos, LTRotation rNewRot, 
			BaseObjArray<HOBJECT> &objArray)=0;

		// Find all the objects touching the given sphere.
		// Don't forget to relinquish the list you get!
		// Be VERY careful of using a large radius.  This function can take
		// tons of cycles if the radius is too large.
		ObjectList* (*FindObjectsTouchingSphere)(LTVector *pPosition, float radius);

		// Any time the engine gives you a list, you must 'give it back' with this,
		// or else you'll have tons of memory leaks.
		void		(*RelinquishList)(ObjectList *pList);

		// Get the bounding box for the current world.
		virtual LTRESULT	GetWorldBox(LTVector &min, LTVector &max)=0;


	// Object list management.

		// Allocate a list (free it with RelinquishList).
		ObjectList*	(*CreateObjectList)();
		
		// Add objects to a list.
		ObjectLink*	(*AddObjectToList)(ObjectList *pList, HOBJECT hObj);
		
		// Remove an object from the list given the handle. 
		// Note: LithTech will just do a search over all the objects in the
		//       list for this, so be warned.
		void		(*RemoveObjectFromList)(ObjectList *pList, HOBJECT hObj);



	// OBSOLETE messaging functions.  Use CommonLT::CreateMessage, ILTMessage::Release, 
	// and ILTServer::SendToX.

		virtual HMESSAGEWRITE	StartSpecialEffectMessage(LPBASECLASS pObject)=0;
		virtual HMESSAGEWRITE	StartInstantSpecialEffectMessage(LTVector *pPos)=0;
		virtual HMESSAGEWRITE	StartMessageToObject(LPBASECLASS pSender, HOBJECT hSendTo, uint32 messageID)=0;
		virtual LTRESULT		StartMessageToServer(LPBASECLASS pSender, uint32 messageID, HMESSAGEWRITE *hWrite)=0;
		virtual HMESSAGEWRITE	StartMessage(HCLIENT hSendTo, uint8 messageID)=0;
		virtual LTRESULT		EndMessage2(HMESSAGEWRITE hMessage, uint32 flags)=0;
		virtual LTRESULT		EndMessage(HMESSAGEWRITE hMessage)=0;	// Just calls EndMessage2 with MESSAGE_GUARANTEED.
		

	// NEW message functions.  The main difference between these and the functions above is
	// that these don't free the message for you so you can send it multiple times.  

		// Use this to setup a special effect message.  If your object has
		// a special effect message, the client shell's SpecialEffectNotify() 
		// will be called.  An object can only have ONE special effect message.
		// If the object already has a special effect message, then it
		// clears out the current one.
		virtual LTRESULT SetObjectSFXMessage(HOBJECT hObject, ILTMessage &msg)=0;

		// Send a message to an object.  hSender can be NULL.
		virtual LTRESULT SendToObject(ILTMessage &msg, uint32 msgID, HOBJECT hSender, HOBJECT hSendTo, uint32 flags)=0;

		// Send the message to the server shell.  hSender can be NULL.
		virtual LTRESULT SendToServer(ILTMessage &msg, uint32 msgID, HOBJECT hSender, uint32 flags)=0;

		// Send the message to the client.  If hSendTo is NULL, it sends to them all.
		virtual LTRESULT SendToClient(ILTMessage &msg, uint8 msgID, HCLIENT hSendTo, uint32 flags)=0;
	
		// Sends the sfx message to all the clients who can see pos.
		virtual LTRESULT SendSFXMessage(ILTMessage &msg, LTVector &pos, uint32 flags)=0;

		// Send a packet thru tcp/ip if we're using tcp/ip.
		virtual LTRESULT SendTo(const void *pData, uint32 len, const char *sAddr, uint32 port)=0;

	
	// Client Functions.

		// Attach one client to another.  This means that messages sent to hParent
		// will also go to hClient, and hClient's client object will be reported
		// as hParent's object.  This is useful for demo playback when you want
		// to watch another player's view.
		LTRESULT	(*AttachClient)(HCLIENT hParent, HCLIENT hChild);

		// Detach a client from its parent attachment.
		LTRESULT	(*DetachClient)(HCLIENT hClient);

		// Iterate over the clients.  Pass in NULL to start.  Returns NULL
		// when there are no more.
		HCLIENT		(*GetNextClient)(HCLIENT hPrev);

		// Iterate over the saved client references.  These come from when
		// a world is saved.  Pass in DNULL to start.  See the Client Functions
		// section for the functions to look at these.
		HCLIENTREF	(*GetNextClientRef)(HCLIENTREF hRef);

		// HCLIENTREFs are used for comparison to HCLIENTs.
		uint32	(*GetClientRefInfoFlags)(HCLIENTREF hClient);
		LTBOOL	(*GetClientRefName)(HCLIENTREF hClient, char *pName, int maxLen);
		HOBJECT	(*GetClientRefObject)(HCLIENTREF hClient);
		
		// Get a client's (unique) ID.
		uint32	(*GetClientID)(HCLIENT hClient);
		
		// Get a client's ping time.
		virtual LTRESULT GetClientPing(HCLIENT hClient, float &ping)=0;
		
		// Get a client's name.
		LTBOOL	(*GetClientName)(HCLIENT hClient, char *pName, int maxLen);
		
		// A combination of the CIF_ flags above.
		void	(*SetClientInfoFlags)(HCLIENT hClient, uint32 dwClientFlags );
		uint32	(*GetClientInfoFlags)(HCLIENT hClient);

		// User data for HCLIENTs.
		void	(*SetClientUserData)(HCLIENT hClient, void *pData);
		void*	(*GetClientUserData)(HCLIENT hClient);

		// Kick a client off the server.
		// OnRemoveClient will be called.
		void	(*KickClient)(HCLIENT hClient, uint32 nReasonCode = 0);

		// Set where the client is seeing/hearing from.  This controls what the 
		// server sends the client.  You should set this every frame.
		LTRESULT	(*SetClientViewPos)(HCLIENT hClient, LTVector *pPos);


	// The 'game console state'.  This is a set of console variables and functions
	// that is used internally by the application DLLs.  The user can't access this
	// at all.  It's very useful for tracking global game variables and triggering
	// them through game objects.

		// Run a string through the game console.  The syntax is the same as any
		// other console string (semicolons separate commands, and new variable names
		// create new HCONVARs).
		void	(*RunGameConString)(char *pString);

		// Sets a console variable.  Creates a new one if it doesn't exist.
		void	(*SetGameConVar)(char *pName, char *pVal);
		
		// Get a handle to a console variable.
		HCONVAR	(*GetGameConVar)(char *pName);
		
	// Helpers.

		// These are used to get the property values from the world file.
		// The property names are case sensitive.  If the property doesn't exist,
		// it will return LT_NOTFOUND.
		LTRESULT	(*GetPropString)(char *pPropName, char *pRet, int maxLen);
		LTRESULT	(*GetPropVector)(char *pPropName, LTVector *pRet);
		LTRESULT	(*GetPropColor)(char *pPropName, LTVector *pRet);
		LTRESULT	(*GetPropReal)(char *pPropName, float *pRet);
		LTRESULT	(*GetPropFlags)(char *pPropName, uint32 *pRet);
		LTRESULT	(*GetPropBool)(char *pPropName, LTBOOL *pRet);
		LTRESULT	(*GetPropLongInt)(char *pPropName, long *pRet);
		LTRESULT	(*GetPropRotation)(char *pPropName, LTRotation *pRet);
		LTRESULT	(*GetPropRotationEuler)(char *pPropName, LTVector *pAngles); // pAngles = (pitch, yaw, roll)
		
		// Fills in the GenericProp for the different data types.  For a list
		// of which property types map to which GenericProp variable, see 
		// the GenericProp structure.
		// Note: if the property exists, it always initializes the members in the prop first,
		// so if the GenericProp variable doesn't support that property type, 
		// it'll be zero
		LTRESULT	(*GetPropGeneric)(char *pPropName, GenericProp *pProp);


		// See if a property exists.  If so, pPropType is filled in (if it's non-NULL) with
		// on of the PT_ defines.  Returns LT_NOTFOUND if it doesn't exist.
		LTRESULT	(*DoesPropExist)(char *pPropName, int *pPropType);

		// Get handles from objects and objects from handles. Note: HandleToObject will return
		// NULL if the given object doesn't reside on this server (it's controlled remotely).
		HOBJECT		(*ObjectToHandle)(LPBASECLASS pObject);
		LPBASECLASS	(*HandleToObject)(HOBJECT hObject);

		// Tests if a command is on for this client.
		LTBOOL	(*IsCommandOn)(HCLIENT hClient, int command);


		// Does a (fast) upper-case string comparison of the 2 strings.
		LTBOOL	(*UpperStrcmp)(char *pStr1, char *pStr2);

		// Parse a string for arguments.  Works similar to command line parser.
		// args within quotation marks are considered one arg.
		// Returns the all args after pCommand and before end of string or semi-colon.
		//		pCommand - Beginning of string.
		//		pNewCommandPos - Parse fills this in with the ending position
		//		argBuffer - memory Parse can use as scratchpad
		//		argPointers - Parse fills these pointers in to point to args found.
		//		nArgs - Parse fills in the number of arguments found.
		//		Return - LTTRUE, semicolon found, more args in string.  LTFALSE, no more args.
		int		(*Parse)(char *pCommand, char **pNewCommandPos, char *argBuffer, char **argPointers, int *nArgs);

	// Sound functions.

		// Play a sound with full control
		// Arguments:
		//		pPlaySoundInfo - sound control structure
		// Returns:
		//		LT_OK if successful.
		//		LT_ERROR on error.
		LTRESULT	(*PlaySound)( PlaySoundInfo *pPlaySoundInfo );

		// Get total length in seconds of sound.
		// Arguments:
		//		hSound - Handle to sound.
		//		fDuration - Duration of sound.
		// Returns:
		//		LT_OK if successful.
		//		LT_INVALIDPARAMS if hSound not available or not tracking time.
		LTRESULT	(*GetSoundDuration)( HLTSOUND hSound, LTFLOAT *fDuration );

		// IsSoundDone
		// Arguments:
		//		hSound - Handle to sound.
		//		bDone - Indicates sound is completed.
		// Returns:
		//		LT_OK if successful.
		//		LT_INVALIDPARAMS if hSound not available or not tracking time.
		LTRESULT	(*IsSoundDone)( HLTSOUND hSound, LTBOOL *bDone );

		// Kill a sound.
		// Arguments:
		//		hSoundHandle - Handle to sound.
		// Returns:
		//		LT_OK if successful.
		//		LT_ERROR on error.
		LTRESULT	(*KillSound)( HLTSOUND hSound );

		// Kills a looping sound.  Sound will continue to play until it reaches
		// the end, then remove itself.
		// Arguments:
		//		hSoundHandle - handle to client side sound.
		LTRESULT	(*KillSoundLoop)( HLTSOUND hSound );



	// Inter-object link manipulation.

		// If you want to hold on to an HOBJECT and get notification when the
		// object is removed from the world, you can create an inter-object link
		// between the two.  The owner will get MID_LINKBROKEN notification when 
		// the link is being broken (by either the owner or linked object being removed).
		// If a link between the two objects already exists, the function will not
		// create another link and return LT_OK.
		// An object cannot make a link to itself.  This will return LT_ERROR.
		LTRESULT	(*CreateInterObjectLink)(HOBJECT hOwner, HOBJECT hLinked);

		// Breaks an inter-object link between the owner and linked object
		// (if one exists..)  You can only break a link from the owner, since
		// the linked object doesn't even know it's linked to the owner..
		// Note: MID_LINKBROKEN will NOT be called.
		void	(*BreakInterObjectLink)(HOBJECT hOwner, HOBJECT hLinked);


	// Object manipulation.

		// Attaches hChild to hParent.  If pSocketName is set, it'll attach hChild to a 
		// specific node on hParent.
		// DE will automatically detach if you remove hParent,
		// but it will NOT automatically detach if you remove hChild.  If you remove the 
		// child without removing the attachment, the results are undefined.
		// Returns LT_OK, LT_NODENOTFOUND, or LT_INVALIDPARAMS.
		LTRESULT	(*CreateAttachment)(HOBJECT hParent, HOBJECT hChild, char *pSocketName, 
			LTVector *pOffset, LTRotation *pRotationOffset, HATTACHMENT *pAttachment);

		// Removes an attachment.  Note: an attachment becomes invalid when you remove the parent
		// so it'll crash if you call it with an attachment with a parent you've removed.
		LTRESULT	(*RemoveAttachment)(HATTACHMENT hAttachment);

		// Look for an attachment on the parent.  Returns LT_ERROR, LT_NOTFOUND,
		// or LT_OK if it found it.  hAttachment is set to NULL if there's an error.
		LTRESULT	(*FindAttachment)(HOBJECT hParent, HOBJECT hChild, HATTACHMENT *hAttachment);


		// Get/Set object color info (RGBA 0-1).
		// All objects default to (0,0,0,1)
		// For lights, this changes the light's color.
		// For models, this brightens a model's shading.
		LTBOOL	(*GetObjectColor)(HOBJECT hObject, float *r, float *g, float *b, float *a);
		LTBOOL	(*SetObjectColor)(HOBJECT hObject, float r, float g, float b, float a);

		// Get/Set an object's user-defined flags.
		uint32	(*GetObjectUserFlags)(HOBJECT hObj);
		LTRESULT	(*SetObjectUserFlags)(HOBJECT hObj, uint32 flags);

		// OBSOLETE: use the CommonLT ones.
		virtual float	GetObjectMass(HOBJECT hObj)=0;
		virtual void	SetObjectMass(HOBJECT hObj, float mass)=0;

		// OBSOLETE: Use PhysicsLT.
		virtual float	GetForceIgnoreLimit(HOBJECT hObj, float &limit)=0;
		virtual void	SetForceIgnoreLimit(HOBJECT hObj, float limit)=0;
		
		// Use this to iterate thru all the objects in the world.
		// Pass in NULL to start off with.  It'll return NULL when
		// you have iterated through all the objects.
		// This is generally a bad idea, but sometimes you have to.
		HOBJECT	(*GetNextObject)(HOBJECT hObj);

		// Same as GetNextObject, but this iterates over all the inactive objects.
		HOBJECT	(*GetNextInactiveObject)(HOBJECT hObj);
		
		// OBSOLETE.  Use the GetObjectName below.
		virtual char*	GetObjectName(HOBJECT hObject)=0;
		
		// Get an object's name.
		virtual LTRESULT	GetObjectName(HOBJECT hObject, char *pName, uint32 nameBufSize)=0;

		// Set an object's friction coefficient.
		virtual LTRESULT	SetFrictionCoefficient(HOBJECT hObj, float coeff)=0;
		
		// This is a counter that controls when each object gets its Update()
		// function called. This is set to 0.0001 when an object is created 
		// so by default, Update() gets called right away.
		void	(*SetNextUpdate)(HOBJECT hObj, LTFLOAT nextUpdate);

		// Sets the time which the engine will automatically deactivate an object.  If object
		// is currently autodeactivated, then this call will activate the object
		void	(*SetDeactivationTime)(HOBJECT hObj, LTFLOAT fDeactivationTime);

		// Activates any objects seen by this object
		void	(*PingObjects)(HOBJECT hObj);

		// Object data accessors.
		void	(*GetObjectPos)(HOBJECT hObj, LTVector *pos);
		void	(*SetObjectPos)(HOBJECT hObj, LTVector *pos);  // Exactly the same as calling Teleport().

		// Scale the object (only works on models and sprites).
		void	(*ScaleObject)(HOBJECT hObj, LTVector *pNewScale);
		LTRESULT	(*GetObjectScale)(HOBJECT hObj, LTVector *pScale);

		// OBSOLETE.  Use PhysicsLT::MoveObject.
		virtual LTRESULT MoveObject(HOBJECT hObj, LTVector *pNewPos)=0;

		// Teleports the object directly to the position.
		LTRESULT	(*TeleportObject)(HOBJECT hObj, LTVector *pNewPos);

		// OBSOLETE.  Use PhysicsLT::GetStandingOn.
		virtual LTRESULT	GetStandingOn(HOBJECT hObj, CollisionInfo *pInfo)=0;

		// Get information about the last collision.  Only valid during MID_TOUCHNOTIFY or MID_CRUSH messages.
		LTRESULT	(*GetLastCollision)(CollisionInfo *pInfo);

		// Get/Set the object's rotation.
		LTRESULT	(*GetObjectRotation)(HOBJECT hObj, LTRotation *pRotation);
		LTRESULT	(*SetObjectRotation)(HOBJECT hObj, LTRotation *pRotation);

		// This rotates the object to the new rotation with possible client side interpolation
		LTRESULT	(*RotateObject)(HOBJECT hObj, LTRotation *pRotation);

		// Tilt their acceleration to be along the plane they're standing on.
		void	(*TiltToPlane)(HOBJECT hObj, LTVector *pNormal);

		// OBSOLETE: Use ILTCommon::GetObjectFlags/SetObjectFlags.
		virtual uint32	GetObjectFlags(HOBJECT hObj)=0;
		virtual void	SetObjectFlags(HOBJECT hObj, uint32 flags)=0;

		// Get/set an object's net flags.  Net flags are a combination of NETFLAG_ defines.
		virtual LTRESULT GetNetFlags(HOBJECT hObj, uint32 &flags)=0;
		virtual LTRESULT SetNetFlags(HOBJECT hObj, uint32 flags)=0;

		// Get/Set the object's state.  State is one of the OBJSTATE_ defines above.
		void	(*SetObjectState)(HOBJECT hObj, int state);
		int		(*GetObjectState)(HOBJECT hObj);

		// OBSOLETE.  Use ILTPhysics.
		virtual void		GetObjectDims(HOBJECT hObj, LTVector *pNewDims)=0;
		virtual LTRESULT	SetObjectDims(HOBJECT hObj, LTVector *pNewDims)=0;
		virtual LTRESULT	SetObjectDims2(HOBJECT hObj, LTVector *pNewDims)=0;

		// OBSOLETE: use ILTCommon functions.
		virtual LTRESULT	GetVelocity(HOBJECT hObj, LTVector *pVel)=0;
		virtual LTRESULT	SetVelocity(HOBJECT hObj, LTVector *pVel)=0;
		virtual LTRESULT	GetAcceleration(HOBJECT hObj, LTVector *pAccel)=0;
		virtual LTRESULT	SetAcceleration(HOBJECT hObj, LTVector *pAccel)=0;

		// Get/Set blocking priority (defaults to 0).
		// See FAQ for a description of how this works.
		void	(*SetBlockingPriority)(HOBJECT hObj, uint8 pri);
		uint8	(*GetBlockingPriority)(HOBJECT hObj);


	// Sprite manipulation.

		// This clips the sprite on the poly.
		// Returns LT_OK or LT_ERROR if not a sprite.
		// Pass in INVALID_HPOLY to un-clip the sprite.
		LTRESULT	(*ClipSprite)(HOBJECT hObj, HPOLY hPoly);

	
	// Light manipulation.

		// Get/Set a light's color (RGB, 0.0f to 1.0f).
		// When you create a light, its color defaults to (0,0,0).
		
		// Note: a light's color is snapped to 256 different values, so if
		// you want to do any fancy interpolation or anything, you'll need
		// to store your own, higher precision, color values.
		
		// Note: this just calls GetObjectColor/SetObjectColor.
		void	(*GetLightColor)(HOBJECT hObj, float *r, float *g, float *b);
		void	(*SetLightColor)(HOBJECT hObj, float r, float g, float b);

		// Get/Set a light's radius.
		// When you create a light, its radius defaults to 100.
		float	(*GetLightRadius)(HOBJECT hObj);
		void	(*SetLightRadius)(HOBJECT hObj, float radius);

	
	// Model manipulation.

		// Iterate through the model's nodes.  Returns LT_FINISHED when there are no more.
		// hCurNode = INVALID_MODEL_NODE;
		// while(interface->GetNextModelNode(hModel, hCurNode, &hCurNode) == LT_OK)
		// { ... }
		LTRESULT	(*GetNextModelNode)(HOBJECT hObject, HMODELNODE hNode, HMODELNODE *pNext);

		// Get a model node's name.
		LTRESULT	(*GetModelNodeName)(HOBJECT hObject, HMODELNODE hNode, char *pName, uint32 maxLen);

		// Get a model's command string.
		LTRESULT	(*GetModelCommandString)(HOBJECT hObj, char *pStr, uint32 maxLen);

		// Hide/unhide a node on the model (they're all unhidden by default).
		// Returns LT_OK, LT_ERROR, LT_NOCHANGE, or LT_NODENOTFOUND.
		LTRESULT	(*SetModelNodeHideStatus)(HOBJECT hObj, char *pNodeName, LTBOOL bHidden);
		LTRESULT	(*GetModelNodeHideStatus)(HOBJECT hObj, char *pNodeName, /* out */LTBOOL *bHidden);
	


		// Get the animation name from an animation.
		// Returns LTNULL if the handle is invalid
		const char *(*GetAnimName)(HOBJECT hObject, HMODELANIM hAnim);

		// Get/Set the Playing state of the model.  The default state is FALSE.
		void	(*SetModelPlaying)(HOBJECT hObj, LTBOOL bPlaying);
		LTBOOL	(*GetModelPlaying)(HOBJECT hObj);

		// Get the model filenames.  You can pass in LTNULL for pFilename and pSkinName.
		// Returns LTFALSE if the object is not a model.
		// Initializes pFilename or pSkinName to zero length if the model doesn't have 
		// a filename or skin.
		LTBOOL	(*GetModelFilenames)(HOBJECT hObj, char *pFilename, int fileBufLen, char *pSkinName, int skinBufLen);

		// OBSOLETE: use ILTCommon::SetObjectFilenames.
		virtual LTRESULT SetModelFilenames(HOBJECT hObj, char *pFilename, char *pSkinName)=0;
		virtual LTRESULT SetObjectFilenames(HOBJECT hObj, char *pFilename, char *pSkinName)=0;

		// OBSOLETE: use ILTCommon.
		virtual LTRESULT GetModelAnimUserDims(HOBJECT hObj, LTVector *pDims, HMODELANIM hAnim)=0;


	// Container manipulation.
	
		// Gets the list of containers the object is inside.
		// pFlagList must be the same size as pContainerList.
		// Returns the number of elements in pList filled in.
		uint32	(*GetObjectContainers)(HOBJECT hObj, 
			HOBJECT *pContainerList, uint32 *pFlagList, uint32 maxListSize);

		// Gets the list of objects inside the container.
		// Returns the number of elements in pList filled in.
		uint32	(*GetContainedObjects)(HOBJECT hContainer, 
			HOBJECT *pObjectList, uint32 *pFlagList, uint32 maxListSize);

	
	// Surface manipulation.

		// OBSOLETE: use ILTCommon.
		virtual LTRESULT GetPolyTextureFlags(HPOLY hPoly, uint32 *pFlags)=0;


	// Save game

		// dwParam gets passed into MID_SAVEOBJECT as fData.
		// Flags is a SAVEOBJECTS_ define.
		LTRESULT (*SaveObjects)(char *pszSaveFileName, ObjectList *pList, uint32 dwParam, uint32 flags);

		// dwParam gets passed into MID_LOADOBJECT as fData.
		// Flags is a combination of RESTOREOBJECTS_ defines.
		LTRESULT (*RestoreObjects)( char *pszRestoreFileName, uint32 dwParam, uint32 flags );


	// Load world

		// Flags is a combination of the LOADWORLD_ flags.
		LTRESULT (*LoadWorld)(char *pszWorldFileName, uint32 flags);
		LTRESULT (*RunWorld)();


	// Network session manipulation

		// Updates the sessions' name.
		LTRESULT (*UpdateSessionName)(const char* sName);

		// Gets the sessions' name.
		LTRESULT (*GetSessionName)(char* sName, uint32 dwBufferSize);

		// Send a message to the standalone server app.  Returns LT_NOTFOUND
		// if there is no server app or if it isn't setup to receive the message.
		LTRESULT (*SendToServerApp)( char *pMsg, uint32 nLen );

		// Gets the tcp/ip address of the main driver if available.
		// If you're hosting a game, hostPort is filled in with the port you're hosting on.
		// If not, it's set to 0xFFFF.
		LTRESULT (*GetTcpIpAddress)(char* sAddress, uint32 dwBufferSize, uint16 &hostPort);


		// Get a list of files/directories in a directory (pass in "" to start with).
		// The list is a noncircular linked list with DNULL terminating it.
		FileEntry*	(*GetFileList)(char *pDirName);
		
		// Use FreeFileList when you're done with each list you get.
		void		(*FreeFileList)(FileEntry *pHead);

		virtual LTRESULT GetClientData(HCLIENT hClient, void *&pData, uint32 &nLength) = 0;

	};


#endif  // __ILTSERVER_H__
