# Microsoft Developer Studio Project File - Name="ClientShellDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ClientShellDLL - Win32 Final Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientShellDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientShellDLL.mak" CFG="ClientShellDLL - Win32 Final Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientShellDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClientShellDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClientShellDLL - Win32 Final Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClientShellDLL - Win32 Final Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Source/ClientShellDLL", FFAAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\shared" /I "..\..\lt2\sdk\inc" /I "..\..\lt2\lithshared\incs" /I "..\ClientShellDLL" /D "NDEBUG" /D "_CLIENTBUILD" /D "WIN32" /D "_WINDOWS" /D "_NOLFBUILD" /D "NO_PRAGMA_LIBS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"LIBCMTD" /out:"release\CShell.dll"
# SUBTRACT LINK32 /pdb:none /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy release\cshell.dll $(NOLF_BUILD_DIR)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\shared" /I "..\..\lt2\sdk\inc" /I "..\..\lt2\lithshared\incs" /I "..\ClientShellDLL" /D "_DEBUG" /D "_CLIENTBUILD" /D "WIN32" /D "_WINDOWS" /D "NO_PRAGMA_LIBS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"debug\CShell.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy debug\cshell.dll $(NOLF_BUILD_DIR)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ClientShellDLL___Win32_Final_Release"
# PROP BASE Intermediate_Dir "ClientShellDLL___Win32_Final_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Final_Release"
# PROP Intermediate_Dir "Final_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\shared" /I "..\..\lt2\sdk\inc" /I "..\..\lt2\lithshared\incs" /I "..\ClientShellDLL" /D "NDEBUG" /D "_CLIENTBUILD" /D "WIN32" /D "_WINDOWS" /D "_NOLFBUILD" /D "NO_PRAGMA_LIBS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\shared" /I "..\..\lt2\sdk\inc" /I "..\..\lt2\lithshared\incs" /I "..\ClientShellDLL" /D "_REZFILE" /D "_FINAL" /D "NDEBUG" /D "_CLIENTBUILD" /D "WIN32" /D "_WINDOWS" /D "_NOLFBUILD" /D "NO_PRAGMA_LIBS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"LIBCMTD" /out:"release\CShell.dll"
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"LIBCMTD" /out:"Final_Release\CShell.dll"
# SUBTRACT LINK32 /pdb:none /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Final_Release\cshell.dll $(NOLF_BUILD_DIR)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ClientShellDLL___Win32_Final_Debug"
# PROP BASE Intermediate_Dir "ClientShellDLL___Win32_Final_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Final_Debug"
# PROP Intermediate_Dir "Final_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\shared" /I "..\..\lt2\sdk\inc" /I "..\..\lt2\lithshared\incs" /I "..\ClientShellDLL" /D "_DEBUG" /D "_CLIENTBUILD" /D "WIN32" /D "_WINDOWS" /D "NO_PRAGMA_LIBS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\shared" /I "..\..\lt2\sdk\inc" /I "..\..\lt2\lithshared\incs" /I "..\ClientShellDLL" /D "_REZFILE" /D "_FINAL" /D "_DEBUG" /D "_CLIENTBUILD" /D "WIN32" /D "_WINDOWS" /D "NO_PRAGMA_LIBS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"debug\CShell.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Final_Debug\CShell.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Final_Debug\cshell.dll $(NOLF_BUILD_DIR)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ClientShellDLL - Win32 Release"
# Name "ClientShellDLL - Win32 Debug"
# Name "ClientShellDLL - Win32 Final Release"
# Name "ClientShellDLL - Win32 Final Debug"
# Begin Group "Source"

# PROP Default_Filter "*.cpp"
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseSelectionFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CycleCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderAdvDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderAudio.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderAwards.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderBriefing.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderControls.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderCrosshair.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderCustomControls.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderCustomLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDifficulty.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderEffects.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderEscape.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderFavoriteLevels.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderGadgets.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderGallery.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderGame.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderGear.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderHost.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderHostLevels.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderHostOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderIntel.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderInventory.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderJoin.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderJoinLAN.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderJoystick.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderMain.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderMission.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderMods.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderMulti.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderMultiBriefing.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderMultiSummary.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderNew.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderObjectives.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderPerformance.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderSave.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderSingle.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderStats.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderSummary.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderViewInventory.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderWeaponControls.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderWeapons.cpp
# End Source File
# Begin Source File

