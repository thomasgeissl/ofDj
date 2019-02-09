#pragma once

#include "ofxPDSP.h"

class deck : public pdsp::Patchable {
    public:
    deck(std::string name = ""){
        addModuleOutput("leftMaster", _leftMasterOutAmp);
        addModuleOutput("rightMaster", _rightMasterOutAmp);
        addModuleOutput("leftMonitor", _leftMonitorOutAmp);
        addModuleOutput("rightMonitor", _rightMonitorOutAmp);

        _leftSampler.addSample(&_sample, 0);
        _rightSampler.addSample(&_sample, 1);

        _pitch >> _leftSampler.in_pitch();
        _pitch >> _rightSampler.in_pitch();
    
        _sampleTrigger >> _leftSampler >> _leftMasterOutAmp;
        _envelopeGate >> _envelope >> _leftMasterOutAmp.in_mod();
        _sampleTrigger >> _rightSampler >> _rightMasterOutAmp;
        _envelopeGate >> _envelope >> _rightMasterOutAmp.in_mod();
     
        _outGain >> _dBtoLin  >> _leftMasterOutAmp.in_mod();
        _dBtoLin  >> _rightMasterOutAmp.in_mod();

        _smooth >> _envelope.in_attack();
        _smooth >> _envelope.in_release();


        _parameters.setName("deck");
        _parameters.add(_outGain.set("gain", 24, -48, 24));
        _parameters.add(_pitch.set("pitch", 0, -24, 24));
        _parameters.add(_smooth.set("fade ms", 0, 0, 50)); 

        _sample.setVerbose(true);
    }
    void update(){
        // auto pos = _leftSampler.meter_position();
        // if(pos > 0){
        //     ofLogNotice() << pos;
        // }
    }

    void load(std::string path){
        stop();
        _sample.load(path);
    }
    void play(){
        _envelopeGate.trigger(1.0f);
        // TODO: trigger only if stopped
        _sampleTrigger.trigger(1.0f);
    }
    void pause(){
        _envelopeGate.off();          
    }
    void stop(){
        _envelopeGate.off();          
    }
    pdsp::Amp _leftMasterOutAmp;
    pdsp::Amp _rightMasterOutAmp;
    pdsp::Amp _leftMonitorOutAmp;
    pdsp::Amp _rightMonitorOutAmp;

    pdsp::TriggerControl _envelopeGate;
    pdsp::ADSR _envelope;
    
    pdsp::DBtoLin _dBtoLin;

    pdsp::TriggerControl _sampleTrigger;
    pdsp::Sampler _leftSampler;
    pdsp::Sampler _rightSampler;
    pdsp::SampleBuffer  _sample;    



    ofParameterGroup _parameters;
    pdsp::Parameter _outGain;    
    pdsp::Parameter _pitch;
    pdsp::Parameter _smooth;
};