//*********************************************************************************
//*********************************************************************************
// Project:		Lith Tech Font Manager
// Purpose:		A general font method for bitmap and system fonts
//*********************************************************************************
// File:		LithFontDefs.h
// Created:		April 7, 1999
// Updated:		October 6, 1999
// Author:		Andy Mattingly
//*********************************************************************************
//*********************************************************************************

#ifndef		_LITHTECH_FONT_DEFS_H_
#define		_LITHTECH_FONT_DEFS_H_

//*********************************************************************************

#ifdef _LITHTECH2
	#include "ltbasedefs.h"
#else
	#include "basedefs_de.h"
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
// ones will be off on the acsii chart.
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

//*********************************************************************************

#define		LTF_OFFSETS_FILENAME		"FontData.fnt"

//*********************************************************************************
// Defined flags for LithFontCreateStruct::nGroupFlags

#define		LTF_INCLUDE_SYMBOLS_1		0x01
#define		LTF_INCLUDE_NUMBERS			0x02
#define		LTF_INCLUDE_SYMBOLS_2		0x04
#define		LTF_INCLUDE_UPPERCASE		0x08
#define		LTF_INCLUDE_SYMBOLS_3		0x10
#define		LTF_INCLUDE_LOWERCASE		0x20
#define		LTF_INCLUDE_SYMBOLS_4		0x40
#define		LTF_INCLUDE_FIXED_END		0x80		// This extra flag calculates the font so the first transparent space
													// after a letter is where the width breaks (otherwise, it will take an
													// average of the transparent space between two letters and place the
													// break there)
#define		LTF_INCLUDE_SYMBOLS			0x55
#define		LTF_INCLUDE_LETTERS			0x28
#define		LTF_INCLUDE_ALL				0x7F
#define		LTF_INCLUDE_ALL_FIXED_END	0xFF

#define		LTF_INCLUDE_TOTAL_GROUPS	7

//*********************************************************************************
// Defined flags for LithFontDrawData::dwFlags

#define		LTF_DRAW_NORMAL				0x00000000	// *** Not used - just for reference ***
#define		LTF_DRAW_SOLID				0x00000001	// Draws the text in a solid color from hColor
#define		LTF_DRAW_FORMATTED			0x00000002	// Automatically formats the text to a certain width
#define		LTF_DRAW_TIMED				0x00000004	// Draws the text using the timed method
#define		LTF_DRAW_ALL				0x000000FF

#define		LTF_USE_NONE				0x00000000	// *** Not used - just for reference ***
#define		LTF_USE_OFFSETS				0x00000100	// Use the offsets specified in the draw data
#define		LTF_USE_CLIPRECT_X			0x00000200	// Use the X positions of the clipping rect
#define		LTF_USE_CLIPRECT_Y			0x00000400	// Use the Y positions of the clipping rect
#define		LTF_USE_CLIPRECT			0x00000600	// Use the X and Y positions of the clipping rect
#define		LTF_USE_EXCLUSIVE_CLIP		0x00000800	// Use the clip rect exclusively (if any part of a line is out of the rect, it won't be drawn)
#define		LTF_USE_ALL					0x0000FF00

#define		LTF_TIMED_NONE				0x00000000	// *** Not used - just for reference ***
#define		LTF_TIMED_LETTERS			0x00010000	// Use the letter delay time
#define		LTF_TIMED_LINES				0x00020000	// Use the line delay time
#define		LTF_TIMED_SCROLL			0x00040000	// Scroll each line
#define		LTF_TIMED_ALL				0x00FF0000

#define		LTF_EXTRA_NONE				0x00000000	// *** Not used - just for reference ***
#define		LTF_EXTRA_NEWLINE_UP		0x01000000	// Make new lines go up instead of down
#define		LTF_EXTRA_LOCKLAST			0x02000000	// Locks the last text line at the cursor position
#define		LTF_EXTRA_ALL				0xFF000000

//*********************************************************************************
// Defined values for LithFontDrawData::byJustify

#define		LTF_JUSTIFY_LEFT			0
#define		LTF_JUSTIFY_RIGHT			1
#define		LTF_JUSTIFY_CENTER			2

//*********************************************************************************
// Defined values for LithFont states

#define		LTF_STATE_NONE				0			// No state
#define		LTF_STATE_DRAW				1			// State draw (normal)
#define		LTF_STATE_DRAW_UPDATING		2			// State draw (timed); text updating
#define		LTF_STATE_DRAW_LINE_DELAY	3			// State draw (timed); text paused
#define		LTF_STATE_DRAW_SCROLLING	4			// Start draw (timed); text scrolling
#define		LTF_STATE_DRAW_FINISHED		5			// State draw (timed); text finished
#define		LTF_STATE_EXTENTS			6			// State extents

//*********************************************************************************
// General defines used internally by LithBitmapFont

#define		LTF_NUM_SYMBOLS_1			15
#define		LTF_NUM_NUMBERS				10
#define		LTF_NUM_SYMBOLS_2			7
#define		LTF_NUM_LETTERS				26
#define		LTF_NUM_SYMBOLS_3			6
#define		LTF_NUM_SYMBOLS_4			4

#define		LTF_NUM_TOTAL_CHARS			94

//*********************************************************************************
// General defines used internally by LithFontMgr

#define		LTF_MGR_MAX_FONTS			32
#define		LTF_MGR_MAX_CURSORS			64

//*********************************************************************************
// General defines used internally by all classes

#define		LTF_REF_NAME_SIZE			64
#define		LTF_MAX_STRING_SIZE			512
#define		LTF_OFFSETS_NAME_SIZE		256
#define		LTF_MAX_FORMAT_LINES		512

//*********************************************************************************
// Font create structure
//*********************************************************************************

