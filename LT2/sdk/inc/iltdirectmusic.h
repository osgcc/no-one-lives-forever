/****************************************************************************
;
;	MODULE:		ILTDirectMusic (.H)
;
;	PURPOSE:	Define types and classes that need to be exposed to the game 
;				for the	Lithtech implementation of directmusic.
;
;	HISTORY:	Aug-1-1999 [BLB]
;
;	NOTICE:		Copyright (c) 1999 Monolith Procutions, Inc.
;
***************************************************************************/

#ifndef __ILTDIRECTMUSIC_H__
#define __ILTDIRECTMUSIC_H__

// types used to describe when to start playing a segment or motif or doing a stop, or anything else
// that reqires some type of change
enum LTDMEnactTypes 
{
	LTDMEnactInvalid = 0,
	LTDMEnactDefault,
	LTDMEnactImmediatly,
	LTDMEnactNextBeat,
	LTDMEnactNextMeasure,
	LTDMEnactNextGrid,
	LTDMEnactNextSegment
};


// Main class for LTDirectMusicMgr
class ILTDirectMusicMgr
{
public:

	// Initialize the Mgr getting initial parameters from the described control file
	virtual LTRESULT Init() = 0;

	// Terminate the mgr
	virtual LTRESULT Term() = 0;

	// Initialize a game level using the parameters in the given control file (up to 3 optional 
	// defines can be given to use when processing the control file)
	virtual LTRESULT InitLevel(const char* sWorkingDirectory, const char* sControlFileName, const char* sDefine1 = NULL,
				   const char* sDefine2 = NULL, const char* sDefine3 = NULL) = 0;

	// Teminate the current game level
	virtual LTRESULT TermLevel() = 0;

	// Begin playing music
	virtual LTRESULT Play() = 0;

	// Stop playing music
	virtual LTRESULT Stop(const LTDMEnactTypes nStart = LTDMEnactDefault) = 0;

	// Pause music playing
	virtual LTRESULT Pause(const LTDMEnactTypes nStart = LTDMEnactDefault) = 0;

	// UnPause music playing
	virtual LTRESULT UnPause() = 0;

	// Set current volume
	virtual LTRESULT SetVolume(const long nVolume) = 0;

	// Change the intensity level
	virtual LTRESULT ChangeIntensity(const int nNewIntensity, const LTDMEnactTypes nStart = LTDMEnactInvalid) = 0;

	// Play a secondary segment
	virtual LTRESULT PlaySecondary(const char* sSecondarySegment, const LTDMEnactTypes nStart = LTDMEnactDefault) = 0;

	// Stop all secondary segments with the specified name (if NULL it stops them all)
	virtual LTRESULT StopSecondary(const char* sSecondarySegment = NULL, const LTDMEnactTypes nStart = LTDMEnactDefault) = 0;

	// Play a motif with the specified name from the specified style if style is NULL find it in any style
	virtual LTRESULT PlayMotif(const char* sStyleName, const char* sMotifName, const LTDMEnactTypes nStart = LTDMEnactDefault) = 0;

	// Stop all motifs with the specified name in the specified style (if Style name is NULL it looks in all styles) (if Motif name is NULL it stops them all)
	virtual LTRESULT StopMotif(const char* sStyleName, const char* sMotifName = NULL, const LTDMEnactTypes nStart = LTDMEnactDefault) = 0;

	// return the current intenisty
	virtual int GetCurIntensity() = 0;

	// convert a string to an enact type
	virtual LTDMEnactTypes StringToEnactType(const char* sName) = 0;

	// convert an enact type to a string
	virtual void EnactTypeToString(LTDMEnactTypes nType, char* sName) = 0;

	// return the number of intensities currently in this level (undefined if not in a level)
	virtual int GetNumIntensities() = 0;

	// return the initial intensity value for this level
	virtual int GetInitialIntensity() = 0;

	// return the initial intensity value for this level
	virtual long GetInitialVolume() = 0;

};

#endif // __ILTDIRECTMUSIC_H__