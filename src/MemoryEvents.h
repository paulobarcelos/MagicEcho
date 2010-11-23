/*
 *  MemoryEvents.h
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 10/1/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#ifndef _MEMORY_EVENTS
#define _MEMORY_EVENTS


#include "ofMain.h"
#include "Echo.h"

class MemoryUpadateEventArgs {
public:
	
};

class MemoryEvents{
	
public:
	ofEvent<MemoryUpadateEventArgs>	updateEvt;
	MemoryUpadateEventArgs			updateEvtArgs;
};
#endif