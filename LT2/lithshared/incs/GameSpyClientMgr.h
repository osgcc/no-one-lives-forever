/****************************************************************************
;
;	 MODULE:		GAMESPYCLIENTMGR (.H)
;
;	PURPOSE:		Game Spy Client Manager
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
	#include "gamespyserver.h"
#else
	#include "..\gamespy\cengine\goaceng.h"
	#include "..\gamespy\gamespyclientmgr\gamespyserver.h"
#endif


// Libraries...

#pragma comment(lib, "wsock32.lib")


// Defines...

#define	GSCM_MAX_STRING		128
#define	GSCM_MAX_UPDATES	12


// Classes...

class CGameSpyClientMgr
{
	// Member functions...

public:
	CGameSpyClientMgr() { Clear(); }
	~CGameSpyClientMgr() { Term(); }

	BOOL				Init(const char* sGameName, const char* sSecretKey);
	void				Term();

	BOOL				IsInitialized() { return(m_bInit); }

	int					GetNumServers();
	int					GetState();
	int					GetProgress() { return(m_nProgress); }

	void				ClearServers();
	BOOL				RefreshServers(BOOL bAsync = TRUE);

	CGameSpyServer*		GetServer(int nIndex);
	CGameSpyServer*		GetServerFromHandle(void* pHandle);
	CGameSpyServer*		GetFirstServer();
	CGameSpyServer*		GetNextServer();

	BOOL				ExistNewServer();

	void				SortServersByName(BOOL bAscending = TRUE);
	void				SortServersByPing(BOOL bAscending = TRUE);
	void				SortServersByPlayers(BOOL bAscending = FALSE);
	void				SortServersByMap(BOOL bAscending = TRUE);
	void				SortServersByGameType(BOOL bAscending = TRUE);
	void				SortServers(BOOL bAscending, char* sSortKey, GCompareMode eCompareMode);

	void				Update();

	void				HandleCallback(GServerList pServerList, int nMsg, void* pParam1, void* pParam2);


protected:
	void				Clear();

	BOOL				CreateServerList();
	void				FreeServerList();

	CGameSpyServer*		CreateGameSpyServer(GServer pGServer);


	// Member variables...

private:
	BOOL				m_bInit;
	GServerList			m_pServerList;
	char				m_sGameName[GSCM_MAX_STRING];
	char				m_sSecretKey[GSCM_MAX_STRING];
	int					m_nGetServerIndex;
	int					m_nProgress;
	BOOL				m_bNewServer;
	CGameSpyServer		m_CurServer;
};






