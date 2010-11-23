/*
 *  Analyser.cpp
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 24/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#include "Analyser.h"
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Analyser::setup (){
	
}
///////////////////////////////////////////////////////////////////////////////////
// hookRecorder -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Analyser::hookRecorder(Recorder * recorderRef){
	this->recorderRef = recorderRef;
	ofAddListener(recorderRef->events.recordedEvt, this, &Analyser::onRecorderEchoRecorded);
}
///////////////////////////////////////////////////////////////////////////////////
// onRecorderEchoRecorded ---------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Analyser::onRecorderEchoRecorded(RecorderRecordedEventArgs &args){
	cout << "Analyser :: onRecorderEchoRecorded " << args.echo << endl;
	analyseEcho(args.echo);
}

///////////////////////////////////////////////////////////////////////////////////
// analyseEcho --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Analyser::analyseEcho(Echo * echo){
	
	//addEchoAtStep(echo, (rand() % sequencerRef->getNumSteps()));
	// dispatch event
	events.analysisEvtArgs.echo = echo;
	events.analysisEvtArgs.length = echo->soundPlayer.length;
	ofNotifyEvent(events.analysisEvt, events.analysisEvtArgs);
}
///////////////////////////////////////////////////////////////////////////////////
// addEchoAtStep ------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool Analyser::addEchoAtStep(Echo * echo, int step){
	//playerRef->addEchoAtStep(echo->label, step);
	
}
