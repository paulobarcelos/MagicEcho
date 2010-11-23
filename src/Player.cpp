/*
 *  Player.cpp
 *  MagicEcho
 *
 *  Created by Paulo on 9/21/10.
 * Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#include "Player.h"
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Player::setup(){
	
}
///////////////////////////////////////////////////////////////////////////////////
// hookSequencer -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Player::hookSequencer(Sequencer * sequencerRef){
	this->sequencerRef = sequencerRef;	
	ofAddListener(sequencerRef->events.tickEvt, this, &Player::onSequencerTick);	
	createSequenceTable(sequencerRef->getNumSteps());
}
///////////////////////////////////////////////////////////////////////////////////
// addEchoAtStep ---------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool Player::addEchoAtStep(int echoLabel, int step){
	for(int i = 0; i < PLAYER_MAX_ECHOES_PER_STEP; i++){
		int tableIndex = step * PLAYER_MAX_ECHOES_PER_STEP + i;
		if(!sequenceTable[tableIndex])
		{
			sequenceTable[tableIndex] = echoLabel;
			return true;
		}
	}
	cout << "Player :: Could't add echo in step. Step is alredy full." << endl;
	return false;
}
///////////////////////////////////////////////////////////////////////////////////
// onSequencerTick ----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Player::onSequencerTick(SequencerTickEventArgs &args){
	//cout << "Player :: onSequencerTick " << args.step << endl;
	for(int i = 0; i < PLAYER_MAX_ECHOES_PER_STEP; i++){
		int tableIndex = args.step * PLAYER_MAX_ECHOES_PER_STEP + i;
		if(sequenceTable[tableIndex]){
			recorderRef->echoes[int(sequenceTable[tableIndex])]->soundPlayer.play();
			cout << "Player :: playing echo " << recorderRef->echoes[int(sequenceTable[tableIndex])]->label<< endl;
		}
	}	
}
///////////////////////////////////////////////////////////////////////////////////
// createSequenceTable ------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Player::createSequenceTable(int numSteps){
	sequenceTable = new int [numSteps * PLAYER_MAX_ECHOES_PER_STEP]; 
	for (int i = 0; i < numSteps * PLAYER_MAX_ECHOES_PER_STEP; i++) sequenceTable[i] = NULL;
}
///////////////////////////////////////////////////////////////////////////////////
// getSequenceTable ---------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int* Player::getSequenceTable(){
	return sequenceTable;
}