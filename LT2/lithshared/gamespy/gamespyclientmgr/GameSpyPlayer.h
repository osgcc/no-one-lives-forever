/****************************************************************************
;
;	 MODULE:		GAMESPYPLAYER (.H)
;
;	PURPOSE:		Game Spy Player Encapsulation Class
;
;	HISTORY:		08/01/00  [blg]  This file was created
;
;	COMMENT:		Copyright (c) 2000, LithTech, Inc.
;
****************************************************************************/

#pragma once


// Includes...

#ifdef GSCM_LOCAL_BUILD
#include "..\cengine\goaceng.h"
#else
#include "..\gamespy\cengine\goaceng.h"
#endif


// Classes...

class CGameSpyPlayer
{
	// Member functions...

public:
	CGameSpyPlayer() { Clear(); }
	~CGameSpyPlayer() { Term(); }

	BOOL				Init(GServer pGServer, int nIndex);
	void				Term();

	BOOL				IsInitialized() { return(m_bInit); }

	char*				GetName();
	int					GetPing();
	int					GetFrags();
	void*				GetHandle() { return((void*)m_nIndex); }

	char*				GetStringValue(char* sKey, char* sDefault = "");
	int					GetIntValue(char* sKey, int nDefault = 0);
	float				GetFloatValue(char* sKey, float fDefault = 0);

protected:
	void				Clear();


	// Member variables...

private:
	GServer				m_pGServer;
	int					m_nIndex;
	BOOL				m_bInit;
};


