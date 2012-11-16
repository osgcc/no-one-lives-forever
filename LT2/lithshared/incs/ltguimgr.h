// LTGUIMgr.h: interface for the CLTGUIMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LTGUIMGR_H__04CA2483_5726_11D2_BD9D_0060971BDC6D__INCLUDED_)
#define AFX_LTGUIMGR_H__04CA2483_5726_11D2_BD9D_0060971BDC6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _LITHTECH2
	#include "lithtech.h"
#else
	#include "basetypes_de.h"
#endif

//#include "..\ltguimgr\coolfont.h"
#include "..\lithfontmgr\lithfontdefs.h"
#include "..\lithfontmgr\lithfontmgr.h"
#include "..\ltguimgr\ltguifont.h"
#include "..\ltguimgr\ltguicommandhandler.h"
#include "..\ltguimgr\ltguilistctrl.h"
#include "..\ltguimgr\ltguifadecolorctrl.h"
#include "..\ltguimgr\ltguifadeitemctrl.h"
#include "..\ltguimgr\ltguitextitemctrl.h"
#include "..\ltguimgr\ltguicolumntextctrl.h"
#include "..\ltguimgr\ltguisliderctrl.h"
#include "..\ltguimgr\ltguionoffctrl.h"
#include "..\ltguimgr\ltguieditctrl.h"
#include "..\ltguimgr\ltguicyclectrl.h"
#include "..\ltguimgr\ltguimessagebox.h"
#include "..\ltguimgr\ltguibitmapctrl.h"
#include "..\ltguimgr\ltguiscrollbarctrl.h"

#ifndef NO_PRAGMA_LIBS
	#ifdef _LITHTECH2
		#ifdef _DEBUG				 
			#pragma comment (lib, "\\proj\\libs\\debug\\LTGUIMgr_LT2.lib")
		#else
			#pragma comment (lib, "\\proj\\libs\\release\\LTGUIMgr_LT2.lib")
		#endif
	#else
		#ifdef _DEBUG				 
			#pragma comment (lib, "\\proj\\libs\\debug\\LTGUIMgr.lib")
		#else
			#pragma comment (lib, "\\proj\\libs\\release\\LTGUIMgr.lib")
		#endif
	#endif
#endif


class CLTGUIMgr  
{
public:
	CLTGUIMgr();
	virtual ~CLTGUIMgr();

};

#endif // !defined(AFX_LTGUIMGR_H__04CA2483_5726_11D2_BD9D_0060971BDC6D__INCLUDED_)
