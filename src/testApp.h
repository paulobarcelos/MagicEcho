#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Recorder.h"
#include "Sequencer.h"
#include "Player.h"
#include "Analyser.h"
#include "Memory.h"
#include "Composer.h"

///////////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
class testApp : public ofBaseApp{

	public:
		void			setup();
		void			update();
		void			draw();
		void			exit();
	
		void			keyPressed  (int key);
		void			keyReleased(int key);
		void			mouseMoved(int x, int y );
		void			mouseDragged(int x, int y, int button);
		void			mousePressed(int x, int y, int button);
		void			mouseReleased(int x, int y, int button);
		void			windowResized(int w, int h);
	
		void			audioReceived(float * input, int bufferSize, int nChannels);
	
		int				sampleRate,bufferSize;
		
		
		Recorder		recorder;
		Sequencer		sequencer;
		Player			player;
		Analyser		analyser;
		Memory			memory;
		Composer		composer;
		
};

#endif
