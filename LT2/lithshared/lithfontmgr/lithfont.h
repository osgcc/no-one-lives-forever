//*********************************************************************************
//*********************************************************************************
// Project:		Lith Tech Font Manager
// Purpose:		A general font method for bitmap and system fonts
//*********************************************************************************
// File:		LithFont.h
// Created:		April 7, 1999
// Updated:		July 15, 1999
// Author:		Andy Mattingly
//*********************************************************************************
//*********************************************************************************

#ifndef		_LITHTECH_FONT_H_
#define		_LITHTECH_FONT_H_

//*********************************************************************************

#include <stdio.h>
#include <mbstring.h>

#ifdef _LITHTECH2
	#include "lithfontdefs.h"
	#include "iltclient.h"
#else
	#include "basedefs_de.h"
	#include "cpp_clientshell_de.h"
	#include "lithfontdefs.h"
#endif

//*********************************************************************************

class LithFont
{
	public:
		// Constructors and destructors
		LithFont();
		~LithFont();

		// Memory allocation and deallocation
		virtual LTBOOL	Init(ILTClient *pClient, LITHFONTCREATESTRUCT *lfCS);
		virtual void	Free();

		// Drawing / rendering
		virtual void	Draw(HSURFACE pDest, char *szString, LITHFONTDRAWDATA *lfDD, int nX = 0, int nY = 0, LITHFONTSAVEDATA *lfSD = LTNULL) = 0;
		void			Draw(HSURFACE pDest, HSTRING szString, LITHFONTDRAWDATA *lfDD, int nX = 0, int nY = 0, LITHFONTSAVEDATA *lfSD = LTNULL);

		// Formatting information
		virtual void	GetTextExtents(char *szString, LITHFONTDRAWDATA *lfDD, uint32 &x, uint32 &y, int index = -1) = 0;
		void			GetTextExtents(HSTRING szString, LITHFONTDRAWDATA *lfDD, uint32 &x, uint32 &y, int index = -1);

		virtual void	GetPositionFromIndex(char *szString, LITHFONTDRAWDATA *lfDD, int index, uint32 &x, uint32 &y) = 0;
		void			GetPositionFromIndex(HSTRING szString, LITHFONTDRAWDATA *lfDD, int index, uint32 &x, uint32 &y);

		// State information
		virtual uint8	GetState(LITHFONTSAVEDATA *lfSD = LTNULL) = 0;

		// Get font information
		void		SetRefName(char *szName)	{ strcpy(m_szRefName, szName); }
		char*		GetRefName()				{ return m_szRefName; }
		int			Height()					{ return m_nHeight; }

		virtual LTBOOL	IsChromaKeyed() = 0;
		virtual LTBOOL	IsSystemFont() = 0;

	protected:
		// Client reference
		ILTClient	*m_pClient;

		// Font data variables
		char		m_szRefName[LTF_REF_NAME_SIZE];		// Reference name for the font
		int			m_nHeight;							// Height of the font characters...

	protected:
		// Function to extract the root filename from an entire path, filename, and extension
		void	GetFilename(char *szFullPath, char *szName);

		// Function to determine whether a line of text should be drawn or not within the given RECT
		virtual LTBOOL	ClipFont(LTRect &rcFont) = 0;
};

//*********************************************************************************

#endif
