// BitmapCtrl.h: interface for the CLTGUIBitmapCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPCTRL_H__639D44A0_1A85_11D3_B2DB_006097097C7B__INCLUDED_)
#define AFX_BITMAPCTRL_H__639D44A0_1A85_11D3_B2DB_006097097C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LTGUIMgr.h"
#include "stdlith.h"


class CLTGUIBitmapCtrl : public CLTGUIFadeColorCtrl
{
public:
	CLTGUIBitmapCtrl();
	virtual ~CLTGUIBitmapCtrl();
    LTBOOL   Create( ILTClient *pClientDE, HSURFACE hNormalBmp,
					HSURFACE hSelectedBmp = NULL,HSURFACE hDisabledBmp = NULL,
					HSURFACE m_hClickedOnSurface = NULL,
                    CLTGUICommandHandler *pCommandHandler = LTNULL,
                    uint32 dwCommandID = LTNULL,
                    uint32 dwParam1 = 0, uint32 dwParam2 = 0,
                    HSTRING hString=LTNULL, CLTGUIFont* pFont=LTNULL,
                    LTIntPt ptOffset=LTIntPt(0,0) );


	// Destruction

	virtual void	Destroy();

	// Render the control
	virtual void	Render ( HSURFACE hDestSurf );
	void			RenderText(HSURFACE hDestSurf);

	// Width/Height calculations
	virtual int		GetWidth ( );
	virtual int		GetHeight ( );

    virtual LTBOOL   OnEnter();
    virtual LTBOOL   OnLButtonDown(int x, int y);
    virtual LTBOOL   OnLButtonUp(int x, int y);

	//determines whether the surfaces should be freed when changing bitmaps and on destruction
    void            AutoFreeSurfaces(LTBOOL bFreeSurf) {m_bFreeSurfaces = bFreeSurf;}


    virtual LTBOOL   SetBitmap(HSURFACE hNormalBmp,HSURFACE hSelectedBmp=LTNULL,HSURFACE hDisabledBmp=LTNULL, HSURFACE hClickedBmp=LTNULL);
	virtual void	FreeSurfaces();

	HSURFACE		GetNormalBitmap(){return m_hNormalSurface;}
	HSURFACE		GetSelectedBitmap(){return m_hSelectedSurface;}
	HSURFACE		GetDisabledBitmap(){return m_hDisabledSurface;}

	// Set the font. Set nNumFonts > 1 to use fade fonts.
	void			SetFont ( CLTGUIFont *pFont);

	// Sets the text for the button
	void			SetText(HSTRING hString);


protected:
	HSURFACE			m_hNormalSurface;
	HSURFACE			m_hSelectedSurface;
	HSURFACE			m_hDisabledSurface;
	HSURFACE			m_hClickedOnSurface;

	HSTRING				m_hText;
	CLTGUIFont*			m_pFont;
	int				m_nNumFonts;			// The number of fonts
    LTIntPt          m_ptOffset;             // Offset for text display
    LTBOOL           m_bButtonDown;

	int				m_nNormalWidth;
	int				m_nNormalHeight;
	int				m_nSelectedWidth;
	int				m_nSelectedHeight;
	int				m_nDisabledWidth;
	int				m_nDisabledHeight;
	int				m_nClickedWidth;
	int				m_nClickedHeight;

    LTBOOL           m_bFreeSurfaces;

	// Receives a message when the "enter" key is pressed.
	CLTGUICommandHandler	*m_pCommandHandler;

};

#endif // !defined(AFX_BITMAPCTRL_H__639D44A0_1A85_11D3_B2DB_006097097C7B__INCLUDED_)