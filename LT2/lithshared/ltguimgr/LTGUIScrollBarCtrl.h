// LTGUIScrollBarCtrl.h: interface for the CLTGUIScrollBarCtrl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LTGUISCROLLBARCTRL_H
#define LTGUISCROLLBARCTRL_H

#include "ltguictrl.h"

class CLTGUIScrollBarCtrl :  public CLTGUICtrl
{
public:
	CLTGUIScrollBarCtrl();
	virtual ~CLTGUIScrollBarCtrl();

	// Create the control
	// pClientDE	- Pointer to the client interface.
	// hBarSurf		- The surface representing the "scroll bar"
	// hTabSurf		- The surface representing the scroll tab which moves over the bar
	// hUpArrow		- The surface representing the up arrow
	// hDownArrow	- The surface representing the down arrow
	// hUpArrowPressed - The surface representing the pressed up arrow
	// hDownArrowPressed - The surface representing the pressed down arrow
	// nWidth		- The width of the scroll bar control
	// nHeight		- The height of the scroll bar control
	// dwIncrement	- The amount to increment the value each time a page up or down is called
	// pnValue		- Pointer to the value to store the position in when UpdateData is called
    LTBOOL           Create (    ILTClient *pClientDE,
								HSURFACE hBarSurf,
								HSURFACE hTabSurf,
								HSURFACE hUpArrow,
								HSURFACE hDownArrow,
								HSURFACE hUpArrowPressed,
								HSURFACE hDownArrowPressed,
								int nWidth,
								int nHeight,
                                uint32 dwIncrement,
								int *pnValue);

	// Update data
    void            UpdateData(LTBOOL bSaveAndValidate=LTTRUE);

	// Sets the min and max of the slider bar
	void			SetScrollBarRange(int nMin, int nMax);

	// Gets/Sets the position of the slider bar
	int				GetTabPos()			{ return m_nTabPos; }
	void			SetTabPos(int nPos);

	// Render the control
	void			Render ( HSURFACE hDestSurf );

	// Handle mouse click
    LTBOOL   OnLButtonDown       (int x, int y);
    LTBOOL   OnLButtonUp         (int x, int y);
	void	IncUp				();
	void	IncDown				();
	void	IncPgUp				();
	void	IncPgDown			();
    LTBOOL   OnMouseMove         (int x, int y);

	// Width/Height calculations
	int		GetWidth	( )	{ return m_dwWidth; }
	int		GetHeight	( )	{ return m_dwHeight; }

protected:
	void			RenderScrollBar(HSURFACE hDestSurf);
	void			CheckRepeat ();

protected:
    uint32          m_dwPgIncrement;// The amount to increment on pg up or down
    uint32          m_dwTabOffset;  // The offset from the top or the control to the top of the tab
    uint32          m_dwTabHeight;  // The height of the tab surface
    uint32          m_dwSliderArea; // The height of the slider area
    uint32          m_dwTopOffset;  // The height of the up arrow
    uint32          m_dwBotOffset;  // The height of the down arrow
    uint32          m_dwWidth;      // The width of the control
    uint32          m_dwHeight;     // The height of the control
	int				m_nMinTabPos;	// The min slider position
	int				m_nMaxTabPos;	// The max slider position
	int				m_nTabPos;		// The current slider position
	HSURFACE		m_hBarSurf;		// The surface representing the "scroll bar"
	HSURFACE		m_hTabSurf;		// The surface representing the scroll tab which moves over the bar
	HSURFACE		m_hUpArrow;		// The surface representing the up arrow
	HSURFACE		m_hDownArrow;	// The surface representing the down arrow
	HSURFACE		m_hUpArrowPressed;	// The surface representing the up arrow
	HSURFACE		m_hDownArrowPressed;// The surface representing the down arrow
	LTBOOL			m_bUpArrowPress;	// The left button is down on the up arrow
	LTBOOL			m_bDownArrowPress;	// The left button is down on ht down arrow
	LTBOOL			m_bTabPress;		// The left button is down on the tab
	int				*m_pnValue;		// Pointer to the value to store the position in when UpdateData is called
    LTFLOAT          m_fRepeatStartTime; //Time marker for repeat
};

#endif // LTGUISCROLLBARCTRL_H