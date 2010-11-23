/*
 *  Echo.h
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 24/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#ifndef _ECHO
#define _ECHO

#include "ofMain.h"
#include "SequencerEvents.h"
#include <sndfile.h>

///////////////////////////////////////////////////////////////////////////////////
// CONSTANTS //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
#define				saveFolder "../../../data/"

///////////////////////////////////////////////////////////////////////////////////
// STRUCTS ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
class Echo{
	
public:
	
	Echo(int label = NULL);
	~Echo();
	
	bool			startRecording(SF_INFO * recordingInfo);
	void			stopRecording();
	
	int				label;
	string          filename;
	ofSoundPlayer	soundPlayer;
	SNDFILE			*outfile;
	bool			isRecorded;
};

#endif