/*
 *  Memory.cpp
 *  MagicEcho
 *
 *  Created by Paulo on 9/29/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#include "Memory.h"
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Memory::setup (){
	analyserRef = NULL;
}
///////////////////////////////////////////////////////////////////////////////////
// hookRecorder -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Memory::hookRecorder(Recorder * recorderRef){
	this->recorderRef = recorderRef;
	ofAddListener(recorderRef->events.recordedEvt, this, &Analyser::onRecorderEchoRecorded);
}
///////////////////////////////////////////////////////////////////////////////////
// onRecorderEchoRecorded ---------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Memory::onRecorderEchoRecorded(RecorderRecordedEventArgs &args){
	cout << "Memory :: onRecorderEchoRecorded " << args.echo << endl;
	rememberEcho(args.echo);
}
///////////////////////////////////////////////////////////////////////////////////
// hookAnalyser -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Memory::hookAnalyser(Analyser * analyserRef){
	this->analyserRef = analyserRef;
	ofAddListener(analyserRef->events.analysisEvt, this, &Memory::onAnalyserAnalysis);
}
///////////////////////////////////////////////////////////////////////////////////
// onAnalyserAnalysis ---------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Memory::onAnalyserAnalysis(AnalyserAnalysisEventArgs &args){
	cout << "Memory :: onAnalyserAnalysis " << args.echo << " - " << args.length << endl;
	rememberEchoLength(args.echo, args.length);
}
///////////////////////////////////////////////////////////////////////////////////
// getEchoesByLength -------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
vector<Echo*> Memory::getEchoesByLength(int length, int tolerance){
	int maxLength = length + tolerance;
	int minLength = length - tolerance;
	
	vector<Echo*> retrievedEchoes;
	for (vector<EchoMemory*>::iterator it = echoMemoryNodes.begin(); it != echoMemoryNodes.end(); it++) {
		if((*it)->echo != NULL && (*it)->length <= maxLength && (*it)->length >= minLength)
			retrievedEchoes.push_back((*it)->echo);
		} 
	}
	return retrievedEchoes;
}
///////////////////////////////////////////////////////////////////////////////////
// rememberEcho ---------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Memory::rememberEcho(Echo *echo){
	echoes.push_back(echo);
	
	// dispatch event
	//ofNotifyEvent(events.updateEvt, events.updateEvtArgs);
}
///////////////////////////////////////////////////////////////////////////////////
// rememberEchoLength ---------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Memory::rememberEchoLength(Echo *echo, int length){
	echoMemoryNodes[echo->label].echo = echo;
	echoMemoryNodes[echo->label].length = length;
	
	// dispatch event
	ofNotifyEvent(events.updateEvt, events.updateEvtArgs);
}