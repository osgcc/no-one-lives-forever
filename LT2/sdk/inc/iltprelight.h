
// This file contains the interfaces used to build light animations
// in the preprocessor.

#ifndef __ILTPRELIGHT_H__
#define __ILTPRELIGHT_H__


	#include "ltbasedefs.h"
	#include "iltmath.h"


	#define MAX_PREWORLDMODELINFONAME_LEN	64


	// This structure describes the position, color, and other info for a frame
	// of light animation.
	class PreLightInfo
	{
	public:
					PreLightInfo()
					{
						m_vPos.Init();
						m_vInnerColor.Init();
						m_vOuterColor.Init();
						m_Radius = 1.0f;
                        m_bDirectional = LTFALSE;
						m_vDirection.Init();
						m_FOV = 0.0f;
					}


	public:

		LTVector	m_vPos;

		LTVector	m_vInnerColor;	// RGB 0-255
		LTVector	m_vOuterColor;
		float		m_Radius;

		LTBOOL		m_bDirectional;
		LTVector	m_vDirection;	// (Used if it's directional).
		float		m_FOV;			// In radians.
	};


	// You can add these to a light animation frame to animate world models.
	class PreWorldModelInfo
	{
	public:

					PreWorldModelInfo()
					{
						m_WorldModelName[0] = 0;
						m_Pos.Init();
						m_Rot.Init();
						m_bInvisible = LTFALSE;
					}

		char		m_WorldModelName[MAX_PREWORLDMODELINFONAME_LEN];
		LTVector	m_Pos;
		LTRotation	m_Rot;
		LTBOOL		m_bInvisible;	// If you want light calculated like the world model
									// doesn't exist..
	};


	class PreLightAnimFrameInfo
	{
	public:

					PreLightAnimFrameInfo()
					{
						m_vSunLightDir.Init();
						m_vSunLightInnerColor.Init();
						m_vSunLightOuterColor.Init();
						m_bSunLight = LTFALSE;

						m_Lights = LTNULL;
						m_nLights = 0;

						m_WorldModels = LTNULL;
						m_nWorldModels = 0;
					}

	public:

		// Does this frame have sunlight?
		LTVector	m_vSunLightDir;
		LTVector	m_vSunLightInnerColor;	// RGB 0-255
		LTVector	m_vSunLightOuterColor;	// RGB 0-255
		LTBOOL		m_bSunLight;

		// The lights that contribute to this frame.
		PreLightInfo	*m_Lights;
		uint32			m_nLights;

		// WorldModel movements..
		PreWorldModelInfo	*m_WorldModels;
		uint32				m_nWorldModels;
	};


	// Preprocessor lighting interface.  Passed to the game code when lightmaps are being
	// generated.
	class ILTPreLight
	{
	public:

        inline ILTMath*  GetMathLT() {return m_pMathLT;}

		// Create a light animation using the specified frames.
		// If bShadowMap is set, then a ShadowMap animation is created.  ShadowMap animations:
		// + take about 10x less data
		// + allow the game to change the light radius and color at runtime
		// - take more processor time at runtime
		// - have more jagged edges than regular animations
		// Returns LT_ERROR for another error.
		// Returns LT_INVALIDPARAMS if nFrames is 0.
		// Returns LT_ALREADYEXISTS if an animation with the same name exists.
		// Note: the engine reserves BASE_LIGHTANIM_NAME (defined in basedefs_de.h).
		virtual LTRESULT CreateLightAnim(
			const char *pName,
			PreLightAnimFrameInfo *pFrames,
			uint32 nFrames,
			LTBOOL bShadowMap)=0;

		// Find objects.
		virtual LTRESULT FindObject(const char *pName, HPREOBJECT &hObject)=0;

		// Get an object's class name.
		virtual LTRESULT GetClassName(HPREOBJECT hObject, char *pClassName, uint32 maxCount)=0;

		// Get properties.  Even if the property can't be found, the GenericProp is initialized.
		virtual LTRESULT GetPropGeneric(HPREOBJECT hObject, const char *pName, GenericProp *pProp)=0;

		// Use the console parser.
		virtual LTRESULT Parse(ConParse *pParse)=0;

		// Print a message to the preprocessor 'console'.
		virtual LTRESULT CPrint(const char *pMsg, ...)=0;

		// WorldModel positions are moved to the center, so this should be used instead
		// of the Pos property.
		virtual LTRESULT GetWorldModelRuntimePos(HPREOBJECT hObj, LTVector &vPos)=0;


	protected:

        ILTMath *m_pMathLT;
	};


#endif // __ILTPRELIGHT_H__