struct LITHFONTCREATESTRUCT
{
	LITHFONTCREATESTRUCT::LITHFONTCREATESTRUCT();

	// General font information
	char		*szRefName;			// Reference name from each font (will be set automatically if not provided)

	// Variables needed to init a bitmap font
	char		*szFontBitmap;
	uint32		nGroupFlags;
	HLTCOLOR	hTransColor;
	LTBOOL		bChromaKey;
	uint8		nFixedPitch;

	// Variables needed to init a system font
	char		*szFontName;
	int			nWidth;
	int			nHeight;
	LTBOOL		bItalic;
	LTBOOL		bUnderline;
	LTBOOL		bBold;
};

//---------------------------------------------------------------------------------

inline LITHFONTCREATESTRUCT::LITHFONTCREATESTRUCT()
{
	memset(this, 0, sizeof(LITHFONTCREATESTRUCT));

	szFontName = "Arial";
	nWidth = 10;
	nHeight = 14;
}

//*********************************************************************************
// Font formatting data
//*********************************************************************************

struct LITHFONTFORMATDATA
{
	LITHFONTFORMATDATA::LITHFONTFORMATDATA();

	uint32		nNumChars;
	uint32		nNumLines;
	uint32		pIndex[LTF_MAX_FORMAT_LINES];
	uint32		pWidths[LTF_MAX_FORMAT_LINES];
	LTFLOAT		pTimes[LTF_MAX_FORMAT_LINES];
};

//---------------------------------------------------------------------------------

inline LITHFONTFORMATDATA::LITHFONTFORMATDATA()
{
	memset(this, 0, sizeof(LITHFONTFORMATDATA));
}

//*********************************************************************************
// Drawing data structure
//*********************************************************************************

struct LITHFONTDRAWDATA
{
	LITHFONTDRAWDATA::LITHFONTDRAWDATA();

	// Variables used to tell how to draw the string
	uint32		dwFlags;

	// Justification of the text
	uint8		byJustify;

	// Drawing offsets from the cursor position (if not from cursor, then top-left of surface)
	int			nXOffset;
	int			nYOffset;

	// Force the string to be reformatted, even if the string remains the same
	uint8		bForceFormat;

	// Formatting data
	uint32		dwFormatWidth;					// The width to format with (for word wrapping)
	LTRect		rcClip;							// The rectangle to clip the text onto

	// Spacing data
	int			nLetterSpace;					// Pixel offset for distance between letters
	int			nLineSpace;						// Pixel offset for distance between lines

	// Color and translucency information
	HLTCOLOR	hColor;							// The solid color to draw the font with
	LTFLOAT		fAlpha;							// The alpha value to use when blitting the font (direct to screen only)

	// Timed drawing variables
	LTFLOAT		fLetterDelay;					// Time it takes to draw one letter (0.1 would draw 10 letters a second)
	LTFLOAT		fLineDelay;						// Time the drawing will delay inbetween lines
	LTFLOAT		fLineScrollTime;				// Time it takes to scroll to the next line
	uint32		nNumWaitLines;					// Number of lines to wait until scrolling the text or locking the last line
};

//---------------------------------------------------------------------------------

inline LITHFONTDRAWDATA::LITHFONTDRAWDATA()
{
	memset(this, 0, sizeof(LITHFONTDRAWDATA));

	fAlpha = 1.0f;
	nNumWaitLines = 1;
}

//*********************************************************************************
// Drawing data structure
//*********************************************************************************

struct LITHFONTSAVEDATA
{
	LITHFONTSAVEDATA::LITHFONTSAVEDATA();

	// Times for drawing with the _TIMED method
	LTFLOAT		fStartDrawTime;						// Start time of drawing
	LTFLOAT		fTotalDrawTime;						// Time to draw the entire string

	// General formatting data for all drawing methods
	LITHFONTFORMATDATA		lfFD;

	// The previous string that was drawn
	char *		szPrevString;

	// The last method used by the font
	uint8		byLastState;

	// ***** System fonts only *****
	int			nLastLetterSpace;					// The last letter space value used
};

//---------------------------------------------------------------------------------

inline LITHFONTSAVEDATA::LITHFONTSAVEDATA()
{
	memset(this, 0, sizeof(LITHFONTSAVEDATA));
}

//*********************************************************************************
// Font offsets data structure
//*********************************************************************************

struct LITHFONTOFFSETDATA
{
	LITHFONTOFFSETDATA::LITHFONTOFFSETDATA();

	char		szRefName[LTF_OFFSETS_NAME_SIZE];
	uint32		pOffsets[LTF_NUM_TOTAL_CHARS + 1];
	uint32		pWidths[LTF_NUM_TOTAL_CHARS];
};

//---------------------------------------------------------------------------------

inline LITHFONTOFFSETDATA::LITHFONTOFFSETDATA()
{
	memset(this, 0, sizeof(LITHFONTOFFSETDATA));
}

//*********************************************************************************
// Cursor create structure
//*********************************************************************************

class LithFont;

struct LITHCURSORCREATESTRUCT
{
	LITHCURSORCREATESTRUCT::LITHCURSORCREATESTRUCT();

	// General cursor information
	char		*szRefName;			// Reference name from each cursor (will NOT be set automatically)

	// Initial values of the cursor variables
	LithFont	*pFont;
	HSURFACE	pDest;

	int			nXLoc;
	int			nYLoc;

	// Initial drawing data for this cursor
	LITHFONTDRAWDATA	lfDD;
};

//---------------------------------------------------------------------------------

inline LITHCURSORCREATESTRUCT::LITHCURSORCREATESTRUCT()
{
	memset(this, 0, sizeof(LITHCURSORCREATESTRUCT));
}

//*********************************************************************************

#endif