SOURCE=.\GameSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceResMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceSurfMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\JoystickAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\LayoutMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadingScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\LTDecisionWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\LTDialogueWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\LTMaskedWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\LTMenuWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\LTMultiWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\LTTextWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\LtWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\MissionData.cpp
# End Source File
# Begin Source File

SOURCE=.\MouseMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupText.cpp
# End Source File
# Begin Source File

SOURCE=.\SliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticTextCtrl.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\Shared\Animator.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\AssertMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\AttachButeMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\BareList.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseLineSystemFX.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseParticleSystemFX.cpp
# End Source File
# Begin Source File

SOURCE=.\BasePolyDrawFX.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseScaleFX.cpp
# End Source File
# Begin Source File

SOURCE=.\BeamFX.cpp
# End Source File
# Begin Source File

SOURCE=.\BodyFX.cpp
# End Source File
# Begin Source File

SOURCE=.\BulletTrailFX.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraOffsetMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\CharacterFX.cpp
# End Source File
# Begin Source File

SOURCE=.\client_physics.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientButeMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientInfoMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSoundMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientUtilities.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientWeaponUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\CMoveMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\CommonUtilities.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\CRC32.cpp
# End Source File
# Begin Source File

SOURCE=.\Credits.cpp
# End Source File
# Begin Source File

SOURCE=.\DamageFXMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\DamageTypes.cpp
# End Source File
# Begin Source File

SOURCE=.\DeathFX.cpp
# End Source File
# Begin Source File

SOURCE=.\DebrisFX.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\DebrisMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\DebugNew.cpp

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DynamicLightFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ExplosionFX.cpp
# End Source File
# Begin Source File

SOURCE=.\FireFX.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashLight.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\FXButeMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\FXStructs.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\GameButeMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\GameClientShell.cpp
# End Source File
# Begin Source File

SOURCE=.\GibFX.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalClientMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\GlobalMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\HeadBobMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\IntelItemMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceMeter.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\IpMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyFixes.cpp
# End Source File
# Begin Source File

SOURCE=.\LaserBeam.cpp
# End Source File
# Begin Source File

SOURCE=.\LaserTriggerFX.cpp
# End Source File
# Begin Source File

SOURCE=.\LeashFX.cpp
# End Source File
# Begin Source File

SOURCE=.\LensFlareFX.cpp
# End Source File
# Begin Source File

SOURCE=.\LightFX.cpp
# End Source File
# Begin Source File

SOURCE=.\LightningFX.cpp
# End Source File
# Begin Source File

SOURCE=.\LightScaleMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\LineSystemFX.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkSFX.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageBoxCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MineFX.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\MissionMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MissionText.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\ModelButeMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiplayerMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\Music.cpp
# End Source File
# Begin Source File

SOURCE=.\MuzzleFlashFX.cpp
# End Source File
# Begin Source File

SOURCE=.\MuzzleFlashParticleFX.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\NetDefs.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeController.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeLinesFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjEditMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjSpriteFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleExplosionFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleShowerFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleSystemFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleTrailFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleTrailSegmentFX.cpp
# End Source File
# Begin Source File

SOURCE=.\PickupItemFX.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerSoundFX.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerStats.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\PlayerSummary.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerVehicleFX.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyDebrisFX.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyGridFX.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyLineFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectileFX.cpp
# End Source File
# Begin Source File

SOURCE=.\PVFXMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\RandomSparksFX.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenTintMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchLightFX.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\ServerOptionMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\SFXMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\SharedFXStructs.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\SharedMission.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellCasingFX.cpp
# End Source File
# Begin Source File

SOURCE=.\SmokeFX.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\SoundFilterMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundFX.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\SoundMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Sparam.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialFXList.cpp
# End Source File
# Begin Source File

SOURCE=.\sprinklesfx.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\Stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SteamFX.cpp
# End Source File
# Begin Source File

SOURCE=.\Subtitle.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\SurfaceFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\SurfaceMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\TeamMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\TemplateList.cpp
# End Source File
# Begin Source File

SOURCE=.\TracerFX.cpp
# End Source File
# Begin Source File

