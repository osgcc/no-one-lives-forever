// LTGUIOnOffCtrl.h: interface for the CLTGUIOnOffCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTGUIONOFFCTRL_H__B4C56631_617A_11D2_BDA7_0060971BDC6D__INCLUDED_)
#define AFX_LTGUIONOFFCTRL_H__B4C56631_617A_11D2_BDA7_0060971BDC6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ltguicyclectrl.h"

class CLTGUIOnOffCtrl : public CLTGUICycleCtrl
{
public:
	CLTGUIOnOffCtrl();
	virtual ~CLTGUIOnOffCtrl();

	// Create the control
	// pClientDE		  - Pointer to the client interface.
	// hString			  - Handle of a string to copy the text from for the control.
	// pFont			  - The font to use for rendering the strings.
	// nRightColumnOffset - The number of pixels from the left edge that the on/off text is
	// pbValue			  - Value to store the on/off status in when UpdateData is called
    LTBOOL           Create ( ILTClient *pClientDE, HSTRING hString, CLTGUIFont *pFont,
                             int nRightColumnOffset, LTBOOL *pbValue=LTNULL, int alignment = LTF_JUSTIFY_CENTER);

	void			SetOnString(HSTRING hStrOn);
	void			SetOffString(HSTRING hStrOff);

	void			SetOnString(int nStrOnID);
	void			SetOffString(int nStrOffID);

	// Update data
    void            UpdateData(LTBOOL bSaveAndValidate=LTTRUE);

	// Sets/gets the on/off status
    LTBOOL           IsOn()              { return m_bOn; }
    virtual void    SetOn(LTBOOL bOn);

	// Left and Right key presses
    virtual LTBOOL   OnLeft()            { SetOn(!IsOn()); return LTTRUE;}
    virtual LTBOOL   OnRight()           { SetOn(!IsOn()); return LTTRUE;}

protected:
    LTBOOL           m_bOn;
    LTBOOL           *m_pbValue;     // Value to store the on/off status in when UpdateData is called.

	HSTRING			m_hStrOn;
	HSTRING			m_hStrOff;
};

#endif // !defined(AFX_LTGUIONOFFCTRL_H__B4C56631_617A_11D2_BDA7_0060971BDC6D__INCLUDED_)