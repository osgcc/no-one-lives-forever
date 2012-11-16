// LTGUICtrl.h: interface for the CLTGUICtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTGUICTRL_H__04CA2480_5726_11D2_BD9D_0060971BDC6D__INCLUDED_)
#define AFX_LTGUICTRL_H__04CA2480_5726_11D2_BD9D_0060971BDC6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _LITHTECH2
	#include "ltbasedefs.h"
	#include "iltclient.h"
#else
	#include "cpp_clientshell_de.h"
	#include "basedefs_de.h"
#endif

#define	LGCS_NORMAL		0	// control states
#define LGCS_SELECTED	1
#define LGCS_DISABLED	2

class CLTGUICtrl : public CLTGUICommandHandler
{
public:
	CLTGUICtrl();
	virtual ~CLTGUICtrl();

	// All controls should have a create function.  Since these parameters vary
	// drastically there is not a create base class method.

	// Destruction
	virtual void	Destroy();

	// Render the control
	virtual void	Render ( HSURFACE hDestSurf ) = 0;

	// Reset the animation of the control if it has one
	virtual void	ResetAnimation();

	// Width/Height calculations
	virtual int		GetWidth ( ) = 0;
	virtual int		GetHeight ( ) = 0;

	// Handles a key press.  Returns FALSE if the key was not processed through this method.
	// Left, Up, Down, Right, and Enter are automatically passed through OnUp(), OnDown(), etc.
    virtual LTBOOL   HandleKeyDown(int key, int rep);

	// Handles a character input.
    virtual LTBOOL   HandleChar(char c);

	// Commonly used keyboard messages
    virtual LTBOOL   OnLeft ( );
    virtual LTBOOL   OnRight ( );
    virtual LTBOOL   OnUp ( );
    virtual LTBOOL   OnDown ( );
    virtual LTBOOL   OnEnter ( );

	// Mouse messages
    virtual LTBOOL   OnLButtonDown(int x, int y);
    virtual LTBOOL   OnLButtonUp(int x, int y);
    virtual LTBOOL   OnLButtonDblClick(int x, int y);
    virtual LTBOOL   OnRButtonDown(int x, int y);
    virtual LTBOOL   OnRButtonUp(int x, int y);
    virtual LTBOOL   OnRButtonDblClick(int x, int y);
    virtual LTBOOL   OnMouseMove(int x, int y);

    virtual void    Create(uint32 dwCommandID, uint32 dwParam1 = 0, uint32 dwParam2 = 0)
					{
						m_dwCommandID = dwCommandID;
						m_dwParam1 = dwParam1;
						m_dwParam2 = dwParam2;
					}

	// Handle a command
    virtual void    OnCommand ( uint32 dwCommandID );

	// Select a control
    void            Select(LTBOOL bSelected);

	// Disable the control
    virtual void    Enable ( LTBOOL bEnabled )       { m_bEnabled=bEnabled; }

	// Update data
    virtual void    UpdateData ( LTBOOL bSaveAndValidate = LTTRUE );

	// Access to member variables
    LTBOOL           IsSelected()                    { return m_bSelected; }
    LTBOOL           IsEnabled()                     { return m_bEnabled; }
    LTBOOL           IsNormal()                      { return(!IsSelected() && IsEnabled()); }
    LTBOOL           IsDisabled()                    { return(!IsSelected() && !IsEnabled()); }

    void            SetPos ( LTIntPt pos )           { m_pos=pos; }
	void			SetPos ( int x, int y )			{ m_pos.x=x; m_pos.y=y; }
    LTIntPt          GetPos ( )                      { return m_pos; }

    virtual uint32  GetID() { return(0); }
	virtual	int		GetState();

    void            SetParam1(uint32 dw) { m_dwParam1 = dw; }
    void            SetParam2(uint32 dw) { m_dwParam2 = dw; }

    uint32          GetParam1() { return(m_dwParam1); }
    uint32          GetParam2() { return(m_dwParam2); }

	int				GetBoxDrawAdjustX() { return(m_xBoxDrawAdj); }
	void			SetBoxDrawAdjustX(int xAdj) { m_xBoxDrawAdj = xAdj; }

    static void     SetShiftState(LTBOOL bShiftDown) { s_bShiftState=bShiftDown; }
    static LTBOOL    IsShiftKeyDown()                { return s_bShiftState; }

    static void     SetCapsState(LTBOOL bCapsDown)   { s_bCapsState=bCapsDown; }
    static LTBOOL    IsCapsKeyDown()                 { return s_bCapsState; }

    virtual uint32  GetHelpID()                     {return m_dwHelpID;}
    virtual void    SetHelpID(uint32 id)            {m_dwHelpID = id;}

    virtual void    SetTransparentColor(HLTCOLOR hColor) {m_hTransColor = hColor;}

protected:
	// Called by Select().  The IsSelected() will return the newly selected state.
	virtual void	OnSelChange()					{}

protected:
    ILTClient       *m_pClientDE;
    uint32          m_dwCommandID;          // The command which is sent when "enter" is pressed
    uint32          m_dwParam1;             // Extra params
    uint32          m_dwParam2;             // Extra params
    LTBOOL           m_bCreated;
    LTIntPt          m_pos;
    LTBOOL           m_bSelected;
    LTBOOL           m_bEnabled;
	int				m_xBoxDrawAdj;

    uint32          m_dwHelpID;

    static LTBOOL    s_bShiftState;  // Track the shift key state
    static LTBOOL    s_bCapsState;   // Track the caps key state

    HLTCOLOR        m_hTransColor;

};

inline int CLTGUICtrl::GetState()
{
	if (IsSelected()) return(LGCS_SELECTED);
	if (IsDisabled()) return(LGCS_DISABLED);
	return(LGCS_NORMAL);
}

#endif // !defined(AFX_LTGUICTRL_H__04CA2480_5726_11D2_BD9D_0060971BDC6D__INCLUDED_)