/*
 *  Recorder.h
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 21/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#include "Recorder.h"
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Recorder::setup(int sampleRate, int bufferSize){
	this->sampleRate = sampleRate;
	this->bufferSize = bufferSize;
	
	recordingInfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	recordingInfo.channels = 2;	
	recordingInfo.frames = sampleRate;
	recordingInfo.samplerate = sampleRate;
	
	sampleCount = 0;
		
	//this->maxEchoes = RECORDER_MAX_ECHOES;
	
	//for (int i = 0; i < RECORDER_MAX_ECHOES; i++) echoes[i] = NULL;
	//echoes[0] = new Echo(); // this is just to make sure the echo labels will start at 1 not 0 
	
	recording = false;
	waitingFirstRecAction = false;
	
	numBufferEnergyHistory = 15;
	bufferEnergyHistory = new float[numBufferEnergyHistory];
	for(int i = 0; i < numBufferEnergyHistory; i++)bufferEnergyHistory[i] = 0;
	curBufferEnergyIndex = 0;
	
	minVol = 0.03;
	minInactiveDur = 100;
	minActiveDur = 20;
	active = false;
	inactive = true;
	inactiveCount = activeCount = 0;
	
}
///////////////////////////////////////////////////////////////////////////////////
// processAudio -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Recorder::processAudio(float * input, int bufferSize, int nChannels){
	// Get Buffer Energy
	bufferEnergy = 0;
	for (int i = 0; i < bufferSize; i++){
		input[i*2] = ofClamp(input[i*2], -1, 1);
		input[i*2+1] = ofClamp(input[i*2+1], -1, 1);
		bufferEnergy += fabs(input[i*2]);
	}
	bufferEnergy = bufferEnergy / bufferSize;
	
	bufferEnergyHistory[curBufferEnergyIndex] = bufferEnergy;
	float bufferEnergyHistorySum = 0;
	for(int i = 0; i < numBufferEnergyHistory; i++) bufferEnergyHistorySum += bufferEnergyHistory[i];
	
	smoothBufferEnergy = bufferEnergyHistorySum / numBufferEnergyHistory;
	
	curBufferEnergyIndex++;
	if(curBufferEnergyIndex > numBufferEnergyHistory - 1) curBufferEnergyIndex = 0;
	
	// Define if it is active or not
	if (smoothBufferEnergy > minVol)
	{
		activeCount++;
		inactiveCount = 0;
		startRecording();
	}
	else
	{
		inactiveCount++;
		activeCount = 0;
	}
	
	if (activeCount > minActiveDur) active = true;
	else active = false;
	
	if (inactiveCount > minInactiveDur) inactive = true;
	else inactive = false;
	
	if (recording)
	{
		if(waitingFirstRecAction)
		{
			if(inactive) stopRecording(true);
			if(active) waitingFirstRecAction = false;
		}
		else
		{
			if(inactive) stopRecording();
		}	
	}
	
	// Write the audio file
	if(recording) sf_write_float(curEcho->outfile, input, bufferSize*nChannels);
	
	// count the Samples
	sampleCount++;
}

///////////////////////////////////////////////////////////////////////////////////
// draw ---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Recorder::draw(){
	float x = ofGetWidth()/2;
	float y = ofGetHeight()/2;
	
	if(recording)
	{
		if(!waitingFirstRecAction)ofSetColor(255, 50, 50);
		else ofSetColor(255, 255, 50);			
		ofCircle(x, y, 200);
	}
	
	ofSetColor(30, 30, 30);
	ofLine(0, y, ofGetWidth(),y);
	ofLine(0, y-100, ofGetWidth(),y-100);
	
	ofSetColor(0, 0, 0);
	ofRect(x-10,y, 20, -smoothBufferEnergy*100);
	
	ofSetColor(255, 0, 0);
	ofLine(0, y-minVol*100, ofGetWidth(), y-minVol*100);
}
///////////////////////////////////////////////////////////////////////////////////
// startRecording -----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Recorder::startRecording(){
	if(!recording)
	{
		curEcho = createEcho();
		
		if (curEcho == NULL)
		{
			cout << "Recorder :: " << "Can't record. Reached the maximum number of recorded echos." << endl;
		}
		else
		{
			cout << "Recorder :: " << "Recording" << endl;
			if(curEcho->startRecording(&recordingInfo))
			{
				recording = true;
				waitingFirstRecAction = true;
			}
			else
			{
				cout << "Recorder :: " << "Recording Error. Can't start writting file." << endl;
				removeEcho (curEcho);
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////
// stopRecording ------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Recorder::stopRecording(bool dispose){
	if(recording)
	{
		recording = false;
		waitingFirstRecAction = false;		
		if(dispose)
		{
			cout << "Recorder :: " << "Audio Disposed!"<< endl;			
			removeEcho (curEcho);
		}
		else
		{
			cout << "Recorder :: " << "Audio Saved!" << endl;
			curEcho->stopRecording();
			// dispatch event
			events.recordedEvtArgs.echo = curEcho;
			ofNotifyEvent(events.recordedEvt, events.recordedEvtArgs);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////
// createEcho ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
Echo * Recorder::createEcho(){
	Echo * echo = new Echo((int)time(0));
	echoes.push_back(echo);
	return echo;
}
///////////////////////////////////////////////////////////////////////////////////
// removeEcho ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool Recorder::removeEcho(Echo * echo){
	for (vector<Echo*>::iterator it = echoes.begin(); it != echoes.end(); it++) {
		if(echo == *it){
			if(*it != NULL) delete *it;
			echoes.erase(it);
			return true;
		} 
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////////
// removeEcho ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool Recorder::removeEcho(int label){
	for (vector<Echo*>::iterator it = echoes.begin(); it != echoes.end(); it++) {
		if(echo->label == (*it)->label){
			if(*it != NULL) delete *it;
			echoes.erase(it);
			return true;
		} 
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////////
// clear --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Recorder::clear(){
	for (vector<Echo*>::iterator it = echoes.begin(); it != echoes.end(); it++) {
		if(*it != NULL) delete *it;
		echoes.erase(it);
	}
}
///////////////////////////////////////////////////////////////////////////////////
// getEchoes ----------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
vector<Echo*> Recorder::getEchoes(){
	return echoes;
}
///////////////////////////////////////////////////////////////////////////////////
// getFreeEchoLabel ---------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
/*
int Recorder::getFreeEchoLabel(){
	for(int i = 0; i < RECORDER_MAX_ECHOES; i++){
		if(echoes[i] == NULL) return i;
	}
	return RECORDER_OUT_OF_BOUNDS;
}
*/