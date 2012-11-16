//----------------------------------------------------------
//
// MODULE  : ltengineobjects.cpp
//
// PURPOSE : C++ LT engine objects
//
// CREATED : 9/17/97
//
//----------------------------------------------------------

#include "iltmessage.h"
#include "ltengineobjects.h"
#include <stdio.h>


// Used by some tools that need the class defs but not the server stuff.
#ifdef AUTO_DEFINE_CLASSES
	DEFINE_CLASSES()
#endif


// ------------------------------------------------------------------------ //
// BaseClass.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(BaseClass)
	ADD_STRINGPROP(Name, "noname")
	ADD_VECTORPROP(Pos)
	ADD_ROTATIONPROP(Rotation)
END_CLASS_DEFAULT_NOPARENT(BaseClass, BaseClass::_EngineMsgFn, BaseClass::_ObjectMsgFn)


void BaseClass::AddAggregate(LPAGGREGATE pAggregate)
{
	pAggregate->m_pNextAggregate = m_pFirstAggregate;
	m_pFirstAggregate = pAggregate;
}


LTBOOL BaseClass::RemoveAggregate(LPAGGREGATE pAggregate)
{
	if (!m_pFirstAggregate)
		return LTFALSE;
	
	// See if the aggregate is the first thing on the list...
	if(m_pFirstAggregate == pAggregate)
	{
		m_pFirstAggregate = m_pFirstAggregate->m_pNextAggregate;
		return LTTRUE;
	}
	else
	{
		// Start on the second item on the list...
		LPAGGREGATE pPrevAggregate = m_pFirstAggregate;
		LPAGGREGATE pCurAggregate = pPrevAggregate->m_pNextAggregate;;

		while (pCurAggregate)
		{
			if (pCurAggregate == pAggregate)
			{
				pPrevAggregate->m_pNextAggregate = pCurAggregate->m_pNextAggregate;
				return LTTRUE;
			}

			pPrevAggregate = pCurAggregate;
			pCurAggregate = pCurAggregate->m_pNextAggregate;
		}
	}

	return LTFALSE;
}


