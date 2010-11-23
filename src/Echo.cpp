/*
 *  Echo.cpp
 *  MagicEcho
 *
 *  Created by Paulo Barcelos on 24/08/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#include "Echo.h"

///////////////////////////////////////////////////////////////////////////////////
// constructor --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
Echo::Echo(int label){
	
	printf("new echo\n");
	this->label = label;
	
	ostringstream labelStr;
	labelStr<<label;
	filename="echo"+labelStr.str()+".wav";
	
	soundPlayer.length = 0;	
	soundPlayer.setMultiPlay(true);
	
	outfile = NULL;
	
	isRecorded = false;
	
}
///////////////////////////////////////////////////////////////////////////////////
// destructor ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
Echo::~Echo(){
	soundPlayer.unloadSound();
	string tempFilapath = saveFolder+filename;
	if(remove( tempFilapath.c_str() ) != 0 ) perror( "Error deleting file" );
}
///////////////////////////////////////////////////////////////////////////////////
// startRecording ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool Echo::startRecording(SF_INFO * recordingInfo){
	string tempFilapath = saveFolder+filename;
	outfile = sf_open (tempFilapath.c_str(), SFM_WRITE, recordingInfo) ;
	bool success;
	if (!outfile)
	{
		cerr<<"Error opening ["<<tempFilapath<<"] : "<<sf_strerror (outfile)<<endl;
		success = false;
		return success;
	}
	success = true;
	return success;	
}

///////////////////////////////////////////////////////////////////////////////////
// stopRecording ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void Echo::stopRecording(){
	sf_close(outfile);
	soundPlayer.loadSound(filename);
	isRecorded = true;
}
