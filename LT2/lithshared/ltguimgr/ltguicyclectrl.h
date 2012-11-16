// LTGUICycleCtrl.h: interface for the CLTGUICycleCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTGUICYCLECTRL_H__7CA44FC0_12B5_11D3_B2DB_006097097C7B__INCLUDED_)
#define AFX_LTGUICYCLECTRL_H__7CA44FC0_12B5_11D3_B2DB_006097097C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ltguitextitemctrl.h"

class CLTGUICycleCtrl : public CLTGUITextItemCtrl
{
public:
	CLTGUICycleCtrl();
	virtual ~CLTGUICycleCtrl();

	// Create the control
	// pClientDE	- Pointer to the client interface.
    // hText        - The header text that is displayed for this control. Pass in LTNULL if you do not want header text.
	// pFont		- The font to use for this control.
	// nHeaderWidth	- The width to use for the header string
	// nSpacerWidth	- The width to use for the space between the header and text
	// pnValue		- Pointer to the value which receives the selection index when UpdateData is called.
	// alignment	- Justification to use when rendering
    LTBOOL           Create ( ILTClient *pClientDE, HSTRING hText, CLTGUIFont *pFont,
                            int nHeaderWidth, int nSpacerWidth = 25, int *pnValue=LTNULL, int alignment = LTF_JUSTIFY_CENTER);

	//this function sets up a notification when the control's value changes
    virtual void    NotifyOnChange(uint32 dwCommandID,CLTGUICommandHandler *pCommandHandler, uint32 dwParam1 = 0, uint32 dwParam2 = 0);

	//these overridden functions are needed to manage the notification
	virtual void	SetSelIndex(int nIndex);
    virtual void    UpdateData(LTBOOL bSaveAndValidate);


	// Render the control
	virtual void	Render ( HSURFACE hDestSurf );
	virtual void	CalculateSize();

	// Since cycle controls do not have command ID's or command handlers,
	// Enter should cycle through the strings, just like the arrow keys.
    virtual LTBOOL   OnEnter ( )         { return OnRight(); }
    virtual LTBOOL   OnLButtonUp(int x, int y) {return OnRight();}
    virtual LTBOOL   OnRButtonUp(int x, int y) {return OnLeft();}


protected:
	HSTRING			m_hHeaderText;
	int				m_nHeaderWidth;
	int				m_nSpacerWidth;
	int				m_nAlign;

    LTBOOL           m_bInUpdate;

};

#endif // !defined(AFX_LTGUICYCLECTRL_H__7CA44FC0_12B5_11D3_B2DB_006097097C7B__INCLUDED_)