uint32 BaseClass::EngineMessageFn(uint32 messageID, void *pData, float fData)
{
	LPAGGREGATE pAggregate;
	ObjectCreateStruct *pStruct;
	GenericProp genProp;
	uint32 i, iSkin;
	char skinPropName[128];
	ConParse conParse;
	ILTServer *pServerLT;


	pServerLT = g_pLTServer;

	// Handle ReadProp.
	switch(messageID)
	{
		case MID_PRECREATE:
		{
			pStruct = (ObjectCreateStruct*)pData;
			
			// If they haven't already set the type, set it to whatever the constructor set.
			if(pStruct->m_ObjectType == OT_NORMAL)
			{
				pStruct->m_ObjectType = m_nType;
			}

			// Get the props.
			if( fData == PRECREATE_WORLDFILE || fData == PRECREATE_STRINGPROP )
			{
				if( pServerLT->GetPropGeneric( "Name", &genProp ) == LT_OK )
				{
					SAFE_STRCPY(pStruct->m_Name, genProp.m_String);
					pStruct->m_Name[MAX_CS_FILENAME_LEN] = '\0';
				}
				if( pServerLT->GetPropGeneric( "Pos", &genProp ) == LT_OK )
				{
					pStruct->m_Pos = genProp.m_Vec;
				}
				if( pServerLT->GetPropGeneric( "Rotation", &genProp ) == LT_OK )
				{
					pStruct->m_Rotation = genProp.m_Rotation;
				}
				if( pServerLT->GetPropGeneric( "Flags", &genProp ) == LT_OK )
				{
					pStruct->m_Flags = genProp.m_Long;
				}
				if( pServerLT->GetPropGeneric( "Visible", &genProp ) == LT_OK )
				{
					if( genProp.m_Bool )
						pStruct->m_Flags |= FLAG_VISIBLE;
					else
						pStruct->m_Flags &= ~FLAG_VISIBLE;
				}
				if( pServerLT->GetPropGeneric( "Shadow", &genProp ) == LT_OK )
				{
					if( genProp.m_Bool )
						pStruct->m_Flags |= FLAG_SHADOW;
					else
						pStruct->m_Flags &= ~FLAG_SHADOW;
				}
				if( pServerLT->GetPropGeneric( "RotateableSprite", &genProp ) == LT_OK )
				{
					if( genProp.m_Bool )
						pStruct->m_Flags |= FLAG_ROTATEABLESPRITE;
					else
						pStruct->m_Flags &= ~FLAG_ROTATEABLESPRITE;
				}
				if( pServerLT->GetPropGeneric( "Solid", &genProp ) == LT_OK )
				{
					if( genProp.m_Bool )
						pStruct->m_Flags |= FLAG_SOLID;
					else
						pStruct->m_Flags &= ~FLAG_SOLID;
				}
				if( pServerLT->GetPropGeneric( "Gravity", &genProp ) == LT_OK )
				{
					if( genProp.m_Bool )
						pStruct->m_Flags |= FLAG_GRAVITY;
					else
						pStruct->m_Flags &= ~FLAG_GRAVITY;
				}
				if( pServerLT->GetPropGeneric( "TouchNotify", &genProp ) == LT_OK )
				{
					if( genProp.m_Bool )
						pStruct->m_Flags |= FLAG_TOUCH_NOTIFY;
					else
						pStruct->m_Flags &= ~FLAG_TOUCH_NOTIFY;
				}
				
				if( pServerLT->GetPropGeneric( "Rayhit", &genProp ) == LT_OK )
				{
					if( genProp.m_Bool )
						pStruct->m_Flags |= FLAG_RAYHIT;
					else
						pStruct->m_Flags &= ~FLAG_RAYHIT;
				}
				
				if( pServerLT->GetPropGeneric( "Filename", &genProp ) == LT_OK )
				{
					SAFE_STRCPY(pStruct->m_Filename, genProp.m_String);
					pStruct->m_Filename[MAX_CS_FILENAME_LEN] = '\0';
				}
				
				if( pServerLT->GetPropGeneric( "Skin", &genProp ) == LT_OK )
				{
					iSkin = 0;
					conParse.Init(genProp.m_String);
					while(pServerLT->Common()->Parse(&conParse) == LT_OK)
					{
						if(conParse.m_nArgs > 0)
						{
							SAFE_STRCPY(pStruct->m_SkinNames[iSkin], conParse.m_Args[0]);
							iSkin++;
						}

						if(iSkin >= MAX_MODEL_TEXTURES)
							break;
					}
					pStruct->m_SkinName[MAX_CS_FILENAME_LEN] = '\0';
				}

				if(pServerLT->GetPropGeneric("Chromakey", &genProp) == LT_OK)
				{
					if(genProp.m_Bool)
						pStruct->m_Flags2 |= FLAG2_CHROMAKEY;
					else
						pStruct->m_Flags2 &= ~FLAG2_CHROMAKEY;
				}
				
				for(i=0; i < MAX_MODEL_TEXTURES; i++)
				{
					sprintf(skinPropName, "Skin%d", i);

					if( pServerLT->GetPropGeneric( skinPropName, &genProp ) == LT_OK )
					{
						SAFE_STRCPY(pStruct->m_SkinNames[i], genProp.m_String);
					}
				}

				break;
			}
		}
	}

	// Call the aggregates.
	pAggregate = m_pFirstAggregate;
	while(pAggregate)
	{
		pAggregate->EngineMessageFn(this, messageID, pData, fData);
		pAggregate = pAggregate->m_pNextAggregate;
	}

	// Default return is 1.
	return 1;
}


uint32 BaseClass::ObjectMessageFn(HOBJECT hSender, uint32 messageID, HMESSAGEREAD hRead)
{
	LPAGGREGATE pAggregate;

	// Call the aggregates.
	pAggregate = m_pFirstAggregate;
	while(pAggregate)
	{
		pAggregate->ObjectMessageFn(this, hSender, messageID, hRead);
		pAggregate = pAggregate->m_pNextAggregate;
	}

	return 1;
}


// ------------------------------------------------------------------------ //
// WorldSection.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(WorldSection)
	ADD_BOOLPROP(VisContainer, LTTRUE)
	ADD_BOOLPROP(Moveable, LTFALSE)
