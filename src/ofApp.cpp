#include "ofApp.h"

ofApp::ofApp() : _deckA(new deck("A")),
                 _deckB(new deck("B")),
                 _externalDeckA(new externalDeck("EXT A")),
                 _externalDeckB(new externalDeck("B")),
                 _microphone(new externalDeck("MIC", true))
{
}

void ofApp::setup()
{
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

    _deckA->play();
    // _deckB->play();

    auto mainLayout = ofxWidgets::layout::hBox::create(_gui.getViewWidth(), _gui.getViewHeight());
    auto unitWidth = mainLayout->getViewWidth() / 13;
    auto unitHeight = mainLayout->getViewHeight();

    auto micWidget = ofxWidgets::widget::create(unitWidth, unitHeight);
    mainLayout->add(micWidget);
    auto micLayout = ofxWidgets::layout::vBox::createAndAddTo(micWidget);
    micLayout->add(ofxWidgets::label::create("MIC", micLayout->getViewWidth(), 40));
    micLayout->add(ofxWidgets::floatSlider::create(_microphone->_masterOutGain.getOFParameterFloat(), micLayout->getViewWidth(), 40, ofxWidgets::floatSlider::style::vertical));

    auto extDeckAWidget = ofxWidgets::widget::create(unitWidth, unitHeight);
    mainLayout->add(extDeckAWidget);
    auto extDeckALayout = ofxWidgets::layout::vBox::createAndAddTo(extDeckAWidget);
    extDeckALayout->add(ofxWidgets::label::create("EXT A", extDeckALayout->getViewWidth(), 40));
    extDeckALayout->add(ofxWidgets::floatSlider::create(_externalDeckA->_masterOutGain.getOFParameterFloat(), extDeckALayout->getViewWidth(), 40, ofxWidgets::floatSlider::style::vertical));

    auto deckAWidget = ofxWidgets::widget::create(unitWidth * 4, unitHeight);
    mainLayout->add(deckAWidget);
    auto deckALayout = ofxWidgets::layout::vBox::createAndAddTo(deckAWidget);
    deckALayout->add(ofxWidgets::label::create("A", deckALayout->getViewWidth(), 40));

    auto deckBWidget = ofxWidgets::widget::create(unitWidth * 4, unitHeight);
    mainLayout->add(deckBWidget);
    auto deckBLayout = ofxWidgets::layout::vBox::createAndAddTo(deckBWidget);
    deckBLayout->add(ofxWidgets::label::create("B", deckBLayout->getViewWidth(), 40));

    auto extDeckBWidget = ofxWidgets::widget::create(unitWidth, unitHeight);
    mainLayout->add(extDeckBWidget);
    auto extDeckBLayout = ofxWidgets::layout::vBox::createAndAddTo(extDeckBWidget);
    extDeckBLayout->add(ofxWidgets::label::create("EXT B", extDeckBLayout->getViewWidth(), 40));
    extDeckBLayout->add(ofxWidgets::floatSlider::create(_externalDeckB->_masterOutGain.getOFParameterFloat(), extDeckBLayout->getViewWidth(), 40, ofxWidgets::floatSlider::style::vertical));

    auto masterWidget = ofxWidgets::widget::create(unitWidth * 2, unitHeight);
    mainLayout->add(masterWidget);
    auto masterLayout = ofxWidgets::layout::vBox::createAndAddTo(masterWidget);
    masterLayout->add(ofxWidgets::label::create("MASTER", masterLayout->getViewWidth(), 40));
    masterLayout->add(ofxWidgets::floatSlider::create(_mixer._masterOutGain.getOFParameterFloat(), masterLayout->getViewWidth(), 40, ofxWidgets::floatSlider::style::vertical));

    _gui.add(mainLayout);

    // # style
    ofFile file("themes/default.json");
    ofJson theme;
    file >> theme;
    _gui.setTheme(theme);
}

void ofApp::update()
{
    // _microphone->update();
    // _externalDeckA->update();
    _deckA->update();
    // _deckB->update();
    // _externalDeckB->update();
    // _mixer.update();
}
void ofApp::draw()
{
    // auto channelWidth = ofGetWidth()/13;

    // // MIC
    // ofSetColor(ofColor::lightGrey);
    // auto x = 0;
    // ofDrawRectangle(x, 0, channelWidth, ofGetHeight());
    // x += channelWidth;

    // // EXT A
    // ofSetColor(ofColor::lightBlue);
    // ofDrawRectangle(x, 0, channelWidth, ofGetHeight());
    // x += channelWidth;

    // // A
    // ofSetColor(ofColor::darkBlue);
    // ofDrawRectangle(x, 0, channelWidth*4, ofGetHeight());
    // _deckAWave._playhead = _deckA->playhead();
    // _deckAWave.draw(x, 200, channelWidth*4, 100);
    // x += channelWidth*4;

    // // B
    // ofSetColor(ofColor::darkRed);
    // ofDrawRectangle(x, 0, channelWidth*4, ofGetHeight());
    // _deckBWave._playhead = _deckB->playhead();
    // _deckBWave.draw(x, 200, channelWidth*4, 100);
    // x += channelWidth*4;

    // // EXT B
    // ofSetColor(ofColor::mistyRose);
    // ofDrawRectangle(x, 0, channelWidth, ofGetHeight());
    // x += channelWidth;

    // // MASTER
    // ofSetColor(ofColor::purple);
    // ofDrawRectangle(x, 0, channelWidth*2, ofGetHeight());
    // x += channelWidth;
}

void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key)
{
    switch (key)
    {
    case 'f':
        ofToggleFullscreen();
        break;
    case 'r':
        // _deckAWave.setSample(_deckA->_sample);
        // _deckBWave.setSample(_deckB->_sample);
        break;
    default:
        break;
    }
}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
void ofApp::gotMessage(ofMessage msg) {}