SOURCE=.\VehicleMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\VersionMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoFX.cpp
# End Source File
# Begin Source File

SOURCE=.\VKDefs.cpp
# End Source File
# Begin Source File

SOURCE=.\WeaponChooser.cpp
# End Source File
# Begin Source File

SOURCE=.\WeaponFX.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\WeaponMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\WeaponModel.cpp
# End Source File
# Begin Source File

SOURCE=.\WeatherFX.cpp
# End Source File
# Begin Source File

SOURCE=.\WinUtil.cpp
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\Shared\AssertMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\AttachButeMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\BankedList.h
# End Source File
# Begin Source File

SOURCE=..\Shared\BankedList_impl.h
# End Source File
# Begin Source File

SOURCE=..\Shared\BareList.h
# End Source File
# Begin Source File

SOURCE=.\BaseFolder.h
# End Source File
# Begin Source File

SOURCE=.\BaseLineSystemFX.h
# End Source File
# Begin Source File

SOURCE=.\BaseMenu.h
# End Source File
# Begin Source File

SOURCE=.\BaseParticleSystemFX.h
# End Source File
# Begin Source File

SOURCE=.\BasePolyDrawFX.h
# End Source File
# Begin Source File

SOURCE=.\BaseScaleFX.h
# End Source File
# Begin Source File

SOURCE=.\BaseSelectionFolder.h
# End Source File
# Begin Source File

SOURCE=.\BeamFX.h
# End Source File
# Begin Source File

SOURCE=.\BitmapCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BodyFX.h
# End Source File
# Begin Source File

SOURCE=.\BulletTrailFX.h
# End Source File
# Begin Source File

SOURCE=.\CameraFX.h
# End Source File
# Begin Source File

SOURCE=.\CameraOffsetMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\CharacterAlignment.h
# End Source File
# Begin Source File

SOURCE=.\CharacterFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\CheatDefs.h
# End Source File
# Begin Source File

SOURCE=.\client_physics.h
# End Source File
# Begin Source File

SOURCE=.\ClientButeMgr.h
# End Source File
# Begin Source File

SOURCE=.\ClientInfoMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\ClientServerShared.h
# End Source File
# Begin Source File

SOURCE=.\ClientSoundMgr.h
# End Source File
# Begin Source File

SOURCE=.\ClientUtilities.h
# End Source File
# Begin Source File

SOURCE=.\ClientWeaponUtils.h
# End Source File
# Begin Source File

SOURCE=.\CMoveMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\CommandIDs.h
# End Source File
# Begin Source File

SOURCE=..\Shared\CommonUtilities.h
# End Source File
# Begin Source File

SOURCE=..\Shared\ContainerCodes.h
# End Source File
# Begin Source File

SOURCE=..\Shared\CRC32.h
# End Source File
# Begin Source File

SOURCE=.\Credits.h
# End Source File
# Begin Source File

SOURCE=..\Shared\CSDefs.h
# End Source File
# Begin Source File

SOURCE=.\CycleCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DamageFXMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\DamageTypes.h
# End Source File
# Begin Source File

SOURCE=.\DeathFX.h
# End Source File
# Begin Source File

SOURCE=.\DebrisFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\DebrisMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\DebrisMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\DebrisTypes.h
# End Source File
# Begin Source File

SOURCE=..\Shared\DebugNew_impl.h
# End Source File
# Begin Source File

SOURCE=.\DynamicLightFX.h
# End Source File
# Begin Source File

SOURCE=.\ExplosionFX.h
# End Source File
# Begin Source File

SOURCE=.\FastList.h
# End Source File
# Begin Source File

SOURCE=.\FireFX.h
# End Source File
# Begin Source File

SOURCE=.\FlashLight.h
# End Source File
# Begin Source File

SOURCE=.\FolderAdvDisplay.h
# End Source File
# Begin Source File

SOURCE=.\FolderAudio.h
# End Source File
# Begin Source File

SOURCE=.\FolderAwards.h
# End Source File
# Begin Source File

SOURCE=.\FolderBriefing.h
# End Source File
# Begin Source File

SOURCE=.\FolderCommands.h
# End Source File
# Begin Source File

SOURCE=.\FolderControls.h
# End Source File
# Begin Source File

