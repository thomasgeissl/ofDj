#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"

#include "deck.h"
#include "externalDeck.h"
#include "mixer.h"

#include "ofxOsc.h"
#include "ofxWidgets.h"
#include "gui/waveForm.h"
#include "gui/deck.h"

class ofApp : public ofBaseApp{
	public:
		ofApp();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        
        pdsp::Engine _engine;
		mixer _mixer;
		externalDeck *_microphone;
		externalDeck *_externalDeckA;
		deck *_deckA;
		deck *_deckB;
		externalDeck *_externalDeckB;

		ofxOscSender _oscSender;

		ofxWidgets::gui _gui;

		waveForm::pointer _waveFormA;
		waveForm::pointer _waveFormB;
};
