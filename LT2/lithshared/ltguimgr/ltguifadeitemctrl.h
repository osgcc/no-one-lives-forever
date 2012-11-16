// LTGUIFadeItemCtrl.h: interface for the CLTGUIFadeItemCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTGUIFADEITEMCTRL_H__F502A540_575A_11D2_BDA0_0060971BDC6D__INCLUDED_)
#define AFX_LTGUIFADEITEMCTRL_H__F502A540_575A_11D2_BDA0_0060971BDC6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ltguictrl.h"

// This control is used to for selecting menu items.  It fades from "selected" to "nonselected"
// play displaying a series of bitmaps. CLTGUITextItemCtrl is available if you wish to use
// text instead of bitmaps.
class CLTGUIFadeItemCtrl : public CLTGUICtrl
{
public:
	CLTGUIFadeItemCtrl();
	virtual ~CLTGUIFadeItemCtrl();

	// Create the control
	// pClientDE	- Pointer to the client interface
	// dwCommandID	- The command ID which is sent when "enter" is pressed.
	// pSurfArray	- An array of surfaces.  The first surface is the selected surface and the last
	//                is the non-selected surface.  The inbetween surfaces are used for fading when the
	//				  selection changes.
	// bOwnSurfaces - Set this to TRUE if you wish the control to destroy the surfaces.
	// pMessageCtrl - control which receives messages when the "enter" key is pressed
    LTBOOL           Create ( ILTClient *pClientDE, uint32 dwCommandID, HSURFACE *pSurfArray, int nSurfaces,
                             HSURFACE hDisabledSurf, LTBOOL bOwnSurfaces, CLTGUICommandHandler *pCommandHandler,
                             uint32 dwParam1 = 0, uint32 dwParam2 = 0 );

	// Destroys the control
	void			Destroy ( );

	// Set the fade out time
    void            SetFadeTime ( uint32 dwFadeTime )   { m_dwFadeTime=dwFadeTime; }

	// Render the control
	void			Render ( HSURFACE hDestSurf );

	// Width/Height calculations
	int				GetWidth ( )						{ return m_dwWidth; }
	int				GetHeight ( )						{ return m_dwHeight; }

	// Commonly used keyboard messages
    virtual LTBOOL   OnEnter ( );
    virtual LTBOOL   OnLButtonUp(int x, int y) {return OnEnter();}

protected:
	// The selection for this control has changed
	void			OnSelChange();

protected:
    LTBOOL           m_bOwnSurfaces;         // True if the control is to destroy the surfaces
    uint32          m_dwFadeTime;           // The "fade out" time in milliseconds
	HSURFACE		*m_pSurfArray;			// The array of surfaces for this control.
	HSURFACE		m_hDisabledSurf;		// The disabled surface

	int				m_nSurfaces;			// The number of surfaces in this control

    uint32          m_dwWidth;              // The width
    uint32          m_dwHeight;             // The height

	float			m_fLastSelTime;			// The last selection time

	// Receives a message when the "enter" key is pressed.
	CLTGUICommandHandler	*m_pCommandHandler;
};

#endif // !defined(AFX_LTGUIFADEITEMCTRL_H__F502A540_575A_11D2_BDA0_0060971BDC6D__INCLUDED_)