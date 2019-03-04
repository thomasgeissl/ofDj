#pragma once

#include "ofxPDSP.h"

class waveForm {
    public:
    waveForm(){
    }
    void setSample(pdsp::SampleBuffer & sample){
        _sample = sample;
        // _leftPlotter.setWaveform(_sample, 0, ofColor::blue, 640, 100);
        // _rightPlotter.setWaveform(_sample, 1, ofColor::blue, 640, 100);
    }
    void draw(float x, float y, float width, float height){
        ofSetColor(ofColor::green);
        // ofDrawRectangle(x, y, width, height);
        
        ofBeginShape();
        if(_sample.length > 0){
            for( auto xWave=0; xWave<width; ++xWave){
                int n = ofMap( xWave, 0, width, 0, _sample.length, true );
                float val = _sample.buffer[0][n];
                float yWave = ofMap( val, -1.0f, 1.0f, height*0.5, 0.0f );
                ofVertex( x + xWave, y+yWave );       
            }
        }
        ofEndShape();
        y += height/2;
        ofBeginShape();
        if(_sample.length > 0){
            for( auto xWave=0; xWave<width; ++xWave){
                int n = ofMap( xWave, 0, width, 0, _sample.length, true );
                float val = _sample.buffer[1][n];
                float yWave = ofMap( val, -1.0f, 1.0f, height*0.5, 0.0f );
                ofVertex( x + xWave, y+yWave );       
            }
        }
        ofEndShape();
        _leftPlotter.draw(x, y, width, height);
        _rightPlotter.draw(x, y+height, width, height);

        float playhead = _playhead * width;
        ofSetColor(ofColor::black);
        ofDrawRectangle(x+playhead, y, 3, height);
    }
    pdsp::SampleBufferPlotter _leftPlotter;
    pdsp::SampleBufferPlotter _rightPlotter;
    pdsp::SampleBuffer  _sample;    
    ofParameterGroup _parameters;
    float _playhead;
};
