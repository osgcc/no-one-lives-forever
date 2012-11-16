// LTGUIListCtrl.h: interface for the CLTGUIListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTGUILISTCTRL_H__F502A543_575A_11D2_BDA0_0060971BDC6D__INCLUDED_)
#define AFX_LTGUILISTCTRL_H__F502A543_575A_11D2_BDA0_0060971BDC6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ltguictrl.h"
#include "stdlith.h"

class CLTGUIListCtrl : public CLTGUICtrl
{
public:
	CLTGUIListCtrl();
	virtual ~CLTGUIListCtrl();

	// Creation
    LTBOOL       Create ( int nHeight );

	// Destroy the control
	void		Destroy ( );

	// Render the control
	void		Render ( HSURFACE hDestSurf );

	// Width/Height calculations
	int			GetWidth ( );
	int			GetHeight ( );

	// Call this if you wish to enable highlighting the item that is under the mouse
	// cursor and changing selection when the mouse is moved.
    void        EnableMouseMoveSelect(LTBOOL bEnable);

	// Handle a keypress
    LTBOOL       HandleKeyDown(int key, int rep);

	// Commonly used keyboard messages
    virtual LTBOOL   OnUp ( );
    virtual LTBOOL   OnDown ( );
    virtual LTBOOL   OnLeft ( );
    virtual LTBOOL   OnRight ( );
    virtual LTBOOL   OnEnter ( );

	// Mouse messages
    virtual LTBOOL   OnLButtonDown(int x, int y);
    virtual LTBOOL   OnLButtonUp(int x, int y);
    virtual LTBOOL   OnMouseMove(int x, int y);

	// Set the number of pixels between items
	void		SetItemSpacing ( int nSpacing )		{ m_nItemSpacing=nSpacing; }

	// Sets the height of the listbox
	void		SetHeight(int nHeight)				{ m_nHeight=nHeight; }

	// Sets whether or not the items should wrap when scrolling
    void        SetScrollWrap(LTBOOL bWrap)          { m_bScrollWrap=bWrap; }

	// Sets whether or not to box the items
    void        EnableBoxFormat(LTBOOL bEnable)      { m_bEnableBoxFormat = bEnable; }

	// Sets whether or not to center the items
    void        SetCenter(LTBOOL bCenter)            { m_nAlign = (bCenter ? LTF_JUSTIFY_CENTER : LTF_JUSTIFY_LEFT) ; }
	void		SetAlignment(int nAlignment)		{ m_nAlign = nAlignment; }
	int			GetAlignment()						{ return m_nAlign;}

	// Add/Remove controls to the array
	int			AddControl ( CLTGUICtrl *pControl );
	void		RemoveControl ( CLTGUICtrl *pControl );
	void		RemoveControl ( int nIndex );
	void		RemoveAllControls ( );
	int			GetNum ( )							{ return m_controlArray.GetSize(); }

	CLTGUICtrl	*GetControl ( int nIndex );

	void		SelectItem ( int nIndex );
	int			GetSelectedItem ( )					{ return m_nCurrentIndex; }

	int			GetLastDisplayedIndex ( )			{ return GetLastDisplayedIndex(GetStartIndex()); }
	int			GetStartIndex ( )					{ return m_nFirstDisplayedItem; }
	void		SetStartIndex ( int nIndex )		{ m_nFirstDisplayedItem=nIndex; }

	// Gets the index of the control that is under the specific screen point.
	// Returns FALSE if there isn't one under the specified point.
	CLTGUICtrl	*GetControlUnderPoint(int xPos, int yPos, int *pnIndex);

protected:
	// Returns the last displayed index while in box format
	int			GetLastDisplayedIndex (int nStartIndex);


protected:
	int			m_nItemSpacing;				// The number of pixels between items
	int			m_nCurrentIndex;			// Selected item
	int			m_nFirstDisplayedItem;		// First item displayed on the screen
	int			m_nHeight;					// Height of the control
    LTBOOL       m_bScrollWrap;              // True if we should wrap when scrolling up and down
    LTBOOL       m_bEnableBoxFormat;         // Formats the controls to a box.  Otherwise the controls position is used.
	int			m_nMouseDownItemSel;		// The control index that is selected from the current mouse down message
    LTBOOL       m_bEnableMouseMoveSelect;   // True when the selected control changes when the mouse is moved
	int			m_nAlign;					// Justification for the options

	CMoArray<CLTGUICtrl *>	m_controlArray;
};

#endif // !defined(AFX_LTGUILISTCTRL_H__F502A543_575A_11D2_BDA0_0060971BDC6D__INCLUDED_)