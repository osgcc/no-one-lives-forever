/****************************************************************************
;
;	 MODULE:		WonClientMgr (.h)
;
;	PURPOSE:		Implements game client side WON functionality
;
;	HISTORY:		11/18/99  [blg]  This file was created
;
;	COMMENT:		Copyright (c) 1999, Monolith Productions, Inc.
;
****************************************************************************/


#ifndef _WONCLIENTMGR_H_
#define _WONCLIENTMGR_H_


// Includes...

#include "wonshared.h"
#include <list>
#include <algorithm>


// Defines

#define WCM_MAX_WON_SERVERS			16		// maximums

#define WCM_DEFAULT_PING_TIMEOUT	5000	// default ping timeout (in ms)
#define WCM_DEFAULT_GAME_TIMEOUT	10000	// default game timeout (in ms)

#define WCM_PS_IDLE					0		// ping status
#define WCM_PS_BUSY					1

#define WCM_GS_IDLE					0		// get status
#define WCM_GS_BUSY					1

#define WCM_DS_UNCHANGED			0		// data status
#define WCM_DS_CHANGED				1

#define WCM_AS_IDLE					0		// all status
#define WCM_AS_BUSY					1

#define WCM_PING_FREQ				100		// next ping frequency (in ms)


// Libs...
#ifndef NO_PRAGMA_LIBS

#ifdef _DEBUG
#pragma comment (lib, "\\proj\\libs\\debug\\wonclientmgr.lib")
#else
#pragma comment (lib, "\\proj\\libs\\release\\wonclientmgr.lib")
#endif

#endif


// Typedefs...

typedef std::list<CWonGameService*> WONGAMELIST;
typedef WONGAMELIST::iterator		WONGAMELISTITER;


// Externs...

class CWonClientMgr;


// Structures...

typedef struct WonPingInst_struct
{
	CWonClientMgr*		pWonClientMgr;
	CWonGameService*	pGame;
	DWORD				dwPing;
	HWONCOMPLETION		hCompletion;

}	WONPINGINST;


// Classes...

class CWonClientMgr
{
	// Member functions...

public:
	CWonClientMgr() { Clear(); }
	virtual	~CWonClientMgr() { Term(); }

	virtual	LTRESULT		Init(const char* sGameDir, const char* sServiceName, DDWORD dwFlags = 0);
	virtual	LTRESULT		Term();
	virtual	LTRESULT		Clear();

	virtual	LTRESULT		AddWonServer(CWonNetAddress& wadServer);

	virtual	LTRESULT		GetWonGameServicesAndPingsAsync(DDWORD dwGameTimeOut = WCM_DEFAULT_GAME_TIMEOUT, DWORD dwPingTimeOut = WCM_DEFAULT_PING_TIMEOUT);
	virtual	LTRESULT		GetWonGameServices(DDWORD dwTimeOut = WCM_DEFAULT_GAME_TIMEOUT);
	virtual	LTRESULT		GetWonGameServicesAsync(DDWORD dwTimeOut = WCM_DEFAULT_GAME_TIMEOUT);
	virtual	LTRESULT		GetGameServicePings(DWORD dwTimeOut = WCM_DEFAULT_PING_TIMEOUT);
	virtual	LTRESULT		GetGameServicePingsAsync(DWORD dwTimeOut = WCM_DEFAULT_PING_TIMEOUT);
	virtual	LTRESULT		GetGameServicePingAsync(CWonGameService* pGame, DWORD dwTimeOut = WCM_DEFAULT_PING_TIMEOUT);
	virtual	LTRESULT		GetFirstGameService(CWonGameService** ppGame);
	virtual	LTRESULT		GetNextGameService(CWonGameService** ppGame);
	virtual	LTRESULT		GetNumGameServices(DDWORD* pNumServices);
	virtual	LTRESULT		GetAsyncGameStatus(DDWORD* pGetStatus);
	virtual	LTRESULT		GetAsyncPingStatus(DDWORD* pPingStatus);
	virtual	LTRESULT		GetAsyncDataStatus(DDWORD* pDataStatus);
	virtual	LTRESULT		GetAsyncAllStatus(DDWORD* pDataStatus);
	virtual LTRESULT		GetAsyncGameCompletionPercentage(DDWORD* pPercent);
	virtual LTRESULT		GetAsyncPingCompletionPercentage(DDWORD* pPercent);
	virtual LTRESULT		GetAllGameServiceData(CWonGameService* pGame, DWORD dwTimeOut = WCM_DEFAULT_GAME_TIMEOUT);
	virtual	LTRESULT		GetAllGameServiceDataAsync(CWonGameService* pGame, DDWORD dwTimeOut = WCM_DEFAULT_GAME_TIMEOUT);

	virtual	LTRESULT		RemoveAllGameServices();

	virtual	LTRESULT		SortGameServices(DDWORD dwSortKey, DDWORD dwSortDir);

	virtual	LTRESULT		OnGetDirCallback(HWONDIRENTITY hDirEntity);
	virtual	LTRESULT		OnAsyncGetGameCompletion();
	virtual	LTRESULT		OnAsyncPingCompletion(WONPINGINST* pPingInst);
	virtual	LTRESULT		OnAsyncAllDataCompletion();

	virtual LTRESULT		Update();

protected:
	virtual	BOOL				PingGameAsync(CWonGameService* pGame);
	virtual	CWonGameService*	AddWonGameService(const char* sName, const char* sDisplayName, CWonNetAddress& wadService, CWonGameHeader* pHdr, DDWORD dwFlags = 0);
	virtual	void				PreGetServices();
	virtual	CWonGameService*	GetNextGameServiceToPing();


	// Member variables...

protected:
	DDWORD					m_dwFlags;
	char					m_sGameDir[WSH_MAX_STRING_LEN];
	char					m_sService[WSH_MAX_STRING_LEN];
	WONIPAddress			m_aWonServers[WCM_MAX_WON_SERVERS];
	DDWORD					m_dwNumWonServers;
	DDWORD					m_dwNumAllWonServices;
	WONGAMELIST				m_listGames;
	WONGAMELIST				m_listPingGames;
	WONGAMELISTITER			m_iterGames;
	WONGAMELISTITER			m_iterPings;
	DDWORD					m_dwAsyncGameStatus;
	DDWORD					m_dwAsyncPingStatus;
	DDWORD					m_dwAsyncDataStatus;
	DDWORD					m_dwAsyncAllStatus;
	DDWORD					m_dwNumPingsDone;
	DDWORD					m_dwNumGameGetsDone;
	DDWORD					m_dwPingTimeOut;
	CWonGameService*		m_pAllDataGame;
	HWONCOMPLETION			m_hCurPingCompletion;
	HWONCOMPLETION			m_hGetGameCompletion;
	HWONCOMPLETION			m_hAllDataCompletion;
	HWONDIRENTITY			m_hAllDataDirEntity;
	DBOOL					m_bWantAsyncPings;
	DBOOL					m_bSingleGamePing;
	DBOOL					m_bValid;
	DBOOL					m_bPingCS;
	CRITICAL_SECTION		m_csPings;
	DDWORD					m_timeNextPing;
};


// EOF...

#endif