END_CLASS_DEFAULT_FLAGS(WorldSection, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// Terrain.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Terrain)
END_CLASS_DEFAULT_FLAGS(Terrain, BaseClass, NULL, NULL, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// Container.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Container)
	ADD_LONGINTPROP(Flags, FLAG_VISIBLE)
	ADD_LONGINTPROP(ContainerCode, 0)
END_CLASS_DEFAULT_FLAGS(Container, BaseClass, NULL, NULL, CF_ALWAYSLOAD | CF_HIDDEN)

uint32 Container::EngineMessageFn(uint32 messageID, void *pData, float fData)
{
	ObjectCreateStruct *pStruct;
	long code;

	if(messageID == MID_PRECREATE)
	{
		pStruct = (ObjectCreateStruct*)pData;
		pStruct->m_ObjectType = OT_CONTAINER;
		pStruct->m_Flags |= FLAG_CONTAINER;

		if( fData == PRECREATE_WORLDFILE )
		{
			code = 0;
			g_pLTServer->GetPropLongInt("ContainerCode", &code);
			pStruct->m_ContainerCode = (uint16)code;
			g_pLTServer->GetPropString("Name", pStruct->m_Filename, MAX_CS_FILENAME_LEN);
		}
	}

	// Pass the message down to the base class.
	return BaseClass::EngineMessageFn(messageID, pData, fData);
}



// ------------------------------------------------------------------------ //
// Sound.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Sound)
	ADD_STRINGPROP(Filename, "")
	ADD_LONGINTPROP(Priority, 0.0f)
	ADD_REALPROP_FLAG(OuterRadius, 100.0f, PF_RADIUS)
	ADD_REALPROP_FLAG(InnerRadius, 10.0f, PF_RADIUS)
	ADD_LONGINTPROP(Volume, 100.0f)
	ADD_BOOLPROP(Ambient, 1)
END_CLASS_DEFAULT_FLAGS(Sound, BaseClass, NULL, NULL, CF_ALWAYSLOAD | CF_HIDDEN)


uint32 Sound::EngineMessageFn(uint32 messageID, void *pData, float fData)
{
	ObjectCreateStruct *pStruct;
	GenericProp genProp;

	if(messageID == MID_PRECREATE)
	{
		pStruct = (ObjectCreateStruct*)pData;

		pStruct->m_ObjectType = OT_NORMAL;
		
		if( fData == PRECREATE_NORMAL )
		{
			m_fOuterRadius = 100.0f;
			m_fInnerRadius = 10.0f;
			
			m_nVolume = 100;
			
			m_nPriority = 0;
			m_bAmbient = LTTRUE;
		}
		else
		{
			if( g_pLTServer->GetPropGeneric( "Filename", &genProp ) == LT_OK )
			{
				SAFE_STRCPY(m_Filename, genProp.m_String);
			}
			else
				m_Filename[0] = '\0';

			if( g_pLTServer->GetPropGeneric("OuterRadius", &genProp ) == LT_OK )
				m_fOuterRadius = genProp.m_Float;
			else
				m_fOuterRadius = 100.0f;

			if( g_pLTServer->GetPropGeneric("InnerRadius", &genProp ) == LT_OK )
				m_fInnerRadius = genProp.m_Float;
			else
				m_fInnerRadius = 10.0f;
			
			if( g_pLTServer->GetPropGeneric("Volume", &genProp) == LT_OK )
				m_nVolume = (uint8)genProp.m_Long;
			else
				m_nVolume = 100;
			
			if( g_pLTServer->GetPropGeneric("Priority", &genProp) == LT_OK )
				m_nPriority = (unsigned char)genProp.m_Long;
			else
				m_nPriority = 0;
			
			if( g_pLTServer->GetPropGeneric("Ambient", &genProp) == LT_OK )
				m_bAmbient = genProp.m_Bool;
			else
				m_bAmbient = LTTRUE;
		}
	}
	else if(messageID == MID_INITIALUPDATE)
	{
		PlaySoundInfo playSoundInfo;
		
		PLAYSOUNDINFO_INIT( playSoundInfo );
		playSoundInfo.m_dwFlags = PLAYSOUND_LOOP;
		SAFE_STRCPY(playSoundInfo.m_szSoundName, m_Filename);
		playSoundInfo.m_nPriority = m_nPriority;
		playSoundInfo.m_fOuterRadius = m_fOuterRadius;
		playSoundInfo.m_fInnerRadius = m_fInnerRadius;
		if( m_nVolume < 100 )
		{
			playSoundInfo.m_nVolume = m_nVolume;
			playSoundInfo.m_dwFlags |= PLAYSOUND_CTRL_VOL;
		}
		
		g_pLTServer->GetObjectPos( m_hObject, &playSoundInfo.m_vPosition );
		if( m_bAmbient )
		{
			playSoundInfo.m_dwFlags |= PLAYSOUND_AMBIENT;
		}
		else
		{
			playSoundInfo.m_dwFlags |= PLAYSOUND_3D;
		}

		g_pLTServer->PlaySound( &playSoundInfo );

		// sounds just remove themselves right away.  Since they don't do
		// anything right now, they just take up memory.
		g_pLTServer->RemoveObject(m_hObject);
	}

	// Pass the message down to the base class.
	return BaseClass::EngineMessageFn(messageID, pData, fData);
}



// ------------------------------------------------------------------------ //
// InsideDef.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(InsideDef)
END_CLASS_DEFAULT_FLAGS(InsideDef, BaseClass, NULL, NULL, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// OutsideDef.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(OutsideDef)
END_CLASS_DEFAULT_FLAGS(OutsideDef, BaseClass, NULL, NULL, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// FastApproxArea.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(FastApproxArea)
END_CLASS_DEFAULT_FLAGS(FastApproxArea, BaseClass, NULL, NULL, CF_NORUNTIME )



// ------------------------------------------------------------------------ //
// Light.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Light)
	ADD_BOOLPROP(ClipLight, 1)
	ADD_BOOLPROP(LightObjects, 1)
	ADD_BOOLPROP(FastLightObjects, 1)
	ADD_REALPROP_FLAG(LightRadius, 300.0f, PF_RADIUS)
	ADD_COLORPROP(LightColor, 255.0f, 255.0f, 255.0f)
	ADD_COLORPROP(OuterColor, 0.0f, 0.0f, 0.0f)
	ADD_REALPROP(BrightScale, 1.0f)
	ADD_REALPROP(Time, 0.0f)
END_CLASS_DEFAULT_FLAGS(Light, BaseClass, NULL, NULL, CF_NORUNTIME)


// ------------------------------------------------------------------------ //
// ObjectLight.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(ObjectLight)
	ADD_REALPROP_FLAG(LightRadius, 300.0f, PF_RADIUS)
	ADD_BOOLPROP(FastLightObjects, 1)
	ADD_COLORPROP(LightColor, 255.0f, 255.0f, 255.0f)
	ADD_COLORPROP(OuterColor, 0.0f, 0.0f, 0.0f)
	ADD_REALPROP(BrightScale, 1.0f)
END_CLASS_DEFAULT_FLAGS(ObjectLight, BaseClass, NULL, NULL, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// DirLight.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(DirLight)
	ADD_BOOLPROP(LightObjects, 1)
	ADD_BOOLPROP(ClipLight, 1)
	ADD_REALPROP_FLAG(LightRadius, 300.0f, PF_FOVRADIUS)
	ADD_BOOLPROP(FastLightObjects, 1)
	ADD_COLORPROP(InnerColor, 255.0f, 255.0f, 255.0f)
	ADD_COLORPROP(OuterColor, 0.0f, 0.0f, 0.0f)
	ADD_REALPROP_FLAG(FOV, 90.0f, PF_FIELDOFVIEW)
	ADD_REALPROP(BrightScale, 1.0f)
	ADD_REALPROP(Time, 0.0f)
END_CLASS_DEFAULT_FLAGS(DirLight, BaseClass, NULL, NULL, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// StaticSunLight.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(StaticSunLight)
	ADD_COLORPROP(InnerColor, 255.0f, 255.0f, 255.0f)
	ADD_COLORPROP(OuterColor, 0.0f, 0.0f, 0.0f)
	ADD_REALPROP(BrightScale, 1.0f)
	ADD_REALPROP(Bias, 1.0f)
END_CLASS_DEFAULT_FLAGS(StaticSunLight, BaseClass, NULL, NULL, CF_ALWAYSLOAD)

uint32 StaticSunLight::EngineMessageFn(uint32 messageID, void *pData, float fData)
{
	switch(messageID)
	{
		case MID_PRECREATE:
		{
			ObjectCreateStruct *pStruct;
			pStruct = (ObjectCreateStruct*)pData;

			pStruct->m_ObjectType = OT_NORMAL;

			if( fData == PRECREATE_WORLDFILE )
			{
				g_pLTServer->GetPropVector("InnerColor", &m_InnerColor);
				g_pLTServer->GetPropVector("InnerColor", &m_OuterColor);
				g_pLTServer->GetPropReal("BrightScale", &m_BrightScale);
			}
			else
			{
				m_InnerColor.Init(255.0f, 255.0f, 255.0f);
				m_OuterColor.Init(0.0f, 0.0f, 0.0f);
				m_BrightScale = 1.0f;
			}
			break;
		}

		case MID_INITIALUPDATE:
		{
			g_pLTServer->SetGlobalLightObject(m_hObject);
			break;
		}
	}

	return BaseClass::EngineMessageFn(messageID, pData, fData);
}


// ------------------------------------------------------------------------ //
// Brush.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Brush)
	ADD_BOOLPROP(Solid, 1)
	ADD_BOOLPROP(Nonexistant, 0)
	ADD_BOOLPROP(Invisible, 0)
	ADD_BOOLPROP(Translucent, 0)
	ADD_BOOLPROP(SkyPortal, 0)
	ADD_BOOLPROP(FullyBright, 0)
	ADD_BOOLPROP(FlatShade, 0)
	ADD_BOOLPROP(GouraudShade, 1)
	ADD_BOOLPROP(LightMap, 1)
	ADD_BOOLPROP(Subdivide, 1)
	ADD_BOOLPROP(HullMaker, 0)		
	ADD_BOOLPROP(AlwaysLightMap, 0)
	ADD_BOOLPROP(DirectionalLight, 0)
	ADD_BOOLPROP(Portal, 0)
	ADD_BOOLPROP(NoSnap, 0)
	ADD_BOOLPROP(SkyPan, 0)
	ADD_BOOLPROP(Additive, 0)
	ADD_BOOLPROP(TerrainOccluder, 0)
	ADD_BOOLPROP(TimeOfDay, 0)
	ADD_BOOLPROP(VisBlocker, 0)
	ADD_BOOLPROP(NotAStep, 0)

	ADD_LONGINTPROP(DetailLevel, 0)
	ADD_STRINGPROP(Effect, "")
	ADD_STRINGPROP(EffectParam, "")
	ADD_REALPROP(FrictionCoefficient, 1)
END_CLASS_DEFAULT_FLAGS(Brush, BaseClass, NULL, NULL, CF_ALWAYSLOAD)



// ------------------------------------------------------------------------ //
// DemoSkyWorldModel.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(DemoSkyWorldModel)
	ADD_VECTORPROP_VAL_FLAG(SkyDims, 0.0f, 0.0f, 0.0f, PF_DIMS)
	ADD_LONGINTPROP(Flags, 1)
	ADD_LONGINTPROP(Index, 0)
	ADD_REALPROP(InnerPercentX, 0.1f)
	ADD_REALPROP(InnerPercentY, 0.1f)
	ADD_REALPROP(InnerPercentZ, 0.1f)
END_CLASS_DEFAULT_FLAGS(DemoSkyWorldModel, BaseClass, NULL, NULL, CF_ALWAYSLOAD)


uint32 DemoSkyWorldModel::EngineMessageFn(uint32 messageID, void *pData, float fData)
{
	SkyDef def;
	LTVector pos, temp;
	ObjectCreateStruct *pStruct;


	switch(messageID)
	{
		case MID_PRECREATE:
		{
			pStruct = (ObjectCreateStruct*)pData;

			pStruct->m_ObjectType = OT_WORLDMODEL;

			if( fData == PRECREATE_WORLDFILE )
			{
				g_pLTServer->GetPropVector("SkyDims", &m_SkyDims);
				g_pLTServer->GetPropString("Name", pStruct->m_Filename, MAX_CS_FILENAME_LEN);
				g_pLTServer->GetPropReal("InnerPercentX", &m_InnerPercentX);
				g_pLTServer->GetPropReal("InnerPercentY", &m_InnerPercentY);
				g_pLTServer->GetPropReal("InnerPercentZ", &m_InnerPercentZ);
				g_pLTServer->GetPropLongInt("Index", &m_Index);
			}
			else
			{
				m_SkyDims.Init();
				m_InnerPercentX = 0.1f;
				m_InnerPercentY = 0.1f;
				m_InnerPercentZ = 0.1f;
				m_Index = 0;
			}
			break;
		}

		case MID_INITIALUPDATE:
		{
			// Set the sky box?
			if(m_SkyDims.x != 0.0f && 
				m_SkyDims.y != 0.0f && 
				m_SkyDims.z != 0.0f)
			{
				g_pLTServer->GetObjectPos(m_hObject, &pos);
				def.m_Min = pos - m_SkyDims;
				def.m_Max = pos + m_SkyDims;

				temp.x = m_SkyDims.x * m_InnerPercentX;
				temp.y = m_SkyDims.y * m_InnerPercentY;
				temp.z = m_SkyDims.z * m_InnerPercentZ;

				def.m_ViewMin = pos - temp;
				def.m_ViewMax = pos + temp;

				g_pLTServer->SetSkyDef(&def);
			}

			uint32 dwFlags = g_pLTServer->GetObjectFlags(m_hObject);
			g_pLTServer->SetObjectFlags(m_hObject, dwFlags | FLAG_FORCEOPTIMIZEOBJECT);

			uint32 dwFlags2;
			g_pLTServer->Common()->GetObjectFlags(m_hObject, OFT_Flags2, dwFlags2);
			g_pLTServer->Common()->SetObjectFlags(m_hObject, OFT_Flags2, dwFlags2 | FLAG2_SKYOBJECT);
			
			g_pLTServer->AddObjectToSky(m_hObject, m_Index);
			break;
		}
	}

	return BaseClass::EngineMessageFn(messageID, pData, fData);
}




// ------------------------------------------------------------------------ //
// SkyPointer.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(SkyPointer)
	ADD_STRINGPROP(SkyObjectName, "")
	ADD_VECTORPROP_VAL_FLAG(SkyDims, 0.0f, 0.0f, 0.0f, PF_DIMS)
	ADD_LONGINTPROP(Flags, 1)
	ADD_LONGINTPROP(Index, 0)
	ADD_REALPROP(InnerPercentX, 0.1f)
	ADD_REALPROP(InnerPercentY, 0.1f)
	ADD_REALPROP(InnerPercentZ, 0.1f)
END_CLASS_DEFAULT_FLAGS(SkyPointer, BaseClass, NULL, NULL, CF_ALWAYSLOAD)


uint32 SkyPointer::EngineMessageFn(
	uint32 messageID, void *pData, float fData)
{
	SkyDef def;
	LTVector pos, temp;
	ObjectCreateStruct *pStruct;
	HOBJECT hObject;


	switch(messageID)
	{
		case MID_PRECREATE:
		{
			pStruct = (ObjectCreateStruct*)pData;

			pStruct->m_ObjectType = OT_NORMAL;

			if( fData == PRECREATE_WORLDFILE )
			{
				g_pLTServer->GetPropVector("SkyDims", &m_SkyDims);
				g_pLTServer->GetPropString("Name", pStruct->m_Filename, MAX_CS_FILENAME_LEN);
				g_pLTServer->GetPropString("SkyObjectName", m_ObjectName, sizeof(m_ObjectName)-1);
				g_pLTServer->GetPropReal("InnerPercentX", &m_InnerPercentX);
				g_pLTServer->GetPropReal("InnerPercentY", &m_InnerPercentY);
				g_pLTServer->GetPropReal("InnerPercentZ", &m_InnerPercentZ);
				g_pLTServer->GetPropLongInt("Index", &m_Index);
			}
			else
			{
				m_ObjectName[0] = 0;
				m_SkyDims.Init();
				m_InnerPercentX = 0.1f;
				m_InnerPercentY = 0.1f;
				m_InnerPercentZ = 0.1f;
				m_Index = 0;
			}
			break;
		}

		case MID_INITIALUPDATE:
		{
			// Set the sky box?
			if(m_SkyDims.x != 0.0f && m_SkyDims.y != 0.0f && m_SkyDims.z != 0.0f)
			{
				g_pLTServer->GetObjectPos(m_hObject, &pos);
				def.m_Min = pos - m_SkyDims;
				def.m_Max = pos + m_SkyDims;

				temp.x = m_SkyDims.x * m_InnerPercentX;
				temp.y = m_SkyDims.y * m_InnerPercentY;
				temp.z = m_SkyDims.z * m_InnerPercentZ;

				def.m_ViewMin = pos - temp;
				def.m_ViewMax = pos + temp;

				g_pLTServer->SetSkyDef(&def);
			}

			g_pLTServer->SetNextUpdate(m_hObject, 0.001f);
			break;
		}

		case MID_UPDATE:
		{
			// Add the first object to the sky.

			// Kai Martin - 10/26/99
			// replaced linked list of objects in favor of new
			// static array of objects.  I left the old code
			// commented out in case I screwed something up.
			ObjArray <HOBJECT, 1> objArray;

			g_pLTServer->FindNamedObjects(m_ObjectName, objArray);

			if(objArray.NumObjects())
			{
				hObject = objArray.GetObject(0);
				g_pLTServer->AddObjectToSky(hObject, m_Index);

				g_pLTServer->SetObjectFlags(hObject, g_pLTServer->GetObjectFlags(hObject) | FLAG_FORCEOPTIMIZEOBJECT);

				uint32 dwFlags2;
				g_pLTServer->Common()->GetObjectFlags(hObject, OFT_Flags2, dwFlags2);
				g_pLTServer->Common()->SetObjectFlags(hObject, OFT_Flags2, dwFlags2 | FLAG2_SKYOBJECT);
			}
			
			// I did my part, remove me!
			g_pLTServer->RemoveObject(m_hObject);
			break;
		}
	}

	return BaseClass::EngineMessageFn(messageID, pData, fData);
}




// ------------------------------------------------------------------------ //
// RaySelecter.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(RaySelecter)
END_CLASS_DEFAULT_FLAGS(RaySelecter, BaseClass, NULL, NULL, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// GenericObject.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(GenericObject)
	ADD_REALPROP(ObjectType, 0)
	ADD_REALPROP(LightRadius, 300)
	ADD_STRINGPROP(Filename, "")
	ADD_STRINGPROP(Skin, "")
	ADD_STRINGPROP(Skin2, "")
	ADD_REALPROP(R, 255)
	ADD_REALPROP(G, 255)
	ADD_REALPROP(B, 255)
	ADD_REALPROP(A, 255)
END_CLASS_DEFAULT_FLAGS(GenericObject, BaseClass, NULL, NULL, 0)


uint32 GenericObject::EngineMessageFn(
	uint32 messageID, void *pData, float fData)
{
	ObjectCreateStruct *pStruct;
	GenericProp genProp;
	ILTServer *pServerLT;


	pServerLT = g_pLTServer;
	switch(messageID)
	{
		case MID_PRECREATE:
		{
			pStruct = (ObjectCreateStruct*)pData;

			if(pServerLT->GetPropGeneric("ObjectType", &genProp) == LT_OK)
				pStruct->m_ObjectType = (uint16)genProp.m_Long;

			if(pServerLT->GetPropGeneric("LightRadius", &genProp) == LT_OK)
				m_LightRadius = genProp.m_Float;

			if(pServerLT->GetPropGeneric("R", &genProp) == LT_OK)
				m_ColorR = genProp.m_Float / 255.0f;
			if(pServerLT->GetPropGeneric("G", &genProp) == LT_OK)
				m_ColorG = genProp.m_Float / 255.0f;
			if(pServerLT->GetPropGeneric("B", &genProp) == LT_OK)
				m_ColorB = genProp.m_Float / 255.0f;
			if(pServerLT->GetPropGeneric("A", &genProp) == LT_OK)
				m_ColorA = genProp.m_Float / 255.0f;
		}
		break;

		case MID_INITIALUPDATE:
		{
			pServerLT->SetLightRadius(m_hObject, m_LightRadius);
			pServerLT->SetObjectColor(m_hObject,
				m_ColorR, m_ColorG, 
				m_ColorB, m_ColorA);
		}
		break;
	}

	return BaseClass::EngineMessageFn(messageID, pData, fData);
}


// ------------------------------------------------------------------------ //
// Zone.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Zone)
END_CLASS_DEFAULT_FLAGS(Zone, BaseClass, NULL, NULL, CF_NORUNTIME)



	
