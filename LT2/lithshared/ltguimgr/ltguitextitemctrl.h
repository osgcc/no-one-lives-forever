// LTGUITextItemCtrl.h: interface for the CLTGUITextItemCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTGUITEXTITEMCTRL_H__DDDEFA74_57D4_11D2_BDA0_0060971BDC6D__INCLUDED_)
#define AFX_LTGUITEXTITEMCTRL_H__DDDEFA74_57D4_11D2_BDA0_0060971BDC6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ltguictrl.h"
#include "stdlith.h"

// This control displays a string of text which fades out upon being unselected.
// It can contain multiple strings (see CLTGUICtrl::AddString()) which are cycled
// when OnLeft() and OnRight() are called.  This is useful in menu code for selecting
// options.
class CLTGUIFont;
class CLTGUITextItemCtrl : public CLTGUIFadeColorCtrl
{
public:
	CLTGUITextItemCtrl();
	virtual ~CLTGUITextItemCtrl();

	// Create the control
	// pClientDE	- Pointer to the client interface.
	// dwCommandID	- The command ID which is sent when "enter" is pressed.
    // hText        - The initial text that is displayed for this control. Pass in LTNULL if you do not want initial text.
	// pFont		- The font to use for this string.
	// pMessageCtrl - control which receives messages when the "enter" key is pressed.
	// pnValue		- Pointer to the value which receives the selection index when UpdateData is called.
    LTBOOL           Create ( ILTClient *pClientDE, uint32 dwCommandID, HSTRING hText, CLTGUIFont *pFont,
                             CLTGUICommandHandler *pCommandHandler, int *pnValue=LTNULL,
                             uint32 dwParam1 = 0, uint32 dwParam2 = 0);

	// Destroys the control
	void			Destroy ( );

	// Update data
    virtual void    UpdateData(LTBOOL bSaveAndValidate);

	// Add more strings to the control.  These are cycled when OnLeft() and OnRight() are called
	void			AddString(HSTRING hString);
	void			AddString(int messageCode);

	HSTRING			GetString(int nIndex);			// Return a string at a specific index
	void			RemoveString(int nIndex);		// Remove a string at a specific index
	void			RemoveAll();					// Remove all strings

	// Return the number of strings
	int				GetNumStrings()						{ return m_stringArray.GetSize(); }

	// Sets/Get the currently selected index
	int				GetSelIndex()						{ return m_nSelIndex; }
	virtual void	SetSelIndex(int nIndex);

	// Render the control
	void			Render ( HSURFACE hDestSurf );

	// Set the font
    LTBOOL           SetFont ( CLTGUIFont *pFont);

	// Width/Height calculations
	int				GetWidth ( )						{ return m_dwWidth; }
	int				GetHeight ( )						{ return m_dwHeight; }

	// Commonly used keyboard messages
    virtual LTBOOL   OnEnter ( );
    virtual LTBOOL   OnLeft ( );
    virtual LTBOOL   OnRight ( );
    virtual LTBOOL   OnLButtonUp(int x, int y) {return OnEnter();}

	// [blg] ctrl id
    uint32          GetID() { return(m_dwCommandID); }

	// fixed width text
    void            SetFixedWidth(uint32 width) {m_dwWidth = width; m_bFixedWidth = LTTRUE; CalculateSize(); }
    void            ClearFixedWidth()           {m_bFixedWidth = LTFALSE; CalculateSize(); }

protected:
	// The selection for this control has changed
	virtual void	OnSelChange();
	virtual void	CalculateSize();

protected:

	CLTGUIFont		*m_pFont;				// The font for this control

    uint32          m_dwWidth;              // The width of the control
    uint32          m_dwHeight;             // The height of the control
    LTBOOL           m_bFixedWidth;          // TRUE is we should format the text to fit a set width

	int				*m_pnValue;				// Receives the current selection when UpdateData is called

	int					m_nSelIndex;		// The currently selected index
	CMoArray<HSTRING>	m_stringArray;		// The array of strings

	// Receives a message when the "enter" key is pressed.
	CLTGUICommandHandler	*m_pCommandHandler;
};

#endif // !defined(AFX_LTGUITEXTITEMCTRL_H__DDDEFA74_57D4_11D2_BDA0_0060971BDC6D__INCLUDED_)