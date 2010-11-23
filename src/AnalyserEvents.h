/*
 *  AnalyserEvents.h
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 9/30/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#ifndef _ORGANIZER_EVENTS
#define _ORGANIZER_EVENTS


#include "ofMain.h"
#include "Echo.h"

class AnalyserAnalysisEventArgs {
public:
	Echo						* echo;
	int							length;
};

class AnalyserEvents{
	
public:
	ofEvent<AnalyserAnalysisEventArgs>	analysisEvt;
	AnalyserAnalysisEventArgs			analysisEvtArgs;
};
#endif