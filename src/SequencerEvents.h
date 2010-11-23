/*
 *  SequencerEvents.h
 *  MagicEcho
 *
 *  Created by paulo on 24/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#ifndef _SEQUENCER_EVENTS
#define _SEQUENCER_EVENTS


#include "ofMain.h"

class SequencerTickEventArgs {
public:
	int							step;
};

class SequencerEvents{
	
public:
	ofEvent<SequencerTickEventArgs> tickEvt;
	SequencerTickEventArgs			tickEvtArgs;
};
#endif