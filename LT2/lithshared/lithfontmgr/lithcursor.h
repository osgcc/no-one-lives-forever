//*********************************************************************************
//*********************************************************************************
// Project:		Lith Tech Font Manager
// Purpose:		A general font method for bitmap and system fonts
//*********************************************************************************
// File:		LithCursor.h
// Created:		April 8, 1999
// Updated:		October 6, 1999
// Author:		Andy Mattingly
//*********************************************************************************
//*********************************************************************************

#ifndef		_LITHTECH_CURSOR_H_
#define		_LITHTECH_CURSOR_H_

//*********************************************************************************

#include "lithfont.h"

//*********************************************************************************

class LithCursor
{
	public:
		// Constructors and destructors
		LithCursor();
		~LithCursor();

		// Memory allocation and deallocation
		LTBOOL Init(ILTClient *pClient, LITHCURSORCREATESTRUCT *lcCS);
		void Free();

		// Data setting and retrieving functions
		void		SetRefName(char *szName)	{ strcpy(m_szRefName, szName); }
		char*		GetRefName()				{ return m_szRefName; }

		void		SetFont(LithFont *pFont)	{ m_pFont = pFont; }
		LithFont*	GetFont()					{ return m_pFont; }

		void		SetDest(HSURFACE pDest)		{ m_pDest = pDest; }
		HSURFACE	GetDest()					{ return m_pDest; }

		void		SetDrawData(LITHFONTDRAWDATA *lfDD)	{ if(lfDD) memcpy(&m_lfDD, lfDD, sizeof(LITHFONTDRAWDATA)); }
		LITHFONTDRAWDATA*	GetDrawData()				{ return &m_lfDD; }
		LITHFONTDRAWDATA&	DrawData()					{ return m_lfDD; }

		uint8		GetState();

		// Cursor movement functions
		void		SetLoc(int x, int y)		{ m_nX = x; m_nY = y; }
		void		GetLoc(int &x, int &y)		{ x = m_nX; y = m_nY; }
		void		ResetLoc()					{ m_nX = 0; m_nY = 0; }

		void		PrevLine()	{ if(m_pFont) m_nY -= (int)(m_pFont->Height() + m_lfDD.nLineSpace); }
		void		NextLine()	{ if(m_pFont) m_nY += (int)(m_pFont->Height() + m_lfDD.nLineSpace); }

		// Drawing functions
		void		Draw(char *szString, LITHFONTDRAWDATA *lfDD = LTNULL);
		void		Draw(HSTRING szString, LITHFONTDRAWDATA *lfDD = LTNULL);

		// Formatting information
		void		GetTextExtents(char *szString, LITHFONTDRAWDATA *lfDD, uint32 &x, uint32 &y);
		void		GetTextExtents(HSTRING szString, LITHFONTDRAWDATA *lfDD, uint32 &x, uint32 &y);

		void		GetPositionFromIndex(char *szString, LITHFONTDRAWDATA *lfDD, int index, uint32 &x, uint32 &y);
		void		GetPositionFromIndex(HSTRING szString, LITHFONTDRAWDATA *lfDD, int index, uint32 &x, uint32 &y);

	protected:
		// Client reference
		ILTClient	*m_pClient;

		// General cursor information
		char		m_szRefName[LTF_REF_NAME_SIZE];		// Reference name from the cursor

		// Current font
		LithFont	*m_pFont;

		// Destination surface
		HSURFACE	m_pDest;

		// Cursor location on dest surface
		int			m_nX;
		int			m_nY;

		// Drawing data
		LITHFONTDRAWDATA	m_lfDD;
		LITHFONTSAVEDATA	m_lfSD;
};

//*********************************************************************************

#endif
