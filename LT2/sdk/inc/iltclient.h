

#ifndef __ILTCLIENT_H__
#define __ILTCLIENT_H__


	#include "ltbasedefs.h"
	#include "iclientshell.h"
	#include "iltcommon.h"
	#include "iltcsbase.h"
	#include "iltsoundmgr.h"
	#include "iltdirectmusic.h"

													
	// Particle system flags. Each one slows it down a little more
	// except for PS_NEVERDIE which speeds it up..
	#define PS_BOUNCE		(1<<0)	// Do they bounce?
	#define PS_NEVERDIE		(1<<2)	// The particles never die (and it doesn't have to check).
	#define PS_DUMB			(1<<3)	// The engine leaves the system alone.. you must
									// update and move them.

	// The particle structure for particle systems.
	struct LTParticle
	{
		LTVector m_Velocity;
		LTVector m_Color;	// Particle colors are 0-255.
		float	 m_Alpha;	// 0-1.
		float	 m_Size;	// Particle size
		LTParticle *m_pNext;
	};

	
	// The line structure for line system.
	struct LTLinePt
	{
		LTVector	m_Pos;
		float		r, g, b, a;	// Values 0-1.
	};

	struct LTLine
	{
		LTLinePt	m_Points[2];
	};

	DEFINE_HANDLE_TYPE(HLTLINE)


	//  Music info

	#define MUSIC_IMMEDIATE			0
	#define MUSIC_NEXTMEASURE		1
	#define MUSIC_NEXTSONG			2
	#define MUSIC_QUEUE				3


	class CSoundInstance;

	class ILTSpriteControl;
	class ILTLightAnim;
	class ILTTexMod;

	class ILTClientPhysics;
	class ILTVideoMgr;
	class ILTModel;
	class ILTTransform;
	class ILTCursor;
	class ILTClientSoundMgr;
	class ILTDirectMusicMgr;


	// ------------------------------------------------------------------ //
	// ILTClient interface. This is what the ClientShells and special
	// effect plugins use to do the interface and client objects for the game.
	// ------------------------------------------------------------------ //

	class ILTClient : public ILTCSBase
	{
	friend class CClientMgr;

	protected:

		virtual			~ILTClient() {}

	
	public:
		
			
		
	// Access to the other interfaces.

		ILTVideoMgr*		VideoMgr()			{return m_pVideoMgr;}
		ILTTexMod*			GetTexMod()			{return m_pTexMod;}
		ILTCursor*			Cursor()			{return m_pCursorLT;}
		ILTDirectMusicMgr*  GetDirectMusicMgr() {return m_pDirectMusicMgr;};

	
	// Connection stuff.

		// Tries to start the game in the mode you specify.
		// This will keep the existing game running until it successfully starts
		// the new game.. ie: if there's an error starting the new world, it
		// will still leave the current one running and put up an error message.
		LTRESULT	(*StartGame)(StartGameRequest *pRequest);

		// Find out what the current game mode is (how we started the last
		// game with StartGame or thru the console).  Fills in mode with 
		// one of the STARTGAME_ defines above.
		LTRESULT	(*GetGameMode)(int *mode);

		// Gets the local client ID.
		// Returns LT_NOTCONNECTED if we're not on a server or haven't
		// gotten a client ID yet.
		LTRESULT	(*GetLocalClientID)(uint32 *pID);

		LTBOOL		(*IsConnected)();	// Are we on a server currently?

		// Disconnect from the server we're on (if any).
		// NOTE: this will destroy any client-side objects you've created!
		void		(*Disconnect)();

		// Shuts down the app (not right away, but after the current update).
		void		(*Shutdown)();

		// Shuts down the app (not right away, but after the current update).
		void		(*ShutdownWithMessage)( char *pMsg, ... );

		// OBSOLETE: use the CommonDE one.
		virtual LTRESULT GetPointStatus(LTVector *pPoint)=0;

		// Get the shade (RGB, 0-255) at the point you specify.
		// Returns LT_NOTINWORLD if the point is outside the world.
		virtual LTRESULT GetPointShade(LTVector *pPoint, LTVector *pColor)=0;
		
	
	// Renderer management.

		// Flip the screen.  Flags are a combination of FLIPSCREEN_ flags in de_codes.
		// Returns LT_OK or LT_NOTINITIALIZED.
		LTRESULT	(*FlipScreen)(uint32 flags);

		// Clear the backbuffer.  Pass in NULL to clear the whole screen.
		// Flags is a combination of the CLEARSCREEN_ flags in de_codes.h.
		// Returns LT_OK or LT_NOTINITIALIZED.
		LTRESULT	(*ClearScreen)(LTRect *pClearRect, uint32 flags);

		// You must be in a Start3D()/End3D() block in order to render
		// through any cameras.
		// Returns LT_OK or LT_NOTINITIALIZED or LT_ALREADYIN3D.
		LTRESULT	(*Start3D)();
		
		// Render from the camera's position into its rectangle.
		// Returns LT_OK or LT_NOTINITIALIZED or LT_NOTIN3D.
		LTRESULT	(*RenderCamera)(HLOCALOBJ hCamera);
		
		// Renders the list of objects through the given camera.
		// Returns LT_OK or LT_NOTINITIALIZED or LT_NOTIN3D.
		LTRESULT	(*RenderObjects)(HLOCALOBJ hCamera, HLOCALOBJ *pObjects, int nObjects);

		// You must be in a StartOptimized2D()/EndOptimized2D() block to draw any optimized 2D surfaces.
		LTRESULT	(*StartOptimized2D)();
		LTRESULT	(*EndOptimized2D)();

		// Change the src/dest blend mode for rendering Optimized2D surfaces  (Defaults to LTSURFACEBLEND_ALPHA)
		// Note : Drawing a surface w/ a blend mode other than _ALPHA will automatically optimize the surface
		LTRESULT	(*SetOptimized2DBlend)(LTSurfaceBlend blend);
		LTRESULT	(*GetOptimized2DBlend)(LTSurfaceBlend &blend);

		// Change the color used on Optimized2D surfaces  (i.e. apply a color filter to Optimized2D)
		LTRESULT	(*SetOptimized2DColor)(HLTCOLOR hColor);
		LTRESULT	(*GetOptimized2DColor)(HLTCOLOR &hColor);

		// Returns LT_OK or LT_NOTINITIALIZED or LT_NOTIN3D.
		LTRESULT	(*End3D)();

		// Get a (NULL-terminated) list of supported render modes.
		RMode*		(*GetRenderModes)();
		void		(*RelinquishRenderModes)(RMode *pModes);
		
		// Fills in the current render mode.
		LTRESULT	(*GetRenderMode)(RMode *pMode);

		// Goes into the requested render mode.
		// Returns LT_OK if successful.  Note: it may not have set the _exact_ mode you
		// requested.  You can check with GetRenderMode() to see what the new mode is.
		// Returns LT_KEPTSAMEMODE if it couldn't set the mode requested, but
		// was able to restore the previous mode.
		// Returns LT_UNABLETORESTOREVIDEO if it couldn't set the mode and couldn't
		// restore the video mode (in which case it will give a message and shutdown
		// afterwards).
		LTRESULT	(*SetRenderMode)(RMode *pMode);
		
		// Shutdown the renderer.  flags is a combination of the RSHUTDOWN_ flags in de_codes.h.
		// The renderer won't come back until you call SetRenderMode().
		LTRESULT	(*ShutdownRender)(uint32 flags);


	// File management.

		// Get a list of files/directories in a directory (pass in "" to start with).
		// The list is a noncircular linked list with LTNULL terminating it.
		FileEntry*	(*GetFileList)(char *pDirName);
		
		// Use FreeFileList when you're done with each list you get.
		void		(*FreeFileList)(FileEntry *pHead);

		// Get the world info string from the World Info dialog in DEdit.
		// Returns LT_NOTFOUND if it can't open the file and LT_INVALIDWORLDFILE
		// if the file is an invalid version.
		LTRESULT	(*GetWorldInfoString)(char *pFilename, char *pInfoString, uint32 maxLen, uint32 *pActualLen);

		// Read/write configuration files.  Returns LT_ERROR if the file doesn't exist
		// or if it can't open the file for writing.
		LTRESULT	(*ReadConfigFile)(char *pFilename);
		LTRESULT	(*WriteConfigFile)(char *pFilename);


	// Interface stuff.

		// offsets is NUM_AXIS_OFFSETS large.
		void		(*GetAxisOffsets)(LTFLOAT *offsets);

		void		(*PlayJoystickEffect)(char *pEffectName, float x, float y);
	

	// Music functions.

		LTBOOL		(*InitMusic)( char *szMusicDLL );

		// Sets the directory to find music data files.
		// IMA only.
		LTBOOL		(*SetMusicDirectory)( char *szMusicDirectory );

		// Downloads DLS.
		// szDLSFile is the Downloadable Synthizer file containing the waves for 
		// instruments.  szStyleFile is a style file, that is a compainion to the 
		// DLS file.  It must contain bands that define the program changes for
		// each instrument in DLS...
		// IMA only.
		LTBOOL		(*InitInstruments)( char *szDLSFile, char *szStyleFile );

		// Cache in a song file.
		LTBOOL		(*LoadSong)(char *szSong);

		// Remove all the songs from memory...
		void		(*DestroyAllSongs)();

		// Plays a playlist.  All songs will be played until end of list.  
		// Arguments:
		//		szPlayList - Name of playlist.
		//		szTransition - Name of transition song to play before playlist starts.  IMA only.
		//		bLoop - Loop the list.
		//		dwBoundaryFlags - Can be MUSIC_IMMEDIATE, MUSIC_MEASURE, MUSIC_SONG, MUSIC_QUEUE.  Valid for IMA only.
		LTBOOL		(*PlayList)( char *szPlayList, char *szTransition, LTBOOL bLoop, uint32 dwBoundaryFlags );

		// Plays a musical break.
		// IMA only.
		// Arguments:
		//		szSong - Name of song.
		//		dwBoundaryFlags - Can be MUSIC_IMMEDIATE, MUSIC_MEASURE, MUSIC_SONG, MUSIC_QUEUE.  Valid for IMA only.
		LTBOOL		(*PlayBreak)( char *szSong, uint32 dwBoundaryFlags );

		// Stops music.  
		// Arguments:
		//		dwBoundaryFlags - Can be MUSIC_IMMEDIATE, MUSIC_MEASURE, MUSIC_SONG, MUSIC_QUEUE.  Valid for IMA only.
		void		(*StopMusic)( uint32 dwBoundaryFlags );

		// Pause music.  Can be resumed...
		LTBOOL		(*PauseMusic)();

		// Resume music...
		LTBOOL		(*ResumeMusic)();

		// Create and add to playlists....
		// Arguments:
		//		szPlayList - Name of playlist.
		//		szSong - Name of song to add.
		LTBOOL		(*AddSongToPlayList)(char *szPlayList, char *szSong);

		// Removes a whole playlist...
		// Arguments:
		//		szPlayList - Name of playlist.
		void		(*DeletePlayList)(char *szPlayList);

		// Plays a motif.
		// Ima only.
		// Arguments:
		//		szMotif - name of motif.
		//		bLoop - Loop the motif.
		LTBOOL		(*PlayMotif)(char *szMotif, LTBOOL bLoop);

		// Stops a motif for IMA.
		// IMA only.
		// Arguments:
		//		szMotif - name of motif.
		void		(*StopMotif)(char *szMotif);

		// Volume range is 0-off, 100-full.
		short		(*GetMusicVolume)();
		void		(*SetMusicVolume)( short wVolume );


	// Sound functions.

		// Gets a list of the 3d sound providers available on system.  Choose one, pass it in the 
		// InitSoundInfo structure.  Use bVerify to tell the engine not to report providers that 
		// aren't completely supported on the system.  This takes longer and causes speaker popping.  
		// Games should only need  to do this when a different provider is chosen.  EAX support
		// can only be checked when the provider is opened, so without the bVerify, the 
		// SOUND3DPROVIDER_CAPS_REVERB cannot be set.  InitSound will report this info in the
		// m_dwResults flags.
		// Be sure to release the list with ReleaseSound3DProviderList.
		LTRESULT		(*GetSound3DProviderLists)( Sound3DProvider *&pSound3DProviderList, LTBOOL bVerify );
		void			(*ReleaseSound3DProviderList)( Sound3DProvider *pSound3DProviderList );

		// Initializes the sound driver.
		LTRESULT		(*InitSound)( InitSoundInfo *pSoundInfo );

		// Volume controls between 0 - 100
		unsigned short	( *GetSoundVolume )();
		void			( *SetSoundVolume )( unsigned short nVolume );

		// Controls the reverb properties.
		// Inputs:
		LTRESULT		( *SetReverbProperties )( ReverbProperties *pReverbProperties );
		LTRESULT		( *GetReverbProperties )( ReverbProperties *pReverbProperties );

	// These PlaySound function allows the client shell to initiate and control sounds
	// without going through the server.  These sounds will only be played 
	// on the client initiating them. These functions will fill m_hSound
	// with the handle to the client sound if you set the PLAYSOUND_GETHANDLE flag.  This will
	// also force the sound not to be automatically deleted when the sound is done playing.  You
	// must call KillSound.  You must get the handle in order to use the other sound functions
	// like SetSoundPosition.

		// Play a sound with full control
		// Arguments:
		//		pPlaySoundInfo - sound control structure
		// Return:
		//		Handle to the client only sound.
		LTRESULT	(*PlaySound)( PlaySoundInfo *pPlaySoundInfo );

		// Update position and orientation of a client only sound.
		// Arguments:
		//		hSound - Handle to client only sound.
		//		pPos - New position of sound. Can be NULL.
		// Return:
		//		LT_OK - Successful.
		//		LT_INVALIDPARAM - Invalid parameters.
		//		LT_ERROR - Unable find hSound
		LTRESULT	(*SetSoundPosition)( HLTSOUND hSound, LTVector *pPos );

		// Get current position and orientation of a client only sound.
		// Arguments:
		//		hSound - Handle to client only sound.
		//		pPos - Destination of position. Can be NULL.
		//		pOrientation - Destination of orientation. Can be NULL.
		// Return:
		//		LT_OK - Successful.
		//		LT_INVALIDPARAM - Invalid parameters.
		//		LT_ERROR - Unable to find hSound.
		LTRESULT	(*GetSoundPosition)( HLTSOUND hSound, LTVector *pPos );

		// Pause/resume sounds.
		void		(*PauseSounds)( );
		void		(*ResumeSounds)( );

		// Get total length in seconds of sound.
		// Arguments:
		//		hSound - Handle to sound.
		//		fDuration - Duration of sound.
		// Returns:
		//		LT_OK if successful.
		//		LT_INVALIDPARAMS if hSound not available.
		LTRESULT	(*GetSoundDuration)( HLTSOUND hSound, LTFLOAT *fDuration );

		// Get current time in seconds of sound.
		// Arguments:
		//		hSound - Handle to sound.
		//		fTimer - Current time of sound.
		// Returns:
		//		LT_OK if successful,  fTimer is set only if this is returned.
		//		LT_FINISHED if sound is not playing (may be delayed due to collisions).
		//		LT_INVALIDPARAMS if hSound not available.
		LTRESULT	(*GetSoundTimer)( HLTSOUND hSound, LTFLOAT *fTimer );

		// Get the sound data and information about the data.
		// This will force the sound to be decompressed.
		//
		// Arguments:
		//		hSound - Handle to sound.
		//		pSixteenBitData    - Set to data buffer if buffer is 16 bits per sample, else set to NULL.
		//		pSixteenBitData    - Set to data buffer if buffer is 8 bits per sample, else set to NULL.
		//		dwSamplesPerSecond - Set to samples per second. 
		//		dwChannels         - Set to number of channels. (samples alternate between each channel).
		//		
		// Returns:
		//		LT_OK if successful,  fTimer is set only if this is returned.
		//		LT_ERROR if sound is neither 8 nor 16 bit format.
		//		LT_INVALIDPARAMS if hSound not available.
		LTRESULT	(*GetSoundData)( HLTSOUND hSound,  
									 int16 * & pSixteenBitData, int8 * & pEightBitData, 
									 uint32 * dwSamplesPerSecond, uint32 * dwChannels );
		
		// Get current offset into sound buffer of sound.
		//
		// Arguments:
		//		hSound   - Handle to sound.
		//		dwOffset - Current offset into sound buffer (in buffer increments, bytes if 8 bit, double bytes if 16 bit).
		//      dwSize   - Size of sound buffer (in bytes).
		// Returns:
		//		LT_OK if successful,  fTimer is set only if this is returned.
		//		LT_FINISHED if sound is not playing (may be delayed due to collisions, or done).
		//		LT_INVALIDPARAMS if hSound not available.
		LTRESULT	(*GetSoundOffset)( HLTSOUND hSound, uint32 * dwOffset, uint32 * dwSize = NULL );

		// Check if sound finished playing or if object it was attached to was removed.
		// Arguments:
		//		pSoundHandle - handle to client only sound
		LTBOOL	(*IsDone)( HLTSOUND pSoundHandle );

		// Kill a sound.
		// Arguments:
		//		pSoundHandle - handle to client only sound
		void	(*KillSound)( HLTSOUND pSoundHandle );

		// Kills a looping sound.  Sound will continue to play until it reaches
		// the end, then remove itself.
		// Arguments:
		//		hSoundHandle - handle to client side sound.
		void	(*KillSoundLoop)( HLTSOUND hSoundHandle );

		// Set the listener status, position and orientation.  If bListenerInClient is TRUE, then
		// pPos and pRot are ignored and can be set to NULL.
		void	(*SetListener)( LTBOOL bListenerInClient, LTVector *pPos, LTRotation *pRot );
		// Return results of above function
		void	(*GetListener)( LTBOOL *bListenerInClient, LTVector *pPos, LTRotation *pRot );


	// Intersections.

		// Intersect a line segment.. (used to be raycast, but line segments are WAY faster).
		// Returns TRUE and fills in pInfo if it hit something.
		LTBOOL		(*IntersectSegment)(ClientIntersectQuery *pQuery, ClientIntersectInfo *pInfo);

		// Same as IntersectSegment, except for it casts a ray from pQuery->m_From
		// in the direction of pQuery->m_Dir.
		LTBOOL		(*CastRay)(ClientIntersectQuery *pQuery, ClientIntersectInfo *pInfo);

		// Find objects in a sphere.  This is only based on their centerpoints, not
		// on their dimensions or anything.  inObjects is filled in and nOutObjects 
		// is set to the number of objects filled in.  nFound might be larger if
		// it found more objects than nInObjects.
		LTRESULT		(*FindObjectsInSphere)(LTVector *pCenter, float radius, 
			HLOCALOBJ *inObjects, uint32 nInObjects, uint32 *nOutObjects, uint32 *nFound);


	// Fonts..

		// Creates the closest font it can to the one you asked for.
		HLTFONT		(*CreateFont)(char *pFontName, int width, int height, 
			LTBOOL bItalic, LTBOOL bUnderline, LTBOOL bBold);

		void		(*DeleteFont)(HLTFONT hFont);

		// Sets the amount of extra space inbetween the letters of the text (in pixels)
		LTRESULT	(*SetFontExtraSpace)(HLTFONT hFont, int pixels);
		LTRESULT	(*GetFontExtraSpace)(HLTFONT hFont, int &pixels);


	// Colors..

		// r, g, and b go from 0 to 1.
		// bTransparent is only used when the function specifies so.
		// Note: anywhere you can pass a color, if you pass in NULL, it'll use black.
		HLTCOLOR	(*CreateColor)(float r, float g, float b, LTBOOL bTransparent);
		void		(*DeleteColor)(HLTCOLOR hColor);

		// Just for convenience.  You don't have to create/delete these colors,
		// and they're always around!
		HLTCOLOR	(*SetupColor1)(float r, float g, float b, LTBOOL bTransparent);
		HLTCOLOR	(*SetupColor2)(float r, float g, float b, LTBOOL bTransparent);

	
	// Surface management.
	// Note:  All the rectangles you specify in here do not include the right and bottom
	//        edges.  ie: If you draw a rectangle (0, 1, 0, 1), it'll draw 1 pixel
	//        instead of 4 pixels. 

	// Note:  Try to use the screen surface as little as possible.  Using the screen
	//        surface stalls ALL asynchronous rendering performance and can cut framerate
	//        in half on some cards.  That's not to say don't use them in the interface,
	//        just don't use them for things that are always there like frag counts, etc..
	//        The only functions that don't stall async performance (feel free to use
	//        these regularly) are:
	//           DrawSurfaceToSurface
	//           DrawSurfaceToSurfaceTransparent
	//           ScaleSurfaceToSurface
	//           ScaleSurfaceToSurfaceTransparent

		// This goes around the edges of the surface and returns the smallest inside
		// rectangle allowing for a border of hColor.  For example, if hSurface 
		// had a black border of 2 pixels on the left and right and a black border 
		// of 3 pixels on the top and bottom, pRect would be set to (2,3,2,3).
		LTRESULT	(*GetBorderSize)(HSURFACE hSurface, HLTCOLOR hColor, LTRect *pRect);

		// Any surfaces you use while rendering 3D stuff at the same time should be optimized
		// with this function and drawn in an StartOptimized2D/EndOptimized2D block.
		// You need to call OptimizeSurface each time you change its contents.
		LTRESULT	(*OptimizeSurface)(HSURFACE hSurface, HLTCOLOR hTransparentColor);
		LTRESULT	(*UnoptimizeSurface)(HSURFACE hSurface);
	
		HSURFACE	(*GetScreenSurface)();

		// Creates a surface sized to the dimensions of the bitmap.
		// The bitmap is an 8-bit (you can use any palette you want..) PCX file.
		// So pBitmapName might look like "interface/bitmaps/menu1.pcx".
		HSURFACE	(*CreateSurfaceFromBitmap)(char *pBitmapName);
		
		// Creates a surface just large enough for the string.
		// You can make the surface a little larger with extraPixelsX and extraPixelsY.
		HSURFACE	(*CreateSurfaceFromString)(HLTFONT hFont, HSTRING hString,
			HLTCOLOR hForeColor, HLTCOLOR hBackColor, 
			int extraPixelsX, int extraPixelsY);
		
		// Create a plain old surface.
		HSURFACE	(*CreateSurface)(uint32 width, uint32 height);
		
		LTRESULT	(*DeleteSurface)(HSURFACE hSurface);

		// Attach whatever user data you want to a surface.
		void*		(*GetSurfaceUserData)(HSURFACE hSurface);
		void		(*SetSurfaceUserData)(HSURFACE hSurface, void *pUserData);

		// Access the pixels (SLOW).
		LTRESULT	(*GetPixel)(HSURFACE hSurface, uint32 x, uint32 y, HLTCOLOR *color);
		LTRESULT	(*SetPixel)(HSURFACE hSurface, uint32 x, uint32 y, HLTCOLOR color);
		
		// Gets the dimensions that this string would take up.
		void		(*GetStringDimensions)(HLTFONT hFont, HSTRING hString, int *sizeX, int *sizeY);

		// Draws the string into the rectangle..
		void		(*DrawStringToSurface)(HSURFACE hDest, HLTFONT hFont, HSTRING hString, 
			LTRect *pRect, HLTCOLOR hForeColor, HLTCOLOR hBackColor);

		// You can pass in NULL for pWidth and pHeight if you want.
		void		(*GetSurfaceDims)(HSURFACE hSurf, uint32 *pWidth, uint32 *pHeight);
		
		// Draw a bitmap to a surface..
		LTBOOL		(*DrawBitmapToSurface)(HSURFACE hDest, char *pSourceBitmapName, 
			LTRect *pSrcRect, int destX, int destY);

		// Draws hSrc to hDest like a normal transparent blit, but tiles hMask's surface
		// into the nontransparent pixels of hSrc (can you say airbrushed text?)
		// You can't have a mask texture larger than 256x256, and the mask must be
		// a power of 2.
		LTRESULT	(*DrawSurfaceMasked)(HSURFACE hDest, HSURFACE hSrc, HSURFACE hMask,
			LTRect *pSrcRect, int destX, int destY, HLTCOLOR hColor);

		// Draws hSrc onto hDest, but fills in the nontransparent pixels with the
		// color you specify.
		LTRESULT	(*DrawSurfaceSolidColor)(HSURFACE hDest, HSURFACE hSrc,
			LTRect *pSrcRect, int destX, int destY, HLTCOLOR hTransColor, HLTCOLOR hFillColor);
		
		// Draws the source surface onto the dest surface.  You can specify a rectangle 
		// in the source surface and the destination coordinates on the destination
		// surface.. it doesn't scale the bitmap..  If you pass in NULL for the source
		// rect, it'll just use the whole thing.
		LTRESULT	(*DrawSurfaceToSurface)(HSURFACE hDest, HSURFACE hSrc, 
			LTRect *pSrcRect, int destX, int destY);

		LTRESULT	(*DrawSurfaceToSurfaceTransparent)(HSURFACE hDest, HSURFACE hSrc, 
			LTRect *pSrcRect, int destX, int destY, HLTCOLOR hColor);

		// Scales the source surface rectangle into the dest rectangle..
		LTRESULT	(*ScaleSurfaceToSurface)(HSURFACE hDest, HSURFACE hSrc,
			LTRect *pDestRect, LTRect *pSrcRect);

		LTRESULT	(*ScaleSurfaceToSurfaceTransparent)(HSURFACE hDest, HSURFACE hSrc,
			LTRect *pDestRect, LTRect *pSrcRect, HLTCOLOR hColor);

		LTRESULT	(*ScaleSurfaceToSurfaceSolidColor)(HSURFACE hDest, HSURFACE hSrc,
			LTRect *pDestRect, LTRect *pSrcRect, HLTCOLOR hTransColor, HLTCOLOR hFillColor);

		// (Affine) warps the source poly into the dest poly.  The source
		// coordinates are CLAMPED to be inside the source surface's rectangle, and
		// the warp is clipped against the destination rectangle (ie: don't specify
		// coordinates outside the source rectangle, but feel free to specify them
		// outside the destination rectangle).  The polygon you specify should be
		// convex.  The minimum number of coordinates is 3 and the maximum
		// is 10.
		LTRESULT	(*WarpSurfaceToSurface)(HSURFACE hDest, HSURFACE hSrc, 
			LTWarpPt *pCoords, int nCoords);

		LTRESULT	(*WarpSurfaceToSurfaceTransparent)(HSURFACE hDest, HSURFACE hSrc, 
			LTWarpPt *pCoords, int nCoords, HLTCOLOR hColor);

		LTRESULT	(*WarpSurfaceToSurfaceSolidColor)(HSURFACE hDest, HSURFACE hSrc, 
			LTWarpPt *pCoords, int nCoords, HLTCOLOR hTransColor, HLTCOLOR hFillColor);

		// Transform the source surface onto the dest surface.  The origin is
		// in the destination surface's coordinates.  If you specify NULL, it will
		// use the centerpoint as the origin.
		LTRESULT	(*TransformSurfaceToSurface)(HSURFACE hDest, HSURFACE hSrc,
			LTFloatPt *pOrigin, int destX, int destY, float angle,
			float scaleX, float scaleY);

		LTRESULT	(*TransformSurfaceToSurfaceTransparent)(HSURFACE hDest, HSURFACE hSrc,
			LTFloatPt *pOrigin, int destX, int destY, float angle,
			float scaleX, float scaleY, HLTCOLOR hColor);

		// Draw a filled rectangle into the surface.
		LTRESULT	(*FillRect)(HSURFACE hDest, LTRect *pRect, HLTCOLOR hColor);

		// Get/set surface alpha (values 0-1, default 1).
		// Note: alpha is only used on optimized surfaces, and only when they are
		// blitted to the screen.
		LTRESULT	(*GetSurfaceAlpha)(HSURFACE hSurface, float &alpha);
		LTRESULT	(*SetSurfaceAlpha)(HSURFACE hSurface, float alpha);



	// Access to client console variables...

		// Register a console program.  pName is just stored so it should either be
		// static or allocated.  When the client shell DLL is unloaded, it gets 
		// rid of any registered programs.
		// Returns LT_OK or LT_ALREADYEXISTS.
		LTRESULT	(*RegisterConsoleProgram)(char *pName, ConsoleProgramFn fn);
		
		// Returns LT_OK or LT_NOTFOUND.
		LTRESULT	(*UnregisterConsoleProgram)(char *pName);

		// Returns NULL if the parameter doesn't exist.
		HCONSOLEVAR		(*GetConsoleVar)(char *pName);
		
	// Access to server console mirror variables...

		// The 'new' accessors for server console variables.  Returns LT_NOTFOUND
		// if the variable isn't found.
		virtual LTRESULT	GetSConValueFloat(char *pName, float &val)=0;
		virtual LTRESULT	GetSConValueString(char *pName, char *valBuf, uint32 bufLen)=0;

		// Gets the value of a parameter .. returns 0/NULL if you pass in NULL.
		// OBSOLETE (will be removed soon).  Use the GetSCon functions.
		virtual float	GetServerConVarValueFloat(char *pName)=0;
		virtual char*	GetServerConVarValueString(char *pName)=0;
				

	// Helpers..

		// Use these to time sections of code.  Timing is done in microseconds
		// (1,000,000 counts per second).
		void		(*StartCounter)(LTCounter *pCounter);
		uint32		(*EndCounter)(LTCounter *pCounter);

		// Setup the panning sky stuff.  Pass in LTNULL for the filename if you want
		// to disable the panning sky.  Returns LT_NOTFOUND if it can't find
		// the texture.
		// index tells which global panning thing you want to change.  It
		// is one of the GLOBALPAN_ defines in de_codes.h.
		LTRESULT	(*SetGlobalPanTexture)(uint32 index, char *pFilename);
		LTRESULT	(*SetGlobalPanInfo)(uint32 index, float xOffset, float zOffset, float xScale, float zScale);

		// Register a surface effect.  You should register all your effects in OnEngineInitialized
		// (before you start a world).
		LTRESULT	(*AddSurfaceEffect)(SurfaceEffectDesc *pDesc);

		// Turn the input state on or off.  This is for times when the client
		// is interacting with menus and you don't want their mouse movement or
		// keystrokes to get sent to the server.  This defaults to ON.
		void		(*SetInputState)(LTBOOL bOn);

		// Clears all the keyboard, command, and axis offset input.
		LTRESULT	(*ClearInput)();

		// Returns a list of DeviceBindings for a given device.  You must call FreeDeviceBindings()
		// to free the list.
		DeviceBinding*	(*GetDeviceBindings)(uint32 nDevice);
		void			(*FreeDeviceBindings)(DeviceBinding* pBindings);

		// Track Input Devices.  Between calls to StartDeviceTrack() and EndDeviceTrack() no command
		// states will be set through the normal input.  Pass in the devices to track (DEVICETYPE_
		// defines) and a buffer size for all input devices.  The buffer size is the number of events
		// that could occur between calls to TrackDevice(), not to exceed MAX_INPUT_BUFFER_SIZE.
		// Supply TrackDevice() with an array of DeviceInput structures, and the number of structures
		// in the array.  When TrackDevice() returns, the pnInOut variable will contain the number of
		// events that have occurred (the number of filled-in DeviceInput structures).  If there were
		// more events that occurred than the original buffer size allowed for, TrackDevice will return
		// LT_INPUTBUFFEROVERFLOW.
		LTRESULT		(*StartDeviceTrack)(uint32 nDevices, uint32 nBufferSize);
		LTRESULT		(*TrackDevice)(DeviceInput* pInputArray, uint32* pnInOut);
		LTRESULT		(*EndDeviceTrack)();

		// Retrieve a list of device objects (like axes, buttons, etc.) for one or more devices.
		// Pass GetDeviceObjects a combination of DEVICETYPE_ flags and it will return a DeviceObject
		// (defined in ltbasedefs.h) list.
		// You must free the list with FreeDeviceObjects().
		DeviceObject*	(*GetDeviceObjects)(uint32 nDeviceFlags);
		void			(*FreeDeviceObjects)(DeviceObject* pList);

		// Get the name of the first input device of the given type.
		// Returns either LT_OK or LT_NOTFOUND.
		LTRESULT		(*GetDeviceName)(uint32 nDeviceType, char* pStrBuffer, uint32 nBufferSize);
		
		// Find out if the specified device is enabled yet.
		// Fills in the LTBOOL pointer and always returns LT_OK.
		LTRESULT		(*IsDeviceEnabled)(char* strDeviceName, LTBOOL* pIsEnabled);
		
		// Attempt to enable specified device.
		// Returns LT_OK or LT_ERROR.
		LTRESULT		(*EnableDevice)(char* strDeviceName);


		// These access the GAME timer (which resides on the server).
		// Since this comes from the server, it will be intermittent, so only 
		// use it for things that must be synced with server.  This timer will
		// not update when there isn't a connection to the server.
		float		(*GetGameTime)();
		float		(*GetGameFrameTime)();

		
		// Used to output a TRACE message to the Debug Output window.  Newlines must be explicitly used.
		void	(*DebugOut)( char *pMsg, ... );

		// Get the sky definition.
		LTRESULT	(*GetSkyDef)(SkyDef *pDef);

		LTBOOL		(*IsCommandOn)(int commandNum);

		// Same as typing a string into the console.
		void		(*RunConsoleString)(char *pString);

		// Get your client object (NULL if you don't currently have one).
		HLOCALOBJ	(*GetClientObject)();

		// You can set a global light scale that's applied to all rendering.
		// Colors are RGB 0-1 (values are clamped for you).	
		void		(*GetGlobalLightScale)(LTVector *pScale);
		void		(*SetGlobalLightScale)(LTVector *pScale);
		void		(*OffsetGlobalLightScale)(LTVector *pOffset);

		// Get/set global light direction.
		virtual LTRESULT	GetGlobalLightDir(LTVector &dir)=0;
		virtual LTRESULT	SetGlobalLightDir(LTVector dir)=0;

		// Get/set global light color
		virtual LTRESULT	GetGlobalLightColor(LTVector &color)=0;
		virtual LTRESULT	SetGlobalLightColor(LTVector color)=0;

		// Get/set ambient light (0-1, affects R, G, and B).
		virtual LTRESULT	GetAmbientLight(float &light)=0;
		virtual LTRESULT	SetAmbientLight(float light)=0;

		// Obsolete, use Parse2.
		int			(*Parse)(char *pCommand, char **pNewCommandPos, char *argBuffer, char **argPointers, int *nArgs);



	// Video functions.  These functions use Smacker movies.
	// OBSOLETE: USE LVideoMgr.
		virtual LTRESULT	StartVideo(char *pFilename, uint32 flags)=0;
		virtual LTRESULT	StopVideo()=0;
		virtual LTRESULT	UpdateVideo()=0;
		virtual LTRESULT	IsVideoPlaying()=0;


	// Messaging.

		virtual HMESSAGEWRITE	StartMessage(uint8 messageID)=0;
		virtual LTRESULT		EndMessage(HMESSAGEWRITE hMessage)=0; // Just calls EndMessage2 with MESSAGE_GUARANTEED.
		virtual LTRESULT		EndMessage2(HMESSAGEWRITE hMessage, uint32 flags)=0;


	// NEW message functions.  These functions don't free the message so you need to
	// call LMessage::Release after sending.

		virtual LTRESULT	SendToServer(ILTMessage &msg, uint8 msgID, uint32 flags)=0;


	// Management of client-side objects.

		HLOCALOBJ	(*CreateObject)(ObjectCreateStruct *pStruct);
		// Obsolete : Use RemoveObject
		LTRESULT	DeleteObject(HLOCALOBJ hObj) { return RemoveObject(hObj); };

		// OBSOLETE: use CommonLT::GetAttachments.
		virtual LTRESULT	GetAttachments(HLOCALOBJ hObj, HLOCALOBJ *inList, uint32 inListSize, 
			uint32 *outListSize, uint32 *outNumAttachments)=0;

		// Updates the position/rotation of the attachments on the object.  Attachments are
		// always automatically updated when the object is rendered.
		virtual LTRESULT	ProcessAttachments(HOBJECT hObj)=0;
		  

		// Change position and rotation.  It's more efficient to set them 
		// at the same time...
		// By default, the engine ignores really small movement values, but if bForce
		// is TRUE, then it will force the move no matter how small.
		void		(*GetObjectPos)(HLOCALOBJ hObj, LTVector *pPos);
		virtual LTRESULT SetObjectPos(HLOCALOBJ hObj, LTVector *pPos, LTBOOL bForce=LTFALSE)=0;

		void		(*GetObjectRotation)(HLOCALOBJ hObj, LTRotation *pRotation);
		void		(*SetObjectRotation)(HLOCALOBJ hObj, LTRotation *pRotation);
		void		(*SetObjectPosAndRotation)(HLOCALOBJ hObj, LTVector *pPos, LTRotation *pRotation);

		// Get/Set scale.
		LTRESULT		(*GetObjectScale)(HLOCALOBJ hObj, LTVector *pScale);
		LTRESULT		(*SetObjectScale)(HLOCALOBJ hObj, LTVector *pScale);

		// RGB 0-1.
		void		(*GetObjectColor)(HLOCALOBJ hObject, float *r, float *g, float *b, float *a);
		void		(*SetObjectColor)(HLOCALOBJ hObject, float r, float g, float b, float a);

		// OBSOLETE: Use CommonDE::GetObjectFlags/SetObjectFlags.
		virtual uint32	GetObjectFlags(HOBJECT hObj)=0;
		virtual void	SetObjectFlags(HOBJECT hObj, uint32 flags)=0;

		// Get/Set object user flags.  Can't set user flags on an object
		// created on the server.
		LTRESULT		(*GetObjectUserFlags)(HLOCALOBJ hObj, uint32 *pFlags);
		LTRESULT		(*SetObjectUserFlags)(HLOCALOBJ hObj, uint32 flags);
		
		// Get/set the client flags (defined above).
		uint32		(*GetObjectClientFlags)(HLOCALOBJ hObj);
		void		(*SetObjectClientFlags)(HLOCALOBJ hObj, uint32 flags);

		// User data for the object..
		void*		(*GetObjectUserData)(HLOCALOBJ hObj);
		void		(*SetObjectUserData)(HLOCALOBJ hObj, void *pData);


	// Camera functions.

		// Gets the 3D coordinates of a screen coordinate given a camera.  The 3D
		// coordinate is one unit out along the forward vector.  Returns LT_OUTSIDE
		// if the screen coordinates aren't inside the camera's rectangle.
		LTRESULT		(*Get3DCameraPt)(HLOCALOBJ hCamera, int sx, int sy, LTVector *pOut);

		// Get/Set a camera's FOV.  It defaults to (PI/2, PI/2).
		// It will clamp your values between (PI/100, 99*PI/100)
		void		(*GetCameraFOV)(HLOCALOBJ hObj, float *pX, float *pY);
		void		(*SetCameraFOV)(HLOCALOBJ hObj, float fovX, float fovY);

		void		(*GetCameraRect)(HLOCALOBJ hObj, LTBOOL *bFullscreen,
			int *left, int *top, int *right, int *bottom);
		
		// Set the camera's rectangle on the screen.
		// If bFullscreen is LTTRUE, then it ignores the rect and draws the
		// camera fullscreen.  If the rectangle extends over the screen
		// boundaries, then it is clipped..
		void		(*SetCameraRect)(HLOCALOBJ hObj, LTBOOL bFullscreen, 
			int left, int top, int right, int bottom);

		// Get/Set the camera light add.  RGB 0-1.  Light add is applied AFTER
		// scaling, so if light is fully bright and scaling is zero, you'll just
		// see whiteness.  When the light add is nonzero, it draws a poly over 
		// the screen so don't use it all the time!
		// These return LTFALSE if the object is not a camera.
		LTBOOL		(*GetCameraLightAdd)(HLOCALOBJ hCamera, LTVector *pAdd);
		LTBOOL		(*SetCameraLightAdd)(HLOCALOBJ hCamera, LTVector *pAdd);



	// Particle system manipulation.

		// gravityAccel default is -500
		// flags default is 0
		// particleRadius default is 300
		// color scale defauls to 1.0
		// Particle colors are 0-255.
		
		// All particle positions are RELATIVE to the particle system's 
		// position and rotation.  In many cases, you can have your code be very simple
		// and fast if you just move and rotate the particle system and not the particles.
		
		// Change the system's parameters.
		LTRESULT		(*SetupParticleSystem)(HLOCALOBJ hObj, char *pTextureName, float gravityAccel, uint32 flags, float particleRadius);

		// The software version uses a single color for all the particles in each
		// system specified here (default 1).  RGB (0-1).
		LTRESULT		(*SetSoftwarePSColor)(HLOCALOBJ hObj, float r, float g, float b);

		virtual LTParticle*	AddParticle(HLOCALOBJ hObj, LTVector *pPos, LTVector *pVelocity, LTVector *pColor, float lifeTime)=0;
		
		void		(*AddParticles)(HLOCALOBJ hObj, uint32 nParticles,
			LTVector *pMinOffset, LTVector *pMaxOffset,
			LTVector *pMinVelocity, LTVector *pMaxVelocity, 
			LTVector *pMinColor, LTVector *pMaxColor,
			float minLifetime, float maxLifetime);

		LTBOOL		(*GetParticles)(HLOCALOBJ hObj, LTParticle **pHead, LTParticle **pTail);

		// Get/Set particle positions.  hSystem is NOT checked to be valid here
		// for speed so make sure it's valid!
		void		(*GetParticlePos)(HLOCALOBJ hSystem, LTParticle *pParticle, LTVector *pPos);
		void		(*SetParticlePos)(HLOCALOBJ hSystem, LTParticle *pParticle, LTVector *pPos);

		// Get particle lifetimes.  hSystem is NOT checked to be valid here
		// for speed so make sure it's valid!
		LTRESULT	(*GetParticleLifetime)(HLOCALOBJ hSystem, LTParticle *pParticle, LTFLOAT & fLifetime);
		LTRESULT	(*GetParticleTotalLifetime)(HLOCALOBJ hSystem, LTParticle *pParticle, LTFLOAT & fTotalLifetime);

		// Remove a particle.
		void		(*RemoveParticle)(HLOCALOBJ hSystem, LTParticle *pParticle);

		// This is an optimization you can make to help the engine minimize its boundaries on
		// a particle system.  If you create particles in various places and they go away, you
		// can use this every so often to recalculate where the particles are.
		LTRESULT	(*OptimizeParticles)(HLOCALOBJ hSystem);
		


	// Line system manipulation.
	// As with particle systems, the lines are centered around the object's origin.
	// Don't just place the object at the origin and put lines way off to the side,
	// it's more efficient to keep the lines as close to the center as possible.

		// Set hPrev to NULL to start, then pass in the return value, etc..
		// Returns LTNULL for last line.
		// ** If you call RemoveLine on the current HLTLINE, DO NOT
		// ** pass that into GetNextLine - call GetNextLine first
		// ** while the HLTLINE is still valid!
		HLTLINE		(*GetNextLine)(HLOCALOBJ hObj, HLTLINE hPrev);

		void		(*GetLineInfo)(HLTLINE hLine, LTLine *pLine);
		void		(*SetLineInfo)(HLTLINE hLine, LTLine *pLine);

		// Adds a line to the end of the line system's list.
		HLTLINE		(*AddLine)(HLOCALOBJ hObj, LTLine *pLine);
		void		(*RemoveLine)(HLOCALOBJ hObj, HLTLINE hLine);


	// Poly grid manipulation.

		// A poly grid is basically a heightmapped grid of pixels that are drawn
		// as polygons.  Each pixel can have a value from -127 to 127.  The pixel's value 
		// defines its height and is a lookup into the color table for the vertex color.
		// You can scale and rotate the poly grid using SetObjectScale and SetObjectRotation.
		// bHalfTriangles will cause it to look VERY triangulated, but draw way faster.
		LTBOOL		(*SetupPolyGrid)(HLOCALOBJ hObj, uint32 width, uint32 height, LTBOOL bHalfTrianges);

		// Set the texture.  The texture MUST be a sprite file.  It CANNOT be a .dtx file!
		LTRESULT	(*SetPolyGridTexture)(HLOCALOBJ hObj, char *pFilename);

		// Set the environment map for the PolyGrid.  This MUST be a DTX file.
		// Specify NULL if you want to disable the environment map.  Returns 
		// LT_NOTFOUND if it can't find the specified map.
		LTRESULT	(*SetPolyGridEnvMap)(HLOCALOBJ hObj, char *pFilename);

		// Get/Set the texture pan and scale for a PolyGrid.
		// Defaults are 0.0 for xPan and yPan, and 1.0 for xScale and yScale.
		LTRESULT	(*GetPolyGridTextureInfo)(HLOCALOBJ hObj, float *xPan, float *yPan, float *xScale, float *yScale);
		LTRESULT	(*SetPolyGridTextureInfo)(HLOCALOBJ hObj, float xPan, float yPan, float xScale, float yScale);
		
		// You can set it to be transparent or not.  It defaults to not being transparent.
		LTRESULT	(*GetPolyGridInfo)(HLOCALOBJ hObj, char **pBytes, uint32 *pWidth, uint32 *pHeight, PGColor **pColorTable);

		// Set pMin and pMax to the dimensions of the box you want the polygrid to fit in.
		// pPos and pScale will be filled in with the recommended position and scale.
		LTRESULT	(*FitPolyGrid)(HLOCALOBJ hObj, LTVector *pMin, LTVector *pMax, LTVector *pPos, LTVector *pScale);


	// Light manipulation.

		// Get/Set a light's color (RGB, 0.0f to 1.0f).
		// When you create a light, its color defaults to (0,0,0).
		void	(*GetLightColor)(HLOCALOBJ hObj, float *r, float *g, float *b);
		void	(*SetLightColor)(HLOCALOBJ hObj, float r, float g, float b);

		// Get/Set a light's radius.
		// When you create a light, its radius defaults to 100.
		float	(*GetLightRadius)(HLOCALOBJ hObj);
		void	(*SetLightRadius)(HLOCALOBJ hObj, float radius);


	// Sprite manipulation.

		// This clips the sprite on the poly.
		// Returns LT_OK or LT_ERROR if not a sprite.
		// Pass in INVALID_HPOLY to un-clip the sprite.
		LTRESULT	(*ClipSprite)(HLOCALOBJ hObj, HPOLY hPoly);

		// Get the sprite control interface for a sprite.  Returns LT_INVALIDPARAMS
		// if the object is not a sprite.
		virtual LTRESULT GetSpriteControl(HLOCALOBJ hObj, ILTSpriteControl* &pControl)=0;


	// Canvas manipulation.

		virtual LTRESULT GetCanvasFn(HOBJECT hCanvas, CanvasDrawFn &fn, void* &pUserData)=0;
		virtual LTRESULT SetCanvasFn(HOBJECT hCanvas, CanvasDrawFn fn, void* pUserData)=0;

		virtual LTRESULT GetCanvasRadius(HOBJECT hCanvas, float &radius)=0;
		virtual LTRESULT SetCanvasRadius(HOBJECT hCanvas, float radius)=0;


	// Client-side models..

		// Use this to control the nodes on the model.
		// NOTE: your function should return as FAST as possible - it will be called a lot.
		// NodeControlFn will be called for each node on the model allowing you to
		// translate and rotate it.
		// Pass NULL for the NodeControlFn to disable it.
		// Note: this slows down rendering because the engine can't assume a bounding radius.
		// If you know your movement won't move anything outside of its bounding radius, you
		// can set CF_INSIDERADIUS to avoid a speed hit.
		virtual LTRESULT ModelNodeControl(HOBJECT hObj, NodeControlFn fn, void *pUserData)=0;
	
		// Iterate through the model's nodes.  Returns LT_FINISHED when there are no more.
		// hCurNode = INVALID_MODEL_NODE;
		// while(interface->GetNextModelNode(hModel, hCurNode, &hCurNode) == LT_OK)
		// { ... }
		LTRESULT	(*GetNextModelNode)(HLOCALOBJ hObject, HMODELNODE hNode, HMODELNODE *pNext);

		// Get a model node's name.
		LTRESULT	(*GetModelNodeName)(HLOCALOBJ hObject, HMODELNODE hNode, char *pName, uint32 maxLen);

		
	// OBSOLETE: Use ModelLT functions.

		// Returns the animation the model is currently on.  (uint32)-1 if none.
		virtual uint32 GetModelAnimation(HLOCALOBJ hObj)=0;
		virtual void SetModelAnimation(HLOCALOBJ hObj, uint32 iAnim)=0;

		// Starts the current animation over.
		virtual LTRESULT	ResetModelAnimation(HLOCALOBJ hObj)=0;

		// Tells what the playback state of the model is (a combination of the
		// MS_ bits defined in basedefs_de.h).
		virtual uint32 GetModelPlaybackState(HLOCALOBJ hObj)=0;

		// Get/Set the looping state of the model.  The default state is TRUE.
		virtual LTBOOL GetModelLooping(HLOCALOBJ hObj)=0;
		virtual void SetModelLooping(HLOCALOBJ hObj, LTBOOL bLoop)=0;

		// Get/Set the playing state of the model.  The default state is FALSE.
		virtual LTBOOL GetModelPlaying(HLOCALOBJ hObj)=0;
		virtual void SetModelPlaying(HLOCALOBJ hObj, LTBOOL bPlaying)=0;

	// (Geometry) surface functions.

		LTBOOL	(*GetSurfaceBounds)(SurfaceData *pSurface, LTVector *pMin, LTVector *pMax);

		// Hide/Unhide a poly.
		LTRESULT	(*SetPolyHideStatus)(HPOLY hPoly, LTBOOL bHide);

		// Get the texture flags from a poly.  Returns LT_OK
		// or LT_ERROR if no world is loaded or hPoly is invalid.
		LTRESULT	(*GetPolyTextureFlags)(HPOLY hPoly, uint32 *pFlags);

	
	// Render hooks.

		// When this is set, the renderer will call your hook function before drawing each
		// model.  Either keep the function very fast or set it to NULL so you don't slow
		// the renderer down.
		LTRESULT	(*SetModelHook)(ModelHookFn fn, void *pUser);


	// Engine hooks.

		// This is here so we can avoid adding API functions if necessary and for
		// some system-dependent or misc. stuff.  Pass in a string describing what
		// you want and it fills in pData.
		// Returns LT_OK if it understands the string or an error otherwise.
		// Strings:
		//    HWND: Returns main window handle.
		LTRESULT	(*GetEngineHook)(char *pName, void **pData);


	// Network startup/join/host functions.

		// Call this function before calling any other
		// network functions. pDriver can be NULL to use the default net driver.
		// No flags are currently supported.
		LTRESULT (*InitNetworking)(char *pDriver, uint32 dwFlags);

		// Gets a list of net services (tcp/ip, modem, etc).
		LTRESULT (*GetServiceList)(NetService* &pListHead);

		// Call this function when you are finished using the list returned by
		// GetServiceList().
		LTRESULT (*FreeServiceList)(NetService *pListHead);

		// Selects the given service as the one to use.
		LTRESULT (*SelectService)(HNETSERVICE hNetService);

		// Gets a list (and count) of enumerated sessions.
		// See driver flags for a description of pInfo.
		LTRESULT (*GetSessionList)(NetSession* &pListHead, char *pInfo);

		// Call this function when you are finished using the list returned by
		// GetSessionList().
		LTRESULT (*FreeSessionList)(NetSession *pListHead);

		LTRESULT (*AddInternetDriver)();
		LTRESULT (*RemoveInternetDriver)();

	// Alternate mode of getting session lists.  These only work for services with
	// the NETSERVICE_TCPIP flag.  These functions return immediately so you can update
	// a UI in the background without having to 'freeze' the UI while it queries hosts.

		// Start querying.  pInfo contains the address list formatted just like GetSessionLists.
		virtual LTRESULT StartQuery(char *pInfo)=0;
		
		// Update the query.  Call this as often as possible.
		virtual LTRESULT UpdateQuery()=0;

		// Get the current list of results from the query.  Each time you call this,
		// a new session list is allocated and you need to free it with FreeSessionList.
		virtual LTRESULT GetQueryResults(NetSession* &pListHead)=0;

		// End the current query.
		virtual LTRESULT EndQuery()=0;


		// Determines if we werw lobby launched.
		LTRESULT (*IsLobbyLaunched)(char* sDriver);

		// Gets the lobby launch info if available.
		LTRESULT (*GetLobbyLaunchInfo)(char* sDriver, void** ppLobbyLaunchData);

		// Gets the tcp/ip address of the main driver if available.
		LTRESULT (*GetTcpIpAddress)(char* sAddress, uint32 dwBufferSize);

	protected:
		
		ILTVideoMgr			*m_pVideoMgr;
		ILTTexMod			*m_pTexMod;
		ILTCursor			*m_pCursorLT;
		ILTDirectMusicMgr	*m_pDirectMusicMgr;
	};



#endif  // __ILTCLIENT_H__
