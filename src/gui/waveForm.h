#pragma once

#include "ofxPDSP.h"
#include "ofxWidgets.h"

class waveForm : public ofxWidgets::widget
{
  public:
    typedef std::shared_ptr<waveForm> pointer;
    static pointer create(ofxWidgets::widget::pointer w)
    {
        return create(w->getViewWidth(), w->getViewHeight());
    }
    static pointer create(int width, int height)
    {
        return std::make_shared<waveForm>(width, height);
    }
    waveForm(int width, int height) : widget(width, height)
    {
    }
    void setSample(pdsp::SampleBuffer &sample)
    {
        _sample = sample;
        // _leftPlotter.setWaveform(_sample, 0, ofColor::blue, 640, 100);
        // _rightPlotter.setWaveform(_sample, 1, ofColor::blue, 640, 100);
    }
    virtual void update()
    {
        setNeedsToBeRedrawn(true);
        if (_needsToBeRedrawn)
        {
            widget::update();
            begin(false);
            ofFill();
            ofSetColor(_color);
            auto x = 0;
            auto y = _contentHeight / 2;
            ofBeginShape();
            if (_sample.length > 0)
            {
                for (auto xWave = 0; xWave < _contentWidth; ++xWave)
                {
                    int n = ofMap(xWave, 0, _contentWidth, 0, _sample.length, true);
                    float val = _sample.buffer[0][n];
                    float yWave = ofMap(val, -1.0f, 1.0f, _contentHeight * 0.5, 0.0f);
                    ofVertex(x + xWave, y + yWave);
                }
            }
            ofEndShape();
            ofBeginShape();
            if (_sample.length > 0)
            {
                for (auto xWave = 0; xWave < _contentWidth; ++xWave)
                {
                    int n = ofMap(xWave, 0, _contentWidth, 0, _sample.length, true);
                    float val = _sample.buffer[1][n];
                    float yWave = ofMap(val, -1.0f, 1.0f, _contentHeight * 0.5, 0.0f);
                    ofVertex(x + xWave, y + yWave);
                }
            }
            ofEndShape();
            end();
            setNeedsToBeRedrawn(true);
        }
    }

  private:
    pdsp::SampleBuffer _sample;
};
