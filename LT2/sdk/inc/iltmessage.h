
// This file defines the ILTMessage class, which handles reading/writing of messages.

#ifndef __ILTMESSAGE_H__
#define __ILTMESSAGE_H__


	#include "ltbasedefs.h"
	#include <stdarg.h>


	#define OPERATOR_READ(type, fn) \
		ILTMessage& operator>>(type &val) {fn(val); return *this;}

	#define OPERATOR_WRITE(type, fn) \
		ILTMessage& operator<<(type &val) {fn(val); return *this;}


	// Message status flags.
	#define LMSTAT_READOVERFLOW		(1<<0)
	#define LMSTAT_WRITEOVERFLOW	(1<<1)


	class ILTMessage
	{
	public:

		// Call this to free the message.
		virtual LTRESULT		Release()=0;
		
		// Helpers..
		uint8		ReadByte()		{uint8 temp; ReadByteFL(temp); return temp;}
		uint16		ReadWord()		{uint16 temp; ReadWordFL(temp); return temp;}
		uint32		ReadDWord()		{uint32 temp; ReadDWordFL(temp); return temp;}
		float		ReadFloat()		{float temp; ReadFloatFL(temp); return temp;}
		HSTRING		ReadHString()	{HSTRING temp; ReadHStringFL(temp); return temp;}
		HOBJECT		ReadObject()	{HOBJECT temp; ReadObjectFL(temp); return temp;}
		LTVector	ReadVector()	{LTVector temp; ReadVectorFL(temp); return temp;}
		LTVector	ReadCompVector(){LTVector temp; ReadCompVectorFL(temp); return temp;}
		LTVector	ReadCompPos()	{LTVector temp; ReadCompPosFL(temp); return temp;}
		LTRotation	ReadRotation()	{LTRotation temp; ReadRotationFL(temp); return temp;}
		LTRotation	ReadCompRotation()	{LTRotation temp; ReadCompRotationFL(temp); return temp;}
		ILTMessage*	ReadMessage()	{ILTMessage *pMsg; ReadMessageFL(pMsg); return pMsg;}
		OPERATOR_READ(uint8, ReadByteFL)
		OPERATOR_READ(uint16, ReadWordFL)
		OPERATOR_READ(uint32, ReadDWordFL)
		OPERATOR_READ(float, ReadFloatFL)
		OPERATOR_READ(LTVector, ReadVectorFL)
		OPERATOR_READ(LTRotation, ReadRotationFL)
		OPERATOR_READ(HOBJECT, ReadObjectFL)
		OPERATOR_WRITE(uint8, WriteByte)
		OPERATOR_WRITE(uint16, WriteWord)
		OPERATOR_WRITE(uint32, WriteDWord)
		OPERATOR_WRITE(float, WriteFloat)
		OPERATOR_WRITE(LTVector, WriteVector)
		OPERATOR_WRITE(LTRotation, WriteRotation)
		OPERATOR_WRITE(HOBJECT, WriteObject)

		// FL means full.. most people will use the simpler versions above.
		virtual LTRESULT	ReadByteFL(uint8 &val)=0;
		virtual LTRESULT	ReadWordFL(uint16 &val)=0;
		virtual LTRESULT	ReadDWordFL(uint32 &val)=0;
		virtual LTRESULT	ReadFloatFL(float &val)=0;
		virtual LTRESULT	ReadStringFL(char *pData, uint32 maxBytes)=0;
		virtual LTRESULT	ReadHStringFL(HSTRING &hString)=0;
		
		// This reads an HSTRING into the string buffer (this is more allocation friendly).
		// Note: if msgBufSize > 0, the string is guaranteed to be null terminated even if an
		// error is returned.
		virtual LTRESULT	ReadHStringAsStringFL(char *pMsg, uint32 msgBufSize)=0;
		
		virtual LTRESULT	ReadRawFL(void *pData, uint32 len)=0;
		virtual LTRESULT	ReadVectorFL(LTVector &vec)=0;
		virtual LTRESULT	ReadCompVectorFL(LTVector &vec)=0;
		virtual LTRESULT	ReadCompPosFL(LTVector &vec)=0;
		virtual LTRESULT	ReadRotationFL(LTRotation &rot)=0;
		virtual LTRESULT	ReadCompRotationFL(LTRotation &rot)=0;
		virtual LTRESULT	ReadMessageFL(ILTMessage* &pMsg)=0;

		// Note: this could very well return NULL if the object sent doesn't still exist.
		// The object will NOT be there if you send a message with the object in it right
		// after creating it.  The server must process at least one update on an object
		// before you can send it to the client.
		virtual LTRESULT	ReadObjectFL(HOBJECT &hObj)=0;
			
		virtual LTRESULT	WriteByte(uint8 val)=0;
		virtual LTRESULT	WriteWord(uint16 val)=0;
		virtual LTRESULT	WriteDWord(uint32 val)=0;
		virtual LTRESULT	WriteFloat(float val)=0;
		virtual LTRESULT	WriteString(char *pData)=0;
		virtual LTRESULT	WriteVector(LTVector &vec)=0;			// 12 bytes
		virtual LTRESULT	WriteCompVector(LTVector &vec)=0;		// 9 bytes
		virtual LTRESULT	WriteCompPos(LTVector &vec)=0;			// 6 bytes
		virtual LTRESULT	WriteRotation(LTRotation &rot)=0;		// 16 bytes
		virtual LTRESULT	WriteCompRotation(LTRotation &rot)=0;	// 3-6 bytes
		virtual LTRESULT	WriteRaw(void *pData, uint32 len)=0;
		virtual LTRESULT	WriteMessage(ILTMessage &msg)=0;
		virtual LTRESULT	WriteHString(HSTRING hString)=0;
		
		// Write a string formatted from a string resource (from cres.dll or sres.dll).
		virtual LTRESULT	WriteHStringFormatted(int messageCode, ...)=0;
		virtual LTRESULT	WriteHStringArgList(int messageCode, va_list *pList)=0;

		// Writes an HSTRING to the message (but saves an allocation of an HSTRING).
		virtual LTRESULT	WriteStringAsHString(char *pStr)=0;

		// Some notes about this function.  This only works for objects created by the
		// server.  If you put an object in here created by the client, then the receiver
		// will get NULL out.  If the object has been removed on the server before this 
		// message gets read, the receiver will wind up with a different object handle, 
		// so be careful!
		virtual LTRESULT	WriteObject(HOBJECT hObj)=0;

		// Reset the read position.  It automatically resets when you read to the end of the
		// message.
		virtual LTRESULT	ResetPos()=0;

		// As you read/write to the message, you can check these flags to see if there was an error.
		// flags will be filled in with a combination of the LMSTAT_ flags above.
		virtual LTRESULT	GetStatus(uint32 &flags)=0;
	};


#endif // __ILTMESSAGE_H__
