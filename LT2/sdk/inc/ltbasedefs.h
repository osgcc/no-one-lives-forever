
#ifndef __LTBASEDEFS_H__
#define __LTBASEDEFS_H__

	#include "lithtech.h"

	#include <stdlib.h>
	#include <string.h>
	#include "ltassert.h"

	#include "ltcodes.h"

	#define LTNULL 0
	#define LTTRUE 1
	#define LTFALSE 0

	#define BEGIN_EXTERNC() extern "C" \
		{
	#define END_EXTERNC() };


	class BaseClass;
	#define LPBASECLASS BaseClass*
	class IAggregate;
	#define LPAGGREGATE IAggregate*

	// If the dest buffer is a static buffer, use LTStrCpy, else do
	// a normal string copy.
	#define SAFE_STRCPY(dest, src) \
	{\
		if(sizeof(dest) > 4)\
		{\
			LTStrCpy(dest, src, sizeof(dest));\
		}\
		else\
		{\
			strcpy(dest, src);\
		}\
	}

	// Safe string copy (strncpy doesn't always null terminate but this does).
	inline void LTStrCpy(char *pDest, const char *pSrc, unsigned long destBytes)
	{
		if(destBytes == 0)
			return;

		strncpy(pDest, pSrc, destBytes - 1);
		pDest[destBytes - 1] = 0; 
	}


	// All worlds have a base light animation which tells the engine what polies
	// are even using lightmaps.  Game code can't create an animation with this name.
	#define BASE_LIGHTANIM_NAME		"LightAnim_BASE"



	// Used in GetFileList/FreeFileList.
	#define TYPE_FILE		1
	#define TYPE_DIRECTORY	2
	
	struct FileEntry
	{
		int			m_Type;				// Directory or file?
		char		*m_pBaseFilename;	// pic1.pcx
		char		*m_pFullFilename;	// interface/bitmaps/pic1.pcx
		FileEntry	*m_pNext;
	};


	// Used in the counter functions.
	struct LTCounter
	{
		unsigned long	m_Data[4];
	};


	// Maximum number of skins per model.
	#define MAX_MODEL_TEXTURES	2

	

	#define DEFINE_HANDLE_TYPE(name) \
		typedef struct {int __nothing;} ##name##_t, *name;


	#define MAX_CS_FILENAME_LEN	127

	// HMESSAGE defines

	// Maximum number of bytes in a communications message.
	#define MAX_PACKET_LEN		4096

	// Maximum number of bytes a single object can save into MID_SAVEOBJECT message.
	#define MAX_SAVEOBJECT_LEN	8192


	// Model state flags.
	#define MS_PLAYDONE		1	// The (nonlooping) model has finished playing the animation.


	// HDECOLOR stuff.
	typedef uint32 HLTCOLOR;
	#define COLOR_TRANSPARENCY_MASK	0x80000000

	// r, g, and b, are 0-255 integers.
	#define SETRGB(r,g,b) \
		(((uint32)(r) << 16) | ((uint32)(g) << 8) | ((uint32)(b)))
		
	// r, g, and b are 0-1 floats.
	#define SETRGB_F(r,g,b) \
		(((uint32)((r)*255.0f) << 16) | ((uint32)((g)*255.0f) << 8) | ((uint32)((b)*255.0f)))

	// Setup a color with transparency.
	#define SETRGB_T(r,g,b)		(SETRGB((r),(g),(b)) | COLOR_TRANSPARENCY_MASK)
	#define SETRGB_FT(r,g,b)	(SETRGB_F((r),(g),(b)) | COLOR_TRANSPARENCY_MASK)

	// Gets r, g, and b as 0-255 integers.
	#define GETR(val) (((val) >> 16) & 0xFF)
	#define GETG(val) (((val) >> 8) & 0xFF)
	#define GETB(val) ((val) & 0xFF)
	#define GETRGB(val, r, g, b) \
	{\
		(r) = GETR(val);\
		(g) = GETG(val);\
		(b) = GETB(val);\
	}

	// Gets translucency value (into a 0 or 1 integer).
	#define GETT(val) (!!((val) & COLOR_TRANSPARENCY_MASK))

		
	class ILTMessage;
	typedef ILTMessage*		HMESSAGEREAD;
	typedef ILTMessage*		HMESSAGEWRITE;



	// Handle definitions.. it defines them in this wierd way so 
	// you can't accidentally cast between them.
	DEFINE_HANDLE_TYPE(HCLASS)
	DEFINE_HANDLE_TYPE(HSURFACE)
	DEFINE_HANDLE_TYPE(HLTFONT)
	DEFINE_HANDLE_TYPE(HSTRING)
	DEFINE_HANDLE_TYPE(HLTSOUND)
	DEFINE_HANDLE_TYPE(HCLIENT);
	DEFINE_HANDLE_TYPE(HATTACHMENT);
	DEFINE_HANDLE_TYPE(HNETSERVICE);
	DEFINE_HANDLE_TYPE(HCONSOLEVAR);

	typedef unsigned long HPRELIGHTANIM;
	typedef unsigned long HPREOBJECT;



	
	
	// ---------------------------------------------------------------- //
	// Here is the layout of all message IDs.
	// ---------------------------------------------------------------- //
	
	// Server->Client (0-255):
	// DirectEngine reserves 0-15 and defines:
	#define STC_BPRINT	0	// Used for debugging.. print a message in the console.

	// Client->Server (0-255):
	// DirectEngine reserves 0-15.

	// Object->Object (0-65k)
	// 0-1000 reserved.
	// 1000-2000 shared general messages (damage, I see you, etc..)
	// 2000-2500 Riot
	// 3500-4000 Blood 2
	// 4000-4500 Dreadon


	// This is used all over to classify which side of a polygon something's on.
	typedef enum
	{
		BackSide=0,
		FrontSide=1,
		Intersect=2
	} PolySide;


	


	#define MAX_FORCEUPDATE_OBJECTS	200
	struct ForceUpdate
	{
		HOBJECT	*m_Objects; // This array is MAX_FORCEUPDATE_OBJECTS large.
		uint32  m_nObjects;
	};



	#define MAX_OCS_CLASSNAME_LEN	64


	// ObjectCreateStruct::m_CreateFlags
		// The default behavior - if the files this object needs are not loaded, the
		// engine will load them up.  If this flag is not set, the object won't be
		// visible until its file is loaded (from a ThreadLoadFile or an object 
		// created with this flag set).
		// This is currently only supported by models and their textures.
		// Note: if this is set and the needed file is being loaded in a thread, 
		// it will wait for the thread to finish loading.
		#define OCS_AUTOLOAD		(1<<0)


	// This structure is used when creating objects.  When you want to
	// create an object, you call ILTServer::CreateObject with one of these.
	// The structure you pass in is passed to the object's PostPropRead function,
	// where it can override whatever it wants to.
	struct ObjectCreateStruct
	{
				ObjectCreateStruct()
				{
					Clear();
				}

		void	Clear()
		{
			int i;

			m_ObjectType = 0;
			m_ContainerCode = 0;
			m_CreateFlags = OCS_AUTOLOAD;
			m_Flags = 0;
			m_Flags2 = 0;
			m_Pos.Init();
			m_Scale.Init(1.0f, 1.0f, 1.0f);
			m_Rotation.Init();
			m_UserData = 0;
			m_ClassName[0] = 0;
			m_Filename[0] = 0;
			
			for(i=0; i < MAX_MODEL_TEXTURES; i++)
			{
				m_SkinNames[i][0] = 0;
			}
			
			m_Name[0] = 0;
			m_NextUpdate = 0.0f;
			m_fDeactivationTime = 0.0f;
		}
		
		// Main info.
		uint16			m_ObjectType;
		uint16			m_ContainerCode;	// Container code if it's a container.  It's in here because
											// you can only set it at creation time.
		uint32			m_CreateFlags;		// Combination of OCS_ flags above;
		uint32			m_Flags;
		uint32			m_Flags2;
		LTVector		m_Pos;
		LTVector		m_Scale;
		LTRotation		m_Rotation;

		uint32			m_UserData;			// User data


		// NOTE: this is ONLY used during MID_PRECREATE messages.  The engine fills this in
		// before calling MID_PRECREATE so the object can get its class info during the 
		// MID_PRECREATE call.  Otherwise it is not used at all.
		char			m_ClassName[MAX_OCS_CLASSNAME_LEN];

		char			m_Filename[MAX_CS_FILENAME_LEN+1];	// This is the model, sound, or sprite filename.
															// It also can be the WorldModel name.
															// This can be zero-length when it's not needed.
		union
		{
			char		m_SkinName[MAX_CS_FILENAME_LEN+1];	// This can be zero-length.. if you set it for an 
															// OT_MODEL, it's the skin filename.
			char		m_SkinNames[MAX_MODEL_TEXTURES][MAX_CS_FILENAME_LEN+1];
		};

		// Server only info.
		char			m_Name[MAX_CS_FILENAME_LEN+1];		// This object's name.
		float			m_NextUpdate;						// This will be the object's starting NextUpdate.
		float			m_fDeactivationTime;				// Amount of time before object deactivates self
	};

	// Initialize an ObjectCreateStruct.
	#define INIT_OBJECTCREATESTRUCT(theStruct) \
	{ \
		(theStruct).Clear();\
	}


	// Model hook.
	#define MHF_USETEXTURE		1	// Use the texture for this model (if any).
	struct ModelHookData
	{
		HLOCALOBJ		m_hObject;
		unsigned long	m_Flags;		// Combination of MHF_ flags above.
		unsigned long	m_ObjectFlags;	// The model's object flags.  You can modify them
										// in here without changing the model's flags
										// permanently.
		LTVector		*m_LightAdd;	// RGB 0-255
		LTVector		*m_ObjectColor; // RGB 0-255
	};


	
	// Model instance hook data.
	#define MIH_CLIPPLANE		(1<<0)

	class ModelInstanceHookData
	{
	public:
		uint32		m_Flags;
		
		// Extra clip plane in world space, used if MIH_CLIPPLANE is set.
		LTPlane		m_ClipPlane;
	};

	// One of these can be associated with each model object and this function will be
	// called before rendering the model.
	// hObj: The model object about to be rendered.
	// pData: You fill this in.
	// flags: Currently unused.
	typedef void (*ModelInstanceHookFn)(HLOCALOBJ hObj, ModelInstanceHookData *pData, uint32 flags);


	// For Canvases.
	class ILTCustomDraw;
	typedef void (*CanvasDrawFn)(ILTCustomDraw *pDraw, HLOCALOBJ hObj, void *pUser);


	// Render modes are what are used to describe a video mode/video card.
	struct RMode
	{
		LTBOOL			m_bHardware;

		char			m_RenderDLL[256];		// What DLL this comes from.		
		char			m_InternalName[128];	// This is what the DLLs use to identify a card.
		char			m_Description[128];		// This is a 'friendly' string describing the card.
		
		uint32			m_Width, m_Height, m_BitDepth;
		RMode			*m_pNext;
	};

	// The ID of the description string contained in render DLLs.
	#define RDLL_DESCRIPTION_STRINGID	5

	// The blend modes for rendering optimized surfaces
	enum LTSurfaceBlend
	{
		LTSURFACEBLEND_ALPHA, // Alpha blend (lerp(src, dest, alpha))
		LTSURFACEBLEND_SOLID, // Solid (src)
		LTSURFACEBLEND_ADD, // Add (src + dest)
		LTSURFACEBLEND_MULTIPLY, // Multiply (src * dest)
		LTSURFACEBLEND_MULTIPLY2, // Multiply * 2 (src * dest * 2)
		LTSURFACEBLEND_MASK, // Mask ((1 - src) * dest)
		LTSURFACEBLEND_MASKADD // Mask & Add (src + (1 - src) * dest)
	};


	// Device input for device tracking
	#define MAX_INPUT_BUFFER_SIZE	32

	#define	DEVICETYPE_KEYBOARD		1
	#define DEVICETYPE_MOUSE		2
	#define DEVICETYPE_JOYSTICK		4
	#define DEVICETYPE_UNKNOWN		8
	
	#define CONTROLTYPE_UNKNOWN		0			// unknown type
	#define CONTROLTYPE_XAXIS		1			// horizontal axis, such as left-right motion of a mouse
	#define CONTROLTYPE_YAXIS		2			// vertical axis, such as forward-backward motion of a mouse
	#define CONTROLTYPE_ZAXIS		3			// z-axis, such as a wheel on a mouse or a throttle on a joystick
	#define CONTROLTYPE_RXAXIS		4			// rotation around the x-axis
	#define CONTROLTYPE_RYAXIS		5			// rotation around the y-axis
	#define CONTROLTYPE_RZAXIS		6			// rotation around the z-axis
	#define CONTROLTYPE_SLIDER		7			// a slider axis
	#define CONTROLTYPE_BUTTON		8			// a mouse button
	#define CONTROLTYPE_KEY			9			// a key on a keyboard
	#define CONTROLTYPE_POV			10			// point-of-view indicator or "hat"

	struct DeviceInput
	{
		uint32			m_DeviceType;			// type of input device (DEVICETYPE_ defines above)
		char			m_DeviceName[128];		// name of input device

		uint32			m_ControlType;			// type of control that changed (CONTROLTYPE_ defines above)
		char			m_ControlName[64];		// name of control that changed
		uint32			m_InputValue;			// input value for the control
	};

	// Device Object for listing objects on a particular device
	struct DeviceObject
	{
		uint32		m_DeviceType;			// type of input device (DEVICETYPE_ defines above)
		char		m_DeviceName[128];		// name of input device ("Keyboard", "Mouse", etc.)

		uint32		m_ObjectType;			// type of object (CONTROLTYPE_ defines above)
		char		m_ObjectName[64];		// name of object ("x-axis", "button 0", etc.)

		float		m_RangeLow;				// low end of range for this object
		float		m_RangeHigh;			// high end of range for this object

		DeviceObject *m_pNext;
	};
	
	// Device Binding info for GetDeviceBindings()

	#define MAX_ACTIONNAME_LEN 30
	#define INPUTNAME_LEN 100

	struct GameAction
	{
		int			nActionCode;						// action number from config file
		char		strActionName[MAX_ACTIONNAME_LEN];	// name of action from config file
		float		nRangeLow;							// low range if used (zero if not used)
		float		nRangeHigh;							// high range if used (zero if not used)
		GameAction	*pNext;								// next in list

	};

	struct DeviceBinding
	{
		char			strDeviceName[INPUTNAME_LEN];		// name of device for this trigger
		char			strTriggerName[INPUTNAME_LEN];		// name of this trigger (device object name)
		float			nScale;								// scale to multiply input by
		float			nRangeScaleMin;						// min for range scale
		float			nRangeScaleMax;						// max for range scale
		float			nRangeScalePreCenterOffset;			// offset of cent value for input data
		GameAction		*pActionHead;						// list of actions bound to this trigger
		DeviceBinding	*pNext;								// next in list
	};



	// Structure used by a driver to describe a net service (such as ipx or tcp/ip).
	#define MAX_NETSERVICENAME_LEN	128
	class NetService
	{
	public:
		HNETSERVICE	m_handle;
		uint32		m_dwFlags; // Combination of NETSERVICE_ flags.
		LTGUID		m_guidService;
		char		m_sName[MAX_NETSERVICENAME_LEN];
		NetService	*m_pNext;
	};


	// Structure used by a driver to describe a specific net session.
	#define MAX_NETSESSIONNAME_LEN	4096
	#define MAX_NETPASSWORD_LEN		64
	#define MAX_HOSTIP_LEN			32
	#define NO_HOST_PORT			0xFFFF

	class NetSession
	{
	public:
					NetSession() {Clear();}
		virtual		~NetSession() {}

		void		Clear()
		{
			m_dwFlags = 0;
			m_dwMaxPlayers = 0;
			m_dwCurPlayers = 0;
			m_Ping = 0;
			m_sName[0] = 0;
			m_sPassword[0] = 0;
			m_HostIP[0] = 0;
			m_HostPort = NO_HOST_PORT;
			m_pNext = LTNULL;
		}

		uint32		m_dwFlags;
		LTGUID		m_guidApp;
		LTGUID		m_guidInst;
		uint32		m_dwMaxPlayers;
		uint32		m_dwCurPlayers;
		uint32		m_Ping;	// Ping time in milliseconds.
		
		// Host info.  0 length string and NO_HOST_PORT if not on TCP/IP.
		char		m_HostIP[MAX_HOSTIP_LEN];
		uint32		m_HostPort;

		char		m_sName[MAX_NETSESSIONNAME_LEN];
		char		m_sPassword[MAX_NETPASSWORD_LEN];
		NetSession	*m_pNext;
	};


	// Structure used by to instruct a driver to create/host a new session.
	struct NetHost
	{
		uint32		m_Port; // Port if TCP/IP.  If zero, it uses the default.
		uint32		m_dwFlags;
		uint32		m_dwMaxPlayers;
		char		m_sName[MAX_NETSESSIONNAME_LEN];
		char		m_sPassword[MAX_NETPASSWORD_LEN];

	};




	// ---------------------------------------------------------------------- //
	// Collision info
	// 
	// Used to determine information in GetStandingOn or GetLastCollision
	// ---------------------------------------------------------------------- //

	class CollisionInfo
	{
	public:
		// The blocking plane of whatever the object collided with.  If both object's are non-solid, then this 
		// will have a normal vector of mag 0.
		LTPlane		m_Plane;

		// The object collided with.
		HOBJECT		m_hObject;

		// If the m_hObject is the world, then m_hPoly contains a handle to the polygon the object collided with.
		// Otherwise it is equal to LTNULL.
		HPOLY		m_hPoly;

		// Stopping velocity.  Engine will automatically apply this velocity to stop object from continuing
		// to collide with blocker.
		LTVector		m_vStopVel;
	};


	// ---------------------------------------------------------------------- //
	// Sound 3D Provider
	//
	// Used with GetSoundSW3DProviderList, GetSoundHW3DProviderList and 
	// ReleaseSound3DProviderList.
	// ---------------------------------------------------------------------- //
	
	// Sound 3D provider ID's
	#define SOUND3DPROVIDERID_NONE					0
	#define SOUND3DPROVIDERID_DS3D_HARDWARE			1
	#define SOUND3DPROVIDERID_DS3D_HARDWARE_EAX		2
	#define SOUND3DPROVIDERID_DS3D_SOFTWARE			3
	#define SOUND3DPROVIDERID_A3D					4
	#define SOUND3DPROVIDERID_INTEL_RSX				5
	#define SOUND3DPROVIDERID_MILES3D				6
	#define SOUND3DPROVIDERID_UNKNOWN				7

	// Caps bits
	#define SOUND3DPROVIDER_CAPS_REVERB			(1<<0)

	struct Sound3DProvider
	{
		uint32				m_dwProviderID;
		char				m_szProvider[_MAX_PATH+1];
		uint32				m_dwCaps;
		Sound3DProvider *	m_pNextProvider;
	};

	// ---------------------------------------------------------------------- //
	// Reverb properties
	//
	// Use this structure with SetReverb and GetReverb
	// ---------------------------------------------------------------------- //
	
	#define REVERBPARAM_VOLUME				(1<<0)		// m_fVolume field valid
	#define REVERBPARAM_ACOUSTICS			(1<<1)		// m_dwAcoustics field valid
	#define REVERBPARAM_REFLECTTIME			(1<<2)		// m_fReflectTime field valid
	#define REVERBPARAM_DECAYTIME			(1<<3)		// m_fDecayTime field valid
	#define REVERBPARAM_DAMPING				(1<<4)		// m_fDamping field valid
	#define REVERBPARAM_ALL					REVERBPARAM_VOLUME | REVERBPARAM_ACOUSTICS | REVERBPARAM_REFLECTTIME | REVERBPARAM_DECAYTIME | REVERBPARAM_DAMPING

	// These are the valid values for m_dwAcoustics field
	enum
	{
		REVERB_ACOUSTICS_GENERIC,
		REVERB_ACOUSTICS_PADDEDCELL,
		REVERB_ACOUSTICS_ROOM,
		REVERB_ACOUSTICS_BATHROOM,
		REVERB_ACOUSTICS_LIVINGROOM,
		REVERB_ACOUSTICS_STONEROOM,
		REVERB_ACOUSTICS_AUDITORIUM,
		REVERB_ACOUSTICS_CONCERTHALL,
		REVERB_ACOUSTICS_CAVE,
		REVERB_ACOUSTICS_ARENA,
		REVERB_ACOUSTICS_HANGAR,
		REVERB_ACOUSTICS_CARPETEDHALLWAY,
		REVERB_ACOUSTICS_HALLWAY,
		REVERB_ACOUSTICS_STONECORRIDOR,
		REVERB_ACOUSTICS_ALLEY,
		REVERB_ACOUSTICS_FOREST,
		REVERB_ACOUSTICS_CITY,
		REVERB_ACOUSTICS_MOUNTAINS,
		REVERB_ACOUSTICS_QUARRY,
		REVERB_ACOUSTICS_PLAIN,
		REVERB_ACOUSTICS_PARKINGLOT,
		REVERB_ACOUSTICS_SEWERPIPE,
		REVERB_ACOUSTICS_UNDERWATER,
		REVERB_ACOUSTICS_DRUGGED,
		REVERB_ACOUSTICS_DIZZY,
		REVERB_ACOUSTICS_PSYCHOTIC,

		REVERB_ACOUSTICS_COUNT           // total number of room types
	};

	struct ReverbProperties
	{
		uint32	m_dwParams;		// Set the params bits for which fields are valid
		float	m_fVolume;		// 0.0 - 1.0
		uint32	m_dwAcoustics;	// One of the REVERB_ACOUSTICS_xxx values
		float	m_fReflectTime;	// 0.0 - 5.0 Time for first reflection
		float	m_fDecayTime;	// 0.1 - 20.0 Determines how quickly reflection diminish
		float	m_fDamping;		// 0.0 - 2.0, == 1.0f is even damping, < 1.0f low frequencies dampen faster
											// > 1.0f high frequencies dampen faster
	};

	// ---------------------------------------------------------------------- //
	// Sound effects.
	// 
	// The type of sounds are:  ambient, local and 3D.  The flags controlling
	// these types are mutually exclusive.  An ambient sound will have distance
	// effects of rolloff, but no orientation effects.  A local sound will have
	// no orientation or distance effects and will be as if the sound was played
	// inside the player's head.  The 3d sound will have distance, orientation
	// and doppler effects.
	//
	// Sounds are played from the beginning once the message reaches the client.
	// If it is important that the playback be synchronized with the server's 
	// beginning time, then set PLAYSOUND_TIMESYNC.  Normally, this is not
	// that important.  The server will use it internally if a client comes in
	// after a sound has already been played.
	//
	// The server keeps a sound object if any of the following flags are set:
	// PLAYSOUND_LOOP, PLAYSOUND_ATTACHED, PLAYSOUND_GETHANDLE, PLAYSOUND_TIMESYNC,
	// PLAYSOUND_TIME. Server kept sounds will update clients that come and go.  
	// Non-server kept sounds are sent to the existing clients once, so the 
	// overhead is much less.
	// 
	// Server kept sounds with PLAYSOUND_GETHANDLE must be removed by the game.  
	// Other server kept sounds are removed if they time out, or the object they
	// are attached to is removed.  When a sound is removed from the server,
	// it tells the clients to remove their copies.
	//
	// Server tells clients about its sounds if the client object is within
	// twice the outer radius of the sound.  If local sound, then server always
	// tells all the clients.
	//
	// Sounds that have a client object in m_hObject and PLAYSOUND_CLIENTLOCAL
	// or PLAYSOUND_ATTACHED are played with PLAYSOUND_LOCAL for that particular client.
	//
	// The PLAYSOUND_CLIENT is for client initiated sounds only.  When playing
	// client side sounds, the PLAYSOUND_ATTACHED and PLAYSOUND_CLIENTLOCAL
	// flags and m_wObjectID are ignored.
	//
	// ---------------------------------------------------------------------- //

	#define PLAYSOUND_LOCAL			0x0000	// Play sound locally (inside head)
	#define PLAYSOUND_AMBIENT		0x0001	// Play sound as ambient sound.
	#define PLAYSOUND_3D			0x0002	// Play sound as 3D sound.
	#define PLAYSOUND_LOOP			0x0004	// Loop the sound.
	#define PLAYSOUND_ATTACHED		0x0008	// Sounds position & orientation comes from object in m_hObject
	#define PLAYSOUND_GETHANDLE		0x0010	// Handle requested
	#define PLAYSOUND_TIME			0x0020	// Server must time sound
	#define PLAYSOUND_CTRL_VOL		0x0040	// Control volume m_nVolume
	#define PLAYSOUND_CTRL_PITCH	0x0080	// Control pitch in m_nPitch
	#define PLAYSOUND_REVERB		0x0100	// Allow reverb
	#define PLAYSOUND_CLIENT		0x0200	// Client side sound
	#define PLAYSOUND_TIMESYNC		0x0400	// Playback synchronized with server clock
	#define PLAYSOUND_CLIENTLOCAL	0x0800	// Sound is played with PLAYSOUND_LOCAL for object in m_hObject
	#define PLAYSOUND_ONCE			0x1000  // This sound will only be played once (reduces memory overhead)

	struct PlaySoundInfo
	{
		// PLAYSOUND flags.
		uint32		m_dwFlags;
	
		// File name of sound
		char 		m_szSoundName[_MAX_PATH+1];

		// SERVER ONLY: Object sound is attached to.
		// Only needed if PLAYSOUND_ATTACHED or PLAYSOUND_CLIENTLOCAL set
		HOBJECT		m_hObject;

		// Handle of sound
		// Filled by PlaySound if PLAYSOUND_GETHANDLE set
		HLTSOUND	m_hSound;

		// Voice priority 
		// 0 is lowest priority
		unsigned char m_nPriority;

		// Maximum radius of sound.  No sound outside this.
		// Only needed if PLAYSOUND_3D or PLAYSOUND_AMBIENT
		float		m_fOuterRadius;
		
		// Inner radius of sound.  Sound at maximum volume inside this radius
		// Only needed if PLAYSOUND_3D or PLAYSOUND_AMBIENT
		float		m_fInnerRadius;
		
		// Volume of sound in percent [0,100].
		// Only needed if PLAYSOUND_CTRL_VOL set, otherwise defaults 100
		uint8 		m_nVolume;

		// Pitch multiplier. [0,]
		// Ignored unless PLAYSOUND_CTRL_PITCH set.
		float		m_fPitchShift;

		// Position of sound.
		// Only needed if PLAYSOUND_AMBIENT and PLAYSOUND_3D set
		// Only needed if PLAYSOUND_ATTACHED cleared
		LTVector	m_vPosition;

		// User data to be passed into IClientShell::OnPlaySound
		uint32		m_UserData;
	};

	#define PLAYSOUNDINFO_COPY( dest, src ) \
		memcpy(( void * )&( dest ), ( void * )&( src ), sizeof( PlaySoundInfo ));

	#define PLAYSOUNDINFO_INIT(x) memset(&x, 0, sizeof(x));

	// ---------------------------------------------------------------------- //
	// InitSoundInfo
	//
	// Used to initialize the sound engine.
	// ---------------------------------------------------------------------- //

	// Maximum number of voices allowed for either sw or 3d
	#define INITSOUNDINFO_MAXVOICES			128

	// Used for m_dwFlags parameter
	#define INITSOUNDINFOFLAG_CONVERT16TO8	(1<<0)	// Convert all 16 bit buffers to 8 bit
	#define INITSOUNDINFOFLAG_RELOADSOUNDS	(1<<1)	// Reload any sounds that exist before InitSound called

	// Engine can fill these flags in the m_dwResults parameter
	#define INITSOUNDINFORESULTS_REVERB		(1<<0)	// Provider chosen supports reverb

	// ------------------------------------------------------------------ //
	// Use this to start a game.
	// ------------------------------------------------------------------ //

	#define STARTGAME_HOST		0	// Start a world and host it (using dialogs).
	#define STARTGAME_HOSTTCP	1	// Start a world and host on TCP/IP.

	#define STARTGAME_CLIENT	2	// Connect to a server using dialogs.
	#define STARTGAME_CLIENTTCP	3	// Connect to the first TCP/IP game it can find
									// at m_pTCPAddress.
	
	#define STARTGAME_NORMAL	4	// Start a normal game.
	#define GAMEMODE_NONE		5	// (Used for GetGameMode, means we're not 
									// running a world or on a server yet).

	#define SG_LOBBY			1	// Game was lobby-launched

	#define MAX_SGR_STRINGLEN	100

	class StartGameRequest
	{
	public:
						StartGameRequest()
						{
							m_Type = STARTGAME_NORMAL;
							m_WorldName[0] = 0;
							m_TCPAddress[0] = 0;
							m_RecordFilename[0] = 0;
							m_PlaybackFilename[0] = 0;
							m_flags = 0;
							m_pGameInfo = LTNULL;
							m_GameInfoLen = 0;
							m_pNetSession = LTNULL;
							m_pClientData = LTNULL;
							m_ClientDataLen = 0;
						}	
		
		int				m_Type;
		char			m_WorldName[MAX_SGR_STRINGLEN];
		char			m_TCPAddress[MAX_SGR_STRINGLEN];		// TCP/IP address, if any.
		
		// Filename to record into, if any (set to 0 length if you don't want to record).
		// NOTE: when this is set, the engine starts the server but doesn't run the level, you must
		// send a message to the server telling it to load the world.
		char			m_RecordFilename[MAX_SGR_STRINGLEN];	
		
		// The filename of a recorded demo.  If this is filled in, the engine starts a server
		// and fills in m_WorldName with the world that the demo record uses.  You need to
		// send a message to the server telling it to load that world.
		char			m_PlaybackFilename[MAX_SGR_STRINGLEN];
		
		NetSession		*m_pNetSession;	// This must be used with STARTGAME_CLIENT.
		NetHost			m_HostInfo;		// This must be used with STARTGAME_HOST.
		uint32			m_flags;		// Various flags

		void			*m_pGameInfo;	// This data is copied over and can be accessed by
		uint32			m_GameInfoLen;	// the server with ServerDE::GetGameInfo() (if you're
										// running a local or hosted game).
	
		// This data gets sent up and passed into OnClientEnterWorld on the server.
		void			*m_pClientData;
		uint32			m_ClientDataLen;
	};


	// Parsing stuff.
	#define PARSE_MAXTOKENS		64
	#define PARSE_MAXTOKENSIZE	80

	// The new console parsing thing.
	class ConParse
	{
	public:
	
				ConParse()				{m_pCommandPos = LTNULL;}
				ConParse(char *pBuffer)	{m_pCommandPos = pBuffer;}

		// Sets it up to parse the specified buffer.
		void	Init(char *pBuffer)		{m_pCommandPos = pBuffer;}

		// The parsed arguments.
		char	*m_Args[PARSE_MAXTOKENS];
		int		m_nArgs;

	// Used internally by the engine.
	public:

		// Parse the next set of tokens.  Returns LTTRUE if it parsed anything.
		LTBOOL	Parse();

		// Parses until it finds tokens with pLookFor as the first one.
		// skipCount says how many to skip.
		// You can use this just like Parse like this:
		// while(ParseFind("AmbientLight", LTFALSE)) { ... }
		LTBOOL	ParseFind(char *pLookFor, LTBOOL bCaseSensitive, uint32 minTokens=1);

	private:
		
		char	*m_pCommandPos;
		char	m_ArgBuffer[PARSE_MAXTOKENS*PARSE_MAXTOKENSIZE];
	};


	template<class T>
	class BaseObjArray
	{
	public:
		
				BaseObjArray()
				{
					m_pArray = LTNULL;
					m_MaxListSize = 0;
					m_nElements = 0;
				}

		inline bool	AddObject(const T& obj)
		{
			if ( m_nElements < m_MaxListSize )
			{
				m_pArray[m_nElements] = obj;
				m_nElements++;
				return LTTRUE;
			}

			return LTFALSE;
		}

		inline T GetObject(uint32 index)
		{
			ASSERT(index < m_nElements);
			return m_pArray[index];
		}

		inline void	Reset()
		{
			m_nElements = 0;
		}

		inline uint32 NumObjects()
		{
			return m_nElements;
		}


	protected:
		T		*m_pArray;
		uint32	m_MaxListSize;

		// Number of valid objects in m_pList.
		uint32	m_nElements;
	};

	template<class T, int size>
	class ObjArray : public BaseObjArray<T>
	{
	public:
			ObjArray()
			{
				m_pArray = m_Array;
				m_MaxListSize = size;
			}

	private:
		T	m_Array[size];
	};

	// ---------------------------------------------------------------------- //
	// Intersection stuff.
	// ---------------------------------------------------------------------- //

	// Return LTTRUE to select this object and LTFALSE to not select it.
	typedef LTBOOL (*ObjectFilterFn)(HOBJECT hObj, void *pUserData);
	typedef LTBOOL (*PolyFilterFn)(HPOLY hPoly, void *pUserData);


	// Pass this in to the IntersectSegment routine.
	class IntersectQuery
	{
	public:

		IntersectQuery()
		{
			m_Flags = 0;
			m_FilterFn = 0;
			m_PolyFilterFn = 0;
			m_pUserData = LTNULL;

			m_From.Init();
			m_To.Init();
			m_Direction.Init();
		}

		// Start and end points.
		LTVector		m_From;
		LTVector		m_To;

		// Only used for CastRay.. this is the direction the ray should be cast in.
		// This doesn't need to be normalized.
		LTVector			m_Direction;

		// A combination of the intersect flags (in ltcodes.h).
		uint32			m_Flags;
		
		// If this is not LTNULL, then it'll call this function when it has a 
		// POSSIBLE object intersection (it doesn't know if it really intersects
		// yet when it calls this).  If you return LTFALSE from this function, 
		// then it will ignore the object and continue on.
		ObjectFilterFn	m_FilterFn;

		// If this is not LTNULL, then it'll call this function when it has a 
		// poly intersection. If you return LTFALSE from this function, 
		// then it will ignore the poly and continue on.
		PolyFilterFn	m_PolyFilterFn;

		// Passed into pUserData of the filter function.
		void			*m_pUserData;		
	};

	
	struct IntersectInfo
	{
		IntersectInfo()
		{
			m_Point.Init();
			m_Plane.m_Normal.Init();
			m_Plane.m_Dist = 0.0f;
			m_hObject = LTNULL;
			m_hPoly = INVALID_HPOLY;
			m_SurfaceFlags = 0;
		}

		// Point of intersection.
		LTVector	m_Point;

		// Plane of intersection.
		LTPlane		m_Plane;

		// Object it hit.
		HOBJECT		m_hObject;

		// The polygon it hit (if it's a world poly).
		// Value is INVALID_HPOLY if it didn't hit one.
		HPOLY		m_hPoly;

		// Surface flags of what it hit (these aren't object flags, and are
		// only set if it hit the world or a WorldModel).
		uint32		m_SurfaceFlags;
	};

	#define ClientIntersectInfo		IntersectInfo
	#define ClientIntersectQuery	IntersectQuery


	typedef void (*ModelHookFn)(ModelHookData *pData, void *pUser);


	// Used in AddSurfaceEffect.
	struct SurfaceEffectDesc
	{
		char	*m_pName;  // You don't have to allocate this..
		
		// If you return LTNULL from here, the effect won't be initialized.
		void*	(*InitEffect)(SurfaceData *pSurfaceData, int argc, char **argv);
		int		(*UpdateEffect)(SurfaceData *pSurfaceData, void *pData);	// pData is what you returned from InitEffect.
												// Return 1 if you changed the surface.
		void	(*TermEffect)(void *pData);
	};



	// ---------------------------------------------------------------------- //
	// GenericProp -
	// Here's a list of which property types map to which variables:
	// PT_STRING   - m_Vec and m_Color if it's formatted like '1 2 3', m_String, m_Long, m_Float, m_Bool.
	//             - if this is 'true' or 'false', it'll set m_Long, m_Float, and m_Bool to 0 or 1.

	// PT_VECTOR   - m_Vec, m_String ('1 2 3')
	// PT_COLOR    - m_Color, m_String ('1 2 3')
	// PT_REAL     - m_String, m_Long, m_Float, m_Bool
	// PT_FLAGS    - m_String, m_Long, m_Float, m_Bool
	// PT_BOOL     - m_String, m_Long, m_Float, m_Bool
	// PT_LONGINT  - m_String, m_Long, m_Float, m_Bool
	// PT_ROTATION - m_Rotation and m_Vec (with euler rotation).
	// ---------------------------------------------------------------------- //

	#define MAX_GP_STRING_LEN 256

	struct GenericProp
	{
		LTVector		m_Vec;
		LTVector		m_Color;

		char		m_String[MAX_GP_STRING_LEN+1];
		LTRotation	m_Rotation;
		long		m_Long;
		float		m_Float;
		LTBOOL		m_Bool;
	};



	////////////////////////////////////////////////////////////////////////
	// Helper functions.
	////////////////////////////////////////////////////////////////////////

	// Returns LTTRUE if the point is touching or inside the box.
	inline LTBOOL base_IsPtInBox(LTVector *pPt, LTVector *pBoxMin, LTVector *pBoxMax)
	{
		return (pPt->x >= pBoxMin->x) && (pPt->y >= pBoxMin->y) && (pPt->z >= pBoxMin->z) && 
			(pPt->x <= pBoxMax->x) && (pPt->y <= pBoxMax->y) && (pPt->z <= pBoxMax->z);
	}


	// Just test on XZ.
	inline LTBOOL base_IsPtInBoxXZ(LTVector *pPt, LTVector *pBoxMin, LTVector *pBoxMax)
	{
		return (pPt->x >= pBoxMin->x) && (pPt->z >= pBoxMin->z) && 
			(pPt->x <= pBoxMax->x) && (pPt->z <= pBoxMax->z);
	}  


	// Object flags.
	#define FLAG_VISIBLE			(1<<0)

	#define FLAG_SHADOW				(1<<1)	// Does this model cast shadows?
	#define FLAG_UNSIGNED			(1<<1)	// Tells the polygrid to use unsigned bytes for its data.

	#define FLAG_SPRITEBIAS			(1<<2)	// Biases the Z towards the view so a sprite doesn't clip as much.
	#define FLAG_MODELTINT			(1<<2)	// If this is set, it draws a model in 2 passes.  In the
											// second pass, it scales down the color with ColorR,
											// ColorG, and ColorB.  This is used to tint the skins
											// in multiplayer.  Note: it uses powers of 2 to determine
											// scale so the color scale maps like this:
											// > 253 = 1.0
											// > 126 = 0.5
											// > 62  = 0.25
											// > 29  = 0.12
											// otherwise 0
	
	#define FLAG_CASTSHADOWS		(1<<3)	// Should this light cast shadows (slower)?
	#define FLAG_ROTATEABLESPRITE	(1<<3)	// Sprites only.
	#define FLAG_DETAILTEXTURE		(1<<3)	// Models: draw with a detail texture.
	#define FLAG_UPDATEUNSEEN		(1<<3)	// Particle systems only.
											// If this is set, the engine will update
											// particles even when they're invisible.
											// You should check FLAG_WASDRAWN
											// on any particle systems you're iterating
											// over so you don't update invisible ones.
	
	#define FLAG_SOLIDLIGHT			(1<<4)	// Use the 'fastlight' method for this light.
	#define FLAG_MODELWIREFRAME		(1<<4)
	#define FLAG_WASDRAWN			(1<<4)	// The engine sets this if a particle system
											// or PolyGrid was drawn.  You can use this to 
											// determine whether or not to do some expensive
											// calculations on it.
	#define FLAG_SPRITE_NOZ			(1<<4)	// Disable Z read/write on sprite (good for lens flares).

	#define FLAG_GLOWSPRITE				(1<<5)	// Shrinks the sprite as the viewer gets nearer.
	#define FLAG_ONLYLIGHTWORLD			(1<<5)	// Lights only - tells it to only light the world.
	#define FLAG_ENVIRONMENTMAP			(1<<5)	// Environment map the model.
	#define FLAG_ENVIRONMENTMAPONLY		(1<<5)	// For PolyGrids - says to only use the environment map (ignore main texture).
	
	#define FLAG_DONTLIGHTBACKFACING	(1<<6)	// Lights only - don't light backfacing polies.
	#define FLAG_REALLYCLOSE			(1<<6)	// This is used for objects that are really close to the camera and would
												// normally be clipped out of the view. PV weapons and effects attached
												// to them are the best example. This tells the renderer to do some tricks
												// to clip their near Z much closer to the eyepoint. This can be used for:
												// - models
												// - sprites without FLAG_ROTATEABLESPRITE
												// - canvases

	#define FLAG_FOGDISABLE			(1<<7)	// Disables fog on WorldModels, Sprites, Particle Systems and Canvases only.
	#define FLAG_ANIMTRANSITION		(1<<7)	// Does a 200ms transition between model animations.
	#define FLAG_ONLYLIGHTOBJECTS	(1<<7)	// Lights only - tells it to only light objects (and not the world).

	#define FLAG_FULLPOSITIONRES	(1<<8)	// LT normally compresses the position and rotation info
											// to reduce packet size.  Some things must be exact 
											// (like some WorldModels) so this will 
											// enlarge the packets for better accuracy.

	#define FLAG_NOLIGHT			(1<<9)	// Just use the object's color and global light scale.
											// (Don't affect by area or by dynamic lights).

	#define FLAG_HARDWAREONLY		(1<<10)	// Don't draw this object if we're using software rendering.
	#define FLAG_PORTALVISIBLE		(1<<10)	// Draw in portals even if the object is invisible.

	#define FLAG_YROTATION			(1<<11)	// Uses minimal network traffic to represent rotation
											// (1 byte instead of 3, but only rotates around the Y axis).

	#define FLAG_RAYHIT				(1<<12) // Object is hit by raycasts.

	#define FLAG_SOLID				(1<<13)	// Object can't go thru other solid objects.

	#define FLAG_BOXPHYSICS			(1<<14)	// Use simple box physics on this object (used for WorldModels and containers).
	#define FLAG_NOGLOBALLIGHTSCALE	(1<<14)	// Particle systems: disables use of global light scale.

	#define FLAG_CLIENTNONSOLID		(1<<15)	// This object is solid on the server and nonsolid on the client.	

	// Which flags the client knows about.
	#define CLIENT_FLAGMASK			(FLAG_VISIBLE|FLAG_SHADOW|FLAG_MODELTINT|\
									FLAG_ROTATEABLESPRITE|FLAG_SOLIDLIGHT|\
									FLAG_REALLYCLOSE|FLAG_SPRITE_NOZ|FLAG_FOGDISABLE|\
									FLAG_FULLPOSITIONRES|FLAG_NOLIGHT|FLAG_ENVIRONMENTMAP|\
									FLAG_HARDWAREONLY|FLAG_YROTATION|FLAG_RAYHIT|\
									FLAG_SOLID|FLAG_BOXPHYSICS|FLAG_CLIENTNONSOLID)

	// Server only flags.
	#define FLAG_TOUCH_NOTIFY		(1<<16)	// Gets touch notification.
	#define FLAG_GRAVITY			(1<<17)	// Gravity is applied.
	#define FLAG_STAIRSTEP			(1<<18)	// Steps up stairs.
	#define FLAG_MODELKEYS			(1<<19)	// The object won't get get MID_MODELSTRINGKEY messages unless
											// it sets this flag.
	#define FLAG_KEEPALIVE			(1<<20)	// Save and restore this object when switching worlds.
	#define FLAG_GOTHRUWORLD		(1<<21) // Object can pass through world
	#define FLAG_DONTFOLLOWSTANDING	(1<<23) // Dont follow the object this object is standing on.
	#define FLAG_FORCECLIENTUPDATE	(1<<24)	// Force client updates even if the object is OT_NORMAL or invisible.
											// Use this whenever possible.. it saves cycles.
	#define FLAG_NOSLIDING			(1<<25)	// Object won't slide agaist polygons

	#define FLAG_POINTCOLLIDE		(1<<26)	// Uses much (10x) faster physics for collision detection, but the
											// object is a point (dims 0,0,0).  Standing info is not set when
											// this flag is set.

	#define FLAG_REMOVEIFOUTSIDE	(1<<27)	// Remove this object automatically if it gets outside the world.

	#define FLAG_FORCEOPTIMIZEOBJECT	(1<<28)	// Force the engine to optimize this object
												// as if the FLAG_OPTIMIZEOBJECT flags were
												// cleared.  This can be used if you have a visible
												// object that's an attachment but it doesn't need
												// touch notifies or raycast hits (like a gun-in-hand).
	
	#define	FLAG_CONTAINER				(1<<29) // Will get an MID_AFFECTPHYSICS message for each object
												// that is inside its volume

	// Internal flags.  Descriptions are there to help the DE developers remember what
	// they're there for, NOT for general use!
	#define FLAG_INTERNAL1			(1<<30)	// (Did the renderer see the object).
	#define FLAG_INTERNAL2			(1<<31)	// (Used by ClientDE::FindObjectsInSphere).
	#define FLAG_LASTFLAG			FLAG_INTERNAL2 


	// If you clear these flags (flags &= ~FLAG_OPTIMIZEMASK) and the object doesn't have 
	// a special effect message, the engine never even iterates over the object for movement,
	// raycasting, visibility, etc.  Use this whenever you can.
	#define FLAG_OPTIMIZEMASK (FLAG_VISIBLE|FLAG_SOLID|FLAG_TOUCH_NOTIFY|\
		FLAG_RAYHIT|FLAG_FORCECLIENTUPDATE|FLAG_GOTHRUWORLD|FLAG_CONTAINER)



	// FLAG2_ defines.
	#define FLAG2_PORTALINVISIBLE	(1<<0)		// This object is invisible in portals.
	
	#define FLAG2_CHROMAKEY			(1<<1)		// For WorldModels and models - use chromakeying to draw.
	#define FLAG2_ADDITIVE			(1<<2)		// For models and sprites - do additive blending.
	#define FLAG2_MULTIPLY			(1<<3)		// For models and sprites. Multiplied color blending.
	#define FLAG2_PLAYERCOLLIDE		(1<<4)		// This object should use the player-friendly cylinder-
												// based collision physics for collisions w/ the BSP
	#define FLAG2_DYNAMICDIRLIGHT	(1<<5)		// For models - re-calculates the directional lighting
												// when the object moves
	#define FLAG2_SKYOBJECT			(1<<6)		// Don't render this object thru the normal stuff,
												// only render it when processing sky objects.


	// Different object types.  Some can only be created on the client.
	#define OT_NORMAL			0	// Invisible object.  Note, client's aren't told about
									// these when they're created on the server! 
	#define OT_MODEL			1	// Model object.
	#define OT_WORLDMODEL		2	// WorldModel.
	#define OT_SPRITE			3	// Sprite.
	#define OT_LIGHT			4	// Dynamic light.
	
	#define OT_CAMERA			5	// Camera.
	#define OT_PARTICLESYSTEM	6	// Particle system.
	#define OT_POLYGRID			7	// Poly grid.
	#define OT_LINESYSTEM		8	// Line system.
	#define OT_CONTAINER		9	// Container.
	#define OT_CANVAS			10	// Canvas (game code renders it).
	#define NUM_OBJECTTYPES		11	// NOTE: the high bit of the object type is reserved
									// for the engine's networking.

	// Size defines used for Parse functions
	// Use these to size your argument buffer and argument pointer
	// buffer accordingly.
	#define PARSE_MAXARGS		30
	#define PARSE_MAXARGLEN		256


	// Useful for objects who need to call Term and return a value
	// (like for loading functions).
	#define TERM_RET(__ret) \
		{ Term(); return __ret; }


	// Maximum number of sky objects.
	#define MAX_SKYOBJECTS	30


	// Helpful math definitions.
	#define MATH_PI				3.141592653589793f
	#define MATH_HALFPI			1.570796326795f
	#define MATH_CIRCLE			6.283185307178f
	#define MATH_ONE_OVER_PI	0.3183098861839f
	#define MATH_EPSILON		0.00000000001f
	#define MATH_DEGREES_TO_RADIANS(x) ((x) *  0.01745329251994f)
	#define MATH_RADIANS_TO_DEGREES(x) ((x) *  57.2957795130967f)

	#define MATH_ONE_OVER_255	0.003921568627451f


	#define LTDIFF(a,b) (((a) < (b)) ? ((b) - (a)) : ((a) - (b)))
	#define LTMIN(a,b) ((a) < (b) ? (a) : (b))
	#define LTMAX(a,b) ((a) > (b) ? (a) : (b))
	#define LTABS(a) ((a) > 0 ? (a) : -(a))
	#define LTCLAMP(a, min, max) ((a) < (min) ? (min) : ((a) > (max) ? (max) : (a)))
	#define LTLERP(min, max, t) ((min) + ((max) - (min)) * (t))

	#define INLINE_FN __inline
	
	// Used for resizing arrays.. mostly for internal DirectEngine stuff.
	#define GENERIC_REMOVE(theArray, iIndex, nElements) \
		ASSERT(nElements > 0);\
		memmove(&theArray[iIndex], &theArray[iIndex+1], sizeof(theArray[0]) * (nElements-iIndex-1));\
		nElements--;

	#define GENERIC_INSERT(type, theArray, nElements, iIndex, value) \
		{\
			type *pNewArray = (type*)malloc(sizeof(type) * (nElements+1));\
			memcpy(pNewArray, theArray, nElements * sizeof(type));\
			memmove(&pNewArray[iIndex+1], &pNewArray[iIndex], sizeof(type)*(nElements-iIndex));\
			memcpy(&pNewArray[iIndex], &value, sizeof(type));\
			free(theArray);\
			theArray = pNewArray;\
			++nElements;\
		}
				
	#define GENERIC_INSERT_CPP(type, theArray, nElements, iIndex, value) \
		{\
			type *pNewArray = new type[nElements+1];\
			memcpy(pNewArray, theArray, nElements * sizeof(type));\
			memmove(&pNewArray[iIndex+1], &pNewArray[iIndex], sizeof(type)*(nElements-iIndex));\
			memcpy(&pNewArray[iIndex], &value, sizeof(type));\
			delete [] theArray;\
			theArray = pNewArray;\
			++nElements;\
		}
				
	#define GENERIC_APPEND(type, theArray, nElements, value) \
		GENERIC_INSERT(type, theArray, nElements, nElements, value);
				
#endif  // __LTBASEDEFS_H__
