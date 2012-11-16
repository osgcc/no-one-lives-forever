
#ifndef __ILTCUSTOMDRAW_H__
#define __ILTCUSTOMDRAW_H__


	// Blend modes.
	#define LTBLEND_ZERO		1
	#define LTBLEND_ONE         2
	#define LTBLEND_SRCCOLOR    3
	#define LTBLEND_INVSRCCOLOR 4
	#define LTBLEND_SRCALPHA    5
	#define LTBLEND_INVSRCALPHA 6

	// Texture addressing modes
	#define LTTEXADDR_WRAP		1
	#define LTTEXADDR_CLAMP		2

	// Blending operations for texturing
	#define LTOP_SELECTTEXTURE	1
	#define LTOP_SELECTDIFFUSE	2
	#define LTOP_MODULATE		3
	#define LTOP_ADD			4
	#define LTOP_ADDSIGNED		5

	typedef enum
	{
										// Defaults:
		LTRSTATE_ALPHABLENDENABLE=0,	// FALSE
		LTRSTATE_ZREADENABLE,			// TRUE
		LTRSTATE_ZWRITEENABLE,			// TRUE
		LTRSTATE_SRCBLEND,				// LTBLEND_SRCALPHA
		LTRSTATE_DESTBLEND,				// LTBLEND_INVSRCALPHA
		LTRSTATE_TEXADDR,				// LTTEXADDR_WRAP
		LTRSTATE_COLOROP,				// LTOP_MODULATE
		LTRSTATE_ALPHAOP,				// LTOP_SELECTTEXTURE
		NUM_LTRSTATES
	} LTRState;	


	class LTVertexColor
	{
	public:
		void	Init(uint8 in_r, uint8 in_g, uint8 in_b, uint8 in_a)
		{
			r = in_r;
			g = in_g;
			b = in_b;
			a = in_a;
		}
		
		// Blue, green, red, alpha.
		uint8	b, g, r, a;
	};

	
	class LTVertex
	{
	public:
		
		LTVector		m_Vec;
		float			m_RHW;		// Don't touch.
		LTVertexColor	m_Color;
		LTVertexColor	m_Specular;	// Don't touch.
		float			m_TU, m_TV;
	};


	class ILTCustomDraw
	{
	public:
		
		// Transforms, clips, and draws the specified primitive.
		virtual LTRESULT	DrawPrimitive(LTVertex *pVerts, uint32 nVerts, uint32 flags)=0;

		// Get/set states.  States are from the LTRSTATE_ enums.
		virtual LTRESULT	SetState(LTRState state, uint32 val)=0;
		virtual LTRESULT	GetState(LTRState state, uint32 &val)=0;

		// Set the current texture  (Use pTexture=LTNULL to disable texturing)
		virtual LTRESULT	SetTexture(const char *pTexture)=0;

		// Get the size of a texel for the currently selected texture
		virtual LTRESULT	GetTexelSize(float &fSizeU, float &fSizeV)=0;
	};


#endif // __ILTCUSTOMDRAW_H__
