// LTGUIEditCtrl.h: interface for the CLTGUIEditCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTGUIEDITCTRL_H__470388F4_63A2_11D2_BDA9_0060971BDC6D__INCLUDED_)
#define AFX_LTGUIEDITCTRL_H__470388F4_63A2_11D2_BDA9_0060971BDC6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ltguictrl.h"

class CLTGUIEditCtrl : public CLTGUIFadeColorCtrl
{
public:
	CLTGUIEditCtrl();
	virtual ~CLTGUIEditCtrl();

	// Create the control
	// pClientDE	   - Pointer to the client interface.
	// dwCommandID	   - The command ID which is sent when "enter" is pressed.
	// hDescription	   - The description of the edit string displayed on the left
	// pFont		   - The font to use for rendering the strings.
	// nTextOffset	   - The number of pixels that the edit string is offset from the left side of the control.
	// nBufferSize	   - The size of the buffer to store the string in.
	// pMessageCtrl    - control which receives messages when the "enter" key is pressed.
	// pStringValue	   - pointer to the string to be modified in UpdateData.
    virtual LTBOOL   Create ( ILTClient *pClientDE, uint32 dwCommandID, HSTRING hDescription, CLTGUIFont *pFont,
                             int nTextOffset, int nBufferSize, CLTGUICommandHandler *pCommandHandler=LTNULL,
                             char *pStringValue=LTNULL, uint32 dwParam1 = 0, uint32 dwParam2 = 0 );

	// Destroys the control
	void			Destroy ( );

	// Update data
    void            UpdateData(LTBOOL bSaveAndValidate=LTTRUE);

	// Render the control
	void			Render ( HSURFACE hDestSurf );

	// Set the font
	void			SetFont ( CLTGUIFont *pFont );

	// Set/Get the text for the edit string
	void			SetText(char *lpszString);
	char			*GetText()						{ return m_lpszString; }

	// Sets the alignment for the description text (LTF_JUSTIFY_LEFT, LTF_JUSTIFY_CENTER, LTF_JUSTIFY_RIGHT)
	void			SetAlignment(int nAlignment)	{ m_nAlignment=nAlignment; }

	// Width/Height calculations
	int				GetWidth ( );
	int				GetHeight ( );

	// Handles a key press
    LTBOOL           HandleKeyDown(int key, int rep);
    LTBOOL           HandleChar(char c);

	// Handle the Enter key being pressed
    virtual LTBOOL   OnEnter ( );
    virtual LTBOOL   OnLButtonUp(int x, int y) {return OnEnter();}

	// Set the cursor usage (default is no cursor)
    void            EnableCursor(float fToggleTime = 0.333f, HLTCOLOR hColor = SETRGB(255,255,255));
    void            DisableCursor() {m_bCursorEnabled = LTFALSE;}

protected:
	// The selection for this control has changed
	void			OnSelChange();

	// Add a character to the end
	void			AddCharacter(char c);

	// Remove a character from the end
	void			RemoveCharacter();

	// Should the cursor be rendered
    LTBOOL           IsCursorOn();

protected:

	CLTGUIFont		*m_pFont;				// The font for this control
	char			*m_lpszString;			// The text for the control

	HSTRING			m_hDescription;			// The description of the edit string displayed on the left
	int				m_nAlignment;			// The alignment for the description text
	int				m_nTextOffset;			// The number of pixels that the edit string is offset from the left side of the control

	int				m_nBufferSize;			// The maximum length for the string
	int				m_nCursorPos;
	char			*m_pStringValue;		// The pointer that is updated in the UpdateData function

    LTBOOL           m_bCursorEnabled;
    HLTCOLOR        m_hCursorColor;
	float			m_fCursorTime;

	// Receives a message when the "enter" key is pressed.
	CLTGUICommandHandler	*m_pCommandHandler;
};

#endif // !defined(AFX_LTGUIEDITCTRL_H__470388F4_63A2_11D2_BDA9_0060971BDC6D__INCLUDED_)