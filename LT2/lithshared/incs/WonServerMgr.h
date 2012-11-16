/****************************************************************************
;
;	 MODULE:		WonServerMgr (.h)
;
;	PURPOSE:		Implements game server side WON functionality
;
;	HISTORY:		11/16/99  [blg]  This file was created
;
;	COMMENT:		Copyright (c) 1999, Monolith Productions, Inc.
;
****************************************************************************/


#ifndef _WONSERVERMGR_H_
#define _WONSERVERMGR_H_


// Includes...

#include "wonshared.h"


// Defines

#define WSM_MAX_WON_SERVERS			16

#define WSM_DEFAULT_GAME_TIMEOUT	10000


// Libs...
#ifndef NO_PRAGMA_LIBS

#ifdef _DEBUG
#pragma comment (lib, "\\proj\\libs\\debug\\wonservermgr.lib")
#else
#pragma comment (lib, "\\proj\\libs\\release\\wonservermgr.lib")
#endif

#endif

// Classes...

class CWonServerMgr
{
	// Member functions...

public:
	CWonServerMgr() { Clear(); }
	virtual	~CWonServerMgr() { Term(); }

	virtual	LTRESULT		Init(const char* sGameDir, const char* sServiceName, DDWORD dwUpdateIntervalSeconds = 60, DDWORD dwFlags = 0);
	virtual	LTRESULT		Term();

	virtual	LTRESULT		AddWonServer(CWonNetAddress& wadServer);

	virtual	LTRESULT		CreateGameService(const char* sDisplayName, CWonNetAddress& wadService, CWonGameHeader* pHeader, CWonGamePlayers* pPlayers, CWonGameData* pData);

	virtual	LTRESULT		RegisterGameService(DDWORD dwLifeSpan = 300, DDWORD dwTimeOut = WSM_DEFAULT_GAME_TIMEOUT);

	virtual LTRESULT		GetGameService(CWonGameService** ppGame);

	virtual LTRESULT		SetUpdateIntervalSeconds(DDWORD dwUpdateIntervalSeconds);
	virtual LTRESULT		SetNextUpdateTime(DDWORD dwNextUpdateTime);
	virtual LTRESULT		ForceNextUpdate();

	virtual	LTRESULT		UpdateGameService(DDWORD dwTimeOut = WSM_DEFAULT_GAME_TIMEOUT);

	virtual LTRESULT		RemoveGameService(DDWORD dwTimeOut = WSM_DEFAULT_GAME_TIMEOUT);

	virtual	LTRESULT		Update(DDWORD dwTimeOut = WSM_DEFAULT_GAME_TIMEOUT);

protected:
	void					Clear();


	// Member variables...

protected:
	DDWORD					m_dwFlags;
	char					m_sGameDir[WSH_MAX_STRING_LEN];
	char					m_sService[WSH_MAX_STRING_LEN];
	WONIPAddress			m_aWonServers[WSM_MAX_WON_SERVERS];
	DDWORD					m_dwNumWonServers;
	DDWORD					m_dwLifeSpan;
	DDWORD					m_dwNextUpdateTime;
	DDWORD					m_dwUpdateInterval;
	CWonGameService*		m_pGameService;
	DBOOL					m_bValid;
};


// EOF...

#endif


