
#ifndef __IOBJECTPLUGIN_H__
#define __IOBJECTPLUGIN_H__

	
	#include "iltprelight.h"


	class IObjectPlugin
	{
	public:

		virtual ~IObjectPlugin() {}


	// Preprocessor plugin functions.
	public:

		// This hook gives the object a chance to create light animations in the preprocessor.
		// If you implement this function, you should always return LT_OK.
		virtual LTRESULT PreHook_Light(
			ILTPreLight *pInterface, 
			HPREOBJECT hObject) 
		{
			return LT_UNSUPPORTED;
		}

		// This hook gives the object a chance to return an array of strings to populate
		// a combobox edit control in DEdit. 
		// If you implement this function, you should always return LT_OK.
		virtual LTRESULT PreHook_EditStringList(
			const char* szRezPath,				// Path to the rez directory for the project (input)
			const char* szPropName,				// Name of the property (input)
			char** aszStrings,					// List of string pointers (output). Just strcpy into aszStrings[i] for string #i.
			uint32* pcStrings,					// How many strings were specified (output)
			const uint32 cMaxStrings,			// Max number of specifiable strings (input)
			const uint32 cMaxStringLength)		// Max length of any string in the list
		{
			return LT_UNSUPPORTED;
		}

		// This hook gives the object a chance to return either the model filename
		// to use to calculate the object's dims in DEdit, or the dims themself (if
		// szModelFilename[0] == '\0').  NOTE:  This is only called on PF_STATICLIST
		// properties...
		// If you implement this function, you should always return LT_OK.
		virtual LTRESULT PreHook_Dims(
			const char* szRezPath,		// Path to the rez directory for the project (input)
			const char* szPropValue,	// Value of the currently selected list item (input)
			char* szModelFilenameBuf,	// Buffer to copy model filename into (output)
			int	  nModelFilenameBufLen,	// Max buffer length (input)
			LTVector & vDims)			// Dims to use (instead of using a model file) (output).
		{
			return LT_UNSUPPORTED;
		}

	};


#endif  // __IOBJECTPLUGIN_H__
