#ifndef REDMGR_H
#define REDMGR_H


// Includes...

#include "lith.h"
#include <mmsystem.h>


// Libs...

#ifndef NO_PRAGMA_LIBS
	#ifdef _DEBUG
		#pragma comment (lib, "\\proj\\libs\\debug\\redmgr.lib")
	#else
		#pragma comment (lib, "\\proj\\libs\\release\\redmgr.lib")
	#endif
#endif


// Classes...

class CRedMgr : public CObject {
public:
  CRedMgr() { m_bIsInited = FALSE; m_posPause = 0; m_bOutputDevIDFound = 0; m_dwOriginalVolume = 0; }
  ~CRedMgr() { Term(); };
  BOOL      Init( HWND hWnd = NULL );                   // Initialize class (must be called first)
  void      Term(BOOL bStopIfPlaying = TRUE);           // Terminate class (must be called last)
  BOOL		PlayTrack(int nTrack);						// Play an entire CD track
  BOOL      Play(int nFromTrack = 1, int nFromMin = 0,  // Play CD track (or portion)
                 int nFromSec = 0, int nFromFrame = 0,
                 int nToTrack = 0, int nToMin = 0, 
                 int nToSec = 0, int nToFrame = 0);
  BOOL      PlayToEnd(int nFromTrack = 1, int nFromMin = 0,  // Play CD track until end of cd
                 int nFromSec = 0, int nFromFrame = 0);
  BOOL      Stop();                                     // Stop playing
  UINT32    GetPosition();                              // Return current play position (in TMSF format)
  UINT32    GetNumTracks();                             // Returns the number of tracks on the current cd
  UINT32    GetTrackLen(int nTrack);                    // Returns the length of the specified track (in MSF format!!!!)
  UINT32    GetTrackLenSeconds(int nTrack);             // Returns the length of the specified track in seconds
  BOOL      MediaPresent();                             // Returns true if a cd is in the drive, false if not
  UINT32    GetStatus();                                // Returns the current status of the cd player
  BOOL      IsPlaying() { return (GetStatus() == MCI_MODE_PLAY); }; // returns true if cd player is playing right now
  BOOL      IsValid() { return (this != NULL); };       // Check if this object is valid                  

  BOOL		Pause();									// [blg] pauses current playback
  BOOL		Resume(int nTrack = 0);						// [blg] resumes previously paused playback (track = 0 means play to end)
  BOOL		IsPaused() { return(m_posPause != 0); }		// [blg] determines if Pause() has been called, but not Resume()
  void		ClearPause() { m_posPause = 0; }			// [blg] clears any pauses so Resume() won't work

  BOOL		IsVolumeControl( ) { return m_bOutputDevIDFound; }
  UINT32	GetVolume( );								// Returns the current volume 0-off, 100-full
  void		SetVolume( UINT32 iVolume );				// Sets the volume

private:
  void      OutMCIErr(MCIERROR nErr, char* sOut);    

  MCI_STATUS_PARMS MCIStatus;                       // MCI_STATUS structure
  MCI_OPEN_PARMS MCIOpen;                           // MCI_OPEN structure
  MCI_PLAY_PARMS MCIPlay;                           // MCI_PLAY structure
  MCI_SET_PARMS MCISet;                             // MCI_SET structure
  BOOL m_bIsInited;                                 // true if init has been called, but not term
  UINT32 m_posPause;									// [blg] paused position
  HWND m_hWnd;										// Window handle for callback on MCI_NOTIFY
  BOOL m_bOutputDevIDFound;							// Output device id found
  UINT m_iOutputDevID;								// Output device used by CD Audio
  DWORD m_dwOriginalVolume;							// Original volume before redmgr initialized
};

#endif
