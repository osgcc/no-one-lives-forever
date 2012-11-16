
#ifndef __LTANIMTRACKER_H__
#define __LTANIMTRACKER_H__


	#include "ltbasedefs.h"


	class LTAnimTracker;
	class AnimTimeRef;
	class AnimKeyFrame;
	class Model;
	class ModelAnim;
	class AnimInfo;
	class ModelInstance;


	typedef void (*StringKeyCallback)(LTAnimTracker *pTracker, AnimKeyFrame *pFrame);


	// All the info on where we are in the animation..
	class FrameLocator
	{
	public:
						
		void			Clear()
		{
			m_iAnim = 0;
			m_iFrame = 0;
			m_Time = 0;
		}

		uint16			m_iAnim;
		uint16			m_iFrame;
		uint32			m_Time;	// Milliseconds...
	};


	// References a specific time in an animation.
	class AnimTimeRef
	{
	public:

				AnimTimeRef()
				{
					m_iWeightSet = INVALID_MODEL_WEIGHTSET;
					Clear();
				}
		
		void	Init(Model *pModel, 
			uint32 iAnim1=0, uint32 iFrame1=0,
			uint32 iAnim2=0, uint32 iFrame2=0,
			float percent=0.0f)
		{
			m_pModel = pModel;
			
			m_Prev.m_iAnim = (uint16)iAnim1;
			m_Prev.m_iFrame = (uint16)iFrame1;
			m_Prev.m_Time = 0;

			m_Cur.m_iAnim = (uint16)iAnim2;
			m_Cur.m_iFrame = (uint16)iFrame2;
			m_Cur.m_Time = 0;

			m_Percent = percent;
		}

		void		Clear()
		{
			Init(LTNULL, 0, 0, 0, 0, 0.0f);
		}

		// Set it between the specified keyframes on the specified animation.
		LTBOOL		SetKeyframePosition(
			uint32 iAnim,
			uint32 iFrame1, 
			uint32 iFrame2, 
			float fPercent);
		
		LTBOOL		IsValid();
		ModelAnim*	GetAnim1();
		ModelAnim*	GetAnim2();


	public:

		Model			*m_pModel;
		
		// This tells exactly where we want the vertices setup.
		FrameLocator	m_Prev;
		FrameLocator	m_Cur;

		// Percentage between the two frames.  Must be between 0 and 1.
		float			m_Percent;

		// If multiple LTAnimTrackers are being used together, this tells how to blend each one.
		// This is ignored for the first weight set.
		uint32			m_iWeightSet;
	};


	// Animation tracker for model instances.
	// Note: Game code should NEVER touch the insides of this structure or call any of its functions.  
	// It should use the ILTModel functions to access these.
	class LTAnimTracker
	{
	public:

		// Tells if the frame locators are on valid frames.
		LTBOOL			IsValid();
		
		ModelAnim*		GetCurAnim();
		ModelAnim*		GetPrevAnim();

		AnimInfo*		GetCurAnimInfo();
		AnimInfo*		GetPrevAnimInfo();

		AnimKeyFrame*	GetCurFrame();
		AnimKeyFrame*	GetPrevFrame();

		void			SetupTimeRef(AnimTimeRef *pRef);
		
		LTBOOL			AllowInvalid();

		// Get/set its linked list info.
		LTAnimTracker*	GetNext()						{return (LTAnimTracker*)m_Link.m_pNext;}
		void			SetNext(LTAnimTracker *pNext)	{m_Link.m_pNext = (LTLink*)pNext;}

		ModelInstance*	GetModelInstance()			{return (ModelInstance*)m_Link.m_pData;}
		void			SetModelInstance(ModelInstance *pInst) {m_Link.m_pData = pInst;}
		
		Model*			GetModel()					{return m_TimeRef.m_pModel;}
		void			SetModel(Model *pModel)		{m_TimeRef.m_pModel = pModel;}


	public:

		LTLink			m_Link;

		StringKeyCallback	m_StringKeyCallback;	// Set this if you want to be notifies of string keys.
		void			*m_pUser1;		// Use this for whatever you want.
		unsigned long	m_CurKey;		// Stuff used to track where it is in the keyframes.

		unsigned short	m_Flags;			// Combination of AT_ flags above.
		unsigned short	m_InterpolationMS;	// How far we've interpolated between prev and cur
											// (when switching animations).  Set to NOT_INTERPOLATING
											// if not interpolating.

		AnimTimeRef		m_TimeRef;
	};


#endif  // __LTANIMTRACKER_H__
