
#ifndef __ILTSTREAM_H__
#define __ILTSTREAM_H__

	#include "ltbasetypes.h"

	// Helper macro to read/write data if your stream pointer is called pStream.
	#define STREAM_READ(_x_) pStream->Read(&(_x_), sizeof(_x_));
	#define STREAM_WRITE(_x_) pStream->Write(&(_x_), sizeof(_x_));


	#define WRITESTREAM_DEFAULT 0xFFFFFFFF
	

	class ILTStream
	{
	protected:
		
		virtual				~ILTStream() {}
	
	public:

		// Call this when you're done with it (same as deleting it).
		virtual void		Release()=0;

		// Read in data.  Returns LT_ERROR if you read past the end.  ALWAYS fills in
		// pData with 0's if it returns an error so you can safely read everything
		// in without checking the return value every time and check ErrorStatus() at the end.
		virtual LTRESULT	Read(void *pData, unsigned long size)=0;
		virtual LTRESULT	ReadString(char *pStr, unsigned long maxBytes)=0;
		
		// LT_OK = no errors, otherwise an error occured.
		virtual LTRESULT	ErrorStatus()=0;
		
		virtual LTRESULT	SeekTo(unsigned long offset)=0;
		virtual LTRESULT	GetPos(unsigned long *offset)=0;
		virtual LTRESULT	GetLen(unsigned long *len)=0;

		// Reads the data in dsSource and writes it to this stream.
		// Returns LT_ERROR if either stream has an ErrorStatus() != LT_OK or
		// returns an error from Read or Write.
		// You can specify the range of dsSource to read, or leave it at 
		// WRITESTREAM_DEFAULT and it will write ALL or dsSource.
		virtual LTRESULT	WriteStream(ILTStream &dsSource, 
			unsigned long dwMin=WRITESTREAM_DEFAULT,
			unsigned long dwMax=WRITESTREAM_DEFAULT)=0;

		// Helpers to make it easy..
		unsigned long		GetPos()
		{
			unsigned long pos;
			GetPos(&pos);
			return pos;
		}

		unsigned long		GetLen()
		{
			unsigned long len;
			GetLen(&len);
			return len;
		}

		template<class T>
		ILTStream&			operator>>(T &toRead) 
		{
			LTStream_Read(this, toRead);
			return *this;
		}

	// Only enabled in writeable streams.
	public:
		
		virtual LTRESULT	Write(const void *pData, unsigned long size)=0;
		virtual LTRESULT	WriteString(char *pStr)=0;

		template<class T>
		ILTStream&			WriteVal(const T toWrite) {Write(&toWrite, sizeof(toWrite)); return *this;}

		template<class T>
		ILTStream&			operator<<(T &toWrite) 
		{
			LTStream_Write(this, toWrite);
			return *this;
		}
	};


	// Functions for all the default types.
	#define READWRITE_FN(type) \
		inline void LTStream_Read(ILTStream *pStream, type &val) {pStream->Read(&val, sizeof(val));}\
		inline void LTStream_Write(ILTStream *pStream, const type &val) {pStream->Write(&val, sizeof(val));}


	READWRITE_FN(char);
	READWRITE_FN(unsigned char);
	READWRITE_FN(short);
	READWRITE_FN(unsigned short);
	READWRITE_FN(int);
	READWRITE_FN(unsigned int);
	READWRITE_FN(long);
	READWRITE_FN(unsigned long);
	READWRITE_FN(float);
	READWRITE_FN(double);


#endif  // __ILTSTREAM_H__