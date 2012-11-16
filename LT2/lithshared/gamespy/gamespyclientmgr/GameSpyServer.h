/****************************************************************************
;
;	 MODULE:		GAMESPYSERVER (.H)
;
;	PURPOSE:		Game Spy Server Encapsulation Class
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
	#include "gamespyplayer.h"
#else
	#include "..\gamespy\cengine\goaceng.h"
	#include "..\gamespy\gamespyclientmgr\gamespyplayer.h"
#endif


// Defines...

#define	GSS_MAX_PLAYERS		64

#define GSS_SORT_NAME		0
#define GSS_SORT_PING		1
#define GSS_SORT_FRAGS		2


// Classes...

class CGameSpyServer
{
	// Member functions...

public:
	CGameSpyServer() { Clear(); }
	~CGameSpyServer() { Term(); }

	BOOL				Init(GServer pServer);
	void				Term();

	BOOL				IsInitialized() { return(m_bInit); }

	char*				GetName();
	char*				GetGameType();
	int					GetPing();
	int					GetNumPlayers();
	int					GetMaxPlayers();
	char*				GetMap();
	char*				GetAddress();
	void*				GetHandle() { return(m_pGServer); }

	char*				GetStringValue(char* sKey, char* sDefault = "");
	int					GetIntValue(char* sKey, int nDefault = 0);
	float				GetFloatValue(char* sKey, float fDefault = 0);

	int					UpdatePlayers();

	CGameSpyPlayer*		GetPlayer(int nIndex);
	CGameSpyPlayer*		GetFirstPlayer();
	CGameSpyPlayer*		GetNextPlayer();

	void				SortPlayersByName(BOOL bAscending = TRUE) { SortPlayers(bAscending, GSS_SORT_NAME); }
	void				SortPlayersByPing(BOOL bAscending = TRUE) { SortPlayers(bAscending, GSS_SORT_PING); }
	void				SortPlayersByFrags(BOOL bAscending = FALSE) { SortPlayers(bAscending, GSS_SORT_FRAGS); }

protected:
	void				Clear();
	void				SortPlayers(BOOL bAscending, int nKey);


	// Member variables...

private:
	GServer				m_pGServer;
	BOOL				m_bInit;
	CGameSpyPlayer		m_aPlayers[GSS_MAX_PLAYERS];
	int					m_nNumPlayers;
	int					m_nPlayerIndex;
};



