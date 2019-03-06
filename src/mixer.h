#pragma once

#include "ofxPDSP.h"

class mixer : public pdsp::Patchable {
    public:
    mixer(){
        addModuleInput("leftMicrophone", _leftMicrophoneOutAmp);
        addModuleInput("rightMicrophone", _rightMicrophoneOutAmp);
        addModuleInput("leftExternalDeckA", _leftExternalDeckAOutAmp);
        addModuleInput("rightExternalDeckA", _rightExternalDeckAOutAmp);
        addModuleInput("leftDeckA", _leftDeckAOutAmp);
        addModuleInput("rightDeckA", _rightDeckAOutAmp);
        addModuleInput("leftDeckB", _leftDeckBOutAmp);
        addModuleInput("rightDeckB", _rightDeckBOutAmp);
        addModuleInput("leftExternalDeckB", _leftExternalDeckBOutAmp);
        addModuleInput("rightExternalDeckB", _rightExternalDeckBOutAmp);

        addModuleOutput("leftMaster", _leftMasterOutAmp);
        addModuleOutput("rightMaster", _rightMasterOutAmp);
        addModuleOutput("leftMonitor", _leftMonitorOutAmp);
        addModuleOutput("rightMonitor", _rightMonitorOutAmp);


        // TODO
        // * EQ
        // * Monitor

        _externalDeckAOutGain >> _dBtoLinExternalDeckAOut >> _leftExternalDeckAOutAmp.in_mod();
        _dBtoLinExternalDeckBOut >> _rightExternalDeckAOutAmp.in_mod();

        _deckAOutGain >> _dBtoLinDeckAOut >> _leftDeckAOutAmp.in_mod();
        _dBtoLinDeckAOut >> _rightDeckAOutAmp.in_mod();

        _deckBOutGain >> _dBtoLinDeckBOut >> _leftDeckBOutAmp.in_mod();
        _dBtoLinDeckBOut >> _rightDeckBOutAmp.in_mod();

        _externalDeckBOutGain >> _dBtoLinExternalDeckBOut >> _leftExternalDeckBOutAmp.in_mod();
        _dBtoLinExternalDeckBOut >> _rightExternalDeckBOutAmp.in_mod();

        _masterOutGain >> _dBtoLinMasterOut >> _leftMasterOutAmp.in_mod();
        _dBtoLinMasterOut >> _rightMasterOutAmp.in_mod();

        _leftMicrophoneOutAmp >> _leftMasterOutAmp;
        _rightMicrophoneOutAmp >> _rightMasterOutAmp;
        _leftExternalDeckAOutAmp >> _leftMasterOutAmp;
        _rightExternalDeckAOutAmp >> _rightMasterOutAmp;
        _leftDeckAOutAmp >> _leftMasterOutAmp;
        _rightDeckAOutAmp >> _rightMasterOutAmp;
        _leftDeckBOutAmp >> _leftMasterOutAmp;
        _rightDeckBOutAmp >> _rightMasterOutAmp;
        _leftExternalDeckBOutAmp >> _leftMasterOutAmp;
        _rightExternalDeckBOutAmp >> _rightMasterOutAmp;

        _parameters.setName("mixer");
        _parameters.add(_microphoneOutGain.set("gain MIC", -48.0, -48.0, 24.0));
        _parameters.add(_externalDeckAOutGain.set("gain EXT A", -48.0, -48.0, 24.0));
        _parameters.add(_deckAOutGain.set("gain A", 0.0, -48.0, 24.0));
        _parameters.add(_deckBOutGain.set("gain B", -48.0, -48.0, 24.0));
        _parameters.add(_externalDeckBOutGain.set("gain EXT B", -48.0, -48.0, 24.0));
        _parameters.add(_masterOutGain.set("gain MASTER", -48.0, -48.0, 24.0));
    }

    pdsp::DBtoLin _dBtoLinMicrophoneOut;
    pdsp::DBtoLin _dBtoLinExternalDeckAOut;
    pdsp::DBtoLin _dBtoLinDeckAOut;
    pdsp::DBtoLin _dBtoLinDeckBOut;
    pdsp::DBtoLin _dBtoLinExternalDeckBOut;
    pdsp::DBtoLin _dBtoLinMasterOut;

    pdsp::Amp _leftDeckAOutAmp;
    pdsp::Amp _rightDeckAOutAmp;
    pdsp::Amp _leftDeckBOutAmp;
    pdsp::Amp _rightDeckBOutAmp;
    pdsp::Amp _leftExternalDeckAOutAmp;
    pdsp::Amp _rightExternalDeckAOutAmp;
    pdsp::Amp _leftExternalDeckBOutAmp;
    pdsp::Amp _rightExternalDeckBOutAmp;
    pdsp::Amp _leftMicrophoneOutAmp;
    pdsp::Amp _rightMicrophoneOutAmp;

    pdsp::Amp _leftMasterOutAmp;
    pdsp::Amp _rightMasterOutAmp;
    pdsp::Amp _leftMonitorOutAmp;
    pdsp::Amp _rightMonitorOutAmp;

    // TODO: balance vs panning
    // pdsp::Panner _masterPanner;
    // pdsp::Panner _monitorPanner;

    ofParameterGroup _parameters;
    pdsp::Parameter _microphoneOutGain;    
    pdsp::Parameter _externalDeckAOutGain;    
    pdsp::Parameter _deckAOutGain;    
    pdsp::Parameter _deckBOutGain;    
    pdsp::Parameter _externalDeckBOutGain;    
    pdsp::Parameter _masterOutGain;    
};