SOURCE=.\FolderCrosshair.h
# End Source File
# Begin Source File

SOURCE=.\FolderCustomControls.h
# End Source File
# Begin Source File

SOURCE=.\FolderCustomLevel.h
# End Source File
# Begin Source File

SOURCE=.\FolderDifficulty.h
# End Source File
# Begin Source File

SOURCE=.\FolderDisplay.h
# End Source File
# Begin Source File

SOURCE=.\FolderEffects.h
# End Source File
# Begin Source File

SOURCE=.\FolderEscape.h
# End Source File
# Begin Source File

SOURCE=.\FolderFavoriteLevels.h
# End Source File
# Begin Source File

SOURCE=.\FolderGadgets.h
# End Source File
# Begin Source File

SOURCE=.\FolderGallery.h
# End Source File
# Begin Source File

SOURCE=.\FolderGame.h
# End Source File
# Begin Source File

SOURCE=.\FolderGear.h
# End Source File
# Begin Source File

SOURCE=.\FolderHost.h
# End Source File
# Begin Source File

SOURCE=.\FolderHostLevels.h
# End Source File
# Begin Source File

SOURCE=.\FolderHostOptions.h
# End Source File
# Begin Source File

SOURCE=.\FolderIntel.h
# End Source File
# Begin Source File

SOURCE=.\FolderInventory.h
# End Source File
# Begin Source File

SOURCE=.\FolderJoin.h
# End Source File
# Begin Source File

SOURCE=.\FolderJoinLAN.h
# End Source File
# Begin Source File

SOURCE=.\FolderJoystick.h
# End Source File
# Begin Source File

SOURCE=.\FolderKeyboard.h
# End Source File
# Begin Source File

SOURCE=.\FolderLoad.h
# End Source File
# Begin Source File

SOURCE=.\FolderMain.h
# End Source File
# Begin Source File

SOURCE=.\FolderMgr.h
# End Source File
# Begin Source File

SOURCE=.\FolderMission.h
# End Source File
# Begin Source File

SOURCE=.\FolderMods.h
# End Source File
# Begin Source File

SOURCE=.\FolderMouse.h
# End Source File
# Begin Source File

SOURCE=.\FolderMulti.h
# End Source File
# Begin Source File

SOURCE=.\FolderMultiBriefing.h
# End Source File
# Begin Source File

SOURCE=.\FolderMultiSummary.h
# End Source File
# Begin Source File

SOURCE=.\FolderNew.h
# End Source File
# Begin Source File

SOURCE=.\FolderObjectives.h
# End Source File
# Begin Source File

SOURCE=.\FolderOptions.h
# End Source File
# Begin Source File

SOURCE=.\FolderPerformance.h
# End Source File
# Begin Source File

SOURCE=.\FolderPlayer.h
# End Source File
# Begin Source File

SOURCE=.\FolderSave.h
# End Source File
# Begin Source File

SOURCE=.\FolderSingle.h
# End Source File
# Begin Source File

SOURCE=.\FolderStats.h
# End Source File
# Begin Source File

SOURCE=.\FolderSummary.h
# End Source File
# Begin Source File

SOURCE=.\FolderSupplies.h
# End Source File
# Begin Source File

SOURCE=.\FolderTexture.h
# End Source File
# Begin Source File

SOURCE=.\FolderViewInventory.h
# End Source File
# Begin Source File

SOURCE=.\FolderWeaponControls.h
# End Source File
# Begin Source File

SOURCE=.\FolderWeapons.h
# End Source File
# Begin Source File

SOURCE=..\Shared\FXButeMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\FXStructs.h
# End Source File
# Begin Source File

SOURCE=..\Shared\GameButeMgr.h
# End Source File
# Begin Source File

SOURCE=.\GameButes.h
# End Source File
# Begin Source File

SOURCE=.\GameClientShell.h
# End Source File
# Begin Source File

SOURCE=.\GameSettings.h
# End Source File
# Begin Source File

SOURCE=.\GibFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\GibTypes.h
# End Source File
# Begin Source File

SOURCE=..\Shared\GlobalMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\Globals.h
# End Source File
# Begin Source File

SOURCE=.\GroupCtrl.h
# End Source File
# Begin Source File

