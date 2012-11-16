//*********************************************************************************
//*********************************************************************************
// Project:		Lith Tech Font Manager
// Purpose:		A general font method for bitmap and system fonts
//*********************************************************************************
// File:		LithBitmapFont.h
// Created:		April 7, 1999
// Updated:		July 15, 1999
// Author:		Andy Mattingly
//*********************************************************************************
//*********************************************************************************

#ifndef		_LITHTECH_BITMAP_FONT_H_
#define		_LITHTECH_BITMAP_FONT_H_

//*********************************************************************************

#include "lithfont.h"

//*********************************************************************************

class LithBitmapFont : public LithFont
{
	public:
		// Constructors and destructors
		LithBitmapFont();
		~LithBitmapFont();

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

		LTBOOL	IsChromaKeyed() {return m_bChromaKey;}
		LTBOOL	IsSystemFont()	{return LTFALSE;}

		// Manual drawing setup functions (without drawing)
		void	SetDrawData(HSURFACE pDest, char *szString, LITHFONTDRAWDATA *lfDD, int nX = 0, int nY = 0, LITHFONTSAVEDATA *lfSD = LTNULL, int index = -1);
		void	ClearDrawData();

	protected:
		// The surface of the font and which groups are included in the graphic
		HSURFACE	m_pFont;				// Bitmap which stores the font
		uint32		m_nSurfWidth;			// Width of the bitmap surface
		uint32		m_nSurfHeight;			// Height of the bitmap surface
		uint32		m_nGroupFlags;			// Flags for which groups are available
		uint32		m_nAvgWidth;			// Average character width

		// Transparency color data
		HLTCOLOR	m_hTransColor;			// Transparency color for the font
		LTBOOL		m_bChromaKey;			// TRUE is the font uses a transparent color
											// FALSEE is the font uses a blending modes

		// Data needed to choose the correct character to draw
		LITHFONTOFFSETDATA	m_lfOD;			// Offset data for the rectangle placement
		LTRect				m_rRect;		// Rectangle to draw from within the font surface

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

	private:
		// Functions to handle the offset data of the font
		LTBOOL	LoadOffsets();
		LTBOOL	CalcOffsets(uint8 nPitch = 0);
		uint32	FindOffset(uint32 nStartPos);
		LTBOOL	SaveOffsets();

		// Function to calculate extra needed values
		LTBOOL	CalcAvgWidth();

	protected:
		// Function to determine whether a line of text should be drawn or not within the given RECT
		LTBOOL	ClipFont(LTRect &rcFont);
	
	// The follow functions are meant for manual drawing...
	// Otherwise, they should only be used internally
	public:
		// Drawing data functions
		uint32	GetStringLength(uint32 nIndex1 = 0, uint32 nIndex2 = 0, LTBOOL bIgnorLastSpace = LTFALSE);
		void	SetFormatData(uint32 nFormatWidth);

		// Drawing method functions
		void	Draw_Method_Normal();
		void	Draw_Method_Timed();

		// Line drawing functions
		void	_Draw(int nX, int nY, uint32 nIndex1 = 0, uint32 nIndex2 = 0);
		void	_DrawSolid(int nX, int nY, uint32 nIndex1 = 0, uint32 nIndex2 = 0);
};

//*********************************************************************************

#endif