
#ifndef __ILTVIDEOMGR_H__
#define __ILTVIDEOMGR_H__


	class VideoInst;
	typedef VideoInst* HVIDEO;


	// Note: all routines in here will return LT_NOTINITIALIZED if the engine can't
	// initialize the system's video modules or the runtime DLLs are missing.
	class ILTVideoMgr
	{
	public:
		
		// LT_OK, VIDEO_ERROR.
		// flags is a combination of the PLAYBACK_ flags in de_codes.h.
		virtual LTRESULT StartOnScreenVideo(char *pFilename, uint32 flags, HVIDEO &hVideo)=0;
		virtual LTRESULT StartTextureVideo(char *pFilename, uint32 flags, HVIDEO &hVideo)=0;

		// For on-screen videos, this draws the current video to the screen.
		virtual LTRESULT UpdateVideo(HVIDEO hVideo)=0;
		
		// LT_OK = still playing
		// LT_FINISHED = done playing
		// When it's done playing, it will sit at the last frame.  You MUST call StopVideo
		// to free a video's resources.
		virtual LTRESULT GetVideoStatus(HVIDEO hVideo)=0;

		// Stop playing a video.  For a texture video, this restores the original textures
		// on any polies it's bound to.
		virtual LTRESULT StopVideo(HVIDEO hVideo)=0;

		virtual LTRESULT BindTextureVideoToPoly(HVIDEO hVideo, HPOLY hPoly)=0;
	};


#endif  // __ILTVIDEOMGR_H__