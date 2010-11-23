/*
 *  Composer.cpp
 *  MagicEcho
 *
 *  Created by Paulo on 10/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Composer.h"
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Composer::setup (){

}
///////////////////////////////////////////////////////////////////////////////////
// hookMemory ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Composer::hookMemory(Memory * memoryRef){
	this->memoryRef = memoryRef;
	ofAddListener(memoryRef->events.updateEvt, this, &Composer::onMemoryUpdate);
}
///////////////////////////////////////////////////////////////////////////////////
// hookPlayer ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Composer::hookPlayer(Player * playerRef){
	this->playerRef = playerRef;
}
///////////////////////////////////////////////////////////////////////////////////
// onMemoryUpdate -----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Composer::onMemoryUpdate(MemoryUpadateEventArgs &args){
	cout << "Composer :: onMemoryUpdate " << endl;
	Echo** echoes = memoryRef->getEchoesByLength(40000, 3000);
	for(int i = 0; i<memoryRef->getNumLastRetrievedEchos(); i++){
		cout<< echoes[i] << endl;
		//echoes[i]->soundPlayer.play();
	}
}

