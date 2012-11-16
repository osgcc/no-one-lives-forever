// ----------------------------------------------------------------------- //
//
// MODULE  : ltengineobjects.h.
//
// PURPOSE : C++ LithTech engine object class(es) definition(s)
//
// CREATED : 9/17/97
//
// ----------------------------------------------------------------------- //

#ifndef __LTENGINEOBJECTS_H__
#define __LTENGINEOBJECTS_H__


	#include "ltbasedefs.h"
	#include "ltserverobj.h"
	#include "iaggregate.h"


	/////////////////////////////////////////////////////////////////////
	// C++ BaseClass interface. 
	// This is the base class of ALL objects.  You MUST derive from this!
	/////////////////////////////////////////////////////////////////////

	class ILTServer;
	extern ILTServer *g_pLTServer;

	class BaseClass
	{
	public:

							BaseClass(uint8 nType=OT_NORMAL) 
							{ 
								m_pFirstAggregate = NULL;
								m_hObject = NULL; 
								m_nType = nType; 
							}
			
		virtual				~BaseClass() {}

		uint8				GetType() const { return m_nType; }
		void				SetType( uint8 type ) { m_nType = type; }
		static ILTServer*	GetServerDE() { return (ILTServer*)g_pLTServer; }

		// If you derive from BaseClass, pass your messages down to here at the
		// end of your message loop.
		virtual uint32		EngineMessageFn(uint32 messageID, void *pData, LTFLOAT lData);

		// Call this when you get an object message function so aggregates will get it.
		virtual uint32		ObjectMessageFn(HOBJECT hSender, uint32 messageID, HMESSAGEREAD hRead);

	
	protected:

		void			AddAggregate(LPAGGREGATE pAggregate);
		LTBOOL			RemoveAggregate(LPAGGREGATE pAggregate);


	public:  // Data members

		// VERY Important that these data memebers stay in this order. 
		// This version and the C version must be the same!
		
		LPAGGREGATE		m_pFirstAggregate;// The first aggregate in the linked list..

		// This is always set.. you can use this to pass in an 
		// HOBJECT to the functions that require on instead of calling
		// ObjectToHandle() every time..
		HOBJECT			m_hObject;

		// C++ only data...
		uint8			m_nType;	// Type of object (see ltbasedefs.h)
	};


	// The WorldSection class.
	class WorldSection : public BaseClass
	{
	public:
	};


	// Terrain.
	class Terrain : public BaseClass
	{
	public:
	};


	// Container.
	class Container : public BaseClass
	{
	public:

		virtual uint32	EngineMessageFn(uint32 messageID, void *pData, float lData);

		uint32	m_ContainerCode;
	};


	// Sound.
	class Sound : public BaseClass
	{
	public:

		virtual uint32	EngineMessageFn(uint32 messageID, void *pData, float lData);

		char	m_Filename[101];
		float	m_fOuterRadius;
		float	m_fInnerRadius;
		uint8	m_nVolume;
		LTBOOL	m_bAmbient;
		unsigned char	m_nPriority;
	};


	// InsideDef.
	// These are used by the preprocessor to define 'inside' areas.
	class InsideDef : public BaseClass
	{
	public:

	};


	// OutsideDef class.
	// These are used if you want the preprocessor to make a leak file for a level.
	class OutsideDef : public BaseClass
	{
	public:
	};


	// FastApproxArea class.
	// This defines an area where only fast approximation vising will occur.  The
	// area is bounded by hullmakers and portals.
	class FastApproxArea : public BaseClass
	{
	public:
	};


	// Light class.
	class Light : public BaseClass
	{
	public:
	};
	
	
	// ObjectLight class (these lights only light objects.. they don't light the world).  These
	// are used for landscape areas lit by GlobalDirLights (which don't light objects).
	class ObjectLight : public BaseClass
	{
	public:
	};


	// DirLight class.
	class DirLight : public BaseClass
	{
	public:
	};


	// StaticSunLight class.
	class StaticSunLight : public BaseClass
	{
	public:
		virtual uint32	EngineMessageFn(uint32 messageID, void *pData, float lData);

		LTVector	m_InnerColor;
		LTVector	m_OuterColor;
		float		m_BrightScale;
	};


	// Brush class.
	class Brush : public BaseClass
	{
	public:
	};


	// DemoSkyWorldModel class.  This is a WorldModel that adds itself to the sky object
	// list and has properties that level designers can edit to set the sky dimensions.
	// If the sky box is set to zero, then it won't set it.  (This is so you can have
	// multiple DemoSkyWorldModels in the world, and only one sets the sky box).
	// The DemoSkyWorldModel uses InnerPercentX, Y, and Z as a percentage of the 
	// SkyDims box for the inner box.
	// Each sky world model must have a (unique) index from 0-30.  Ones with
	// lower indices get drawn first.
	class DemoSkyWorldModel : public BaseClass
	{
	public:

		virtual uint32	EngineMessageFn(uint32 messageID, void *pData, float lData);

		LTVector	m_SkyDims;
		float		m_InnerPercentX, m_InnerPercentY, m_InnerPercentZ;
		long		m_Index;
	};


	// This works exactly the same as a DemoSkyWorldModel, except you identify the object by name.
	class SkyPointer : public BaseClass
	{
	public:
		virtual uint32	EngineMessageFn(
			uint32 messageID, void *pData, float lData);

		LTVector	m_SkyDims;
		float		m_InnerPercentX, m_InnerPercentY, m_InnerPercentZ;
		long		m_Index;
		char		m_ObjectName[100];
	};


	// These objects, when used with the preprocessor's -RaySelect flag, will cause the
	// first brush this object's forward vector hits to be selected in the ED file.
	class RaySelecter : public BaseClass
	{
	public:
	};


	// This has functionality to be almost any type of engine object.
	class GenericObject : public BaseClass
	{
	public:
		virtual uint32	EngineMessageFn(
			uint32 messageID, void *pData, float lData);

		float		m_LightRadius;
		float		m_ColorR;
		float		m_ColorG;
		float		m_ColorB;
		float		m_ColorA;
	};
			
	

	// Used to assist visibility scheme.
	class Zone : public BaseClass
	{
	public:
	};


#endif  // __LTENGINEOBJECTS_H__