SOURCE=.\HeadBobMgr.h
# End Source File
# Begin Source File

SOURCE=.\IntelItemMgr.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceMeter.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceMgr.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceResMgr.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceSurfMgr.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceTimer.h
# End Source File
# Begin Source File

SOURCE=.\IpMgr.h
# End Source File
# Begin Source File

SOURCE=.\JoystickAxis.h
# End Source File
# Begin Source File

SOURCE=.\KeyFixes.h
# End Source File
# Begin Source File

SOURCE=.\LaserBeam.h
# End Source File
# Begin Source File

SOURCE=.\LayoutMgr.h
# End Source File
# Begin Source File

SOURCE=.\LeashFX.h
# End Source File
# Begin Source File

SOURCE=.\LensFlareFX.h
# End Source File
# Begin Source File

SOURCE=.\LightFX.h
# End Source File
# Begin Source File

SOURCE=.\LightningFX.h
# End Source File
# Begin Source File

SOURCE=.\LightScaleMgr.h
# End Source File
# Begin Source File

SOURCE=.\LineSystemFX.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\LoadingScreen.h
# End Source File
# Begin Source File

SOURCE=.\LTDecisionWnd.h
# End Source File
# Begin Source File

SOURCE=.\LTDialogueWnd.h
# End Source File
# Begin Source File

SOURCE=.\LTMaskedWnd.h
# End Source File
# Begin Source File

SOURCE=.\LTMenuWnd.h
# End Source File
# Begin Source File

SOURCE=.\LTMultiWnd.h
# End Source File
# Begin Source File

SOURCE=.\LTTextWnd.h
# End Source File
# Begin Source File

SOURCE=.\LtWnd.h
# End Source File
# Begin Source File

SOURCE=.\LTWndMessages.h
# End Source File
# Begin Source File

SOURCE=.\MarkSFX.h
# End Source File
# Begin Source File

SOURCE=.\MenuJoystickAxis.h
# End Source File
# Begin Source File

SOURCE=.\MessageBox.h
# End Source File
# Begin Source File

SOURCE=.\MessageBoxCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MessageMgr.h
# End Source File
# Begin Source File

SOURCE=.\MineFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\MissionData.h
# End Source File
# Begin Source File

SOURCE=..\Shared\MissionMgr.h
# End Source File
# Begin Source File

SOURCE=.\MissionText.h
# End Source File
# Begin Source File

SOURCE=..\Shared\ModelButeMgr.h
# End Source File
# Begin Source File

SOURCE=.\MouseMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\MsgIDs.h
# End Source File
# Begin Source File

SOURCE=.\MultiplayerMenu.h
# End Source File
# Begin Source File

SOURCE=.\Music.h
# End Source File
# Begin Source File

SOURCE=.\MuzzleFlashFX.h
# End Source File
# Begin Source File

SOURCE=.\MuzzleFlashParticleFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\NetDefs.h
# End Source File
# Begin Source File

SOURCE=.\NetInfo.h
# End Source File
# Begin Source File

SOURCE=.\NetStart.h
# End Source File
# Begin Source File

SOURCE=.\NodeController.h
# End Source File
# Begin Source File

SOURCE=.\NodeLinesFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\Objectives.h
# End Source File
# Begin Source File

SOURCE=.\ObjEditMgr.h
# End Source File
# Begin Source File

SOURCE=.\Overlays.h
# End Source File
# Begin Source File

SOURCE=.\ParticleExplosionFX.h
# End Source File
# Begin Source File

SOURCE=.\ParticleShowerFX.h
# End Source File
# Begin Source File

SOURCE=.\ParticleSystemFX.h
# End Source File
# Begin Source File

SOURCE=.\ParticleTrailFX.h
# End Source File
# Begin Source File

SOURCE=.\ParticleTrailSegmentFX.h
# End Source File
# Begin Source File

SOURCE=.\PickupItemFX.h
# End Source File
# Begin Source File

SOURCE=.\PlayerCamera.h
# End Source File
# Begin Source File

SOURCE=.\PlayerData.h
# End Source File
# Begin Source File

SOURCE=.\PlayerSoundFX.h
# End Source File
# Begin Source File

SOURCE=.\PlayerStats.h
# End Source File
# Begin Source File

