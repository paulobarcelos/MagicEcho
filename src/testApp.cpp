#include "testApp.h"

///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::setup(){
    	
	ofSetFrameRate(60);	
	ofBackground(255,255,255);
	
	sampleRate = 44100;	
	bufferSize = 256;	
	ofSoundStreamSetup(0,2,this, sampleRate, bufferSize, 4);
	
	recorder.setup(sampleRate, bufferSize);
	// Set up the step sequencer
	// - lenght of the sequence loop (in samples) | 1 second ~= sampleRate / bufferSize;
	// - number of steps in the sequence
	sequencer.setup(2 * (sampleRate / bufferSize), 8);
	sequencer.setMainStep(0);
	sequencer.setMainStep(5);	
	
	analyser.setup();
	memory.setup();
	player.setup();
	composer.setup();
	
	// hook the elements
	analyser.hookRecorder(&recorder);
	
	memory.hookAnalyser(&analyser);
	player.hookSequencer(&sequencer);
	composer.hookMemory(&memory);
	composer.hookPlayer(&player);
}

///////////////////////////////////////////////////////////////////////////////////
// update --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::update(){

}
///////////////////////////////////////////////////////////////////////////////////
// draw --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::draw(){
	recorder.draw();
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 20,20);	
}
///////////////////////////////////////////////////////////////////////////////////
// exit ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::exit(){
	recorder.clear();
}
///////////////////////////////////////////////////////////////////////////////////
// audioReceived ------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::audioReceived (float * input, int bufferSize, int nChannels){			
	recorder.processAudio(input, bufferSize, nChannels);
	sequencer.update();
}
///////////////////////////////////////////////////////////////////////////////////
// keyPressed ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::keyPressed  (int key){
	switch (key){
		case ' ':
			sequencer.toogleMetronome();
			break;
	}
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}