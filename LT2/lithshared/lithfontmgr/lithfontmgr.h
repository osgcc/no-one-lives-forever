//*********************************************************************************
//*********************************************************************************
// Project:		Lith Tech Font Manager
// Purpose:		A general font method for bitmap and system fonts
//*********************************************************************************
// File:		LithFontMgr.h
// Created:		April 8, 1999
// Updated:		April 8, 1999
// Author:		Andy Mattingly
//*********************************************************************************
//*********************************************************************************

#ifndef		_LITHTECH_FONT_MGR_H_
#define		_LITHTECH_FONT_MGR_H_

//*********************************************************************************

#include "..\lithfontmgr\lithfontdefs.h"
#include "..\lithfontmgr\lithbitmapfont.h"
#include "..\lithfontmgr\lithsystemfont.h"
#include "..\lithfontmgr\lithcursor.h"


#ifndef NO_PRAGMA_LIBS
	#ifdef _LITHTECH2
		#ifdef _DEBUG				 
			#pragma comment (lib, "\\proj\\libs\\debug\\LithFontMgr_LT2.lib")
		#else
			#pragma comment (lib, "\\proj\\libs\\release\\LithFontMgr_LT2.lib")
		#endif
	#else
		#ifdef _DEBUG				 
			#pragma comment (lib, "\\proj\\libs\\debug\\LithFontMgr.lib")
		#else
			#pragma comment (lib, "\\proj\\libs\\release\\LithFontMgr.lib")
		#endif
	#endif
#endif

//*********************************************************************************

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
// ***** SPECIAL NOTE ABOUT BITMAP FONTS!!! *****
//
// Be careful not to have any vertical lines of transparency for characters within
// the font itself.  The only blank lines should be between the individual characters
// so that the calculation of the widths can be accurate.  Otherwise, you'll end
// up with characters that look like 'half letters' and any characters after the bad
// ones will be off on the ascii chart.
//
// Pay special attention to characters like " because of it's inherent blank space.
// LithFontMgr WILL count this as two characters unless you fill in that gap. A creative
// way to do this would be just to angle the two lines so there's no straight vertical
// space.   If you notice weirdness with the font letters... check for this problem
// before anything else.
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

//*********************************************************************************

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
// ***** SPECIAL NOTE ABOUT LITH CURSORS!!! *****
//
// It is recommended that you use one cursor per string when drawing simutanious lines
// at once. This is due to the fact that the cursor stores data about how the string
// is currently being drawn... so if you use the same cursor to draw multiple strings
// in the same frame, you may lose data from one string to the next.  Plus, there are
// some enhancements that speed up the formatting of the string data when you use one
// cursor per string.
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
// ***** LITHCURSORCREATESTRUCT *****
//
// Here are the members of LITHCURSORCREATESTRUCT:
//
// char			*szRefName;		// Reference name from each cursor (will NOT be set automatically)
// LithFont		*pFont;			// The font to use when drawing the string
// HSURFACE		pDest;			// The surface to draw the string onto
// int			nXLoc;			// X location of the cursor on the destination surface
// int			nYLoc;			// Y location of the cursor on the destination surface
// LITHFONTDRAWDATA	lfDD;		// Initial drawing data for this cursor
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

//*********************************************************************************
// Use these functions for general purpose creating and deleting fonts and cursors

extern LithFont*	CreateLithFont(ILTClient *pClient, LITHFONTCREATESTRUCT *lfCS, LTBOOL bEnglish = LTTRUE);
extern void			FreeLithFont(LithFont* lf);
extern LithCursor*	CreateLithCursor(ILTClient *pClient, LITHCURSORCREATESTRUCT *lcCS);
extern void			FreeLithCursor(LithCursor* lc);

//*********************************************************************************
// Use this class if you want the fonts and cursors managed for you and accessible
// by their reference names or indexes

class LithFontMgr
{
	public:
		// Constructors and destructors
		LithFontMgr();
		~LithFontMgr();

		// Initialization and deallocation functions
		void	Init(ILTClient *pClient, LTBOOL bEnglish);
		void	Free();

		// Font functions
		LithFont*	AddFont(LITHFONTCREATESTRUCT *lfCS, int nIndex = -1);	// -1 places the font at the first available slot
		LTBOOL		DeleteFont(int nIndex);
		LTBOOL		DeleteFont(char *szName);

		LithFont*	Font(int nIndex);
		LithFont*	Font(char *szName);

		// Cursor functions
		LithCursor*	AddCursor(LITHCURSORCREATESTRUCT *lcCS, int nIndex = -1);// -1 places the cursor at the first available slot
		LTBOOL		DeleteCursor(int nIndex);
		LTBOOL		DeleteCursor(char *szName);

		LithCursor*	Cursor(int nIndex);
		LithCursor*	Cursor(char *szName);

		// Easy drawing functions
		LTBOOL		Draw(int nCursor, HSTRING szString);
		LTBOOL		Draw(char *szCursor, HSTRING szString);
		LTBOOL		Draw(int nCursor, int nFont, HSTRING szString);
		LTBOOL		Draw(char *szCursor, char *szFont, HSTRING szString);

	protected:
		// Client data
		ILTClient		*m_pClient;

		// Font data
		LithFont		*m_pFontList[LTF_MGR_MAX_FONTS];

		// Cursor data
		LithCursor		*m_pCursorList[LTF_MGR_MAX_CURSORS];

		// FontMgr data
		LTBOOL			m_bEnglish;
};

//*********************************************************************************

#endif