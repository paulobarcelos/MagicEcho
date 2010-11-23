/*
 *  Sequencer.h
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 21/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#ifndef _SEQUENCER
#define _SEQUENCER

#include "ofMain.h"
#include "Constants.h"
#include "SequencerEvents.h"

///////////////////////////////////////////////////////////////////////////////////
// CONSTANTS //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
// STRUCTS ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
class Sequencer{
	
public:
	void			setup(int lenght,int numSteps);
	void			update();	
	void			tooglePause();	
	void			toogleMetronome();
	void			restart();	
	
	// setters
	void			setLenghtAndSteps(int newLenght,int newNumSteps);
	void			setMainStep(int step);
	void			removeMainStep(int step);
	
	// getters
	int				getLenght();
	int				getNumSteps();
	int				getCurStep();
	bool			isPaused();
	bool*			getMainSteps();
	
	// events
	SequencerEvents	events;
	
private:
	bool			firstRun;
		
	int				lenght;
	float			stepSize;
	int				numSteps, curStep, curStepCheck;
	bool			paused;
		
	int				curSample;
	
	ofSoundPlayer	metronomeMainTick, metronomeTick;
	bool			playMetronome;
	bool			*mainSteps;
	void			onSequencerTick (SequencerTickEventArgs &args);
	
};

#endif
