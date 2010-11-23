/*
 *  Sequencer.cpp
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 21/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#include "Sequencer.h"

///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::setup(int lenght,int numSteps){
	mainSteps = new bool[SEQUENCER_MAX_NUM_STEPS];
	memset(mainSteps, 0, sizeof(int));
	setLenghtAndSteps(lenght, numSteps);
	paused = false;
	
	// metronome
	metronomeMainTick.loadSound("main-tick.wav");
	metronomeTick.loadSound("tick.wav");
	playMetronome = false;
	ofAddListener(events.tickEvt, this, &Sequencer::onSequencerTick);	
}
///////////////////////////////////////////////////////////////////////////////////
// update -------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::update(){
	if(!paused)
	{
		int intStep;
		if(firstRun) intStep = 0;
		else intStep = stepSize * float(curStep + 1) - 1;
		
		if(curSample >= intStep ){
			if(!firstRun)curStep++;
			if(curStep > numSteps - 1) curStep = 0;
			// dispatch event
			events.tickEvtArgs.step = curStep;
			ofNotifyEvent(events.tickEvt, events.tickEvtArgs);
		}
				
		curSample++;
		if (curSample > lenght - 1) curSample = 0;
		
		if(firstRun) firstRun = false;
	}
}

///////////////////////////////////////////////////////////////////////////////////
// tooglePause --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::tooglePause(){
	paused = !paused;	
}
///////////////////////////////////////////////////////////////////////////////////
// toogleMetronome ----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::toogleMetronome(){
	playMetronome = !playMetronome;	
}
///////////////////////////////////////////////////////////////////////////////////
// restart ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::restart(){
	curSample = 0;
	curStep = 0;
	firstRun = true;
}

///////////////////////////////////////////////////////////////////////////////////
// setLenghtAndSteps --------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::setLenghtAndSteps( int newLenght, int newNumSteps){
	if(newLenght > SEQUENCER_MAX_LENGH) newLenght = SEQUENCER_MAX_LENGH;
	else if(newLenght < SEQUENCER_MIN_LENGH) newLenght = SEQUENCER_MIN_LENGH;
	
	
	if(newNumSteps > SEQUENCER_MAX_NUM_STEPS) newNumSteps = SEQUENCER_MAX_NUM_STEPS;
	else if(newNumSteps < SEQUENCER_MIN_NUM_STEPS) newNumSteps = SEQUENCER_MIN_NUM_STEPS;
	
	lenght = newLenght;
	
	if(numSteps != newNumSteps){
		numSteps = newNumSteps;
		for(int i = 0; i <numSteps ; i++){
			mainSteps[i] = false;
		}
		
		restart();
	}
	else numSteps = newNumSteps;	
	
	stepSize = float(lenght) / float(numSteps);	
}
///////////////////////////////////////////////////////////////////////////////////
// setMainStep --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::setMainStep(int step){
	if(step >=0 && step <= numSteps) mainSteps[step] = true;
}
///////////////////////////////////////////////////////////////////////////////////
// removeMainStep -----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::removeMainStep(int step){
	if(step >=0 && step <= numSteps) mainSteps[step] = false;
}

///////////////////////////////////////////////////////////////////////////////////
// getLenght ----------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int Sequencer::getLenght(){
	return lenght;
}
///////////////////////////////////////////////////////////////////////////////////
// getNumSteps --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int Sequencer::getNumSteps(){
	return numSteps;	
}
///////////////////////////////////////////////////////////////////////////////////
// getCurStep ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int Sequencer::getCurStep(){
	return curStep;	
}
///////////////////////////////////////////////////////////////////////////////////
// isPaused -----------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool Sequencer::isPaused(){
	return paused;
}
///////////////////////////////////////////////////////////////////////////////////
// getMainSteps -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool* Sequencer::getMainSteps(){
	return mainSteps;
}

///////////////////////////////////////////////////////////////////////////////////
// onSequencerTick ----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Sequencer::onSequencerTick(SequencerTickEventArgs &args){
	if(playMetronome){
		if(mainSteps[curStep]) metronomeMainTick.play();
		else metronomeTick.play();
	}
}