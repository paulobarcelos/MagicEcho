/*
 *  Memory.h
 *  MagicEcho
 *
 *  Created by Paulo on 9/29/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#ifndef _MEMEORY
#define _MEMEORY

#include "ofMain.h"
#include "Constants.h"
#include "MemoryEvents.h"
#include "Echo.h"
#include "Recorder.h"
#include "AnalyserEvents.h"
#include "Analyser.h"

///////////////////////////////////////////////////////////////////////////////////
// CONSTANTS //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
// STRUCTS ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
struct EchoMemory{
	Echo	*echo;
	int		length;
	int		pitch;
	int		*steps;
	int		stepsCount;
};
///////////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
class Memory{
public:
	void			setup();
	void			hookRecorder(Recorder* recorderRef);
	void			hookAnalyser(Analyser* analyserRef);
	
	// getters
	vector<Echo*>	getEchoesByLength(int length, int tolerance);
	vector<Echo*>	getEchoesByPitch(int pitch, int tolerance);
	vector<Echo*>	getEchoesByStep(int step, int tolerance);
	//int				getNumLastRetrievedEchos();	// <- always call after any getEchoesBy, it informs you the bounds of the last returned array.
	
	// setter
	void			rememberEcho(Echo *echo);
	void			rememberEchoLength(Echo *echo, int length);
	void			rememberEchoPitch(Echo *echo, int pitch);
	void			rememberEchoSteps(Echo *echo, int *steps);
	
	// events
	MemoryEvents	events;
		
private:
	vector<Echo*>	echoes;
	//EchoMemory	echoMemoryNodes[RECORDER_MAX_ECHOES];
	vector<EchoMemory*>	echoMemoryNodes;
	//Echo*			retrievedEchos[RECORDER_MAX_ECHOES];
	//Echo*			retrievedEchos;
	//Echo			*retrievedEchosPtr;
	//int				numRetrievedEchos;
	
	Recorder*		recorderRef;
	Analyser*		analyserRef;
	
	void			onRecorderEchoRecorded (RecorderRecordedEventArgs &args);
	void			onAnalyserAnalysis (AnalyserAnalysisEventArgs &args);
};

#endif