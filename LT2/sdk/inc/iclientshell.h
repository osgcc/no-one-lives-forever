
#ifndef __ICLIENTSHELL_H__
#define __ICLIENTSHELL_H__


	#include "ltbasedefs.h"
	#include "iltstream.h"



	class ILTClient;
	extern ILTClient *g_pLTClient;



	/////////////////////////////////////////////////////////////////////
	// IClientShell interface. This is full of callback functions that
	// Lithtech will call to notify you of things.
	/////////////////////////////////////////////////////////////////////

	class IClientShell
	{
	public :

		virtual		~IClientShell() {}

		ILTClient*	GetClientDE() const	{return g_pLTClient;}


		// Notification for when commands go on and off.
		virtual void OnCommandOn(int command) {}
		virtual void OnCommandOff(int command) {}

		// Key up/down notification. Try to use command notification whenever
		// possible because key up/down notification isn't portable.
		virtual void OnKeyDown(int key, int rep) {}
		virtual void OnKeyUp(int key) {}

		// Handle messages from the server.
		virtual void OnMessage(uint8 messageID, HMESSAGEREAD hMessage) {}

		// Called when a model hits a model key.
		virtual void OnModelKey(HLOCALOBJ hObj, ArgList *pArgs) {}

		// Called right before a world is loaded.  After this call, it shows whatever
		// you've drawn to the screen, then loads the world.
		virtual void PreLoadWorld(char *pWorldName) {}

		// Called when you enter/exit a world.  You lose ALL server objects when
		// you exit the world, so don't reference them after exiting the world!
		virtual void OnEnterWorld() {}
		virtual void OnExitWorld() {}

		// Called when the server tells the client about a special effect object.
		virtual void SpecialEffectNotify(HLOCALOBJ hObj, HMESSAGEREAD hMessage) {}

		// Called when an object with client flag CF_NOTIFYONREMOVE is removed.
		virtual void OnObjectRemove(HLOCALOBJ hObj) {}

		virtual void PreUpdate() {}
		virtual void Update() {}
		virtual void PostUpdate() {}

		// Called when an object is about to move.
		virtual LTRESULT OnObjectMove(HLOCALOBJ hObj, LTBOOL bTeleport, LTVector *pNewPos) {return LT_OK;}
		virtual LTRESULT OnObjectRotate(HLOCALOBJ hObj, LTBOOL bTeleport, LTRotation *pNewRot) {return LT_OK;}

		// Called after the engine has fully initialized and is ready to go!
		// The engine doesn't initialize the renderer itself, but it passes in the 
		// default RMode it would use to initialize it (from the "RenderDLL", "ScreenWidth",
		// and "ScreenHeight" console variables).  You must call SetRenderMode to
		// initialize the renderer in here.
		// Initialize appGuid before returning.  This controls what netgames you can query and
		// which ones you can connect to.
		// If this returns something other than LT_OK the engine will shutdown immediately.
		virtual LTRESULT OnEngineInitialized(RMode *pMode, LTGUID *pAppGuid) {return LT_ERROR;}

		// Called before the engine uninitializes itself.
		virtual void OnEngineTerm() {}

		// Called when a particular engine event happens.
		// Parameters:
		//		pShell - Game client shell.
		//		dwEvent - Event ID.  One of the LTEVENT_ values
		//		dwParam - Event data.
		virtual void OnEvent( uint32 dwEventID, uint32 dwParam ) {}

		// Called when an object moved on the client side collides with another.
		virtual LTRESULT OnTouchNotify(HOBJECT hMain, CollisionInfo *pInfo, float forceMag) {return LT_OK;}

		// The engine uses this to sync the random number generator.  Just call
		// srand() with a constant.
		virtual void SRand() {srand(123);}

		// Called when a demo is about to be recorded or played.  Save/load the variables
		// that will affect demo playback.
		virtual void DemoSerialize(ILTStream *pStream, LTBOOL bLoad) {}

		// Called when a sound is played by the client or server
		virtual void OnPlaySound(PlaySoundInfo *pPlaySoundInfo) {}

		// Called when the engine wants to tell the game a disconnection code (a.k.a. hack)
		virtual void SetDisconnectCode(uint32 nCode, const char *pMsg, uint32 nSubReason = 0) {}
	}; 


	typedef IClientShell* LPCLIENTSHELLDE;


	#define CLIENTSHELL_VERSION	2

	typedef IClientShell* (*CreateClientShellFn)(ILTClient *pClientDE);
	typedef void (*DeleteClientShellFn)(IClientShell *);
	
	// You must implement these two functions to create and delete your client shell.
	// When you create it, you should set all of its function pointers.
	IClientShell* CreateClientShell(ILTClient *pClientDE);
	void DeleteClientShell(IClientShell *);

	// The HINSTANCE for the DLL.
	// You MUST set g_pClientDE to pClientDE in CreateClientShell.
	extern void *g_hLTDLLInstance;


	#define SETUP_CLIENTSHELL()\
		void *g_hLTDLLInstance=0;\
		ILTClient *g_pLTClient=0;\
		BEGIN_EXTERNC() \
			__declspec(dllexport) void GetClientShellFunctions(CreateClientShellFn *pCreate, DeleteClientShellFn *pDelete);\
			__declspec(dllexport) int GetClientShellVersion();\
			__declspec(dllexport) void SetInstanceHandle(void *handle);\
		END_EXTERNC()\
		void GetClientShellFunctions(CreateClientShellFn *pCreate, DeleteClientShellFn *pDelete)\
		{\
			*pCreate = CreateClientShell;\
			*pDelete = DeleteClientShell;\
		}\
		int GetClientShellVersion()\
		{\
			return CLIENTSHELL_VERSION;\
		}\
		void SetInstanceHandle(void *handle)\
		{\
			g_hLTDLLInstance = handle;\
		}


#endif  // __ICLIENTSHELL_H__

