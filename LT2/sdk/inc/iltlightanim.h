
// Defines the ILTLightAnim interface.  

#ifndef __ILIGHTANIM_H__
#define __ILIGHTANIM_H__


	#include "ltbasedefs.h"


	#define INVALID_LIGHT_ANIM	0xFFFFFFFF
	#define LIGHTANIMFRAME_NONE	0xFFFFFFFF

	// NOTE: you can write HLIGHTANIMs to messages as uint32's.
	typedef unsigned long HLIGHTANIM;


	// LightAnim info;
	class LAInfo
	{
	public:

		// Is this a shadow-mapped animation?
		// This can't be changed at runtime.
		LTBOOL	m_bShadowMap;		

		// What frame(s) we're going between.
		// NOTE: to disable the light entirely, set iFrame1 and iFrame2 to LIGHTANIMFRAME_NONE.
		uint32	m_iFrames[2];
		float	m_fPercentBetween;	// How far between the two frames.

		// fBlendPercent (value 0-1) tells how much of the data to blend in, so for a flicker
		// light, you could just flicker fBlendPercent between 0-1 to go on and off.
		float	m_fBlendPercent;

		// Lighting info, if we're using shadow maps.
		LTVector	m_vLightPos;
		LTVector	m_vLightColor;	// RGB 0-255.
		float		m_fLightRadius;
	};


	// The ILTLightAnim interface allows game code to animate the light animations
	// that are created in the preprocessor.

	// NOTE: like most things in the engine, you can control it from the server or the 
	// client, but you should never control it from both (since the client never knows
	// when an engine server update will get there, it can't change something and assume
	// that the server won't change it).
	class ILTLightAnim
	{
	public:
		
		// Get a handle to a light animation.
		// Sets hLightAnim to INVALID_LIGHT_ANIM and returns LT_NOTFOUND if pName is not found.
		virtual LTRESULT	FindLightAnim(const char *pName, HLIGHTANIM &hLightAnim)=0;

		// Get the number of frames in a light animation.
		virtual LTRESULT	GetNumFrames(HLIGHTANIM hLightAnim, uint32 &nFrames)=0;

		// Get/Set the anim info.
		virtual LTRESULT	GetLightAnimInfo(HLIGHTANIM hLightAnim, LAInfo &info)=0;
		virtual LTRESULT	SetLightAnimInfo(HLIGHTANIM hLightAnim, LAInfo &info)=0;
	};


#endif // __ILIGHTANIM_H__


