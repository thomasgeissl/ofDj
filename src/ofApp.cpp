#include "ofApp.h"

ofApp::ofApp() : 
    _deckA(new deck("A")),
    _deckB(new deck("B")),
    _externalDeckA(new externalDeck("EXT A")),
    _externalDeckB(new externalDeck("B")),
    _microphone(new externalDeck("MIC", true))
    {

}

void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    _engine.listDevices();
    _engine.setDeviceID(2);
    _engine.setChannels(2, 2);
    _engine.setup(44100, 512, 3);

    _microphone->out("leftMaster") >> _mixer.in("leftMicrophone");
    _microphone->out("rightMaster") >> _mixer.in("rightMicrophone");
    _externalDeckA->out("leftMaster") >> _mixer.in("leftExternalDeckA");
    _externalDeckA->out("rightMaster") >> _mixer.in("rightExternalDeckA");
    _deckA->out("leftMaster") >> _mixer.in("leftDeckA");
    _deckA->out("rightMaster") >> _mixer.in("rightDeckA");
    _deckB->out("leftMaster") >> _mixer.in("leftDeckB");
    _deckB->out("rightMaster") >> _mixer.in("rightDeckB");
    _externalDeckB->out("leftMaster") >> _mixer.in("leftExternalDeckB");
    _externalDeckB->out("rightMaster") >> _mixer.in("rightExternalDeckB");

    // _engine.audio_in(0) >> _mixer.in("leftExternalA");
    // _engine.audio_in(1) >> _mixer.in("rightExternalA");
    // _engine.audio_in(2) >> _mixer.in("leftExternalB");
    // _engine.audio_in(3) >> _mixer.in("rightExternalB");
    // _engine.audio_in(4) >> _mixer.in("leftMicrophone");

    _mixer.out("leftMaster") >> _engine.audio_out(0);
    _mixer.out("rightMaster") >> _engine.audio_out(1);

    // _mixer.out("leftMonitor") >> _engine.audio_out(2);
    // _mixer.out("rightMonitor") >> _engine.audio_out(3);

    ofSetEscapeQuitsApp(false);

    // ofLogNotice() << ofFilePath::getUserHomeDir();
    _deckA->load("/Users/thomasgeissl/Desktop/Radiohead_Idioteque.mp3");
    // _deckA->load("~/Desktop/Radiohead_Idioteque.mp3");
    _deckB->load("/Users/thomasgeissl/Desktop/AnimalCollective_LeafHouse.mp3");

    // _deckA->play();
    _deckB->play();
}

void ofApp::update(){
    // _microphone->update();
    // _externalDeckA->update();
    _deckA->update();
    // _deckB->update();
    // _externalDeckB->update();
    // _mixer.update();
}
void ofApp::draw(){
    auto channelWidth = ofGetWidth()/13;

    // MIC
    ofSetColor(ofColor::lightGrey);
    auto x = 0;
    ofDrawRectangle(x, 0, channelWidth, ofGetHeight());
    x += channelWidth;

    // EXT A
    ofSetColor(ofColor::lightBlue);
    ofDrawRectangle(x, 0, channelWidth, ofGetHeight());
    x += channelWidth;

    // A
    ofSetColor(ofColor::darkBlue);
    ofDrawRectangle(x, 0, channelWidth*4, ofGetHeight());
    x += channelWidth*4;

    // B
    ofSetColor(ofColor::darkRed);
    ofDrawRectangle(x, 0, channelWidth*4, ofGetHeight());
    x += channelWidth*4;

    // EXT B
    ofSetColor(ofColor::mistyRose);
    ofDrawRectangle(x, 0, channelWidth, ofGetHeight());
    x += channelWidth;

    // MASTER
    ofSetColor(ofColor::purple);
    ofDrawRectangle(x, 0, channelWidth*2, ofGetHeight());
    x += channelWidth;
}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){
    switch (key)
    {
        case 'f':
            ofToggleFullscreen();
            break;
        default:
            break;
    }
}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
void ofApp::gotMessage(ofMessage msg){}
