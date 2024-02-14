#ifndef WAVESHAPER_H
#define WAVESHAPER_H

#include "../../Parameters/AudioParameter.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input sanples
 ***************************************************************/
using namespace daisysp;

class WaveShaper
{
public:

    void init(DaisySeed* seed);
    void tick();

    inline void setBypass(int b) { bypass.value = b; }
    inline void setInput(float i) { input.value = i; }
    inline void setWaveShape(int ws) { waveShape.value = ws; }
    
    void prepare();
    void calculateAutoGain();
    void process();

private:

    ParameterWrapper<int> bypass;
    ParameterWrapper<float> input;
    ParameterWrapper<int> waveShape;

    float gain;
};

#endif