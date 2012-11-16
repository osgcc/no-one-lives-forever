
#ifndef __ILTSPRITECONTROL_H__
#define __ILTSPRITECONTROL_H__


	// Sprite control flags.  Default flags for a sprite are SC_PLAY|SC_LOOP.
	#define SC_PLAY		(1<<0)
	#define SC_LOOP		(1<<1)


	class ILTSpriteControl
	{
	public:

		virtual LTRESULT	GetNumAnims(uint32 &nAnims)=0;
		virtual LTRESULT	GetNumFrames(uint32 iAnim, uint32 &nFrames)=0;
		
		virtual LTRESULT	GetCurPos(uint32 &iAnim, uint32 &iFrame)=0;
		virtual LTRESULT	SetCurPos(uint32 iAnim, uint32 iFrame)=0;
		
		virtual LTRESULT	GetFlags(uint32 &flags)=0;
		virtual LTRESULT	SetFlags(uint32 flags)=0;
	};


#endif  // __ILTSPRITECONTROL_H__