SOURCE=.\PlayerVehicleFX.h
# End Source File
# Begin Source File

SOURCE=.\PlayerVehicleFX.h
# End Source File
# Begin Source File

SOURCE=.\PolyDebrisFX.h
# End Source File
# Begin Source File

SOURCE=.\PolyGridFX.h
# End Source File
# Begin Source File

SOURCE=.\PolyLineFX.h
# End Source File
# Begin Source File

SOURCE=.\PopupText.h
# End Source File
# Begin Source File

SOURCE=.\ProjectileFX.h
# End Source File
# Begin Source File

SOURCE=.\PVFXMgr.h
# End Source File
# Begin Source File

SOURCE=.\RandomSparksFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SCDefs.h
# End Source File
# Begin Source File

SOURCE=.\ScreenTintMgr.h
# End Source File
# Begin Source File

SOURCE=.\SearchLightFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\ServerOptionMgr.h
# End Source File
# Begin Source File

SOURCE=.\SFXMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SFXMsgIds.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SharedBaseFXStructs.h
# End Source File
# Begin Source File

SOURCE=.\SharedDefs.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SharedFXStructs.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SharedMission.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SharedMovement.h
# End Source File
# Begin Source File

SOURCE=.\ShellCasingFX.h
# End Source File
# Begin Source File

SOURCE=.\SliderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SmokeFX.h
# End Source File
# Begin Source File

SOURCE=.\SoundFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SoundMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SoundTypes.h
# End Source File
# Begin Source File

SOURCE=.\Sparam.h
# End Source File
# Begin Source File

SOURCE=.\SpecialFX.h
# End Source File
# Begin Source File

SOURCE=.\SpecialFXList.h
# End Source File
# Begin Source File

SOURCE=.\sprinklesfx.h
# End Source File
# Begin Source File

SOURCE=.\StaticTextCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Shared\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\SteamFX.h
# End Source File
# Begin Source File

SOURCE=.\Subtitle.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SurfaceFunctions.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SurfaceMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\TeamMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\TemplateList.h
# End Source File
# Begin Source File

SOURCE=..\Shared\Timer.h
# End Source File
# Begin Source File

SOURCE=.\TracerFX.h
# End Source File
# Begin Source File

SOURCE=.\VarTrack.h
# End Source File
# Begin Source File

SOURCE=.\VehicleMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\VersionMgr.h
# End Source File
# Begin Source File

SOURCE=.\VideoFX.h
# End Source File
# Begin Source File

SOURCE=.\VKDefs.h
# End Source File
# Begin Source File

SOURCE=.\VolumeBrushFX.h
# End Source File
# Begin Source File

SOURCE=.\WeaponChooser.h
# End Source File
# Begin Source File

SOURCE=.\WeaponFX.h
# End Source File
# Begin Source File

SOURCE=..\Shared\WeaponFXTypes.h
# End Source File
# Begin Source File

SOURCE=..\Shared\WeaponMgr.h
# End Source File
# Begin Source File

SOURCE=.\WeaponModel.h
# End Source File
# Begin Source File

SOURCE=.\WeaponStringDefs.h
# End Source File
# Begin Source File

SOURCE=.\WeatherFX.h
# End Source File
# Begin Source File

SOURCE=.\WinUtil.h
# End Source File
# End Group
# Begin Group "libs_debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Debug\LithFontMgr_LT2.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Debug\ltguimgr_LT2.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Debug\MFCStub.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Debug\CryptMgr.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Debug\StdLith.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Debug\ButeMgrNoMFC.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Debug\GameSpyClientMgr.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Lt2\lithshared\libs\Debug\RegMgr.lib
# End Source File
# End Group
# Begin Group "libs_release"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Release\StdLith.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Release\CryptMgr.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Release\LithFontMgr_LT2.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Release\ltguimgr_LT2.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Release\MFCStub.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Release\ButeMgrNoMFC.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\LT2\lithshared\libs\Release\GameSpyClientMgr.lib

!IF  "$(CFG)" == "ClientShellDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Release"

!ELSEIF  "$(CFG)" == "ClientShellDLL - Win32 Final Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Lt2\lithshared\libs\Release\RegMgr.lib
# End Source File
# End Group
# End Target
# End Project
