
#ifndef __ILTCOMMON_H__
#define __ILTCOMMON_H__


	#include "ltbasedefs.h"


	class ILTMessage;
	class ILTTransform;
	class ILTModel;
	class CLTClient;


	class ILTCommon
	{
	friend class CLTServer;
	friend class CLTClient;
	
	public:

		virtual			~ILTCommon() {}

		ILTTransform*	GetTransformLT()	{return m_pTransformLT;}
		ILTModel*		GetModelLT()		{return m_pModelLT;}


	// Object stuff.
	public:

		// Change the filenames of a model or a sprite.
		// Only m_Filename and m_SkinNames in ObjectCreateStruct are used.
		virtual LTRESULT SetObjectFilenames(HOBJECT pObj, ObjectCreateStruct *pStruct)=0;

		// Get/Set the object's flag parameters.
		// You specify what flag type you're accessing and the value.
		virtual LTRESULT GetObjectFlags(
			const HOBJECT hObj,
			const ObjFlagType flagType,
			uint32 &dwFlags)=0;

		virtual LTRESULT SetObjectFlags(
			HOBJECT hObj,
			const ObjFlagType flagType,
			uint32 dwFlags)=0;

	
	// Attachments.
	public:

		// Get the parent and child of an attachment.
		// If either of the objects don't exist, LT_NOTINITIALIZED is returned.
		virtual LTRESULT	GetAttachmentObjects(HATTACHMENT hAttachment, HOBJECT &hParent, HOBJECT &hChild)=0;

		// Gets the objects attached to this object.  
		// Inputs:
		//		- inList points to the list to be filled in.
		//		- inListSize tells how large inList is.
		// Outputs:
		//		- outListSize is set to how many elements in inList were filled in.
		//		- outNumAttachments is set to how many attachments hObj has.  This number can be
		//		  larger that outListSize if inList can't hold all the attachments.
		virtual LTRESULT	GetAttachments(HLOCALOBJ hObj, HLOCALOBJ *inList, uint32 inListSize, 
			uint32 &outListSize, uint32 &outNumAttachments)=0;

		// Get the attachment transform (based off the parent object position, 
		// model socket, and attachment offset).
		// If bWorldSpace is DTRUE, then the transform is in world space.
		virtual LTRESULT	GetAttachmentTransform(HATTACHMENT hAttachment, LTransform &transform, 
			LTBOOL bWorldSpace)=0;

		// Basically ILTCommon::GetAttachmentTransform(WORLD) * ModelLT::GetNodeTransform(LOCAL)...
		virtual LTRESULT	GetAttachedModelNodeTransform(HATTACHMENT hAttachment, 
			HMODELNODE hNode, LTransform &transform)=0;

		// Basically ILTCommon::GetAttachmentTransform(WORLD) * ModelLT::GetSocketTransform(LOCAL)...
		virtual LTRESULT	GetAttachedModelSocketTransform(HATTACHMENT hAttachment, 
			HMODELSOCKET hSocket, LTransform &transform)=0;


	// Helpers.
	public:

		// Initialize the ConParse and call.  Fills in m_Args and m_nArgs with each set of tokens.  
		// Returns LT_FINISHED when done.  Sample loop:
		// parse.Init(pStr);
		// while(pEngine->Parse2(&parse) == LT_OK)
		// {
		//     .. process args ..
		// }
		virtual LTRESULT	Parse(ConParse *pParse)=0;

		// Tells you what type of object this is.
		virtual LTRESULT	GetObjectType(HOBJECT hObj, uint32 *type)=0;

		// Gets a model animation's user dimensions (what they set for dimensions in ModelEdit).
		virtual LTRESULT	GetModelAnimUserDims(HOBJECT hObject, LTVector *pDims, HMODELANIM hAnim)=0;

		// OBSOLETE: Use MathLT::GetRotationVectors.
		virtual LTRESULT	GetRotationVectors(LTRotation &rot, LTVector &up, LTVector &right, LTVector &forward)=0;

		// OBSOLETE: Use MathLT::SetupEuler.
		virtual LTRESULT	SetupEuler(LTRotation &rot, float pitch, float yaw, float roll)=0;

		// Start a message.  Send it with a SendTo function and free it by calling ILTMessage::Release.
		virtual LTRESULT	CreateMessage(ILTMessage* &pMsg)=0;


	// Geometry stuff.
	public:
		// Returns LT_NOTINWORLD if no world is loaded, or LT_INSIDE if the point
		// is in the world or LT_OUTSIDE if the point is not in the world.
		virtual LTRESULT	GetPointStatus(LTVector *pPoint)=0;

		// Get the shade (RGB, 0-255) at the point you specify.
		// Returns LT_NOTINWORLD if the point is outside the world.
		virtual LTRESULT	GetPointShade(LTVector *pPoint, LTVector *pColor)=0;
			
		// Get the texture flags from a poly.  Returns LT_OK
		// or LT_ERROR if no world is loaded or hPoly is invalid.
		virtual LTRESULT	GetPolyTextureFlags(HPOLY hPoly, uint32 *pFlags)=0;


	protected:

		// Some of the functions use these.
		ILTTransform	*m_pTransformLT;
		ILTModel		*m_pModelLT;
	};


#endif // __ILTCOMMON_H__
