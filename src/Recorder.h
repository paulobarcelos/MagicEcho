/*
 *  Recorder.h
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 21/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */


#ifndef _ECHO_RECORDER
#define _ECHO_RECORDER

#include "ofMain.h"
#include "Constants.h"
#include "RecorderEvents.h"
#include "Echo.h"

///////////////////////////////////////////////////////////////////////////////////
// CONSTANTS //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
// STRUCTS ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
class Recorder{
	
public:
	void			setup(int sampleRate, int bufferSize);
	void			draw();	
	void			processAudio(float * input, int bufferSize, int nChannels);
	
	bool			removeEcho(Echo * echo);
	bool			removeEcho(int label);
	
	void			clear();				// remove all echoes
	
	// getters
	//Echo**			getEchoes();
	vector<Echo*>	getEchoes();
	
	// events
	RecorderEvents	events;	
	
	//Echo			*echoes[RECORDER_MAX_ECHOES];
	vector<Echo*>	echoes;
	
private:
	void			startRecording();
	void			stopRecording(bool dispose = false);
	
	//int				getFreeEchoLabel();
	Echo*			createEcho();
	Echo*			curEcho;
	
	SF_INFO			recordingInfo;
	int				sampleRate, bufferSize;
	int				sampleCount;
	
	
	int				maxEchoes;
	
	bool			recording, waitingFirstRecAction;
	
	float			*bufferEnergyHistory, bufferEnergy, smoothBufferEnergy;
	int				numBufferEnergyHistory,curBufferEnergyIndex;
	
	float			minVol;
	int				minInactiveDur, minActiveDur;
	bool			active, inactive;
	int				inactiveCount, activeCount;
};

#endif
