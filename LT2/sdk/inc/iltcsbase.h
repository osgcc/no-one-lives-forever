
// Base class for ILTClient and ILTServer.  This is just here for b/w compatibility.

#ifndef __ILTCSBASE_H__
#define __ILTCSBASE_H__


	#include "ltbasedefs.h"
	#include "iltmath.h"
	#include "iltcommon.h"

	// Forward declarations of base interface classes
	class ILTPhysics;
	class ILTModel;
	class ILTTransform;
	class ILTLightAnim;
	class ILTSoundMgr;

	class ILTCSBase
	{
	public:

		inline ILTMath*		GetMathLT()	{return &m_MathLT;}
		inline ILTCommon*	Common()	{return m_pCommonLT;}
		inline ILTPhysics*	Physics()	{return m_pPhysicsLT;}
		inline ILTModel*	GetModelLT()	{return m_pModelLT;}
		inline ILTTransform*	GetTransformLT()	{return m_pTransformLT;}
		inline ILTLightAnim*	GetLightAnimLT()	{return m_pLightAnimLT;}
		inline ILTSoundMgr*		SoundMgr()	{return m_pSoundMgr;}

	
	// Messaging functions.  ALL these functions are obsolete.  Use the LMessage functions.
	public:
				
		// Start a data message for writing.  A data message is used to write an HMESSAGEWRITE into another
		// already open HMESSAGEWRITE.  When the data message is complete, first call
		// WriteToMessageHMessageWrite to write it into the other HMESSAGE, then call EndMessageHMessageWrite to free it.
		virtual HMESSAGEWRITE	StartHMessageWrite()=0;
		
		virtual LTRESULT	WriteToMessageFloat(HMESSAGEWRITE hMessage, float val);
		virtual LTRESULT	WriteToMessageByte(HMESSAGEWRITE hMessage, uint8 val);
		virtual LTRESULT	WriteToMessageWord(HMESSAGEWRITE hMessage, uint16 val);
		virtual LTRESULT	WriteToMessageDWord(HMESSAGEWRITE hMessage, uint32 val);
		virtual LTRESULT	WriteToMessageString(HMESSAGEWRITE hMessage, char *pStr);
		virtual LTRESULT	WriteToMessageVector(HMESSAGEWRITE hMessage, LTVector *pVal); // 12 bytes
		virtual LTRESULT	WriteToMessageCompVector(HMESSAGEWRITE hMessage, LTVector *pVal); // 9 bytes
		virtual LTRESULT	WriteToMessageCompPosition(HMESSAGEWRITE hMessage, LTVector *pVal); // 7 bytes
		virtual LTRESULT	WriteToMessageRotation(HMESSAGEWRITE hMessage, LTRotation *pVal);
		virtual LTRESULT	WriteToMessageHString(HMESSAGEWRITE hMessage, HSTRING hString);

		// Writes a HMESSAGEWRITE into an already opened HMESSAGEWRITE.
		// Inputs:
		//		hMessage -		HMESSAGEWRITE written to.
		//		hDataMessage -	HMESSAGEWRITE written from.
		virtual LTRESULT	WriteToMessageHMessageWrite(HMESSAGEWRITE hMessage, HMESSAGEWRITE hDataMessage);
		
		// Writes a HMESSAGEREAD into an already opened HMESSAGEWRITE.
		// Inputs:
		//		hMessage -		HMESSAGEWRITE written to.
		//		hDataMessage -	HMESSAGEREAD written from.
		virtual LTRESULT	WriteToMessageHMessageRead(HMESSAGEWRITE hMessage, HMESSAGEREAD hDataMessage);
		
		// Helper so you don't have to FormatString and FreeString..
		virtual LTRESULT	WriteToMessageFormattedHString(HMESSAGEWRITE hMessage, int messageCode, ...);

		// Note: you can't send object references to the client yet, so the client can't
		// even read object references.
		// You can't write object references in a HMESSAGEWRITE passed in MID_SAVEOBJECT.
		virtual LTRESULT	WriteToMessageObject(HMESSAGEWRITE hMessage, HOBJECT hObj);	

		// Use this only while saving objects (inside MID_SAVEOBJECT).
		virtual LTRESULT	WriteToLoadSaveMessageObject(HMESSAGEWRITE hMessage, HOBJECT hObject);
		

		// When your OnMessage function is called, use the handle you're given
		// to read the message data with these functions.
		virtual float		ReadFromMessageFloat(HMESSAGEREAD hMessage);
		virtual uint8		ReadFromMessageByte(HMESSAGEREAD hMessage);
		virtual uint16		ReadFromMessageWord(HMESSAGEREAD hMessage);
		virtual uint32		ReadFromMessageDWord(HMESSAGEREAD hMessage);
		virtual void		ReadFromMessageVector(HMESSAGEREAD hMessage, LTVector *pVal); // 12 bytes
		virtual void		ReadFromMessageCompVector(HMESSAGEREAD hMessage, LTVector *pVal); // 9 bytes
		virtual void		ReadFromMessageCompPosition(HMESSAGEREAD hMessage, LTVector *pVal); // 7 bytes
		virtual void		ReadFromMessageRotation(HMESSAGEREAD hMessage, LTRotation *pVal);
		virtual HOBJECT		ReadFromMessageObject(HMESSAGEREAD hMessage);
		virtual HSTRING		ReadFromMessageHString(HMESSAGEREAD hMessage);
		
		// Use this only while loading objects (inside MID_LOADOBJECT).
		virtual LTRESULT	ReadFromLoadSaveMessageObject(HMESSAGEREAD hMessage, HOBJECT *hObject);

		// Reads a data message from an HMESSAGEREAD.  The returned HMESSAGEREAD can then be used in the
		// ReadFromMessageX functions.  This will create a new HMESSAGEREAD which must be
		// freed with a call to EndHMessageRead().
		// Inputs:
		//		hMessage -		HMESSAGEREAD read from.
		virtual HMESSAGEREAD	ReadFromMessageHMessageRead(HMESSAGEREAD hMessage);

		// Frees a HMESSAGEREAD created from a call of ReadFromMessageHMessageRead.
		virtual void		EndHMessageRead(HMESSAGEREAD hMessage);

		// Frees a HMESSAGEWRITE created from a call of StartHMessageWrite.
		virtual void		EndHMessageWrite(HMESSAGEWRITE hMessage);
		
		// Reset reading (so you can read the message again).
		// This is useful if you read out of a message and subclasses
		// will be reading out of it.  Note: the message will AUTOMATICALLY
		// reset when you hit the end, so you won't need this in most cases.
		virtual void		ResetRead(HMESSAGEREAD hRead);


		// Get an animation index from a model.
		// Returns -1 if the animation doesn't exist (or if the object isn't a model).
		virtual HMODELANIM	GetAnimIndex(HOBJECT hObj, char *pAnimName) = 0;

		// If the object is a model, this sets its current animation.
		virtual void	SetModelAnimation(HOBJECT hObj, HMODELANIM hAnim) = 0;
		// Returns the animation the model is currently on.  (HMODELANIM)-1 if none.
		virtual HMODELANIM	GetModelAnimation(HOBJECT hObj) = 0;

		// Get/Set the looping state of the model.  The default state is TRUE.
		virtual void	SetModelLooping(HOBJECT hObj, LTBOOL bLoop) = 0;
		virtual LTBOOL	GetModelLooping(HOBJECT hObj) = 0;

		// Starts the current animation over.
		virtual LTRESULT	ResetModelAnimation(HOBJECT hObj) = 0;

		// Tells what the playback state of the model is (a combination of the
		// MS_ bits defined in basedefs_de.h).
		virtual uint32	GetModelPlaybackState(HOBJECT hObj) = 0;

		// Free unused model files
		virtual LTRESULT	FreeUnusedModels() = 0;

		// A better BPrint.. prints right to the console (doesn't do any network stuff) and 
		// doesn't matter if you're connected yet.
		virtual void	CPrint(char *pMsg, ...) = 0;

		// Find out what containers contain the given point.
		// Returns the number of containers filled in.
		virtual uint32	GetPointContainers(LTVector *pPoint, HOBJECT *pList, uint32 maxListSize) = 0;

		// Get the container's container code (can only be set in the ObjectCreateStruct during creation).
		// Returns LTFALSE if the object isn't a container.
		virtual LTBOOL	GetContainerCode(HOBJECT hObj, uint16 *pCode) = 0;

		// Open a file up.  Pass in the relative filename.
		// Free the file by calling DStream::Release().
		virtual LTRESULT OpenFile(char *pFilename, ILTStream **pStream) = 0;

		// Copies a file.  This function is useful for copying files out of the
		// rez file to a temporary file, so you can do special operations on it like
		// LoadLibrary.
		virtual LTRESULT CopyFile( const char *pszSourceFile, const char *pszDestFile ) = 0;

	// String functions.  Strings are reference counted objects that cannot
	// be manipulated.  When you create one with FormatString or CreateString,
	// the reference count is 1.  When you copy a string with CopyString, the
	// reference count is incremented.  When you free one with FreeString,
	// it decrements the reference count.. when the reference count goes to
	// zero, it deletes the string.  If you forget to free up any strings, 
	// LithTech will spit out a message telling you about it..

		// In Windows, messageCode comes from your resource DLL.  The messages
		// need to be formatted with %1!s! %2!s! (the number is the argument 
		// number and the !s! says its a string).  You can also use !f! and !d!
		// for floating point and whole number.
		virtual HSTRING	FormatString(int messageCode, ...) = 0;
		
		// Copy a string.. much more efficient than CreateString().
		virtual HSTRING	CopyString(HSTRING hString) = 0;
		virtual HSTRING	CreateString(char *pString) = 0;
		virtual void	FreeString(HSTRING hString) = 0;

		virtual LTBOOL	CompareStrings(HSTRING hString1, HSTRING hString2) = 0;
		virtual LTBOOL	CompareStringsUpper(HSTRING hString1, HSTRING hString2) = 0;

		// Get the string's data.. you really should only use this for strings
		// that you stored off and want to pass to the engine for a filename 
		// or something..  Most strings could be in some format other than ANSI.
		virtual char*	GetStringData(HSTRING hString) = 0;


		// Get the floating point value of a console variable.  If the hVar is
		// NULL, then it returns 0.
		virtual float GetVarValueFloat(HCONSOLEVAR hVar) = 0;

		// Get the string value of a console variable.  If the hVar is
		// NULL, then it returns NULL.
		virtual char* GetVarValueString(HCONSOLEVAR hVar) = 0;

		// Returns the current time, in seconds, since the shell started
		virtual LTFLOAT	GetTime() = 0;
		
		// Returns the time since the last shell update.
		virtual LTFLOAT	GetFrameTime() = 0;

		// Remove the object from the world.  Note: the object won't be removed
		// or deleted until the end of the frame.
		virtual LTRESULT RemoveObject(HOBJECT hObj) = 0;

		// OBSOLETE: Use CommonLT version.
		uint32	GetObjectType(HOBJECT hObj)		{uint32 temp; Common()->GetObjectType(hObj, &temp); return temp;}

	// OBSOLETE: Use MathLT functions.  NOTE: PARAMETER ORDERINGS ARE DIFFERENT
	// FOR SOME OF THE FUNCTIONS.
	public:

		virtual LTRESULT	GetRotationVectors(LTRotation *pRotation, 
			LTVector *pUp, LTVector *pRight, LTVector *pForward);
		virtual void		GetRotationVectorsFromMatrix(LTMatrix *pMat, 
			LTVector *pUp, LTVector *pRight, LTVector *pForward);
		virtual void		RotateAroundAxis(LTRotation *pRotation, LTVector *pAxis, float amount);
		virtual void		EulerRotateX(LTRotation *pRotation, float amount);
		virtual void		EulerRotateY(LTRotation *pRotation, float amount);
		virtual void		EulerRotateZ(LTRotation *pRotation, float amount);
		virtual void		AlignRotation(LTRotation *pRotation, LTVector *pVector, LTVector *pUp);
		virtual LTRESULT	SetupEuler(LTRotation *pRotation, float pitch, float yaw, float roll);
		virtual LTRESULT	InterpolateRotation(LTRotation *pDest, LTRotation *pRot1, LTRotation *pRot2, float t);
		virtual void		SetupTransformationMatrix( LTMatrix *pMat, LTVector *pTranslation, LTRotation *pRotation );
		virtual void		SetupTranslationMatrix( LTMatrix *pMat, LTVector *pTranslation );
		virtual void		SetupRotationMatrix(LTMatrix *pMat, LTRotation *pRot);
		virtual void		SetupTranslationFromMatrix( LTVector *pTranslation, LTMatrix *pMat );
		virtual void		SetupRotationFromMatrix(LTRotation *pRot, LTMatrix *pMat);
		virtual void		SetupRotationAroundPoint(LTMatrix *pMat, LTRotation *pRot, LTVector *pPoint);


	protected:

		ILTMath		m_MathLT;
		ILTCommon	*m_pCommonLT;
		ILTPhysics	*m_pPhysicsLT;
		ILTModel	*m_pModelLT;
		ILTTransform	*m_pTransformLT;
		ILTLightAnim	*m_pLightAnimLT;
		ILTSoundMgr	*m_pSoundMgr;
	};


#endif // __ILTCSBASE_H__
