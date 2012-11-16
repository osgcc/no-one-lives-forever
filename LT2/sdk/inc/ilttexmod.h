
// The ILTTexMod interface allows the game to modify textures and bump maps in realtime.

#ifndef __ILTTEXMOD_H__
#define __ILTTEXMOD_H__

	
	#include "ltpvalue.h"


	// Color data is always loaded into memory, but you can have a bumpmap loaded as well.
	#define THANDLE_BUMPMAP	(1<<0)

	#define TLOCK_TEXTURE	0	// If this is used, then the data is in PValue format.
	#define TLOCK_BUMPMAP	1	// If this is used, then the data is a DBYTE heightmap.


	class TextureInfo
	{
	public:
		uint32		m_Width;
		uint32		m_Height;
	};


	class SharedTexture;
	typedef SharedTexture* HTEXTURE;


	// Texture-modification interface.
	class ILTTexMod
	{
	public:

		// Use these to get and release texture handles.
		// The first time you get a texture handle, it will allocate space for the texture and/or
		// the bumpmap, based on the flags you specify.  If you need to specify different flags,
		// you must release ALL texture handles and get a new one.
		// When all texture handles for a texture are released, the texture goes back to its
		// original form (from its disk file).
		virtual LTRESULT	GetTextureHandle(
			char *pFilename, 
			HTEXTURE &hTexture, 
			const uint32 flags	// Combination of the THANDLE_ flags.
			)=0;
		
		virtual LTRESULT	ReleaseTextureHandle(const HTEXTURE hTexture)=0;

		// Get info about a texture.
		virtual LTRESULT	GetTextureInfo(const HTEXTURE hTexture, TextureInfo &info)=0;

		// Returns LT_YES if the texture was drawn in the last Render call and LT_NO otherwise.
		// (Or LT_INVALIDPARAMS if the texture handle is invalid).
		// This should be called before you ever update a texture's contents.  If it returns
		// LT_NO, then you don't need to update the texture because it's not being viewed.
		virtual LTRESULT	WasTextureDrawnLastFrame(const HTEXTURE hTexture)=0;

		// The texture lock returns a uint8 pointer to the data because you should iterate over
		// the texture's lines like this:
		//		uint8 *pLines;
		//		if(pInterface->LockTexture(hTexture, &rect, lockFlags, pLines, lPitch) == LT_OK)
		//		{
		//			height = rect.bottom - rect.top;
		//			while(height--)
		//			{
		//				pRealData = (cast pLines to a PValue or DBYTE and fill the line)
		//				pLines += lPitch;
		//			}
		//			
		//			pInterface->UnlockTexture(hTexture);
		//		}
		virtual LTRESULT	LockTexture(
			const HTEXTURE hTexture,	// Texture handle.
			const LTRect *pRect,		// Rect to lock (NULL for the whole texture).
			const uint32 lockType,		// Must be one of the TLOCK_ defs.
			uint8* &pData,				// Data (format depends on TLOCK_ flags).
			long &lPitch				// Pitch in bytes.
			)=0;

		// Once you unlock the texture, the engine converts the data to the renderer's format.
		// It also automatically updates the texture's mipmaps (if any).  Ideally, textures
		// that you're updating in realtime won't have mipmaps.
		virtual LTRESULT	UnlockTexture(const HTEXTURE hTexture)=0;
	};


#endif  // __ILTTEXMOD_H__