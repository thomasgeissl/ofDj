#pragma once

#include "ofxPDSP.h"

class externalDeck : public pdsp::Patchable {
    public:
    externalDeck(std::string name = "", bool isMono = false){
        addModuleInput("left", _leftInAmp);
        addModuleInput("right", _rightInAmp);
        addModuleOutput("leftMaster", _leftMasterOutAmp);
        addModuleOutput("rightMaster", _rightMasterOutAmp);
        addModuleOutput("leftMonitor", _leftMonitorOutAmp);
        addModuleOutput("rightMonitor", _rightMonitorOutAmp);
    }
    pdsp::Amp _leftInAmp;
    pdsp::Amp _rightInAmp;
    pdsp::Amp _leftMasterOutAmp;
    pdsp::Amp _rightMasterOutAmp;
    pdsp::Amp _leftMonitorOutAmp;
    pdsp::Amp _rightMonitorOutAmp;

    ofParameterGroup _parameters;
};