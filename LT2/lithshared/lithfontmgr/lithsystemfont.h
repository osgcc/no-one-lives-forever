//*********************************************************************************
//*********************************************************************************
// Project:		Lith Tech Font Manager
// Purpose:		A general font method for bitmap and system fonts
//*********************************************************************************
// File:		LithSystemFont.h
// Created:		April 7, 1999
// Updated:		April 7, 1999
// Author:		Andy Mattingly
//*********************************************************************************
//*********************************************************************************

#ifndef		_LITHTECH_SYSTEM_FONT_H_
#define		_LITHTECH_SYSTEM_FONT_H_

//*********************************************************************************

#include "lithfont.h"

//*********************************************************************************

class LithSystemFont : public LithFont
{
	public:
		// Constructors and destructors
		LithSystemFont();
		~LithSystemFont();

		// Memory allocation and deallocation
		LTBOOL	Init(ILTClient *pClient, LITHFONTCREATESTRUCT *lfCS);
		void	Free();

		// Drawing / rendering
		void	Draw(HSURFACE pDest, char *szString, LITHFONTDRAWDATA *lfDD, int nX = 0, int nY = 0, LITHFONTSAVEDATA *lfSD = LTNULL);

		// Formatting information
		void	GetTextExtents(char *szString, LITHFONTDRAWDATA *lfDD, uint32 &x, uint32 &y, int index = -1);
		void	GetPositionFromIndex(char *szString, LITHFONTDRAWDATA *lfDD, int index, uint32 &x, uint32 &y);

		// State information
		uint8	GetState(LITHFONTSAVEDATA *lfSD = LTNULL);
		LTBOOL	IsChromaKeyed() {return LTFALSE;}
		LTBOOL	IsSystemFont()	{return LTTRUE;}

		// Manual drawing setup functions (without drawing)
		void	SetDrawData(HSURFACE pDest, char *szString, LITHFONTDRAWDATA *lfDD, int nX = 0, int nY = 0, LITHFONTSAVEDATA *lfSD = LTNULL, int index = -1);
		void	ClearDrawData();

	protected:
		// Font device and rendering surface
		HLTFONT		m_pFont;				// Handle to the engine font
		HSURFACE	m_pStringSurf;			// Surface to draw the string onto

		// Data needed to draw the correct characters
		LTRect				m_rRect;		// Rectangle to draw within the render surface

		// Temporary save data used when no save structure is passed in
		LITHFONTSAVEDATA	m_temp_lfSD;

		// Temp Drawing data for the drawing methods
		HSURFACE			m_pDest;
		uint32				m_nDestSurfWidth;
		uint32				m_nDestSurfHeight;
		char				*m_szString;
		LITHFONTDRAWDATA	*m_lfDD;
		LITHFONTSAVEDATA	*m_lfSD;
		LITHFONTFORMATDATA	*m_lfFD;		// Temporary format data for the string
		uint32				m_dwFlags;
		uint8				m_byJustify;
		int					m_nX;
		int					m_nY;
		int					m_nExtraLetterSpace;
		uint32				m_nWaitLines;

	protected:
		// Function to determine whether a line of text should be drawn or not within the given RECT
		LTBOOL	ClipFont(LTRect &rcFont);

		// Handle setting up the surface
		LTBOOL	SetupCompositeSurface();

	// The follow functions are meant for manual drawing...
	// Otherwise, they should only be used internally
	public:
		// Drawing data functions
		void	SetFormatData(uint32 nFormatWidth);

		// Drawing method functions
		void	Draw_Method_Normal();
		void	Draw_Method_Timed();
};

//*********************************************************************************

#endif