
#ifndef __ISERVERSHELL_H__
#define __ISERVERSHELL_H__


	#include "ltbasedefs.h"
	#include "ltengineobjects.h"
	#include "iltserver.h"



	class ILTServer;
	extern ILTServer *g_pLTServer;



	/////////////////////////////////////////////////////////////////////
	// IServerShell interface.  You must implement this for a server.
	/////////////////////////////////////////////////////////////////////

	class IServerShell
	{
	public :

						IServerShell() {}
		virtual			~IServerShell() {}

		ILTServer*		GetServerDE() const {return g_pLTServer;}
		ILTServer*		GetLTServer() const {return g_pLTServer;}

		// A message from the server app.
		virtual LTRESULT	ServerAppMessageFn(char *pMsg, int nLen) {return LT_OK;}

		// Notification when new clients come in.
		virtual void	OnAddClient(HCLIENT hClient) {}
		virtual void	OnRemoveClient(HCLIENT hClient) {}

		// You must create an object to represent the client.
		// It uses the object's position to determine what the client can see.
		// The client data comes from the StartGameRequest from the client connecting.
		virtual LPBASECLASS	OnClientEnterWorld(HCLIENT hClient, void *pClientData, uint32 clientDataLen)=0;
		virtual void		OnClientExitWorld(HCLIENT hClient) {}

		// Called before and after you switch worlds.
		virtual void	PreStartWorld(LTBOOL bSwitchingWorlds) {}
		virtual void	PostStartWorld() {}		

		// Message handler.
		virtual void	OnMessage(HCLIENT hSender, uint8 messageID, HMESSAGEREAD hMessage) {}

		// Handler for messages from objects.
		virtual void	OnObjectMessage(LPBASECLASS pSender, uint32 messageID, HMESSAGEREAD hMessage) {}		

		// Command notification.
		virtual void	OnCommandOn(HCLIENT hClient, int command) {}
		virtual void	OnCommandOff(HCLIENT hClient, int command) {}

		// Update loop callback.. do whatever you like in here.
		// Time since the last Update() call is passed in.
		virtual void	Update(LTFLOAT timeElapsed) {}

		// Called when a demo playback is done.
		virtual void	OnPlaybackFinish() {}

		// This is where the main caching takes place.  Call ILTServer::CacheFile() for
		// each sprite, model, texture, and sound that you want to make sure are in
		// memory for the level.  The engine will get everything the level requires 
		// (any models or sprites that are in the level after it is loaded), but will
		// unload everything else.
		virtual void	CacheFiles() {}

		// You need to call SRand() here with a constant (done automatically in C++).
		virtual void	SRand(unsigned int uiRand) {srand(uiRand);}

		// Called when a file is done loading (from a call to ThreadLoadFile).
		// status will be LT_OK or an error if an error occured.
		virtual LTRESULT	FileLoadNotify(const char *pFilename, LTRESULT status) {return LT_OK;}

		// The engine calls this for packets it doesn't understand.
		virtual LTRESULT	ProcessPacket(char *pData, uint32 dataLen, uint8 senderAddr[4], uint16 senderPort) { return LT_OK; }
	};




	#define SERVERSHELL_VERSION 2

	typedef IServerShell* (*CreateServerShellFn)(ILTServer *pServer);
	typedef void (*DeleteServerShellFn)(IServerShell *);
	
	// You must implement these two functions to create and delete your server shell.
	IServerShell* CreateServerShell(ILTServer *pServer);
	void DeleteServerShell(IServerShell *);

	// The HINSTANCE for the DLL.
	extern void *g_hLTDLLInstance;


	#define SETUP_SERVERSHELL()\
		void *g_hLTDLLInstance=0;\
		BEGIN_EXTERNC() \
			__declspec(dllexport) void GetServerShellFunctions(CreateServerShellFn *pCreate, DeleteServerShellFn *pDelete);\
			__declspec(dllexport) int GetServerShellVersion();\
			__declspec(dllexport) void SetInstanceHandle(void *handle);\
		END_EXTERNC()\
		void GetServerShellFunctions(CreateServerShellFn *pCreate, DeleteServerShellFn *pDelete)\
		{\
			*pCreate = CreateServerShell;\
			*pDelete = DeleteServerShell;\
		}\
		int GetServerShellVersion()\
		{\
			return SERVERSHELL_VERSION;\
		}\
		void SetInstanceHandle(void *handle)\
		{\
			g_hLTDLLInstance = handle;\
		}


#endif  // __ISERVERSHELL_H__



