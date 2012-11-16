#ifndef __ILT_CURSOR_H__
#define __ILT_CURSOR_H__


	#include "ltbasetypes.h"


	typedef enum
	{
		CM_None=0,
		CM_Hardware
	} CursorMode;


	class ILTCursorInst {

		public:
			ILTCursorInst() {};
			~ILTCursorInst() {};

		virtual LTRESULT IsValid() = 0;
		virtual void	SetData(const void *pData) = 0;
		virtual void	*GetData() = 0;
	};

	typedef ILTCursorInst *HLTCURSOR;

	class ILTCursor
	{
		public:

		// Enable/disable hardware cursor.
		virtual LTRESULT	SetCursorMode(CursorMode cMode) = 0;

		// Get current cursor mode.  Always returns LT_OK and always fills in cMode.
		virtual LTRESULT	GetCursorMode(CursorMode &cMode) = 0;

		// Returns LT_YES if a hardware cursor can be used, LT_NO otherwise.
		// Since we can't detect this, just return LT_YES for now.
		virtual LTRESULT	IsCursorModeAvailable(CursorMode cMode) = 0;

		// Set the current hardware cursor bitmap.  The bitmap comes from cshell.dll.
		virtual LTRESULT	LoadCursorBitmapResource(const char *pName, HLTCURSOR &hCursor) = 0;

		// Free a cursor.
		virtual LTRESULT	FreeCursor(const HLTCURSOR hCursor) = 0;

		// Set the current cursor.
		virtual LTRESULT	SetCursor(HLTCURSOR hCursor) = 0;

		// Check if an HLTCURSOR is a valid one; returns LT_YES or LT_NO
		virtual LTRESULT	IsValidCursor(HLTCURSOR hCursor) = 0;

		// Refresh cursor
		virtual LTRESULT	RefreshCursor() = 0;
	};


#endif // __ILT_CURSOR_H__