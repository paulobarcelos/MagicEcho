/*
 *  RecorderEvents.h
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 24/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#ifndef _RECORDER_EVENTS
#define _RECORDER_EVENTS


#include "ofMain.h"
#include "Echo.h"

class RecorderRecordedEventArgs {
public:
	Echo						* echo;
};

class RecorderEvents{
	
public:
	ofEvent<RecorderRecordedEventArgs>	recordedEvt;
	RecorderRecordedEventArgs			recordedEvtArgs;
};
#endif