
// This file defines the server interface.

#ifndef __SERVER_INTERFACE_H__
#define __SERVER_INTERFACE_H__


	#include "ltbasedefs.h"


	#define SI_VERSION	2


	// Update flags for the server.
		
		// Non-active (ie: the server should just eat up time but not update anything).
		#define UPDATEFLAG_NONACTIVE		1

	
	// Create status.	
	#define SI_CREATESTATUS	int
	#define SI_OK				0			// Create a server successfully.
	#define SI_ALREADYINSTANCED	1			// A server has already been instanced.
	#define SI_INVALIDVERSION	2			// Different server version.
	#define SI_ERRORINITTING	3			// Error initializing.
	#define SI_CANTLOADRESOURCEMODULE	4	// Couldn't load de_msg.dll.



	// Client info structure.
	#define	MAX_CLIENTINFO_NAME	64
	struct ClientInfo
	{
		char	m_sName[MAX_CLIENTINFO_NAME];
		uint32	m_ClientID;
		float	m_Ping;
	};



	// You should derive from this class and pass a pointer to it to
	// ServerInterface::SetHandler so it can talk back to you.
	class ServerAppHandler
	{
	public:

		// This message comes from ServerDE::SendToServerApp.  Format stuff
		// going back and forth into strings to reduce incompatibilities.
		virtual LTRESULT ShellMessageFn(char *pInfo, uint32 nLen) {return LT_OK;}

		// All console output goes into here.
		virtual LTRESULT ConsoleOutputFn(char *pszMsg) {return LT_OK;}
		
		// Called when the server has run out of memory.  A message should
		// be displayed and exit() should be called immediately.. if you don't,
		// LT exits() right after calling OutOfMemory().
		virtual LTRESULT OutOfMemory() {return LT_OK;}

		// The engine calls this for packets it doesn't understand (used for Gamespy).
		virtual LTRESULT ProcessPacket(char *pData, uint32 dataLen, uint8 senderAddr[4], uint16 senderPort) {return LT_OK;}
	};

	
	class ServerInterface
	{
	public:

		// Set this on startup.. this is how the engine and game talk to you.
		virtual LTRESULT SetAppHandler(ServerAppHandler *pHandler)=0;


		// Run a string in the console.
		virtual LTRESULT RunConsoleString(char *pStr)=0;

		// Get access to console variables.  hVar is filled in.  If a variable with the given
		// name doesn't exist and pDefaultVal is set, it'll set the value to pDefaultVal
		// and return LT_FINISHED.  If it already existed, it returns LT_OK.
		virtual LTRESULT GetConsoleVar(char *pName, HCONSOLEVAR *hVar, char *pDefaultVal)=0;
		virtual LTRESULT GetVarValueFloat(HCONSOLEVAR hVar, float *val)=0;
		virtual LTRESULT GetVarValueString(HCONSOLEVAR hVar, char *pStr, uint32 maxLen)=0;

		// Load/save config files into the server's console state.
		virtual LTRESULT LoadConfigFile(char *pFilename)=0;
		virtual LTRESULT SaveConfigFile(char *pFilename)=0;

		// Calls ServerShellDE::ServerAppMessageFn (the equivalent of the game
		// calling ServerDE::SendToServerApp but in the opposite direction).
		// Returns LT_NOTFOUND if the server shell hasn't been created (it gets
		// created in AddResources).
		virtual LTRESULT SendToServerShell(char *pInfo, int nLen)=0;
	
		// Add resources for the server to use.
		virtual LTBOOL	AddResources(char **pResources, uint32 nResources)=0;

		// Load the object.lto file.
		virtual LTBOOL LoadBinaries( )=0;

		// Look thru the available worlds.
		virtual FileEntry*	GetFileList(char *pDirName)=0;
		virtual void	FreeFileList(FileEntry *pList)=0;

		// Open a file up.  Pass in the relative filename.
		// Free the file by calling DStream::Release().
		virtual LTRESULT OpenFile(char *pFilename, ILTStream **pStream) = 0;

		// Copies a file.  This function is useful for copying files out of the
		// rez file to a temporary file, so you can do special operations on it like
		// LoadLibrary.
		virtual LTRESULT CopyFile( const char *pszSourceFile, const char *pszDestFile ) = 0;

		// Sets game info.  Call this before LoadBinaries.
		virtual LTBOOL	SetGameInfo( void *pGameInfo, uint32 nGameInfoLen ) = 0;

		// Look at the clients.
		virtual int		GetNumClients()=0;
		virtual LTBOOL	GetClientName(int index, char *pName, int maxChars)=0;
		virtual LTBOOL	GetClientInfo(int index, ClientInfo* pInfo)=0;
		virtual	LTBOOL	BootClient(uint32 dwClientID)=0;
		virtual LTRESULT GetClientPing( uint32 nClientId, float &ping )=0;

		// When an error occurs, you can get the error code and error string.
		virtual int		GetErrorCode()=0;
		virtual void	GetErrorString(char *pString, int maxLen)=0;

		// Update as often as possible.		
		virtual LTBOOL	Update(long flags)=0;

		// Call this function, with the app's LTGUID, before calling any other
		// network functions. pDriver can be LTNULL to use the default net driver.
		// No flags are currently supported.
		virtual LTBOOL	InitNetworking(char *pDriver, uint32 dwFlags)=0;

		// Gets a list (and count) of enumerated services.
		virtual LTBOOL	GetServiceList(NetService *&pListHead)=0;

		// Call this function when you are finished using the list returned by
		// GetServiceList().
		virtual LTBOOL	FreeServiceList(NetService *pListHead)=0;

		// Selects the given service as the one to use.
		virtual LTBOOL	SelectService(HNETSERVICE hNetService)=0;

		// Updates the sessions's name (only the host can do this).
		virtual LTBOOL	UpdateSessionName(const char* sName)=0;

		// Hosts the game session.
		virtual LTBOOL	HostGame( NetHost &hostInfo )=0;

		// Gets the tcp/ip address of the main driver if available.
		virtual LTBOOL	GetTcpIpAddress(char* sAddress, uint32 dwBufferSize, unsigned short &hostPort)=0;

		// Send a packet thru tcp/ip if we're using tcp/ip.
		virtual LTRESULT	SendTo(const void *pData, uint32 len, const char *sAddr, uint32 port)=0;
	};

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __SERVERAPI_EXPORT__
#define SERVERAPI	__declspec( dllexport )
#else
#define SERVERAPI	__declspec( dllimport )
#endif

	// The server DLL implements these functions to create and delete a 
	// server.  You can only have one server at a time.  Pass in SI_VERSION to CreateServer.
	SERVERAPI SI_CREATESTATUS CreateServer(int version, LTGUID &appGuid, ServerInterface **ppServer);
	SERVERAPI void DeleteServer();

#ifdef __cplusplus
}
#endif

#endif  // __SERVER_INTERFACE_H__

